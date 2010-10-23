// DisCDiscISO9660.cpp: Implementierung der Klasse CDiscISO9660.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "ObjFull\DiscRecord.h"
#include "ObjFull\DiscRecordObj.h"
#include "disc.h"
#include "DiscISO9660.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <stdio.h>
#include "discparser.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CDiscISO9660::CDiscISO9660() : m_pRoot(NULL),
							   m_bFirstPass(false),
							   m_bAbort(false),
							   m_nWrittenSize(0),
							   m_nReadSoFar(0),
							   m_nCurSessionStart(0)
{
	memset(m_szLabel, 0, 50 * sizeof(char));
}

CDiscISO9660::~CDiscISO9660()
{
	Reset();
//	_ASSERT(m_pRoot->GetSubItems()->GetSize() == 0);
}

//DEL bool CDiscISO9660::AddDirectory(char* pstrLocalPath, char* pstrPathOnCD)
//DEL {
//DEL 	// Passes the directory on to the root item, where subdirs
//DEL 	// will be scanned and added to the structure.
//DEL 	// No writing occurs here.
//DEL 	// The pathoncd specified which subitem to add the item to
//DEL 	// It is in the form \hello\dir1
//DEL 
//DEL 	CFileRecord* pTargetRecord = m_pRoot->FindDirectory(pstrPathOnCD);
//DEL 	if (pTargetRecord)
//DEL 		return pTargetRecord->AddDirectoryItems(pstrLocalPath);
//DEL 
//DEL 	return false;
//DEL }

//DEL bool CDiscISO9660::AddFile(char* pstrLocalPath, char* pstrPathOnCD)
//DEL {
//DEL 	// see description above
//DEL 	CFileRecord* pTargetRecord = m_pRoot->FindDirectory(pstrPathOnCD);
//DEL 	_ASSERT(pTargetRecord); // should never assert
//DEL 	
//DEL 	if (pTargetRecord)
//DEL 		return pTargetRecord->AddFile(pstrPath);
//DEL 
//DEL 	return false;
//DEL }

bool CDiscISO9660::SetAndPrimeSession(int nSession, int nSessionStartLBA)
{
	// This function actually writes the image, and does not
	// return till the image is complete
	
	while (m_pathTable.GetSize())
	{
		m_pathTable.RemoveAt(0);
	}

	if (nSessionStartLBA > 0)
	{
		// then this is a multisession disc
		m_pDiscParser->ReadVolumeDescriptors(false);
		m_pDiscParser->LoadDirectoryStructure();
		m_pRoot->MergeItems(m_pDiscParser->GetRoot());
	}

	// construct path table
	if (!m_bAbort)
		m_pRoot->ConstructPathTable(m_pathTable);
	
	m_nCurSessionStart = nSessionStartLBA;
	m_nWrittenSize = 0;

	// first pass to get size info
	m_bFirstPass = true;
	if (!m_bAbort)
		WriteData();
	else
		return false;

	m_bFirstPass = false;
	
	m_nWrittenSize = 0;

	// open file. When it is open, the data is actually written
	if (m_stream.Open(NULL) == false)
		return false;	
	
	// We start a thread to feed us the data, and when the thread
	// has buffered our buffer size = 10mb, we return

	DWORD dwThreadID = 0;
	CreateThread(NULL,                  // Security attributes
                 (DWORD) 0,             // Initial stack size
                 WriteDataThread,     // Thread start address
                  (LPVOID) this,         // Thread parameter
                 (DWORD) 0,             // Creation flags
                 &dwThreadID);          // Thread identifier

	while (m_stream.IsBufferAtMax() == FALSE)
		Sleep(300);

//	m_stream.Close();

	m_bAbort = false;

	return true;
}

