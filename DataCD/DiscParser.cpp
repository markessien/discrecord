// DiscParser.cpp: Implementierung der Klasse CDiscParser.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DiscParser.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CDiscParser::CDiscParser(IDiscReader* pReader) : m_pReader(pReader), m_root(NULL)
{
	memset(&m_volDescPrimary, 0, sizeof(VolumeDesc));
	memset(&m_volDescSecondary, 0, sizeof(VolumeDesc));
}

CDiscParser::~CDiscParser()
{
	m_root.DestroySubItems(&m_root);
}

bool CDiscParser::ReadVolumeDescriptors(bool bFromFirstSession)
{
	memset(&m_volDescSecondary, 0, sizeof(VolumeDesc));
	memset(&m_volDescPrimary, 0, sizeof(VolumeDesc));

	m_pReader->InitDiscRead(0);

	long nSessionStart = bFromFirstSession ? 0 : m_pReader->GetLastSessionLBA();
	m_pReader->ReadFromDisc((BYTE*)&m_volDescPrimary, nSessionStart + 16, 1, true);

	if (strncmp(m_volDescPrimary.id, "CD001", 5) == 0)
	{
		int nOffset = nSessionStart + 17;
		// We have a pvd. We try to read the svd
		m_pReader->ReadFromDisc((BYTE*)&m_volDescSecondary, nOffset, 1, true);
		
		do 
		{
			nOffset++;
			switch (m_volDescSecondary.type[0])
			{
			case 0x02: // svd, maybe joliet
				{
					if (strncmp(m_volDescSecondary.id, "CD001", 5) == 0)
					{
						if (m_volDescSecondary.escape_sequences[0] == 37 &&
							m_volDescSecondary.escape_sequences[1] == 47)
						{
							// this is a joliet svd
							return true;
						}
					}
				}
				break;
			case 0xFF: // terminator
				return true;
			}

			if (nOffset > 32)
				return true; // wierd
		}
		while(m_pReader->ReadFromDisc((BYTE*)&m_volDescSecondary, nOffset, 1, true));
	}

	return false;
}

bool CDiscParser::LoadDirectoryStructure()
{
	m_root.DestroySubItems(&m_root);

	if (strncmp(m_volDescSecondary.id, "CD001", 5) == 0)
	{
		memcpy(&m_iso9660root, m_volDescSecondary.root_dir, 34);
		return ReadDirectory(&m_iso9660root, &m_root, true);
	}

	if (strncmp(m_volDescPrimary.id, "CD001", 5) == 0)
	{
		memcpy(&m_iso9660root, m_volDescPrimary.root_dir, 34);
		return ReadDirectory(&m_iso9660root, &m_root, false);
	}

	return false;
}

long CDiscParser::BothEndianDWORDtoLong(char szValue[])
{
	DWORD dwLittle = 0;
	DWORD dwBig = 0;

	memcpy(&dwLittle, &szValue[0], 4);
	memcpy(&dwBig, &szValue[4], 4);

	char szBig[4] = {0};

	szBig[0] = (BYTE)(dwBig >> 24);
	szBig[1] = (BYTE)(dwBig >> 16);
	szBig[2] = (BYTE)(dwBig >> 8);
	szBig[3] = (BYTE)(dwBig);

	memcpy(&dwBig, &szBig[0], 4);
	
	ASSERT(dwBig == dwLittle);

	if (dwLittle == 0)
		return dwBig;

	return dwLittle;
}

