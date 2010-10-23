// AudioDisc.cpp : Implementierung von CAudioItem
#include "stdafx.h"
#include "DiscRecord.h"
#include "AudioItem.h"
#include "..\disc.h"
#include "..\audiocd\DiscAudio.h"

/////////////////////////////////////////////////////////////////////////////
// CAudioItem


STDMETHODIMP CAudioItem::AddTrack(BSTR SourceFile)
{

	USES_CONVERSION;

	double dDuration = 0;
	dDuration = m_pAudioDisc->AddAudioFile(W2A(SourceFile), dDuration);
	
	if (dDuration == 0)
		return S_OK;

	CAudioItem* pItem = NULL;
	CreateItem(&pItem);

	m_arrTracks.Add(pItem);

	pItem->m_dDuration = dDuration;
	pItem->m_bIsRoot = false;
	pItem->m_strLocalPath = SourceFile;

	char szTitle[MAX_PATH];
	char sz[MAX_PATH];
	strcpy(sz, W2A(SourceFile));
	char * psz = strrchr(sz, '\\');
	if (psz)
		strcpy(szTitle, psz + 1);
	else
		strcpy(szTitle, sz);
	
	char szName[500] = {0};
	sprintf(szName, "Audio Track %lu (%s)", m_arrTracks.GetSize(), szTitle);
	pItem->m_strName = szName;

	return S_OK;
}

void CAudioItem::FinalRelease()
{
	for (int i=0;i<m_arrTracks.GetSize();i++)
	{
		m_arrTracks.GetAt(i)->Release();
	}

	m_arrTracks.RemoveAll();
}

STDMETHODIMP CAudioItem::RemoveTrack(long Index)
{
	if (Index < 1 || Index > m_arrTracks.GetSize())
		return E_FAIL;

	m_arrTracks.RemoveAt(Index - 1);

	return S_OK;
}

STDMETHODIMP CAudioItem::get_TrackCount(long *pVal)
{
	*pVal = m_arrTracks.GetSize();

	return S_OK;
}

STDMETHODIMP CAudioItem::get_Duration(double *pVal)
{
	if (m_bIsRoot)
		*pVal = m_pAudioDisc->GetTotalDuration();
	else
		*pVal = m_dDuration;

	return S_OK;
}

void CAudioItem::SetAudioDisc(CDiscAudio *pAudioDisc)
{
	m_pAudioDisc = pAudioDisc;
}

STDMETHODIMP CAudioItem::get_Name(BSTR *pVal)
{
	m_strName.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CAudioItem::put_Name(BSTR newVal)
{
	m_strName = newVal;

	return S_OK;
}

STDMETHODIMP CAudioItem::get_LocalFilePath(BSTR *pVal)
{
	m_strLocalPath.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CAudioItem::get_Track(long Index, IAudioItem **pVal)
{

	*pVal = m_arrTracks.GetAt(Index - 1);
	(*pVal)->AddRef();

	return S_OK;
}

HRESULT CAudioItem::CreateItem(CAudioItem **ppItem)
{
	HRESULT hr = CoCreateInstance(CLSID_AudioItem, 
								  NULL, CLSCTX_INPROC_SERVER,
								  IID_IAudioItem, 
								  (void**)ppItem);
	ASSERT(SUCCEEDED(hr));
	ASSERT(*ppItem);
	return hr;
}


STDMETHODIMP CAudioItem::MoveTrack(long Index, long NewIndex)
{
	if (Index < 0 || NewIndex < 0 || 
		Index > m_arrTracks.GetSize() - 1 ||
		NewIndex > m_arrTracks.GetSize() - 1)
		return S_OK;

	CAudioItem* pTrack = m_arrTracks.GetAt(Index);
	
	if (NewIndex <= Index)
	{
		m_arrTracks.InsertAt(NewIndex ? NewIndex : 0, pTrack);
		m_arrTracks.RemoveAt(++Index);
	}
	else
	{
		m_arrTracks.InsertAt(NewIndex + 1, pTrack);
		m_arrTracks.RemoveAt(Index);
	}

	return S_OK;
}

STDMETHODIMP CAudioItem::AddFile(BSTR SourceFile)
{
	AddTrack(SourceFile);

	return S_OK;
}