DWORD __stdcall CDiscISO9660::WriteDataThread(LPVOID lpvThreadParm)
{
	CDiscISO9660* pThis = (CDiscISO9660*)lpvThreadParm;

	// This is important to know, to understand how the buffering works:
	// When the session is primed, WriteData is called the first time,
	// and all the files are scanned and their sizes are recorded, gathering
	// the information we need to actually write stuff like total size to the iso
	// image. This function is called synchronously. After that, the real reading
	// of the file will start. So this thread is started, and the writedata
	// we start writing the data to the file. Now, the data is being added to the
	// circular buffer, and without the data being read after a while, the 
	// buffer is going to block, and wait for data to be read. We exploit this
	// and poll in the function that calls this thread, and wait for the buffer
	// to be filled up before we start burning.
	if (!pThis->m_bAbort)
		pThis->WriteData();

	CHelper::Trace("Write data thread exited\n");
	return 0;
}

void CDiscISO9660::Reset()
{
	// Destroy the directory structure

	m_pRoot->Destroy();
}

bool CDiscISO9660::WriteData()
{
	
	WritePrimaryVolumeDescriptor();

	// Don't forget to write .. and . !!!!

	// To write the path table for multisession files, we have
	// got to include the path table of the previous session. We
	// can assume that the previous session performed the same link
	// to its previous session, so if we simply copy the entire path table
	// pf the previous session, we should have links to all the available
	// files on the cd. If the previous session only contains one type of
	// path table, for example, big endian or little endian, we will copy
	// the available path table, and simply not write the other path table, so
	// we don't have to actually parse the contents. The pvd contains the length
	// an position of both path tables, so we simply need to read at those offset
	// and not actually parse.

	////////////////////////////////////////////////////
	/////// Little Endian Path Table follows. See ecma 119 or 130 s9.4


	// Where is root directory? You have to wrote that.
	// Update: darn, this is confusing shit. Does the root
	// have to be written or not?

	// MULTISESSION NOTE
	m_nLittleEndianPathTableSector = m_stream.GetCurSector();
	
	m_stream.WriteByte(1);
	m_stream.WriteByte(0);  // number of sectors in extended attribute record

	// MULTISESSION NOTE
	m_stream.WriteLittleEndian((DWORD)(m_pRoot->GetSector() + m_nCurSessionStart));
	m_stream.WriteLittleEndian((WORD) 1);
	m_stream.WriteByte(0);
	m_stream.WriteByte(0);
	
	for (int i=1;i<m_pathTable.GetSize();i++)
	{
		CFileRecord* recDir = m_pathTable.GetAt(i);
		if (i == 0)
			m_stream.WriteByte(1);
		else
			m_stream.WriteByte((BYTE)recDir->GetNameLength());

		m_stream.WriteByte(0);

		// MULTISESSION NOTE
		m_stream.WriteLittleEndian((DWORD)(recDir->GetSector() + m_nCurSessionStart));
		m_stream.WriteLittleEndian((WORD) (i == 0 ? 1 : recDir->GetParentIndex()));

		if (i == 0)
			m_stream.WriteByte(0);
		else
			m_stream.WriteString(recDir->GetName());
		
		// Padding byte, if length is odd number
		if (recDir->GetNameLength() & 1) // if odd
			m_stream.WriteByte(0);

		if (m_bAbort)
			return false;
	}
	
	// MULTISESSION NOTE (m_nLittleEndianPathTableSector). This don't
	// affect multisession, because we do not incremenent m_nLittleEndianPathTableSector
	m_nPathTableSize = (m_stream.GetCurSector() - m_nLittleEndianPathTableSector) * SECTOR_SIZE + m_stream.GetCurSectorPos();

	m_stream.FillSector();

	//////////////////////////////////////
	//////// Big endian path table follows

	// MULTISESSION NOTE
	m_nBigEndianPathTableSector = m_stream.GetCurSector();
	
	m_stream.WriteByte(1);
	m_stream.WriteByte(0);  // number of sectors in extended attribute record

	// MULTISESSION NOTE
	m_stream.WriteBigEndian((DWORD)(m_pRoot->GetSector() + m_nCurSessionStart));
	m_stream.WriteBigEndian((WORD) 1);
	m_stream.WriteByte(0);
	m_stream.WriteByte(0);
	
	for (i=1;i<m_pathTable.GetSize();i++)
	{
		CFileRecord* recDir = m_pathTable.GetAt(i);
		
		if (i == 0)
			m_stream.WriteByte(1);
		else
			m_stream.WriteByte((BYTE)recDir->GetNameLength());

		m_stream.WriteByte(0);

		// MULTISESSION NOTE
		m_stream.WriteBigEndian((DWORD)(recDir->GetSector() + m_nCurSessionStart));
		m_stream.WriteBigEndian((WORD) (i == 0 ? 1 : recDir->GetParentIndex()));
		
		if (i == 0)
			m_stream.WriteByte(0);
		else
			m_stream.WriteString(recDir->GetName());
		
		// See description above
		if (recDir->GetNameLength() & 1)
			m_stream.WriteByte(0);

		if (m_bAbort)
			return false;
	}

	m_stream.FillSector();

	///////////////////////////////////////
	// Write directories and files
	
	// We are looping through our constructued path table,
	// so ALL directories are listed there.
	
	int nTableSize = m_pathTable.GetSize();
	for (int k=0; k < nTableSize; k++)
	{
		// From pje: A directory consists of a series of directory records in 
		// one or more consecutive sectors. However, unlike path 
		// records, directory records may not straddle sector boundaries.
		// There may be unused space at the end of each sector, which 
		// is filled with zeros. 
		
		CFileRecord* pDir = m_pathTable.GetAt(k);
		CFileRecord* pParent = k == 0 ? pDir : m_pathTable.GetAt(pDir->GetParentIndex() - 1);
		
		//CHelper::Trace("Looping through path table for write. Current Name=%s", pDir->GetName());
		
		// The sector of a directory points to the location where the data
		// of the directory starts. The data of a directory is simply the
		// 1. The directory record of the directory itself.
		// 2. The directory record of the parent directory
		// 3. The directory records of all subdirectories and file
		
		// MULTISESSION NOTE. We do not add m_nCurSessionStart, because this is just the 0
		// relative value set on the object. When we write the value to
		// the stream, we offset by m_nCurSessionStart
		
		// On an iso9660 level, we are sure that this is a directory, and not
		// a file, because only directories are allowed in the path table. Since
		// we are copying all the directory structures inot the new path table, it
		// is alright that this points to a lcoation in the current sector instead
		// of pointing at an older sessions directory.

		pDir->SetSector(m_stream.GetCurSector());
		
		// Here, we write the current directory, and then it's parent
		// if the directory is the root directory, the parent dir is
		// the same as the root dir itself

		WriteDirectoryRecord(pDir, CFileRecord::DOT_RECORD);
		WriteDirectoryRecord(pParent, CFileRecord::DOT_DOT_RECORD);
		
		// We write all the directory records of the subitems,
		// bot files and directories. When a directory or file is
		// written, the sector is already known, since it was worked
		// out in the first pass.

		for (int j=0;j<pDir->GetSubItems()->GetSize();j++)
		{
			WriteDirectoryRecord(pDir->GetSubItems()->GetAt(j), pDir->GetSubItems()->GetAt(j)->GetFileRecordType());
			
			if (m_bAbort)
				return false;
		}
		
		// At this postion, if this is the first loop,
		// we can copy all the directory records from the
		// root directory of the previous session, and write them here. They
		// are all subitems of the root directory of this session, so if we write
		// them immediately after writing the root items, we should have access
		// to those files and directories. To get to the root item data, we jump
		// to the position in the root directory start


		// fill the sector with 0s
		m_stream.FillSector();
		
		// We set the size of the directory. This is a combination of all the
		// record data in the sector.
		pDir->SetFileSize((m_stream.GetCurSector() - pDir->GetSector()) * SECTOR_SIZE);
			
		// We write the file data
		for (int h=0;h<pDir->GetSubItems()->GetSize();h++)
		{
			CFileRecord* pFile = pDir->GetSubItems()->GetAt(h);
			
			if (m_bAbort)
				return false;

			if (pFile->GetFileRecordType() == CFileRecord::FILE_RECORD) // watch out!! Look at original
			{
				// MULTISESSION NOTE. see comments on pDir above
				
				// on an iso9600 level, this value points at the actual data
				// of the file which might be in a previous session

				if (pFile->GetAlreadyOnCD() == false)
					pFile->SetSector(m_stream.GetCurSector());


				// there is a bug here. In the first pass, the file size can
				// always be retrieved. In the second pass however, the file
				// may not actually be able to be opened, and so the file will
				// not be written. This will shift a lot of data by that amount
				// of bytes, and all following files and directories will not
				// be visible. I have no idea how iso buster reads and finds em
				// it was one clever dude who programmed iso buster. Or maybe just 
				// a lucky guy. Did he actually anticipate this problem? I wouldn't
				// have.

				DWORD dwSize = pFile->GetFileSize();
				if (m_stream.IsOpen() == false)
				{
					// this is first pass.
					// The following code increments the sector value by the ammount that
					// actually writing the file would increment it by. Hence, if the file
					// is from a previous session, it does not incremement it by anything
					
					if (pFile->GetAlreadyOnCD() == false)
					{
						// check that file can be opened
						int h = _open(pFile->GetFullpath(), _O_RDONLY|_O_BINARY);
						if (h >= 0)
						{
							DWORD nNoSectors = (dwSize + SECTOR_SIZE - 1) / SECTOR_SIZE;
							m_stream.SetCurSector(m_stream.GetCurSector() + nNoSectors);
							m_nWrittenSize += dwSize; // cosmetic. for progress bar
							close(h);
						}
					}
					
				}
				else if (pFile->GetAlreadyOnCD() == false)
				{
					// this is write pass
					int h = _open(pFile->GetFullpath(), _O_RDONLY|_O_BINARY);
					if (h < 0)
					{
						CHelper::Trace("Can't open %s\n", pFile->GetFullpath());
						continue;
					}

					while (dwSize > 0)
					{
						int n = BUFFER_SIZE - m_stream.GetBufferPos();
						if ((DWORD) n > dwSize)
							n = dwSize;
						
						if (_read(h, m_stream.GetBuffer() + m_stream.GetBufferPos(), n) < n)
						{
							CHelper::Trace("Read error in file %s\n", pFile->GetFullpath());
							_ASSERT(FALSE);
							close(h);
							continue;
						}
						
						if (m_bAbort == true)
						{
							close(h);
							return false;
						}

						m_nWrittenSize += n;

						m_stream.SetBufferPos(m_stream.GetBufferPos() + n);
						if (m_stream.GetBufferPos() == BUFFER_SIZE)
							m_stream.FlushBuffer();
						
						m_stream.SetCurSector(m_stream.GetCurSector() + (n / SECTOR_SIZE));
						m_stream.SetCurSectorPos(m_stream.GetCurSectorPos() + (n % SECTOR_SIZE));

						dwSize -= n;

						CHelper::Trace("Writing data >>>Sector:%lu\n", m_stream.GetCurSector());
					}

					close(h);
		
					m_stream.FillSector();

				} //else
			} //if is file
		} // for
	}
	
	m_stream.FillSector();
	
	if (!m_bAbort)
		m_stream.WriteBlock(0, SESSION_END_ZEROS);

	m_stream.FlushBuffer();
	
	m_nTotalSectors = m_stream.GetCurSector();
	
	if (m_stream.IsOpen())
		m_stream.GetFileBuffer()->IndicateNoMoreInput();

	return true;
}

