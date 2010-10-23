/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed May 21 14:07:03 2003
 */
/* Compiler settings for X:\Dev\OutsourcedProjects\Burn\DiscRecord\ObjAudio\AudioRecord.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __AudioRecord_h__
#define __AudioRecord_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IAudioRecordObj_FWD_DEFINED__
#define __IAudioRecordObj_FWD_DEFINED__
typedef interface IAudioRecordObj IAudioRecordObj;
#endif 	/* __IAudioRecordObj_FWD_DEFINED__ */


#ifndef ___IAudioRecordObjEvents_FWD_DEFINED__
#define ___IAudioRecordObjEvents_FWD_DEFINED__
typedef interface _IAudioRecordObjEvents _IAudioRecordObjEvents;
#endif 	/* ___IAudioRecordObjEvents_FWD_DEFINED__ */


#ifndef __AudioRecordObj_FWD_DEFINED__
#define __AudioRecordObj_FWD_DEFINED__

#ifdef __cplusplus
typedef class AudioRecordObj AudioRecordObj;
#else
typedef struct AudioRecordObj AudioRecordObj;
#endif /* __cplusplus */

#endif 	/* __AudioRecordObj_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __AUDIORECORDLib_LIBRARY_DEFINED__
#define __AUDIORECORDLib_LIBRARY_DEFINED__

/* library AUDIORECORDLib */
/* [helpstring][version][uuid] */ 

typedef 
enum DiscType
    {	discCDRW	= 0,
	discCDR	= discCDRW + 1,
	discCD	= discCDR + 1,
	discDVD	= discCD + 1,
	discCDI	= discDVD + 1,
	discCDXA	= discCDI + 1
    }	EnumDiscType;

typedef 
enum DiscState
    {	discNotAvailable	= 0,
	discEmpty	= discNotAvailable + 1,
	discOpen	= discEmpty + 1,
	discClosed	= discOpen + 1
    }	EnumDiscState;

typedef 
enum Status
    {	statusNothing	= 0,
	statusWritingISO	= statusNothing + 1,
	statusWritingData	= statusWritingISO + 1,
	statusSyncingCache	= statusWritingData + 1,
	statusClosingTrack	= statusSyncingCache + 1,
	statusClosingSession	= statusClosingTrack + 1,
	statusSendingOPC	= statusClosingSession + 1,
	statusSessionInit	= statusSendingOPC + 1,
	statusTrackInit	= statusSessionInit + 1,
	statusUserAbort	= statusTrackInit + 1,
	statusEject	= statusUserAbort + 1,
	statusInitializing	= statusEject + 1,
	statusComplete	= statusInitializing + 1,
	statusErrorISOFileOpen	= statusComplete + 1,
	statusFileOpenFailed	= statusErrorISOFileOpen + 1,
	statusErrorReadFailed	= statusFileOpenFailed + 1,
	statusErrorDeviceNotReady	= statusErrorReadFailed + 1,
	statusErrorIO	= statusErrorDeviceNotReady + 1,
	statusErrorModePage	= statusErrorIO + 1,
	statusErrorTrackData	= statusErrorModePage + 1,
	statusErrorSessionData	= statusErrorTrackData + 1,
	statusErrorNoASPI	= statusErrorSessionData + 1,
	statusErrorAddr	= statusErrorNoASPI + 1,
	statusErrorDiscSpace	= statusErrorAddr + 1,
	statusErrorNotWriteable	= statusErrorDiscSpace + 1,
	statusErrorCueSheet	= statusErrorNotWriteable + 1,
	statusErrorReadDisc	= statusErrorCueSheet + 1
    }	EnumStatus;

typedef 
enum StatusType
    {	statusMessage	= 0,
	statusWarning	= statusMessage + 1,
	statusError	= statusWarning + 1,
	statusTrace	= statusError + 1
    }	EnumStatusType;

typedef 
enum Communication
    {	commASPI	= 0,
	commSPTI	= commASPI + 1
    }	EnumCommunication;

typedef 
enum WriteType
    {	writeTAO	= 0,
	writeSAO	= 1
    }	EnumWriteType;

