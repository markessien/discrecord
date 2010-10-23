// FileItem.cpp : Implementierung von CFileItem
#include "stdafx.h"
#include "DiscRecord.h"
#include "FileItem.h"
#include "..\datacd\filerecord.h"

/////////////////////////////////////////////////////////////////////////////
// CFileItem
CFileItem::CFileItem()
{
	m_pRecord = NULL;
	m_pParent = NULL;
}

void CFileItem::FinalRelease()
{
	Clear();

	delete m_pRecord;
	m_pRecord = NULL;
}

STDMETHODIMP CFileItem::get_Type(EnumFileType *pVal)
{
	*pVal = m_pRecord->GetFileRecordType() == CFileRecord::FILE_RECORD ? typeFile : typeDirectory;

	return S_OK;
}


STDMETHODIMP CFileItem::get_Name(BSTR *pVal)
{
	CComBSTR str = m_pRecord->GetName();
	str.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CFileItem::put_Name(BSTR newVal)
{
	USES_CONVERSION;
	m_pRecord->SetName(W2A(newVal));

	return S_OK;
}

STDMETHODIMP CFileItem::get_LocalPath(BSTR *pVal)
{
	CComBSTR str = m_pRecord->GetFullpath();
	str.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CFileItem::put_LocalPath(BSTR newVal)
{
	return E_NOTIMPL;
}

STDMETHODIMP CFileItem::get_Size(double *pVal)
{
	*pVal = m_pRecord->GetTotalSize();

	return S_OK;
}

STDMETHODIMP CFileItem::get_SubFileCount(long *pVal)
{
	*pVal = m_arrFiles.GetSize();

	return S_OK;
}

STDMETHODIMP CFileItem::get_SubFile(long Index, IFileItem **pVal)
{
	 // 1 based index

	if (Index < 1 || Index > m_arrFiles.GetSize())
	{
		*pVal = NULL;
		return S_OK;
	}

	*pVal = m_arrFiles.GetAt(Index - 1);
	_ASSERT(*pVal);
	(*pVal)->AddRef();

	return S_OK;
}


STDMETHODIMP CFileItem::AddFile(BSTR LocalPath, IFileItem** ppItem)
{
	// This function adds a COM object to the subfile array in this
	// class, and adds one to
	
	*ppItem = NULL;
	if (m_pRecord->GetFileRecordType() == CFileRecord::DIRECTORY_RECORD)
	{
		CFileItem* pItem = NULL;
		CreateItem(&pItem);
		m_arrFiles.Add(pItem);
		pItem->SetParent(this);

		USES_CONVERSION;
		CFileRecord* pRecord = m_pRecord->AddFile(W2A(LocalPath));
		pItem->SetFileRecord(pRecord);
		
		pItem->AddRef();
		*ppItem = pItem;
	}

	return S_OK;
}

STDMETHODIMP CFileItem::RemoveByIndex(long Index)
{	
	if (Index < 1 || Index > m_arrFiles.GetSize())
		return E_FAIL;

	CFileItem* pItem = m_arrFiles.GetAt(Index - 1);
	pItem->Clear();

	m_arrFiles.RemoveAt(Index - 1);
	m_pRecord->RemoveSubItem(Index - 1, false);

	pItem->Release();
	
	return S_OK;
}

STDMETHODIMP CFileItem::AddEmptyFolder(BSTR Name, IFileItem** ppItem)
{
	*ppItem = NULL;
	if (m_pRecord->GetFileRecordType() == CFileRecord::DIRECTORY_RECORD)
	{
		CFileItem* pItem = NULL;
		CreateItem(&pItem);
		m_arrFiles.Add(pItem);
		pItem->SetParent(this);

		USES_CONVERSION;
		CFileRecord* pRecord = m_pRecord->AddEmptyDirectory(W2A(Name));
		pItem->SetFileRecord(pRecord);

		pItem->AddRef();
		*ppItem = pItem;
	}

	return S_OK;
}

HRESULT CFileItem::CreateItem(CFileItem **ppItem)
{
	HRESULT hr = CoCreateInstance(CLSID_FileItem, 
								  NULL, CLSCTX_INPROC_SERVER,
								  IID_IFileItem, 
								  (void**)ppItem);
	ASSERT(SUCCEEDED(hr));
	ASSERT(*ppItem);
	return hr;
}

void CFileItem::SetFileRecord(CFileRecord *pRecord)
{
	m_pRecord = pRecord;
	_ASSERT(m_pRecord);
}

STDMETHODIMP CFileItem::Sort()
{
	// sort the record
	m_pRecord->Sort();
	
	qsort(m_arrFiles.GetData(), m_arrFiles.GetSize(), 
		  sizeof(CFileItem*), CFileItem::SortProc);

	return S_OK;
}

int CFileItem::SortProc(const void *arg1,  const void *arg2)
{
	CFileItem* pRec1 = (CFileItem*)*(long*)arg1;
	CFileItem* pRec2 = (CFileItem*)*(long*)arg2;
	
	if (pRec1->m_pRecord->GetFileRecordType() == CFileRecord::DIRECTORY_RECORD &&
		pRec2->m_pRecord->GetFileRecordType() == CFileRecord::FILE_RECORD)
	{
		return -1;
	}
	
	if (pRec2->m_pRecord->GetFileRecordType() == CFileRecord::DIRECTORY_RECORD &&
		pRec1->m_pRecord->GetFileRecordType() == CFileRecord::FILE_RECORD)
	{
		return 1;
	}

	int iResult = _stricmp(pRec1->m_pRecord->GetName(), pRec2->m_pRecord->GetName());
	return iResult;
}

STDMETHODIMP CFileItem::Clear()
{
	ClearDirectory(this);

	return S_OK;
}

void CFileItem::ClearDirectory(CFileItem* pItem)
{
	long nCount = pItem->m_arrFiles.GetSize();

	for (int i=1;i<=nCount;i++)
	{
		if (pItem->m_pRecord->GetFileRecordType() == CFileRecord::DIRECTORY_RECORD)
		{
			ClearDirectory(pItem->m_arrFiles.GetAt(i-1));
			pItem->m_pRecord->RemoveSubItem(pItem->m_arrFiles.GetAt(i-1)->m_pRecord, false);
			pItem->m_arrFiles.GetAt(i-1)->Release();
		}
		else
		{
			pItem->m_pRecord->RemoveSubItem(pItem->m_arrFiles.GetAt(i-1)->m_pRecord, false);
			pItem->m_arrFiles.GetAt(i-1)->Release();
		}
	}

	pItem->m_arrFiles.RemoveAll();
}

STDMETHODIMP CFileItem::get_Parent(IFileItem **pVal)
{
	*pVal = m_pParent;

	if (m_pParent)
		m_pParent->AddRef();

	return S_OK;
}

void CFileItem::SetParent(CFileItem *pParent)
{
	m_pParent = pParent;
}

STDMETHODIMP CFileItem::XPathAddFile(BSTR LocalPath, BSTR PathOnCD)
{
	IFileItem* pParentFolder = NULL;
	FindSubItem(PathOnCD, &pParentFolder);

	if (pParentFolder == NULL)
	{
		pParentFolder = this;
		pParentFolder->AddRef();
	}
	
	IFileItem* pItem = NULL;
	pParentFolder->AddFile(LocalPath, &pItem);
	pItem->Release();
	pParentFolder->Release();

	return S_OK;
}

STDMETHODIMP CFileItem::XPathAddEmptyFolder(BSTR Name, BSTR PathOnCD)
{
	IFileItem* pParentFolder = NULL;
	FindSubItem(PathOnCD, &pParentFolder);

	if (pParentFolder == NULL)
	{
		pParentFolder = this;
		pParentFolder->AddRef();
	}

	IFileItem* pFolder = NULL;
	pParentFolder->AddEmptyFolder(Name, &pFolder);
	pFolder->Release();
	pParentFolder->Release();

	return S_OK;
}

STDMETHODIMP CFileItem::FindSubItem(BSTR RelativePath, IFileItem **ppItem)
{
	CFileItem* pResult = this;
	
	*ppItem = NULL;

	USES_CONVERSION;

	// We copy a copy we can modify
	char szPath[MAX_PATH] = {0};
	strcpy(szPath, W2A(RelativePath));

	if (strcmp(szPath, "\\") == 0 ||
		strcmp(szPath, "") == 0)
	{
		pResult = this; // if \ then this is the result
		*ppItem = pResult;
		pResult->AddRef();
		return S_OK;
	}

	char* pch = NULL;
	pch = strtok (szPath, "\\");
	while (pch != NULL)
	{
		//each pch will point at a piece of the path
		bool bFound = false;
		for (int i=0;i<pResult->m_pRecord->GetSubItems()->GetSize();i++)
		{
			if (strcmp(pResult->m_pRecord->GetSubItems()->GetAt(i)->GetName(), pch) == 0)
			{
				pResult = pResult->m_arrFiles.GetAt(i);
				bFound = true;
				break;
			}
		}

		pch = strtok (NULL, "\\");
	}
	
	if (pResult)
		pResult->AddRef();
	*ppItem = pResult;
	return S_OK;
}
