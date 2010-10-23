// SCSI.h: Schnittstelle für die Klasse CSCSI.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCSI_H__812A45F1_7F81_4FFA_8FDF_D76E150400E1__INCLUDED_)
#define AFX_SCSI_H__812A45F1_7F81_4FFA_8FDF_D76E150400E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ASPI.h"
#include "SPTI.h"
#include "discwriterdefs.h"

enum DiscInfo
{
	InfoCDRW,
	InfoCDR,
	InfoCD,
	InfoCDI,
	InfoCDXA,
	InfoUnknown,
	InfoEmpty,
	InfoOpen,
	InfoClosed
};

struct SCSIDEVICE
{
	// item identification values
	BYTE ha;
	BYTE tgt;
	BYTE lun;
	HANDLE hDrive;
	char cLetter;

	// is valid?
	BOOL bIsValid;

	// item description
	char szID[MAXIDLEN + 1];
	char szVendor[9];
	char szProdId[17];
	char szRev[5];
	char szVendSpec[21];
	char szAdapter[64];

	// speed arrays
	CArray<long, long> arrSupportedWriteSpeeds;
	CArray<long, long> arrSupportedWriteSpeedsKB;
	CArray<long, long> arrSupportedReadSpeeds;

	// read capabilites
	BOOL bReadCDR;
	BOOL bReadCDRW;
	BOOL bReadDVDROM;
	BOOL bReadDVDR;
	BOOL bReadDVDRAM;

	// write capabilities
	BOOL bWriteCDR;
	BOOL bWriteCDRW;
	BOOL bWriteDVDR;
	BOOL bWriteDVDRAM;

	BOOL bJustlink;
	BOOL bTestWrite;
    
	// other capabilities
	long nMaxWriteSpeed;
	long nCurWriteSpeed;
	long nCurReadSpeed;
	long nMaxReadSpeed;

	long nBufferSize;	
};

typedef BYTE CDRomCapabilitiesStatusMask[23];

class CSCSI  
{
public:	
	CSCSI();
	virtual ~CSCSI();
	
	void EndCommunication();
	int  InitCommunication(CArray<SCSIDEVICE*, SCSIDEVICE*>* arrCDR, bool bUseASPI);
	int  ReadTOC(SCSIDEVICE & device, long * pnLastSessionStartLBA, long * pnTrackCount);
	int  SetBlockSize(SCSIDEVICE &device, long nBlockSize, unsigned char cDensity, bool bMode);
	int  ReadBlock(SCSIDEVICE & device, BYTE* ptr, long nBlocksToRead, long nBytesToRead, long nStartLBA);
	int  UpdateDeviceSpeeds(SCSIDEVICE & device);
	void TranslateError(int iError, char* pszBuffer);
	int  PerformOPC(SCSIDEVICE & device);
	int  StartEraseDisc(SCSIDEVICE & device, bool bQuickErase);
	int  ReadTrackInfo(SCSIDEVICE &device, int nTrack, bool * pbDamage, long * pnTrackMode,  long * pnTrackStart, long * pnNextWriteAddr, long * pnTrackSize);
	int  ReadDiscInformation(SCSIDEVICE & device, long * pnDiskType, long * pnDiscState, long * pnSessionCount, long * pnLastSessionStartLBA);
	int  CloseTrackOrSession(SCSIDEVICE & device, bool bCloseSession, int nTrackNumber);
	int  EjectDevice(SCSIDEVICE & device, bool bEject);
	int  GetModePage(SCSIDEVICE & device, int pageCode, BYTE* pModePage, BYTE* pModePageHeader, BYTE* pBlockDesc, long nPageBufLen);
	int  ReadBufferCapacity(SCSIDEVICE & device, long &nLength, long &nBlank);
	int  SynchronizeCache(SCSIDEVICE & device);
	int  WriteBlock(SCSIDEVICE & device, BYTE* ptr, long nBlocksToWrite, long nBytesToWrite, long nStartLBA);
	int  TestUnitReady(SCSIDEVICE & device, bool bTestReadDiscInfo);
	int  SendModePage(SCSIDEVICE & device, BYTE* pModePage, BYTE* pModePageHeader, BYTE* pBlockDesc);
	
	int  ReadDiscCapacity(SCSIDEVICE & device, long &nLength, long &nMin, long &nSec);
	int  SetSpeed(SCSIDEVICE & device, long * nReadSpeed, long * nWriteSpeed);
	int  ReadDiscSize(SCSIDEVICE &device, long &nLength);
	int  ReadDeviceName(SCSIDEVICE &device);
	int  SendCueSheet(SCSIDEVICE &device, BYTE* pBuffer, long nLen);
	int  UpdateDeviceInfo(SCSIDEVICE & device, bool bScanWriteSpeeds, bool bScanReadSpeeds);
	int  GetRicohModePageInfo(SCSIDEVICE & device, BOOL & bJustlink);

	int ScanReadSpeeds(SCSIDEVICE &device);
	int WaitForDeviceReady(SCSIDEVICE& device);
	int ScanWriteSpeeds(SCSIDEVICE& device);
	int GetSpeedsMMC4(SCSIDEVICE &device);

protected:
	int  ExecSCSICommand(SCSIDEVICE &device, BYTE cdblen, BYTE * pcdbbyte, DWORD dwWait, BYTE* pBuf, int nBufLen, int nDirection);
	int  ScsiIoError(int aspi_status, int adapter_status, int target_status, unsigned char* sense);
	static int DigitSortProc(const void *arg1,  const void *arg2);
	void RemoveDoubleCharFromString(char* pstr, char cToRemove);
	long MSFToLBA(int min, int sec, int frac);
	
	int  Round( float num );
	int  ResetSCSIBus(SCSIDEVICE & device);
	
	int  KBSpeedToMultipleSpeed(int nKB);

private:
	bool m_bUseASPI;
	CASPI m_aspi;
	CSPTI m_spti;
};

#endif // !defined(AFX_SCSI_H__812A45F1_7F81_4FFA_8FDF_D76E150400E1__INCLUDED_)
