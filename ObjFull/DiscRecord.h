/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Feb 07 13:16:24 2005
 */
/* Compiler settings for C:\Personal\Dev\OutsourcedProjects\Burn\DiscRecord\ObjFull\DiscRecord.idl:
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

#ifndef __DiscRecord_h__
#define __DiscRecord_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IFileItem_FWD_DEFINED__
#define __IFileItem_FWD_DEFINED__
typedef interface IFileItem IFileItem;
#endif 	/* __IFileItem_FWD_DEFINED__ */


#ifndef __IAudioItem_FWD_DEFINED__
#define __IAudioItem_FWD_DEFINED__
typedef interface IAudioItem IAudioItem;
#endif 	/* __IAudioItem_FWD_DEFINED__ */


#ifndef __IDiscRecordObj_FWD_DEFINED__
#define __IDiscRecordObj_FWD_DEFINED__
typedef interface IDiscRecordObj IDiscRecordObj;
#endif 	/* __IDiscRecordObj_FWD_DEFINED__ */


#ifndef ___IAudioItemEvents_FWD_DEFINED__
#define ___IAudioItemEvents_FWD_DEFINED__
typedef interface _IAudioItemEvents _IAudioItemEvents;
#endif 	/* ___IAudioItemEvents_FWD_DEFINED__ */


#ifndef ___IDiscRecordObjEvents_FWD_DEFINED__
#define ___IDiscRecordObjEvents_FWD_DEFINED__
typedef interface _IDiscRecordObjEvents _IDiscRecordObjEvents;
#endif 	/* ___IDiscRecordObjEvents_FWD_DEFINED__ */


#ifndef __DiscRecord_FWD_DEFINED__
#define __DiscRecord_FWD_DEFINED__

#ifdef __cplusplus
typedef class DiscRecord DiscRecord;
#else
typedef struct DiscRecord DiscRecord;
#endif /* __cplusplus */

#endif 	/* __DiscRecord_FWD_DEFINED__ */


#ifndef __FileItem_FWD_DEFINED__
#define __FileItem_FWD_DEFINED__

#ifdef __cplusplus
typedef class FileItem FileItem;
#else
typedef struct FileItem FileItem;
#endif /* __cplusplus */

#endif 	/* __FileItem_FWD_DEFINED__ */


#ifndef __AudioItem_FWD_DEFINED__
#define __AudioItem_FWD_DEFINED__

#ifdef __cplusplus
typedef class AudioItem AudioItem;
#else
typedef struct AudioItem AudioItem;
#endif /* __cplusplus */

#endif 	/* __AudioItem_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __DISCRECORDLib_LIBRARY_DEFINED__
#define __DISCRECORDLib_LIBRARY_DEFINED__

/* library DISCRECORDLib */
/* [helpstring][version][uuid] */ 

typedef 
enum FileType
    {	typeFile	= 0,
	typeDirectory	= typeFile + 1
    }	EnumFileType;

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
	statusWritingTOC	= statusComplete + 1,
	statusErrorISOFileOpen	= statusWritingTOC + 1,
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


EXTERN_C const IID LIBID_DISCRECORDLib;

#ifndef __IFileItem_INTERFACE_DEFINED__
#define __IFileItem_INTERFACE_DEFINED__

