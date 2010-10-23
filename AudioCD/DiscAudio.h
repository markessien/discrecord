// DiscAudio.h: Schnittstelle für die Klasse CDiscAudio.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DISCAUDIO_H__AEBFBFC4_9805_4B26_9D5D_9988B907FB02__INCLUDED_)
#define AFX_DISCAUDIO_H__AEBFBFC4_9805_4B26_9D5D_9988B907FB02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "disc.h"
#include "..\AudioDecompress\AudioDecompress.h"

#define CTrackArray CArray< CDiscAudio::CAudioTrack*,  CDiscAudio::CAudioTrack*>

class CDiscAudio  : public CDisc
{
public:
	
	long GetCueSheetLen();
	BYTE* GetCueSheet(long nAudioPause);


	struct CAudioTrack
	{
		void CalculateSize() 
		{
			long nFactor = 44100 * 4;
			double dSize = dDuration * (double)nFactor;
			nSize = (long)dSize;
		}
		
		long    nSize;
		double  dDuration;
		CString strPath;
	};

	CDiscAudio();
	virtual ~CDiscAudio();
	
	CArray<CAudioTrack*, CAudioTrack*>* GetTrackArray();
	
	void ReadBufferInfo(long &nValid, long &nSize){
		AudioExtrGetBufferInfo(nValid, nSize);
	}
	
	double GetDurationTime() {return GetTotalDuration(); }
	double GetProgressTime() {return GetProgress() / (44100 * ((2 * 16) / 8));}

	double GetTotalDuration();
	double AddAudioFile(char* pstrPath, double dDuration);
	bool Read(BYTE* pBuffer, long & nLen);
	bool SetAndPrimeTrack(int nTrack);
	void Finished();
	void Reset();
	
	double GetProgress();
	double GetDuration();

	int  GetTrackCount()   {return m_arrTracks.GetSize();}
	int  GetSessionCount() {return 1;}
	long GetBlockSize()    {return 2352;}
	BYTE GetMode()         {return 0x00;}
	int  GetTrackType(int nTrack) {return 1;}

private:
	void SecToMFS(double timeSecs, long & min, long & sec, long &frame);
	BOOL LbaToMsf(long lba, long &min, long &sec, long &frame);
	void LbaToMsfAlt(long lba, long &min, long &sec, long &frame);

private:
	long m_nCurTrack;
	long m_nReadPosTrack;
	long m_nCueSheetLen;
//	int m_iWriteType;
	CArray<CAudioTrack*, CAudioTrack*> m_arrTracks;
	long m_nReadPos;
	BYTE* m_pCueSheet;
};

#endif // !defined(AFX_DISCAUDIO_H__AEBFBFC4_9805_4B26_9D5D_9988B907FB02__INCLUDED_)
