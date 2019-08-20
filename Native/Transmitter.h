#ifndef _NANOFRAMEWORK_HARDWARE_ESP32_RMT_NANOFRAMEWORK_HARDWARE_ESP32_RMT_TX_TRANSMITTER_H_
#define _NANOFRAMEWORK_HARDWARE_ESP32_RMT_NANOFRAMEWORK_HARDWARE_ESP32_RMT_TX_TRANSMITTER_H_

#include <map>

#include "rmt.h"

#include "NativeContext.h"

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
                        static std::map<rmt_channel_t, NativeContext> nativechannels;

                        // Declaration of stubs. These functions are implemented by Interop code developers
                        static void NativeDispose( signed int channel, HRESULT &hr );
                        static unsigned char NativeGetClockDiv(signed int channel, HRESULT &hr);
                        static bool NativeGetTransmitIdleLevel(signed int channel, HRESULT &hr);
                        static signed int NativeInit( signed int gpio_number, HRESULT &hr );
                        static bool NativeIsSource80MHz( signed int channel, HRESULT &hr );
                        static void NativeSetClockDiv(signed int channel, unsigned char clockdiv, HRESULT &hr);
                        static void NativeSetSource80MHz(signed int channel, bool is80MhzMode, HRESULT &hr);
                        static bool NativeIsTransmitIdleEnabled(signed int channel, HRESULT &hr);
                        static void NativeSendData(signed int channel, CLR_RT_TypedArray_UINT8 data, HRESULT &hr);
                        static void NativeSetCarierMode(signed int channel, bool carier_en,
                                unsigned short high_lvl, unsigned short low_level, bool carier_at_one, HRESULT &hr);
                        static void NativeSetTransmitIdleEnabled(signed int channel, bool enabled, HRESULT &hr);
                        static void NativeSetTransmitIdleLevel(signed int channel, bool idle_lvl, HRESULT &hr);

                    private:
                        static intr_handle_t isr_info;

                        static signed int find_next_channel();

                        static void RMT_ISR(void *arg); 
                        static void init_RMT();
                        static void deinit_RMT();
                    };
                }
            }
        }
    }
}
#endif  //_NANOFRAMEWORK_HARDWARE_ESP32_RMT_NANOFRAMEWORK_HARDWARE_ESP32_RMT_TX_TRANSMITTER_H_
