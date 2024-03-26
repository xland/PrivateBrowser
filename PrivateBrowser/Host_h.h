

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for Host.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0628 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */


#ifndef __Host_h_h__
#define __Host_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef DECLSPEC_XFGVIRT
#if defined(_CONTROL_FLOW_GUARD_XFG)
#define DECLSPEC_XFGVIRT(base, func) __declspec(xfg_virtual(base, func))
#else
#define DECLSPEC_XFGVIRT(base, func)
#endif
#endif

/* Forward Declarations */ 

#ifndef __IHost_FWD_DEFINED__
#define __IHost_FWD_DEFINED__
typedef interface IHost IHost;

#endif 	/* __IHost_FWD_DEFINED__ */


#ifndef __Host_FWD_DEFINED__
#define __Host_FWD_DEFINED__

#ifdef __cplusplus
typedef class Host Host;
#else
typedef struct Host Host;
#endif /* __cplusplus */

#endif 	/* __Host_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __HostLibrary_LIBRARY_DEFINED__
#define __HostLibrary_LIBRARY_DEFINED__

/* library HostLibrary */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_HostLibrary;

#ifndef __IHost_INTERFACE_DEFINED__
#define __IHost_INTERFACE_DEFINED__

/* interface IHost */
/* [local][object][uuid] */ 


EXTERN_C const IID IID_IHost;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3a14c9c0-bc3e-453f-a314-4ce4a0ec81d8")
    IHost : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE HitTest( 
            int htValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MinimizeWindow( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MaximizeWindow( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CloseWindow( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RestoreWindow( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IHostVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IHost * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IHost * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IHost * This);
        
        DECLSPEC_XFGVIRT(IHost, HitTest)
        HRESULT ( STDMETHODCALLTYPE *HitTest )( 
            IHost * This,
            int htValue);
        
        DECLSPEC_XFGVIRT(IHost, MinimizeWindow)
        HRESULT ( STDMETHODCALLTYPE *MinimizeWindow )( 
            IHost * This);
        
        DECLSPEC_XFGVIRT(IHost, MaximizeWindow)
        HRESULT ( STDMETHODCALLTYPE *MaximizeWindow )( 
            IHost * This);
        
        DECLSPEC_XFGVIRT(IHost, CloseWindow)
        HRESULT ( STDMETHODCALLTYPE *CloseWindow )( 
            IHost * This);
        
        DECLSPEC_XFGVIRT(IHost, RestoreWindow)
        HRESULT ( STDMETHODCALLTYPE *RestoreWindow )( 
            IHost * This);
        
        END_INTERFACE
    } IHostVtbl;

    interface IHost
    {
        CONST_VTBL struct IHostVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHost_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IHost_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IHost_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IHost_HitTest(This,htValue)	\
    ( (This)->lpVtbl -> HitTest(This,htValue) ) 

#define IHost_MinimizeWindow(This)	\
    ( (This)->lpVtbl -> MinimizeWindow(This) ) 

#define IHost_MaximizeWindow(This)	\
    ( (This)->lpVtbl -> MaximizeWindow(This) ) 

#define IHost_CloseWindow(This)	\
    ( (This)->lpVtbl -> CloseWindow(This) ) 

#define IHost_RestoreWindow(This)	\
    ( (This)->lpVtbl -> RestoreWindow(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IHost_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Host;

#ifdef __cplusplus

class DECLSPEC_UUID("637abc45-11f7-4dde-84b4-317d62a638d3")
Host;
#endif
#endif /* __HostLibrary_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


