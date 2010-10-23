// DiscRecordObj.h : Deklaration von CDiscRecordObj

#ifndef __DISCRECORDOBJ_H_
#define __DISCRECORDOBJ_H_

#include "resource.h"       // Hauptsymbole
#include <atlctl.h>
#include "DiscRecordCP.h"
#include "license.h"
#include "..\stdafx.h"

#define ICallback CDiscRecordObj

class CDiscWriter;
class CDiscAudio;
class CDiscISO9660;
class CFileItem;
class CAudioItem;
class CDiscImage;
class CDiscParser;

/////////////////////////////////////////////////////////////////////////////
// CDiscRecordObj
class ATL_NO_VTABLE CDiscRecordObj : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IDiscRecordObj, &IID_IDiscRecordObj, &LIBID_DISCRECORDLib>,
	public CComControl<CDiscRecordObj>,
	public IPersistStreamInitImpl<CDiscRecordObj>,
	public IOleControlImpl<CDiscRecordObj>,
	public IOleObjectImpl<CDiscRecordObj>,
	public IOleInPlaceActiveObjectImpl<CDiscRecordObj>,
	public IViewObjectExImpl<CDiscRecordObj>,
	public IOleInPlaceObjectWindowlessImpl<CDiscRecordObj>,
	public IConnectionPointContainerImpl<CDiscRecordObj>,
	public IPersistStorageImpl<CDiscRecordObj>,
	public ISpecifyPropertyPagesImpl<CDiscRecordObj>,
	public IQuickActivateImpl<CDiscRecordObj>,
	public IDataObjectImpl<CDiscRecordObj>,
	public IProvideClassInfo2Impl<&CLSID_DiscRecord, &DIID__IDiscRecordObjEvents, &LIBID_DISCRECORDLib>,
	public IPropertyNotifySinkCP<CDiscRecordObj>,
	public CComCoClass<CDiscRecordObj, &CLSID_DiscRecord>,
	public CProxy_IDiscRecordObjEvents< CDiscRecordObj >
{

//	DECLARE_CLASSFACTORY2(CLicense)

public:
	CDiscRecordObj();
	
	HRESULT FinalConstruct( )
	{
		SIZEL size = {32, 32};
		AtlPixelToHiMetric( &size, &m_sizeExtent );
		m_sizeNatural = m_sizeExtent;

		SIZEL szlPixels, szlMetric;
		szlPixels.cx = 32;
		szlPixels.cy = 32;

		AtlPixelToHiMetric(&szlPixels, &szlMetric);

		// IOleObjectImpl
		SetExtent(DVASPECT_CONTENT, &szlMetric);

		// update control sizing...
		m_rcPos.right= m_rcPos.left + 32;
		m_rcPos.bottom= m_rcPos.top + 32;

		m_bAutoSize = TRUE;

		return S_OK;
	}

	void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_DISCRECORDOBJ)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDiscRecordObj)
	COM_INTERFACE_ENTRY(IDiscRecordObj)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_PROP_MAP(CDiscRecordObj)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Beispieleinträge
	// PROP_ENTRY("Eigenschaftenbeschreibung", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CDiscRecordObj)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__IDiscRecordObjEvents)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CDiscRecordObj)
	CHAIN_MSG_MAP(CComControl<CDiscRecordObj>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Prototypen von Behandlungsroutinen:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);



// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IDiscRecordObj
public:
	STDMETHOD(get_FadeBetweenTracks)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_FadeBetweenTracks)(/*[in]*/ long newVal);
	STDMETHOD(put_LicenseKey)(/*[in]*/ BSTR newVal);
	STDMETHOD(OpenDevice)(/*[in]*/ long Index);
	STDMETHOD(get_WriteSpeed)(/*[in]*/ long Index, /*[out, retval]*/ long *pVal);
	STDMETHOD(get_WriteSpeedCount)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_DriveName)(/*[in]*/ long Index, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_DriveCount)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_LeaveSessionOpen)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_LeaveSessionOpen)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(DoNothing)();
	STDMETHOD(get_CurrentReadSpeed)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_CurrentReadSpeed)(/*[in]*/ long newVal);
	STDMETHOD(AbortCopy)();
	STDMETHOD(get_TempDirectory)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_TempDirectory)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Erasing)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_AudioDisc)(/*[out, retval]*/ IAudioItem* *pVal);
	STDMETHOD(QueryFileBuffer)(/*[out]*/ long * Used, /*[out]*/ long * Length);
	STDMETHOD(get_DataDisc)(/*[out, retval]*/ IFileItem **pVal);
	STDMETHOD(get_WriteFeatureSupported)(/*[in]*/ EnumFeature FeatureName, /*[out, retval]*/ EnumFeatureSupport *pVal);
	STDMETHOD(get_ReadFeatureSupported)(/*[in]*/ EnumFeature FeatureName, /*[out, retval]*/ EnumFeatureSupport *pVal);
	STDMETHOD(ListAvailableReadSpeeds)();
	STDMETHOD(QueryDriveInfo)(/*[out]*/ BSTR * DriveName, /*[out]*/ BSTR * FirmwareVersion, /*[out]*/  long * BufferSize, /*[out]*/  BSTR * Date, /*[out]*/ BSTR  * SerialNumber);
	STDMETHOD(get_WriteType)(/*[out, retval]*/ EnumWriteType *pVal);
	STDMETHOD(put_WriteType)(/*[in]*/ EnumWriteType newVal);
	STDMETHOD(get_PreferredCommunicationMethod)(/*[out, retval]*/ EnumCommunication *pVal);
	STDMETHOD(get_CommunicationMethod)(/*[out, retval]*/ EnumCommunication *pVal);
	STDMETHOD(put_CommunicationMethod)(/*[in]*/ EnumCommunication newVal);
	STDMETHOD(StartDiscErase)(VARIANT_BOOL QuickErase);
	STDMETHOD(get_PauseBetweenTracks)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_PauseBetweenTracks)(/*[in]*/ double newVal);
	STDMETHOD(get_ProgressCurSeconds)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_ProgressMaxSeconds)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_BurnProof)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_BurnProof)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_TimeElapsed)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_CurrentLBA)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_CurrentTrack)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_DiscCapacitySeconds)(/*[out, retval]*/ double *pVal);
	STDMETHOD(BurnAudioCD)();
	STDMETHOD(get_TestMode)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_TestMode)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(QueryDriveBuffer)(long *Used, long *Length);
	STDMETHOD(ListAvailableWriteSpeeds)();
	STDMETHOD(get_CurrentWriteSpeed)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_CurrentWriteSpeed)(/*[in]*/ long newVal);
	STDMETHOD(get_DiscCapacityBytes)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_DiscState)(/*[out, retval]*/ EnumDiscState *pVal);
	STDMETHOD(get_DiscType)(/*[out, retval]*/ EnumDiscType *pVal);
	STDMETHOD(BurnDataCD)();
	STDMETHOD(BurnFromISO)(/*[in]*/ BSTR InputISOPath);
	STDMETHOD(get_CDLabel)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_CDLabel)(/*[in]*/ BSTR newVal);
	STDMETHOD(AbortBurn)();
	STDMETHOD(EjectDevice)(/*[in]*/ VARIANT_BOOL bEject);
	STDMETHOD(get_SelectedWriterDeviceIndex)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_SelectedWriterDeviceIndex)(/*[in]*/ long newVal);
	STDMETHOD(get_ProgressCur)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_ProgressMax)(/*[out, retval]*/ double *pVal);
	STDMETHOD(FileSelectDialog)(/*[in]*/ long HwndParent, /*[in]*/ VARIANT_BOOL IsSaveDialog, /*[in]*/ BSTR FilterMask, /*[in]*/ BSTR DefaultExt, /*[in]*/ long nFilterIndex, /*[out, retval]*/ BSTR * pResult);
	STDMETHOD(Initialize)();
	STDMETHOD(ListDevices)(VARIANT_BOOL OnlyWriteable);
	STDMETHOD(get_SelectedWriterDeviceDriveLetter)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(CopyCDToFixedDrive)(long DeviceIndex, /*[in]*/ BSTR TargetFile);
	STDMETHOD(ClearFiles)();
	STDMETHOD(get_EjectWhenDone)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_EjectWhenDone)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_DiscSize)(/*[out, retval]*/ long *pVal);
	
private:
	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
		RECT& rc = *(RECT*)di.prcBounds;
		DrawIcon(di.hdcDraw, rc.left, rc.top, m_hIcon);

		return S_OK;
	}

private:
	CComBSTR m_strTempDirectory;
	
	CAudioItem* m_pAudioRoot;
	CFileItem* m_pDataRoot;

	CDiscAudio* m_pAudioDisc;
	CDiscISO9660* m_pDataDisc;
	CDiscImage* m_pImageDisc;
	CDiscWriter* m_pDiscWriter;

	HICON m_hIcon;
	bool m_bASPI;
};

#endif //__DISCRECORDOBJ_H_
