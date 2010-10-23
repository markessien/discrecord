// SCSI.cpp: Implementierung der Klasse CSCSI.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SCSI.h"
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CSCSI::CSCSI() : m_bUseASPI(true)
{
}

CSCSI::~CSCSI()
{

}

int CSCSI::ExecSCSICommand(SCSIDEVICE & device, BYTE cdblen, BYTE * pcdbbyte, DWORD dwWait, BYTE* pBuf, int nBufLen, int nDirection)
{
	// check if the target device is valid
	if (device.bIsValid == false)
		return SCSINoAdapter;

	// declare the structure to be passed to the interface
	SRB_ExecSCSICmd s;
	memset( &s, 0, sizeof( s ) ); // set it to 0
	
	// copy the byte buffer into the space in the structure reserved
	// for the command byte buffer
	memcpy(s.CDBByte, pcdbbyte, cdblen);

	// create an event we can use to wait for the completion of the command
	HANDLE heventSRB;
	heventSRB = CreateEvent( NULL, TRUE, FALSE, NULL );
 
	// populate the structure
	s.SRB_Cmd        = SC_EXEC_SCSI_CMD; // we want an execute request
	s.SRB_HaId       = device.ha; // drive id
	s.SRB_Target     = device.tgt; // drive  id
	s.SRB_Lun        = device.lun; // drive id

	// flags. We specify if we are receiving or sending a command
	// to the device over the nDirection parameter. The SRB_EVENT_NOTIFY
	// flag tells the interface how we want to wait for the responce, which
	// in this case is over the event we declared above
	s.SRB_Flags      = nDirection | SRB_EVENT_NOTIFY; 
	s.SRB_SenseLen   = SENSE_LEN; // the length of our error sense buffer
	s.SRB_BufLen     = nBufLen; // the command buffer length. Optional
	s.SRB_BufPointer = pBuf; // the buffer for input or output
	s.SRB_CDBLen     = cdblen; // the length of the command buffer. 6, 10, 12
	s.SRB_PostProc   = (LPVOID)heventSRB; // event handle

	ResetEvent( heventSRB );

	// send the command using the specified interface
	DWORD dwStatus;
	if (m_bUseASPI)
		dwStatus = m_aspi.SendCommand( (LPSRB)&s );
	else
		dwStatus = m_spti.ExecCommand(device.hDrive, &s, dwWait );

	// wait for the command to complete if our return code indicates that
	// our execution is not complete
	if ( dwStatus == SS_PENDING )
	{
		// Wait forever, because close session can take long
		WaitForSingleObject( heventSRB, dwWait ); 
	}
	
	CloseHandle( heventSRB );
	
	// we test for error
	if ( s.SRB_Status != SS_COMP )
	{
		// Error. We return the error code. 0 = noerror. Use TranslateError to get
		// the test
		return ScsiIoError(s.SRB_Status, s.SRB_HaStat, s.SRB_TargStat, s.SenseArea);
	}

	return 0;
}


int CSCSI::ScsiIoError(int aspi_status, int adapter_status, int target_status, unsigned char* sense)
{
	int i;
	switch ( aspi_status )  
	{
	case 0x82:
		i = SCSINoDevice;
		break;
	case 0x80:
		i = SCSIAspiInval;
		break;
	case 0x81:
		i = SCSINoAdapter;
		break;
	case 0x02:
		i = SCSIAbort;
		break;
	case 0x04:
		/*
		* Ok, this means scsi-io-error, so we see if
		* we can find more details about the error.
		*/
		i = SCSIIOErr;
		if ( adapter_status )
		{
			switch ( adapter_status )  
			{
			case 0x11:
				i = SCSISelTimeout;
				CHelper::Trace("IOError: SCSISelTimeout\n");
			break;
			case 0x12:
				i = SCSIDataOverrun;
				CHelper::Trace("IOError: SCSIDataOverrun\n");
			break;
			case 0x13:
				i = SCSIBusFree;
				CHelper::Trace("IOError: SCSIBusFree\n");
			break;
			case 0x14:
				i = SCSIBusFail;
				CHelper::Trace("IOError: SCSIBusFail\n");
			break;
			}
		} 
		else 
			switch ( target_status )
			{
			case 0x08:                         
				i = SCSITargetBusy;
				CHelper::Trace("IOError: SCSITargetBusy\n");
				break;
			case 0x18:
				i = SCSIReservation;
				CHelper::Trace("IOError: SCSIReservation\n");
				break;
			case 0x02:
				/* 
				 * Allright, the target has send
				 * sense data to the sense-data allocation
				 * area at the end of the srb.
			 */
				if ( sense != ( unsigned char *) 0 )
				{
					switch ( sense[2] & 0x0f )  
					{
					case 0x00:  /* This means "no sense", but we check for End of Medium */
						if ( sense[2] & 0x40 ) i = SCSIEndOfMedium;
						CHelper::Trace("IOError: SCSIEndOfMedium\n");
						break;
					case 0x01:
						i = SCSINoError;/* this would be pretty stupid to report, but anyway */
					break;
					case 0x02:
						i = SCSINotReady;
						CHelper::Trace("IOError: SCSINotReady\n");
					break;
					case 0x03:
						i = SCSIMedium;
						CHelper::Trace("IOError: SCSIMedium\n");
					break;
					case 0x04:
						i = SCSIHardware;
						CHelper::Trace("IOError: SCSIHardware\n");
					break;
					case 0x05:
						i = SCSIIllegalReq;
						CHelper::Trace("IOError: SCSIIllegalReq\n");
					break;
					case 0x06:
						i = SCSIUnitAttention;
						CHelper::Trace("IOError: SCSIUnitAttention\n");
					break;
					case 0x07:
						i = SCSIDataProtect;
						CHelper::Trace("IOError: SCSIDataProtect\n");
					break;
					case 0x08:
						i = SCSIBlankCheck;
						CHelper::Trace("IOError: SCSIBlankCheck\n");
					break;
					case 0x0b:
						i = SCSITargetAbort;
						CHelper::Trace("IOError: SCSITargetAbort\n");
					break;
					case 0x0d:
						i = SCSIVolOverflow;
					CHelper::Trace("IOError: SCSIVolOverflow\n");
					break;
					}
				}
			  break;
			}
			break;
  }

  return(i);
}

void CSCSI::TranslateError(int iError, char *pszBuffer)
{
	switch (iError)
	{
	case SCSINoError:
		strcpy(pszBuffer, "No Error");
		break;
	case SCSINoAspi:
		strcpy(pszBuffer, "No Aspi Manager Installed");
		break;
	case SCSIBusy:          
		strcpy(pszBuffer, "Aspi Module is busy (this should never occur)");
		break;
	case SCSIAspiErr:        /* Undefined Aspi error */
		strcpy(pszBuffer, "Undefined Aspi error");
		break;
	case SCSINoMem:          /* Can't allocate memory */
		strcpy(pszBuffer, "Can't allocate memory");
		break;
	case SCSINoDevice:       /* The device is not installed */
		strcpy(pszBuffer, "The device is not installed");
		break;
	case SCSIAspiInval:      /* Invalid ASPI request */
		strcpy(pszBuffer, "Invalid ASPI request");
		break;
	case SCSINoAdapter:      /* Invalid Host Adapter Number */
		strcpy(pszBuffer, "No Error");
		break;
	case SCSIAbort:          /* ASPI request aborted by Host */
		strcpy(pszBuffer, "ASPI request aborted by Host");
		break;
	case SCSISelTimeout:     /* Selection Timeout */
		strcpy(pszBuffer, "Selection Timeout");
		break;
	case SCSIDataOverrun:   /* Data over-run/under-run */
		strcpy(pszBuffer, "Data over-run/under-run");
		break;
	case SCSIBusFree:       /* Unexpected Bus Free */
		strcpy(pszBuffer, "Unexpected Bus Free");
		break;
	case SCSIBusFail:       /* Target bus phase sequence failure */
		strcpy(pszBuffer, "Target bus phase sequence failure");
		break;

	case SCSITargetBusy:    /* The specified Target/LUN is busy */
		strcpy(pszBuffer, "The specified Target/LUN is busy");
		break;

	case SCSIReservation:   /* Reservation conflict */
		strcpy(pszBuffer, "Reservation conflict");
		break;

	case SCSINotReady :      /* lun cannot be accessed */
		strcpy(pszBuffer, "Not Ready. LUN cannot be accessed");
		break;

	case SCSIMedium:        /* Medium Error */
		strcpy(pszBuffer, "Medium Error");
		break;

	case SCSIHardware :      /* Non recoverable hardware error */
		strcpy(pszBuffer, "Non recoverable hardware error");
		break;

	case SCSIIllegalReq:    /* Illegal Request */
		strcpy(pszBuffer, "Illegal Request");
		break;

	case SCSIUnitAttention: /* Unit Attention */
		strcpy(pszBuffer, "Unit Attention");
		break;

	case SCSIDataProtect:   /* The Block is protected */
		strcpy(pszBuffer, "No Error");
		break;

	case SCSIBlankCheck:    /* Encounterd non blank data */
		strcpy(pszBuffer, " Encounterd non blank data");
		break;

	case SCSITargetAbort:   /* The Target Aborted the command */
		strcpy(pszBuffer, "The Target Aborted the command");
		break;

	case SCSIVolOverflow:   /* Volume overflow */
		strcpy(pszBuffer, "Volume overflow");
		break;

	case SCSIMiscompare:    /* Source and data did nor match */
		strcpy(pszBuffer, "Source and data did nor match");
		break;

	case SCSIIOErr:         /* An IO Error of unknown type */
		strcpy(pszBuffer, "Unknown IO Error");
		break;

	case SCSILockLMem:      /* Can not lock local memory */
		strcpy(pszBuffer, " Can not lock local memory");
		break;

	case SCSILockGMem :      /* Can not lock global memory */
		strcpy(pszBuffer, "Can not lock global memory");
		break;

	case SCSIFatal:      /* Fatal Error - unemploy the programmer :-) */
		strcpy(pszBuffer, "Fatal Error");
		break;

	case SCSINoChannel :     /* The logical channel is not initialized */
		strcpy(pszBuffer, "The logical channel is not initialized");
		break;

	case SCSINotActive :     /* The logical channel is not active */
		strcpy(pszBuffer, "The logical channel is not active");
		break;

	case SCSIChannelOverflow : /* Logical Channel overflow */
		strcpy(pszBuffer, "Logical Channel overflow");
		break;

	case SCSIStreamerInUse : /* streamer is already configured for a channel */
		strcpy(pszBuffer, "Streamer is already configured for a channel");
		break;

	case SCSIBlockLimit :    /* Illegal blocksize for a streamer */
		strcpy(pszBuffer, "Illegal blocksize for a streamer");
		break;

	case SCSIOffset :        /* Illegal offset allowed for this operation */
		strcpy(pszBuffer, "Illegal offset allowed for this operation");
		break;

	case SCSIPosition :      /* Illegal position for this operarion */
		strcpy(pszBuffer, "Illegal position for this operarion");
		break;

	case SCSIBlockLen :      /* Illegal block length for this operation */
		strcpy(pszBuffer, "Illegal block length for this operation");
		break;

	case SCSIEndOfMedium :   /* End of Medium detected, not really an error */
		strcpy(pszBuffer, "End of Medium detected");
		break;
	}

	CHelper::Trace("Translate Error called. Error Number=%lu, Error Msg=%s", iError, pszBuffer);
}

