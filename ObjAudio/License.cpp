// License.cpp: Implementierung der Klasse CLicense.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <windows.h>
#include "License.h"
#include <string.h>

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
// http://faqchest.dynhost.com/msdn/ATL/atl-98/atl-9808/atl98081019_09097.html

// constants. No need to change
#define NO_ENCRYPTION 0
#define ENCRYPT_MODSUB 1

// ---- Definations. Change per app

// Lic file path is the path where the license file is to be read from
// valid values are $AppPath, $WinDir, $WinSysDir

#define DISPLAY_KEY_ON_RUN 0
#define LICFILE_PATH "$WinDir"
#define LICFILE_NAME "audiorec.lic"
#define ENCRYPTION_METHOD ENCRYPT_MODSUB
#define UNENCRYPTED_KEY "AAAAAAAAAAAAAAAA"
#define MOD_SUB_KEY_NUM 213124142
#define KEY_PREFIX "erd:audiorecord:dev"

// Errors
#define ERR_LIC_NOT_FOUND "The license file does not exist. This component cannot be used in a development enviroment"
#define ERR_LIC_PATH_INVALID "The path specified for the license file is invalid. This component cannot be used in a development enviroment"
#define ERR_LIC_FILE_BADSIZE "The license file has got an invalid size. This component cannot be used in a development enviroment"
#define ERR_LIC_BAD_DATA "The license file data was not valid. This component cannot be used in a development enviroment"
#define ERR_LIC_KEY_INVALID "The specified license key was invalid. This component cannot be used in a development enviroment" 
// ---- End defs

CLicense::CLicense()
{

}

CLicense::~CLicense()
{

}

BOOL CLicense::VerifyLicenseKey(BSTR bstr)
{
    // The license key is passed in here, and we have to verify if the
    // key is alright
	
	USES_CONVERSION;

	char strResult[256];
	memset(strResult, 0, 256 * sizeof(char));

	char * pstrKey = W2A(bstr);
	
	if (UnEncryptString(pstrKey, strResult) == FALSE)
	{
		return FALSE;
	}

	if (strcmp(UNENCRYPTED_KEY, strResult) == 0)
		return TRUE;

	return FALSE;
}

BOOL CLicense::GetLicenseKey(DWORD dwReserved, BSTR* pBstr) 
{
    // This function is called to retrieve a license key from
	// the component. The component is supposed to simply gen-
	// arate a license key, which the app is then going to store
	// somewhere internally, and will pass to VerifyKey to make
	// sure it is ok, both at compile and run time
	
	char strResult[256];
	memset(strResult, 0, 256 * sizeof(char));
	
	if (EncryptString(UNENCRYPTED_KEY, strResult) == FALSE)
		return FALSE;

	CComBSTR strKey = strResult;
	strKey.CopyTo(pBstr);

	return TRUE;
}

BOOL CLicense::IsLicenseValid() 
{
	// This function is called when the user tries to instanciate
	// the object in a development enviroment. We are to read the
	// license file in this function, and check if the license key
	// is valid.

	if (DISPLAY_KEY_ON_RUN == 1)
	{
#ifdef _DEBUG
		
		char strResult[256];
		memset(strResult, 0, 256 * sizeof(char));
	
		EncryptString(UNENCRYPTED_KEY, strResult);

		OutputDebugString("\n\nKEY is=");
		OutputDebugString(strResult);
		OutputDebugString("\n\n");
	
		UnEncryptString(strResult, strResult);

		if (strcmp(strResult, UNENCRYPTED_KEY) != 0)
		{	
			OutputDebugString(strResult);
			OutputDebugString("\nINVALID KEY! DO NOT USE!\n");
		}

		::MessageBox(NULL, "Key Traced. Retrieve and reset const to 0", "Retrieve Key", 0);
		exit(0);
#endif
	}

	char szPath[MAX_PATH];
	if (GetLicensePath(szPath) == FALSE)
	{
		LicenseError(ERR_LIC_PATH_INVALID);
		return FALSE;
	}

	HANDLE hFile = CreateFile(szPath, 
							  GENERIC_READ,
							  FILE_SHARE_READ | FILE_SHARE_WRITE, 
							  0, OPEN_EXISTING, 0, 0);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		LicenseError(ERR_LIC_NOT_FOUND);
		return FALSE;
	}
	
	DWORD dwSize = GetFileSize(hFile, 0);
	if (dwSize == 0 || dwSize > 1024*1024)
	{
		CloseHandle(hFile);
		LicenseError(ERR_LIC_FILE_BADSIZE);
		return FALSE;
	}

	BYTE * pLicData = new BYTE[dwSize+1];
	memset(pLicData, 0, dwSize+1);

	DWORD dwRead = 0;
	ReadFile(hFile, pLicData, dwSize, &dwRead, 0);
	pLicData[dwRead] = 0;

	CloseHandle(hFile);
	hFile = INVALID_HANDLE_VALUE;

	if (dwRead == 0)
	{
		delete [] pLicData;
		LicenseError(ERR_LIC_FILE_BADSIZE);
		return FALSE;
	}

	// At this point, we have the contents of the file
	// in our buffer.
	
	char strResult[256];
	memset(strResult, 0, 256 * sizeof(char));
	
	if (UnEncryptString((const char*)pLicData, strResult) == FALSE)
	{	
		delete [] pLicData;
		LicenseError(ERR_LIC_BAD_DATA);
		return FALSE;
	}

	// at this point, the contents of the buffer have been unencrypted
	// to the form where we can compare with our internal value
	if (strcmp(UNENCRYPTED_KEY, strResult) == 0)
	{
		delete [] pLicData;
		return TRUE;
	}
	
	delete [] pLicData;
	LicenseError(ERR_LIC_KEY_INVALID);
    return FALSE;
}

