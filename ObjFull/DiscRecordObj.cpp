// DiscRecordObj.cpp : Implementierung von CDiscRecordObj

#include "stdafx.h"
#include "DiscRecord.h"
#include "DiscRecordObj.h"
#include "discwriter.h"
#include "stdio.h"
#include "disc.h"
#include "..\datacd\disciso9660.h"
#include "..\audiocd\discaudio.h"
#include "..\datacd\discimage.h"
#include "..\datacd\discparser.h"
#include "FileItem.h"
#include "audioitem.h"

/////////////////////////////////////////////////////////////////////////////
// CDiscRecordObj

CDiscRecordObj::CDiscRecordObj() : m_hIcon( LoadIcon(_Module.m_hInstResource, (LPCTSTR) IDI_DISCRECORD) )
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(-1); // For memory leaks. Change to allocation number to break at that position.
							// Don't forget to reset back to -1 to make life easier for other developers.
	char szPath[MAX_PATH];
	GetTempPath(MAX_PATH, szPath);
	m_strTempDirectory = szPath;

	CoInitialize(0);

	m_pDiscWriter = new CDiscWriter((ICallback*)this);
	m_pAudioDisc = new CDiscAudio;
	m_pDataDisc = new CDiscISO9660;
	m_pImageDisc = new CDiscImage;
	
	m_pDataRoot = NULL;

	HRESULT hr = CoCreateInstance(CLSID_FileItem, 
								  NULL, CLSCTX_INPROC_SERVER,
								  IID_IFileItem, 
								  (void**)&m_pDataRoot);
	ASSERT(!FAILED(hr));
	ASSERT(m_pDataRoot);
	
	CFileRecord* pRecord = new CFileRecord(0);
	m_pDataRoot->SetFileRecord(pRecord);
	m_pDataDisc->SetFileRecord(pRecord);

	m_pAudioRoot = NULL;
	hr = CoCreateInstance(CLSID_AudioItem, 
						  NULL, CLSCTX_INPROC_SERVER,
						  IID_IAudioItem, 
						  (void**)&m_pAudioRoot);
	ASSERT(!FAILED(hr));
	ASSERT(m_pAudioRoot);

	m_pAudioRoot->SetAudioDisc(m_pAudioDisc);

	m_bASPI = true;
}
	
void CDiscRecordObj::FinalRelease()
{
	delete m_pDiscWriter;
	delete m_pAudioDisc;
	delete m_pDataDisc;
	delete m_pImageDisc;

	m_pDataRoot->Release();
	m_pDataRoot = NULL;

	m_pAudioRoot->Release();
	m_pAudioRoot = NULL;

	CoUninitialize();
}