int CSCSI::InitCommunication(CArray<SCSIDEVICE*, SCSIDEVICE*>* arrCDR, bool bUseASPI)
{
	// Call this to load ASPI or SPTI
	CHelper::LogTimeStamp(false);
	CHelper::Trace("\n");
	CHelper::LogTimeStamp(true);

	CHelper::Trace("CSCSI::InitCommunication Entry. Use ASPI=%lu.\n", bUseASPI);
	
	m_bUseASPI = bUseASPI;
//	m_bUseASPI = true;

	if (m_bUseASPI)
	{
		CHelper::Trace("Loading ASPI\n");

		if (m_aspi.LoadASPI() != 0)
		{
			CHelper::Trace("\n\nATTENTION! LoadASPI FAILED!\n\n");
			return SCSINoAspi;
		}
		
		int iASPIDeviceCount = m_aspi.GetSupportInfo();

		SRB_HAInquiry haInquiry;
 		memset( &haInquiry, 0, sizeof(SRB_HAInquiry) ); 
 		
 		haInquiry.SRB_Cmd = SC_HA_INQUIRY;
 		for (int i=0; i<iASPIDeviceCount; i++)
 		{
 			haInquiry.SRB_HaId = i;
 			m_aspi.SendCommand( (LPSRB)&haInquiry );
 
 			if ( haInquiry.SRB_Status != SS_COMP )
 			{
 				CHelper::Trace("ASPI enquiry failed. i=%lu\n", i);
 				continue;
 			}
 			
 			SRB_GDEVBlock devBlock;
 
 			int maxTgt = (int)haInquiry.HA_Unique[3];
 			
 			if ( maxTgt == 0 ) maxTgt = 8;
 
 			for( int j = 0; j < maxTgt; j++ )
 			{
 				for ( int k = 0; k < 8; k++ )
 				{
 					memset( &devBlock, 0, sizeof( devBlock ) );
 					devBlock.SRB_Cmd   = SC_GET_DEV_TYPE;
 					devBlock.SRB_HaId  = i;
 					devBlock.SRB_Target = j;
 					devBlock.SRB_Lun   = k;
 					
 					m_aspi.SendCommand( (LPSRB)&devBlock );
 					
 					if( devBlock.SRB_DeviceType == DTYPE_CDROM )
 					{
 						CHelper::Trace("nDeviceType Device detected. i=%lu, j=%lu, k=%lu\n", i, j, k);
						
						SCSIDEVICE* pDevice = new SCSIDEVICE;
						
						pDevice->bIsValid = TRUE;
 						pDevice->ha = i;
 						pDevice->tgt = j;
 						pDevice->lun = k;
						pDevice->cLetter = '0';
						pDevice->hDrive = NULL;

 						//strncpy(pDevice->szAdapter, (char*)&haInquiry.HA_Identifier[0], 63);
						strcpy(pDevice->szAdapter, "");

						ReadDeviceName(*pDevice);
						CHelper::Trace("Device detected=%s", pDevice->szID);

						UpdateDeviceInfo(*pDevice, true, true);
						
						CHelper::Trace("UpdateDeviceInfo ok. adding to array\n");

						//if (pDevice->bWriteCDR || pDevice->bWriteCDRW)
							arrCDR->Add(pDevice);
						//else
						//	delete pDevice;

						CHelper::Trace("Array add ok\n");
 					}
 				} // for k 
 			} // for j
 		} // for i

		CHelper::Trace("ASPI loaded succesfully. ASPI device count=%lu\n", iASPIDeviceCount);
	}
	else
	{
		CHelper::Trace("CSCSI::InitCommunication - Loading SPTI. Checking if NT platform...\n");
		
		OSVERSIONINFO osver;
		ZeroMemory( &osver, sizeof(osver) );
		osver.dwOSVersionInfoSize = sizeof(osver);
		GetVersionEx( &osver );
		
		if (osver.dwPlatformId != VER_PLATFORM_WIN32_NT)
		{
			CHelper::Trace("CSCSI::InitCommunication - NT platform not found. No SPTI! Change to ASPI mode!\n");
			return SCSINoSPTI;
		}

		CHelper::Trace("CSCSI::InitCommunication - NT platform confirmed. About to scan drives...\n");

		char drv[4];
 		for (int i = 2; i < 26; i++)
 		{
 			wsprintf(drv, "%c:\\", (char)('A' + i));
 
 			if (GetDriveType(drv) == DRIVE_CDROM)
 			{
				CHelper::Trace("CSCSI::InitCommunication - CD-rom drive found (%c)\n", (char)('A' + i));
				CHelper::Trace("CSCSI::InitCommunication - opening drive...\n");

 				// we have found a CD drive.
 				HANDLE hDrive;
 				hDrive = m_spti.OpenDrive(i);
 				if (hDrive == INVALID_HANDLE_VALUE)
				{
					CHelper::Trace("CSCSI::InitCommunication - Drive open failed. Trying next drive\n");
 					continue;
				}
				
				CHelper::Trace("CSCSI::InitCommunication - Drive open succeded. About to INQUIRY...\n");

 				PSCSI_PASS_THROUGH_DIRECT_WITH_BUFFER pswb;
 				PSCSI_ADDRESS pscsiAddr;
 
 				//Get the drive inquiry data
 				char buf[1024];
 				ZeroMemory( &buf, 1024 );
 
 				BYTE inqData[100];
 				ZeroMemory( inqData, 100 );
 				
 				pswb                      = (PSCSI_PASS_THROUGH_DIRECT_WITH_BUFFER)buf;
 				pswb->spt.Length          = sizeof(SCSI_PASS_THROUGH);
 				pswb->spt.CdbLength       = 6;
 				pswb->spt.SenseInfoLength = 24;
 				pswb->spt.DataIn          = SCSI_IOCTL_DATA_IN;
 				pswb->spt.DataTransferLength = 100;
 				pswb->spt.TimeOutValue    = 2;
 				pswb->spt.DataBuffer      = inqData;
 				pswb->spt.SenseInfoOffset = offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER,ucSenseBuf );
 				pswb->spt.Cdb[0]          = 0x12;
 				pswb->spt.Cdb[4]          = 100;
 
 				unsigned long length = sizeof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER);
 				unsigned long returned = 0;
 				BOOL status = DeviceIoControl(hDrive,
 										IOCTL_SCSI_PASS_THROUGH_DIRECT,
 										pswb,
 										length,
 										pswb,
 										length,
 										&returned,
 										NULL );
 
 				if ( !status )
 				{
					CHelper::Trace("CSCSI::InitCommunication - INQUIRY failed! Skipping to next drive\n");
 					CloseHandle(hDrive);
 					continue;
 				}
				
				CHelper::Trace("CSCSI::InitCommunication - INQUIRY succeded. About to query address via IOCTL_SCSI_GET_ADDRESS...\n");

 				// get the address (path/tgt/lun) of the drive via IOCTL_SCSI_GET_ADDRESS
 				ZeroMemory( &buf, 1024 );
 				pscsiAddr = (PSCSI_ADDRESS)buf;
 				pscsiAddr->Length = sizeof(SCSI_ADDRESS);
 				if (DeviceIoControl( hDrive, IOCTL_SCSI_GET_ADDRESS, NULL, 0, pscsiAddr, sizeof(SCSI_ADDRESS), &returned, NULL ))
 				{
					CHelper::Trace("CSCSI::InitCommunication - Address retrieved. Constructing structure for this drive...\n");

					SCSIDEVICE* pDevice = new SCSIDEVICE;
					
					pDevice->bIsValid = TRUE;
 					pDevice->ha = pscsiAddr->PortNumber;
 					pDevice->tgt = pscsiAddr->TargetId;
 					pDevice->lun = pscsiAddr->Lun;
					pDevice->cLetter = (char)('A' + i);
					pDevice->hDrive = hDrive;

 					//strncpy(pDevice->szAdapter, (char*)&haInquiry.HA_Identifier[0], 63);
					strcpy(pDevice->szAdapter, "SPTI");

					memset(pDevice->szID, 0, MAXIDLEN+1);
					memset(pDevice->szVendor, 0, 9);
					memset(pDevice->szProdId, 0, 17);
					memset(pDevice->szVendSpec, 0, 21);
					memset(pDevice->szRev, 0, 5);

					memcpy(pDevice->szVendor, &inqData[8], 8);
					memcpy(pDevice->szProdId, &inqData[16], 16);
					memcpy(pDevice->szRev, &inqData[32], 4);
					memcpy(pDevice->szVendSpec, &inqData[36], 20);

					RemoveDoubleCharFromString(pDevice->szVendor, ' ');
					RemoveDoubleCharFromString(pDevice->szProdId, ' ');
					RemoveDoubleCharFromString(pDevice->szRev, ' ');
					RemoveDoubleCharFromString(pDevice->szVendSpec, ' ');

					char szID[101];
					sprintf(szID, "%s %s", 
 							 (char*)&pDevice->szVendor[0], 
 							 (char*)&pDevice->szProdId[0]);

 					strncpy(pDevice->szID, szID, MAXIDLEN);
 					pDevice->szID[MAXIDLEN] = 0;

					CHelper::Trace("CSCSI::InitCommunication - Drive info set: ID=%s, Letter=%c, ha=%lu, tgt=%lu, lun=%lu\n", 
									pDevice->szID, pDevice->cLetter, pDevice->ha, pDevice->tgt, pDevice->lun);
					
					CHelper::Trace("CSCSI::InitCommunication - About to call UpdateDeviceInfo on this drive...\n");

					UpdateDeviceInfo(*pDevice, true, true);

					arrCDR->Add(pDevice);


					if (!pDevice->bWriteCDR || !pDevice->bWriteCDRW)
					{
						// maybe we should close the handle since we don't use the
						// cd reader devices muchg anyways?

//						CloseHandle(hDrive);
//						delete pDevice;
					}

 					// look
 					//memcpy(inqData, inqData, 36 );
 
 					//strncpy(arrDevices[nDeviceCount].szAdapter, (char*)&haInquiry.HA_Identifier[0], 63);
  			    }
 			}
		}
	}

	return 0;
}


