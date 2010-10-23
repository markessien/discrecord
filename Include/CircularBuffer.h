// CircularBuffer.h: Schnittstelle für die Klasse CCircularBuffer.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CIRCULARBUFFER_H__343C2CD6_0CEF_4F7D_9173_3D38927BC342__INCLUDED_)
#define AFX_CIRCULARBUFFER_H__343C2CD6_0CEF_4F7D_9173_3D38927BC342__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SyncWait.h"
#include "helper.h"

//#define circ_trace(x) CHelper::Trace(x)
//#define circ_trace(x) OutputDebugString(x)
#define circ_trace

class CCircularBuffer  
{
public:
	long GetBufferValid();
	long GetBufferSize();
	void IndicateNoMoreInput();
	BOOL IsBufferAtMax();
	bool IsOpen();
	bool Open(bool bBufferToFile, long nBufferLen);
	void Close();
	CCircularBuffer();
	virtual ~CCircularBuffer();
	
	bool ReadData(BYTE* pBuffer, long &nLen);
	bool AddData(BYTE* pBuffer, long & nLen);

private:
	char m_szFile[MAX_PATH];
	bool m_bAbort;
	bool m_bWaitingAtHalf;
	bool m_bWaitingAtBridge;
	bool m_bNoMoreInput;
	CSyncWait m_syncRead;
	HANDLE m_hFile;
	BYTE* m_pBuffer;
	bool m_bToFile;
	long m_nBufferLen;
	long m_nValidBytesInBuffer;
	long m_nWritePos;
	long m_nReadPos;
	CRITICAL_SECTION m_crit;
};

#endif // !defined(AFX_CIRCULARBUFFER_H__343C2CD6_0CEF_4F7D_9173_3D38927BC342__INCLUDED_)
