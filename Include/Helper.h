
// Helper.h: Schnittstelle für die Klasse CHelper.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HELPER_H__F278B60D_78E6_4CDD_AB27_DE654BC6A6BF__INCLUDED_)
#define AFX_HELPER_H__F278B60D_78E6_4CDD_AB27_DE654BC6A6BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//void RETRY(int nSuccesReturnValue, int nTimesToTry, int nTimeOut, int nResult, void* pFunc,);
//#define RETRY(func, succces_ret, times_to_try, timeout_secs, result) {iRetry = times_to_try; while (func != succces_ret && iRetry > 0) { Sleep(timeout_secs); iRetry--; }


//#define Trace CHelper::Trace
#include <stdio.h>

class CHelper  
{
public:
	
	static void LogTimeStamp(BOOL bTimeStamp)
	{
		m_bTimeStamp = bTimeStamp;
	}

	static void Trace(LPCTSTR pStr, ...)
	{
		_TCHAR szBuff[1024];

		va_list va;
		va_start(va, pStr);
		wvsprintf (szBuff, pStr, va);
		va_end(va);
		
#if 1 // change to 0, not to log to a file
		SYSTEMTIME time;
		GetLocalTime(&time); 

		FILE* pFile = GetLogStream();
		if (pFile)
		{
			if (m_bTimeStamp)
			{
				_ftprintf(pFile, TEXT("%04u/%02u/%02u %02u:%02u:%02u-%03u\t%s"), 
						  time.wYear, time.wMonth, time.wDay, time.wHour,
						  time.wMinute, time.wSecond, time.wMilliseconds, 
						  szBuff);
			}
			else
			{
				_ftprintf(pFile, TEXT("%s"), szBuff);
			}
			
			fflush(pFile);
		}
#endif

		OutputDebugString(szBuff);
	}

	static FILE* CHelper::GetLogStream();

	static BOOL m_bTimeStamp;
};

#endif // !defined(AFX_HELPER_H__F278B60D_78E6_4CDD_AB27_DE654BC6A6BF__INCLUDED_)
