// AudioRecordObj.cpp : Implementierung von CAudioRecordObj

#include "stdafx.h"
#include "AudioRecord.h"
#include "AudioRecordObj.h"
#include "discwriter.h"
#include "stdio.h"
#include "disc.h"
#include "..\audiocd\discaudio.h"

/////////////////////////////////////////////////////////////////////////////
// CAudioRecordObj


CAudioRecordObj::CAudioRecordObj() : m_hIcon( LoadIcon(_Module.m_hInstResource, (LPCTSTR) IDI_RECORD) )
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(-1); // For memory leaks. Change to allocation number to break at that position.
						   // Don't forget to reset back to -1 to make life easier for other developers.

	m_pDiscWriter = new CDiscWriter((ICallback*)this);
	m_pAudioDisc = new CDiscAudio;

	m_bASPI = true;
}
	
void CAudioRecordObj::FinalRelease()
{
	delete m_pDiscWriter;
	delete m_pAudioDisc;
}

STDMETHODIMP CAudioRecordObj::ListDevices()
{
//	m_pDiscWriter->RescanCDWriterDevices();
	
	int iCount = m_pDiscWriter->GetDeviceCount();
	for (int i= 0; i< iCount;i++)
	{
		CComBSTR strID = m_pDiscWriter->GetDevice(i)->szID;
		CComBSTR strAdapter = m_pDiscWriter->GetDevice(i)->szAdapter;

		if (m_pDiscWriter->GetDevice(i)->bWriteCDR || 
			m_pDiscWriter->GetDevice(i)->bWriteCDRW)
		{
			Fire_DeviceListed(strID, strAdapter);
		}
	//	else
	//		if (OnlyWriteable == VARIANT_FALSE)
	//			Fire_DeviceListed(strID, strAdapter, VARIANT_FALSE);	
	}

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::Initialize()
{
	m_pDiscWriter->Initialize(m_bASPI);

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::FileSelectDialog(long HwndParent, VARIANT_BOOL IsSaveDialog, BSTR FilterMask, BSTR DefaultExt, long nFilterIndex, BSTR *pResult)
{
	char szSelectedFile[MAX_PATH] = {0, 0};
	
	HWND hwndAx = (HWND)HwndParent;

    if (HwndParent == NULL)
    {
	    m_spInPlaceSite->GetWindow(&hwndAx);
    }
	
	USES_CONVERSION;
	
	char szMask[1024] = {0};
	strcpy(szMask, W2A(FilterMask));
	
	int nLen = strlen(szMask);
	for (int i=0; i<nLen;i++)
	{
		if (szMask[i] == '|')
			szMask[i] = '\0';
	}
	szMask[i+1] = '\0';

    OPENFILENAME ofn;
    memset(&ofn, 0, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = (HWND)hwndAx;
    ofn.lpstrFilter = szMask;
    ofn.lpstrFile = szSelectedFile;
    ofn.lpstrTitle = NULL;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = W2A(DefaultExt);
	ofn.nFilterIndex = nFilterIndex;

	CComBSTR bstr = L"";
	if ((IsSaveDialog == VARIANT_FALSE) && GetOpenFileName(&ofn) != 0)
	{
		bstr = szSelectedFile;
	} else
	if ((IsSaveDialog == VARIANT_TRUE) && GetSaveFileName(&ofn) != 0)
	{
		bstr = szSelectedFile;
	}
	
	bstr.CopyTo(pResult);


	return S_OK;
}

STDMETHODIMP CAudioRecordObj::get_Duration(double *pVal)
{
	*pVal = m_pDiscWriter->GetDuration();

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::get_Progress(double *pVal)
{
	*pVal = m_pDiscWriter->GetProgress();

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::get_CurrentDevice(long *pVal)
{
	*pVal = m_pDiscWriter->GetCurrentDeviceIndex();

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::put_CurrentDevice(long newVal)
{
	m_pDiscWriter->SetCurrentDeviceIndex(newVal);

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::EjectDevice(VARIANT_BOOL bEject)
{
	m_pDiscWriter->EjectDevice(bEject == VARIANT_TRUE);

	return S_OK;
}


STDMETHODIMP CAudioRecordObj::AbortBurn()
{
	m_pDiscWriter->AbortWrite();

	return S_OK;
}

//DEL STDMETHODIMP CAudioRecordObj::AddDirectory(BSTR Path, BSTR PathOnCD)
//DEL {
//DEL 	USES_CONVERSION;
//DEL 	CFileRecord* pRecord = m_pDataDisc->GetFileSystem()->FindDirectory(W2A(PathOnCD));
//DEL 
//DEL 	if (pRecord)
//DEL 		pRecord->AddDirectory(W2A(Path));
//DEL 
//DEL 	return S_OK;
//DEL }

//DEL STDMETHODIMP CAudioRecordObj::AddFile(BSTR Path, BSTR PathOnCD)
//DEL {
//DEL 	USES_CONVERSION;
//DEL 	CFileRecord* pRecord = m_pDataDisc->GetFileSystem()->FindDirectory(W2A(PathOnCD));
//DEL 
//DEL 	if (pRecord)
//DEL 		pRecord->AddFile(W2A(Path));
//DEL 
//DEL 	return S_OK;
//DEL }


//DEL STDMETHODIMP CAudioRecordObj::get_CDLabel(BSTR *pVal)
//DEL {
//DEL 	m_pDataDisc->GetLabel();
//DEL 
//DEL 	CComBSTR str = m_pDataDisc->GetLabel();
//DEL 	str.CopyTo(pVal);
//DEL 
//DEL 	return S_OK;
//DEL }

//DEL STDMETHODIMP CAudioRecordObj::put_CDLabel(BSTR newVal)
//DEL {
//DEL 	USES_CONVERSION;
//DEL 	m_pDataDisc->SetLabel(W2A(newVal));	
//DEL 
//DEL 	return S_OK;
//DEL }

//DEL STDMETHODIMP CAudioRecordObj::BurnFromISO(BSTR InputISOPath)
//DEL {
//DEL 
//DEL 	return S_OK;
//DEL }

//DEL STDMETHODIMP CAudioRecordObj::Burn()
//DEL {
//DEL 	USES_CONVERSION;
//DEL //	m_pDiscWriter->WriteDisc(m_pDataDisc, NULL);
//DEL 
//DEL 	return S_OK;
//DEL }

STDMETHODIMP CAudioRecordObj::get_DiscType(EnumDiscType *pVal)
{
	*pVal = m_pDiscWriter->GetDiscType();

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::get_DiscState(EnumDiscState *pVal)
{
	*pVal = m_pDiscWriter->GetDiscState();

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::get_DiscCapacity(long *pVal)
{
	*pVal = m_pDiscWriter->GetDiscCapacity();

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::get_WriteSpeed(long *pVal)
{
	*pVal = m_pDiscWriter->GetCurrentWriteSpeed();

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::put_WriteSpeed(long newVal)
{
	m_pDiscWriter->SetCurrentWriteSpeed(newVal);

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::ListAvailableWriteSpeeds()
{
	long nCount = m_pDiscWriter->GetWriteSpeedCount();

	for (int i=0;i<nCount;i++)
	{
		long nSpeed = m_pDiscWriter->GetWriteSpeed(i);

		char szDesc[10] = {0};
		sprintf(szDesc, "%luX", nSpeed);
		
		Fire_WriteSpeedListed(nSpeed, CComBSTR(szDesc));
	}

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::DriveBufferInfo(long *BufferSize, long *BufferFree)
{
	*BufferSize = 0;
	*BufferFree = 0;

	m_pDiscWriter->GetBufferInfo(*BufferSize, *BufferFree);

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::get_TestMode(VARIANT_BOOL *pVal)
{
	*pVal = m_pDiscWriter->GetTestMode() ? VARIANT_TRUE : VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::put_TestMode(VARIANT_BOOL newVal)
{
	m_pDiscWriter->SetTestMode(newVal == VARIANT_TRUE);

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::get_DiscSize(long *pVal)
{
	*pVal = m_pDiscWriter->GetDiscSize();

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::get_EjectWhenDone(VARIANT_BOOL *pVal)
{
	*pVal = m_pDiscWriter->GetEjectWhenDone() ? VARIANT_TRUE : VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::put_EjectWhenDone(VARIANT_BOOL newVal)
{
	m_pDiscWriter->SetEjectWhenDone(newVal == VARIANT_TRUE);

	return S_OK;
}

//DEL STDMETHODIMP CAudioRecordObj::Remove(BSTR PathOnCD)
//DEL {
//DEL 	USES_CONVERSION;
//DEL 
//DEL 	CFileRecord* pTargetRecord = m_pDataDisc->GetFileSystem()->FindDirectory(W2A(PathOnCD));
//DEL  	ASSERT(pTargetRecord); // should never assert
//DEL  
//DEL  	if (pTargetRecord)
//DEL 	{
//DEL  		CFileRecord* pParent = pTargetRecord->GetParent();
//DEL  		pParent->RemoveSubItem(pTargetRecord);
//DEL  	}
//DEL 
//DEL 	return S_OK;
//DEL }

STDMETHODIMP CAudioRecordObj::ClearDirectoryStructure()
{
	m_pAudioDisc->Reset();

	return S_OK;
}

//DEL STDMETHODIMP CAudioRecordObj::BurnToISO(BSTR TargetISOFile)
//DEL {
//DEL 	USES_CONVERSION;
//DEL //	m_pDiscWriter->WriteDisc(m_pDataDisc, W2A(TargetISOFile));
//DEL 
//DEL 	return S_OK;
//DEL }

//DEL STDMETHODIMP CAudioRecordObj::get_DeviceDriveLetter(BSTR *pVal)
//DEL {
//DEL 	char szLetter[10] = {0, ':', '\\', 0};
//DEL 	szLetter[0] = m_pDiscWriter->GetDriveLetter();
//DEL 	
//DEL 	CComBSTR str(szLetter);
//DEL 	str.CopyTo(pVal);
//DEL 
//DEL 	return S_OK;
//DEL }

//DEL STDMETHODIMP CAudioRecordObj::get_RootFolder(IFileItem **pVal)
//DEL {
//DEL 	// ZU ERLEDIGEN: Implementierungscode hier hinzufügen
//DEL 
//DEL 	return S_OK;
//DEL }

//DEL STDMETHODIMP CAudioRecordObj::AddEmptyDirectory(BSTR Name, BSTR PathOnCD)
//DEL {
//DEL 	USES_CONVERSION;
//DEL 
//DEL 	CFileRecord* pTargetRecord = m_pDataDisc->GetFileSystem()->FindDirectory(W2A(PathOnCD));
//DEL  	ASSERT(pTargetRecord); // should never assert
//DEL  
//DEL  	if (pTargetRecord)
//DEL 		pTargetRecord->AddEmptyDirectory(W2A(Name));
//DEL 
//DEL 	return S_OK;
//DEL }

//DEL STDMETHODIMP CAudioRecordObj::Rename(BSTR PathOnCD, BSTR NewName)
//DEL {
//DEL 	USES_CONVERSION;
//DEL 	CFileRecord* pTargetRecord = m_pDataDisc->GetFileSystem()->FindDirectory(W2A(PathOnCD));
//DEL  	ASSERT(pTargetRecord); // should never assert
//DEL 	
//DEL 	if (pTargetRecord)
//DEL 		pTargetRecord->SetName(W2A(NewName));
//DEL 
//DEL 	return S_OK;
//DEL }

STDMETHODIMP CAudioRecordObj::AddAudioTrack(BSTR SourceFile, double * pdDuration)
{
	USES_CONVERSION;
	*pdDuration = m_pAudioDisc->AddAudioFile(W2A(SourceFile));

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::BurnAudioCD()
{
	m_pDiscWriter->WriteDisc(m_pAudioDisc);

	return S_OK;
}

//DEL STDMETHODIMP CAudioRecordObj::ListFilesInDataDirectory(BSTR PathOnCD)
//DEL {
//DEL 	USES_CONVERSION;
//DEL 	CFileRecord* pTargetRecord = m_pDataDisc->GetFileSystem()->FindDirectory(W2A(PathOnCD));
//DEL  	ASSERT(pTargetRecord); // should never assert
//DEL 	
//DEL 	if (pTargetRecord)
//DEL 	{
//DEL 		for (int i=0;i<pTargetRecord->GetSubItems()->GetSize();i++)
//DEL 		{
//DEL 			Fire_FileInDirectoryListed(CComBSTR(pTargetRecord->GetSubItems()->GetAt(i)->GetName()),
//DEL 									   CComBSTR(pTargetRecord->GetSubItems()->GetAt(i)->GetPathOnCD()),
//DEL 									   CComBSTR(pTargetRecord->GetSubItems()->GetAt(i)->GetFullpath()),
//DEL 									   pTargetRecord->GetSubItems()->GetAt(i)->GetFileRecordType() == CFileRecord::DIRECTORY_RECORD ?
//DEL 										VARIANT_TRUE : VARIANT_FALSE,
//DEL 										pTargetRecord->GetSubItems()->GetAt(i)->GetFileRecordType() == CFileRecord::DIRECTORY_RECORD ?
//DEL 										pTargetRecord->GetSubItems()->GetAt(i)->GetTotalSize() : pTargetRecord->GetSubItems()->GetAt(i)->GetFileSize());						   
//DEL 		}
//DEL 	}
//DEL 
//DEL 	return S_OK;
//DEL }

STDMETHODIMP CAudioRecordObj::AbortFileScan()
{
	// ZU ERLEDIGEN: Implementierungscode hier hinzufügen

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::ListAudioTracks()
{
	CTrackArray* pArray = m_pAudioDisc->GetTrackArray();

	for (int i=0;i<pArray->GetSize();i++)
	{
		Fire_AudioTrackListed(i, CComBSTR(pArray->GetAt(i)->strPath), pArray->GetAt(i)->dDuration);
	}

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::get_TotalAudioTrackDuration(double *pVal)
{
	*pVal = m_pAudioDisc->GetTotalDuration();

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::get_TotalFileSize(double *pVal)
{
	// ZU ERLEDIGEN: Implementierungscode hier hinzufügen

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::get_DiscCapacitySeconds(double *pVal)
{
	*pVal = m_pDiscWriter->GetDiscCapacitySecs();

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::get_CurTrack(long *pVal)
{
	*pVal = m_pDiscWriter->GetCurrentTrack();

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::get_CurLBA(long *pVal)
{
	*pVal = m_pDiscWriter->GetCurrentLBA();

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::get_FileBufferSize(long *pVal)
{
	long l = 0;
	m_pDiscWriter->ReadFileBufferInfo(l, *pVal);

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::get_FileBufferUsed(long *pVal)
{
	long l = 0;
	m_pDiscWriter->ReadFileBufferInfo(*pVal, l);

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::get_TimeElapsed(double *pVal)
{
	*pVal = m_pDiscWriter->GetTimeElapsed();

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::RemoveAudioTrack(long Index)
{
	CDiscAudio::CAudioTrack * pTrack = m_pAudioDisc->GetTrackArray()->GetAt(Index);
	delete pTrack;
	m_pAudioDisc->GetTrackArray()->RemoveAt(Index);

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::get_BurnProof(VARIANT_BOOL *pVal)
{
	*pVal = m_pDiscWriter->GetBurnProof() ? VARIANT_TRUE : VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::put_BurnProof(VARIANT_BOOL newVal)
{
	m_pDiscWriter->EnableBurnProof(newVal == VARIANT_TRUE);

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::MoveAudioTrack(long Index, long NewIndex)
{
	if (Index < 0 || NewIndex < 0 || 
		Index > m_pAudioDisc->GetTrackArray()->GetSize() - 1 ||
		NewIndex > m_pAudioDisc->GetTrackArray()->GetSize() - 1)
		return S_OK;

	CDiscAudio::CAudioTrack* pTrack = m_pAudioDisc->GetTrackArray()->GetAt(Index);
	
	if (NewIndex <= Index)
	{
		m_pAudioDisc->GetTrackArray()->InsertAt(NewIndex ? NewIndex : 0, pTrack);
		m_pAudioDisc->GetTrackArray()->RemoveAt(++Index);
	}
	else
	{
		m_pAudioDisc->GetTrackArray()->InsertAt(NewIndex + 1, pTrack);
		m_pAudioDisc->GetTrackArray()->RemoveAt(Index);
	}

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::get_DurationTime(double *pVal)
{
	*pVal = m_pDiscWriter->GetDurationTime();

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::get_ProgressTime(double *pVal)
{
	*pVal = m_pDiscWriter->GetProgressTime();

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::get_AudioPause(double *pVal)
{
	*pVal = m_pDiscWriter->GetAudioPause();

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::put_AudioPause(double newVal)
{
	m_pDiscWriter->SetAudioPause((long)newVal);

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::StartDiscErase(VARIANT_BOOL QuickErase)
{
	// ZU ERLEDIGEN: Implementierungscode hier hinzufügen

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::get_EraseProgress(long *pVal)
{
	// ZU ERLEDIGEN: Implementierungscode hier hinzufügen

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::get_CommMethod(EnumCommunication *pVal)
{
	*pVal = m_bASPI ? commASPI : commSPTI;

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::put_CommMethod(EnumCommunication newVal)
{
	if (m_pDiscWriter->IsInited())
	{
		// then we already inited the communication, and will have to
		// rescan everything now

		bool bNewUseAspi = newVal ==  commASPI;
		if (bNewUseAspi != m_bASPI)
		{
			m_bASPI = newVal == commASPI;

			// the we are changing the comm
			m_pDiscWriter->UnInit();
			m_pDiscWriter->Initialize(m_bASPI);
		}
	}
	else
		m_bASPI = newVal == commASPI;

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::get_PreferredCommMethod(EnumCommunication *pVal)
{
	OSVERSIONINFO osver;
	ZeroMemory( &osver, sizeof(osver) );
	osver.dwOSVersionInfoSize = sizeof(osver);
	GetVersionEx( &osver );
	
	if (osver.dwPlatformId == VER_PLATFORM_WIN32_NT)
	{
		*pVal = commSPTI;
	}
	else
		*pVal = commASPI;

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::get_WriteType(EnumWriteType *pVal)
{
	*pVal = m_pDiscWriter->GetWriteType();

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::put_WriteType(EnumWriteType newVal)
{
	m_pDiscWriter->SetWriteType(newVal);

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::get_AudioTrackDuration(long Index, double *pVal)
{
	*pVal = m_pAudioDisc->GetTrackArray()->GetAt(Index)->dDuration;

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::GetDriveInfo(BSTR *DriveName, BSTR *FirmwareVersion, long *BufferSize, BSTR *Date, BSTR *SerialNumber)
{
	SCSIDEVICE& device = m_pDiscWriter->GetCurrentDevice();
	
	CComBSTR strName = device.szID;
	strName.CopyTo(DriveName);

	*BufferSize = device.nBufferSize;
	
	CComBSTR strFirmware = device.szRev; //L"1.00.00";
	strFirmware.CopyTo(FirmwareVersion);

	char szDate[10] = {0};
	strncpy(szDate, device.szVendSpec, 2);
	strcat(szDate, "-");
	strncat(szDate, &device.szVendSpec[2], 2);
	strcat(szDate, "-");	
	strncat(szDate, &device.szVendSpec[4], 2);

	CComBSTR strDate = szDate;
	strDate.CopyTo(Date);

	char szSerial[20] = {0};
	strncpy(szSerial, &device.szVendSpec[9], 4);
	strcat(szSerial, " ");
	strncat(szSerial, &device.szVendSpec[13], 6);

	CComBSTR strSerial = szSerial;
	strSerial.CopyTo(SerialNumber);

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::ListAvailableReadSpeeds()
{
	long nCount = m_pDiscWriter->GetReadSpeedCount();
	for (int i=0;i<nCount;i++)
	{
		long nSpeed = m_pDiscWriter->GetReadSpeed(i);

		char szDesc[10] = {0};
		sprintf(szDesc, "%luX", nSpeed);
		
		Fire_ReadSpeedListed(nSpeed, CComBSTR(szDesc));
	}

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::get_ReadFeatureSupported(EnumFeature FeatureName, EnumFeatureSupport *pVal)
{
	SCSIDEVICE& device = m_pDiscWriter->GetCurrentDevice();

	bool bSupported = false;
	switch(FeatureName)
	{
	case featureCDR:
		if (device.bReadCDR) bSupported = true;
		break;
	case featureCDRW:
		if (device.bReadCDRW) bSupported = true;
		break;
	case featureDVDRAM:
		if (device.bReadDVDRAM) bSupported = true;
		break;
	case featureDVDROM:
		if (device.bReadDVDROM) bSupported = true;
		break;
	case featureDVDR:
		if (device.bReadDVDR) bSupported = true;
		break;
	default:
		*pVal = featureUnknown;
		return S_OK;
	}
	
	*pVal = bSupported ? featureSupported : featureNotSupported;

	return S_OK;
}

STDMETHODIMP CAudioRecordObj::get_WriteFeatureSupported(EnumFeature FeatureName, EnumFeatureSupport *pVal)
{
	SCSIDEVICE& device = m_pDiscWriter->GetCurrentDevice();

	bool bSupported = false;
	switch(FeatureName)
	{
	case featureCDR:
		if (device.bWriteCDR) bSupported = true;
		break;
	case featureCDRW:
		if (device.bWriteCDRW) bSupported = true;
		break;
	case featureDVDRAM:
		if (device.bWriteDVDRAM) bSupported = true;
		break;
	case featureDVDROM:
		bSupported = false;
		break;
	case featureDVDR:
		if (device.bWriteDVDR) bSupported = true;
		break;
	case featureBufferProtect:
		if (device.bJustlink) bSupported = true;
		break;
	case featureTAO:
	case featureDAO:
	case featureSAO:
	default:
		*pVal = featureUnknown;
		return S_OK;
	}
	
	*pVal = bSupported ? featureSupported : featureNotSupported;

	return S_OK;
}
