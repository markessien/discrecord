// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__91C5BBFE_3E23_48E8_993B_8F08D4BEFB8C__INCLUDED_)
#define AFX_STDAFX_H__91C5BBFE_3E23_48E8_993B_8F08D4BEFB8C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif
#define _ATL_APARTMENT_THREADED

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>
#include <atlctl.h>
#include "Include\rdstring.h"
#include "Include\rdcollections.h"
#include "Include\helper.h"
#include "Include\notifywindow.h"
#include "Include\CircularBuffer.h"

#define LOGFILE "c:\\burnrecord.log"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // !defined(AFX_STDAFX_H__91C5BBFE_3E23_48E8_993B_8F08D4BEFB8C__INCLUDED)