void CSCSI::EndCommunication()
{
	// Call this to free ASPI or SPTI
}

int CSCSI::ReadDeviceName(SCSIDEVICE &device)
{
	// This function will fill the secondary details for a device
	// make sure the tgt, lun values are valid. You would usually
	// call this after calling getscsidevicelist to get the details

	CHelper::Trace("ReadDeviceName\n");

	BYTE cdb[24]  = {SCSI_INQUIRY, 0, 0, 0, 100, 0};
	BYTE buf[100] = {0};

	int iResult = ExecSCSICommand(device, 6, cdb, DEFWAITLEN, buf, 100, SRB_DIR_IN);

	if (iResult)
 		return iResult;

	memset(device.szID, 0, MAXIDLEN+1);
	memset(device.szVendor, 0, 9);
	memset(device.szProdId, 0, 17);
	memset(device.szVendSpec, 0, 21);
	memset(device.szRev, 0, 5);

	memcpy(device.szVendor, &buf[8], 8);
	memcpy(device.szProdId, &buf[16], 16);
	memcpy(device.szRev, &buf[32], 4);
	memcpy(device.szVendSpec, &buf[36], 20);

	RemoveDoubleCharFromString(device.szVendor, ' ');
	RemoveDoubleCharFromString(device.szProdId, ' ');
	RemoveDoubleCharFromString(device.szRev, ' ');
	RemoveDoubleCharFromString(device.szVendSpec, ' ');

	char szID[101];
	sprintf(szID, "%s %s", 
 			 (char*)&device.szVendor[0], 
 			 (char*)&device.szProdId[0]);

	strncpy(device.szID, szID, MAXIDLEN);
	device.szID[MAXIDLEN] = 0;

	return 0;
}

int CSCSI::ReadDiscInformation(SCSIDEVICE & device, long * pnDiskType, long * pnDiscState, long * pnSessionCount, long * pnLastSessionStartLBA)
{
	// This function queries the actual disc inserted, and tells
	// you whatsup with the disc. See mmc 6.2.6
	// enum DiscInfo{InfoCDRW,InfoCDR,InfoCD,InfoEmpty,InfoOpen,InfoClosed};
	// DiscInfo gives the values for the nDiskType and nDiskStatus
	// LOOK AT read ATIP mmc 5.1.13
	
	CHelper::LogTimeStamp(false);
	CHelper::Trace("\n");
	CHelper::LogTimeStamp(true);

	CHelper::Trace("CSCSI::ReadDiscInformation entry\n");

	BYTE buf[100] = {0};
	BYTE cdb[24] = {0x51, 0};
	cdb[7] = 100 >> 8;
	cdb[8] = 100;
	
	int iError = ExecSCSICommand(device, 10, cdb, DEFWAITLEN, buf, 100, SRB_DIR_IN);
	if (iError)
	{
		if (iError == -15)
			CHelper::Trace("CSCSI::ReadDiscInformation - No Disc In Drive=%d\n", iError);
		else
			CHelper::Trace("CSCSI::ReadDiscInformation FAILED! Error=%d\n", iError);
		return iError;
	}
	
	CHelper::Trace("CSCSI::ReadDiscInformation - Query succeded. Information=");
	CHelper::LogTimeStamp(false);
	
	if (pnSessionCount)
		*pnSessionCount = buf[4];
	
	if (pnLastSessionStartLBA)
	{
		// min sec frac are in buf 17, 18, 19 according to dao
		// convert the msfs to lba
		*pnLastSessionStartLBA = (buf[17] * 4500) + (buf[18] * 75) + buf[19];
	}

	if (pnDiscState)
	{
		switch (buf[2] & 0x03)
		{
		case 0:
			{
				// empty cd
				CHelper::Trace("Empty CD");
				*pnDiscState = InfoEmpty;
			}
			break;
		case 1:
			{
				// apendeable
				CHelper::Trace("Open CD");
				*pnDiscState = InfoOpen;
			}
			break;
		case 2:
			{
				// complete and locked. Cannot write to this
				CHelper::Trace("Closed CD");
				*pnDiscState = InfoClosed;
			}
			break;
		}
	}
	
	if (pnDiskType)
	{
		if (buf[8] == 0x00)
		{
			// Normal CD
			*pnDiskType = InfoCD;
			
			if (pnDiscState && *pnDiscState == InfoEmpty)
			{
				*pnDiskType = InfoCDR;
			}

			// We check if rewriteable
			if (buf[2] & 0x10)
			{
				*pnDiskType = InfoCDRW;
			}
		}
		else if (buf[8] == 0x10)
		{
			*pnDiskType = InfoCDI;
		}
		else if (buf[8] == 0x20)
		{
			*pnDiskType = InfoCDXA;
		}
		else if (buf[8] == 0xFF)
		{
			// disc type not defined. this is officially a hack
			// when you have multisession, it won't work no more
			// thus, you have to query ATIP

			if (pnDiscState && *pnDiscState == InfoEmpty)
			{
				*pnDiskType = InfoCDR;
			}
			else
			{
				*pnDiskType = InfoCD;
			}

			// We check if rewriteable
			if (buf[2] & 0x10)
			{
				*pnDiskType = InfoCDRW;
			}
		}
		else
		{
			*pnDiskType = InfoUnknown;
		}
	}

	CHelper::Trace("\n");
	CHelper::LogTimeStamp(true);

	return 0;
}


int CSCSI::CloseTrackOrSession(SCSIDEVICE & device, bool bCloseSession, int nTrackNumber)
{
	// Closes the track or the session
	// mmc 6.2.3
	CHelper::Trace("CloseTrackOrSession\n");

	BYTE cdb[10] = {0};
	memset(cdb, 0, 10);

	cdb[0] = 0x5B; // close track or session
	cdb[1] = 0; // immediate = 1, not immediate = 0

	if (bCloseSession)
	{
		cdb[2] = 0x02; //Close session. must be valid
		cdb[5] = 0; // Track number
	}
	else
	{
		cdb[2] = 1; //Close track.
		cdb[5] = nTrackNumber; // Track number. 1 based
	}

	int iError = ExecSCSICommand(device, 10, cdb, INFINITE, 0, 0, 0);
	if (iError)
	{	
		if (bCloseSession)
		{
			CHelper::Trace("Close session command failed!\n");
		}
		else
		{
			CHelper::Trace("Close track command failed!\n");
		}
	
		return iError;
	}
		
	CHelper::Trace("Close track command went OK!\n");

	return 0;
}


int CSCSI::EjectDevice(SCSIDEVICE & device, bool bEject)
{
	CHelper::Trace("Eject called. Value=%lu\n", bEject);

	// mode sense command is in the spc 7.11

	BYTE cdb[24] = {0};
	cdb[0] = 0x1B;
	cdb[1] = 1 << 0;
	cdb[4] = bEject ? 0x02 : 0x03; //bin = 101, pc = 0, 
	
	int iError = ExecSCSICommand(device, 10, cdb, INFINITE, 0, 0, 0);
	if (iError)
		return iError;

	return 0;
}

