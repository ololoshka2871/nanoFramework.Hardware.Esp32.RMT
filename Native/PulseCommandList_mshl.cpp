#include "nanoFramework_Hardware_Esp32_RMT.h"
#include "PulseCommandList.h"

using namespace nanoFramework::Hardware::Esp32::RMT::Tx;

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
