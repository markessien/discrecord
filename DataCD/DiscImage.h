// DiscImage.h: Schnittstelle für die Klasse CDiscImage.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DISCIMAGE_H__B5A2AB45_1DAE_4EE1_AA43_3080A86B30C8__INCLUDED_)
#define AFX_DISCIMAGE_H__B5A2AB45_1DAE_4EE1_AA43_3080A86B30C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Raw image file. The file is copied to disc verbatim

class CDiscImage : public CDisc  
{
public:
	bool SetSourceFile(char* pstrPath);
	CDiscImage();
	virtual ~CDiscImage();
	
	bool SetAndPrimeSession(int nSession, int nSessionStartLBA);
	BYTE GetMode();
	int  GetTrackType(int nTrack);
	bool Read(BYTE* pBuffer, long & nLen);
	long GetBlockSize();
	void Finished();
	void Reset();
	double GetProgress();
	double GetDuration();

private:
	long m_nSize;
	long m_nPos;
	char m_szSourceFile[MAX_PATH];
	HANDLE m_hFile;
};

#endif // !defined(AFX_DISCIMAGE_H__B5A2AB45_1DAE_4EE1_AA43_3080A86B30C8__INCLUDED_)
