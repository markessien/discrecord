// FileRecord.cpp: Implementierung der Klasse CFileRecord.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ObjFull\DiscRecord.h"
#include "ObjFull\DiscRecordObj.h"
#include "FileRecord.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CFileRecord::CFileRecord(CFileRecord* pParent) :
						 m_iParentIndex(0),
						 m_eType(DIRECTORY_RECORD),
						 m_nSector(0),
						 m_nFileSize(0),
						 m_pstrName(0),
						 m_pstrFullpath(0),
						 m_pstrPathOnCD(0),
						 m_nTotalSize(0),
						 m_pParent(pParent),
						 m_bAlreadyOnCD(false)
{
	GetSystemTimeAsFileTime(&m_creationTime);
	GetTimeAsSystemTime();
	
	m_pstrPathOnCD = new char[10];
	strcpy(m_pstrPathOnCD, "\\");
}

CFileRecord::~CFileRecord()
{
	if (m_pstrFullpath)
	{
		delete [] m_pstrFullpath;
		m_pstrFullpath = NULL;
	}

	if (m_pstrName)
	{
		delete [] m_pstrName;
		m_pstrName = NULL;
	}
	
	if (m_pstrPathOnCD)
	{
		delete []m_pstrPathOnCD;
		m_pstrPathOnCD= NULL;
	}

//	Destroy();
}

void CFileRecord::SetName(LPCTSTR pstrName)
{
	_ASSERT(pstrName);
	int nLen = strlen(pstrName);
	
	if (nLen > MAX_PATH)
		nLen = MAX_PATH;

	if (m_pstrName)
	{
		delete [] m_pstrName;
		m_pstrName = NULL;
	}

	m_pstrName = new char[nLen+2];
	memset(m_pstrName, 0, nLen +2);

	strcpy(m_pstrName, pstrName);
	
	ASSERT(m_pstrPathOnCD);
	delete [] m_pstrPathOnCD;
	m_pstrPathOnCD = new char[strlen(m_pParent->GetPathOnCD()) + nLen + 4];
	
	strcpy(m_pstrPathOnCD, m_pParent->GetPathOnCD());

	AddSlash(m_pstrPathOnCD);
	strcat(m_pstrPathOnCD, pstrName);
}

void CFileRecord::SetFullpath(LPCTSTR pstrFullpath)
{
	_ASSERT(pstrFullpath);
	int nLen = strlen(pstrFullpath);
	
	if (nLen > MAX_PATH)
		nLen = MAX_PATH;

	if (m_pstrFullpath)
	{
		delete [] m_pstrFullpath;
		m_pstrFullpath = NULL;
	}

	m_pstrFullpath = new char[nLen+2];
	memset(m_pstrFullpath, 0, nLen +2);

	strcpy(m_pstrFullpath, pstrFullpath);
}

LPCTSTR CFileRecord::GetName()
{
	return m_pstrName;
}

LPCTSTR CFileRecord::GetFullpath()
{
	return m_pstrFullpath;
}

void CFileRecord::SetParentIndex(int iNewParentIndex)
{
	m_iParentIndex = iNewParentIndex;
}

int CFileRecord::GetParentIndex()
{
	return m_iParentIndex;
}

void CFileRecord::SetFileSize(long nNewSize)
{
	if (m_nFileSize)
		m_nTotalSize -= m_nFileSize;

	m_nFileSize = nNewSize;
	m_nTotalSize += nNewSize;
}

long CFileRecord::GetFileSize()
{
	return m_nFileSize;
}

void CFileRecord::SetSector(long nNewSector)
{
	m_nSector = nNewSector;
}

long CFileRecord::GetSector()
{
	return m_nSector;
}

CFileRecord::EnumRecordType CFileRecord::GetFileRecordType()
{
	return m_eType;
}

void CFileRecord::SetFileRecordType(CFileRecord::EnumRecordType eNewType)
{
	m_eType = eNewType;
}

void CFileRecord::AddSlash(char* pstr)
{
	if (pstr[strlen(pstr) - 1] != '\\')
		strcat(pstr, "\\");
}