int CSCSI::GetModePage(SCSIDEVICE & device, int pageCode, BYTE* pModePage, BYTE* pModePageHeader, BYTE* pBlockDesc, long nPageBufLen)
{
	CHelper::Trace("CSCSI::GetModePage - entry\n");

	// mode sense command is in the spc 7.11
	int nDataLen = nPageBufLen + 8 + 100; // cdrecord uses 100
	BYTE* pLocalBuf = new BYTE[nDataLen];
	memset(pLocalBuf, 0, nDataLen);
	
	BYTE cdb[10] = {0x5A, 0};
	cdb[2]     = pageCode & 0x3f; //bin = 101, pc = 0, 
	cdb[7]     = nDataLen >> 8; //buflen msb
	cdb[8]     = nDataLen; //buflen lsb

	int iError = ExecSCSICommand(device, 10, cdb, DEFWAITLEN, pLocalBuf, nDataLen, SRB_DIR_IN);
	if (iError)
	{
		CHelper::Trace(" CSCSI::GetModePage - returned error. Error=%d\n", iError);

		delete [] pLocalBuf;
		return iError;
	}
	

	long modeDataLen = (pLocalBuf[0] << 8) | pLocalBuf[1];
	long blockDescLen = (pLocalBuf[6] << 8) | pLocalBuf[7];

	CHelper::Trace("CSCSI::GetModePage - went ok, datalen=%d, blocklen=%d\n", modeDataLen, blockDescLen);

	// copy header in
	memcpy(pModePageHeader, pLocalBuf, 8);
	
	// copy block desc in
	if (blockDescLen >= 8)
		memcpy(pBlockDesc, pLocalBuf + 8, 8);
    else 
		memset(pBlockDesc, 0, 8);
	
	// copy mode data in
	if (modeDataLen > blockDescLen + 6) 
	{
		unsigned char *modePage = pLocalBuf + blockDescLen + 8;
		long modePageLen = modePage[1] + 2;

		if (modePageLen > nPageBufLen)
			modePageLen = nPageBufLen;

		memcpy(pModePage, modePage, modePageLen);
		
	}
	else
	{
		CHelper::Trace("CSCSI::GetModePage - No mode page data received.\n");
		delete[] pLocalBuf;
	
		return SCSINoModePage;
	}

	delete [] pLocalBuf;
	return 0;
}

int CSCSI::ReadBufferCapacity(SCSIDEVICE & device, long &nLength, long &nBlank)
{
	// mmc 6.2.5
	CHelper::Trace("ReadBufferCapacity\n");

	BYTE cdb[10];
	BYTE data[12];

	memset(cdb, 0, 10);
	memset(data, 0, 12);

	cdb[0] = 0x5c; // READ BUFFER CAPACITY
	cdb[8] = 12;
	
	static nLastLen = 0;
	int iError = ExecSCSICommand(device, 10, cdb, 100, data, 12, SRB_DIR_IN);
	if (iError)
	{
		nLength = nLastLen;
		nBlank = 0;
		return iError;
	}

	nLength  = (data[4] << 24) | (data[5] << 16) | (data[6] << 8) | data[7];
    nBlank = (data[8] << 24) | (data[9] << 16) | (data[10] << 8) | data[11];
	
	nLastLen = nLength;
	return 0;
}

int CSCSI::SynchronizeCache(SCSIDEVICE & device)
{
	// The description of this commands is in the mmc 6.2.13
	
	// output to log
	CHelper::Trace("SynchronizeCache\n");

	// declare buffer with first parameter specifying the command
	// and all other parameters equal to 0
	BYTE cdb[10] = {0x35, 0};

	// pass this buffer to the ExecSCSICommand, which will send it
	// to the device over the ExecSCSICommand function

	int iError = ExecSCSICommand(device, 10, cdb, INFINITE, 0, 0, 0);
	if (iError)
	{
		CHelper::Trace("Sync cache command FAILED!\n");
		return iError;
	}

	CHelper::Trace("Sync cache command went OK!\n");

	return 0;
}


int CSCSI::WriteBlock(SCSIDEVICE & device, BYTE* ptr, long nBlocksToWrite, long nBytesToWrite, long nStartLBA)
{
	// write command is in the spc 6.2.14
	
	CHelper::Trace("\nCSCSI::WriteBlock entry\n");
	
	BYTE cdb[10] = {0x2A, 0};

	cdb[2]     = (BYTE)(nStartLBA >> 3*8);
	cdb[3]     = (BYTE)(nStartLBA >> 2*8);
	cdb[4]     = (BYTE)(nStartLBA >> 1*8);
	cdb[5]     = (BYTE)(nStartLBA >> 0*8);
	cdb[7]     = (BYTE)(nBlocksToWrite >> 8); // len msb
	cdb[8]     = (BYTE)(nBlocksToWrite & 0xff); // len lsb
	
	int iError = ExecSCSICommand(device, 10, cdb, INFINITE, ptr, nBytesToWrite, SRB_DIR_OUT);
	if (iError)
	{
		CHelper::Trace("WriteBlock failed with return value=%d\n", iError);
		return iError;
	}

	return 0;
}

int CSCSI::TestUnitReady(SCSIDEVICE & device, bool bTestReadDiscInfo)
{
	CHelper::Trace("TestUnitReady. bTestReadDiscInfo=%lu\n", bTestReadDiscInfo);

	// TestUnitReady command is in the spc 7.24
	
	BYTE cdb[12] = {0};

	int iError = ExecSCSICommand(device, 10, cdb, INFINITE, NULL, 0, 0);
	if (iError)
	{
		CHelper::Trace("TestUnitReady 0x00 failed\n");
		return iError;
	}
	
	if (!bTestReadDiscInfo)
	{
		CHelper::Trace("TestUnitReady: User doesn't require disc check\n");

		// unit is ready, and user doesn't want us to check if disc is available
		return 0;
	}
	
	BYTE buf[4] = {0};
	
	
	// We check read disc info to see what it has to say about the ready
	// state
	memset(cdb, 0, 12);
	
	cdb[0]     = 0x51;
	cdb[8]     = 4; // dao

	iError = ExecSCSICommand(device, 10, cdb, INFINITE, buf, 4, SRB_DIR_IN);
	if (iError)
	{
		CHelper::Trace("TestUnitReady 0x51 also failed\n");
		return iError;
	}
	
	return 0;
}

int CSCSI::SendModePage(SCSIDEVICE & device, BYTE* pModePage, BYTE* pModePageHeader, BYTE* pBlockDesc)
{
	CHelper::Trace("CSCSI::SendModePage entry\n");

	// mode select command is in the spc 7.9

	long pageLen = pModePage[1] + 2;
	long dataLen = pageLen + 8 + (pBlockDesc ? 8 : 0);
	
	BYTE* data = new BYTE[dataLen];
	memset(data, 0, dataLen);
	
	if (pModePageHeader != NULL)
		memcpy(data, pModePageHeader, 8);
	
	// why this? I don't know.
	data[0] = 0;
	data[1] = 0;
	data[4] = 0;
	data[5] = 0;
	
	if (pBlockDesc != NULL) 
	{
		memcpy(data + 8, pBlockDesc, 8);
		memcpy(data + 16, pModePage, pageLen);
		data[6] = 0;
		data[7] = 8;
	}
	else 
	{
		memcpy(data + 8, pModePage, pageLen);
		data[6] = 0;
		data[7] = 0;
	}
	
	BYTE cdb[24] = {0x55, 0};
	cdb[1]     = 0x10; // hex = 1 0000 binary
	cdb[7]     = (BYTE)(dataLen >> 8); //buflen msb
	cdb[8]     = (BYTE)dataLen; //buflen lsb
	
	int iError = ExecSCSICommand(device, 10, cdb, INFINITE, data, dataLen, SRB_DIR_OUT);
	if (iError)
	{
		CHelper::Trace("CSCSI::SendModePage failed. Error=%d\n", iError);

		delete [] data;
		return iError;
	}
	
	CHelper::Trace("CSCSI::SendModePage went ok\n");

	delete [] data;

	return 0;
}

int CSCSI::ResetSCSIBus(SCSIDEVICE & device)
{
	CHelper::Trace("ResetSCSIBus\n");

	HANDLE hEventSRB = CreateEvent ( NULL, true, false, NULL );

	// reset the SCSI bus
	SRB_BusDeviceReset srbReset;
	memset ( &srbReset, 0, sizeof ( SRB_BusDeviceReset ) );

	srbReset.SRB_Cmd = SC_RESET_DEV;
	srbReset.SRB_HaId = device.ha;  // host adapter # 0
	srbReset.SRB_Flags = SRB_EVENT_NOTIFY;
	srbReset.SRB_Target = device.tgt; // SCSI ID = 2
	srbReset.SRB_Lun = device.lun;
	srbReset.SRB_PostProc = ( LPVOID ) hEventSRB;

	ResetEvent ( hEventSRB );
	
	m_aspi.SendCommand ( ( LPSRB ) &srbReset );
	
	if (srbReset.SRB_Status == SS_PENDING)
		WaitForSingleObject ( hEventSRB, INFINITE );

	CloseHandle ( hEventSRB );

	if ( srbReset.SRB_Status == SS_COMP )
	{
		CHelper::Trace("Reset bus went OK.\n");
		return 0;
	}

	CHelper::Trace("Reset bus FAILED!!.\n");
	int iErr = ScsiIoError(srbReset.SRB_Status, srbReset.SRB_HaStat, srbReset.SRB_TargStat, 0);
	return iErr;
}

