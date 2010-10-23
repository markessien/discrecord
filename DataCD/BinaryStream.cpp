// BinaryStream.cpp: Implementierung der Klasse CBinaryStream.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BinaryStream.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CBinaryStream::CBinaryStream() : //m_hFile(INVALID_HANDLE_VALUE),
								 m_pBuffer(NULL),
								 m_nBufLen(0),
								 m_nBufPos(0),
								 m_nCurSector(0),
								 m_nCurSectorPos(0)
{
	SetBufferSize(8*2048); // 8 * sector size
}

CBinaryStream::~CBinaryStream()
{
	_ASSERT(m_pBuffer == NULL);
//	_ASSERT(m_hFile == INVALID_HANDLE_VALUE);
}

bool CBinaryStream::Open(LPCTSTR lpszFileName)
{
	// Delete the file, because we always overwrite
//	DeleteFile(lpszFileName);
/*	
	if (m_hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hFile);
		m_hFile = INVALID_HANDLE_VALUE;
	}
*/
	ASSERT(lpszFileName == NULL); // we don't use this!

	m_nBufPos = 0;
	m_nCurSector = 0;
	m_nCurSectorPos = 0;
	
	if (m_pBuffer)
	{
		delete [] m_pBuffer;
		m_pBuffer = NULL;
	}

	m_fileBuffer.Open(true, 1024*1024*10); // 10meg file

	/*
	m_hFile = CreateFile(lpszFileName, GENERIC_WRITE,
                         FILE_SHARE_READ|FILE_SHARE_WRITE,
						 0, CREATE_ALWAYS, 0, 0);

	if (m_hFile == INVALID_HANDLE_VALUE)
    {
		_ASSERT(m_hFile != INVALID_HANDLE_VALUE);
        CHelper::Trace("CBinaryStream::Open: Could not open file for write!\n");
        return false;
    }
	*/
	// Create the buffer
	_ASSERT(m_nBufLen);
	_ASSERT(m_pBuffer == NULL);

	m_pBuffer = new BYTE[m_nBufLen];
	
	return true;
}

void CBinaryStream::Close()
{
	/*
	if (m_hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hFile);
		m_hFile = INVALID_HANDLE_VALUE;
	}
	*/

	m_fileBuffer.Close();

	if (m_pBuffer)
	{
		delete [] m_pBuffer;
		m_pBuffer = NULL;
	}
}

bool CBinaryStream::IsOpen()
{
//	_ASSERT(m_hFile);
//	return (m_hFile != INVALID_HANDLE_VALUE);
	return m_fileBuffer.IsOpen();
}

bool CBinaryStream::SetBufferSize(UINT nCount)
{
	// You can only change buffer size when file is closed
/*	
	if (m_hFile != INVALID_HANDLE_VALUE)
	{
		_ASSERT(FALSE);
		return false;
	}
	else
	*/
		m_nBufLen = nCount;

	
	return true;
}

bool CBinaryStream::WriteBigEndian(WORD x)
{
	WriteByte((BYTE)(x >> 8));
	return WriteByte((BYTE)x);
}

bool CBinaryStream::WriteBigEndian(DWORD x)
{
	WriteByte((BYTE)(x >> 24));
	WriteByte((BYTE)(x >> 16));
	WriteByte((BYTE)(x >> 8));
	return WriteByte((BYTE)x);
}

bool CBinaryStream::WriteBlock(BYTE value, UINT nCount)
{
	while (nCount != 0)
	{
	    WriteByte(value);
	    nCount--;
	}

	return true;
}

bool CBinaryStream::WriteBothEndian(WORD x)
{
	WriteLittleEndian(x);
	return WriteBigEndian(x);
}

bool CBinaryStream::WriteBothEndian(DWORD x)
{
	WriteLittleEndian(x);
	return WriteBigEndian(x);
}

bool CBinaryStream::WriteByte(BYTE x)
{
//	_ASSERT(m_hFile != INVALID_HANDLE_VALUE);
	
	bool bRet = true;
//	if (m_hFile != INVALID_HANDLE_VALUE)
	if (m_fileBuffer.IsOpen())
	{
		m_pBuffer[m_nBufPos] = x;
		
		if (++m_nBufPos == m_nBufLen)
			bRet = FlushBuffer();
	}
	
	if (++m_nCurSectorPos == SECTOR_SIZE)
	{
		m_nCurSector++;
		m_nCurSectorPos = 0;
	}

	return bRet;
}

bool CBinaryStream::WriteLittleEndian(WORD x)
{
	WriteByte((BYTE)x);
	return WriteByte((BYTE)(x >> 8));
}

bool CBinaryStream::WriteLittleEndian(DWORD x)
{
	WriteByte((BYTE)x);
	WriteByte((BYTE)(x >> 8));
	WriteByte((BYTE)(x >> 16));
	return WriteByte((BYTE)(x >> 24));
}

bool CBinaryStream::WriteString(const char *s)
{
	while (s && *s != 0)
	{
		WriteByte(*s++);
	}

	return true;
}

bool CBinaryStream::FlushBuffer()
{
//	_ASSERT(m_hFile != INVALID_HANDLE_VALUE);

//	if (m_hFile != INVALID_HANDLE_VALUE)
	if (m_fileBuffer.IsOpen())
	{
//		DWORD dwWritten = 0;
		long nBufLen = m_nBufLen;
	//	if (WriteFile(m_hFile, m_pBuffer, m_nBufLen, &dwWritten, 0) == FALSE ||
		if (m_fileBuffer.AddData(m_pBuffer, nBufLen) == false ||
			(UINT)nBufLen != m_nBufLen)
		{
			_ASSERT(FALSE);
			// We have a problem, such as no disk space
			CHelper::Trace(" CBinaryStream::FlushBuffer:: Could not write data!!!\n");
			Close();
			return false;
		}

		m_nBufPos = 0;
	}

	return true;
}

bool CBinaryStream::FillSector()
{
	while (m_nCurSectorPos != 0)
	{
		WriteByte(0);
	}

	return true;
}

long CBinaryStream::GetCurSector()
{
	return m_nCurSector;
}

void CBinaryStream::SetCurSector(long nNewPos)
{
	m_nCurSector = nNewPos;
}

BYTE* CBinaryStream::GetBuffer()
{
	return m_pBuffer;
}

long CBinaryStream::GetBufferPos()
{
	return m_nBufPos;
}

long CBinaryStream::GetCurSectorPos()
{
	return m_nCurSectorPos;
}

void CBinaryStream::SetCurSectorPos(long nNewPos)
{
	m_nCurSectorPos = nNewPos;
}

void CBinaryStream::SetBufferPos(long nNewPos)
{
	m_nBufPos = nNewPos;
}

BOOL CBinaryStream::IsBufferAtMax()
{
	return m_fileBuffer.IsBufferAtMax();
}

CCircularBuffer* CBinaryStream::GetFileBuffer()
{
	return &m_fileBuffer;
}
