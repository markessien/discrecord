// CDWriter.h: Schnittstelle für die Klasse CDiscWriter.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CDWRITER_H__77F89A4A_BCEF_4C3B_8204_8B74219FD654__INCLUDED_)
#define AFX_CDWRITER_H__77F89A4A_BCEF_4C3B_8204_8B74219FD654__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "scsi.h"
#include <time.h>
#include "discreader.h"

class CDisc;
class CDiscParser;

#define WM_STATUSCHANGE WM_APP + 13
#define WM_COMPLETE WM_APP + 14

class CDiscWriter : public IDiscReader
{
public:
	long GetWriteSpeedKB(int iIndex);
	void AbortRead();
	CDiscWriter(ICallback* pCallback);
	virtual ~CDiscWriter();
	
	void UnInit();
	bool IsInited();
	bool CopyDisc(long nSourceDeviceIndex, char* pstrTargetFile);
	bool CheckEraseComplete();
	void SetAudioPause(long nPause);
	long GetAudioPause();
	int  StartDiscErase(bool bQuickErase);
	bool GetBurnProof();
	int  ReadFileBufferInfo(long & nValid, long & nSize);
	long GetCurrentLBA();
	long GetCurrentTrack();
	long GetDiscCapacitySecs();
	void EnableBurnProof(bool bEnable);
	char GetDriveLetter();
	void SetEjectWhenDone(bool bEject);
	bool GetEjectWhenDone();
	long GetDiscSize();
	bool AbortWrite();
	bool Initialize(bool bUseAspi);
	bool RescanCDWriterDevices();
	bool WriteDisc(CDisc* discToWrite);
	int  GetCurrentDeviceIndex();
	bool SetCurrentDeviceIndex(int iNewIndex);
	long GetCurrentReadSpeed();
	bool SetCurrentWriteSpeed(long nFactor);
	long GetWriteSpeed(int iIndex);
	long GetWriteSpeedCount();
	long GetReadSpeed(int iIndex);
	bool SetCurrentReadSpeed(long nFactor);
	long GetReadSpeedCount();
	long GetCurrentWriteSpeed();
	long GetDiscCapacity();
	bool GetBufferInfo(long & lSize, long & lFree);
	void EjectDevice(bool bEject);
	void SetTestMode(bool bTestMode);
	bool GetTestMode();
	long GetDeviceCount();
	void SetWriteType(EnumWriteType eWriteType);
	void SetCloseSession(bool bValue);
	bool GetCloseSession();

	LPCTSTR GetCurrentStatus();
	EnumWriteType GetWriteType();
	EnumDiscType GetDiscType();
	EnumDiscState GetDiscState();
	SCSIDEVICE* GetDevice(int iIndex);
	SCSIDEVICE & GetCurrentDevice();
	CDiscParser* GetDiscParser();

	double GetDurationTime();
	double GetProgressTime();
	double GetTimeElapsed();
	double GetProgress();
	double GetDuration();

	// idiscreader implementation
	bool ReadFromDisc(BYTE* pBuffer, long nStartLBA, long nBlockLen, bool bFromWriter);
	bool InitDiscRead(long nMode);
	long GetLastSessionLBA();

private:
	static DWORD __stdcall WriteDiscThreadEntry(LPVOID lpvThreadParm);
	static DWORD __stdcall CopyDiscThreadEntry(LPVOID lpvThreadParm);

	static BOOL NotifyFunc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, long pClass);
	void ChangeStatus(char* pstrNewStatus, Status status, StatusType statusType);
	void WriteDisc();
	void SetModePageParameters(BYTE pModePage[], int nTrack);
	int  WriteTAO(long blockCount, BYTE* pBuffer);
	bool ZeroAlignBuffer(BYTE* pBuffer, long & blockCount, long &lRead);
	int  GetNextWriteAddress();
	bool SendWriteModePage();
	void DestroyCDRList();
	int  WriteSAO(long blockCount, BYTE* pBuffer);
	void CopyDisc();
	void BaseStringToIndexedString(char *pstrSource, char* pstrTarget, int nIndex);
	int  WriteByte(int nBlockCount, int nStartLBA, BYTE cToWrite, BOOL bRetry);

private:
	
	ICallback* m_pCallback;

	CDisc*  m_discToWrite;
	CSCSI m_scsi;
	SCSIDEVICE m_devicenull;
	CNotifyWindow m_wndNotify;
	CDiscParser* m_pDiscParser;

	Status m_status;
	StatusType m_statusType;
	CString m_strStatus;

	CArray<SCSIDEVICE*, SCSIDEVICE*> m_cdrList;
	
	WriteType m_eWriteType;
	long m_nAudioPause;
	bool m_bInWrite;
	long m_nDrvBufLen;
	long m_nDrvBufBlank;
	long m_nCurTrack;
	long m_nCurLBA;
	long m_nCopyDeviceIndex;
	int  m_iDeviceCount;
	int  m_iCurrentDevice;
	bool m_bTestMode;
	bool m_bInited; // important, so we don't query device before init
	char m_szISOFile[MAX_PATH];
	double m_dDuration;
	double m_dProgress;
	long m_arrSpeedsMultiple[50];
	long m_arrSpeedsKiloByte[50];
	bool m_bAbortWrite;
	bool m_bEjectWhenDone;
	bool m_bBurnproof;
	bool m_bCloseSession;
	bool m_bAbortRead;
	time_t m_tStartTime;
	time_t m_tEraseStart;
};

#endif // !defined(AFX_CDWRITER_H__77F89A4A_BCEF_4C3B_8204_8B74219FD654__INCLUDED_)
