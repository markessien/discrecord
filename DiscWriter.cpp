// CDWriter.cpp: Implementierung der Klasse CDiscWriter.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#if defined(AUDIO_CD_ONLY)
#include "ObjAudio\AudioRecord.h"
#include "ObjAudio\AudioRecordObj.h"
#else
#include "ObjFull\DiscRecord.h"
#include "ObjFull\DiscRecordObj.h"
#include "DataCD\discparser.h"
#endif

#include <stdio.h>
#include "DiscWriter.h"
#include "disc.h"
#include <dbt.h>
#include <time.h>

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CDiscWriter::CDiscWriter(ICallback* pCallback) :						 
						 m_bTestMode(false),
						 m_pCallback(pCallback),
						 m_dDuration(0),
						 m_dProgress(0),
						 m_iCurrentDevice(0),
						 m_iDeviceCount(0),
						 m_bAbortWrite(false),
						 m_bInited(false),
						 m_bEjectWhenDone(true),
						 m_bBurnproof(true),
						 m_nCurTrack(0),
						 m_nCurLBA(0),
						 m_tStartTime(0),
						 m_nDrvBufLen(0),
						 m_nDrvBufBlank(0),
						 m_tEraseStart(0),
						 m_bInWrite(false),
						 m_discToWrite(NULL),
						 m_nAudioPause(2),
						 m_eWriteType(writeTAO),
						 m_bCloseSession(false),
						 m_nCopyDeviceIndex(0),
						 m_bAbortRead(false)
{
	
	
	CHelper::Trace("Starting application\n");
	
#ifndef AUDIO_CD_ONLY
	m_pDiscParser = new CDiscParser(this);
#endif

	memset(&m_arrSpeedsMultiple, 0, sizeof(long)*50);
	memset(&m_arrSpeedsKiloByte, 0, sizeof(long)*50);
	memset(m_szISOFile, 0, MAX_PATH);

	m_devicenull.bIsValid = FALSE;

	ChangeStatus("", statusNothing, statusMessage);
}

CDiscWriter::~CDiscWriter()
{
	DestroyCDRList();
	
#ifndef AUDIO_CD_ONLY
	delete m_pDiscParser;
#endif

	CHelper::Trace("Ending application\n");
}

BOOL CDiscWriter::NotifyFunc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, long pClass)
{
	CDiscWriter* pThis = (CDiscWriter*)pClass;
	_ASSERT(pThis);

	BOOL bResult = FALSE;
	switch(uMsg)
	{
	case WM_STATUSCHANGE:
		pThis->m_pCallback->Fire_StatusChange(CComBSTR(pThis->m_strStatus), pThis->m_status, pThis->m_statusType);
		break;
	case WM_COMPLETE:
		pThis->m_pCallback->Fire_Complete();
		break;
	case WM_TIMER:
		pThis->m_pCallback->Fire_DiscStatusChanged();
		KillTimer(hWnd, wParam);
		break;
	case WM_DEVICECHANGE:
		{
			PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)lParam;
//			char szMsg[80];
			switch(wParam)
			{
			case DBT_DEVICEARRIVAL: // See if a CD-ROM or DVD was inserted into a drive.
				{
					 if (lpdb -> dbch_devicetype == DBT_DEVTYP_VOLUME)
					 {
						PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;

						if (lpdbv -> dbcv_flags & DBTF_MEDIA)
						{
//							wsprintf(szMsg, "%c:", FirstDriveFromMask(lpdbv ->dbcv_unitmask));
							pThis->m_pCallback->Fire_DiscStatusChanged();
							SetTimer(hWnd, 1, 5000, 0);
					//		SetTimer(hWnd, 2, 6000, 0);
					//		SetTimer(hWnd, 3, 9000, 0);
						}
					 }
				}
				break;
			 case DBT_DEVICEREMOVECOMPLETE:
				 {
					// See if a CD-ROM was removed from a drive.
					if (lpdb -> dbch_devicetype == DBT_DEVTYP_VOLUME)
					{
					   PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;

					   if (lpdbv -> dbcv_flags & DBTF_MEDIA)
					   {
//						  wsprintf(szMsg, "%c:", FirstDriveFromMask(lpdbv ->dbcv_unitmask));
						  pThis->m_pCallback->Fire_DiscStatusChanged();
						  SetTimer(hWnd, 1, 3000, 0);
						  SetTimer(hWnd, 2, 6000, 0);
						  SetTimer(hWnd, 3, 9000, 0);
					   }
					}
				 }
				 break;
			} // switch 
		}
		break;

	}

	return bResult;
}

bool CDiscWriter::Initialize(bool bUseAspi)
{
	CHelper::Trace("CDiscWriter::Initialize\n");
		
	m_wndNotify.SetDrainFunction(NotifyFunc, (long) this);
			
	RECT rect;
	rect.left = 0; rect.top = 0; rect.right = 5; rect.bottom = 5;
	m_wndNotify.Create(NULL, rect, _T("NotifyWnd"), WS_POPUP);
	
	CHelper::Trace("CDiscWriter::Initialize. Window created. Bout to query InitComm on scsi\n");

	if (m_scsi.InitCommunication(&m_cdrList, bUseAspi) !=  0)
	{
		ChangeStatus("Initialisation failed. ASPI may not be installed", statusErrorNoASPI, statusError);
		return false;
	}

	m_bInited = true;
	return true;
}

bool CDiscWriter::RescanCDWriterDevices()
{
	/*
	if (!m_bInited)
		return false;
	
	_ASSERT(FALSE);

	DestroyCDRList();

	m_scsi.EndCommunication();
	//m_scsi.InitCommunication(&m_cdrList, true);
*/
	return true;
}

DWORD __stdcall CDiscWriter::WriteDiscThreadEntry(LPVOID lpvThreadParm)
{
	CDiscWriter* pThis = (CDiscWriter*)lpvThreadParm;
	pThis->WriteDisc();
	return 0;
}

DWORD __stdcall CDiscWriter::CopyDiscThreadEntry(LPVOID lpvThreadParm)
{
	CDiscWriter* pThis = (CDiscWriter*)lpvThreadParm;
	pThis->CopyDisc();
	return 0;
}

