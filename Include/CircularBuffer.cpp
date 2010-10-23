// CircularBuffer.cpp: Implementierung der Klasse CCircularBuffer.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CircularBuffer.h"

#define HALF(x) x/2
// The circular buffer is a bufe
//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CCircularBuffer::CCircularBuffer()
{
	m_bNoMoreInput = false;
	m_nValidBytesInBuffer = 0;
	m_nReadPos = 0;
	m_nWritePos = 0;
	m_hFile = INVALID_HANDLE_VALUE;
	m_nBufferLen = 0;
	m_bWaitingAtHalf = false;
	m_bWaitingAtBridge = false;
	m_bAbort = false;
	m_pBuffer = NULL;
	m_bToFile = true;
	m_nBufferLen = 1024*1024*10; // 10MB
	
	strcpy(m_szFile, "");

	InitializeCriticalSection(&m_crit); 
}

CCircularBuffer::~CCircularBuffer()
{

}

bool CCircularBuffer::AddData(BYTE *pBuffer, long &nLen)
{
	CHelper::Trace("CCircularBuffer::AddData: nLen=%d, cur valid=%d, +this=%d\n", nLen, m_nValidBytesInBuffer, m_nValidBytesInBuffer + nLen);

//	_ASSERT(m_bNoMoreInput == false);
	if (m_bNoMoreInput || m_bAbort)
	{
		circ_trace("CCircularBuffer::AddData returns false\n");
		return false;
	}
	
//	circ_trace("CCircularBuffer::AddData going on\n");

	// nlen is a maximum at 1/4 of the buffer len
	_ASSERT(nLen < m_nBufferLen / 4);
	_ASSERT(m_hFile != INVALID_HANDLE_VALUE);

	if (m_bToFile)
    {
		// If the write position + the length we are to write exceeds 
		// the length we are to write.
		if (m_nWritePos + nLen > m_nBufferLen)
		{
			// we check if the read is already at at least the half mark
			// Once it is past the half mark, we can begin to write to the
			// first half. We do not just write to make the read process steady
			// and faster.
		
			circ_trace("Write would exceed bridge!\n");
			
			if (m_nWritePos < m_nBufferLen)
			{
				// this implies that there is still small space
				// at the end of our buffer. We copy some part
				// of our data in
				
				circ_trace("Stuffing bridge!\n");

				EnterCriticalSection(&m_crit);

				if (m_hFile == INVALID_HANDLE_VALUE)
				{
					LeaveCriticalSection(&m_crit);
					return false;
				}
				
				if (m_bAbort)
				{
					LeaveCriticalSection(&m_crit);
					return false;
				}
				
				long nToWrite = m_nBufferLen - m_nWritePos;
				DWORD dwWritten = 0;
				::SetFilePointer(m_hFile, m_nWritePos, 0, FILE_BEGIN);
				::WriteFile(m_hFile, pBuffer, nToWrite, &dwWritten, 0);
				m_nWritePos+=dwWritten;
				m_nValidBytesInBuffer+=dwWritten;
				
				_ASSERT(nToWrite == (long)dwWritten);

				// we set our buffer so the next write won't be confused
				pBuffer = &pBuffer[dwWritten];
				nLen += dwWritten;

				LeaveCriticalSection(&m_crit);
			}

			while (m_nReadPos <  HALF(m_nBufferLen))
			{
				// sync read is locked and unlocked every time
				// data is read, so we can use as notification
				// every time data is read. It's better than Sleep()ing
				
				circ_trace("At Bridge\n");

				m_bWaitingAtBridge = true;
				m_syncRead.WaitForLock(INFINITE);
				m_syncRead.WaitForUnlock(INFINITE);

				if (m_bAbort)
					break;
			}
			
			m_bWaitingAtBridge = false;

			if (m_bAbort)
				return false;

			// at this point, the first half of the file at least
			// is free for write

			_ASSERT(m_nReadPos >= HALF(m_nBufferLen)); // asserts!?
			_ASSERT(m_nReadPos < m_nBufferLen);

			// we set the pointers back
			m_nWritePos = 0;
		}
		
		// If the write position + the length we are about to write enters
		// the second half of the buffer. If it enters, we wait till it loops and
		// goes over to the second half
		if (m_nWritePos + nLen > HALF(m_nBufferLen) && m_nReadPos > HALF(m_nBufferLen))
		{
			circ_trace("Write would exceed half point and read is in second half!\n");

			while (m_nReadPos >  HALF(m_nBufferLen))
			{
				// sync read is locked and unlocked every time
				// data is read, so we can use as notification
				// every time data is read. It's better than Sleep()ing
				m_bWaitingAtHalf = true;
				m_syncRead.WaitForUnlock(INFINITE);

				if (m_bAbort)
					break;
			}
			
			m_bWaitingAtHalf = false;

			if (m_bAbort)
				return false;

			_ASSERT(m_nReadPos < HALF(m_nBufferLen));
		}
		
//		circ_trace("CCircularBuffer::AddData about to touch crit\n");
		EnterCriticalSection(&m_crit);

		if (m_hFile == INVALID_HANDLE_VALUE)
		{
			LeaveCriticalSection(&m_crit);
			return false;
		}
		
		if (m_bAbort)
		{
			LeaveCriticalSection(&m_crit);
			return false;
		}

		DWORD dwWritten = 0;
		::SetFilePointer(m_hFile, m_nWritePos, 0, FILE_BEGIN);
		::WriteFile(m_hFile, pBuffer, nLen, &dwWritten, 0);
		m_nWritePos+=dwWritten;
		m_nValidBytesInBuffer+=dwWritten;

		LeaveCriticalSection(&m_crit);

		return true;
	}
	else
	{
		circ_trace("CCircularBuffer::AddData buffer to MEMORY. NOT IMPLEMENTED\n");
	}
	
	circ_trace("CCircularBuffer::AddData did something whack\n");

	return false;
}