STDMETHODIMP CDiscRecordObj::ListDevices(VARIANT_BOOL OnlyWriteable)
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
			Fire_DeviceListed(strID, strAdapter, VARIANT_TRUE);
		}
		else
			if (OnlyWriteable == VARIANT_FALSE)
				Fire_DeviceListed(strID, strAdapter, VARIANT_FALSE);	
	}

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::Initialize()
{
	m_pDiscWriter->Initialize(m_bASPI);

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::FileSelectDialog(long HwndParent, VARIANT_BOOL IsSaveDialog, BSTR FilterMask, BSTR DefaultExt, long nFilterIndex, BSTR *pResult)
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

STDMETHODIMP CDiscRecordObj::get_ProgressMax(double *pVal)
{
	*pVal = m_pDiscWriter->GetDuration();

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::get_ProgressCur(double *pVal)
{
	*pVal = m_pDiscWriter->GetProgress();

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::get_SelectedWriterDeviceIndex(long *pVal)
{
	int iCurWriterIndex = 0;

	int iCount = m_pDiscWriter->GetDeviceCount();
	for (int i= 0; i< iCount;i++)
	{
		if (m_pDiscWriter->GetDevice(i)->bWriteCDR || 
			m_pDiscWriter->GetDevice(i)->bWriteCDRW)
		{
			iCurWriterIndex++;
		}

		if (m_pDiscWriter->GetCurrentDeviceIndex() == i)
		{
			*pVal = iCurWriterIndex;
			return S_OK;
		}
	}

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::put_SelectedWriterDeviceIndex(long newVal)
{
	int iCurWriterIndex = 0;

	int iCount = m_pDiscWriter->GetDeviceCount();
	for (int i= 0; i< iCount;i++)
	{
		if (m_pDiscWriter->GetDevice(i)->bWriteCDR || 
			m_pDiscWriter->GetDevice(i)->bWriteCDRW)
		{
			if (iCurWriterIndex == newVal)
			{
				m_pDiscWriter->SetCurrentDeviceIndex(i);
				return S_OK;
			}

			iCurWriterIndex++;
		}
	}

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::EjectDevice(VARIANT_BOOL bEject)
{
	m_pDiscWriter->EjectDevice(bEject == VARIANT_TRUE);

	return S_OK;
}


STDMETHODIMP CDiscRecordObj::AbortBurn()
{
	m_pDiscWriter->AbortWrite();

	return S_OK;
}


STDMETHODIMP CDiscRecordObj::get_CDLabel(BSTR *pVal)
{
	m_pDataDisc->GetLabel();

	CComBSTR str = m_pDataDisc->GetLabel();
	str.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::put_CDLabel(BSTR newVal)
{
	USES_CONVERSION;
	m_pDataDisc->SetLabel(W2A(newVal));	

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::BurnFromISO(BSTR InputISOPath)
{
	SYSTEMTIME t;
	GetSystemTime(&t);
	if (t.wYear > 2004)
		return S_OK;

	USES_CONVERSION;
	m_pImageDisc->SetSourceFile(W2A(InputISOPath));
	m_pDiscWriter->WriteDisc(m_pImageDisc);

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::BurnDataCD()
{
	SYSTEMTIME t;
	GetSystemTime(&t);
	if (t.wYear > 2004)
		return S_OK;

	USES_CONVERSION;
	m_pDiscWriter->WriteDisc(m_pDataDisc);

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::get_DiscType(EnumDiscType *pVal)
{
	*pVal = m_pDiscWriter->GetDiscType();

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::get_DiscState(EnumDiscState *pVal)
{
	*pVal = m_pDiscWriter->GetDiscState();

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::get_DiscCapacityBytes(long *pVal)
{
	*pVal = m_pDiscWriter->GetDiscCapacity();

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::get_CurrentWriteSpeed(long *pVal)
{
	*pVal = m_pDiscWriter->GetCurrentWriteSpeed();

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::put_CurrentWriteSpeed(long newVal)
{
	m_pDiscWriter->SetCurrentWriteSpeed(newVal);

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::ListAvailableWriteSpeeds()
{
	long nCount = m_pDiscWriter->GetWriteSpeedCount();

	CHelper::Trace("Write Speed Count=%lu\n", nCount);

	for (int i=0;i<nCount;i++)
	{
		long nSpeed = m_pDiscWriter->GetWriteSpeed(i);
		long nSpeedKB = m_pDiscWriter->GetWriteSpeedKB(i);

		char szDesc[10] = {0};
		sprintf(szDesc, "%luX (%luKB/sec)", nSpeed, nSpeedKB);
		
		Fire_WriteSpeedListed(nSpeed, CComBSTR(szDesc));
	}

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::QueryDriveBuffer(long *Used, long *Length)
{
	*Used = 0;
	*Length = 0;

	m_pDiscWriter->GetBufferInfo(*Length, *Used);
	*Used = *Length - *Used;

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::get_TestMode(VARIANT_BOOL *pVal)
{
	*pVal = m_pDiscWriter->GetTestMode() ? VARIANT_TRUE : VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::put_TestMode(VARIANT_BOOL newVal)
{
	m_pDiscWriter->SetTestMode(newVal == VARIANT_TRUE);

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::get_DiscSize(long *pVal)
{
	*pVal = m_pDiscWriter->GetDiscSize();

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::get_EjectWhenDone(VARIANT_BOOL *pVal)
{
	*pVal = m_pDiscWriter->GetEjectWhenDone() ? VARIANT_TRUE : VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::put_EjectWhenDone(VARIANT_BOOL newVal)
{
	m_pDiscWriter->SetEjectWhenDone(newVal == VARIANT_TRUE);

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::ClearFiles()
{
	m_pDataDisc->Reset();
	m_pAudioDisc->Reset();

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::CopyCDToFixedDrive(long DeviceIndex, BSTR TargetFile)
{
	USES_CONVERSION;
	m_pDiscWriter->CopyDisc(DeviceIndex, W2A(TargetFile));

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::get_SelectedWriterDeviceDriveLetter(BSTR *pVal)
{
	char szLetter[10] = {0, ':', '\\', 0};
	szLetter[0] = m_pDiscWriter->GetDriveLetter();
	
	CComBSTR str(szLetter);
	str.CopyTo(pVal);

	return S_OK;
}


STDMETHODIMP CDiscRecordObj::BurnAudioCD()
{
	SYSTEMTIME t;
	GetSystemTime(&t);
	if (t.wYear > 2004)
		return S_OK;

	m_pDiscWriter->WriteDisc(m_pAudioDisc);

	return S_OK;
}



STDMETHODIMP CDiscRecordObj::get_DiscCapacitySeconds(double *pVal)
{
	*pVal = m_pDiscWriter->GetDiscCapacitySecs();

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::get_CurrentTrack(long *pVal)
{
	*pVal = m_pDiscWriter->GetCurrentTrack();

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::get_CurrentLBA(long *pVal)
{
	*pVal = m_pDiscWriter->GetCurrentLBA();

	return S_OK;
}


STDMETHODIMP CDiscRecordObj::get_TimeElapsed(double *pVal)
{
	*pVal = m_pDiscWriter->GetTimeElapsed();

	return S_OK;
}


STDMETHODIMP CDiscRecordObj::get_BurnProof(VARIANT_BOOL *pVal)
{
	*pVal = m_pDiscWriter->GetBurnProof() ? VARIANT_TRUE : VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::put_BurnProof(VARIANT_BOOL newVal)
{
	m_pDiscWriter->EnableBurnProof(newVal == VARIANT_TRUE);

	return S_OK;
}


STDMETHODIMP CDiscRecordObj::get_ProgressMaxSeconds(double *pVal)
{
	*pVal = m_pDiscWriter->GetDurationTime();

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::get_ProgressCurSeconds(double *pVal)
{
	*pVal = m_pDiscWriter->GetProgressTime();

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::get_PauseBetweenTracks(double *pVal)
{
	*pVal = m_pDiscWriter->GetAudioPause();

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::put_PauseBetweenTracks(double newVal)
{
	m_pDiscWriter->SetAudioPause(newVal);

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::StartDiscErase(VARIANT_BOOL QuickErase)
{
	m_pDiscWriter->StartDiscErase(QuickErase == VARIANT_TRUE);

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::get_CommunicationMethod(EnumCommunication *pVal)
{
	*pVal = m_bASPI ? commASPI : commSPTI;

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::put_CommunicationMethod(EnumCommunication newVal)
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

STDMETHODIMP CDiscRecordObj::get_PreferredCommunicationMethod(EnumCommunication *pVal)
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

STDMETHODIMP CDiscRecordObj::get_WriteType(EnumWriteType *pVal)
{
	*pVal = m_pDiscWriter->GetWriteType();

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::put_WriteType(EnumWriteType newVal)
{
	m_pDiscWriter->SetWriteType(newVal);

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::QueryDriveInfo(BSTR *DriveName, BSTR *FirmwareVersion, long *BufferSize, BSTR *Date, BSTR *SerialNumber)
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

STDMETHODIMP CDiscRecordObj::ListAvailableReadSpeeds()
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

STDMETHODIMP CDiscRecordObj::get_ReadFeatureSupported(EnumFeature FeatureName, EnumFeatureSupport *pVal)
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

STDMETHODIMP CDiscRecordObj::get_WriteFeatureSupported(EnumFeature FeatureName, EnumFeatureSupport *pVal)
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

STDMETHODIMP CDiscRecordObj::get_DataDisc(IFileItem **pVal)
{
	m_pDataRoot->AddRef();
	*pVal = m_pDataRoot;

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::QueryFileBuffer(long *Used, long *Length)
{
	m_pDiscWriter->ReadFileBufferInfo(*Used, *Length);
	
	return S_OK;
}

STDMETHODIMP CDiscRecordObj::get_AudioDisc(IAudioItem **pVal)
{
	*pVal = m_pAudioRoot;
	m_pAudioRoot->AddRef();

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::get_Erasing(VARIANT_BOOL *pVal)
{
	*pVal = m_pDiscWriter->CheckEraseComplete() ? VARIANT_FALSE : VARIANT_TRUE;

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::get_TempDirectory(BSTR *pVal)
{
	m_strTempDirectory.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::put_TempDirectory(BSTR newVal)
{
	m_strTempDirectory = newVal;

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::AbortCopy()
{
	m_pDiscWriter->AbortRead();

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::get_CurrentReadSpeed(long *pVal)
{
	*pVal = m_pDiscWriter->GetCurrentReadSpeed();

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::put_CurrentReadSpeed(long newVal)
{
	m_pDiscWriter->SetCurrentReadSpeed(newVal);

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::DoNothing()
{
	MessageBox("This function is for debuggin purposes only! ANYTHING can happen when you click OK!");

	m_pDiscWriter->GetDiscParser()->ReadVolumeDescriptors(true);
	m_pDiscWriter->GetDiscParser()->LoadDirectoryStructure();

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::get_LeaveSessionOpen(VARIANT_BOOL *pVal)
{
	*pVal = m_pDiscWriter->GetCloseSession() ? VARIANT_FALSE : VARIANT_TRUE;

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::put_LeaveSessionOpen(VARIANT_BOOL newVal)
{
	m_pDiscWriter->SetCloseSession(newVal == VARIANT_FALSE);

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::get_DriveCount(long *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::get_DriveName(long Index, BSTR *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::get_WriteSpeedCount(long *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::get_WriteSpeed(long Index, long *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::OpenDevice(long Index)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::put_LicenseKey(BSTR newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::get_FadeBetweenTracks(long *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CDiscRecordObj::put_FadeBetweenTracks(long newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}
