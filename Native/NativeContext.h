#ifndef _NANOFRAMEWORK_HARDWARE_ESP32_RMT_TX_NANOFRAMEWORK_HARDWARE_ESP32_RMT_TX_TRANSMITTER_NATIVE_CONTEXT_H_
#define _NANOFRAMEWORK_HARDWARE_ESP32_RMT_TX_NANOFRAMEWORK_HARDWARE_ESP32_RMT_TX_TRANSMITTER_NATIVE_CONTEXT_H_

#include <algorithm>
#include <cstring>

#define DEFAULT_DEVIDER                         4
#define HALF_BUFFER_SIZE                        (sizeof(RMTMEM) / sizeof(rmt_item32_t))

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
                    struct NativeContext
                    {
                        NativeContext(rmt_channel_t channel) 
                        : channel(channel),
                          write_mutex(xSemaphoreCreateBinary()) {
                            // Это по факту регистры
                            auto &ch = ::RMT.conf_ch[channel];
                            ch.conf0.div_cnt = DEFAULT_DEVIDER;
                            ch.conf0.mem_size = 1;        // 1 block (64 commands) of memory for channel
                            ch.conf0.carrier_en = 0;      // no carrier
                            ch.conf0.carrier_out_lv = 1;  // carier at output 1
                            ch.conf0.mem_pd = 0;          // memory active 

                            ch.conf1.rx_en = 0;           // ressiver not enabled
                            ch.conf1.mem_owner = 0;       // transmitter uses the memory block
                            ch.conf1.tx_conti_mode = 0;   // loopback mode disabled
                            ch.conf1.ref_always_on = 1;   // clk source - use apb clock: 80M
                            ch.conf1.idle_out_en = 1;     // idle control Tx enabled
                            ch.conf1.idle_out_lv = 0;     // Idle TX lvl

                            ::RMT.tx_lim_ch[channel].limit = 
                                static_cast<uint8_t>(HALF_BUFFER_SIZE); // generate interrupt then MAX_PULSES commands processed
                        }

                        ~NativeContext() {
                            vSemaphoreDelete(write_mutex);
                        }

                        void SetClockDiv(uint8_t clockdiv) { ::RMT.conf_ch[channel].conf0.div_cnt = clockdiv; }
                        void Set80MhzclkSource(bool is80MhzMode) { ::RMT.conf_ch[channel].conf1.ref_always_on = is80MhzMode;}
                        void SetTransmitIdleEnabled(bool enabled) { ::RMT.conf_ch[channel].conf1.idle_out_en = enabled; }
                        void SetTransmitIdleLevel(bool idle_lvl) { ::RMT.conf_ch[channel].conf1.idle_out_lv = idle_lvl; }
                        void SetCarierMode(bool carier_en, unsigned short high_lvl, unsigned short low_level,
                            bool carier_at_one) { 
                            auto &ch = ::RMT.conf_ch[channel];
                            ch.conf0.carrier_en = carier_en;
                            ch.conf0.carrier_out_lv = carier_at_one;
                            auto &cdc = ::RMT.carrier_duty_ch[channel];
                            cdc.high = high_lvl;
                            cdc.low = low_level;
                        }

                        bool isRef80MHz() const { return ::RMT.conf_ch[channel].conf1.ref_always_on; }
                        uint8_t GetClockDiv() const { return ::RMT.conf_ch[channel].conf0.div_cnt; }
                        bool GetTransmitIdleLevel() const { return ::RMT.conf_ch[channel].conf1.idle_out_lv; }
                        bool IsTransmitIdleEnabled() const { return ::RMT.conf_ch[channel].conf1.idle_out_en; }

                        void SendAsync(std::vector<rmt_item32_t>&& new_data) {
                            xSemaphoreTake(write_mutex, portMAX_DELAY); // release on transmission finished

                            data = std::move(new_data);
                            reset_transmission();
                            fill_half_buffer();
                            fill_half_buffer();
                            start_transmission();
                        }

                        inline void halfTransmitted() {
                            fill_half_buffer();
                        }

                        inline void TransmissionFinished() {
                             portBASE_TYPE taskAwoken = 0;
                             xSemaphoreGiveFromISR(write_mutex, &taskAwoken);
                        }

                    private:
                        const rmt_channel_t channel;
                        std::vector<rmt_item32_t> data;
                        rmt_item32_t* tr_it;
                        xSemaphoreHandle write_mutex;
                        bool next_fill_high;

                        void start_transmission() {
                            ::RMT.conf_ch[channel].conf1.mem_rd_rst = 1;
                            ::RMT.conf_ch[channel].conf1.tx_start = 1;
                        }

                        void reset_transmission() {
                            tr_it = data.data();
                            next_fill_high = false;
                        }

                        void fill_half_buffer() {
                            const auto end = data.data() + data.size();
                            if (tr_it == end)
                                return;

                            auto dest = tr_it;
                            size_t this_iteration_copy = std::min(
                                static_cast<size_t>(end - dest - 1), 
                                static_cast<size_t>(HALF_BUFFER_SIZE));

                            std::memcpy(const_cast<rmt_item32_t*>(
                                    &RMTMEM.chan[channel].data32[next_fill_high ? HALF_BUFFER_SIZE : 0]), 
                                tr_it, this_iteration_copy);

                            next_fill_high = !next_fill_high;
                            tr_it += this_iteration_copy;
                        }
                    };
                }
            }
        }
    }
}
#endif  //_NANOFRAMEWORK_HARDWARE_ESP32_RMT_TX_NANOFRAMEWORK_HARDWARE_ESP32_RMT_TX_TRANSMITTER_NATIVE_CONTEXT_H_