void CSCSI::RemoveDoubleCharFromString(char *pstr, char cToRemove)
{
	// this function looks through a string, and if a character
	// occurs twice or more, it removes the char

	char szDbl[3];
	szDbl[0] = cToRemove;
	szDbl[1] = cToRemove;
	szDbl[2] = 0;

	char* pstrRes = strstr(pstr, szDbl);
	while (pstrRes != NULL)
	{
		// pstr at this point is pointing at a location of a
		// double character

		int nLen = strlen(pstrRes);
		for (int i=1;i<nLen;i++)
		{
			// we shift the characters down
			pstrRes[i] = pstrRes[i+1];
		}

		pstrRes = strstr(pstr, szDbl);
	}
}

int CSCSI::ReadDiscCapacity(SCSIDEVICE &device, long &nLength, long &nMin, long &nSec)
{
	CHelper::LogTimeStamp(false);
	CHelper::Trace("\n");
	CHelper::LogTimeStamp(true);

	CHelper::Trace("CSCSI::ReadDiscCapacity entry\n");

	BYTE buf[100] = {0};
	BYTE cdb[24] = {0x51, 0};
	cdb[7] = 100 >> 8;
	cdb[8] = 100;
	
	int iError = ExecSCSICommand(device, 10, cdb, DEFWAITLEN, buf, 100, SRB_DIR_IN);
	if (iError)
	{
		CHelper::Trace("CSCSI::ReadDiscCapacity FAILED. Error=%d\n", iError);
		return iError;
	}
	
	if (buf[21] != 0xff || buf[22] != 0xff || buf[23] != 0xff) 
	{
		nMin = buf[21];
		nSec = buf[22];
		nLength = (MSFToLBA(buf[21], buf[22], buf[23])) * 2048;
    }
	else
		nLength = 0;

	CHelper::Trace("CSCSI::ReadDiscCapacity went ok. Length=%lu\n", nLength);
	
	return 0;
}

long CSCSI::MSFToLBA(int min, int sec, int frac)
{
	_ASSERT(frac >= 0 && frac < 75);
	_ASSERT(sec >= 0 && sec < 60);
	_ASSERT(min >= 0);

	return (min * 4500 + sec * 75 + frac);
}

//----------------------------------
//Rounds a float to the closest int
//----------------------------------
int CSCSI::Round( float num )
{
	int roundnum = (int)num;
	
	if( (num - roundnum) >= .5 )
		return roundnum+1;

	return roundnum;
}

int CSCSI::KBSpeedToMultipleSpeed(int nKB)
{
	int iResult = Round((float)nKB/(float)176);
	if (iResult > 1 && iResult % 2 != 0)
		iResult--;
	return iResult;
}

#define RETRY(func, failval, wait, loop) iRetry = loop; while(func == failval && iRetry > 0) {Sleep(wait); iRetry--;}

//DEL int CSCSI::GetWriteSpeedInformation(SCSIDEVICE &device, long *arrSpeedMultiple, long * arrSpeedKBs, int nArraySize, long *plCurrentSpeed, long *plMaxSpeed)
//DEL {
//DEL 	// We can get max speed and current speed easily
//DEL 	// the speeds are in kb/sec
//DEL 
//DEL 	CHelper::Trace("GetWriteSpeedInformation\n");
//DEL 	
//DEL 	int iRetry = 0;
//DEL 
//DEL 	DWORD dwCurSpeed = 0;
//DEL 	RETRY(QueryDeviceParams(device, CDP_CURRWSPEED, dwCurSpeed, true), FALSE, 1000, 10);
//DEL 	if (iRetry == 0) // failed
//DEL 		return -1;
//DEL 
//DEL 	if (plCurrentSpeed)
//DEL 		*plCurrentSpeed = KBSpeedToMultipleSpeed(dwCurSpeed);
//DEL 
//DEL 	DWORD dwMaxSpeed = 0;
//DEL 	RETRY(QueryDeviceParams(device, CDP_MAXWSPEED, dwMaxSpeed, true), FALSE, 1000, 10);
//DEL 	if (iRetry == 0)
//DEL 		return -1;
//DEL 
//DEL 	if (plMaxSpeed)
//DEL 		*plMaxSpeed = KBSpeedToMultipleSpeed(dwMaxSpeed);
//DEL 	
//DEL 	CHelper::Trace("Max Write Speed=%lu. Current speed=%lu\n", dwMaxSpeed, dwCurSpeed);
//DEL 
//DEL 	// We now try to get the supported speeds
//DEL 	
//DEL 	if (arrSpeedMultiple)
//DEL 	{
//DEL 		memset(arrSpeedMultiple, 0, sizeof(long) * nArraySize);
//DEL 		memset(arrSpeedKBs, 0, sizeof(long) * nArraySize);
//DEL 
//DEL 		if (dwMaxSpeed == 0)
//DEL 			return -1;
//DEL 		
//DEL 		int iCur = 0;
//DEL 		for (int xSpeed = KBSpeedToMultipleSpeed(dwMaxSpeed); xSpeed >= 1; xSpeed-=2 )
//DEL 		{
//DEL 			arrSpeedMultiple[iCur] = xSpeed;
//DEL 			arrSpeedKBs[iCur] = xSpeed * 176;
//DEL 			iCur++;
//DEL 		}
//DEL 		
//DEL 		qsort(arrSpeedMultiple, iCur, sizeof(long), DigitSortProc);
//DEL 
//DEL 		/*
//DEL 		long lCurrentSpeed = 0;
//DEL 		
//DEL 		int iSafety = 0;
//DEL 		while (SCSITargetBusy == SetSpeed(device, NULL, (long*)&dwMaxSpeed))
//DEL 		{
//DEL 			Sleep(100);
//DEL 			iSafety++;
//DEL 
//DEL 			if (iSafety == 40)
//DEL 				break;
//DEL 		}
//DEL 
//DEL 		int iError = GetWriteSpeedInformation(device, NULL, NULL, 0, &lCurrentSpeed, 0);
//DEL 		ASSERT(iError == 0);
//DEL 
//DEL 		arrSpeedMultiple[0] = lCurrentSpeed;
//DEL 		arrSpeedKBs[0] = dwMaxSpeed;
//DEL 
//DEL 		int nArrayPos = 1;
//DEL 		int nTolerance = 0; // tolerance in kb/sec. Used to measure speeds left and right
//DEL 
//DEL 		for (int xSpeed = KBSpeedToMultipleSpeed(dwMaxSpeed); xSpeed >= 1; xSpeed-- )
//DEL 		{
//DEL 			int kbSpeed = xSpeed * X1;
//DEL 
//DEL 		//	for (int kbSpeed = (xSpeed*X1) + nTolerance; kbSpeed >= (xSpeed*X1) - nTolerance; kbSpeed-- )
//DEL 			{
//DEL 				// fire doevents here
//DEL 				iSafety = 0;
//DEL 				while (SCSITargetBusy == SetSpeed(device, NULL, (long*)&kbSpeed))
//DEL 				{
//DEL 					Sleep(100);
//DEL 					iSafety++;
//DEL 
//DEL 					if (iSafety == 40)
//DEL 						break;
//DEL 				}
//DEL 
//DEL 				// Get current speed info
//DEL 				long lCurrentSpeed = 0;
//DEL 				iError = GetWriteSpeedInformation(device, NULL, NULL, 0, &lCurrentSpeed, 0);
//DEL 				ASSERT(iError == 0);
//DEL 
//DEL 				bool bAlreadyIn = false;
//DEL 				for (int i=0;i<=nArrayPos;i++)
//DEL 				{
//DEL 					if (arrSpeedMultiple[i] == lCurrentSpeed)
//DEL 					{
//DEL 						bAlreadyIn = true;
//DEL 						break;
//DEL 					}
//DEL 				}
//DEL 				
//DEL 				if (iError != 0)
//DEL 					bAlreadyIn = true; // don't add it, error when setting it
//DEL 
//DEL 				if (bAlreadyIn == false)
//DEL 				{
//DEL 					CHelper::Trace("\n\nSpeed Detected = %luX. KB/Sec=%lu\n\n", lCurrentSpeed, kbSpeed);
//DEL 
//DEL 					arrSpeedMultiple[nArrayPos] = lCurrentSpeed;
//DEL 					arrSpeedKBs[nArrayPos] = kbSpeed;
//DEL 					nArrayPos++;
//DEL 				}
//DEL 			}
//DEL 		}
//DEL */
//DEL 		//qsort(arrSpeedMultiple, nArrayPos, sizeof(long), DigitSortProc);
//DEL 	}
//DEL 	
//DEL 	
//DEL 	return 0;
//DEL }

