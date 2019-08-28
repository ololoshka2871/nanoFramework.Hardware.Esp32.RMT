#ifndef _NANOFRAMEWORK_HARDWARE_ESP32_RMT_NANOFRAMEWORK_HARDWARE_ESP32_RMT_TX_PULSECOMMANDLIST_H_
#define _NANOFRAMEWORK_HARDWARE_ESP32_RMT_NANOFRAMEWORK_HARDWARE_ESP32_RMT_TX_PULSECOMMANDLIST_H_

#include <map>
#include <list>

namespace nanoFramework
{
    namespace Hardware
    {
        namespace Esp32
        {
            namespace RMT
            {
                namespace Tx
                {
                    struct PulseCommandList
                    {
                        static std::map<CLR_RT_HeapBlock*, std::list<CLR_RT_HeapBlock*>> commandListsByMngObj;

                        // Declaration of stubs. These functions are implemented by Interop code developers
                        static void NativeCommandAdd( CLR_RT_HeapBlock* pMngObj, CLR_RT_HeapBlock* command, HRESULT &hr );
                        static void NativeFree( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
                        static signed int NativeGetCommandCount( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
                        static void NativeInit( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
                        static CLR_RT_HeapBlock* NativeLastCommand( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
                        static void NativeSerialiseTo( CLR_RT_HeapBlock* pMngObj, CLR_RT_TypedArray_UINT8 dest, HRESULT &hr );
                        static CLR_RT_HeapBlock* NativeGetElement( CLR_RT_HeapBlock* pMngObj, signed int index, HRESULT &hr );
                        static void NativeSetCommand( CLR_RT_HeapBlock* pMngObj, signed int index, CLR_RT_HeapBlock* value, HRESULT &hr );
                    };
                }
            }
        }
    }
}
#endif  //_NANOFRAMEWORK_HARDWARE_ESP32_RMT_NANOFRAMEWORK_HARDWARE_ESP32_RMT_TX_PULSECOMMANDLIST_H_
