// Disc.h: Schnittstelle für die Klasse CDisc.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DISC_H__63752A60_1CFF_4CF2_AA25_3EA10AF9FC70__INCLUDED_)
#define AFX_DISC_H__63752A60_1CFF_4CF2_AA25_3EA10AF9FC70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDiscParser;

// base class for the discs

class CDisc  
{
public:		
	CDisc();
	virtual ~CDisc();
	
	virtual BYTE GetMode();
	virtual int  GetTrackType(int nTrack);
	virtual bool Read(BYTE* pBuffer, long & nLen);
	virtual bool SetAndPrimeSession(int nSession, int nSessionStartLBA);
	virtual bool SetAndPrimeTrack(int nTrack);
	virtual int  GetTrackCount();
	virtual int  GetSessionCount();
	virtual long GetBlockSize();
	virtual void Finished();
	virtual void Reset();
	virtual long GetCueSheetLen();

	virtual void SetWriteType(int iWriteType);

	virtual double GetProgress();
	virtual double GetDuration();

	virtual void ReadBufferInfo(long & nValid, long & nSize);
	
	virtual BYTE* GetCueSheet(long nAudioPause);
	virtual double GetDurationTime();
	virtual double GetProgressTime();

	virtual void SetDiscParser(CDiscParser* pDiscParser);
};

#endif // !defined(AFX_DISC_H__63752A60_1CFF_4CF2_AA25_3EA10AF9FC70__INCLUDED_)