void CDiscISO9660::WriteDirectoryRecord(CFileRecord* dir, int nType, bool bFinal)
{
	// ISO 9660 : 99, Table 8 - Format of a Directory Record 
	// 6.8.1 Directory 
	
	// ISO: A directory shall be recorded as a file containing a set of records
	// each of which identifies a File Section or another directory. 
	// A directory shall not be recorded as an Associated File, shall not 
	// be recorded in interleaved mode and shall consist of only one File 
	// Section. 
	
	// ISO: The first or only Directory Record recorded in a Logical Sector
	// shall begin at the first byte of the first Data Field of that 
	// Logical Sector. Each subsequent Directory Record recorded in that 
	// Logical Sector shall begin at the byte immediately following the 
	// last byte of the preceding Directory Record in that Logical Sector. 
	// Each Directory Record shall end in the Logical Sector in which it 
	// begins. Unused positions after the last Directory Record in a 
	// Logical Sector shall be set to (OO). 

	CHelper::Trace("WriteDirectoryRecord::name=%s, parent=%lu, sector=%lu\n", dir->GetName() ? dir->GetName() : "noname", dir->GetParentIndex(), dir->GetSector());

	unsigned identifier_size = 0;
	switch (nType)
	{
	case CFileRecord::DOT_RECORD:
	case CFileRecord::DOT_DOT_RECORD:
		identifier_size = 1;
		break;
	case CFileRecord::DIRECTORY_RECORD:
		identifier_size = dir->GetNameLength();
		break;
	case CFileRecord::FILE_RECORD:
		identifier_size = dir->GetNameLength() + 2;
		break;
	}

	unsigned record_size = 33 + identifier_size; // is 32 in apple sample, and 33 in ederlsky
	
	if ((identifier_size & 1) == 0)
		record_size++;

	if (m_stream.GetCurSectorPos() + record_size > SECTOR_SIZE)
		m_stream.FillSector();

	m_stream.WriteByte(record_size);
	m_stream.WriteByte(0); // number of sectors in extended attribute record

	// MULTISESSION NOTE
	if (dir->GetAlreadyOnCD() == false)
		m_stream.WriteBothEndian((DWORD)(dir->GetSector() + this->m_nCurSessionStart));
	else
		m_stream.WriteBothEndian((DWORD)dir->GetSector());

	m_stream.WriteBothEndian((DWORD)dir->GetFileSize());
	
	// file time & date. See ecma119, 9.1.5
	// It is differet from the volume date.../time

	
	m_stream.WriteByte((BYTE)(dir->GetTimeAsSystemTime().wYear - 1900)); // years since 1900
	m_stream.WriteByte((BYTE)dir->GetTimeAsSystemTime().wMonth);  //month
	m_stream.WriteByte((BYTE)dir->GetTimeAsSystemTime().wDay);  // day
	m_stream.WriteByte((BYTE)dir->GetTimeAsSystemTime().wHour); //hour
	m_stream.WriteByte((BYTE)dir->GetTimeAsSystemTime().wMinute); //minute
	m_stream.WriteByte((BYTE)dir->GetTimeAsSystemTime().wSecond); //second
	m_stream.WriteByte(0);  // GMT offset

	if (nType == CFileRecord::FILE_RECORD)
	{
		BYTE Flags = 0;

		m_stream.WriteByte(Flags);
	}
	else
	{
		// Either directory, or dot-dot
		BYTE Flags = 2; // Binary 

		m_stream.WriteByte(Flags);
	}

	m_stream.WriteByte(0);  // file unit size for an interleaved file
	m_stream.WriteByte(0);  // interleave gap size for an interleaved file
	m_stream.WriteBothEndian((WORD) 1); // volume sequence number
	m_stream.WriteByte(identifier_size);

	switch (nType)
	{
    case CFileRecord::DOT_RECORD:
		m_stream.WriteByte(0);
		break;
    case CFileRecord::DOT_DOT_RECORD:
		m_stream.WriteByte(1);
		break;
    case CFileRecord::DIRECTORY_RECORD:
		m_stream.WriteString(dir->GetName());
		break;
    case CFileRecord::FILE_RECORD:
		m_stream.WriteString(dir->GetName());
		m_stream.WriteString(";1");
		break;
	}

	// If identifier_size is even, then a padding byte
	if ((identifier_size & 1) == 0)
		m_stream.WriteByte(0);
}

