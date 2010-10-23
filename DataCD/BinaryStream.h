// BinaryStream.h: Schnittstelle für die Klasse CBinaryStream.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BINARYSTREAM_H__252DAF0E_255D_414D_8257_E624E875E600__INCLUDED_)
#define AFX_BINARYSTREAM_H__252DAF0E_255D_414D_8257_E624E875E600__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


const unsigned SECTOR_SIZE = 2048;
const unsigned BUFFER_SIZE = 8*SECTOR_SIZE;

class CBinaryStream  
{
public:
	CCircularBuffer* GetFileBuffer();
	BOOL IsBufferAtMax();
	void SetBufferPos(long nNewPos);
	void SetCurSectorPos(long nNewPos);
	long GetCurSectorPos();
	long GetBufferPos();
	BYTE* GetBuffer();
	void SetCurSector(long nNewPos);
	long GetCurSector();
	bool FillSector();
	bool FlushBuffer();

	CBinaryStream();
	virtual ~CBinaryStream();

	bool WriteString(const char* s);
	bool WriteLittleEndian(DWORD x);
	bool WriteLittleEndian(WORD x);
	bool WriteByte(BYTE x);
	bool WriteBothEndian(DWORD x);
	bool WriteBothEndian(WORD x);
	bool WriteBlock(BYTE value, UINT nCount);
	bool WriteBigEndian(DWORD x);
	bool WriteBigEndian(WORD x);
	bool SetBufferSize(UINT nCount);
	bool IsOpen();
	void Close();
	bool Open(LPCTSTR lpszFileName);

private:
	CCircularBuffer m_fileBuffer;
//	HANDLE m_hFile;
	BYTE*  m_pBuffer;
	UINT   m_nBufLen;
	UINT   m_nBufPos;
	long   m_nCurSector;
	long   m_nCurSectorPos;
};

#endif // !defined(AFX_BINARYSTREAM_H__252DAF0E_255D_414D_8257_E624E875E600__INCLUDED_)