bool CDiscParser::ReadDirectory(CDiscParser::iso9660_dir *pDir, CFileRecord *pTargetRecord, bool bUnicode)
{
	USES_CONVERSION;

	long nDirDataPos = BothEndianDWORDtoLong(pDir->dr_data_pos);
	long nDirDataLen = BothEndianDWORDtoLong(pDir->dr_data_len);

	// If directory
	if (pDir->dr_file_flags[0] & 2)
	{
		if (nDirDataLen > ((1024* 1024) * 10)) // we check that it is less than 10 mb
		{
			ASSERT(FALSE);
			return false;
		}

		// Allocate buffer for the entire dire table
		long nBlocks = (nDirDataLen/2048) + 1;
		BYTE* pData = new BYTE[nBlocks * 2048];
		memset(pData, 0, nBlocks * 2048);

		// Read entire dir table into mem
		
		if (m_pReader->ReadFromDisc(pData, nDirDataPos, nBlocks, true) == false)
		{
			delete [] pData;
			return false;
		}
		
		// loop through the directories
		int nPos = 0;
		iso9660_dir* pcurfile;
		while ((int)(nPos + sizeof(iso9660_dir)) < nDirDataLen)
		{
			pcurfile = (iso9660_dir*)&pData[nPos];
			if (pcurfile->dr_len[0] == 0)
				break;
			
			int nLen = pcurfile->dr_len[0];
			if (nLen < 0)
				nLen = 255 + (0 - nLen);

			ASSERT(nLen > 0);

			if (bUnicode && pcurfile->dr_file_name_len[0] > 2 ||
				!bUnicode && pcurfile->dr_file_name_len[0] > 1)
			{
				CFileRecord* pSubItem = new CFileRecord(pTargetRecord);
				pTargetRecord->GetSubItems()->Add(pSubItem);
				
				if (bUnicode)
				{
					int nStringLen = pcurfile->dr_file_name_len[0]/2;
					ASSERT(nStringLen);

					WCHAR* pwstrName = new WCHAR[nStringLen + 1];
					memcpy(pwstrName, &pData[nPos + (sizeof(iso9660_dir) - 1)], pcurfile->dr_file_name_len[0]);
					pwstrName[nStringLen] = 0;

					// motorola bit order, so we flip all the bytes
					for (int i=0;i<nStringLen;i++)
					{
						char szVal[2] = {0};

						memcpy(szVal, &pwstrName[i], 2);
						memcpy(szVal, &szVal[1], 1);
						memcpy(&szVal[1], &pwstrName[i], 1);
						memcpy(&pwstrName[i], szVal, 2);
					}
					
					WCHAR* pstr = wcsrchr(pwstrName, ';');
					if (pstr) pstr[0] = 0;

					pSubItem->SetName(W2A(pwstrName));

					OutputDebugString("Read:");
					OutputDebugString(pSubItem->GetName());
					OutputDebugString("\n");

					delete [] pwstrName;
				}
				else
				{
					char* pstrName = new char[pcurfile->dr_file_name_len[0] + 1];
					memset(pstrName, 0, pcurfile->dr_file_name_len[0] + 1);
					memcpy(pstrName, &pData[nPos + (sizeof(iso9660_dir) - 1)], pcurfile->dr_file_name_len[0]);
					char* pstr = strrchr(pstrName, ';');
					if (pstr) pstr[0] = 0;

					pSubItem->SetName(pstrName);

					OutputDebugString("Read:");
					OutputDebugString(pstrName);
					OutputDebugString("\n");

					delete [] pstrName;
				}
				
				long nFileDataPos = BothEndianDWORDtoLong(pcurfile->dr_data_pos);
				long nFileDataLen = BothEndianDWORDtoLong(pcurfile->dr_data_len);

				pSubItem->SetSector(nFileDataPos);
				pSubItem->SetFileSize(nFileDataLen);
				pSubItem->SetFileRecordType(CFileRecord::FILE_RECORD);
				pSubItem->SetAlreadyOnCD(true);

				SYSTEMTIME systime;
				systime.wYear = pcurfile->dr_recording_time[0] + 1900;
				systime.wMonth = pcurfile->dr_recording_time[1];
				systime.wDay = pcurfile->dr_recording_time[2];
				systime.wHour = pcurfile->dr_recording_time[3];
				systime.wMinute = pcurfile->dr_recording_time[4];
				systime.wSecond = pcurfile->dr_recording_time[5];
				systime.wMilliseconds = 0;
				systime.wDayOfWeek = 0; // ignored in conversion

				FILETIME filetime;
				SystemTimeToFileTime(&systime, &filetime);

				pSubItem->SetTime(filetime);

				if (pcurfile->dr_file_flags[0] & 2)
				{
					pSubItem->SetFileRecordType(CFileRecord::DIRECTORY_RECORD);
					ReadDirectory(pcurfile, pSubItem, bUnicode);
				}
			}
			
			nPos += nLen;
		}
		
		delete [] pData;

		pTargetRecord->Sort();

		return true;
	}

	return false;
}

CFileRecord* CDiscParser::GetRoot()
{
	return &m_root;
}