void CDiscISO9660::SetLabel(char* pstrLabel)
{
	strcpy(m_szLabel, pstrLabel);
}

char* CDiscISO9660::GetLabel()
{
	return m_szLabel;
}

void CDiscISO9660::WritePrimaryVolumeDescriptor()
{
	// ISO 9660: 98, 8.4 Primary Volume Descriptor 

	// The first 16 sectors are zeros in the ISO standard
	m_stream.WriteBlock(0, 16 * SECTOR_SIZE);

	// Primary Volume Descriptor. Label.
	m_stream.WriteByte(0x01); // Volume Descriptor Type
	m_stream.WriteString("CD001"); // Standard Identifier
	m_stream.WriteByte(0x01); // Volume Descriptor Version
	m_stream.WriteByte(0); // Unused Field

	m_stream.WriteBlock(' ', 32);  // system identifier

    const char* t = m_szLabel;
    for (int i = 0; i < 32; i++)
		m_stream.WriteByte(*t != 0 ? toupper(*t++) : ' '); // Volume Identifier
  
	m_stream.WriteBlock(0, 8); // Unused Field

	// what is written here with multi-session? Is it the total sectors including
	// file data in the previous session, or just this session? Dunno yet
	m_stream.WriteBothEndian(m_nTotalSectors); // total sectors is the number of sectors in the image file (Volume space size)
	m_stream.WriteBlock(0, 32);
	m_stream.WriteBothEndian((WORD) 1); // volume set size
	m_stream.WriteBothEndian((WORD) 1); // volume sequence number
	m_stream.WriteBothEndian((WORD) 2048); // sector size (Logical Block Size)
	m_stream.WriteBothEndian((DWORD)m_nPathTableSize); // path table size (8)

	// MULTISESSION NOTE
	m_stream.WriteLittleEndian((DWORD)(m_nLittleEndianPathTableSector + m_nCurSessionStart));
	m_stream.WriteLittleEndian((DWORD) 0);  // second little endian path table

	// MULTISESSION NOTE
	m_stream.WriteBigEndian((DWORD)(m_nBigEndianPathTableSector + m_nCurSessionStart));
	m_stream.WriteBigEndian((DWORD) 0);  // second big endian path table
	
	WriteDirectoryRecord(&(*m_pRoot), CFileRecord::DOT_RECORD);

	m_stream.WriteBlock(' ', 128);      // volume set identifier
	m_stream.WriteString("ERD");
	m_stream.WriteBlock(' ', 125);      // publisher identifier
	m_stream.WriteString("ERD");
	m_stream.WriteBlock(' ', 125);      // data preparer identifier
	m_stream.WriteString("ERD");
	m_stream.WriteBlock(' ', 125);      // application identifier
	m_stream.WriteBlock(' ', 37);       // copyright file identifier
	m_stream.WriteBlock(' ', 37);       // abstract file identifier
	m_stream.WriteBlock(' ', 37);       // bibliographic file identifier
	m_stream.WriteString("0000000000000000");  // volume creation
	m_stream.WriteByte(0);
	m_stream.WriteString("0000000000000000");  // most recent modification
	m_stream.WriteByte(0);
	m_stream.WriteString("0000000000000000");  // volume expires
	m_stream.WriteByte(0);
	m_stream.WriteString("0000000000000000");  // volume is effective
	m_stream.WriteByte(0);
	m_stream.WriteByte(1);
	m_stream.WriteByte(0);
	m_stream.FillSector();

	// Volume Descriptor Set Terminator

	m_stream.WriteString("\377CD001\1");
	m_stream.FillSector();

}

long CDiscISO9660::GetWrittenSize()
{
	return m_nWrittenSize;
}

void CDiscISO9660::Finished()
{
	m_stream.Close();
}

CFileRecord* CDiscISO9660::GetFileSystem()
{
	return m_pRoot;
}

bool CDiscISO9660::Read(BYTE* pBuffer, long & nLen)
{
	m_nReadSoFar += nLen;
	return m_stream.GetFileBuffer()->ReadData(pBuffer, nLen);
}

void CDiscISO9660::SetFileRecord(CFileRecord *pRoot)
{
	m_pRoot = pRoot;
}

void CDiscISO9660::SetDiscParser(CDiscParser* pDiscParser)
{
	m_pDiscParser = pDiscParser;
}