typedef 
enum Feature
    {	featureCDR	= 0,
	featureCDRW	= featureCDR + 1,
	featureDVDRAM	= featureCDRW + 1,
	featureDVDROM	= featureDVDRAM + 1,
	featureDVDR	= featureDVDROM + 1,
	featureBufferProtect	= featureDVDR + 1,
	featureTAO	= featureBufferProtect + 1,
	featureDAO	= featureTAO + 1,
	featureSAO	= featureDAO + 1
    }	EnumFeature;

typedef 
enum FeatureSupport
    {	featureUnknown	= 0,
	featureNotSupported	= featureUnknown + 1,
	featureSupported	= featureNotSupported + 1
    }	EnumFeatureSupport;


EXTERN_C const IID LIBID_AUDIORECORDLib;

#ifndef __IAudioRecordObj_INTERFACE_DEFINED__
#define __IAudioRecordObj_INTERFACE_DEFINED__

/* interface IAudioRecordObj */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IAudioRecordObj;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("48C77DF0-CB4A-47C6-BDA3-FD6C8401556A")
    IAudioRecordObj : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ListDevices( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Initialize( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FileSelectDialog( 
            /* [in] */ long HwndParent,
            /* [in] */ VARIANT_BOOL IsSaveDialog,
            /* [in] */ BSTR FilterMask,
            /* [in] */ BSTR DefaultExt,
            /* [in] */ long nFilterIndex,
            /* [retval][out] */ BSTR __RPC_FAR *pResult) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Duration( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Progress( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentDevice( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CurrentDevice( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EjectDevice( 
            /* [in] */ VARIANT_BOOL bEject) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AbortBurn( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DiscType( 
            /* [retval][out] */ EnumDiscType __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DiscState( 
            /* [retval][out] */ EnumDiscState __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DiscCapacity( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_WriteSpeed( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_WriteSpeed( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ListAvailableWriteSpeeds( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DriveBufferInfo( 
            /* [out] */ long __RPC_FAR *BufferSize,
            /* [out] */ long __RPC_FAR *BufferFree) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TestMode( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TestMode( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DiscSize( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EjectWhenDone( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EjectWhenDone( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ClearDirectoryStructure( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddAudioTrack( 
            /* [in] */ BSTR SourceFile,
            /* [retval][out] */ double __RPC_FAR *pdDuration) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE BurnAudioCD( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AbortFileScan( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ListAudioTracks( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TotalAudioTrackDuration( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TotalFileSize( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DiscCapacitySeconds( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurTrack( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurLBA( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileBufferSize( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileBufferUsed( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TimeElapsed( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveAudioTrack( 
            /* [in] */ long Index) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BurnProof( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BurnProof( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MoveAudioTrack( 
            /* [in] */ long Index,
            /* [in] */ long NewIndex) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DurationTime( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProgressTime( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AudioPause( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AudioPause( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartDiscErase( 
            /* [in] */ VARIANT_BOOL QuickErase) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EraseProgress( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CommMethod( 
            /* [retval][out] */ EnumCommunication __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CommMethod( 
            /* [in] */ EnumCommunication newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PreferredCommMethod( 
            /* [retval][out] */ EnumCommunication __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_WriteType( 
            /* [retval][out] */ EnumWriteType __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_WriteType( 
            /* [in] */ EnumWriteType newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AudioTrackDuration( 
            /* [in] */ long Index,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDriveInfo( 
            /* [out] */ BSTR __RPC_FAR *DriveName,
            /* [out] */ BSTR __RPC_FAR *FirmwareVersion,
            /* [out] */ long __RPC_FAR *BufferSize,
            /* [out] */ BSTR __RPC_FAR *Date,
            /* [out] */ BSTR __RPC_FAR *SerialNumber) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ListAvailableReadSpeeds( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ReadFeatureSupported( 
            /* [in] */ EnumFeature FeatureName,
            /* [retval][out] */ EnumFeatureSupport __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_WriteFeatureSupported( 
            /* [in] */ EnumFeature FeatureName,
            /* [retval][out] */ EnumFeatureSupport __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAudioRecordObjVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAudioRecordObj __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAudioRecordObj __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ListDevices )( 
            IAudioRecordObj __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IAudioRecordObj __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FileSelectDialog )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [in] */ long HwndParent,
            /* [in] */ VARIANT_BOOL IsSaveDialog,
            /* [in] */ BSTR FilterMask,
            /* [in] */ BSTR DefaultExt,
            /* [in] */ long nFilterIndex,
            /* [retval][out] */ BSTR __RPC_FAR *pResult);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Duration )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Progress )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentDevice )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CurrentDevice )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EjectDevice )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL bEject);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AbortBurn )( 
            IAudioRecordObj __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DiscType )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [retval][out] */ EnumDiscType __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DiscState )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [retval][out] */ EnumDiscState __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DiscCapacity )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WriteSpeed )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WriteSpeed )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ListAvailableWriteSpeeds )( 
            IAudioRecordObj __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DriveBufferInfo )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *BufferSize,
            /* [out] */ long __RPC_FAR *BufferFree);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TestMode )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TestMode )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DiscSize )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EjectWhenDone )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EjectWhenDone )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ClearDirectoryStructure )( 
            IAudioRecordObj __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddAudioTrack )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [in] */ BSTR SourceFile,
            /* [retval][out] */ double __RPC_FAR *pdDuration);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BurnAudioCD )( 
            IAudioRecordObj __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AbortFileScan )( 
            IAudioRecordObj __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ListAudioTracks )( 
            IAudioRecordObj __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TotalAudioTrackDuration )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TotalFileSize )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DiscCapacitySeconds )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurTrack )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurLBA )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FileBufferSize )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FileBufferUsed )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TimeElapsed )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveAudioTrack )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [in] */ long Index);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BurnProof )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BurnProof )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MoveAudioTrack )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [in] */ long Index,
            /* [in] */ long NewIndex);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DurationTime )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProgressTime )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AudioPause )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AudioPause )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartDiscErase )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL QuickErase);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EraseProgress )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CommMethod )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [retval][out] */ EnumCommunication __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CommMethod )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [in] */ EnumCommunication newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PreferredCommMethod )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [retval][out] */ EnumCommunication __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WriteType )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [retval][out] */ EnumWriteType __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WriteType )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [in] */ EnumWriteType newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AudioTrackDuration )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [in] */ long Index,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDriveInfo )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *DriveName,
            /* [out] */ BSTR __RPC_FAR *FirmwareVersion,
            /* [out] */ long __RPC_FAR *BufferSize,
            /* [out] */ BSTR __RPC_FAR *Date,
            /* [out] */ BSTR __RPC_FAR *SerialNumber);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ListAvailableReadSpeeds )( 
            IAudioRecordObj __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReadFeatureSupported )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [in] */ EnumFeature FeatureName,
            /* [retval][out] */ EnumFeatureSupport __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WriteFeatureSupported )( 
            IAudioRecordObj __RPC_FAR * This,
            /* [in] */ EnumFeature FeatureName,
            /* [retval][out] */ EnumFeatureSupport __RPC_FAR *pVal);
        
        END_INTERFACE
    } IAudioRecordObjVtbl;

    interface IAudioRecordObj
    {
        CONST_VTBL struct IAudioRecordObjVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAudioRecordObj_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAudioRecordObj_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAudioRecordObj_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAudioRecordObj_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAudioRecordObj_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAudioRecordObj_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAudioRecordObj_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAudioRecordObj_ListDevices(This)	\
    (This)->lpVtbl -> ListDevices(This)

#define IAudioRecordObj_Initialize(This)	\
    (This)->lpVtbl -> Initialize(This)

#define IAudioRecordObj_FileSelectDialog(This,HwndParent,IsSaveDialog,FilterMask,DefaultExt,nFilterIndex,pResult)	\
    (This)->lpVtbl -> FileSelectDialog(This,HwndParent,IsSaveDialog,FilterMask,DefaultExt,nFilterIndex,pResult)

#define IAudioRecordObj_get_Duration(This,pVal)	\
    (This)->lpVtbl -> get_Duration(This,pVal)

#define IAudioRecordObj_get_Progress(This,pVal)	\
    (This)->lpVtbl -> get_Progress(This,pVal)

#define IAudioRecordObj_get_CurrentDevice(This,pVal)	\
    (This)->lpVtbl -> get_CurrentDevice(This,pVal)

#define IAudioRecordObj_put_CurrentDevice(This,newVal)	\
    (This)->lpVtbl -> put_CurrentDevice(This,newVal)

#define IAudioRecordObj_EjectDevice(This,bEject)	\
    (This)->lpVtbl -> EjectDevice(This,bEject)

#define IAudioRecordObj_AbortBurn(This)	\
    (This)->lpVtbl -> AbortBurn(This)

#define IAudioRecordObj_get_DiscType(This,pVal)	\
    (This)->lpVtbl -> get_DiscType(This,pVal)

#define IAudioRecordObj_get_DiscState(This,pVal)	\
    (This)->lpVtbl -> get_DiscState(This,pVal)

#define IAudioRecordObj_get_DiscCapacity(This,pVal)	\
    (This)->lpVtbl -> get_DiscCapacity(This,pVal)

#define IAudioRecordObj_get_WriteSpeed(This,pVal)	\
    (This)->lpVtbl -> get_WriteSpeed(This,pVal)

#define IAudioRecordObj_put_WriteSpeed(This,newVal)	\
    (This)->lpVtbl -> put_WriteSpeed(This,newVal)

#define IAudioRecordObj_ListAvailableWriteSpeeds(This)	\
    (This)->lpVtbl -> ListAvailableWriteSpeeds(This)

#define IAudioRecordObj_DriveBufferInfo(This,BufferSize,BufferFree)	\
    (This)->lpVtbl -> DriveBufferInfo(This,BufferSize,BufferFree)

#define IAudioRecordObj_get_TestMode(This,pVal)	\
    (This)->lpVtbl -> get_TestMode(This,pVal)

#define IAudioRecordObj_put_TestMode(This,newVal)	\
    (This)->lpVtbl -> put_TestMode(This,newVal)

#define IAudioRecordObj_get_DiscSize(This,pVal)	\
    (This)->lpVtbl -> get_DiscSize(This,pVal)

#define IAudioRecordObj_get_EjectWhenDone(This,pVal)	\
    (This)->lpVtbl -> get_EjectWhenDone(This,pVal)

#define IAudioRecordObj_put_EjectWhenDone(This,newVal)	\
    (This)->lpVtbl -> put_EjectWhenDone(This,newVal)

#define IAudioRecordObj_ClearDirectoryStructure(This)	\
    (This)->lpVtbl -> ClearDirectoryStructure(This)

#define IAudioRecordObj_AddAudioTrack(This,SourceFile,pdDuration)	\
    (This)->lpVtbl -> AddAudioTrack(This,SourceFile,pdDuration)

#define IAudioRecordObj_BurnAudioCD(This)	\
    (This)->lpVtbl -> BurnAudioCD(This)

#define IAudioRecordObj_AbortFileScan(This)	\
    (This)->lpVtbl -> AbortFileScan(This)

#define IAudioRecordObj_ListAudioTracks(This)	\
    (This)->lpVtbl -> ListAudioTracks(This)

#define IAudioRecordObj_get_TotalAudioTrackDuration(This,pVal)	\
    (This)->lpVtbl -> get_TotalAudioTrackDuration(This,pVal)

#define IAudioRecordObj_get_TotalFileSize(This,pVal)	\
    (This)->lpVtbl -> get_TotalFileSize(This,pVal)

#define IAudioRecordObj_get_DiscCapacitySeconds(This,pVal)	\
    (This)->lpVtbl -> get_DiscCapacitySeconds(This,pVal)

#define IAudioRecordObj_get_CurTrack(This,pVal)	\
    (This)->lpVtbl -> get_CurTrack(This,pVal)

#define IAudioRecordObj_get_CurLBA(This,pVal)	\
    (This)->lpVtbl -> get_CurLBA(This,pVal)

#define IAudioRecordObj_get_FileBufferSize(This,pVal)	\
    (This)->lpVtbl -> get_FileBufferSize(This,pVal)

#define IAudioRecordObj_get_FileBufferUsed(This,pVal)	\
    (This)->lpVtbl -> get_FileBufferUsed(This,pVal)

#define IAudioRecordObj_get_TimeElapsed(This,pVal)	\
    (This)->lpVtbl -> get_TimeElapsed(This,pVal)

#define IAudioRecordObj_RemoveAudioTrack(This,Index)	\
    (This)->lpVtbl -> RemoveAudioTrack(This,Index)

#define IAudioRecordObj_get_BurnProof(This,pVal)	\
    (This)->lpVtbl -> get_BurnProof(This,pVal)

#define IAudioRecordObj_put_BurnProof(This,newVal)	\
    (This)->lpVtbl -> put_BurnProof(This,newVal)

#define IAudioRecordObj_MoveAudioTrack(This,Index,NewIndex)	\
    (This)->lpVtbl -> MoveAudioTrack(This,Index,NewIndex)

#define IAudioRecordObj_get_DurationTime(This,pVal)	\
    (This)->lpVtbl -> get_DurationTime(This,pVal)

#define IAudioRecordObj_get_ProgressTime(This,pVal)	\
    (This)->lpVtbl -> get_ProgressTime(This,pVal)

#define IAudioRecordObj_get_AudioPause(This,pVal)	\
    (This)->lpVtbl -> get_AudioPause(This,pVal)

#define IAudioRecordObj_put_AudioPause(This,newVal)	\
    (This)->lpVtbl -> put_AudioPause(This,newVal)

#define IAudioRecordObj_StartDiscErase(This,QuickErase)	\
    (This)->lpVtbl -> StartDiscErase(This,QuickErase)

#define IAudioRecordObj_get_EraseProgress(This,pVal)	\
    (This)->lpVtbl -> get_EraseProgress(This,pVal)

#define IAudioRecordObj_get_CommMethod(This,pVal)	\
    (This)->lpVtbl -> get_CommMethod(This,pVal)

#define IAudioRecordObj_put_CommMethod(This,newVal)	\
    (This)->lpVtbl -> put_CommMethod(This,newVal)

#define IAudioRecordObj_get_PreferredCommMethod(This,pVal)	\
    (This)->lpVtbl -> get_PreferredCommMethod(This,pVal)

#define IAudioRecordObj_get_WriteType(This,pVal)	\
    (This)->lpVtbl -> get_WriteType(This,pVal)

#define IAudioRecordObj_put_WriteType(This,newVal)	\
    (This)->lpVtbl -> put_WriteType(This,newVal)

#define IAudioRecordObj_get_AudioTrackDuration(This,Index,pVal)	\
    (This)->lpVtbl -> get_AudioTrackDuration(This,Index,pVal)

#define IAudioRecordObj_GetDriveInfo(This,DriveName,FirmwareVersion,BufferSize,Date,SerialNumber)	\
    (This)->lpVtbl -> GetDriveInfo(This,DriveName,FirmwareVersion,BufferSize,Date,SerialNumber)

#define IAudioRecordObj_ListAvailableReadSpeeds(This)	\
    (This)->lpVtbl -> ListAvailableReadSpeeds(This)

#define IAudioRecordObj_get_ReadFeatureSupported(This,FeatureName,pVal)	\
    (This)->lpVtbl -> get_ReadFeatureSupported(This,FeatureName,pVal)

#define IAudioRecordObj_get_WriteFeatureSupported(This,FeatureName,pVal)	\
    (This)->lpVtbl -> get_WriteFeatureSupported(This,FeatureName,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_ListDevices_Proxy( 
    IAudioRecordObj __RPC_FAR * This);


void __RPC_STUB IAudioRecordObj_ListDevices_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_Initialize_Proxy( 
    IAudioRecordObj __RPC_FAR * This);


void __RPC_STUB IAudioRecordObj_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_FileSelectDialog_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [in] */ long HwndParent,
    /* [in] */ VARIANT_BOOL IsSaveDialog,
    /* [in] */ BSTR FilterMask,
    /* [in] */ BSTR DefaultExt,
    /* [in] */ long nFilterIndex,
    /* [retval][out] */ BSTR __RPC_FAR *pResult);


void __RPC_STUB IAudioRecordObj_FileSelectDialog_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_get_Duration_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IAudioRecordObj_get_Duration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_get_Progress_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IAudioRecordObj_get_Progress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_get_CurrentDevice_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IAudioRecordObj_get_CurrentDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_put_CurrentDevice_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IAudioRecordObj_put_CurrentDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_EjectDevice_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL bEject);