BOOL CLicense::GetLicensePath(char *pBuffer)
{
	char* pstrDef = LICFILE_PATH;

	if (stricmp(pstrDef, "$windir") == 0)
	{
		GetWindowsDirectory(pBuffer, MAX_PATH);
	}
	else if (stricmp(pstrDef, "$appdir") == 0)
	{
		GetCurrentDirectory(MAX_PATH, pBuffer);
	}
	else if (stricmp(pstrDef, "$sysdir") == 0)
	{
		GetSystemDirectory(pBuffer, MAX_PATH);
	}
	else
		return FALSE;
	
	strcat(pBuffer, "\\");
	strcat(pBuffer, LICFILE_NAME);

	return TRUE;
}

void CLicense::LicenseError(char *pstrMsg)
{
	::MessageBox(::GetDesktopWindow(), pstrMsg, "Licensing Error!", 
			     MB_OK|MB_ICONERROR|MB_APPLMODAL|
			     MB_SYSTEMMODAL|MB_TASKMODAL|MB_SETFOREGROUND);
}

BOOL CLicense::UnEncryptString(const char *pstrValue, char *pstrResult)
{
	if (pstrValue == NULL ||
		pstrResult == NULL ||
		strlen(pstrValue) == 0)
	{
		return FALSE;
	}

	if (ENCRYPTION_METHOD == NO_ENCRYPTION)
	{
		strcpy(pstrResult, pstrValue);
	}
	else if (ENCRYPTION_METHOD == ENCRYPT_MODSUB)
	{
		strcpy(pstrResult, pstrValue);

		UnNormalizeString(pstrResult);
	
		char strKey[128] = {0};
		sprintf(strKey, "%lu", MOD_SUB_KEY_NUM);
	
		CLicense::CEncryptModSub ecMod;
		ecMod.bNothing = false;

		ecMod.ModsubDecrypt(pstrResult, strKey);
	}

	return TRUE;
}

BOOL CLicense::EncryptString(const char *pstrString, char *pstrResult)
{
	if (ENCRYPTION_METHOD == NO_ENCRYPTION)
	{
		strcpy(pstrResult, pstrString);
	}
	else if (ENCRYPTION_METHOD == ENCRYPT_MODSUB)
	{
		char strKey[128] = {0};
		sprintf(strKey, "%lu", MOD_SUB_KEY_NUM);
		
		strcpy(pstrResult, pstrString);

		CEncryptModSub ecMod;
		ecMod.bNothing = false;

		ecMod.ModsubEncrypt(pstrResult, strKey);

		NormalizeString(pstrResult);
	}

	return TRUE;
}

// mod sub encryption!

static const int random_perm[]={
 179,   4, 238, 123, 227, 234,  27, 181,  83, 161,  99, 142, 200,  64, 201, 152,
 233, 141, 148, 174,  39,  23,  95, 222, 188, 180, 229, 167, 252,  73, 120,   7,
 176,  74, 221,  35, 108, 224,  26,  72,  58, 242,  15,  57, 216,  17,  71, 182,
 105,  37, 150,  90,  21, 172, 166, 102,  96, 251,  77, 165,  55, 217, 195, 198,
  13, 187, 202,  67, 155,  59, 203, 197, 127,  92, 132, 147,  78, 111, 158, 226,
 178, 250, 243, 154,  87, 241, 163, 191,  22, 254, 249, 210, 240,  20, 186,  53,
 245, 112, 107,  85, 168,  62, 225,   3,  75, 135, 110,   8, 151, 156, 177,  94,
 232,  80, 114,  32, 214,  63, 100,  46, 130,  88,  98, 218,   1, 244, 126,  38,
  50, 220, 192,  34, 160, 215, 183, 236,  93,  30, 196,  79, 239, 213, 125, 117,
 104,  45, 231,  18, 139,  19,   5,  52, 157, 124, 162, 235, 118, 145,  54, 228,
 199, 223, 212, 164, 247,  84, 206,  33,  82, 246, 169,   6,  65, 134, 194, 122,
 219, 133, 113,  11, 146, 190,  56, 128,  16,  41, 109, 140,  51, 103, 208,  40,
 253, 193, 205,  66,  86, 119, 211,  69, 116, 153,  36,  44, 138, 136,  14,  61,
  28,  76, 121, 159, 101, 175, 144,  49,  12, 106, 149,  81, 209, 131, 143, 184,
 185,  97,  91, 137, 171, 170, 237,   9,  60, 189,  70,  31,   2,  42, 204,  48,
  43, 230,  24,  89,  10, 255, 129, 173, 207,  25,  68, 248,  47, 115,  29};


