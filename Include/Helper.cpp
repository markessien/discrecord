// Helper.cpp: Implementierung der Klasse CHelper.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Helper.h"
#include <stdio.h>
//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

BOOL CHelper::m_bTimeStamp = TRUE;

FILE* CHelper::GetLogStream() 
{ 
	// Author: Mark A. Essien
	// Date: 12.02.2002
	// Description: Returns a pointer to log file, and opens the file if not already open

	static FILE *streamLog = NULL;

	if( streamLog != NULL || (streamLog = _tfopen( _T(LOGFILE), _T("w+") )) != NULL )
	{
		return streamLog;
	}

	return NULL;
}
