// DiscImage.cpp: Implementierung der Klasse CDiscImage.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Disc.h"
#include "DiscImage.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CDiscImage::CDiscImage()
{
	m_hFile = INVALID_HANDLE_VALUE;
	memset(m_szSourceFile, 0, sizeof(m_szSourceFile));
	m_nSize = 0;
	m_nPos = 0;
}

CDiscImage::~CDiscImage()
{

}

BYTE CDiscImage::GetMode()
{
	return 0x08; // data
}

int CDiscImage::GetTrackType(int nTrack)
{
	return 0;
}

bool CDiscImage::Read(BYTE* pBuffer, long & nLen)
{
	DWORD dwRead = 0;
	if (ReadFile(m_hFile, pBuffer, nLen, &dwRead, 0) == FALSE)
		return false;

	if (dwRead == 0)
		return false;

	nLen = dwRead;
	m_nPos += dwRead;

	return true;
}

long CDiscImage::GetBlockSize()
{
	return 2048;
}

void CDiscImage::Finished()
{
	if (m_hFile != INVALID_HANDLE_VALUE)
		CloseHandle(m_hFile);

	m_hFile = INVALID_HANDLE_VALUE;
}

void CDiscImage::Reset()
{
	Finished();
	memset(m_szSourceFile, 0, sizeof(m_szSourceFile));
}

double CDiscImage::GetProgress()
{
	return m_nPos;
}

double CDiscImage::GetDuration()
{
	return m_nSize;
}

bool CDiscImage::SetSourceFile(char *pstrPath)
{
	strcpy(m_szSourceFile, pstrPath);
	
	m_hFile = CreateFile(m_szSourceFile, GENERIC_READ,
						 FILE_SHARE_READ|FILE_SHARE_WRITE, 
						 0,OPEN_EXISTING, 
						 0, 0);

	if (m_hFile == INVALID_HANDLE_VALUE)
		return false;

	m_nSize = GetFileSize(m_hFile, 0);
	CloseHandle(m_hFile);

	return true;
}

bool CDiscImage::SetAndPrimeSession(int nSession, int nSessionStartLBA)
{
	m_hFile = CreateFile(m_szSourceFile, GENERIC_READ,
						 FILE_SHARE_READ|FILE_SHARE_WRITE, 
						 0,OPEN_EXISTING, 
						 0, 0);

	if (m_hFile == INVALID_HANDLE_VALUE)
		return false;

	return true;
}