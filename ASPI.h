// ASPI.h: Schnittstelle für die Klasse CASPI.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASPI_H__EED69E29_4CE9_4960_8D43_760BDD54BD8F__INCLUDED_)
#define AFX_ASPI_H__EED69E29_4CE9_4960_8D43_760BDD54BD8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "include\scsidefs.h"
#include "include\wnaspi32.h"


class CASPI  
{
public:
	CASPI();
	virtual ~CASPI();

	DWORD SendCommand(LPSRB psrb);
	long GetSupportInfo();
	long LoadASPI();

private:
	DWORD (*pfnGetASPI32SupportInfo)(void);
	DWORD (*pfnSendASPI32Command)(LPSRB);
	BOOL  (*pfnGetASPI32Buffer)(PASPI32BUFF);
	BOOL  (*pfnFreeASPI32Buffer)(PASPI32BUFF);
	BOOL  (*pfnTranslateASPI32Address)(PDWORD,PDWORD);
	DWORD (*pfnGetASPI32DLLVersion)(void);
	static HINSTANCE m_hAspiInst;
	bool m_bAspiLoaded;
};

#endif // !defined(AFX_ASPI_H__EED69E29_4CE9_4960_8D43_760BDD54BD8F__INCLUDED_)