/* interface IFileItem */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IFileItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5BE10F89-5990-41D7-B9F8-C5B9F357BEC5")
    IFileItem : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ EnumFileType __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LocalPath( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LocalPath( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Size( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SubFileCount( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SubFile( 
            /* [in] */ long Index,
            /* [retval][out] */ IFileItem __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddFile( 
            /* [in] */ BSTR LocalPath,
            /* [retval][out] */ IFileItem __RPC_FAR *__RPC_FAR *ppItem) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveByIndex( 
            /* [in] */ long Index) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddEmptyFolder( 
            /* [in] */ BSTR Name,
            /* [retval][out] */ IFileItem __RPC_FAR *__RPC_FAR *ppItem) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Sort( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IFileItem __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE XPathAddFile( 
            /* [in] */ BSTR LocalPath,
            /* [in] */ BSTR PathOnCD) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE XPathAddEmptyFolder( 
            /* [in] */ BSTR Name,
            /* [in] */ BSTR PathOnCD) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FindSubItem( 
            /* [in] */ BSTR RelativePath,
            /* [retval][out] */ IFileItem __RPC_FAR *__RPC_FAR *ppItem) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFileItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IFileItem __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IFileItem __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IFileItem __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IFileItem __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IFileItem __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IFileItem __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IFileItem __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            IFileItem __RPC_FAR * This,
            /* [retval][out] */ EnumFileType __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IFileItem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            IFileItem __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocalPath )( 
            IFileItem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LocalPath )( 
            IFileItem __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Size )( 
            IFileItem __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SubFileCount )( 
            IFileItem __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SubFile )( 
            IFileItem __RPC_FAR * This,
            /* [in] */ long Index,
            /* [retval][out] */ IFileItem __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddFile )( 
            IFileItem __RPC_FAR * This,
            /* [in] */ BSTR LocalPath,
            /* [retval][out] */ IFileItem __RPC_FAR *__RPC_FAR *ppItem);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveByIndex )( 
            IFileItem __RPC_FAR * This,
            /* [in] */ long Index);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddEmptyFolder )( 
            IFileItem __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [retval][out] */ IFileItem __RPC_FAR *__RPC_FAR *ppItem);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Sort )( 
            IFileItem __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clear )( 
            IFileItem __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IFileItem __RPC_FAR * This,
            /* [retval][out] */ IFileItem __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *XPathAddFile )( 
            IFileItem __RPC_FAR * This,
            /* [in] */ BSTR LocalPath,
            /* [in] */ BSTR PathOnCD);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *XPathAddEmptyFolder )( 
            IFileItem __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [in] */ BSTR PathOnCD);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindSubItem )( 
            IFileItem __RPC_FAR * This,
            /* [in] */ BSTR RelativePath,
            /* [retval][out] */ IFileItem __RPC_FAR *__RPC_FAR *ppItem);
        
        END_INTERFACE
    } IFileItemVtbl;

    interface IFileItem
    {
        CONST_VTBL struct IFileItemVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFileItem_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFileItem_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IFileItem_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IFileItem_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IFileItem_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IFileItem_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IFileItem_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IFileItem_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define IFileItem_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IFileItem_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define IFileItem_get_LocalPath(This,pVal)	\
    (This)->lpVtbl -> get_LocalPath(This,pVal)

#define IFileItem_put_LocalPath(This,newVal)	\
    (This)->lpVtbl -> put_LocalPath(This,newVal)

#define IFileItem_get_Size(This,pVal)	\
    (This)->lpVtbl -> get_Size(This,pVal)

#define IFileItem_get_SubFileCount(This,pVal)	\
    (This)->lpVtbl -> get_SubFileCount(This,pVal)

#define IFileItem_get_SubFile(This,Index,pVal)	\
    (This)->lpVtbl -> get_SubFile(This,Index,pVal)

#define IFileItem_AddFile(This,LocalPath,ppItem)	\
    (This)->lpVtbl -> AddFile(This,LocalPath,ppItem)

#define IFileItem_RemoveByIndex(This,Index)	\
    (This)->lpVtbl -> RemoveByIndex(This,Index)

#define IFileItem_AddEmptyFolder(This,Name,ppItem)	\
    (This)->lpVtbl -> AddEmptyFolder(This,Name,ppItem)

#define IFileItem_Sort(This)	\
    (This)->lpVtbl -> Sort(This)

#define IFileItem_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#define IFileItem_get_Parent(This,pVal)	\
    (This)->lpVtbl -> get_Parent(This,pVal)

#define IFileItem_XPathAddFile(This,LocalPath,PathOnCD)	\
    (This)->lpVtbl -> XPathAddFile(This,LocalPath,PathOnCD)

#define IFileItem_XPathAddEmptyFolder(This,Name,PathOnCD)	\
    (This)->lpVtbl -> XPathAddEmptyFolder(This,Name,PathOnCD)

#define IFileItem_FindSubItem(This,RelativePath,ppItem)	\
    (This)->lpVtbl -> FindSubItem(This,RelativePath,ppItem)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFileItem_get_Type_Proxy( 
    IFileItem __RPC_FAR * This,
    /* [retval][out] */ EnumFileType __RPC_FAR *pVal);


void __RPC_STUB IFileItem_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFileItem_get_Name_Proxy( 
    IFileItem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IFileItem_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IFileItem_put_Name_Proxy( 
    IFileItem __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IFileItem_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFileItem_get_LocalPath_Proxy( 
    IFileItem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IFileItem_get_LocalPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IFileItem_put_LocalPath_Proxy( 
    IFileItem __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IFileItem_put_LocalPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFileItem_get_Size_Proxy( 
    IFileItem __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IFileItem_get_Size_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFileItem_get_SubFileCount_Proxy( 
    IFileItem __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IFileItem_get_SubFileCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFileItem_get_SubFile_Proxy( 
    IFileItem __RPC_FAR * This,
    /* [in] */ long Index,
    /* [retval][out] */ IFileItem __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IFileItem_get_SubFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileItem_AddFile_Proxy( 
    IFileItem __RPC_FAR * This,
    /* [in] */ BSTR LocalPath,
    /* [retval][out] */ IFileItem __RPC_FAR *__RPC_FAR *ppItem);


void __RPC_STUB IFileItem_AddFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileItem_RemoveByIndex_Proxy( 
    IFileItem __RPC_FAR * This,
    /* [in] */ long Index);


void __RPC_STUB IFileItem_RemoveByIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileItem_AddEmptyFolder_Proxy( 
    IFileItem __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [retval][out] */ IFileItem __RPC_FAR *__RPC_FAR *ppItem);


void __RPC_STUB IFileItem_AddEmptyFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileItem_Sort_Proxy( 
    IFileItem __RPC_FAR * This);


void __RPC_STUB IFileItem_Sort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileItem_Clear_Proxy( 
    IFileItem __RPC_FAR * This);


void __RPC_STUB IFileItem_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFileItem_get_Parent_Proxy( 
    IFileItem __RPC_FAR * This,
    /* [retval][out] */ IFileItem __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IFileItem_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileItem_XPathAddFile_Proxy( 
    IFileItem __RPC_FAR * This,
    /* [in] */ BSTR LocalPath,
    /* [in] */ BSTR PathOnCD);


void __RPC_STUB IFileItem_XPathAddFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileItem_XPathAddEmptyFolder_Proxy( 
    IFileItem __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [in] */ BSTR PathOnCD);


void __RPC_STUB IFileItem_XPathAddEmptyFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileItem_FindSubItem_Proxy( 
    IFileItem __RPC_FAR * This,
    /* [in] */ BSTR RelativePath,
    /* [retval][out] */ IFileItem __RPC_FAR *__RPC_FAR *ppItem);


void __RPC_STUB IFileItem_FindSubItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFileItem_INTERFACE_DEFINED__ */


#ifndef __IAudioItem_INTERFACE_DEFINED__
#define __IAudioItem_INTERFACE_DEFINED__

/* interface IAudioItem */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IAudioItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3015A012-DDCE-44EA-9474-4D6430C874AF")
    IAudioItem : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddTrack( 
            /* [in] */ BSTR SourceFile) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveTrack( 
            /* [in] */ long Index) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TrackCount( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Duration( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LocalFilePath( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Track( 
            /* [in] */ long Index,
            /* [retval][out] */ IAudioItem __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MoveTrack( 
            /* [in] */ long Index,
            /* [in] */ long NewIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddFile( 
            /* [in] */ BSTR SourceFile) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAudioItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAudioItem __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAudioItem __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAudioItem __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAudioItem __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAudioItem __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAudioItem __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAudioItem __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddTrack )( 
            IAudioItem __RPC_FAR * This,
            /* [in] */ BSTR SourceFile);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveTrack )( 
            IAudioItem __RPC_FAR * This,
            /* [in] */ long Index);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TrackCount )( 
            IAudioItem __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Duration )( 
            IAudioItem __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IAudioItem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            IAudioItem __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocalFilePath )( 
            IAudioItem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Track )( 
            IAudioItem __RPC_FAR * This,
            /* [in] */ long Index,
            /* [retval][out] */ IAudioItem __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MoveTrack )( 
            IAudioItem __RPC_FAR * This,
            /* [in] */ long Index,
            /* [in] */ long NewIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddFile )( 
            IAudioItem __RPC_FAR * This,
            /* [in] */ BSTR SourceFile);
        
        END_INTERFACE
    } IAudioItemVtbl;

    interface IAudioItem
    {
        CONST_VTBL struct IAudioItemVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAudioItem_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAudioItem_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAudioItem_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAudioItem_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAudioItem_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAudioItem_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAudioItem_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAudioItem_AddTrack(This,SourceFile)	\
    (This)->lpVtbl -> AddTrack(This,SourceFile)

#define IAudioItem_RemoveTrack(This,Index)	\
    (This)->lpVtbl -> RemoveTrack(This,Index)

#define IAudioItem_get_TrackCount(This,pVal)	\
    (This)->lpVtbl -> get_TrackCount(This,pVal)

#define IAudioItem_get_Duration(This,pVal)	\
    (This)->lpVtbl -> get_Duration(This,pVal)

#define IAudioItem_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IAudioItem_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define IAudioItem_get_LocalFilePath(This,pVal)	\
    (This)->lpVtbl -> get_LocalFilePath(This,pVal)

#define IAudioItem_get_Track(This,Index,pVal)	\
    (This)->lpVtbl -> get_Track(This,Index,pVal)

#define IAudioItem_MoveTrack(This,Index,NewIndex)	\
    (This)->lpVtbl -> MoveTrack(This,Index,NewIndex)

#define IAudioItem_AddFile(This,SourceFile)	\
    (This)->lpVtbl -> AddFile(This,SourceFile)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAudioItem_AddTrack_Proxy( 
    IAudioItem __RPC_FAR * This,
    /* [in] */ BSTR SourceFile);


void __RPC_STUB IAudioItem_AddTrack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAudioItem_RemoveTrack_Proxy( 
    IAudioItem __RPC_FAR * This,
    /* [in] */ long Index);


void __RPC_STUB IAudioItem_RemoveTrack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAudioItem_get_TrackCount_Proxy( 
    IAudioItem __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IAudioItem_get_TrackCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAudioItem_get_Duration_Proxy( 
    IAudioItem __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IAudioItem_get_Duration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAudioItem_get_Name_Proxy( 
    IAudioItem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IAudioItem_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAudioItem_put_Name_Proxy( 
    IAudioItem __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IAudioItem_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAudioItem_get_LocalFilePath_Proxy( 
    IAudioItem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IAudioItem_get_LocalFilePath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAudioItem_get_Track_Proxy( 
    IAudioItem __RPC_FAR * This,
    /* [in] */ long Index,
    /* [retval][out] */ IAudioItem __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IAudioItem_get_Track_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAudioItem_MoveTrack_Proxy( 
    IAudioItem __RPC_FAR * This,
    /* [in] */ long Index,
    /* [in] */ long NewIndex);


void __RPC_STUB IAudioItem_MoveTrack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAudioItem_AddFile_Proxy( 
    IAudioItem __RPC_FAR * This,
    /* [in] */ BSTR SourceFile);


void __RPC_STUB IAudioItem_AddFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAudioItem_INTERFACE_DEFINED__ */


#ifndef __IDiscRecordObj_INTERFACE_DEFINED__
#define __IDiscRecordObj_INTERFACE_DEFINED__

/* interface IDiscRecordObj */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IDiscRecordObj;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7C37EF0E-1178-4ABA-9906-8E52554612D6")
    IDiscRecordObj : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ListDevices( 
            VARIANT_BOOL OnlyWriteable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Initialize( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FileSelectDialog( 
            /* [in] */ long HwndParent,
            /* [in] */ VARIANT_BOOL IsSaveDialog,
            /* [in] */ BSTR FilterMask,
            /* [in] */ BSTR DefaultExt,
            /* [in] */ long nFilterIndex,
            /* [retval][out] */ BSTR __RPC_FAR *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EjectDevice( 
            /* [in] */ VARIANT_BOOL bEject) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AbortBurn( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE BurnFromISO( 
            /* [in] */ BSTR InputISOPath) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE BurnDataCD( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ListAvailableWriteSpeeds( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE QueryDriveBuffer( 
            /* [out] */ long __RPC_FAR *Used,
            /* [out] */ long __RPC_FAR *Length) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ClearFiles( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CopyCDToFixedDrive( 
            /* [in] */ long DeviceIndex,
            /* [in] */ BSTR TargetFile) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE BurnAudioCD( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartDiscErase( 
            /* [in] */ VARIANT_BOOL QuickErase) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE QueryDriveInfo( 
            /* [out] */ BSTR __RPC_FAR *DriveName,
            /* [out] */ BSTR __RPC_FAR *FirmwareVersion,
            /* [out] */ long __RPC_FAR *BufferSize,
            /* [out] */ BSTR __RPC_FAR *Date,
            /* [out] */ BSTR __RPC_FAR *SerialNumber) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ListAvailableReadSpeeds( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE QueryFileBuffer( 
            /* [out] */ long __RPC_FAR *Used,
            /* [out] */ long __RPC_FAR *Length) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProgressMax( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProgressCur( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SelectedWriterDeviceIndex( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SelectedWriterDeviceIndex( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CDLabel( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CDLabel( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DiscType( 
            /* [retval][out] */ EnumDiscType __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DiscState( 
            /* [retval][out] */ EnumDiscState __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DiscCapacityBytes( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentWriteSpeed( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CurrentWriteSpeed( 
            /* [in] */ long newVal) = 0;
        
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
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SelectedWriterDeviceDriveLetter( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DiscCapacitySeconds( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentTrack( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentLBA( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TimeElapsed( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BurnProof( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BurnProof( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProgressMaxSeconds( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PauseBetweenTracks( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PauseBetweenTracks( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CommunicationMethod( 
            /* [retval][out] */ EnumCommunication __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CommunicationMethod( 
            /* [in] */ EnumCommunication newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PreferredCommunicationMethod( 
            /* [retval][out] */ EnumCommunication __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_WriteType( 
            /* [retval][out] */ EnumWriteType __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_WriteType( 
            /* [in] */ EnumWriteType newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ReadFeatureSupported( 
            /* [in] */ EnumFeature FeatureName,
            /* [retval][out] */ EnumFeatureSupport __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_WriteFeatureSupported( 
            /* [in] */ EnumFeature FeatureName,
            /* [retval][out] */ EnumFeatureSupport __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DataDisc( 
            /* [retval][out] */ IFileItem __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AudioDisc( 
            /* [retval][out] */ IAudioItem __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProgressCurSeconds( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Erasing( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TempDirectory( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TempDirectory( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AbortCopy( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentReadSpeed( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CurrentReadSpeed( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DoNothing( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LeaveSessionOpen( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LeaveSessionOpen( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DriveCount( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DriveName( 
            /* [in] */ long Index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_WriteSpeedCount( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_WriteSpeed( 
            /* [in] */ long Index,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenDevice( 
            /* [in] */ long Index) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LicenseKey( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FadeBetweenTracks( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FadeBetweenTracks( 
            /* [in] */ long newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDiscRecordObjVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDiscRecordObj __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDiscRecordObj __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ListDevices )( 
            IDiscRecordObj __RPC_FAR * This,
            VARIANT_BOOL OnlyWriteable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IDiscRecordObj __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FileSelectDialog )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [in] */ long HwndParent,
            /* [in] */ VARIANT_BOOL IsSaveDialog,
            /* [in] */ BSTR FilterMask,
            /* [in] */ BSTR DefaultExt,
            /* [in] */ long nFilterIndex,
            /* [retval][out] */ BSTR __RPC_FAR *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EjectDevice )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL bEject);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AbortBurn )( 
            IDiscRecordObj __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BurnFromISO )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [in] */ BSTR InputISOPath);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BurnDataCD )( 
            IDiscRecordObj __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ListAvailableWriteSpeeds )( 
            IDiscRecordObj __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryDriveBuffer )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *Used,
            /* [out] */ long __RPC_FAR *Length);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ClearFiles )( 
            IDiscRecordObj __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CopyCDToFixedDrive )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [in] */ long DeviceIndex,
            /* [in] */ BSTR TargetFile);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BurnAudioCD )( 
            IDiscRecordObj __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartDiscErase )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL QuickErase);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryDriveInfo )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *DriveName,
            /* [out] */ BSTR __RPC_FAR *FirmwareVersion,
            /* [out] */ long __RPC_FAR *BufferSize,
            /* [out] */ BSTR __RPC_FAR *Date,
            /* [out] */ BSTR __RPC_FAR *SerialNumber);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ListAvailableReadSpeeds )( 
            IDiscRecordObj __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryFileBuffer )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *Used,
            /* [out] */ long __RPC_FAR *Length);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProgressMax )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProgressCur )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SelectedWriterDeviceIndex )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SelectedWriterDeviceIndex )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CDLabel )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CDLabel )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DiscType )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [retval][out] */ EnumDiscType __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DiscState )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [retval][out] */ EnumDiscState __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DiscCapacityBytes )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentWriteSpeed )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CurrentWriteSpeed )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TestMode )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TestMode )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DiscSize )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EjectWhenDone )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EjectWhenDone )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SelectedWriterDeviceDriveLetter )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DiscCapacitySeconds )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentTrack )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentLBA )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TimeElapsed )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BurnProof )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BurnProof )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProgressMaxSeconds )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PauseBetweenTracks )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PauseBetweenTracks )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CommunicationMethod )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [retval][out] */ EnumCommunication __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CommunicationMethod )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [in] */ EnumCommunication newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PreferredCommunicationMethod )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [retval][out] */ EnumCommunication __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WriteType )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [retval][out] */ EnumWriteType __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WriteType )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [in] */ EnumWriteType newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReadFeatureSupported )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [in] */ EnumFeature FeatureName,
            /* [retval][out] */ EnumFeatureSupport __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WriteFeatureSupported )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [in] */ EnumFeature FeatureName,
            /* [retval][out] */ EnumFeatureSupport __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DataDisc )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [retval][out] */ IFileItem __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AudioDisc )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [retval][out] */ IAudioItem __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProgressCurSeconds )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Erasing )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TempDirectory )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TempDirectory )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AbortCopy )( 
            IDiscRecordObj __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentReadSpeed )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CurrentReadSpeed )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DoNothing )( 
            IDiscRecordObj __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LeaveSessionOpen )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LeaveSessionOpen )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DriveCount )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DriveName )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [in] */ long Index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WriteSpeedCount )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WriteSpeed )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [in] */ long Index,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenDevice )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [in] */ long Index);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LicenseKey )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FadeBetweenTracks )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FadeBetweenTracks )( 
            IDiscRecordObj __RPC_FAR * This,
            /* [in] */ long newVal);
        
        END_INTERFACE
    } IDiscRecordObjVtbl;

    interface IDiscRecordObj
    {
        CONST_VTBL struct IDiscRecordObjVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDiscRecordObj_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDiscRecordObj_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDiscRecordObj_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDiscRecordObj_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDiscRecordObj_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDiscRecordObj_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDiscRecordObj_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDiscRecordObj_ListDevices(This,OnlyWriteable)	\
    (This)->lpVtbl -> ListDevices(This,OnlyWriteable)

#define IDiscRecordObj_Initialize(This)	\
    (This)->lpVtbl -> Initialize(This)

#define IDiscRecordObj_FileSelectDialog(This,HwndParent,IsSaveDialog,FilterMask,DefaultExt,nFilterIndex,pResult)	\
    (This)->lpVtbl -> FileSelectDialog(This,HwndParent,IsSaveDialog,FilterMask,DefaultExt,nFilterIndex,pResult)

#define IDiscRecordObj_EjectDevice(This,bEject)	\
    (This)->lpVtbl -> EjectDevice(This,bEject)

#define IDiscRecordObj_AbortBurn(This)	\
    (This)->lpVtbl -> AbortBurn(This)

#define IDiscRecordObj_BurnFromISO(This,InputISOPath)	\
    (This)->lpVtbl -> BurnFromISO(This,InputISOPath)

#define IDiscRecordObj_BurnDataCD(This)	\
    (This)->lpVtbl -> BurnDataCD(This)

#define IDiscRecordObj_ListAvailableWriteSpeeds(This)	\
    (This)->lpVtbl -> ListAvailableWriteSpeeds(This)

#define IDiscRecordObj_QueryDriveBuffer(This,Used,Length)	\
    (This)->lpVtbl -> QueryDriveBuffer(This,Used,Length)

#define IDiscRecordObj_ClearFiles(This)	\
    (This)->lpVtbl -> ClearFiles(This)

#define IDiscRecordObj_CopyCDToFixedDrive(This,DeviceIndex,TargetFile)	\
    (This)->lpVtbl -> CopyCDToFixedDrive(This,DeviceIndex,TargetFile)

#define IDiscRecordObj_BurnAudioCD(This)	\
    (This)->lpVtbl -> BurnAudioCD(This)

#define IDiscRecordObj_StartDiscErase(This,QuickErase)	\
    (This)->lpVtbl -> StartDiscErase(This,QuickErase)

#define IDiscRecordObj_QueryDriveInfo(This,DriveName,FirmwareVersion,BufferSize,Date,SerialNumber)	\
    (This)->lpVtbl -> QueryDriveInfo(This,DriveName,FirmwareVersion,BufferSize,Date,SerialNumber)

#define IDiscRecordObj_ListAvailableReadSpeeds(This)	\
    (This)->lpVtbl -> ListAvailableReadSpeeds(This)

#define IDiscRecordObj_QueryFileBuffer(This,Used,Length)	\
    (This)->lpVtbl -> QueryFileBuffer(This,Used,Length)

#define IDiscRecordObj_get_ProgressMax(This,pVal)	\
    (This)->lpVtbl -> get_ProgressMax(This,pVal)

#define IDiscRecordObj_get_ProgressCur(This,pVal)	\
    (This)->lpVtbl -> get_ProgressCur(This,pVal)

#define IDiscRecordObj_get_SelectedWriterDeviceIndex(This,pVal)	\
    (This)->lpVtbl -> get_SelectedWriterDeviceIndex(This,pVal)

#define IDiscRecordObj_put_SelectedWriterDeviceIndex(This,newVal)	\
    (This)->lpVtbl -> put_SelectedWriterDeviceIndex(This,newVal)

#define IDiscRecordObj_get_CDLabel(This,pVal)	\
    (This)->lpVtbl -> get_CDLabel(This,pVal)

#define IDiscRecordObj_put_CDLabel(This,newVal)	\
    (This)->lpVtbl -> put_CDLabel(This,newVal)

#define IDiscRecordObj_get_DiscType(This,pVal)	\
    (This)->lpVtbl -> get_DiscType(This,pVal)

#define IDiscRecordObj_get_DiscState(This,pVal)	\
    (This)->lpVtbl -> get_DiscState(This,pVal)

#define IDiscRecordObj_get_DiscCapacityBytes(This,pVal)	\
    (This)->lpVtbl -> get_DiscCapacityBytes(This,pVal)

#define IDiscRecordObj_get_CurrentWriteSpeed(This,pVal)	\
    (This)->lpVtbl -> get_CurrentWriteSpeed(This,pVal)

#define IDiscRecordObj_put_CurrentWriteSpeed(This,newVal)	\
    (This)->lpVtbl -> put_CurrentWriteSpeed(This,newVal)

#define IDiscRecordObj_get_TestMode(This,pVal)	\
    (This)->lpVtbl -> get_TestMode(This,pVal)

#define IDiscRecordObj_put_TestMode(This,newVal)	\
    (This)->lpVtbl -> put_TestMode(This,newVal)

#define IDiscRecordObj_get_DiscSize(This,pVal)	\
    (This)->lpVtbl -> get_DiscSize(This,pVal)

#define IDiscRecordObj_get_EjectWhenDone(This,pVal)	\
    (This)->lpVtbl -> get_EjectWhenDone(This,pVal)

#define IDiscRecordObj_put_EjectWhenDone(This,newVal)	\
    (This)->lpVtbl -> put_EjectWhenDone(This,newVal)

#define IDiscRecordObj_get_SelectedWriterDeviceDriveLetter(This,pVal)	\
    (This)->lpVtbl -> get_SelectedWriterDeviceDriveLetter(This,pVal)

#define IDiscRecordObj_get_DiscCapacitySeconds(This,pVal)	\
    (This)->lpVtbl -> get_DiscCapacitySeconds(This,pVal)

#define IDiscRecordObj_get_CurrentTrack(This,pVal)	\
    (This)->lpVtbl -> get_CurrentTrack(This,pVal)

#define IDiscRecordObj_get_CurrentLBA(This,pVal)	\
    (This)->lpVtbl -> get_CurrentLBA(This,pVal)

#define IDiscRecordObj_get_TimeElapsed(This,pVal)	\
    (This)->lpVtbl -> get_TimeElapsed(This,pVal)

#define IDiscRecordObj_get_BurnProof(This,pVal)	\
    (This)->lpVtbl -> get_BurnProof(This,pVal)

#define IDiscRecordObj_put_BurnProof(This,newVal)	\
    (This)->lpVtbl -> put_BurnProof(This,newVal)

#define IDiscRecordObj_get_ProgressMaxSeconds(This,pVal)	\
    (This)->lpVtbl -> get_ProgressMaxSeconds(This,pVal)

#define IDiscRecordObj_get_PauseBetweenTracks(This,pVal)	\
    (This)->lpVtbl -> get_PauseBetweenTracks(This,pVal)

#define IDiscRecordObj_put_PauseBetweenTracks(This,newVal)	\
    (This)->lpVtbl -> put_PauseBetweenTracks(This,newVal)

#define IDiscRecordObj_get_CommunicationMethod(This,pVal)	\
    (This)->lpVtbl -> get_CommunicationMethod(This,pVal)

#define IDiscRecordObj_put_CommunicationMethod(This,newVal)	\
    (This)->lpVtbl -> put_CommunicationMethod(This,newVal)

#define IDiscRecordObj_get_PreferredCommunicationMethod(This,pVal)	\
    (This)->lpVtbl -> get_PreferredCommunicationMethod(This,pVal)

#define IDiscRecordObj_get_WriteType(This,pVal)	\
    (This)->lpVtbl -> get_WriteType(This,pVal)

#define IDiscRecordObj_put_WriteType(This,newVal)	\
    (This)->lpVtbl -> put_WriteType(This,newVal)

#define IDiscRecordObj_get_ReadFeatureSupported(This,FeatureName,pVal)	\
    (This)->lpVtbl -> get_ReadFeatureSupported(This,FeatureName,pVal)

#define IDiscRecordObj_get_WriteFeatureSupported(This,FeatureName,pVal)	\
    (This)->lpVtbl -> get_WriteFeatureSupported(This,FeatureName,pVal)

#define IDiscRecordObj_get_DataDisc(This,pVal)	\
    (This)->lpVtbl -> get_DataDisc(This,pVal)

#define IDiscRecordObj_get_AudioDisc(This,pVal)	\
    (This)->lpVtbl -> get_AudioDisc(This,pVal)

#define IDiscRecordObj_get_ProgressCurSeconds(This,pVal)	\
    (This)->lpVtbl -> get_ProgressCurSeconds(This,pVal)

#define IDiscRecordObj_get_Erasing(This,pVal)	\
    (This)->lpVtbl -> get_Erasing(This,pVal)

#define IDiscRecordObj_get_TempDirectory(This,pVal)	\
    (This)->lpVtbl -> get_TempDirectory(This,pVal)

#define IDiscRecordObj_put_TempDirectory(This,newVal)	\
    (This)->lpVtbl -> put_TempDirectory(This,newVal)

#define IDiscRecordObj_AbortCopy(This)	\
    (This)->lpVtbl -> AbortCopy(This)

#define IDiscRecordObj_get_CurrentReadSpeed(This,pVal)	\
    (This)->lpVtbl -> get_CurrentReadSpeed(This,pVal)

#define IDiscRecordObj_put_CurrentReadSpeed(This,newVal)	\
    (This)->lpVtbl -> put_CurrentReadSpeed(This,newVal)

#define IDiscRecordObj_DoNothing(This)	\
    (This)->lpVtbl -> DoNothing(This)

#define IDiscRecordObj_get_LeaveSessionOpen(This,pVal)	\
    (This)->lpVtbl -> get_LeaveSessionOpen(This,pVal)

#define IDiscRecordObj_put_LeaveSessionOpen(This,newVal)	\
    (This)->lpVtbl -> put_LeaveSessionOpen(This,newVal)

#define IDiscRecordObj_get_DriveCount(This,pVal)	\
    (This)->lpVtbl -> get_DriveCount(This,pVal)

#define IDiscRecordObj_get_DriveName(This,Index,pVal)	\
    (This)->lpVtbl -> get_DriveName(This,Index,pVal)

#define IDiscRecordObj_get_WriteSpeedCount(This,pVal)	\
    (This)->lpVtbl -> get_WriteSpeedCount(This,pVal)

#define IDiscRecordObj_get_WriteSpeed(This,Index,pVal)	\
    (This)->lpVtbl -> get_WriteSpeed(This,Index,pVal)

#define IDiscRecordObj_OpenDevice(This,Index)	\
    (This)->lpVtbl -> OpenDevice(This,Index)

#define IDiscRecordObj_put_LicenseKey(This,newVal)	\
    (This)->lpVtbl -> put_LicenseKey(This,newVal)

#define IDiscRecordObj_get_FadeBetweenTracks(This,pVal)	\
    (This)->lpVtbl -> get_FadeBetweenTracks(This,pVal)

#define IDiscRecordObj_put_FadeBetweenTracks(This,newVal)	\
    (This)->lpVtbl -> put_FadeBetweenTracks(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_ListDevices_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    VARIANT_BOOL OnlyWriteable);


void __RPC_STUB IDiscRecordObj_ListDevices_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_Initialize_Proxy( 
    IDiscRecordObj __RPC_FAR * This);


void __RPC_STUB IDiscRecordObj_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_FileSelectDialog_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [in] */ long HwndParent,
    /* [in] */ VARIANT_BOOL IsSaveDialog,
    /* [in] */ BSTR FilterMask,
    /* [in] */ BSTR DefaultExt,
    /* [in] */ long nFilterIndex,
    /* [retval][out] */ BSTR __RPC_FAR *pResult);


void __RPC_STUB IDiscRecordObj_FileSelectDialog_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_EjectDevice_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL bEject);


void __RPC_STUB IDiscRecordObj_EjectDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_AbortBurn_Proxy( 
    IDiscRecordObj __RPC_FAR * This);


void __RPC_STUB IDiscRecordObj_AbortBurn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_BurnFromISO_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [in] */ BSTR InputISOPath);


void __RPC_STUB IDiscRecordObj_BurnFromISO_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_BurnDataCD_Proxy( 
    IDiscRecordObj __RPC_FAR * This);


void __RPC_STUB IDiscRecordObj_BurnDataCD_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_ListAvailableWriteSpeeds_Proxy( 
    IDiscRecordObj __RPC_FAR * This);


void __RPC_STUB IDiscRecordObj_ListAvailableWriteSpeeds_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_QueryDriveBuffer_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *Used,
    /* [out] */ long __RPC_FAR *Length);


void __RPC_STUB IDiscRecordObj_QueryDriveBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_ClearFiles_Proxy( 
    IDiscRecordObj __RPC_FAR * This);


void __RPC_STUB IDiscRecordObj_ClearFiles_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_CopyCDToFixedDrive_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [in] */ long DeviceIndex,
    /* [in] */ BSTR TargetFile);