void __RPC_STUB IAudioRecordObj_EjectDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_AbortBurn_Proxy( 
    IAudioRecordObj __RPC_FAR * This);


void __RPC_STUB IAudioRecordObj_AbortBurn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_get_DiscType_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [retval][out] */ EnumDiscType __RPC_FAR *pVal);


void __RPC_STUB IAudioRecordObj_get_DiscType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_get_DiscState_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [retval][out] */ EnumDiscState __RPC_FAR *pVal);


void __RPC_STUB IAudioRecordObj_get_DiscState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_get_DiscCapacity_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IAudioRecordObj_get_DiscCapacity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_get_WriteSpeed_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IAudioRecordObj_get_WriteSpeed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_put_WriteSpeed_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IAudioRecordObj_put_WriteSpeed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_ListAvailableWriteSpeeds_Proxy( 
    IAudioRecordObj __RPC_FAR * This);


void __RPC_STUB IAudioRecordObj_ListAvailableWriteSpeeds_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_DriveBufferInfo_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *BufferSize,
    /* [out] */ long __RPC_FAR *BufferFree);


void __RPC_STUB IAudioRecordObj_DriveBufferInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_get_TestMode_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IAudioRecordObj_get_TestMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_put_TestMode_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IAudioRecordObj_put_TestMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_get_DiscSize_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IAudioRecordObj_get_DiscSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_get_EjectWhenDone_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IAudioRecordObj_get_EjectWhenDone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_put_EjectWhenDone_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IAudioRecordObj_put_EjectWhenDone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_ClearDirectoryStructure_Proxy( 
    IAudioRecordObj __RPC_FAR * This);


