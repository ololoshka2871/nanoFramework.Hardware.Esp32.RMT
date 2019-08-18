//-----------------------------------------------------------------------------
//
//                   ** WARNING! ** 
//    This file was generated automatically by a tool.
//    Re-running the tool will overwrite this file.
//    You should copy this file to a custom location
//    before adding any customization in the copy to
//    prevent loss of your changes when the tool is
//    re-run.
//
//-----------------------------------------------------------------------------
#ifndef _NANOFRAMEWORK_HARDWARE_ESP32_RMT_TX_NANOFRAMEWORK_HARDWARE_ESP32_RMT_TX_TRANSMITTER_H_
#define _NANOFRAMEWORK_HARDWARE_ESP32_RMT_TX_NANOFRAMEWORK_HARDWARE_ESP32_RMT_TX_TRANSMITTER_H_

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
                    struct Transmitter
                    {
                        // Helper Functions to access fields of managed object
                        static bool& Get_mCarierEnabled( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_bool( pMngObj, Library_nanoFramework_Hardware_Esp32_RMT_Tx_nanoFramework_Hardware_Esp32_RMT_Tx_Transmitter::FIELD__mCarierEnabled ); }

                        static unsigned short& Get_mCarierHighLevel( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UINT16( pMngObj, Library_nanoFramework_Hardware_Esp32_RMT_Tx_nanoFramework_Hardware_Esp32_RMT_Tx_Transmitter::FIELD__mCarierHighLevel ); }

                        static bool& Get_mCarierHighLvl( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_bool( pMngObj, Library_nanoFramework_Hardware_Esp32_RMT_Tx_nanoFramework_Hardware_Esp32_RMT_Tx_Transmitter::FIELD__mCarierHighLvl ); }

                        static unsigned short& Get_mCarierLowLevel( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_UINT16( pMngObj, Library_nanoFramework_Hardware_Esp32_RMT_Tx_nanoFramework_Hardware_Esp32_RMT_Tx_Transmitter::FIELD__mCarierLowLevel ); }

                        static signed int& Get_mChannel( CLR_RT_HeapBlock* pMngObj )    { return Interop_Marshal_GetField_INT32( pMngObj, Library_nanoFramework_Hardware_Esp32_RMT_Tx_nanoFramework_Hardware_Esp32_RMT_Tx_Transmitter::FIELD__mChannel ); }

                        // Declaration of stubs. These functions are implemented by Interop code developers
                        static void NativeDispose( signed int param0, HRESULT &hr );
                        static unsigned char NativeGetClockDiv( signed int param0, HRESULT &hr );
                        static bool NativeGetLoopTxMode( signed int param0, HRESULT &hr );
                        static void NativeGetTransmitterIdleLevel( signed int param0, bool * param1, bool * param2, HRESULT &hr );
                        static signed int NativeInit( signed int param0, HRESULT &hr );
                        static bool NativeIsSource80MHz( signed int param0, HRESULT &hr );
                        static void NativeSetClockDiv( signed int param0, unsigned char param1, HRESULT &hr );
                        static void NativeSetLoopTxMode( signed int param0, bool param1, HRESULT &hr );
                        static void NativeSetSource80MHz( signed int param0, bool param1, HRESULT &hr );
                        static void NativeSetTransmitterIdleLevel( signed int param0, bool param1, bool param2, HRESULT &hr );
                        static void NativeSetCarioerMode( signed int param0, bool param1, unsigned short param2, unsigned short param3, bool param4, HRESULT &hr );
                        static void NativeSendData( signed int param0, CLR_RT_TypedArray_UINT8 param1, HRESULT &hr );
                    };
                }
            }
        }
    }
}
#endif  //_NANOFRAMEWORK_HARDWARE_ESP32_RMT_TX_NANOFRAMEWORK_HARDWARE_ESP32_RMT_TX_TRANSMITTER_H_
