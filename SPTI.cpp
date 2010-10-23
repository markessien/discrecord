// SPTI.cpp: Implementierung der Klasse CSPTI.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SPTI.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CSPTI::CSPTI()
{

}

CSPTI::~CSPTI()
{

}

long CSPTI::GetSupportInfo()
{
	return 0;
}

HANDLE CSPTI::OpenDrive( BYTE drvLetter )
{
	char buf[12];
	HANDLE fh;
	
	OSVERSIONINFO osver;
	DWORD dwFlags;

	ZeroMemory( &osver, sizeof(osver) );
	osver.dwOSVersionInfoSize = sizeof(osver);
	GetVersionEx( &osver );

	// if Win2K or greater, add GENERIC_WRITE
	dwFlags = GENERIC_READ;
	if ( (osver.dwPlatformId == VER_PLATFORM_WIN32_NT) &&
       (osver.dwMajorVersion > 4) )
    {
      dwFlags |= GENERIC_WRITE;
    }

	wsprintf( buf, "\\\\.\\%c:", (char)('A'+drvLetter) );

	fh = CreateFile( buf, dwFlags, FILE_SHARE_READ, NULL,
			OPEN_EXISTING, 0, NULL );

	if ( fh == INVALID_HANDLE_VALUE )
    {
		// it went foobar somewhere, so try it with the GENERIC_WRITE 
		// bit flipped
		dwFlags ^= GENERIC_WRITE;
		fh = CreateFile( buf, dwFlags, FILE_SHARE_READ, NULL,
			       OPEN_EXISTING, 0, NULL );
    }
	
	return fh;
}

DWORD CSPTI::ExecCommand(HANDLE hDrive, LPSRB_ExecSCSICmd lpsrb, DWORD dwTimeOut)
{
	ULONG length, returned;

	if (lpsrb->CDBByte[0] == 0x12)
	{
		 // INQUIRY is not supported by this function.
		_ASSERT(FALSE);
		return SS_COMP;
	}

	_ASSERT(hDrive != INVALID_HANDLE_VALUE);
	if (hDrive == INVALID_HANDLE_VALUE)
		return -5;
	
	// setup the pass through structure
	SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER swb;
	ZeroMemory( &swb, sizeof(swb) );
	
	swb.spt.Length = sizeof(SCSI_PASS_THROUGH);
	swb.spt.CdbLength = lpsrb->SRB_CDBLen;
	
	if ( lpsrb->SRB_Flags & SRB_DIR_IN )
		swb.spt.DataIn = SCSI_IOCTL_DATA_IN;
	else if ( lpsrb->SRB_Flags & SRB_DIR_OUT )
		swb.spt.DataIn = SCSI_IOCTL_DATA_OUT;
	else
		swb.spt.DataIn = SCSI_IOCTL_DATA_UNSPECIFIED;

	swb.spt.DataTransferLength = lpsrb->SRB_BufLen;
	
	if (dwTimeOut == INFINITE)
		swb.spt.TimeOutValue = 60 * 60; // 60minutes
	else
	{
		float fTimeOut = (float)dwTimeOut / 1000.0f;
		swb.spt.TimeOutValue      = (DWORD)fTimeOut;
	}

	swb.spt.DataBuffer        = lpsrb->SRB_BufPointer;
	swb.spt.SenseInfoOffset   =
    offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER, ucSenseBuf );
	memcpy( swb.spt.Cdb, lpsrb->CDBByte, lpsrb->SRB_CDBLen );
	length = sizeof(swb);
	
	BOOL bResult = FALSE;
	bResult = DeviceIoControl(hDrive,
			    IOCTL_SCSI_PASS_THROUGH_DIRECT,
			    &swb,
			    length,
			    &swb,
			    length,
			    &returned,
			    NULL );

	if (bResult)
    {
		lpsrb->SRB_Status = SS_COMP;
    }
	else
    {
		lpsrb->SRB_Status = SS_ERR;
		lpsrb->SRB_TargStat = 0x0004;

		if (RequestSense(hDrive, swb.ucSenseBuf))
		{
			lpsrb->SRB_TargStat = 0x0002;
			memcpy(lpsrb->SenseArea, swb.ucSenseBuf, 14);
		}
		
		DWORD dwErrCode;
		dwErrCode = GetLastError();
    }

	return lpsrb->SRB_Status;
}

bool CSPTI::RequestSense(HANDLE hDrive, BYTE* pSenseBuffer)
{
	SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER swb;
	ZeroMemory( &swb, sizeof(swb) );
	
	swb.spt.Length = sizeof(SCSI_PASS_THROUGH);
	swb.spt.CdbLength = 6;
	swb.spt.DataIn = SCSI_IOCTL_DATA_IN;
	swb.spt.DataTransferLength = 32;
	swb.spt.TimeOutValue = 2;
	swb.spt.DataBuffer = pSenseBuffer;
	swb.spt.SenseInfoOffset = offsetof(SCSI_PASS_THROUGH_DIRECT_WITH_BUFFER, ucSenseBuf);
	swb.spt.Cdb[0] = 0x03;
	swb.spt.Cdb[1] = 0;
	swb.spt.Cdb[2] = 0;
	swb.spt.Cdb[3] = 0;
	swb.spt.Cdb[4] = 32;
	swb.spt.Cdb[5] = 0;

	ULONG length, returned;
	length = sizeof(swb);
	
	BOOL bResult = FALSE;
	bResult = DeviceIoControl(hDrive,
			    IOCTL_SCSI_PASS_THROUGH_DIRECT,
			    &swb,
			    length,
			    &swb,
			    length,
			    &returned,
			    NULL );

	if (bResult)
    {
		return true;
    }
	
	return false;
}