void __RPC_STUB IAudioRecordObj_ClearDirectoryStructure_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_AddAudioTrack_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [in] */ BSTR SourceFile,
    /* [retval][out] */ double __RPC_FAR *pdDuration);


void __RPC_STUB IAudioRecordObj_AddAudioTrack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_BurnAudioCD_Proxy( 
    IAudioRecordObj __RPC_FAR * This);


void __RPC_STUB IAudioRecordObj_BurnAudioCD_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_AbortFileScan_Proxy( 
    IAudioRecordObj __RPC_FAR * This);


void __RPC_STUB IAudioRecordObj_AbortFileScan_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_ListAudioTracks_Proxy( 
    IAudioRecordObj __RPC_FAR * This);


void __RPC_STUB IAudioRecordObj_ListAudioTracks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_get_TotalAudioTrackDuration_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IAudioRecordObj_get_TotalAudioTrackDuration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_get_TotalFileSize_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IAudioRecordObj_get_TotalFileSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_get_DiscCapacitySeconds_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IAudioRecordObj_get_DiscCapacitySeconds_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_get_CurTrack_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IAudioRecordObj_get_CurTrack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_get_CurLBA_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IAudioRecordObj_get_CurLBA_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_get_FileBufferSize_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IAudioRecordObj_get_FileBufferSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_get_FileBufferUsed_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IAudioRecordObj_get_FileBufferUsed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_get_TimeElapsed_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IAudioRecordObj_get_TimeElapsed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_RemoveAudioTrack_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [in] */ long Index);


