// DiscAudio.cpp: Implementierung der Klasse CDiscAudio.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "disc.h"
#include "DiscAudio.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CDiscAudio::CDiscAudio()
{
	m_nCurTrack = 0;
	m_nReadPos = 0;
	m_nCueSheetLen = 0;
	m_pCueSheet = NULL;
	m_nReadPosTrack = 0;
}

CDiscAudio::~CDiscAudio()
{
	Reset();
}

double CDiscAudio::AddAudioFile(char *pstrPath, double dDuration)
{
	if (dDuration <= 0.0f)
	{
		dDuration = AudioExtrGetFileDuration(pstrPath);
		if (dDuration < 2.0f)
			return 0;
	}

	CAudioTrack* pTrack = new CAudioTrack;
	pTrack->dDuration = dDuration;
	pTrack->strPath = pstrPath;
	pTrack->CalculateSize();

	m_arrTracks.Add(pTrack);

	return dDuration;
}

double CDiscAudio::GetTotalDuration()
{
	double dTotal = 0.0f;
	for (int i=0;i<m_arrTracks.GetSize();i++)
	{
		dTotal += m_arrTracks.GetAt(i)->dDuration;
	}

	return dTotal;
}

bool CDiscAudio::Read(BYTE* pBuffer, long & nLen)
{
	_ASSERT(nLen > 0);
	_ASSERT(m_arrTracks.GetAt(m_nCurTrack)->nSize);
	if (m_arrTracks.GetAt(m_nCurTrack)->nSize == m_nReadPosTrack || nLen == 0)
	{
		nLen = 0;
		return false;
	}

	long nRequest = nLen;	
	bool bResult = (AudioExtrReadData(pBuffer, nLen) != 0);
	m_nReadPos += nLen;

	// if (we received less than what we asked for) and
	// Current Position + What we received does not reach
	// the size
	
	_ASSERT(nRequest > 0);
	if (nRequest < nLen && 
		m_nReadPosTrack + nLen < m_arrTracks.GetAt(m_nCurTrack)->nSize)
	{
		// if this happens, the we don't have any more data, but the cue
		// sheet expects some data to still arrive. This happens if the 
		// time is recorded as being too long. In this case, we pad the track
		// with 0s till the time reaches. Or the end of the read buffer reaches
		// in which case this function will be called again
		
		// make the buffer leftover 0
		memset(&pBuffer[nLen], 0, nRequest - nLen);
		
		// Get the amount that we need to fill the needed size completely
		long nLeftOver = m_arrTracks.GetAt(m_nCurTrack)->nSize - m_nReadPosTrack;

		// [leftover is the empty space at the end of the file]
		// is the leftover + the read data > than the buffer size?
		// If so we indicate the whole buffer as valid, and this function
		// will be called again
		if (nLen + nLeftOver >= nRequest)
		{
			nLen = nRequest;
		}
		else
		{
			// this implies that the leftover does not fill the buffer
			// entirely, or it flushes with the edge of the buffer
			nLen = nLen + nLeftOver;
		}

		bResult = true;
	}
	else if (m_nReadPosTrack + nLen > m_arrTracks.GetAt(m_nCurTrack)->nSize)
	{
		// if this happens then the read will exceed the length that we
		// previously detected our media file to have. In this case, we
		// align the data to our calculated size, and return. Usually
		// this usually happens because of rounding errors, and the amount
		// of data cut off will be in the fractions of seconds
		
		_ASSERT(nLen > (m_arrTracks.GetAt(m_nCurTrack)->nSize - m_nReadPosTrack));

		nLen = m_arrTracks.GetAt(m_nCurTrack)->nSize - m_nReadPosTrack;
		_ASSERT(nLen > 0);
		bResult = true;
	}

	m_nReadPosTrack += nLen;
	_ASSERT(m_nReadPosTrack >= 0);

	return bResult;
}

bool CDiscAudio::SetAndPrimeTrack(int nTrack)
{
	CHelper::Trace("SetAndPrimeTrackCalled. nTrack=%lu. m_arrTracks.GetSize()=%lu\n", nTrack, m_arrTracks.GetSize());

	ASSERT(nTrack >= 0 && nTrack < m_arrTracks.GetSize());
	
	CHelper::Trace("AudioExtrSetBufferMode about to be called. Blocks=%lu\n",  GetBlockSize()*16);

	AudioExtrSetBufferMode(0, GetBlockSize()*16); // 16 blocks, one write pass!!!

	m_nReadPosTrack = 0;
	m_nCurTrack = nTrack;

	CString pstrFile = m_arrTracks.GetAt(nTrack)->strPath;

	CHelper::Trace("About to call AudioExtrOpenFile. pstrFile=%s\n", (LPCTSTR)pstrFile);

	if (AudioExtrOpenFile((char*)(LPCTSTR)pstrFile, _Module.m_hInst) == 0)
	{
		CHelper::Trace("AudioExtrOpenFile went okay\n");
		return true;
	}

	CHelper::Trace("AudioExtrOpenFile failed! Returning false\n");
	return false;
}

