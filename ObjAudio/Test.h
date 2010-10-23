// Test.h : Declaration of the CTest

#ifndef __TEST_H_
#define __TEST_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTest
class ATL_NO_VTABLE CTest : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTest, &CLSID_Test>,
	public IConnectionPointContainerImpl<CTest>,
	public IDispatchImpl<ITest, &IID_ITest, &LIBID_AUDIORECORDLib>
{
public:
	CTest()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_TEST)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTest)
	COM_INTERFACE_ENTRY(ITest)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(CTest)
END_CONNECTION_POINT_MAP()


// ITest
public:
};

#endif //__TEST_H_