void __RPC_STUB IAudioRecordObj_RemoveAudioTrack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_get_BurnProof_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IAudioRecordObj_get_BurnProof_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_put_BurnProof_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IAudioRecordObj_put_BurnProof_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_MoveAudioTrack_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [in] */ long Index,
    /* [in] */ long NewIndex);


void __RPC_STUB IAudioRecordObj_MoveAudioTrack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_get_DurationTime_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IAudioRecordObj_get_DurationTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_get_ProgressTime_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IAudioRecordObj_get_ProgressTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_get_AudioPause_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IAudioRecordObj_get_AudioPause_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_put_AudioPause_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IAudioRecordObj_put_AudioPause_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_StartDiscErase_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL QuickErase);


void __RPC_STUB IAudioRecordObj_StartDiscErase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_get_EraseProgress_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IAudioRecordObj_get_EraseProgress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_get_CommMethod_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [retval][out] */ EnumCommunication __RPC_FAR *pVal);


void __RPC_STUB IAudioRecordObj_get_CommMethod_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_put_CommMethod_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [in] */ EnumCommunication newVal);


void __RPC_STUB IAudioRecordObj_put_CommMethod_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_get_PreferredCommMethod_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [retval][out] */ EnumCommunication __RPC_FAR *pVal);


void __RPC_STUB IAudioRecordObj_get_PreferredCommMethod_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_get_WriteType_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [retval][out] */ EnumWriteType __RPC_FAR *pVal);