int CSCSI::SetSpeed(SCSIDEVICE & device, long *nReadSpeed, long *nWriteSpeed)
{
//	CHelper::Trace("SetSpeed. WriteSpeed=%lu\n", *nWriteSpeed);
		
	BYTE cdb[12] = {0};
	cdb[0] = 0xBB;

	if (nReadSpeed)
	{
		cdb[2] = (BYTE)((*nReadSpeed) >> 8);
		cdb[3] = (BYTE)(*nReadSpeed);
	}
	else
	{
		cdb[2] = (BYTE)(device.nCurReadSpeed >> 8);
		cdb[3] = (BYTE)device.nCurReadSpeed;
	}
	
	if (nWriteSpeed)
	{
		if (*nWriteSpeed == 0)
		{
			cdb[4] = (BYTE)0xFF;
			cdb[5] = (BYTE)0xFF;
		}
		else
		{
			cdb[4] = (BYTE)(*nWriteSpeed >> 8);
			cdb[5] = (BYTE)*nWriteSpeed;
		}
	}
	else
	{
		cdb[4] = (BYTE)(device.nCurWriteSpeed >> 8);
		cdb[5] = (BYTE)(device.nCurWriteSpeed);
	}
	
//	CHelper::Trace("SetSpeed. About to exec command\n");
	try
	{
		return ExecSCSICommand(device, 12, cdb, INFINITE, 0, 0, 0);
	}
	catch(...)
	{
		CHelper::Trace("SetSpeed crashed!\n");
	}

	return -1;
}

int CSCSI::DigitSortProc(const void *arg1,  const void *arg2)
{
	if (*(long*)arg1 < *(long*)arg2)
		return 1;
	else if (*(long*)arg1 > *(long*)arg2)
		return -1;

	return 0;
}

int CSCSI::ReadDiscSize(SCSIDEVICE &device, long &nLength)
{
	CHelper::LogTimeStamp(false);
	CHelper::Trace("\n");
	CHelper::LogTimeStamp(true);

	CHelper::Trace("CSCSI::ReadDiscSize entry\n");

	// This capacity reads the capacity available for read
	BYTE cdb[10];
	BYTE data[8];

	memset(cdb, 0, 10);
	memset(data, 0, 8);

	cdb[0] = 0x25; // READ CD RECORDED CAPACITY

	int iError = ExecSCSICommand(device, 10, cdb, INFINITE, data, 8, SRB_DIR_IN);
	if (iError)
	{
		CHelper::Trace("CSCSI::ReadDiscSize FAILED! Error=%d\n", iError);
		return iError;
	}

	nLength  = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
	
	// nLength is the last block. Multiply by 1024 (?) for the size

	nLength = nLength * 2048;

	CHelper::Trace("CSCSI::ReadDiscSize went ok. Length=%lu\n", nLength);

	return 0;
}

int CSCSI::ReadTrackInfo(SCSIDEVICE &device, int nTrack, bool *pbDamage, long *pnTrackMode, long *pnTrackStart, long *pnNextWriteAddr, long * pnTrackSize)
{
	BYTE cdb[10];
	BYTE data[30];

	memset(cdb, 0, 10);
	memset(data, 0, 30);

	cdb[0] = 0x52;
	cdb[1] = 1;
	cdb[2] = (BYTE)(nTrack >> 24);
	cdb[3] = (BYTE)(nTrack >> 16);
	cdb[4] = (BYTE)(nTrack >> 8);
	cdb[5] = (BYTE)nTrack;
	cdb[7] = 0; // msb of 16
	cdb[8] = 30;

	int iError = ExecSCSICommand(device, 10, cdb, INFINITE, data, 30, SRB_DIR_IN);
	if (iError)
		return iError;
	
	if (pnNextWriteAddr)
		*pnNextWriteAddr = 0;

	if ((data[6] & 0x40) && (data[7] & 0x01) && !(data[6] & 0xb0))
	{
		if (pnNextWriteAddr)
		{
			*pnNextWriteAddr |= data[12] << 24; // MSB of LBA
			*pnNextWriteAddr |= data[13] << 16;
			*pnNextWriteAddr |= data[14] << 8;
			*pnNextWriteAddr |= data[15];       // LSB of LBA
		}
	}

	if (pnTrackSize)
	{
		*pnTrackSize = (data[24] << 24) | (data[25] << 16) | (data[26] << 8) | data[27];
	}

	if (pnTrackStart)
	{
		*pnTrackStart = (data[8] << 24) | (data[9] << 16) | (data[10] << 8) | data[11];
	}

	return 0;
}

int CSCSI::StartEraseDisc(SCSIDEVICE &device, bool bQuickErase)
{
	// mmc 6.2.2

	BYTE cdb[12] = {0};
	memset(cdb, 0, 12);

	cdb[0] = 0xA1;
	cdb[1] = bQuickErase ? 0x01 : 0x00;
	
	cdb[1] |= 1 << 4; // immediate return

	int iError = ExecSCSICommand(device, 12, cdb, INFINITE, NULL, 0, NULL);
	if (iError)
		return iError;
	
	return 0;
}

int CSCSI::PerformOPC(SCSIDEVICE &device)
{
	BYTE cdb[10];
	memset(cdb, 0, 10);

	cdb[0] = 0x54; // SEND OPC INFORMATION
	cdb[1] = 1;

	int iError = ExecSCSICommand(device, 10, cdb, INFINITE, NULL, 0, SRB_DIR_OUT);
	if (iError)
		return iError;
	
	return 0;
}

int CSCSI::UpdateDeviceInfo(SCSIDEVICE &device, bool bScanWriteSpeeds, bool bScanReadSpeeds)
{
	CHelper::LogTimeStamp(false);
	CHelper::Trace("\n");
	CHelper::LogTimeStamp(true);

 	CHelper::Trace("CSCSI::UpdateDeviceInfo entry. ScanWriteSpeeds=%lu, ScanReadSpeeds=%lu\n", bScanWriteSpeeds, bScanReadSpeeds);
	
	// reset the values
	device.bReadCDR   = true;
	device.bReadCDRW  = true;
	device.bWriteCDR  = true;
	device.bWriteCDRW = false;
	device.bTestWrite = false;
	device.bReadDVDR = false;
	device.bReadDVDRAM = false;
	device.bReadDVDROM = false;
	device.bWriteDVDR = false;
	device.bWriteDVDRAM = false;
	device.bJustlink = false;

	device.nMaxReadSpeed  = 0;
	device.nMaxWriteSpeed = 0;
	device.nCurReadSpeed  = 0;
	device.nCurWriteSpeed = 0;
	
	device.nBufferSize = 0;
	
	long nDataLen = 256;
	// Get all mode pages, and see what it supports
	BYTE cdb[10] = {0x5A, 0, 0x3F, 0, 0, 0, 0, (BYTE)(nDataLen >> 8), (BYTE)nDataLen, 0};
	//BYTE cdb[24] = {0x5A, 0, CDRCAPS, 0, 0, 0, 0, 0x01, 0x00};
 	BYTE buf[256] = {0};

	CHelper::Trace("CSCSI::UpdateDeviceInfo - About to MODE SENSE\n");

	int iRetry = 0;
 	int iResult = ExecSCSICommand(device, 10, cdb, DEFWAITLEN, buf, 256, SRB_DIR_IN);		
 	if (iResult)
	{
		CHelper::Trace("CSCSI::UpdateDeviceInfo - Getting mode page failed. Error=%d\n", iResult);
 		return iResult;
	}
	
	CDRomCapabilitiesStatusMask ccsm;

 	int lenData = ((unsigned int)buf[0] << 8) + buf[1];
	
	CHelper::Trace("CSCSI::UpdateDeviceInfo - MODE SENSE succeded. Returned datalen=%lu.\n", lenData);
	CHelper::Trace("CSCSI::UpdateDeviceInfo - About to check returned mode pages for cd-r caps...\n");

	bool bModePageFound = false;

 	// set to first sense mask, and then walk through the masks
 	BYTE* pCur = buf + 8;
 	BYTE* pMax = buf + 256;
 	
	try
	{
 		while( (pCur < &(buf[2+lenData])) && (pCur < pMax) )
		 {
 			BYTE which;
 
 			which = pCur[0] & 0x3F;
 			switch( which )
 			{
 			case CDRCAPS:
				CHelper::Trace("CSCSI::UpdateDeviceInfo - cd-r caps mode page found. Len=%lu. If neccesary, will be truncated to 23.\n", pCur[1]+2);
				
				bModePageFound = true;

				long nLen = pCur[1]+2 <= 23 ? pCur[1]+2 : 23;

				memcpy(ccsm, pCur, nLen);

				device.bReadCDR   = (ccsm[2] & 0x01) != 0;
				device.bReadCDRW  = (ccsm[2] & 0x02) != 0;
				device.bReadDVDROM  = (ccsm[2] & 0x08) != 0;
				device.bReadDVDR  = (ccsm[2] & 0x10) != 0;
				device.bReadDVDRAM  = (ccsm[2] & 0x20) != 0;

				device.bWriteCDR  = (ccsm[3] & 0x01) != 0;
				device.bWriteCDRW = (ccsm[3] & 0x02) != 0;
				device.bTestWrite = (ccsm[3] & 0x04) != 0;
				device.bWriteDVDR = (ccsm[3] & 0x10) != 0;
				device.bWriteDVDRAM = (ccsm[3] & 0x20) != 0;
				
				BOOL bJustLink = false;
				if (GetRicohModePageInfo(device, bJustLink) == 0)
				{
					device.bJustlink = bJustLink;
				}
				else
					device.bJustlink = (ccsm[4] & 0x80) != 0;

				device.nMaxReadSpeed  = ((DWORD)ccsm[8] << 8) + (DWORD)ccsm[9];
				device.nMaxWriteSpeed = ((DWORD)ccsm[18] << 8) + (DWORD)ccsm[19];
				device.nCurReadSpeed  = ((DWORD)ccsm[14] << 8) + (DWORD)ccsm[15];
				device.nCurWriteSpeed = ((DWORD)ccsm[20] << 8) + (DWORD)ccsm[21];
				
				device.nBufferSize = ((DWORD)ccsm[12] << 8) + (DWORD)ccsm[13];
			//	pCur = pMax;
 			break;
 			}
			
			if (bModePageFound) break;

 			pCur += (pCur[1] + 2);
		 }
	}
	catch(...)
	{
		CHelper::Trace("UpdateDeviceInfo: crash while checking mode page\n");
	}
	
	if (bModePageFound == false)
	{
		CHelper::Trace("CSCSI::UpdateDeviceInfo - CD-R caps page not found\n");
		return -1;
	}

	CHelper::Trace("CSCSI::UpdateDeviceInfo exit\n");
	return 0;
}