bool CFileRecord::AddDirectoryItems(LPCTSTR pstrPath, CFileRecord* pDirectoryRecord)
{
	CHelper::Trace("CFileRecord::AddDirectory=%s.\n", pstrPath);
	
	// If we don't have a subdirectory to add it to, we point at our current
	// class. Allows us to use recursion.
	if (pDirectoryRecord == NULL)
		pDirectoryRecord = this;
	
	// Make a copy which we can modify later. The passed string is const.
	// We make sure there is a backslash, and add the *.* we need to search
	// the contents of the directory in their entirity
	
	char szBaseDir[MAX_PATH];
	strcpy(szBaseDir, pstrPath);
	AddSlash(szBaseDir);

	char szSearch[MAX_PATH];
	strcpy(szSearch, szBaseDir);
	strcat(szSearch, "*.*");
	
	// We list all the items in the directory

	WIN32_FIND_DATA f;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	
	if ((hFind = FindFirstFile(szSearch, &f)) != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (f.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)	
			{
				// We have a directory. We don't add the dot dirs

				if (strcmp(f.cFileName, ".") != 0 &&
					strcmp(f.cFileName, "..") != 0)
				{
					CFileRecord* pRecord = new CFileRecord(pDirectoryRecord);
					SetRecordProperties(pRecord, f, szBaseDir);
					pDirectoryRecord->m_arrFiles.Add(pRecord);
					pDirectoryRecord->m_nTotalSize += f.nFileSizeLow;

					m_nTotalSize += f.nFileSizeLow;

					AddDirectoryItems(pRecord->GetFullpath(), pRecord);
				}
			}
			else if (f.dwFileAttributes & FILE_ATTRIBUTE_NORMAL   ||
					 f.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE  ||
					 f.dwFileAttributes & FILE_ATTRIBUTE_READONLY )
			{
				CFileRecord* pRecord = new CFileRecord(pDirectoryRecord);
				SetRecordProperties(pRecord, f, szBaseDir);
				pDirectoryRecord->m_arrFiles.Add(pRecord);
				pDirectoryRecord->m_nTotalSize += f.nFileSizeLow;

				m_nTotalSize += f.nFileSizeLow;
			}
		} 
		while (FindNextFile(hFind, &f) != 0);

		FindClose(hFind);
	} // if
	
	/*
	qsort(pDirectoryRecord->m_arrFiles.GetData(), 
		  pDirectoryRecord->m_arrFiles.GetSize(), 
		  sizeof(CFileRecord*), CFileRecord::SortProc);
*/
	return true;
}

int CFileRecord::SortProc(const void *arg1,  const void *arg2)
{
	CFileRecord* pRec1 = (CFileRecord*)*(long*)arg1;
	CFileRecord* pRec2 = (CFileRecord*)*(long*)arg2;
	
	if (pRec1->GetFileRecordType() == CFileRecord::DIRECTORY_RECORD &&
		pRec2->GetFileRecordType() == CFileRecord::FILE_RECORD)
	{
		return -1;
	}
	
	if (pRec2->GetFileRecordType() == CFileRecord::DIRECTORY_RECORD &&
		pRec1->GetFileRecordType() == CFileRecord::FILE_RECORD)
	{
		return 1;
	}


	int iResult = _stricmp(pRec1->GetName(), pRec2->GetName());
	return iResult;
}

