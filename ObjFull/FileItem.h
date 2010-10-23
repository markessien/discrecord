// FileItem.h : Deklaration von CFileItem

#ifndef __FILEITEM_H_
#define __FILEITEM_H_

#include "resource.h"       // Hauptsymbole
//#include "FileRecord.h"

class CFileRecord;

/////////////////////////////////////////////////////////////////////////////
// CFileItem
class ATL_NO_VTABLE CFileItem : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFileItem, &CLSID_FileItem>,
	public IDispatchImpl<IFileItem, &IID_IFileItem, &LIBID_DISCRECORDLib>
{
public:
	CFileItem();
	void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_FILEITEM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFileItem)
	COM_INTERFACE_ENTRY(IFileItem)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IFileItem
public:
	STDMETHOD(FindSubItem)(/*[in]*/ BSTR RelativePath, /*[out, retval]*/ IFileItem** ppItem);
	STDMETHOD(XPathAddEmptyFolder)(/*[in]*/ BSTR Name, /*[in]*/ BSTR PathOnCD);
	STDMETHOD(XPathAddFile)(/*[in]*/ BSTR LocalPath, /*[in]*/ BSTR PathOnCD);
	void SetParent(CFileItem* pParent);
	STDMETHOD(get_Parent)(/*[out, retval]*/ IFileItem* *pVal);
	STDMETHOD(Clear)();
	STDMETHOD(Sort)();
	void SetFileRecord(CFileRecord* pRecord);
	
	STDMETHOD(AddEmptyFolder)(/*[in]*/ BSTR Name,  IFileItem** ppItem);
	STDMETHOD(RemoveByIndex)(/*[in]*/ long Index);
	STDMETHOD(AddFile)(/*[in]*/ BSTR LocalPath, IFileItem** ppItem);
	STDMETHOD(get_SubFile)(/*[in]*/ long Index, /*[out, retval]*/ IFileItem **pVal);
	STDMETHOD(get_SubFileCount)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_Size)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_LocalPath)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_LocalPath)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Name)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Type)(/*[out, retval]*/ EnumFileType *pVal);

private:
	static HRESULT CreateItem(CFileItem** ppItem);
	static int SortProc(const void *arg1,  const void *arg2);
	void ClearDirectory(CFileItem* pItem);
private:
	CFileRecord* m_pRecord;
	CArray<CFileItem*, CFileItem*> m_arrFiles;
	CFileItem* m_pParent;
};

#endif //__FILEITEM_H_