void __RPC_STUB IDiscRecordObj_CopyCDToFixedDrive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_BurnAudioCD_Proxy( 
    IDiscRecordObj __RPC_FAR * This);


void __RPC_STUB IDiscRecordObj_BurnAudioCD_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_StartDiscErase_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL QuickErase);


void __RPC_STUB IDiscRecordObj_StartDiscErase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_QueryDriveInfo_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *DriveName,
    /* [out] */ BSTR __RPC_FAR *FirmwareVersion,
    /* [out] */ long __RPC_FAR *BufferSize,
    /* [out] */ BSTR __RPC_FAR *Date,
    /* [out] */ BSTR __RPC_FAR *SerialNumber);


void __RPC_STUB IDiscRecordObj_QueryDriveInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_ListAvailableReadSpeeds_Proxy( 
    IDiscRecordObj __RPC_FAR * This);


void __RPC_STUB IDiscRecordObj_ListAvailableReadSpeeds_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_QueryFileBuffer_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *Used,
    /* [out] */ long __RPC_FAR *Length);


void __RPC_STUB IDiscRecordObj_QueryFileBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_get_ProgressMax_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IDiscRecordObj_get_ProgressMax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_get_ProgressCur_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IDiscRecordObj_get_ProgressCur_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_get_SelectedWriterDeviceIndex_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IDiscRecordObj_get_SelectedWriterDeviceIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_put_SelectedWriterDeviceIndex_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IDiscRecordObj_put_SelectedWriterDeviceIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_get_CDLabel_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IDiscRecordObj_get_CDLabel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_put_CDLabel_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IDiscRecordObj_put_CDLabel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_get_DiscType_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [retval][out] */ EnumDiscType __RPC_FAR *pVal);