void CFileRecord::SetRecordProperties(CFileRecord *pRecord, WIN32_FIND_DATA &wfind, char* pstrDir)
{
	pRecord->SetName(wfind.cFileName);
	pRecord->SetFileSize(wfind.nFileSizeLow);

	char szFullpath[MAX_PATH];
	_ASSERT(strlen(pstrDir) < MAX_PATH);

	strcpy(szFullpath, pstrDir);
	AddSlash(szFullpath);
	strcat(szFullpath, pRecord->GetName());

	pRecord->SetFullpath(szFullpath);
	pRecord->SetTime(wfind.ftCreationTime);

	if (wfind.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		pRecord->SetFileRecordType(DIRECTORY_RECORD);
	else
		pRecord->SetFileRecordType(FILE_RECORD);

}

void CFileRecord::SetTime(FILETIME creationTime)
{
	m_creationTime = creationTime;
}

FILETIME CFileRecord::GetTime()
{
	return m_creationTime;
}

void CFileRecord::Destroy()
{
	// destroyed by FileItem class
//	DestroySubItems(this);
}

void CFileRecord::DestroySubItems(CFileRecord* pRecord)
{
	while (pRecord->m_arrFiles.GetSize())
	{
		CFileRecord* pRecSub = pRecord->m_arrFiles.GetAt(0);

		DestroySubItems(pRecSub);

		pRecord->m_arrFiles.RemoveAt(0);

		delete pRecSub;
		pRecSub = NULL;
	}
}

void CFileRecord::AddRecordChildrenToArray(CFileRecord* pRecord, CRecordArray& arrChildren, int iParentIndex, bool bAddDirsOnly)
{
	// recursive function that goes through the subfiles, and adds
	// them to the passed in array. If bDirsOnly is true, only add
	// the directories.

	for (int i = 0;i<pRecord->m_arrFiles.GetSize();i++)
	{
		CFileRecord* pChild = pRecord->m_arrFiles.GetAt(i);
		// Remember, the parent index is determined by the position of
		// the parent in the path table. As such, it is only relevant
		// for the path table, and is set when the path table is 
		// constructed.
		pChild->SetParentIndex(iParentIndex);
		
		if (bAddDirsOnly && pChild->m_eType == DIRECTORY_RECORD)
		{
			arrChildren.Add(pChild);
		}
		else if (bAddDirsOnly == false)
		{
			arrChildren.Add(pChild);
		}
	}
}

bool CFileRecord::ConstructPathTable(CRecordArray &arrPathTable)
{
	// This function naviagates the subdiretories, and places
	// them in the supplied array in the order required by a 
	// path table. This function would usually be called on the
	// root item, as it doesn't make sense on any other item.
	
	// ISO 9660:99 - 6.9 Path Table (The first record in the Path Table shall identify 
	// the Root Directory and its location.)
	arrPathTable.Add((CFileRecord*)this);
	
	// the path table should be sorted here.

	int i = 0;
	while (i<arrPathTable.GetSize())
	{
		// Add all subitems of this item to the function. Index of dir
		// is the index in the path table. Thus, i+1 is used as the index
		// We pass a ptr to arrPathTable, and it will be filled with the subdir
		// from m_arrfiles. The true parameter indicates that it is just the dirs
		// that should be added
		AddRecordChildrenToArray(arrPathTable.GetAt(i), arrPathTable, i+1, true);
		++i;
	}
	
#ifdef _DEBUG
	CHelper::Trace("Dumping path table -->>>>\n");

	for (i=0;i<arrPathTable.GetSize();i++)
	{
		CHelper::Trace("Name=%s, File=%s, ParentIndex=%lu\n", 
			  arrPathTable.GetAt(i)->GetName(), 
			  arrPathTable.GetAt(i)->GetFullpath(), 
			  arrPathTable.GetAt(i)->GetParentIndex());
	}
#endif
	
	return true;
}

long CFileRecord::GetNameLength()
{
	if (m_pstrName)
		return strlen(m_pstrName);
	
	return 0;
}

CRecordArray* CFileRecord::GetSubItems()
{
	return &(m_arrFiles);
}

CFileRecord* CFileRecord::FindDirectory(LPCTSTR pstrPath, bool bCreate)
{
	// This function runs down all subitems, looking for
	// the specified directory. It isn't really a 'find',
	// since you have to specify the full path of the 
	// directory you want. For example, \ gives you the root.
	// if you call \ on an item that is not the root item,
	// you get that very item. The path you pass in is always
	// relative to the current node.
	// if you are in the root, and you pass \hello\, it scans
	// the children for an item called hello. If you call \hello\world
	// it look for hello, then searches hello for an item called world.

	// this function is useful when you want to insert something into
	// a child folder, or you want to modify a file.
	
	CFileRecord* pResult = this;
	
	if (strcmp(pstrPath, "\\") == 0 ||
		strcmp(pstrPath, "") == 0)
	{
		pResult = this; // if \ then this is the result
		return pResult;
	}

	// We copy a copy we can modify
	char szPath[MAX_PATH];
	strcpy(szPath, pstrPath);

	char* pch = NULL;
	pch = strtok (szPath, "\\");
	while (pch != NULL)
	{
		//each pch will point at a piece of the path
		bool bFound = false;
		for (int i=0;i<pResult->m_arrFiles.GetSize();i++)
		{
			if (strcmp(pResult->m_arrFiles.GetAt(i)->GetName(), pch) == 0)
			{
				pResult = pResult->m_arrFiles.GetAt(i);
				bFound = true;
				break;
			}
		}
		
		if (bFound == false && bCreate)
			AddEmptyDirectory(pch);

		pch = strtok (NULL, "\\");
	}

	return pResult;
}

CFileRecord* CFileRecord::AddFile(LPCTSTR pstrPath)
{
	char szBaseDir[MAX_PATH];
	strcpy(szBaseDir, pstrPath);
	
	// remove filename
	char* pstr = strrchr(szBaseDir, '\\');
	if (pstr) pstr[1] = 0;

	WIN32_FIND_DATA f;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	
	CFileRecord* pRecord = NULL;
	if ((hFind = FindFirstFile(pstrPath, &f)) != INVALID_HANDLE_VALUE)
	{
		pRecord = new CFileRecord(this);
		SetRecordProperties(pRecord, f, szBaseDir);

		m_nTotalSize += f.nFileSizeLow;

		m_arrFiles.Add(pRecord);
	
		if (m_pParent)
			m_pParent->SubFileAdded(f.nFileSizeLow);
	}
	else
		return NULL;
	
	return pRecord;
}

long CFileRecord::GetTotalSize()
{
	return m_nTotalSize;
}

LPCTSTR CFileRecord::GetPathOnCD()
{
	return m_pstrPathOnCD;
}

CFileRecord* CFileRecord::GetParent()
{
	return m_pParent;
}

void CFileRecord::RemoveSubItem(CFileRecord *pRecord, bool bDelete)
{
	for (int i=0;i<m_arrFiles.GetSize();i++)
	{
		if (m_arrFiles.GetAt(i) == pRecord)
		{
			RemoveSubItem(i, bDelete);
			return;
		}
	}
}

CFileRecord* CFileRecord::AddEmptyDirectory(char *pstrName)
{
	char szPath[MAX_PATH];
	strcpy(szPath, "\\");
	strcat(szPath, pstrName);

	CFileRecord* pRecord = new CFileRecord(this);
	pRecord->SetName(pstrName);
	pRecord->SetFileRecordType(DIRECTORY_RECORD);

	m_arrFiles.Add(pRecord);

	return pRecord;
}

SYSTEMTIME CFileRecord::GetTimeAsSystemTime()
{
	SYSTEMTIME st;
	FileTimeToSystemTime(&m_creationTime, &st);
	return st;
}

CFileRecord* CFileRecord::CreateAndReturnPath(char *pstrPathOnCD)
{
	CFileRecord* pRecord = FindDirectory(pstrPathOnCD);

	if (pRecord)
		return pRecord;

	CFileRecord* pResult = NULL;

	char szPath[MAX_PATH];
	strcpy(szPath, pstrPathOnCD);

	char* pch = NULL;
	pch = strtok (szPath, "\\");
	while (pch != NULL)
	{		
		for (int i=0;i<pResult->m_arrFiles.GetSize();i++)
		{
			if (strcmp(pResult->m_arrFiles.GetAt(i)->GetName(), pch) == 0)
			{
				pResult = pResult->m_arrFiles.GetAt(i);
				break;
			}
		}

		pch = strtok (NULL, "\\");
	}
	
	// pResult can never be NULL.

	return pResult;
}

bool CFileRecord::AddDirectory(LPCTSTR pstrLocalPath)
{
	char szBaseDir[MAX_PATH];
	strcpy(szBaseDir, pstrLocalPath);
	AddSlash(szBaseDir);

	char szDirName[MAX_PATH] = {0};
	if (szBaseDir[strlen(szBaseDir) - 2] == ':')
	{
		strcpy(szDirName, ""); // root dir
	}
	else
	{
		szBaseDir[strlen(szBaseDir) - 1] = 0; // remove ending slash
		char* pstr = strrchr(szBaseDir, '\\'); // find slash
		if (pstr)
			strcpy(szDirName, pstr + 1);

		CFileRecord* pRecord = AddEmptyDirectory(szDirName);
		return pRecord->AddDirectoryItems(pstrLocalPath);
	}
	
	return AddDirectoryItems(pstrLocalPath, NULL);
}

void CFileRecord::RemoveSubItem(int Index, bool bDelete)
{
	CFileRecord* pRecord = m_arrFiles.GetAt(Index);
	m_nTotalSize -= pRecord->GetTotalSize();

	if (m_pParent)
		m_pParent->SubFileAdded(-pRecord->GetTotalSize());

	m_arrFiles.RemoveAt(Index);
	if (bDelete)
		delete pRecord;
}

void CFileRecord::Sort()
{
	qsort(m_arrFiles.GetData(), m_arrFiles.GetSize(), 
		  sizeof(CFileRecord*), CFileRecord::SortProc);
}

void CFileRecord::SubFileAdded(long nSize)
{
	m_nTotalSize += nSize;

	if (m_pParent)
		m_pParent->SubFileAdded(nSize);
}

bool CFileRecord::AddSubItem(CFileRecord *pItem)
{
	// this adds an item to the children array
	// if an existing item with that name is there
	// it is replaced. Call sort afterwards

	m_arrFiles.Add(pItem);

	return true;
}

bool CFileRecord::MergeItems(CFileRecord *pItem)
{
	// this takes a file item, and merges the contents
	// with this one. You can delete the item afterwards

	for (int i=0; i<pItem->GetSubItems()->GetSize();i++)
	{
		AddSubItem(pItem->GetSubItems()->GetAt(i));
	}

	Sort();

	return true;
}

bool CFileRecord::GetAlreadyOnCD()
{
	return m_bAlreadyOnCD;
}

void CFileRecord::SetAlreadyOnCD(bool bValue)
{
	m_bAlreadyOnCD = bValue;
}