void CDiscAudio::Finished()
{
	AudioExtrCloseFile();

	m_nReadPos = 0;

	if (m_pCueSheet)
		delete [] m_pCueSheet;
	m_pCueSheet = NULL;
}

double CDiscAudio::GetProgress()
{
	return m_nReadPos;
}

double CDiscAudio::GetDuration()
{
	// Get duration in minutes
	double dDuration = GetTotalDuration();

	// what does this translate to in bytes?
	// samples persec * bytes per sec (16 bits/2) * no channels (=2)
	long nBytesPerSec = 44100 * ((2 * 16) / 8);
	
	// Add the 150 blocks per track
//	nBytesPerSec += m_arrTracks.GetSize() * (150 * GetBlockSize());

	return (dDuration * nBytesPerSec);
}

void CDiscAudio::Reset()
{
	// Removes all tracks
	while (m_arrTracks.GetSize())
	{
		delete m_arrTracks.GetAt(0);
		m_arrTracks.RemoveAt(0);
	}
}

CArray< CDiscAudio::CAudioTrack*,  CDiscAudio::CAudioTrack*>* CDiscAudio::GetTrackArray()
{
	return &m_arrTracks;
}

BYTE* CDiscAudio::GetCueSheet(long nAudioPause)
{
	// auido sample cue sheet mmc annex p, table p1 
	// Send cue sheet command 6.2.11
	// dummy
		
	CHelper::Trace("CDiscAudio::GetCueSheet entry. AudioPause=%lu\n", nAudioPause);

	// FOR ALL CD MEDIA, LBA 0 is = MSF 0,2,0. Is this correct? Hot damn, I don't know

	// no catalog code
	m_nCueSheetLen = 3; // lead-in, gap, lead-out

	for (int i=0;i<m_arrTracks.GetSize();i++)
	{
		m_nCueSheetLen += 1; // track line

		if (i != 0 && nAudioPause)
			m_nCueSheetLen += 1; // pre-gap line

		// no ISRC, 1 index, no cd-text.
		// note, you might have to increment once for the index
	}
	
	CHelper::Trace("CDiscAudio::GetCueSheet - lines=%lu\n", m_nCueSheetLen);

	m_nCueSheetLen = m_nCueSheetLen * 8;
	m_pCueSheet = new BYTE[m_nCueSheetLen];

	int n=0; // current address
	BYTE ctl = 0; // control nibbles of cue sheet entry CTL/ADR
	BYTE dataMode = 0;

	// entry for lead-in
	m_pCueSheet[n*8] = 0x01 | ctl; // CTL/ADR
	m_pCueSheet[n*8+1] = 0;    // Track number
	m_pCueSheet[n*8+2] = 0;    // Index
	m_pCueSheet[n*8+3] = 0x01; // toc lead in mode, data form
	m_pCueSheet[n*8+4] = 0;    // Serial Copy Management System
	m_pCueSheet[n*8+5] = 0;    // MIN
    m_pCueSheet[n*8+6] = 0;    // SEC
    m_pCueSheet[n*8+7] = 0;    // FRAME
	
	n++; // next line
	
	long nCurLba = 0;
	long min = 0;
	long sec = 0;
	long frame = 0;

	_ASSERT(nAudioPause);

	// generate the lines for all the tracks
	for (i=0;i<m_arrTracks.GetSize();i++)
	{
		CHelper::Trace("CDiscAudio::GetCueSheet - constructing track %lu line\n", i);

		// dataMode stays 0, indicating no subchannels
		// only 2 audio channels, no isrc, no pre-emphasis
		ctl = 0;
		ctl |= 0x20; // copy permitted

		// entry for pre-gap of all tracks
		if (nAudioPause)
		{
			LbaToMsfAlt(nCurLba, min, sec, frame);

			m_pCueSheet[n*8]   = ctl | 0x01;
			m_pCueSheet[n*8+1] = i+1; // track number
			m_pCueSheet[n*8+2] = 0; // Index 0 indicates pre-gap
			m_pCueSheet[n*8+3] = dataMode; // Data Form
			m_pCueSheet[n*8+4] = 0; // no alternate copy bit
			m_pCueSheet[n*8+5] = (BYTE)min;
			m_pCueSheet[n*8+6] = (BYTE)sec;
			m_pCueSheet[n*8+7] = (BYTE)frame;
			n++;

			nCurLba += 150;

			CHelper::Trace("CDiscAudio::GetCueSheet - constructing track pregap. CurLBA=%lu\n", nCurLba);
		}
		
		CHelper::Trace("CDiscAudio::GetCueSheet - constructing track entry. CurLBA=%lu\n", nCurLba);

		LbaToMsfAlt(nCurLba, min, sec, frame);

		// The main track itself
		m_pCueSheet[n*8]   = ctl | 0x01;
		m_pCueSheet[n*8+1] = i+1;
		m_pCueSheet[n*8+2] = 1; // Index 1
		m_pCueSheet[n*8+3] = dataMode; // Data Form
		m_pCueSheet[n*8+4] = 0; // no alternate copy bit
		m_pCueSheet[n*8+5] = (BYTE)min;
		m_pCueSheet[n*8+6] = (BYTE)sec;
		m_pCueSheet[n*8+7] = (BYTE)frame;
		n++;
		
		// no other indeces

		// increment time
		nCurLba += (m_arrTracks.GetAt(i)->nSize / GetBlockSize());

		CHelper::Trace("CDiscAudio::GetCueSheet - constructing track entry. CurLBA=%lu\n", nCurLba);

	}

	// entry for lead out. This is shifted by 150

	nCurLba += 150;
	LbaToMsfAlt(nCurLba, min, sec, frame);
	
	ctl = 0;
	m_pCueSheet[n*8]   = ctl | 0x01;
	m_pCueSheet[n*8+1] = 0xAA; // track no. AAh for lead-out
	m_pCueSheet[n*8+2] = 1; // Index 1. Always 1 for lead-out
	m_pCueSheet[n*8+3] = dataMode;
	m_pCueSheet[n*8+4] = 0; // no alternate copy bit
	m_pCueSheet[n*8+5] = (BYTE)min;
	m_pCueSheet[n*8+6] = (BYTE)sec;
	m_pCueSheet[n*8+7] = (BYTE)frame;
	
	CHelper::Trace("CDiscAudio::GetCueSheet - written lead-out. Exit\n");

	return m_pCueSheet;
}