void __RPC_STUB IDiscRecordObj_get_DiscType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_get_DiscState_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [retval][out] */ EnumDiscState __RPC_FAR *pVal);


void __RPC_STUB IDiscRecordObj_get_DiscState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_get_DiscCapacityBytes_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IDiscRecordObj_get_DiscCapacityBytes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_get_CurrentWriteSpeed_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IDiscRecordObj_get_CurrentWriteSpeed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_put_CurrentWriteSpeed_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IDiscRecordObj_put_CurrentWriteSpeed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_get_TestMode_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IDiscRecordObj_get_TestMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_put_TestMode_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IDiscRecordObj_put_TestMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_get_DiscSize_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IDiscRecordObj_get_DiscSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_get_EjectWhenDone_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IDiscRecordObj_get_EjectWhenDone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_put_EjectWhenDone_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IDiscRecordObj_put_EjectWhenDone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_get_SelectedWriterDeviceDriveLetter_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IDiscRecordObj_get_SelectedWriterDeviceDriveLetter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_get_DiscCapacitySeconds_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IDiscRecordObj_get_DiscCapacitySeconds_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_get_CurrentTrack_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IDiscRecordObj_get_CurrentTrack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_get_CurrentLBA_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IDiscRecordObj_get_CurrentLBA_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_get_TimeElapsed_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IDiscRecordObj_get_TimeElapsed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_get_BurnProof_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IDiscRecordObj_get_BurnProof_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_put_BurnProof_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IDiscRecordObj_put_BurnProof_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_get_ProgressMaxSeconds_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IDiscRecordObj_get_ProgressMaxSeconds_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_get_PauseBetweenTracks_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IDiscRecordObj_get_PauseBetweenTracks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_put_PauseBetweenTracks_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IDiscRecordObj_put_PauseBetweenTracks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_get_CommunicationMethod_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [retval][out] */ EnumCommunication __RPC_FAR *pVal);


