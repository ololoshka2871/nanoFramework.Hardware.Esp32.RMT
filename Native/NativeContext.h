#ifndef _NANOFRAMEWORK_HARDWARE_ESP32_RMT_TX_NANOFRAMEWORK_HARDWARE_ESP32_RMT_TX_TRANSMITTER_NATIVE_CONTEXT_H_
#define _NANOFRAMEWORK_HARDWARE_ESP32_RMT_TX_NANOFRAMEWORK_HARDWARE_ESP32_RMT_TX_TRANSMITTER_NATIVE_CONTEXT_H_

#define DEFAULT_DEVIDER                         4
#define MAX_PULSES                              32

// see components/soc/esp32/include/soc/rmt_struct.h : RMT.int_st
#define TX_END_MASK_START                       24
#define TX_END_MASK_CH_STEP                     1
#define TX_THR_MASK_START                       0
#define TX_THR_MASK_CH_STEP                     3

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
                          tx_thr_event_mask(1u << (TX_THR_MASK_START + (channel * TX_THR_MASK_CH_STEP))),
                          tx_end_event_mask(1u << (TX_END_MASK_START + (channel * TX_THR_MASK_CH_STEP))),
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

                            ::RMT.tx_lim_ch[channel].limit = MAX_PULSES; // generate interrupt then MAX_PULSES commands processed
                        }

                        ~NativeContext() {
                            vSemaphoreDelete(write_mutex);
                        }

                        void SetClockDiv(uint8_t clockdiv) { ::RMT.conf_ch[channel].conf0.div_cnt = clockdiv; }
                        void SetLoopMode(bool LoopMode) { ::RMT.conf_ch[channel].conf1.tx_conti_mode = LoopMode; }
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
                        bool  GetLoopTxMode() const { return ::RMT.conf_ch[channel].conf1.tx_conti_mode; }
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

                        // isr context
                        void doInterrupt() {
                            portBASE_TYPE taskAwoken = 0;
                            const auto thisISRregSTA = ::RMT.int_st.val;

                            if (thisISRregSTA & tx_thr_event_mask) {
                                fill_half_buffer();
                                ::RMT.int_clr.val = tx_thr_event_mask;
                            }
                            else if (thisISRregSTA & tx_end_event_mask) {
                                xSemaphoreGiveFromISR(write_mutex, &taskAwoken);
                                ::RMT.int_clr.val = tx_end_event_mask;
                            }
                        }

                    private:
                        const rmt_channel_t channel;
                        const uint32_t tx_thr_event_mask;
                        const uint32_t tx_end_event_mask;
                        std::vector<rmt_item32_t> data;
                        xSemaphoreHandle write_mutex;

                        void start_transmission() {
                            ::RMT.conf_ch[channel].conf1.mem_rd_rst = 1;
                            ::RMT.conf_ch[channel].conf1.tx_start = 1;
                        }

                        void reset_transmission() {

                        }

                        void fill_half_buffer() {
                            //
                        }
                    };
                }
            }
        }
    }
}
#endif  //_NANOFRAMEWORK_HARDWARE_ESP32_RMT_TX_NANOFRAMEWORK_HARDWARE_ESP32_RMT_TX_TRANSMITTER_NATIVE_CONTEXT_H_
