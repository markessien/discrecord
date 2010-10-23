// FileRecord.h: Schnittstelle für die Klasse CFileRecord.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILERECORD_H__C1C5A797_8640_4522_8F61_A977C7E2AEF1__INCLUDED_)
#define AFX_FILERECORD_H__C1C5A797_8640_4522_8F61_A977C7E2AEF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define CRecordArray CArray<CFileRecord*, CFileRecord*>

class CFileRecord  
{
public:	
	void SetAlreadyOnCD(bool bValue);
	bool GetAlreadyOnCD();
	bool MergeItems(CFileRecord* pItem);
	bool AddSubItem(CFileRecord* pItem);
	void SubFileAdded(long nSize);
	void Sort();
	void RemoveSubItem(int Index, bool bDelete);
	bool AddDirectory(LPCTSTR pstrLocalPath);
	CFileRecord* CreateAndReturnPath(char* pstrPathOnCD);
	SYSTEMTIME GetTimeAsSystemTime();
	CFileRecord* AddEmptyDirectory(char* pstrName);
	void RemoveSubItem(CFileRecord* pRecord, bool bDelete);
	CFileRecord* GetParent();
	LPCTSTR GetPathOnCD();
	long GetTotalSize();
	
	enum EnumRecordType
	{
		DOT_RECORD, 
		DOT_DOT_RECORD, 
		DIRECTORY_RECORD, 
		FILE_RECORD
	};

	long GetSector();
	void SetSector(long nNewSector);
	long GetFileSize();
	void SetFileSize(long nNewSize);
	int GetParentIndex();
	void SetParentIndex(int iNewParentIndex);
	LPCTSTR GetFullpath();
	LPCTSTR GetName();
	void SetFullpath(LPCTSTR pstrFullpath);
	void SetName(LPCTSTR pstrName);
	void SetFileRecordType(EnumRecordType eNewType);
	EnumRecordType GetFileRecordType();
	FILETIME GetTime();
	void SetTime(FILETIME creationTime);
	
	void Destroy();
	CFileRecord* FindDirectory(LPCTSTR pstrPath, bool bCreate = false);
	CRecordArray* GetSubItems();
	long GetNameLength();
	bool ConstructPathTable(CRecordArray & arrPathTable);
	CFileRecord* AddFile(LPCTSTR pstrPath);

	CFileRecord(CFileRecord* pParent);
	virtual ~CFileRecord();

	void DestroySubItems(CFileRecord* pRecord);

protected:
	void SetRecordProperties(CFileRecord* pRecord, WIN32_FIND_DATA& wfind, char* pstrDir);
	void AddSlash(char* pstr);
	void AddRecordChildrenToArray(CFileRecord* pRecord, CRecordArray& arrChildren, int iParentIndex, bool bAddDirsOnly);
	static int SortProc(const void *arg1,  const void *arg2);
	bool AddDirectoryItems(LPCTSTR pstrPath, CFileRecord* pDirectoryRecord = NULL);

private:
	bool m_bAlreadyOnCD;
	long m_nTotalSize;
	FILETIME m_creationTime;
	int m_iParentIndex;
	EnumRecordType m_eType;
	long  m_nSector;
	long  m_nFileSize;
	char* m_pstrName;
	char* m_pstrFullpath;
	char* m_pstrPathOnCD;
	CRecordArray m_arrFiles;
	CFileRecord* m_pParent;
};

#endif // !defined(AFX_FILERECORD_H__C1C5A797_8640_4522_8F61_A977C7E2AEF1__INCLUDED_)