int CSCSI::SendCueSheet(SCSIDEVICE &device, BYTE *pBuffer, long nLen)
{
	BYTE cdb[10] = {0x5D, 0};
	cdb[6]     = (BYTE)(nLen >> 16); //buflen msb
	cdb[7]     = (BYTE)(nLen >> 8); //buflen msb
	cdb[8]     = (BYTE)nLen; //buflen lsb
	
	int iError = ExecSCSICommand(device, 10, cdb, INFINITE, pBuffer, nLen, SRB_DIR_OUT);
	if (iError)
	{
		return iError;
	}

	return 0;
}


int CSCSI::GetRicohModePageInfo(SCSIDEVICE &device, BOOL &bJustlink)
{
	CHelper::Trace("CSCSI::GetRicohModePageInfo - about to check if it has ricoh mode page\n");

	BYTE cdb[24] = {0x5A, 0, 0x30, 0, 0, 0, 0, 0x01, 0x00};
 	BYTE buf[256] = {0xFF};
 
 	int iResult = ExecSCSICommand(device,  12, cdb, DEFWAITLEN, buf, 256, SRB_DIR_IN);
 	if (iResult)
	{
		CHelper::Trace("CSCSI::GetRicohModePageInfo - getting mode page failed\n");
 		return iResult;
	}

	int lenData = ((unsigned int)buf[0] << 8) + buf[1];
	if (lenData < 10)
		return -1;

	typedef BYTE RicohPage[14];
	RicohPage ricohPage;

	// set to first sense mask, and then walk through the masks
 	BYTE* pCur = buf + 8;
 	BYTE* pMax = buf + 256;
 
 	while( (pCur < &(buf[2+lenData])) && (pCur < pMax) )
	{
 		BYTE which;

 		which = pCur[0] & 0x3F;
 		switch( which )
 		{
 		case 0x30:
			
			long nLen = pCur[1]+2 <= 12 ? pCur[1]+2 : 12;
			memcpy(&ricohPage, pCur, nLen);
			
			bJustlink = (ricohPage[2] & 0x01) != 0;

			CHelper::Trace("CSCSI::GetRicohModePageInfo - mode page found. Justlink Enabled=%lu\n", bJustlink);

			break;
		}

		pCur += (pCur[1] + 2);
	}
	
	return 0;
}

int CSCSI::UpdateDeviceSpeeds(SCSIDEVICE &device)
{
	CDRomCapabilitiesStatusMask ccsm;

	long nDataLen = 256;
	BYTE buf[256] = {0};
	BYTE cdb[10] = {0x5A, 0, 0x3F, 0, 0, 0, 0, (BYTE)(nDataLen >> 8), (BYTE)nDataLen, 0};
 	
 	int iResult = ExecSCSICommand(device, 10, cdb, DEFWAITLEN, buf, 256, SRB_DIR_IN);				
 	if (iResult) {
 		return iResult;
	}
	
 	int lenData = ((unsigned int)buf[0] << 8) + buf[1];

 	BYTE* pCur = buf + 8;
 	BYTE* pMax = buf + 256;
 	
	bool bModePageFound = false;
	while( (pCur < &(buf[2+lenData])) && (pCur < pMax) )
	 {
 		BYTE which;

 		which = pCur[0] & 0x3F;
 		switch( which )
 		{
		case CDRCAPS:

			long nLen = pCur[1]+2 <= 23 ? pCur[1]+2 : 23;

			memcpy(ccsm, pCur, nLen);
			
			device.nMaxReadSpeed  = ((DWORD)ccsm[8] << 8) + (DWORD)ccsm[9];
			device.nMaxWriteSpeed = ((DWORD)ccsm[18] << 8) + (DWORD)ccsm[19];
			device.nCurReadSpeed  = ((DWORD)ccsm[14] << 8) + (DWORD)ccsm[15];
			device.nCurWriteSpeed = ((DWORD)ccsm[20] << 8) + (DWORD)ccsm[21];
			bModePageFound = true;
 		break;
 		}
		
		if (bModePageFound) break;

 		pCur += (pCur[1] + 2);
	 }

	return 0;
}

int CSCSI::ReadBlock(SCSIDEVICE &device, BYTE *ptr, long nBlocksToRead, long nBytesToRead, long nStartLBA)
{
	CHelper::Trace("\nCSCSI::ReadBlock entry\n");
	
	BYTE cdb[10] = {0x28, 0};

	cdb[2]     = (BYTE)(nStartLBA >> 3*8);
	cdb[3]     = (BYTE)(nStartLBA >> 2*8);
	cdb[4]     = (BYTE)(nStartLBA >> 1*8);
	cdb[5]     = (BYTE)(nStartLBA >> 0*8);
	cdb[6]     = (BYTE)(nBlocksToRead >> 16); // len msb
	cdb[7]     = (BYTE)(nBlocksToRead >> 8); // len msb
	cdb[8]     = (BYTE)(nBlocksToRead & 0xff); // len lsb
	cdb[9]     = 0xF0;

	int iError = ExecSCSICommand(device, 10, cdb, DEFWAITLEN, ptr, nBytesToRead, SRB_DIR_IN);
	if (iError)
	{
		CHelper::Trace("ReadBlock failed with return value=%d\n", iError);
		return iError;
	}

	return 0;
}

int CSCSI::SetBlockSize(SCSIDEVICE &device, long nBlockSize, unsigned char cDensity, bool bMode)
{
	// from dao, whai axe whai?
	BYTE cdb[10] = {0};
	cdb[0] = 0x15; // MODE SELECT6

	if (bMode == false)
	{
		BYTE init1[] = { 0, 0, 0, 0x08, 0, 0, 0, 0, 0, 0, 0x09, 0x30, 0x23, 6, 0, 0, 0, 0, 0, 0x80 };
		BYTE init2[] = { 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 9, 48, 1, 6, 32, 7, 0, 0, 0, 0 };
		
		cdb[1] = 0x10; // no save
		cdb[4] = 0x14;

		for (int i=0; i<2; i++)
		{
			int iError = ExecSCSICommand(device, 6, cdb, INFINITE, i == 0 ? init1 : init2, 0x14, 0);
			if (iError)
			{
				CHelper::Trace("SetBlockSize failed with return value=%d\n", iError);
				return iError;
			}
		}
	}
	else
	{
		BYTE init[16] = {0, 0, 0, 8, cDensity};
		init[10] = (BYTE)(nBlockSize >> 8);
		init[11] = (BYTE)(nBlockSize);

		cdb[4] = 12;

		int iError = ExecSCSICommand(device, 6, cdb, INFINITE, init, 12, 0);
		if (iError)
		{
			CHelper::Trace("SetBlockSize failed with return value=%d\n", iError);
			return iError;
		}
	}

	return 0;
}

int CSCSI::ReadTOC(SCSIDEVICE &device, long * pnLastSessionStartLBA, long * pnTrackCount)
{
	BYTE cdb[10] = {0};
	BYTE data[12] = {0};

	cdb[0] = 0x43;
	cdb[8] = 12;
	
	if (pnLastSessionStartLBA)
	{
		cdb[2] = 1;

		int iError = ExecSCSICommand(device, 10, cdb, INFINITE, data, 12, SRB_DIR_IN);
		if (iError)
			return iError;
		
		*pnLastSessionStartLBA = (data[8] << 24) | (data[9] << 16) | (data[10] << 8) | data[11];
	}

	if (pnTrackCount)
	{
		cdb[2] = 0;

		int iError = ExecSCSICommand(device, 10, cdb, INFINITE, data, 12, SRB_DIR_IN);
		if (iError)
			return iError;
		
		*pnTrackCount = data[3];
	}

	return 0;
}

