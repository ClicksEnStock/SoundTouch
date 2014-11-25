
#include "Common.h"

int Extension::GetVersion()
{
    return sndVersion;
}

TCHAR* Extension::LastError()
{
    _tcscpy (errorTemp,lastError);
	_snwprintf_s(lastError, _countof(lastError),ERRORSIZE,ErrorS[noError]);
	return  errorTemp;
}