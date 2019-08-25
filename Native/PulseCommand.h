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
                        // Declaration of stubs. These functions are implemented by Interop code developers
                        static void SerialiseTo( CLR_RT_TypedArray_UINT8 buf, signed int offset, unsigned short duration1, unsigned short duration2, bool level1, bool level2, HRESULT &hr );
                    };
                }
            }
        }
    }
}
#endif  //_NANOFRAMEWORK_HARDWARE_ESP32_RMT_NANOFRAMEWORK_HARDWARE_ESP32_RMT_TX_PULSECOMMAND_H_
