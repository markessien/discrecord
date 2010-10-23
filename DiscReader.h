#pragma once

// callback class for reading of discs
class IDiscReader
{
public:
	virtual bool ReadFromDisc(BYTE* pBuffer, long nStartLBA, long nBlockLen, bool bParam) = 0;
	virtual bool InitDiscRead(long nMode) = 0;
	virtual long GetLastSessionLBA() = 0;
};