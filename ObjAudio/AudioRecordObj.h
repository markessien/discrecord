// AudioRecordObj.h : Deklaration von CAudioRecordObj

#ifndef __AUDIORECORDOBJ_H_
#define __AUDIORECORDOBJ_H_

#include "resource.h"       // Hauptsymbole
#include <atlctl.h>
#include "license.h"
#include "..\stdafx.h"
#include "AudioRecordCP.h"

#define ICallback CAudioRecordObj

class CDiscWriter;
class CDiscAudio;

/////////////////////////////////////////////////////////////////////////////
// CAudioRecordObj
class ATL_NO_VTABLE CAudioRecordObj : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IAudioRecordObj, &IID_IAudioRecordObj, &LIBID_AUDIORECORDLib>,
	public CComControl<CAudioRecordObj>,
	public IPersistStreamInitImpl<CAudioRecordObj>,
	public IOleControlImpl<CAudioRecordObj>,
	public IOleObjectImpl<CAudioRecordObj>,
	public IOleInPlaceActiveObjectImpl<CAudioRecordObj>,
	public IViewObjectExImpl<CAudioRecordObj>,
	public IOleInPlaceObjectWindowlessImpl<CAudioRecordObj>,
	public IConnectionPointContainerImpl<CAudioRecordObj>,
	public IPersistStorageImpl<CAudioRecordObj>,
	public ISpecifyPropertyPagesImpl<CAudioRecordObj>,
	public IQuickActivateImpl<CAudioRecordObj>,
	public IDataObjectImpl<CAudioRecordObj>,
	public IProvideClassInfo2Impl<&CLSID_AudioRecordObj, &DIID__IAudioRecordObjEvents, &LIBID_AUDIORECORDLib>,
	public IPropertyNotifySinkCP<CAudioRecordObj>,
	public CComCoClass<CAudioRecordObj, &CLSID_AudioRecordObj>,
	public CProxy_IAudioRecordObjEvents< CAudioRecordObj >
{
	DECLARE_CLASSFACTORY2(CLicense)
public:
	CAudioRecordObj();

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

DECLARE_REGISTRY_RESOURCEID(IDR_AUDIORECORDOBJ)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CAudioRecordObj)
	COM_INTERFACE_ENTRY(IAudioRecordObj)
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

BEGIN_PROP_MAP(CAudioRecordObj)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Beispieleinträge
	// PROP_ENTRY("Eigenschaftenbeschreibung", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CAudioRecordObj)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__IAudioRecordObjEvents)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CAudioRecordObj)
	CHAIN_MSG_MAP(CComControl<CAudioRecordObj>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Prototypen von Behandlungsroutinen:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);



// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IAudioRecordObj
public:
	
	STDMETHOD(get_WriteFeatureSupported)(/*[in]*/ EnumFeature FeatureName, /*[out, retval]*/ EnumFeatureSupport *pVal);
	STDMETHOD(get_ReadFeatureSupported)(/*[in]*/ EnumFeature FeatureName, /*[out, retval]*/ EnumFeatureSupport *pVal);
	STDMETHOD(ListAvailableReadSpeeds)();
	STDMETHOD(GetDriveInfo)(/*[out]*/ BSTR * DriveName, /*[out]*/ BSTR * FirmwareVersion, /*[out]*/  long * BufferSize, /*[out]*/  BSTR * Date, /*[out]*/ BSTR  * SerialNumber);
	STDMETHOD(get_AudioTrackDuration)(/*[in]*/ long Index, /*[out, retval]*/ double *pVal);
	STDMETHOD(get_WriteType)(/*[out, retval]*/ EnumWriteType *pVal);
	STDMETHOD(put_WriteType)(/*[in]*/ EnumWriteType newVal);
	STDMETHOD(get_PreferredCommMethod)(/*[out, retval]*/ EnumCommunication *pVal);
	STDMETHOD(get_CommMethod)(/*[out, retval]*/ EnumCommunication *pVal);
	STDMETHOD(put_CommMethod)(/*[in]*/ EnumCommunication newVal);
	STDMETHOD(get_EraseProgress)(/*[out, retval]*/ long *pVal);
	STDMETHOD(StartDiscErase)(VARIANT_BOOL QuickErase);
	STDMETHOD(get_AudioPause)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_AudioPause)(/*[in]*/ double newVal);
	STDMETHOD(get_ProgressTime)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_DurationTime)(/*[out, retval]*/ double *pVal);
	STDMETHOD(MoveAudioTrack)(/*[in]*/ long Index, /*[in]*/ long NewIndex);
	STDMETHOD(get_BurnProof)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_BurnProof)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(RemoveAudioTrack)(/*[in]*/ long Index);
	STDMETHOD(get_TimeElapsed)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_FileBufferUsed)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_FileBufferSize)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_CurLBA)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_CurTrack)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_DiscCapacitySeconds)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_TotalFileSize)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_TotalAudioTrackDuration)(/*[out, retval]*/ double *pVal);
	STDMETHOD(ListAudioTracks)();
	STDMETHOD(AbortFileScan)();
	STDMETHOD(BurnAudioCD)();
	STDMETHOD(AddAudioTrack)(/*[in]*/ BSTR SourceFile, double * pdDuration);
	STDMETHOD(get_TestMode)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_TestMode)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(DriveBufferInfo)(/*[out]*/ long * BufferSize, /*[out]*/ long * BufferFree);
	STDMETHOD(ListAvailableWriteSpeeds)();
	STDMETHOD(get_WriteSpeed)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_WriteSpeed)(/*[in]*/ long newVal);
	STDMETHOD(get_DiscCapacity)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_DiscState)(/*[out, retval]*/ EnumDiscState *pVal);
	STDMETHOD(get_DiscType)(/*[out, retval]*/ EnumDiscType *pVal);
	STDMETHOD(AbortBurn)();
	STDMETHOD(EjectDevice)(/*[in]*/ VARIANT_BOOL bEject);
	STDMETHOD(get_CurrentDevice)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_CurrentDevice)(/*[in]*/ long newVal);
	STDMETHOD(get_Progress)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_Duration)(/*[out, retval]*/ double *pVal);
	STDMETHOD(FileSelectDialog)(/*[in]*/ long HwndParent, /*[in]*/ VARIANT_BOOL IsSaveDialog, /*[in]*/ BSTR FilterMask, /*[in]*/ BSTR DefaultExt, /*[in]*/ long nFilterIndex, /*[out, retval]*/ BSTR * pResult);
	STDMETHOD(Initialize)();
	STDMETHOD(ListDevices)();
	STDMETHOD(ClearDirectoryStructure)();
	STDMETHOD(get_EjectWhenDone)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_EjectWhenDone)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_DiscSize)(/*[out, retval]*/ long *pVal);

	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
		RECT& rc = *(RECT*)di.prcBounds;
		DrawIcon(di.hdcDraw, rc.left, rc.top, m_hIcon);

		return S_OK;
	}
	
	void FileScanned(const char* pstrName, const char * pstrPathOnCD, long nSize){
		Fire_FileScanned(CComBSTR(pstrName), CComBSTR(pstrPathOnCD), nSize);
	}

private:
	CDiscAudio* m_pAudioDisc;
	CDiscWriter* m_pDiscWriter;
	HICON m_hIcon;
	bool m_bASPI;
};

#endif //__AUDIORECORDOBJ_H_