void CLicense::CEncryptModSub::ModsubEncrypt(char* x, char* key) 
{
     int r, i, x_length, key_length;
     x_length = strlen(x);             /* length of string x   */
     key_length = strlen(key);         /* length of string key */
     for (r=0;r<ROUNDS;r++)
       for (i=0;i<x_length;i++)
           x[i] = MOD_ADD( x[i], SUB( x[LAST] ), SUB( x[NEXT] ), key[(2*r+i)%key_length] );


     return;
}

void CLicense::CEncryptModSub::ModsubDecrypt(char* x, char* key) 
{

     int r, i, x_length, key_length;
     x_length = strlen(x);
     key_length = strlen(key);
     for (r=ROUNDS-1;r>=0;r--)
       for (i=x_length-1;i>=0;i--)
           x[i] = MOD_SUBTR( x[i], SUB( x[LAST] ), SUB( x[NEXT] ), key[(2*r+i)%key_length] );
     return;
}

void CLicense::NormalizeString(char *pstrString)
{
	// valid ascii is from 65 to 122. This function takes the input
	// string, and moves the characters into the ascii range

	char strControl[500] = {0};
	memset(strControl, '0', 500 * sizeof(char));

	int nLen = strlen(pstrString);
	
	strControl[nLen] = 0;

	for (int i=0;i<nLen;i++)
	{
		// make sure there are no negative vals
		int iCtrlVal = '0';
		if (pstrString[i] < 0)
		{
			iCtrlVal = '5';
			pstrString[i] = -pstrString[i];
			strControl[i] = '5';
			_ASSERT(pstrString[i] > 0);
		}
			
		_ASSERT(pstrString[i] < 255);

		if (pstrString[i] <= 57)
		{
			// if it is below 57, we can simply add 65
			// and we will land in the correct range
			pstrString[i] += 65;
			strControl[i] = iCtrlVal + 1;
		}
		else if (pstrString[i] > 57 && pstrString[i] < 65)
		{
			// If the string is in this area, we add 10
			pstrString[i] += 10;
			strControl[i] = iCtrlVal + 2;
		}
		else if (pstrString[i] > 122 && pstrString[i] < 179)
		{
			// in this case, we can subtract 57, and we will fall
			// within our range
			pstrString[i] -= 57;
			strControl[i] = iCtrlVal + 3;
		}
		else if (pstrString[i] >= 179 && pstrString[i] < 236)
		{
			// subtract 114
			pstrString[i] -= 114;
			strControl[i] = iCtrlVal + 4;
		}
		else if (pstrString[i] >= 236 && pstrString[i] < 255)
		{
			_ASSERT(FALSE);
			// subtract 133
		//	pstrString[i] -= 133;
		//	strControl[i] = iCtrlVal + 5;
		}
	}
	
	// interleave the control and main strings
	char szResult[500]= {0};
	nLen = strlen(strControl);
	//nLen += nLen;

	int k = 0;
	for (i=0;i<nLen;i++, k+=2)
	{
		szResult[k] = pstrString[i];
		szResult[k+1] = strControl[i];
	}

	strcpy(pstrString, szResult);
}

void CLicense::UnNormalizeString(char *pstrString)
{
	char szResult[500] = {0};

	int nLen = strlen(pstrString);
	for (int i=0;i<nLen;i+=2)
	{
		bool bNeg = false;
		if (pstrString[i+1] >= '5')
		{
			//pstrString[i] = -pstrString[i];
			pstrString[i+1] -= 5;
			bNeg = true;
		}

		switch (pstrString[i+1])
		{
		case '1': pstrString[i] -= 65; break;
		case '2': pstrString[i] -= 10; break;
		case '3': pstrString[i] += 57; break;
		case '4': pstrString[i] += 114; break;
		}
		
		if (bNeg)
			pstrString[i] = -pstrString[i];

		strncat(&szResult[0], &pstrString[i], 1);
	}

	strcpy(pstrString, szResult);
}
