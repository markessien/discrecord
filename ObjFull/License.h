
#include <fstream>
using namespace std;

// http://faqchest.dynhost.com/msdn/ATL/atl-98/atl-9808/atl98081019_09097.html

// change these
#define LICENSE_KEY 235792357835234I64 // 16 characters in numbers
#define ERR_MSG "This component is not licensed to be used in a development enviroment"
#define LICFILE_NAME "\\discrec.lic"

// don't change these
#define MAKELICENSE(x) MakeLicense(x)
#define UNMAKELICENSE(x) UnMakeLicense(x)

// for the key
static char g_szLicKey[50] = {0};

#if defined(AN_UNDEFINED_SYMBOL)
#else
class CLicense  
{
protected:

	static inline char* MakeLicense(__int64 iKey)
	{
		// this function uses the number to generate a license key
		DWORD nLower = (DWORD)iKey;
		DWORD nUpper = (DWORD)(iKey >> 32);
		
		// Some confuzion
		__int64 uValidate = UInt32x32To64(nLower, nUpper);
		LONGLONG llValidate = Int32x32To64(nLower, nUpper);

		sprintf(g_szLicKey, "%lu%lu", nLower, nUpper);
		strcat(g_szLicKey, "__erdinc");

		OutputDebugString("\n\nLICENSE KEY IS ");
		OutputDebugString(g_szLicKey);
		OutputDebugString("\n\n");

		return g_szLicKey;
	}
	
	static inline __int64 UnMakeLicense(char* pstrKey)
	{
		// this function uses the number to generate a license key
		if (pstrKey == NULL || strlen(pstrKey) == 0)
			return 0;
		
		// get the shifted key
		__int64 i64Key = _atoi64(pstrKey); // does nothing
		DWORD nLower = (DWORD)i64Key; // does nothing
		DWORD nUpper = (DWORD)(i64Key << 32); // does nothing
		__int64 iResult = nLower | nUpper; // does nothing
		
		char* pstrOriginalKey = MakeLicense(LICENSE_KEY);

		if (strcmp(pstrOriginalKey, pstrKey) == 0)
		{
			char* pstrThisKey = MakeLicense(i64Key); // does nothing
			return LICENSE_KEY;
		}
		else
			return 181280; // false key
		
		// This function will never enter here.

		return iResult;
	}

   static BOOL VerifyLicenseKey(BSTR bstr)
   {
	   // The license key is passed in here, and we have to verify if the
	   // key is alright

      USES_CONVERSION;
      return (UNMAKELICENSE(W2A(bstr)) == LICENSE_KEY);
   }

   static BOOL GetLicenseKey(DWORD dwReserved, BSTR* pBstr) 
   {
	   // Return the license key. Called at compile time
      USES_CONVERSION;
      *pBstr = SysAllocString( T2OLE(_T(MAKELICENSE(LICENSE_KEY)))); 
      return TRUE;
   }

   static BOOL IsLicenseValid() 
   {
       char szPath[MAX_PATH];
       GetWindowsDirectory(szPath, MAX_PATH); 
       strcat(szPath, LICFILE_NAME);
        
       	std::ifstream file;
	    file.open(szPath);

	    if (!file.is_open())
        {
            MessageBox(::GetDesktopWindow(), ERR_MSG, "Licensing Error", MB_ICONSTOP|MB_APPLMODAL|MB_SYSTEMMODAL|MB_SETFOREGROUND|MB_TOPMOST|MB_OK);
            return FALSE;
        }
        
        char szLine[1024];
		file.getline(szLine, 1024);
	    
        if (UNMAKELICENSE(szLine) == LICENSE_KEY)
        {
		    return TRUE;
        }
        else
            MessageBox(::GetDesktopWindow(), ERR_MSG, "Licensing Error", MB_ICONSTOP|MB_APPLMODAL|MB_SYSTEMMODAL|MB_SETFOREGROUND|MB_TOPMOST|MB_OK);

        file.close();

        return FALSE;
   }
};
#endif