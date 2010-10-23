// Disc.cpp: Implementierung der Klasse CDisc.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "DiscRecord.h"
//#include "DiscRecordObj.h"
#include "Disc.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CDisc::CDisc()
{

}

CDisc::~CDisc()
{

}

bool CDisc::Read(BYTE *pBuffer, long &nLen)
{
	return false;
}

int CDisc::GetSessionCount()
{
	return 1;
}

int CDisc::GetTrackCount()
{
	return 1;
}

bool CDisc::SetAndPrimeTrack(int iTrack)
{
	return true;
}

bool CDisc::SetAndPrimeSession(int iSession, int nSessionStartLBA)
{
	return true;
}

void CDisc::Finished()
{

}

long CDisc::GetBlockSize()
{
	return 2048;
}

void CDisc::Reset()
{

}

double CDisc::GetDuration()
{
	return 0.0f;
}

BYTE CDisc::GetMode()
{
	// 0x00 is raw mode for audio
	// 0x08 is mode1 for data

	return 0x08;
}

double CDisc::GetProgress()
{
	return 0.0f;
}

int CDisc::GetTrackType(int nTrack)
{
	return 0; 
}

void CDisc::ReadBufferInfo(long &nValid, long &nSize)
{
}

double CDisc::GetProgressTime()
{
	return 0.0f;
}

double CDisc::GetDurationTime()
{
	return 0.0f;
}

BYTE* CDisc::GetCueSheet(long nAudioPause)
{
	return NULL;
}

void CDisc::SetWriteType(int iWriteType)
{

}

long CDisc::GetCueSheetLen()
{
	return 0;
}

void CDisc::SetDiscParser(CDiscParser* pDiscParser)
{
}