bool CDiscWriter::WriteDisc(CDisc* discToWrite)
{
	if (!m_bInited)
		return false;
	
	// There may be a problem with high speed recorders.
	// See mmc4, page 80

	CHelper::Trace("WriteDisc entered. Thread about to be started\n");
	
	m_discToWrite = discToWrite;
	m_bAbortWrite = false;
	m_dDuration = 0;
	m_dProgress = 0;
	
	DWORD dwThreadID = 0;
	CreateThread(NULL,                  // Security attributes
                 (DWORD) 0,             // Initial stack size
                 WriteDiscThreadEntry,     // Thread start address
                  (LPVOID) this,         // Thread parameter
                 (DWORD) 0,             // Creation flags
                 &dwThreadID);          // Thread identifier

	return true; // we always return true
}

double CDiscWriter::GetDuration()
{
	return m_dDuration;
}

double CDiscWriter::GetProgress()
{	
	//m_scsi.ReadBufferCapacity(GetCurrentDevice(), m_nDrvBufLen, m_nDrvBufBlank);
	return m_dProgress;
}

bool CDiscWriter::SetCurrentDeviceIndex(int iNewIndex)
{
	m_iCurrentDevice = iNewIndex;
	return true;
}

int CDiscWriter::GetCurrentDeviceIndex()
{
	return m_iCurrentDevice;
}