void __RPC_STUB IDiscRecordObj_get_CommunicationMethod_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_put_CommunicationMethod_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [in] */ EnumCommunication newVal);


void __RPC_STUB IDiscRecordObj_put_CommunicationMethod_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_get_PreferredCommunicationMethod_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [retval][out] */ EnumCommunication __RPC_FAR *pVal);


void __RPC_STUB IDiscRecordObj_get_PreferredCommunicationMethod_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_get_WriteType_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [retval][out] */ EnumWriteType __RPC_FAR *pVal);


void __RPC_STUB IDiscRecordObj_get_WriteType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_put_WriteType_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [in] */ EnumWriteType newVal);


void __RPC_STUB IDiscRecordObj_put_WriteType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_get_ReadFeatureSupported_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [in] */ EnumFeature FeatureName,
    /* [retval][out] */ EnumFeatureSupport __RPC_FAR *pVal);


void __RPC_STUB IDiscRecordObj_get_ReadFeatureSupported_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_get_WriteFeatureSupported_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [in] */ EnumFeature FeatureName,
    /* [retval][out] */ EnumFeatureSupport __RPC_FAR *pVal);


void __RPC_STUB IDiscRecordObj_get_WriteFeatureSupported_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_get_DataDisc_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [retval][out] */ IFileItem __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IDiscRecordObj_get_DataDisc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_get_AudioDisc_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [retval][out] */ IAudioItem __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IDiscRecordObj_get_AudioDisc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_get_ProgressCurSeconds_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IDiscRecordObj_get_ProgressCurSeconds_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_get_Erasing_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IDiscRecordObj_get_Erasing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_get_TempDirectory_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IDiscRecordObj_get_TempDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_put_TempDirectory_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IDiscRecordObj_put_TempDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_AbortCopy_Proxy( 
    IDiscRecordObj __RPC_FAR * This);


