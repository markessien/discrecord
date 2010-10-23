// SyncWait.h: interface for the CSyncWait class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYNCWAIT_H__CC960801_0729_46C1_8CE0_BBC164BAD2A8__INCLUDED_)
#define AFX_SYNCWAIT_H__CC960801_0729_46C1_8CE0_BBC164BAD2A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSyncWait  
{
public:
	BOOL IsFrozen();
	void UnFreeze();
	void Freeze();
	void WaitForLock(DWORD dwMilliseconds);
	BOOL IsLocked();
	void Unlock();
	void Lock();
	void WaitForUnlock(DWORD dwMilliseconds);

	CSyncWait();
	virtual ~CSyncWait();

private:
	HANDLE m_hEvent;
	HANDLE m_hEventUnlock;
	BOOL   m_bIsLocked;
	BOOL   m_bFreeze;
};

#endif // !defined(AFX_SYNCWAIT_H__CC960801_0729_46C1_8CE0_BBC164BAD2A8__INCLUDED_)