void __RPC_STUB IAudioRecordObj_get_WriteType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_put_WriteType_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [in] */ EnumWriteType newVal);


void __RPC_STUB IAudioRecordObj_put_WriteType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_get_AudioTrackDuration_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [in] */ long Index,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IAudioRecordObj_get_AudioTrackDuration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_GetDriveInfo_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *DriveName,
    /* [out] */ BSTR __RPC_FAR *FirmwareVersion,
    /* [out] */ long __RPC_FAR *BufferSize,
    /* [out] */ BSTR __RPC_FAR *Date,
    /* [out] */ BSTR __RPC_FAR *SerialNumber);


void __RPC_STUB IAudioRecordObj_GetDriveInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_ListAvailableReadSpeeds_Proxy( 
    IAudioRecordObj __RPC_FAR * This);


void __RPC_STUB IAudioRecordObj_ListAvailableReadSpeeds_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_get_ReadFeatureSupported_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [in] */ EnumFeature FeatureName,
    /* [retval][out] */ EnumFeatureSupport __RPC_FAR *pVal);


void __RPC_STUB IAudioRecordObj_get_ReadFeatureSupported_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAudioRecordObj_get_WriteFeatureSupported_Proxy( 
    IAudioRecordObj __RPC_FAR * This,
    /* [in] */ EnumFeature FeatureName,
    /* [retval][out] */ EnumFeatureSupport __RPC_FAR *pVal);


void __RPC_STUB IAudioRecordObj_get_WriteFeatureSupported_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAudioRecordObj_INTERFACE_DEFINED__ */


#ifndef ___IAudioRecordObjEvents_DISPINTERFACE_DEFINED__
#define ___IAudioRecordObjEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IAudioRecordObjEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IAudioRecordObjEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("262CCA6C-01C2-4585-8123-976D20937E98")
    _IAudioRecordObjEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IAudioRecordObjEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IAudioRecordObjEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IAudioRecordObjEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IAudioRecordObjEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IAudioRecordObjEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IAudioRecordObjEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IAudioRecordObjEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IAudioRecordObjEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IAudioRecordObjEventsVtbl;

    interface _IAudioRecordObjEvents
    {
        CONST_VTBL struct _IAudioRecordObjEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IAudioRecordObjEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IAudioRecordObjEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IAudioRecordObjEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IAudioRecordObjEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IAudioRecordObjEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IAudioRecordObjEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IAudioRecordObjEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IAudioRecordObjEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_AudioRecordObj;

#ifdef __cplusplus

class DECLSPEC_UUID("01AD1373-8240-4926-BC8F-331845EC1F70")
AudioRecordObj;
#endif
#endif /* __AUDIORECORDLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