int CSCSI::GetSpeedsMMC4(SCSIDEVICE &device)
{
	CHelper::Trace("GetSpeedsMMC4\n");

	long nLen = 640;
	long nMaxDesc = 40;
	BYTE data[640] = {0};
	memset(data, 0, nLen);

	BYTE cdb[12] = {0};
	memset(cdb, 0, 12);

	cdb[0] = 0xAC;
	cdb[8] = (BYTE)(nMaxDesc >> 8);
	cdb[9] = (BYTE)nMaxDesc;
	cdb[10] = 0x03; // write speed desc
	
	int iError = ExecSCSICommand(device, 12, cdb, INFINITE, data, nLen, SRB_DIR_IN);
	if (iError)
	{
		CHelper::Trace("GetSpeedsMMC4 FAILED\n");
		return iError;
	}
	
	long nSize = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];

	nSize -= 4; // 4 bytes of the header are added to this

	CHelper::Trace("GetSpeedsMMC4 okay. nSize=%lu\n", nSize);

	device.arrSupportedWriteSpeeds.RemoveAll();
	device.arrSupportedWriteSpeedsKB.RemoveAll();

	// write speed block is 16 bytes!
	for (int i=8;i<nSize;i+=16)
	{
		long nReadSpeed = (data[i+8] << 24) | (data[i+9] << 16) | (data[i+10] << 8) | data[11];
		long nWriteSpeed = (data[i+12] << 24) | (data[i+13] << 16) | (data[i+14] << 8) | data[15];
		
		if (nWriteSpeed > (device.nMaxWriteSpeed + 176))
			continue;

		long multSpeed = KBSpeedToMultipleSpeed(nWriteSpeed);

		device.arrSupportedWriteSpeeds.Add(multSpeed);
		device.arrSupportedWriteSpeedsKB.Add(nWriteSpeed);

		if (data[i] & 0x10)
			CHelper::Trace("Notesure bit = true\n");
		else
			CHelper::Trace("Notesure bit = false\n");

		CHelper::Trace("Speeds reported. Write=%lu, Read=%lu\n", nWriteSpeed, nReadSpeed);
	}

	// add the max speed, in case it is not already in

	long multSpeed = KBSpeedToMultipleSpeed(device.nMaxWriteSpeed);

	for (i=0;i<device.arrSupportedWriteSpeeds.GetSize();i++)
	{
		if (device.arrSupportedWriteSpeeds.GetAt(i) == multSpeed)
		{
			device.arrSupportedWriteSpeeds.RemoveAt(i);
			device.arrSupportedWriteSpeedsKB.RemoveAt(i);
			break;
		}
	}

	CHelper::Trace("GetSpeedsMMC4 adding max=%lu, %lu\n", multSpeed, device.nMaxWriteSpeed);
	device.arrSupportedWriteSpeeds.Add(multSpeed);
	device.arrSupportedWriteSpeedsKB.Add(device.nMaxWriteSpeed);

	if (device.arrSupportedWriteSpeeds.GetSize() == 0)
	{
		// in this case, we did not receive any speed. Samsung does this.

	}

	if (device.arrSupportedWriteSpeeds.GetSize() > 1)
	{
		// sort the speeds
		qsort(device.arrSupportedWriteSpeeds.GetData(), 
			  device.arrSupportedWriteSpeeds.GetSize(),
			  sizeof(long), DigitSortProc);

		qsort(device.arrSupportedWriteSpeedsKB.GetData(), 
			  device.arrSupportedWriteSpeedsKB.GetSize(),
			  sizeof(long), DigitSortProc);
	}

	return 0;
}

int CSCSI::ScanWriteSpeeds(SCSIDEVICE &device)
{
	if (device.bWriteCDR == false && device.bWriteCDRW == false)
		return -1;

	// try the new command set
	int nResult = GetSpeedsMMC4(device);
	if (nResult == 0 && device.arrSupportedWriteSpeedsKB.GetSize() >= 2)
		return 0;

	CHelper::Trace("CSCSI::UpdateDeviceInfo - Scanning write speeds : Max speed=%lu, Cur Speed=%lu\n", device.nMaxWriteSpeed, device.nCurWriteSpeed);

	WaitForDeviceReady(device);
			
	device.arrSupportedWriteSpeeds.RemoveAll();
	device.arrSupportedWriteSpeedsKB.RemoveAll();

	CHelper::Trace("CSCSI::UpdateDeviceInfo - Scanning speeds: \n");
	CHelper::LogTimeStamp(false);
	CHelper::Trace("--------------------------->>>\n");

	// scan the speeds
	for (int multSpeed = KBSpeedToMultipleSpeed(device.nMaxWriteSpeed); multSpeed >= 1; multSpeed-- )
	{
		long kbSpeed = multSpeed * 176;
		long nSpeed = 0;

		if (multSpeed == KBSpeedToMultipleSpeed(device.nMaxWriteSpeed))
			kbSpeed = device.nMaxWriteSpeed;
 		
		CHelper::Trace("%lu:", multSpeed);
		
		// try testunitready here
	/*	if (WaitForDeviceReady(device) != 0)
		{
			// the there is no cd in the drive. The samsung needs this
			// hack to display write speeds when there is no cd in drive
			
			CHelper::Trace("Cheating to get the write speed! Adding 2 multiple!\n");
			if (multSpeed % 2 == 0)
			{
				device.arrSupportedWriteSpeeds.Add(multSpeed);
				device.arrSupportedWriteSpeedsKB.Add(kbSpeed);

				CHelper::Trace("Adding Speeds=%lu, %lu\n", multSpeed, kbSpeed);
			}
		}
		else*/
		{

			// We are starting from the highest support speed in multiple, and
			// going down to the lowest. We test if the drive accepts the speed
			int iError = SetSpeed(device, &device.nCurReadSpeed, &kbSpeed);
			if (iError == 0)
			{	
				bool bFound = false;

				// check what speed got set
				UpdateDeviceSpeeds(device);
				nSpeed = device.nCurWriteSpeed / 176;

				// make sure the speed isn't already there
				for (int i=0;i<device.arrSupportedWriteSpeeds.GetSize();i++)
					if (device.arrSupportedWriteSpeeds.GetAt(i) == nSpeed)
					{
						bFound = true;
						device.arrSupportedWriteSpeeds.RemoveAt(i);
						device.arrSupportedWriteSpeedsKB.RemoveAt(i);
					}
						
				// Add speed to array
				device.arrSupportedWriteSpeeds.Add(nSpeed);
				device.arrSupportedWriteSpeedsKB.Add(device.nCurWriteSpeed);
				
				if (bFound)
					CHelper::Trace("no, ");
				else
					CHelper::Trace("yes, ");
			}
			else
			{
				CHelper::Trace("no\n");
			}
		} // if else

	} // for
	
	CHelper::Trace("\n");

		
	if (device.arrSupportedWriteSpeeds.GetSize() == 0)
	{
		// in this case, we did not receive any speed. Samsung does this.
		CHelper::Trace("No write speeds!\n");

	}

	if (device.arrSupportedWriteSpeeds.GetSize() > 1)
	{
		// sort the speeds
		qsort(device.arrSupportedWriteSpeeds.GetData(), 
			  device.arrSupportedWriteSpeeds.GetSize(),
			  sizeof(long), DigitSortProc);

		qsort(device.arrSupportedWriteSpeedsKB.GetData(), 
			  device.arrSupportedWriteSpeedsKB.GetSize(),
			  sizeof(long), DigitSortProc);
	}
	
	CHelper::Trace("--------------------------->>>\n");
	CHelper::LogTimeStamp(true);

	return 0;
}

int CSCSI::WaitForDeviceReady(SCSIDEVICE &device)
{
	CHelper::Trace("WaitForDeviceReady\n");

	int iError = SetSpeed(device, &device.nCurReadSpeed, &device.nCurWriteSpeed);
	if (iError != 0)
	{
		CHelper::Trace("CSCSI::UpdateDeviceInfo - Device busy. Waiting for SetSpeed to work\n");

		// Set speed fails, implying the device is busy
		int iRetry = 6;
		while (TestUnitReady(device, false) != 0 && iRetry) {
			Sleep(1000); iRetry--; }
	}

	CHelper::Trace("WaitForDeviceReady complete. iError=%lu\n", iError);
	return iError;
}

int CSCSI::ScanReadSpeeds(SCSIDEVICE &device)
{
	CHelper::Trace("CSCSI::UpdateDeviceInfo - Starting read speed scan\n");

	WaitForDeviceReady(device);
		
	CHelper::Trace("CSCSI::UpdateDeviceInfo - looping through available speed range. Max=%lu, Cur=%lu\n", device.nMaxReadSpeed, device.nCurReadSpeed);
	CHelper::LogTimeStamp(false);

	device.arrSupportedReadSpeeds.RemoveAll();
		
	// scan the speeds
	for (int multSpeed = KBSpeedToMultipleSpeed(device.nMaxReadSpeed); multSpeed >= 1; multSpeed-- )
	{
		long kbSpeed = multSpeed * 176;
		long nSpeed = 0;

		if (multSpeed == KBSpeedToMultipleSpeed(device.nMaxReadSpeed))
			kbSpeed = device.nMaxReadSpeed;
 			
		// We are starting from the highest support speed in multiple, and
		// going down to the lowest. We test if the drive accepts the speed
		if (TestUnitReady(device, true) != 0)
		{
			// the there is no cd in the drive. The samsung needs this
			// hack to display write speeds when there is no cd in drive
			
			if (multSpeed % 2 == 0)
			{
				device.arrSupportedReadSpeeds.Add(multSpeed);
			}
		}
		else
		{
			int iError = SetSpeed(device, &kbSpeed, &device.nCurWriteSpeed);
			if (iError == 0)
			{
				// check what speed got set
				UpdateDeviceSpeeds(device);
				nSpeed = device.nCurReadSpeed / 176;

				// make sure the speed isn't already there
				for (int i=0;i<device.arrSupportedReadSpeeds.GetSize();i++)
					if (device.arrSupportedReadSpeeds.GetAt(i) == nSpeed) 
						device.arrSupportedReadSpeeds.RemoveAt(i);

				// Add speed to array
				device.arrSupportedReadSpeeds.Add(nSpeed);
			}
		}
	} // for
		
	if (device.arrSupportedReadSpeeds.GetSize() > 1)
	{
		// sort the speeds
		qsort(device.arrSupportedReadSpeeds.GetData(), 
			  device.arrSupportedReadSpeeds.GetSize(),
			  sizeof(long), DigitSortProc);
	}
	
	CHelper::LogTimeStamp(true);
	return 0;
}