//DEL void CDiscAudio::SetWriteType(WriteType eWriteType)
//DEL {
//DEL 	m_eWriteType = eWriteType;
//DEL }

long CDiscAudio::GetCueSheetLen()
{
	return m_nCueSheetLen;
}

void CDiscAudio::SecToMFS(double timeSecs, long &min, long &sec, long &frame)
{
//	min = timeSecs / 60;
//	sec = (long)timeSecs % 60;
//	frac = 0; // ?
	
	if (timeSecs == 0)
	{
		min = 0;
		sec = 0;
		frame = 0;
		return;
	}

	// convert the seconds to an lba
	long lba = (long)(timeSecs * (44100 * ((2 * 16) / 8)));
	lba = lba / GetBlockSize();

	LbaToMsfAlt(lba, min, sec, frame);
}

void CDiscAudio::LbaToMsfAlt(long lba, long &min, long &sec, long &frame)
{
	min = lba / 4500;
	lba %= 4500;

	sec = lba / 75;
	lba %= 75;

	frame = lba;
}

BOOL CDiscAudio::LbaToMsf(long lba, long &min, long &sec, long &frame)
{
	int	m;
	int	s;
	int	f;

	if (lba >= -150) {
		m = (lba) / 60 / 75;
		s = (lba - m*60*75)  / 75;
		f = (lba - m*60*75 - s*75);

	} else if (lba >= -45150 && lba <= -151) {
		m = (lba + 450150) / 60 / 75;
		s = (lba + 450150 - m*60*75)  / 75;
		f = (lba + 450150 - m*60*75 - s*75);

	} else {
		min   = -1;
		sec   = -1;
		frame = -1;

		return (FALSE);
	}
	min   = m;
	sec   = s;
	frame = f;

	if (lba > 404849)			/* 404850 -> 404999: lead out */
		return (FALSE);
	return (TRUE);
}