bool CCircularBuffer::ReadData(BYTE *pBuffer, long &nLen)
{
	EnterCriticalSection(&m_crit);
	
	m_syncRead.Lock();
	
	CHelper::Trace("CCircularBuffer::ReadData. Valid=%d\n", m_nValidBytesInBuffer);

	if (m_bAbort)
	{
		LeaveCriticalSection(&m_crit);
		return false;
	}
	
	if (m_bNoMoreInput == false && m_nValidBytesInBuffer <= (long)0)
	{
		// This implies that data is arriving too slowly. We wait for max
		// of 5 seconds
		CHelper::Trace("DATA ARRIVING TOO SLOW! Waiting. This will cause buffer underrun.\n");

		int iRetry = 100;
		while (iRetry)
		{
			if (m_nValidBytesInBuffer >= nLen) // enough data has arrived for at least one write.
				break;

			Sleep(100);
			iRetry--;

			CHelper::Trace("Waiting for data. retry=%lu\n", iRetry);
		}
	}

	if (m_nValidBytesInBuffer <= (long)0)
	{
		_ASSERT(m_nValidBytesInBuffer == 0);
		CHelper::Trace("\n\nI've run out of data to fead. ReadData return false! Valid=%d\n\n\n", m_nValidBytesInBuffer);
		LeaveCriticalSection(&m_crit);
		return false;
	}

	if (m_hFile == INVALID_HANDLE_VALUE)
	{
		circ_trace("ReadData return false because file closed\n");
		LeaveCriticalSection(&m_crit);
		return false;
	}
	 
	bool bResult = false;

	if (m_bToFile)
    {
		bResult = true;
		DWORD dwRead = 0;

		::SetFilePointer(m_hFile, m_nReadPos, 0, FILE_BEGIN);

		if (nLen > m_nValidBytesInBuffer) nLen = m_nValidBytesInBuffer;

		::ReadFile(m_hFile, pBuffer, nLen, &dwRead, 0);
		m_nReadPos += dwRead;	
		m_nValidBytesInBuffer -= dwRead;
		
		_ASSERT(m_nValidBytesInBuffer >= 0);

		if (m_nReadPos == m_nBufferLen)
		{
			CHelper::Trace("We have reached end of buffer, but have all the data we need.\n");
			CHelper::Trace("So we reset pointer to 0, and exit function\n");
			
			m_nReadPos = 0;
		}
		else if ((long)dwRead < nLen && m_nValidBytesInBuffer > 0)
		{
			CHelper::Trace("Less data read than we needed. dwRead=%d, nLen=%d, m_nReadPos=%d,m_nBufferLen=%d\n", dwRead, nLen, m_nReadPos, m_nBufferLen);

			// In this case, we read less data that we actually wanted
			// we reset our pointer back to the beginning of the file
			// and 
			m_nReadPos = 0;
			::SetFilePointer(m_hFile, m_nReadPos, 0, FILE_BEGIN);
			
			DWORD dwRead2 = 0;
			if ((long)dwRead < nLen)
			{
				long nRead2 = nLen - dwRead;

				if (nRead2 > m_nValidBytesInBuffer) nRead2 = m_nValidBytesInBuffer;
				
				::ReadFile(m_hFile, &pBuffer[dwRead], nRead2, &dwRead2, 0);
				m_nValidBytesInBuffer-= dwRead2;

				_ASSERT(m_nValidBytesInBuffer >= 0);
			}
			
			if (dwRead2 + dwRead == 0)
				bResult = false;
			else
				bResult = true;

			nLen = dwRead2 + dwRead;
		}
		else
			nLen = dwRead;
	}
	
	m_syncRead.Unlock();
	LeaveCriticalSection(&m_crit);
	
//	circ_trace("Exit CCircularBuffer::ReadData\n");

	return bResult;
}

