// DiscISO9660.h: Schnittstelle für die Klasse CDiscISO9660.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DISCISO9660_H__50C79839_B6D6_452F_89EE_D270ACBEFD48__INCLUDED_)
#define AFX_DISCISO9660_H__50C79839_B6D6_452F_89EE_D270ACBEFD48__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "disc.h"
#include "filerecord.h"
#include "binarystream.h"

#define SESSION_END_ZEROS (427 * SECTOR_SIZE)

class CDiscISO9660  : public CDisc
{
public:
	void SetFileRecord(CFileRecord* pRoot);
	
	CDiscISO9660();
	virtual ~CDiscISO9660();

	CFileRecord* GetFileSystem();	
	
	long GetWrittenSize();
	
	bool Read(BYTE* pBuffer, long & nLen);
	bool SetAndPrimeSession(int nSession, int nSessionStartLBA);
	bool SetAndPrimeTrack(int nTrack) { return true;}
	void Finished();
	void Reset();

	char* GetLabel();
	void SetLabel(char* pstrLabel);
	
	double GetProgress() { return m_nReadSoFar; }
	double GetDuration() { return (m_pRoot->GetTotalSize() + SESSION_END_ZEROS); }
	
	int  GetTrackType(int nTrack) {return 0;}
	
	void ReadBufferInfo(long &nValid, long &nSize){
		nValid = m_stream.GetFileBuffer()->GetBufferValid();
		nSize = m_stream.GetFileBuffer()->GetBufferSize();
	}

	void SetDiscParser(CDiscParser* pDiscParser);

private:
	void WriteDirectoryRecord(CFileRecord* dir, int nType, bool bFinal = true);
	void WritePrimaryVolumeDescriptor();
	bool WriteData();
	static DWORD __stdcall WriteDataThread(LPVOID lpvThreadParm);

private:
	CFileRecord* m_pRoot;
	CBinaryStream m_stream;
	CRecordArray m_pathTable;
	CDiscParser* m_pDiscParser;

	char m_szLabel[50];
	
	long  m_nCurSessionStart;
	long  m_nReadSoFar;
	bool  m_bAbort;
	long  m_nWrittenSize;
	bool  m_bFirstPass;
	DWORD m_nTotalSectors;
	DWORD m_nPathTableSize;
	DWORD m_nLittleEndianPathTableSector;
	DWORD m_nBigEndianPathTableSector;
};

#endif // !defined(AFX_DISCISO9660_H__50C79839_B6D6_452F_89EE_D270ACBEFD48__INCLUDED_)
