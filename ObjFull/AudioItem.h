// AudioItem.h : Deklaration von CAudioItem

#ifndef __AudioItem_H_
#define __AudioItem_H_

#include "resource.h"       // Hauptsymbole
#include "DiscRecordCP.h"

class CDiscAudio;

/////////////////////////////////////////////////////////////////////////////
// CAudioItem
class ATL_NO_VTABLE CAudioItem : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAudioItem, &CLSID_AudioItem>,
	public IConnectionPointContainerImpl<CAudioItem>,
	public IDispatchImpl<IAudioItem, &IID_IAudioItem, &LIBID_DISCRECORDLib>,
	public CProxy_IDiscRecordObjEvents< CAudioItem >
{
public:
	CAudioItem()
	{
		m_dDuration = 0;
		m_bIsRoot = true;
		m_pAudioDisc = NULL;
	}

	void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_AUDIOITEM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CAudioItem)
	COM_INTERFACE_ENTRY(IAudioItem)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CAudioItem)
CONNECTION_POINT_ENTRY(DIID__IDiscRecordObjEvents)
END_CONNECTION_POINT_MAP()

// IAudioItem
public:
	STDMETHOD(AddFile)(/*[in]*/ BSTR SourceFile);
	STDMETHOD(MoveTrack)(/*[in]*/ long Index, /*[in]*/ long NewIndex);
	STDMETHOD(get_Track)(/*[in]*/ long Index, /*[out, retval]*/ IAudioItem* *pVal);
	STDMETHOD(get_LocalFilePath)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Name)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Duration)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_TrackCount)(/*[out, retval]*/ long *pVal);
	STDMETHOD(RemoveTrack)(/*[in]*/ long Index);
	STDMETHOD(AddTrack)(/*[in]*/ BSTR SourceFile);
	
	void SetAudioDisc(CDiscAudio* pAudioDisc);
private:
	HRESULT CAudioItem::CreateItem(CAudioItem **ppItem);

private:
	bool m_bIsRoot;
	double m_dDuration;
	CDiscAudio* m_pAudioDisc;
	CArray<CAudioItem*, CAudioItem*> m_arrTracks;
	CComBSTR m_strName;
	CComBSTR m_strLocalPath;
};

#endif //__AudioItem_H_