bool CDiscWriter::AbortWrite()
{
	if (!m_bInited)
		return false;
	
	m_bAbortWrite = true;

	ChangeStatus("Aborting write..", statusUserAbort, statusMessage);
	
	if (m_discToWrite)
		m_discToWrite->Finished();

	while (m_bInWrite)
	{
		MSG msg;
		while (::PeekMessage(&msg, m_wndNotify.m_hWnd, (UINT) 0,(UINT) 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		Sleep(100);
	}
	
	m_bAbortWrite = false;

	return true;
}

SCSIDEVICE & CDiscWriter::GetCurrentDevice()
{
	if (!m_bInited)
		return m_devicenull;

	if (m_iCurrentDevice >= 0 && m_iCurrentDevice < m_cdrList.GetSize())
	{
		return (*m_cdrList[m_iCurrentDevice]);
	}
	
	_ASSERT(FALSE);
	return m_devicenull;
}

void CDiscWriter::EjectDevice(bool bEject)
{
	if (!m_bInited)
		return;

	m_scsi.EjectDevice(GetCurrentDevice(), bEject);
}

bool CDiscWriter::GetBufferInfo(long &nSize, long &nFree)
{
	if (!m_bInited)
		return false;
	
	nSize = m_nDrvBufLen;
	nFree = m_nDrvBufBlank;

	int iError = m_scsi.ReadBufferCapacity(GetCurrentDevice(), nSize, nFree);
	if (iError)
		return false;

	return true;
}

long CDiscWriter::GetDiscCapacity()
{
	if (!m_bInited)
		return 0;
	
	long nMin, nSec;
	long lResult = 0;
	int iError = m_scsi.ReadDiscCapacity(GetCurrentDevice(), lResult, nMin, nSec);
	if (iError != 0)
		lResult = 0;

	return lResult;
}

EnumDiscState CDiscWriter::GetDiscState()
{	
	if (!m_bInited)
		return discEmpty;

	long nDiscState = 0;

	int iError = m_scsi.ReadDiscInformation(GetCurrentDevice(), 0, &nDiscState, 0, 0);
	if (iError)
	{
		return discNotAvailable;
	}
	
	switch (nDiscState)
	{
	case InfoEmpty:
		return discEmpty;
	case InfoOpen:
		return discOpen;
	case InfoClosed:
		return discClosed;
	default:
		_ASSERT(FALSE);
	}

	return discNotAvailable;
}

EnumDiscType CDiscWriter::GetDiscType()
{
	if (!m_bInited)
		return discCD;

	long nDiscType = 0;

	int iError = m_scsi.ReadDiscInformation(GetCurrentDevice(), &nDiscType, 0, 0, 0);
	if (iError)
	{
		return discCD;
	}
	
	switch (nDiscType)
	{
	case InfoCD:
		return discCD;
	case InfoCDR:
		return discCDR;
	case InfoCDRW:
		return discCDRW;
	case InfoCDI:
		return discCDI;
	case InfoCDXA:
		return discCDXA;
	case InfoUnknown:
	default:
		return discCD;
	}

	return discCD;
}

long CDiscWriter::GetCurrentWriteSpeed()
{
	if (!m_bInited)
		return 0;

	m_scsi.UpdateDeviceInfo(GetCurrentDevice(), false, false);
	return GetCurrentDevice().nCurWriteSpeed / 176;
}

long CDiscWriter::GetCurrentReadSpeed()
{
	if (!m_bInited)
		return 0;

	m_scsi.UpdateDeviceInfo(GetCurrentDevice(), false, false);
	return GetCurrentDevice().nCurReadSpeed / 176;
}

long CDiscWriter::GetWriteSpeedCount()
{
	CHelper::Trace("CDiscWriter::GetWriteSpeedCount()");
	m_scsi.ScanWriteSpeeds(GetCurrentDevice());

	return GetCurrentDevice().arrSupportedWriteSpeeds.GetSize();
}

long CDiscWriter::GetWriteSpeed(int iIndex)
{
	// GetSpeedCount to get the valid speed count
	if (iIndex < 0 ||  iIndex > GetCurrentDevice().arrSupportedWriteSpeeds.GetSize() - 1)
		return 0;

	return GetCurrentDevice().arrSupportedWriteSpeeds.GetAt(iIndex);
}

long CDiscWriter::GetReadSpeedCount()
{
	m_scsi.UpdateDeviceInfo(GetCurrentDevice(), false, true);

	return GetCurrentDevice().arrSupportedReadSpeeds.GetSize();
}

long CDiscWriter::GetReadSpeed(int iIndex)
{
	// GetSpeedCount to get the valid speed count

	return GetCurrentDevice().arrSupportedReadSpeeds.GetAt(iIndex);
}


bool CDiscWriter::SetCurrentWriteSpeed(long nFactor)
{
	if (!m_bInited)
		return false;

	long nWriteSpeed = nFactor * X1;
	for (int i=0;i<GetCurrentDevice().arrSupportedWriteSpeeds.GetSize();i++)
	{
		if (GetCurrentDevice().arrSupportedWriteSpeeds.GetAt(i) == nWriteSpeed)
		{
			nWriteSpeed = GetCurrentDevice().arrSupportedWriteSpeedsKB.GetAt(i);
			CHelper::Trace("Write speed real kb value found=%lu\n", nWriteSpeed);
			ASSERT(nWriteSpeed);
			break;
		}
	}
	
	CHelper::Trace("Setting write speed=%lu\n", nWriteSpeed);
	int iError = m_scsi.SetSpeed(GetCurrentDevice(), NULL, &nWriteSpeed);
	if (iError != 0)
	{
		CHelper::Trace("Write speed set failed\n");
		return false;
	}

	m_scsi.UpdateDeviceSpeeds(GetCurrentDevice());
	CHelper::Trace("Current Write Speed=%lu\n", GetCurrentDevice().nCurWriteSpeed);

	return true;
}

bool CDiscWriter::SetCurrentReadSpeed(long nFactor)
{
	if (!m_bInited)
		return false;

	long nReadSpeed = nFactor * X1;
	int iError = m_scsi.SetSpeed(GetCurrentDevice(), &nReadSpeed, NULL);

	if (iError != 0)
		return false;

	return true;
}

long CDiscWriter::GetDeviceCount()
{
	return m_cdrList.GetSize();
}

SCSIDEVICE* CDiscWriter::GetDevice(int iIndex)
{
	if (iIndex >= 0 && iIndex < m_cdrList.GetSize())
	{
		return (m_cdrList[iIndex]);
	}

	return &m_devicenull;
}

bool CDiscWriter::GetTestMode()
{
	return m_bTestMode;
}

void CDiscWriter::SetTestMode(bool bTestMode)
{
	m_bTestMode = bTestMode;
}

LPCTSTR CDiscWriter::GetCurrentStatus()
{
	return m_strStatus;
}

void CDiscWriter::ChangeStatus(char *pstrNewStatus, Status status, StatusType statusType)
{
	m_strStatus = pstrNewStatus;
	m_status = status;
	m_statusType = statusType;
	
	CHelper::Trace("CDiscWriter::ChangeStatus - NewStatus=%s\n", pstrNewStatus);

	if (m_wndNotify.IsWindow())
		m_wndNotify.SendMessage(WM_STATUSCHANGE);
}

long CDiscWriter::GetDiscSize()
{
	long nSize = 0;
	m_scsi.ReadDiscSize(GetCurrentDevice(), nSize);
	return nSize;
}

bool CDiscWriter::GetEjectWhenDone()
{
	return m_bEjectWhenDone;
}

void CDiscWriter::SetEjectWhenDone(bool bEject)
{
	m_bEjectWhenDone = bEject;
}

char CDiscWriter::GetDriveLetter()
{
	/*
	int iCount = 0;
	char cDrive = 'D';

	// guess the drive letter
	for (char driveLetter = 'C'; driveLetter <= 'Z'; driveLetter++ )
	{
		CString driveRootDir = CString(driveLetter) + ":\\";
		if (DRIVE_CDROM != GetDriveType(driveRootDir.GetBuffer(1))) 
			continue;
		/*
		SetErrorMode(SEM_FAILCRITICALERRORS);
		
		DWORD dwSerialNumber = 0;
		if (!::GetVolumeInformation ((LPCTSTR) driveRootDir, NULL, 0,
									&dwSerialNumber, NULL, NULL, NULL, 0)) 
		{
		}
		*/
		/*
		if (iCount == 0)
			cDrive = driveLetter;

		iCount++;
	}
	
	if (iCount)
		return cDrive;

	return 'D';
	*/

	return GetCurrentDevice().cLetter;
}

// Write Disc: Writes the disc
// Write pmp = mmc 6.1.1
// mode sense = spc 7.1
// see mmc o.8 on writing multiple tracks

void CDiscWriter::WriteDisc()
{
	m_bInWrite = true;

	ChangeStatus("Preparing parameters for Burn", statusInitializing, statusMessage);
	
	m_tStartTime = time(0);

	// Get the duration for the progress notifications. This can be anything
	// such as total size, or total length in minutes. It is not essential, only
	// for the progress bar
 	m_dDuration = m_discToWrite->GetDuration();
		
	// Set the write type. If the write is SAO, the disc is going
	// to generate the entire sao info like lead-in, etc. Else, it will
	// simply give us the data
	m_discToWrite->SetWriteType(m_eWriteType);

	// check if the cd inserted has enough space for the items we are about to burn
	double dSize = m_discToWrite->GetDuration();
	
	long nLength, nMin, nSec;
	m_scsi.ReadDiscCapacity(GetCurrentDevice(), nLength, nMin, nSec);

	if ((long)dSize> nLength || m_bAbortWrite)
	{
		// this cd will not contain everything
		if (!m_bAbortWrite)
			ChangeStatus("Not enough disk space to burn the selection", statusErrorDiscSpace, statusError);
		
		m_bInWrite = false;
		m_wndNotify.SendMessage(WM_COMPLETE);
		return;
	}
	
	// check if the cd is writeable
	long nDiscType = discCDR, nDiscStatus = InfoEmpty;
	int iError = m_scsi.ReadDiscInformation(GetCurrentDevice(), &nDiscType, &nDiscStatus, 0, 0);

	if ((nDiscStatus != InfoEmpty && nDiscStatus != InfoOpen) || iError != 0)
	{
		ChangeStatus("The inserted disc is not writeable", statusErrorNotWriteable, statusError);
		
		m_bInWrite = false;
		m_wndNotify.SendMessage(WM_COMPLETE);
		return;
	}
	// do power calibration
	ChangeStatus("Performing power calibration. Please wait...", statusSendingOPC, statusMessage);
	m_scsi.PerformOPC(GetCurrentDevice());

	// Allocate our buffer for read and write. We make a buffer that is 16 blocks
	// long. The block length is different between audio and data cds.
	long blockCount = 16;
	BYTE* pBuffer = new BYTE[m_discToWrite->GetBlockSize() * blockCount];
	memset(pBuffer, 0, m_discToWrite->GetBlockSize() * blockCount);
	
	// Write the data
	if (m_eWriteType == writeTAO)
		WriteTAO(blockCount, pBuffer);
	else
		WriteSAO(blockCount, pBuffer);

	// eject device
	if (m_bEjectWhenDone)
 	{
 		ChangeStatus("Ejecting Device", statusEject, statusMessage);
 		m_scsi.EjectDevice(GetCurrentDevice(), true);
 	}

 	// set complete status
 	ChangeStatus("Burn Complete", statusComplete, statusMessage);
	
 	// reset variables
	m_dProgress = m_dDuration;
 	delete [] pBuffer;
 	pBuffer = NULL;
 	m_bAbortWrite = false;
	m_tStartTime = 0;

	// Call Finished, so that the disc can delete anything
	// it might have allocated
	m_discToWrite->Finished();

 	CHelper::Trace("Goodbye\n");
 	
	m_bInWrite = false;

	m_wndNotify.SendMessage(WM_COMPLETE);
}

void CDiscWriter::EnableBurnProof(bool bEnable)
{
	m_bBurnproof = bEnable;
}

void CDiscWriter::SetModePageParameters(BYTE pModePage[], int nTrack)
{
	// mmc 6.1.1 write params mode page

	pModePage[0] &= 0x7f; // clear PS flag
	pModePage[2] &= 0xe0;

	// Change for session at once mode
	// 0x2 is session, 0x1 is track
	if (m_eWriteType == writeTAO)
		pModePage[2] |= 0x01; // write type: track-at-once
	else if (m_eWriteType == writeSAO)
		pModePage[2] |= 0x02; // write type: session-at-once

	// Multi-session: No B0 pointer, next session not allowed, 
	// audio track, digital copy allowed, = 100 0010
	// This flag will have to be changed when we support
	// multisession

	if (m_discToWrite->GetTrackType(nTrack) == 0)
		if (m_bCloseSession)
			pModePage[3] = 0x46; // data, close session
		else
			pModePage[3] = 0xC6; // data, allow next session
	else
		pModePage[3] = 0x42; // audio
	
	// raw mode -> 2352 bytes per block
	pModePage[4] = m_discToWrite->GetMode(); 

	if (m_bTestMode) 
		pModePage[2] |= 1 << 4; // test write?

	if (m_bBurnproof) 
		pModePage[2] |= 0x40;
	else
		pModePage[2] &= ~0x40;

	//audio pause. 150blocks = 2sec. mmc 6.1.1
	long nPauseBlocks = m_nAudioPause * 75;
	pModePage[14] = (BYTE)(nPauseBlocks >> 8);
	pModePage[15] = (BYTE)nPauseBlocks;
}

long CDiscWriter::GetDiscCapacitySecs()
{
	if (!m_bInited)
		return 0;
	
	long nSize, nMin, nSec;
	int iError = m_scsi.ReadDiscCapacity(GetCurrentDevice(), nSize, nMin, nSec);
	if (iError != 0)
		nSize = 0;
	
	nSize = (nMin * 60) + nSec;
	return nSize;
}

long CDiscWriter::GetCurrentTrack()
{
	return m_nCurTrack + 1;
}

long CDiscWriter::GetCurrentLBA()
{
	return m_nCurLBA;
}

int CDiscWriter::ReadFileBufferInfo(long &nValid, long &nSize)
{
	if (m_discToWrite)
		m_discToWrite->ReadBufferInfo(nValid, nSize);

	return 0;
}	

double CDiscWriter::GetTimeElapsed()
{
	if (m_tStartTime == 0.0f)
		return 0;

	return (time(0) - m_tStartTime);
}

bool CDiscWriter::GetBurnProof()
{
	return m_bBurnproof;
}

double CDiscWriter::GetProgressTime()
{
	if (m_discToWrite)
		return m_discToWrite->GetProgressTime();
	return 0;
}

double CDiscWriter::GetDurationTime()
{
	if (m_discToWrite)
		return m_discToWrite->GetDurationTime();
	return 0;
}

int CDiscWriter::StartDiscErase(bool bQuickErase)
{
	m_tEraseStart = time(0);
	return m_scsi.StartEraseDisc(GetCurrentDevice(), bQuickErase);
}

bool CDiscWriter::CheckEraseComplete()
{
	if (m_scsi.TestUnitReady(GetCurrentDevice(), true) == 0)
	{
		return true;
	}
	return false;
}

long CDiscWriter::GetAudioPause()
{
	return m_nAudioPause;
}

void CDiscWriter::SetAudioPause(long nPause)
{
	m_nAudioPause = nPause;
}

void CDiscWriter::DestroyCDRList()
{
	while (m_cdrList.GetSize())
	{
		SCSIDEVICE * pd = m_cdrList.GetAt(0);
		if (pd->hDrive)
			CloseHandle(pd->hDrive);

		delete pd;
		m_cdrList.RemoveAt(0);
	}
}

void CDiscWriter::SetWriteType(EnumWriteType eWriteType)
{
	m_eWriteType = eWriteType;
}

EnumWriteType CDiscWriter::GetWriteType()
{
	return m_eWriteType;
}

int CDiscWriter::WriteSAO(long blockCount, BYTE* pBuffer)
{
	CHelper::Trace("CDiscWriter::WriteSAO entry\n");

	ChangeStatus("Initializing session", statusSessionInit, statusMessage);
	
	if (m_discToWrite == NULL)
		return -1;

	if (m_bAbortWrite || m_discToWrite->SetAndPrimeSession(1, 0) == false)
	{
		ChangeStatus("Session could not be primed for burn", statusErrorSessionData, statusWarning);
		return -1;
	}

	m_nCurLBA = 0;
	
	CHelper::Trace("CDiscWriter::WriteSAO - about to send write mode page\n");

	// send the mode page, with sao mode set
	if (SendWriteModePage() == false)
	{
		CHelper::Trace("CDiscWriter::WriteSAO - send write mode page failed. Aborting\n");
		return -1;
	}
	
	int iErr = m_scsi.TestUnitReady(GetCurrentDevice(), true);
	ASSERT(iErr == 0);

	CHelper::Trace("CDiscWriter::WriteSAO - about to get and send cue sheet\n");

	// create cue sheet, and send it
	BYTE* pCue = m_discToWrite->GetCueSheet(m_nAudioPause);
	int iError = m_scsi.SendCueSheet(GetCurrentDevice(), pCue,  m_discToWrite->GetCueSheetLen());
	if (iError != 0)
	{
		CHelper::Trace("CDiscWriter::WriteSAO - cue sheet was not accepted\n");

		ChangeStatus("The cue sheet was not accepted by the device. Check that session at once mode is supported by your cd burner", statusErrorCueSheet, statusError);
		return -1;
	}
	
	iErr = m_scsi.TestUnitReady(GetCurrentDevice(), true);
	ASSERT(iErr == 0);

	CHelper::Trace("CDiscWriter::WriteSAO - cue sheet accepted\n");

	if (m_bAbortWrite)
		return -1;

	// call get next address. We won't use it tho
	long nNextWriteAddr = GetNextWriteAddress();
	if (nNextWriteAddr == -1)
	{
		// we could not get or estimate the next position we are 
		// to write at. So we fail.
		ChangeStatus("The write address for the next track was not returned by the device", statusErrorAddr, statusError);
		return -1;
	}

	CHelper::Trace("CDiscWriter::WriteSAO - nwa=%d\n", nNextWriteAddr);
	CHelper::Trace("CDiscWriter::WriteSAO - Checking if unit ready\n");
	
	m_nCurLBA = -150;

	ChangeStatus("Writing CD", statusWritingData, statusMessage);

//	long n;
//	while( m_scsi.ReadBufferCapacity(GetCurrentDevice(), n, n) != 0);

	blockCount = 16;
	memset(pBuffer, 0, blockCount * m_discToWrite->GetBlockSize());
	long lRead = m_discToWrite->GetBlockSize() * blockCount; // blockCount blocks

	for (m_nCurTrack=0;m_nCurTrack<m_discToWrite->GetTrackCount();m_nCurTrack++)
	{
		CHelper::Trace("CDiscWriter::WriteSAO - writing pre-gap for track %lu\n", m_nCurTrack);

		// write pre-gap
		if (WriteByte(150, m_nCurLBA, 0, TRUE) != 0)
		{
			CHelper::Trace("CDiscWriter::WriteSAO - writing pre-gap for track %lu failed!\n", m_nCurTrack);
			return -1;
		}
		
		CHelper::Trace("CDiscWriter::WriteSAO - about to prime track for burn\n");

		// open file
		if (m_discToWrite->SetAndPrimeTrack(m_nCurTrack) == false)
		{
			CHelper::Trace("CDiscWriter::WriteSAO - track prime failed. Skipping to next track\n");

			ChangeStatus("Track could not be primed for burn", statusErrorTrackData, statusWarning);
			continue;
		}
		
		CHelper::Trace("CDiscWriter::WriteSAO - starting to read data\n");

		// read the data
		while (m_discToWrite->Read(pBuffer, lRead) == true)
		{
			_ASSERT(lRead);

			m_dProgress = m_discToWrite->GetProgress();
			
			if (m_bAbortWrite)
				break;

			// Make sure that if the data we receive does not fill the last block, 
			// that the rest is 0s, and not garbage,w hich might cause clicks with
			// audio tracks.

			if (lRead < (m_discToWrite->GetBlockSize() * blockCount))
			{
				ZeroAlignBuffer(pBuffer, blockCount, lRead);
			}
					
			int iRetry = 40;
			int iError = m_scsi.WriteBlock(GetCurrentDevice(), pBuffer, blockCount, lRead, m_nCurLBA);
	 		while (iError != 0 && iRetry > 0)
	 		{
				Sleep(500);
				CHelper::Trace("Write failed. Retrying. iError=%d, iRetry=%d\n", iError, iRetry);
				iError = m_scsi.WriteBlock(GetCurrentDevice(), pBuffer, blockCount, lRead, m_nCurLBA);
				iRetry--;
	 		}
					
			if (iError != 0)
			{
				// we retried but there is really something wrong
				CHelper::Trace("\n\nThe write really could not succeed!\n\n");
				if (iError == -16)
					ChangeStatus("Medium speed error", statusErrorIO, statusError);
				else
					ChangeStatus("Write error", statusErrorIO, statusError);

	 			return -1;
			}

			CHelper::Trace("Write went OK. LBA=%d\n", m_nCurLBA);

			m_nCurLBA += blockCount;
			
			blockCount = 16;
			lRead = m_discToWrite->GetBlockSize() * blockCount;

		} // while

		blockCount = 16;
		lRead = m_discToWrite->GetBlockSize() * blockCount;	
	}
	
	m_nCurTrack--;

	CHelper::Trace("CDiscWriter::WriteSAO - data read complete. About to snyc cache\n");

	ChangeStatus("Closing Session, Writing lead-in and out. Please wait!",
				statusClosingSession, statusMessage);

	// write lead out ??? This is officially a hack.
	// if error crops up, it will simply fail
	WriteByte(150, m_nCurLBA, 0, FALSE);
	
	m_scsi.SynchronizeCache(GetCurrentDevice());
	
	return 0;
}

int CDiscWriter::WriteTAO(long blockCount, BYTE* pBuffer)
{
	// We loop through the sessions that the disc says we
	// should write, and write each of them. Audio is 1 session
	// data is one session. If we are continueing a multi-session
	// disc, the source disc wil still contain only one session.
	// however, this session will not start at lba 0. Mixed mode data
	// and audio could contain multiple sessions, for example.

	ASSERT(m_discToWrite);
	if (m_discToWrite == NULL)
		return -1;

	for (int n=0;n<m_discToWrite->GetSessionCount();n++)
	{
		// We call this function, to make sure the disc allocates and
		// creates all object neccesary for this session. ISO9660 will
		// do the first pass, and buffer an initial 10mb when we call this
		// function for a session. Audio will not do anything, since it does
		// the stuff in the corresponing function for tracks
		
		ChangeStatus("Initializing session", statusSessionInit, statusMessage);
		
		if (SendWriteModePage() == false)
			break;

		CHelper::Trace("Getting write address\n");

		// Get the session write address, so we can pass to the iso
		// generation discs
		long nNextWriteAddr = GetNextWriteAddress();
		if (nNextWriteAddr == -1)
		{
			// we could not get or estimate the next position we are 
			// to write at. So we fail.
			ChangeStatus("The write address for the next track was not returned by the device", statusErrorAddr, statusError);
			break;
		}
		
		m_discToWrite->SetDiscParser(m_pDiscParser);

		if (m_bAbortWrite || m_discToWrite->SetAndPrimeSession(n, nNextWriteAddr) == false)
		{
			ChangeStatus("Session could not be primed for burn", statusErrorSessionData, statusWarning);
			continue;
		}
		
		// We loop through the tracks. Not that the track count
		// returns the number of tracks in the set session, and no
		// the total number of tracks.
		for (m_nCurTrack=0;m_nCurTrack<m_discToWrite->GetTrackCount();m_nCurTrack++)
		{
			// We prime the track. for audio cds, this function will
			// buffer 2mb of the uncomressed audio. It does not do anything
			// for data cds.

			ChangeStatus("Initializing track", statusTrackInit, statusMessage);

			CHelper::Trace("About to call SetAndPrimeTrack\n");

			if (m_discToWrite->SetAndPrimeTrack(m_nCurTrack) == false)
			{
				ChangeStatus("Track could not be primed for burn", statusErrorTrackData, statusError);
				continue;
			}			

			if (m_bAbortWrite)
			{
				CHelper::Trace("m_bAbortWrite = true. This is immediately after SetAndPrimeTrack\n");
				break;
			}
			
			CHelper::Trace("Getting write address\n");


			nNextWriteAddr = GetNextWriteAddress();
			if (nNextWriteAddr == -1)
			{
				// we could not get or estimate the next position we are 
				// to write at. So we fail.
				ChangeStatus("The write address for the next track was not returned by the device", statusErrorAddr, statusError);
				break;
			}
			
			ChangeStatus("Writing CD", statusWritingData, statusMessage);
			
			blockCount = 16; // zero align
			m_nCurLBA = nNextWriteAddr;

	 		long lRead = m_discToWrite->GetBlockSize() * blockCount; // blockCount blocks
			while (m_discToWrite->Read(pBuffer, lRead) == true)
			{
				m_dProgress = m_discToWrite->GetProgress();
				
				if (m_bAbortWrite)
				{
					CHelper::Trace("Write aborted\n");
					break;
				}

				// Make sure that if the data we receive does not fill the last block, 
				// that the rest is 0s, and not garbage,w hich might cause clicks with
				// audio tracks.

				if (lRead < (m_discToWrite->GetBlockSize() * blockCount))
				{
					ZeroAlignBuffer(pBuffer, blockCount, lRead);
				}
				
				int iRetry = 30;
				int iError = m_scsi.WriteBlock(GetCurrentDevice(), pBuffer, blockCount, lRead, m_nCurLBA);
	 			while (iError != 0 && iRetry > 0)
	 			{
					CHelper::Trace("Write failed. Retrying. iError=%d, iRetry=%d\n", iError, iRetry);
					iError = m_scsi.WriteBlock(GetCurrentDevice(), pBuffer, blockCount, lRead, m_nCurLBA);
					iRetry--;

					if (iRetry > 10)
						Sleep(1000);
					else if (iRetry  > 5)
						Sleep(100);
					else
						Sleep(10);
	 			}
				
				if (iError != 0)
				{
					// we retried but there is really something wrong
					CHelper::Trace("\n\nThe write really could not succeed!\n\n");
					if (iError == -16)
						ChangeStatus("Medium speed error", statusErrorIO, statusError);
					else if (iError == -15)
						ChangeStatus("Device Busy error", statusErrorIO, statusError);
					else 
						ChangeStatus("Write error", statusErrorIO, statusError);
	 				break;
				}

				CHelper::Trace("Write went OK. LBA=%d. Read=%d\n", m_nCurLBA, lRead);

				m_nCurLBA += blockCount;
			} // while

			ChangeStatus("Closing Track", statusClosingTrack, statusMessage);
	 		
			m_scsi.SynchronizeCache(GetCurrentDevice());
	 		//m_scsi.CloseTrackOrSession(GetCurrentDevice(), false, m_nCurTrack+1);
			m_scsi.CloseTrackOrSession(GetCurrentDevice(), false, 0xFF);
	 
		} // for track
		
		m_nCurTrack--;

		if (m_bAbortWrite)
			break;
		
		// Close session
		ChangeStatus("Closing Session, Writing lead-in and out. Please wait!",
					 statusClosingSession, statusMessage);

		m_scsi.CloseTrackOrSession(GetCurrentDevice(), true, 0);
		
		int iSecs = 60 * 5;
		// allow session close for 5 minutes. spti bug
		while (m_scsi.TestUnitReady(GetCurrentDevice(), true) != 0 && iSecs > 0)
		{
			CHelper::Trace("Waiting for session to close. Loop=%lu", iSecs);

			Sleep(1000);
			iSecs--;
		}
	} // for session

	return 0;
}

bool CDiscWriter::SendWriteModePage()
{
	// Allocate the buffers for the mode page
	BYTE modePage[0x38] = {0};
	BYTE modePageHeader[8] = {0};
	BYTE blockDesc[8] = {0};
	
	// Get, modify and send back the mode page for the write.
	if (m_scsi.GetModePage(GetCurrentDevice(), 5, modePage, modePageHeader, blockDesc, 0x38) == 0)
 	{
 		CHelper::Trace("CDiscWriter::SendWriteModePage - Get mode page went OK! Setting flags\n");

		SetModePageParameters(modePage, m_nCurTrack);

 		if (m_scsi.SendModePage(GetCurrentDevice(), modePage, modePageHeader, 0) != 0)
 		{
			CHelper::Trace("CDiscWriter::SendWriteModePage - m_scsi.SendModePage failed.\n");

			if (m_bBurnproof == false)
			{
				CHelper::Trace("CDiscWriter::SendWriteModePage - m_scsi.SendModePage failed with burnproof off.\n");

				ChangeStatus("Error: Mode page not accepted", statusErrorModePage, statusError);
 				return false;
			}
			
			CHelper::Trace("CDiscWriter::SendWriteModePage - m_scsi.SendModePage failed with burnproof on. Testing without burnproof\n");

			// we check if it works better without burn proof enabled
			m_bBurnproof = false;
			return SendWriteModePage();
 		}
 		
 		CHelper::Trace("Modified mode page with write params was accepted\n");
 	}
 	else
 	{
		CHelper::Trace("CDiscWriter::SendWriteModePage - Get mode page FAILED!\n");
 		ChangeStatus("Error: Mode page could not be retrieved", statusErrorModePage, statusError);
		return false;
 	}

	return true;
}

int CDiscWriter::GetNextWriteAddress()
{
	long nNextWriteAddr = 0;
	//int iError = m_scsi.ReadTrackInfo(GetCurrentDevice(), m_nCurTrack + 1, 0, 0, 0, &nNextWriteAddr);	
	int iError = m_scsi.ReadTrackInfo(GetCurrentDevice(), 0xFF, 0, 0, 0, &nNextWriteAddr, 0);	
	ASSERT(iError == 0);

	if (iError != 0) 
	{
		nNextWriteAddr = -1;

		// We cannot get the track info
		if (m_nCurLBA == 0)
			nNextWriteAddr = 0;
		else
		{
			nNextWriteAddr = -1;
			int iRetry = 10;
			// retry
			//while(iError = m_scsi.ReadTrackInfo(GetCurrentDevice(), m_nCurTrack + 1, 0, 0, 0, &nNextWriteAddr) != 0 && iRetry) {
			while(iError = m_scsi.ReadTrackInfo(GetCurrentDevice(), 0xFF, 0, 0, 0, &nNextWriteAddr, 0) != 0 && iRetry) {
				Sleep(500); iRetry--;
			}
		}
	}

	return nNextWriteAddr;
}

bool CDiscWriter::ZeroAlignBuffer(BYTE *pBuffer, long & blockCount, long &lRead)
{
	// this function is only used if the data we read is less than the ammount
	// we need.

	long nBufferLen = m_discToWrite->GetBlockSize() * blockCount;
	long nLeftOver = nBufferLen - lRead;

	// We 0 the buffer
	memset(&pBuffer[lRead], 0, nLeftOver);

	// we need to round the figure to the lowest possible block

	if (lRead % nBufferLen == 0)
	{
		// no problem. Block aligned
		blockCount = lRead / m_discToWrite->GetBlockSize();
	}
	else
	{
		// not block aligned
		blockCount = lRead / m_discToWrite->GetBlockSize();
		blockCount += 1;
		lRead = blockCount * m_discToWrite->GetBlockSize();
	}

	return true;
}

int CDiscWriter::WriteByte(int nBlockCount, int nStartLBA, BYTE cToWrite, BOOL bRetry)
{
	CHelper::Trace("CDiscWriter::WriteByte - Start=%d\n", nStartLBA);

	m_nCurLBA = nStartLBA;

	// Create a buffer that is exactly the size we want to write, and
	// memset it to the byte we require
	BYTE * pBuffer = new BYTE[m_discToWrite->GetBlockSize()*16];
	memset(pBuffer, cToWrite, m_discToWrite->GetBlockSize()*16);

	// try to write 16 blocks at a time
	int iError;
	int iRetry = 0;
	for (int k=0;k<nBlockCount;k+=16)
	{
		int nBlocks = k + 16 > nBlockCount ? (nBlockCount - k) - 1 : 16;
		
		CHelper::Trace("CDiscWriter::WriteByte - StartBlock=%lu. ToWrite=%lu\n", k, nBlocks);

		iRetry = 0;
		do 
		{
			if (iRetry)	{
				CHelper::Trace("CDiscWriter::WriteByte - failed. Looping. Times=%lu\n", iRetry);
				Sleep(1000);

				if (iRetry > 120 || bRetry == FALSE) break;
			}
			
			iError = m_scsi.WriteBlock(GetCurrentDevice(), pBuffer, 
									   nBlocks, 
									   m_discToWrite->GetBlockSize() * nBlocks, 
									   m_nCurLBA);

			iRetry++;
/*
			if (m_scsi.TestUnitReady(GetCurrentDevice(), false) != 0)
			{
				CHelper::Trace("CDiscWriter::WriteByte - TEST UNIT READY failed! Lopping till unit ready for write\n");
				
				int iTestLoop = 0;
				while (m_scsi.TestUnitReady(GetCurrentDevice(), false) != 0)
				{
					CHelper::Trace("CDiscWriter::WriteByte - TEST UNIT READY loop=%lu\n", iTestLoop);

					Sleep(1000);
					iTestLoop++;
					if (iTestLoop > 60 || bRetry == FALSE) break;
				}
			}
			*/

		}
		while (iError == SCSINotReady || iError == SCSIMedium || iError == -16);
		
		if (iError)
		{
			delete [] pBuffer;
			return iError;
		}

		m_nCurLBA += nBlocks;
	}
	
	delete [] pBuffer;
	return 0;
}

bool CDiscWriter::IsInited()
{
	return m_bInited;
}

void CDiscWriter::UnInit()
{
	if (m_wndNotify.IsWindow())
		m_wndNotify.DestroyWindow();

	DestroyCDRList();
	m_scsi.EndCommunication();
}

bool CDiscWriter::CopyDisc(long nSourceDeviceIndex, char *pstrTargetFile)
{
	if (!m_bInited)
		return false;
	
	CHelper::Trace("CopyDisc entered. Thread about to be started\n");

	strcpy(m_szISOFile, pstrTargetFile);

	m_bAbortRead = false;
	m_dDuration = 0;
	m_dProgress = 0;
	m_nCopyDeviceIndex = nSourceDeviceIndex;

	DWORD dwThreadID = 0;
	CreateThread(NULL,                  // Security attributes
                 (DWORD) 0,             // Initial stack size
                 CopyDiscThreadEntry,     // Thread start address
                  (LPVOID) this,         // Thread parameter
                 (DWORD) 0,             // Creation flags
                 &dwThreadID);          // Thread identifier

	return true;
}

#define MODE1_BLOCK_LEN 2048

void CDiscWriter::CopyDisc()
{
	// Each session has got to be copied to an individual file,
	// and then each session burnt one after the other as a disc

	long nTrackCount = 0;
	m_scsi.ReadTOC(*GetDevice(m_nCopyDeviceIndex), 0, &nTrackCount);

	if (nTrackCount <= 0)
	{
		ChangeStatus("There were no tracks on this disc that could be copied", statusErrorReadDisc, statusError);
		m_wndNotify.SendMessage(WM_COMPLETE);
		return;
	}

	HANDLE hFile = INVALID_HANDLE_VALUE;

	for (int i=0;i<nTrackCount;i++)
	{
		if (m_bAbortRead)
			break;

		char szTrack[MAX_PATH] = {0};
		BaseStringToIndexedString(m_szISOFile, szTrack, i+1);

		hFile = CreateFile(szTrack, GENERIC_WRITE|GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE, 0, CREATE_ALWAYS, 0, 0);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			ChangeStatus("The output file for the disc copy could not be created", statusErrorReadDisc, statusError);
			m_wndNotify.SendMessage(WM_COMPLETE);
			return;
		}
		
		CHelper::Trace("Copying to %s\n", szTrack);
		
		long nTrackStart = 0;
		long nTotalBlocks = 0;
		if (m_scsi.ReadTrackInfo(*GetDevice(m_nCopyDeviceIndex), i+1, 0, 0, &nTrackStart, 0, &nTotalBlocks) != 0)
			continue;

		InitDiscRead(1);
		
		int nBlocksToRead = 16;
		m_dDuration = nTotalBlocks;

		BYTE* pBuffer = new BYTE[2048*16];
		for (int nPos=nTrackStart;nPos<(nTrackStart + nTotalBlocks);nPos+=16)
		{
			if (nPos + 16 > (nTrackStart + nTotalBlocks))
				nBlocksToRead = (nTrackStart + nTotalBlocks) - nPos;

			ASSERT(nBlocksToRead <= 16);
			ASSERT(nBlocksToRead > 0);

			if (ReadFromDisc(pBuffer, nPos, nBlocksToRead, false) == false)
			{
				//ChangeStatus("Disc Read error", statusErrorReadDisc, statusError);
				//break;
				//continue;
				ASSERT(FALSE);
				CHelper::Trace("Could not read from disc!\n");
				break;
			}

			DWORD dwWritten = 0;
			WriteFile(hFile, pBuffer, 2048*nBlocksToRead, &dwWritten, 0);
			ASSERT(dwWritten == 2048*nBlocksToRead);
		
			m_dProgress = nPos - nTrackStart;
			
			if (m_bAbortRead)
				break;

			CHelper::Trace("Data Read. LBA=%lu, Length=%lu\n", nPos, nBlocksToRead);
		}

		CloseHandle(hFile);

		delete [] pBuffer;
		CHelper::Trace("Track Read complete. Handles closed\n");
		
	}

	CHelper::Trace("Copy complete\n");

	m_wndNotify.SendMessage(WM_COMPLETE);
}

bool CDiscWriter::ReadFromDisc(BYTE* pBuffer, long nStartLBA, long nBlockLen, bool bFromWriter)
{
	// this can be changed, but till then, we stick with reading 16 blocks

	int nBytesToRead = nBlockLen * 2048;
	int iError = m_scsi.ReadBlock(bFromWriter ? GetCurrentDevice() : *GetDevice(this->m_nCopyDeviceIndex),
								  pBuffer, nBlockLen, nBytesToRead, nStartLBA);
	if (iError != 0)
	{
		// we might want to retry a few times, y'know
		return false;
	}

	if (nBlockLen > 16)
	{
		return ReadFromDisc(&pBuffer[16], nStartLBA + 16, nBlockLen - 16, bFromWriter);
	}

	return true;
}

bool CDiscWriter::InitDiscRead(long nMode)
{
	// this command returns an error on some devices. I don't know why.
	// Don't check for error, else it will fail occasionally.

	int iError = 0;
	if (nMode == 1)
		iError = m_scsi.SetBlockSize(*GetDevice(this->m_nCopyDeviceIndex), MODE1_BLOCK_LEN, 0, true);
	else
		iError = m_scsi.SetBlockSize(GetCurrentDevice(), MODE1_BLOCK_LEN, 0, true);
	
	/* And this??? Don't know, it works with the above. See akrip
	if (iError != 0)
		iError = m_scsi.SetBlockSize(GetCurrentDevice(), MODE1_BLOCK_LEN, 0, false);
	*/

	if (iError)
		return false;

	return true;
}

long CDiscWriter::GetLastSessionLBA()
{
	long nStartLBA = 0;
	int iError = m_scsi.ReadTOC(GetCurrentDevice(), &nStartLBA, 0);

	if (iError)
		return 0;

	return nStartLBA;
}

CDiscParser* CDiscWriter::GetDiscParser()
{
	return m_pDiscParser;
}

void CDiscWriter::BaseStringToIndexedString(char *pstrSource, char *pstrTarget, int nIndex)
{
	strcpy(pstrTarget, pstrSource);
	
	char szNumber[5];
	sprintf(szNumber, "%lu", nIndex);

	char * pstrDot = strrchr(pstrTarget, '.');
	if (pstrDot)
	{
		strcpy(pstrDot, szNumber);
		strcat(pstrDot, ".tao");
	}
	else
	{
		strcat(pstrTarget, szNumber);
		strcat(pstrTarget, ".tao");
	}
}

bool CDiscWriter::GetCloseSession()
{
	return m_bCloseSession;
}

void CDiscWriter::SetCloseSession(bool bValue)
{
	m_bCloseSession = bValue;
}

void CDiscWriter::AbortRead()
{
	m_bAbortRead = true;
}

long CDiscWriter::GetWriteSpeedKB(int iIndex)
{
	if (iIndex < 0 ||  iIndex > GetCurrentDevice().arrSupportedWriteSpeedsKB.GetSize() - 1)
		return 0;

	return GetCurrentDevice().arrSupportedWriteSpeedsKB.GetAt(iIndex);
}
