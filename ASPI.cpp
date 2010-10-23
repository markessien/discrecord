// ASPI.cpp: Implementierung der Klasse CASPI.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ASPI.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

HINSTANCE CASPI::m_hAspiInst = NULL;

CASPI::CASPI() : m_bAspiLoaded(false)
{
	
}

CASPI::~CASPI()
{
	if (m_hAspiInst)
		FreeLibrary(m_hAspiInst);

	m_hAspiInst = NULL;
}

long CASPI::LoadASPI()
{
//	DWORD dwErr = 0;

	if (m_hAspiInst != NULL)
		return 0;

	m_hAspiInst = LoadLibrary( "WNASPI32.DLL" );
	if (m_hAspiInst)
	{
		pfnGetASPI32SupportInfo = (DWORD(*)(void))GetProcAddress( m_hAspiInst, "GetASPI32SupportInfo" );
		pfnSendASPI32Command = (DWORD(*)(LPSRB))GetProcAddress( m_hAspiInst, "SendASPI32Command" );
		pfnGetASPI32Buffer = (BOOL(*)(PASPI32BUFF))GetProcAddress( m_hAspiInst, "GetASPI32Buffer" );
		pfnFreeASPI32Buffer = (BOOL(*)(PASPI32BUFF))GetProcAddress( m_hAspiInst, "FreeASPI32Buffer" );
		pfnTranslateASPI32Address = (BOOL(*)(PDWORD,PDWORD))GetProcAddress( m_hAspiInst, "TranslateASPI32Address" );
		pfnGetASPI32DLLVersion = (DWORD(*)(void))GetProcAddress( m_hAspiInst, "GetASPI32DLLVersion" );

		if ( !pfnGetASPI32SupportInfo || !pfnSendASPI32Command )
		{
			if ( !pfnGetASPI32SupportInfo )
				return -2;
			else
				return -3;
		}
	}
	else
		return -1;

	
	m_bAspiLoaded = true;

	return 0;
}

long CASPI::GetSupportInfo()
{
	if (m_bAspiLoaded == false)
		return -1;

	BYTE nAdptCount;
	BYTE nASPIStatus;
	DWORD nSupportInfo;
	
	nSupportInfo = pfnGetASPI32SupportInfo();

	nASPIStatus = HIBYTE(LOWORD(nSupportInfo));
	nAdptCount = LOBYTE(LOWORD(nSupportInfo));

	if (nASPIStatus != SS_COMP && nASPIStatus != SS_NO_ADAPTERS)
	{
		_ASSERT(nASPIStatus != SS_NO_ASPI);
		_ASSERT(nASPIStatus != SS_FAILED_INIT);

		return -1;
	}
	else
	{
		return nAdptCount;
	}

	return 0;
}

DWORD CASPI::SendCommand(LPSRB psrb)
{
	return pfnSendASPI32Command(psrb);
}
