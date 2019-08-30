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
                        // Helper Functions to access fields of managed object
                        static CLR_RT_HeapBlock_ArrayList* Get_Commands( CLR_RT_HeapBlock* pMngObj )    { 
                            return (CLR_RT_HeapBlock_ArrayList*)pMngObj[ Library_nanoFramework_Hardware_Esp32_RMT_nanoFramework_Hardware_Esp32_RMT_Tx_PulseCommandList::FIELD__Commands ].Dereference(); }

                        // Declaration of stubs. These functions are implemented by Interop code developers
                        static void NativeSerialiseTo( CLR_RT_HeapBlock* pMngObj, CLR_RT_TypedArray_UINT8 dest, HRESULT &hr );
                    };
                }
            }
        }
    }
}
#endif  //_NANOFRAMEWORK_HARDWARE_ESP32_RMT_NANOFRAMEWORK_HARDWARE_ESP32_RMT_TX_PULSECOMMANDLIST_H_
