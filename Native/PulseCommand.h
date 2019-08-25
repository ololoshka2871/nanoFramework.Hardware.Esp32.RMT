#ifndef _NANOFRAMEWORK_HARDWARE_ESP32_RMT_NANOFRAMEWORK_HARDWARE_ESP32_RMT_TX_PULSECOMMAND_H_
#define _NANOFRAMEWORK_HARDWARE_ESP32_RMT_NANOFRAMEWORK_HARDWARE_ESP32_RMT_TX_PULSECOMMAND_H_

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
                    struct PulseCommand
                    {
                        // Helper Functions to access fields of managed object
                        static bool& Get_level1( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_bool( pMngObj, Library_nanoFramework_Hardware_Esp32_RMT_nanoFramework_Hardware_Esp32_RMT_Tx_PulseCommand::FIELD__level1 ); }

                        static bool& Get_level2( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_bool( pMngObj, Library_nanoFramework_Hardware_Esp32_RMT_nanoFramework_Hardware_Esp32_RMT_Tx_PulseCommand::FIELD__level2 ); }

                        static unsigned short& Get_mDuration1( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UINT16( pMngObj, Library_nanoFramework_Hardware_Esp32_RMT_nanoFramework_Hardware_Esp32_RMT_Tx_PulseCommand::FIELD__mDuration1 ); }

                        static unsigned short& Get_mDuration2( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UINT16( pMngObj, Library_nanoFramework_Hardware_Esp32_RMT_nanoFramework_Hardware_Esp32_RMT_Tx_PulseCommand::FIELD__mDuration2 ); }


                        // Declaration of stubs. These functions are implemented by Interop code developers
                        static void SerialiseTo( CLR_RT_TypedArray_UINT8 buf, signed int offset, unsigned short duration1, unsigned short duration2, bool level1, bool level2, HRESULT &hr );
                    };
                }
            }
        }
    }
}
#endif  //_NANOFRAMEWORK_HARDWARE_ESP32_RMT_NANOFRAMEWORK_HARDWARE_ESP32_RMT_TX_PULSECOMMAND_H_
