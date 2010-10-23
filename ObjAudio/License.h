// License.h: Schnittstelle für die Klasse CLicense.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LICENSE_H__FD69A43F_F0F5_4DCB_B4F1_9B12DC454DEB__INCLUDED_)
#define AFX_LICENSE_H__FD69A43F_F0F5_4DCB_B4F1_9B12DC454DEB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLicense  
{
public:
	
	friend class CEncryptModSub;

	// modsub encryption
	class CEncryptModSub
	{
	public:
		#define C2I(c)                 ((int)c & 0377)         /* convert char to int, no sign ext. */
		#define SUB(x)                 random_perm[C2I(x)-1]   /* substitution function */
		#define NORMALIZE(a)           (a+1274)%255 + 1        /* creates number equivalent modulo 255 */
															   /* which is valid non-zero character    */

		#define MOD_ADD(a,b,c,d)       NORMALIZE(C2I(a)+C2I(b)+C2I(c)+C2I(d))   /* addition modulo 255 */
		#define MOD_SUBTR(a,b,c,d)     NORMALIZE(C2I(a)-C2I(b)-C2I(c)-C2I(d))   /* subtraction modulo 255 */

		#define ROUNDS 4

		#define NEXT  (i==x_length-1) ? 0 : i+1        /* index of the next character in x */
		#define LAST  (i==0) ? x_length-1 : i-1        /* index of the last character in x */

		static void ModsubEncrypt(char* x, char* key);
		static void ModsubDecrypt(char* x, char* key);
		
		bool bNothing;
	};

	CLicense();
	virtual ~CLicense();

	static BOOL VerifyLicenseKey(BSTR bstr);
	static BOOL GetLicenseKey(DWORD dwReserved, BSTR* pBstr);
	static BOOL IsLicenseValid();

private:
	static void NormalizeString(char* pstrString);
	static void UnNormalizeString(char* pstrString);
	static BOOL GetLicensePath(char* pBuffer);
	static void LicenseError(char* pstrMsg);
	static BOOL UnEncryptString(const char* pstrValue, char* pstrResult);
	static BOOL EncryptString(const char* pstrString, char* pstrResult);

};




#endif // !defined(AFX_LICENSE_H__FD69A43F_F0F5_4DCB_B4F1_9B12DC454DEB__INCLUDED_)
