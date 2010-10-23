// SyncWait.cpp: implementation of the CSyncWait class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SyncWait.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSyncWait::CSyncWait()
{
	m_bIsLocked = FALSE;
	m_bFreeze = FALSE;
	m_hEvent = CreateEvent(0, true, true, 0);
	m_hEventUnlock = CreateEvent(0, true, false, 0);
	
}

CSyncWait::~CSyncWait()
{

}

void CSyncWait::WaitForUnlock(DWORD dwMilliseconds)
{
	if (m_bFreeze)
		return;

	if (IsLocked())
		WaitForSingleObject(m_hEvent, dwMilliseconds); // Elapses after 10 seconds
}

void CSyncWait::Lock()
{
	// Set the event so that other threads will know when
	// we are in this function.

	if (m_bFreeze)
		return;


	m_bIsLocked = TRUE;
	ResetEvent(m_hEvent);
	SetEvent(m_hEventUnlock);
}

void CSyncWait::Unlock()
{
	if (m_bFreeze)
		return;

	m_bIsLocked = FALSE;
	SetEvent(m_hEvent);
	ResetEvent(m_hEventUnlock);
}

BOOL CSyncWait::IsLocked()
{
	return m_bIsLocked;
}

void CSyncWait::WaitForLock(DWORD dwMilliseconds)
{
	if (m_bFreeze)
		return;

	if (IsLocked() == FALSE)
		WaitForSingleObject(m_hEventUnlock, dwMilliseconds);
}

void CSyncWait::Freeze()
{
	// Calling freeze mkaes it impossible to change
	// the state of the sync object
	m_bFreeze = TRUE;
}

void CSyncWait::UnFreeze()
{
	m_bFreeze = FALSE;
}

BOOL CSyncWait::IsFrozen()
{
	return m_bFreeze;
}
