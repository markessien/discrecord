/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed May 21 14:07:03 2003
 */
/* Compiler settings for X:\Dev\OutsourcedProjects\Burn\DiscRecord\ObjAudio\AudioRecord.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID LIBID_AUDIORECORDLib = {0xB53696AB,0x693D,0x452E,{0x8A,0xA5,0x73,0x53,0x93,0x21,0x88,0xAE}};


const IID IID_IAudioRecordObj = {0x48C77DF0,0xCB4A,0x47C6,{0xBD,0xA3,0xFD,0x6C,0x84,0x01,0x55,0x6A}};


const IID DIID__IAudioRecordObjEvents = {0x262CCA6C,0x01C2,0x4585,{0x81,0x23,0x97,0x6D,0x20,0x93,0x7E,0x98}};


const CLSID CLSID_AudioRecordObj = {0x01AD1373,0x8240,0x4926,{0xBC,0x8F,0x33,0x18,0x45,0xEC,0x1F,0x70}};


#ifdef __cplusplus
}
#endif