void __RPC_STUB IDiscRecordObj_AbortCopy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_get_CurrentReadSpeed_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IDiscRecordObj_get_CurrentReadSpeed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_put_CurrentReadSpeed_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IDiscRecordObj_put_CurrentReadSpeed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_DoNothing_Proxy( 
    IDiscRecordObj __RPC_FAR * This);


void __RPC_STUB IDiscRecordObj_DoNothing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_get_LeaveSessionOpen_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IDiscRecordObj_get_LeaveSessionOpen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_put_LeaveSessionOpen_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IDiscRecordObj_put_LeaveSessionOpen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_get_DriveCount_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IDiscRecordObj_get_DriveCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_get_DriveName_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [in] */ long Index,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IDiscRecordObj_get_DriveName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_get_WriteSpeedCount_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IDiscRecordObj_get_WriteSpeedCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_get_WriteSpeed_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [in] */ long Index,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IDiscRecordObj_get_WriteSpeed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_OpenDevice_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [in] */ long Index);


void __RPC_STUB IDiscRecordObj_OpenDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_put_LicenseKey_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IDiscRecordObj_put_LicenseKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_get_FadeBetweenTracks_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IDiscRecordObj_get_FadeBetweenTracks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDiscRecordObj_put_FadeBetweenTracks_Proxy( 
    IDiscRecordObj __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IDiscRecordObj_put_FadeBetweenTracks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDiscRecordObj_INTERFACE_DEFINED__ */


#ifndef ___IAudioItemEvents_DISPINTERFACE_DEFINED__
#define ___IAudioItemEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IAudioItemEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IAudioItemEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("4EA9C5E0-0B3D-43C6-8D96-6A3A76B8BB28")
    _IAudioItemEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IAudioItemEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IAudioItemEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IAudioItemEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IAudioItemEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IAudioItemEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IAudioItemEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IAudioItemEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IAudioItemEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IAudioItemEventsVtbl;

    interface _IAudioItemEvents
    {
        CONST_VTBL struct _IAudioItemEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IAudioItemEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IAudioItemEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IAudioItemEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IAudioItemEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IAudioItemEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IAudioItemEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IAudioItemEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IAudioItemEvents_DISPINTERFACE_DEFINED__ */


#ifndef ___IDiscRecordObjEvents_DISPINTERFACE_DEFINED__
#define ___IDiscRecordObjEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IDiscRecordObjEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IDiscRecordObjEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("49EEAF1C-1EF4-40FD-9CCA-AF80133B116E")
    _IDiscRecordObjEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IDiscRecordObjEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IDiscRecordObjEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IDiscRecordObjEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IDiscRecordObjEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IDiscRecordObjEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IDiscRecordObjEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IDiscRecordObjEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IDiscRecordObjEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IDiscRecordObjEventsVtbl;

    interface _IDiscRecordObjEvents
    {
        CONST_VTBL struct _IDiscRecordObjEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IDiscRecordObjEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IDiscRecordObjEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IDiscRecordObjEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IDiscRecordObjEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IDiscRecordObjEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IDiscRecordObjEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IDiscRecordObjEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IDiscRecordObjEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_DiscRecord;

#ifdef __cplusplus

class DECLSPEC_UUID("2A708B0E-9289-446B-A892-697C6803AF3A")
DiscRecord;
#endif

EXTERN_C const CLSID CLSID_FileItem;

#ifdef __cplusplus

class DECLSPEC_UUID("B77A6D02-8857-4631-99C6-C2663F676C0C")
FileItem;
#endif

EXTERN_C const CLSID CLSID_AudioItem;

#ifdef __cplusplus

class DECLSPEC_UUID("5FD6E998-04F9-4E9B-AFAF-7E6B16E65773")
AudioItem;
#endif
#endif /* __DISCRECORDLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