void CCircularBuffer::Close()
{
	// This critical section will prevent us from entering
	// this function while either a write is occuring right now
	// or a read. It will not deadlock with the waits in the write
	// function because those waits are not affected by the crit
	
	circ_trace("CCircularBuffer::Close()\n");

	EnterCriticalSection(&m_crit);
	
	circ_trace("CCircularBuffer::Close() passed crit\n");

	if (m_bWaitingAtBridge || m_bWaitingAtHalf)
	{
		circ_trace("CCircularBuffer::Close() waiting at bridge or half\n");

		m_bAbort = true;
		
		while (m_bWaitingAtBridge || m_bWaitingAtHalf)
		{
			m_syncRead.Lock();
			m_syncRead.Unlock();
			Sleep(20);
		}

		m_bAbort = false;
	}
	
	circ_trace("CCircularBuffer::Close() closing and deleting file\n");
	
	if (m_hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hFile);
		m_hFile = INVALID_HANDLE_VALUE;
	}
	
	if (strcmp(m_szFile, "") != 0)
	{
		DeleteFile(m_szFile);
		strcpy(m_szFile, "");
	}
	
	if (m_pBuffer)
	{
		delete [] m_pBuffer;
		m_pBuffer = NULL;
	}
	
	IndicateNoMoreInput();

	circ_trace("CCircularBuffer::Close() exit\n");

	LeaveCriticalSection(&m_crit);
}

bool CCircularBuffer::Open(bool bBufferToFile, long nBufferLen)
{
	Close();
	
	CHelper::Trace("CCircularBuffer::Open ");

	m_bToFile = bBufferToFile;
	m_nBufferLen = nBufferLen;
	
	_ASSERT(m_bWaitingAtHalf == false);
	_ASSERT(m_bWaitingAtBridge == false);
	_ASSERT(m_hFile == INVALID_HANDLE_VALUE);
	_ASSERT(m_nValidBytesInBuffer == 0);

	m_bAbort = false;
	m_bWaitingAtHalf = false;
	m_bWaitingAtBridge = false;
	m_bNoMoreInput = false;
	m_nValidBytesInBuffer = 0;
	m_nWritePos = 0;
	m_nReadPos = 0;

	if (m_bToFile)
    {
		char szFile[MAX_PATH];
		GetTempPath(MAX_PATH, szFile);

		GetTempFileName(szFile, "drd", 0, m_szFile);
		
		CHelper::Trace(m_szFile);
		CHelper::Trace("\n");

		m_hFile = CreateFile(m_szFile, GENERIC_WRITE|GENERIC_READ,
							 FILE_SHARE_READ|FILE_SHARE_WRITE, 
							 0, CREATE_ALWAYS, 
							 FILE_ATTRIBUTE_TEMPORARY|FILE_FLAG_RANDOM_ACCESS, 0);

		if (m_hFile == INVALID_HANDLE_VALUE)
			return false;
	}
	else
	{
		m_pBuffer = new BYTE[m_nBufferLen];

		if (m_pBuffer == NULL)
			return false;
	}

	return true;
}

bool CCircularBuffer::IsOpen()
{
	return (m_hFile != INVALID_HANDLE_VALUE);
}

BOOL CCircularBuffer::IsBufferAtMax()
{
	if (m_bNoMoreInput)
	{
		circ_trace("Return IsBufferAtMax TRUE because no more input\n");
		return TRUE;
	}

	if (m_bWaitingAtBridge && m_nWritePos > HALF(m_nBufferLen))
	{
		circ_trace("Return IsBufferAtMax TRUE because at bridge and write pos in upper half\n");
		return TRUE;
	}

	return FALSE;
}

void CCircularBuffer::IndicateNoMoreInput()
{
	circ_trace("CCircularBuffer::NoMoreInput\n");
	m_bNoMoreInput = true;
}

long CCircularBuffer::GetBufferSize()
{
	return m_nBufferLen;
}

long CCircularBuffer::GetBufferValid()
{
	return m_nValidBytesInBuffer;
}
