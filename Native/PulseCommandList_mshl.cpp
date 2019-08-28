#include "nanoFramework_Hardware_Esp32_RMT.h"
#include "PulseCommandList.h"

using namespace nanoFramework::Hardware::Esp32::RMT::Tx;


HRESULT Library_nanoFramework_Hardware_Esp32_RMT_nanoFramework_Hardware_Esp32_RMT_Tx_PulseCommandList::NativeCommandAdd___VOID__OBJECT( CLR_RT_StackFrame& stack )
{
    NANOCLR_HEADER(); hr = S_OK;
    {
        CLR_RT_HeapBlock* pMngObj = Interop_Marshal_RetrieveManagedObject( stack );

        FAULT_ON_NULL(pMngObj);

        CLR_RT_HeapBlock* param0 = stack.Arg1().Dereference();
        NANOCLR_CHECK_HRESULT( param0 != nullptr ? S_OK : S_FALSE );

        PulseCommandList::NativeCommandAdd( pMngObj,  param0, hr );
        NANOCLR_CHECK_HRESULT( hr );
    }
    NANOCLR_NOCLEANUP();
}

HRESULT Library_nanoFramework_Hardware_Esp32_RMT_nanoFramework_Hardware_Esp32_RMT_Tx_PulseCommandList::NativeFree___VOID( CLR_RT_StackFrame& stack )
{
    NANOCLR_HEADER(); hr = S_OK;
    {
        CLR_RT_HeapBlock* pMngObj = Interop_Marshal_RetrieveManagedObject( stack );

        FAULT_ON_NULL(pMngObj);

        PulseCommandList::NativeFree( pMngObj,  hr );
        NANOCLR_CHECK_HRESULT( hr );
    }
    NANOCLR_NOCLEANUP();
}

HRESULT Library_nanoFramework_Hardware_Esp32_RMT_nanoFramework_Hardware_Esp32_RMT_Tx_PulseCommandList::NativeGetCommandCount___I4( CLR_RT_StackFrame& stack )
{
    NANOCLR_HEADER(); hr = S_OK;
    {
        CLR_RT_HeapBlock* pMngObj = Interop_Marshal_RetrieveManagedObject( stack );

        FAULT_ON_NULL(pMngObj);

        signed int retVal = PulseCommandList::NativeGetCommandCount( pMngObj,  hr );
        NANOCLR_CHECK_HRESULT( hr );
        SetResult_INT32( stack, retVal );

    }
    NANOCLR_NOCLEANUP();
}

HRESULT Library_nanoFramework_Hardware_Esp32_RMT_nanoFramework_Hardware_Esp32_RMT_Tx_PulseCommandList::NativeInit___VOID( CLR_RT_StackFrame& stack )
{
    NANOCLR_HEADER(); hr = S_OK;
    {
        CLR_RT_HeapBlock* pMngObj = Interop_Marshal_RetrieveManagedObject( stack );

        FAULT_ON_NULL(pMngObj);

        PulseCommandList::NativeInit( pMngObj,  hr );
        NANOCLR_CHECK_HRESULT( hr );
    }
    NANOCLR_NOCLEANUP();
}

HRESULT Library_nanoFramework_Hardware_Esp32_RMT_nanoFramework_Hardware_Esp32_RMT_Tx_PulseCommandList::NativeLastCommand___OBJECT( CLR_RT_StackFrame& stack )
{
    NANOCLR_HEADER(); hr = S_OK;
    {
        CLR_RT_HeapBlock* pMngObj = Interop_Marshal_RetrieveManagedObject( stack );

        FAULT_ON_NULL(pMngObj);

        CLR_RT_HeapBlock* retVal = PulseCommandList::NativeLastCommand( pMngObj,  hr );
        NANOCLR_CHECK_HRESULT( hr );
        
        stack.SetResult_Object( retVal ); 
    }
    NANOCLR_NOCLEANUP();
}

HRESULT Library_nanoFramework_Hardware_Esp32_RMT_nanoFramework_Hardware_Esp32_RMT_Tx_PulseCommandList::NativeSerialiseTo___VOID__SZARRAY_U1( CLR_RT_StackFrame& stack )
{
    NANOCLR_HEADER(); hr = S_OK;
    {
        CLR_RT_HeapBlock* pMngObj = Interop_Marshal_RetrieveManagedObject( stack );

        FAULT_ON_NULL(pMngObj);

        CLR_RT_TypedArray_UINT8 param0;
        NANOCLR_CHECK_HRESULT( Interop_Marshal_UINT8_ARRAY( stack, 1, param0 ) );

        PulseCommandList::NativeSerialiseTo( pMngObj,  param0, hr );
        NANOCLR_CHECK_HRESULT( hr );
    }
    NANOCLR_NOCLEANUP();
}

HRESULT Library_nanoFramework_Hardware_Esp32_RMT_nanoFramework_Hardware_Esp32_RMT_Tx_PulseCommandList::NativeGetElement___OBJECT__I4( CLR_RT_StackFrame& stack )
{
    NANOCLR_HEADER(); hr = S_OK;
    {
        CLR_RT_HeapBlock* pMngObj = Interop_Marshal_RetrieveManagedObject( stack );

        FAULT_ON_NULL(pMngObj);

        signed int param0;
        NANOCLR_CHECK_HRESULT( Interop_Marshal_INT32( stack, 1, param0 ) );

        CLR_RT_HeapBlock* retVal = PulseCommandList::NativeGetElement( pMngObj,  param0, hr );
        NANOCLR_CHECK_HRESULT( hr );
        stack.SetResult_Object( retVal ); 
    }
    NANOCLR_NOCLEANUP();
}

HRESULT Library_nanoFramework_Hardware_Esp32_RMT_nanoFramework_Hardware_Esp32_RMT_Tx_PulseCommandList::NativeSetCommand___VOID__I4__OBJECT( CLR_RT_StackFrame& stack )
{
    NANOCLR_HEADER(); hr = S_OK;
    {
        CLR_RT_HeapBlock* pMngObj = Interop_Marshal_RetrieveManagedObject( stack );

        FAULT_ON_NULL(pMngObj);

        signed int param0;
        NANOCLR_CHECK_HRESULT( Interop_Marshal_INT32( stack, 1, param0 ) );

        UNSUPPORTED_TYPE param1;
        NANOCLR_CHECK_HRESULT( Interop_Marshal_UNSUPPORTED_TYPE( stack, 2, param1 ) );

        PulseCommandList::NativeSetCommand( pMngObj,  param0, param1, hr );
        NANOCLR_CHECK_HRESULT( hr );
    }
    NANOCLR_NOCLEANUP();
}