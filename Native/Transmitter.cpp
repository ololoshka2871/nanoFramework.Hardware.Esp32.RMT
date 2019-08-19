#include "nanoFramework_Hardware_Esp32_RMT_Tx.h"
#include "Transmitter.h"

#include <vector>
#include <cstring>

// based on https://github.com/FozzTexx/ws2812-demo
#define MY_CLEANUP()							hr = S_OK; nanoCLR_Cleanup: return
#define MY_CLEANUP_D(r)							hr = S_OK; nanoCLR_Cleanup: return r
#define CHANNEL(ch)                             static_cast<rmt_channel_t>(ch)

// see components/soc/esp32/include/soc/rmt_struct.h : RMT.int_st
#define TX_END_MASK_START                       24
#define TX_END_MASK_CH_STEP                     1
#define TX_THR_MASK_START                       0
#define TX_THR_MASK_CH_STEP                     3

#define TX_THR_FLAG(ch)                         (1u << (TX_THR_MASK_START + (channel * TX_THR_MASK_CH_STEP)))
#define TX_END_FLAG(ch)                         (1u << (TX_END_MASK_START + (channel * TX_THR_MASK_CH_STEP)))

using namespace nanoFramework::Hardware::Esp32::RMT::Tx;

std::map<rmt_channel_t, NativeContext> Transmitter::nativechannels;
intr_handle_t Transmitter::isr_info;

static bool isChannelHalfTransmitted(rmt_channel_t channel) {
    return (::RMT.int_st.val & TX_THR_FLAG(channel)) != 0;
}

static bool isChannelFinishedTransmission(rmt_channel_t channel) {
    return (::RMT.int_st.val & TX_END_FLAG(channel)) != 0;
}

static void resetHalfTransmittedChannel(rmt_channel_t channel) {
    ::RMT.int_clr.val = TX_THR_FLAG(channel);
}

static void resetFinishedTransmissionChannel(rmt_channel_t channel) {
    ::RMT.int_clr.val = TX_END_FLAG(channel);
}

void Transmitter::init_RMT() {
    if (nativechannels.size() > 0) return;

    DPORT_SET_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_RMT_CLK_EN);
    DPORT_CLEAR_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_RMT_RST);

    ::RMT.apb_conf.fifo_mask = 1;         // use memory access, instead of FIFO mode.
    ::RMT.apb_conf.mem_tx_wrap_en = 1;    // wrap around when hitting end of buffer

    esp_intr_alloc(ETS_RMT_INTR_SOURCE, 0, RMT_ISR, nullptr, &isr_info);
}

void Transmitter::deinit_RMT() {
    if (nativechannels.size() > 0) return; 

    esp_intr_free(isr_info);

    DPORT_SET_PERI_REG_MASK(DPORT_PERIP_RST_EN_REG, DPORT_RMT_RST);
    DPORT_CLEAR_PERI_REG_MASK(DPORT_PERIP_CLK_EN_REG, DPORT_RMT_CLK_EN);
}

void Transmitter::NativeDispose(signed int channel, HRESULT &hr) {
    if (channel < 0) {
        hr = CLR_E_INDEX_OUT_OF_RANGE;
        NANOCLR_LEAVE();
    }
    if (nativechannels.find(CHANNEL(channel)) == nativechannels.end()) {
        hr = CLR_E_OBJECT_DISPOSED;
        NANOCLR_LEAVE();
    }

    if (rmt_driver_uninstall(CHANNEL(channel)) != ESP_OK)
        hr = CLR_E_PROCESS_EXCEPTION;
    
    nativechannels.erase(CHANNEL(channel));
    deinit_RMT();

    MY_CLEANUP();
}

unsigned char Transmitter::NativeGetClockDiv(signed int channel, HRESULT &hr)
{
    unsigned char retVal = 0; 
    if (channel < 0) {
        hr = CLR_E_INDEX_OUT_OF_RANGE;
        NANOCLR_LEAVE();
    }
    {
        auto nc = nativechannels.find(CHANNEL(channel));
        if (nc == nativechannels.end()) {
            hr = CLR_E_OBJECT_DISPOSED;
            NANOCLR_LEAVE();
        }

        retVal = nc->second.GetClockDiv(); 
    }
    MY_CLEANUP_D(retVal);
}

signed int Transmitter::NativeInit(signed int gpio_number, HRESULT &hr) {
    auto ch = find_next_channel();
    if (ch < 0) {
        hr = CLR_E_DRIVER_NOT_REGISTERED;
        NANOCLR_LEAVE();
    }

    if (rmt_set_pin(CHANNEL(ch), RMT_MODE_TX, (gpio_num_t)gpio_number) != ESP_OK) {
        ch = 1;
        hr = CLR_E_DRIVER_NOT_REGISTERED;
        NANOCLR_LEAVE();
    }

    init_RMT();

    {
        auto emplaced = nativechannels.emplace(std::piecewise_construct,
                         std::forward_as_tuple(CHANNEL(ch)),
                         std::forward_as_tuple(CHANNEL(ch)));
        if(!emplaced.second) {
            hr = CLR_E_OUT_OF_MEMORY;
            NANOCLR_LEAVE();
        }
    }
    
    MY_CLEANUP_D(ch);
}

bool Transmitter::NativeIsSource80MHz(signed int channel, HRESULT &hr) {
    bool retVal = false;
    if (channel < 0) {
        hr = CLR_E_INDEX_OUT_OF_RANGE;
        NANOCLR_LEAVE();
    }
    {
        auto nc = nativechannels.find(CHANNEL(channel));
        if (nc == nativechannels.end()) {
            hr = CLR_E_OBJECT_DISPOSED;
            NANOCLR_LEAVE();
        }

        retVal = nc->second.isRef80MHz(); 
    }
    MY_CLEANUP_D(retVal);
}

void Transmitter::NativeSetClockDiv(signed int channel, unsigned char clockdiv, HRESULT &hr) {
    if (channel < 0) {
        hr = CLR_E_INDEX_OUT_OF_RANGE;
        NANOCLR_LEAVE();
    }
    {
        auto nc = nativechannels.find(CHANNEL(channel));
        if (nc == nativechannels.end()) {
            hr = CLR_E_OBJECT_DISPOSED;
            NANOCLR_LEAVE();
        }
        nc->second.SetClockDiv(clockdiv);
    }
    MY_CLEANUP();
}

void Transmitter::NativeSetSource80MHz(signed int channel, bool is80MhzMode, HRESULT &hr) {
    if (channel < 0) {
        hr = CLR_E_INDEX_OUT_OF_RANGE;
        NANOCLR_LEAVE();
    }
    {
        auto nc = nativechannels.find(CHANNEL(channel));
        if (nc == nativechannels.end()) {
            hr = CLR_E_OBJECT_DISPOSED;
            NANOCLR_LEAVE();
        }
        nc->second.Set80MhzclkSource(is80MhzMode);
    }
    MY_CLEANUP();
}

void Transmitter::NativeSendData(signed int channel, CLR_RT_TypedArray_UINT8 data, HRESULT &hr) {
    if (channel < 0) {
        hr = CLR_E_INDEX_OUT_OF_RANGE;
        NANOCLR_LEAVE();
    }
    {
        auto nc = nativechannels.find(CHANNEL(channel));
        if (nc == nativechannels.end()) {
            hr = CLR_E_OBJECT_DISPOSED;
            NANOCLR_LEAVE();
        }
        
        const auto element_size = sizeof(rmt_item32_t);
        if (data.GetSize() % element_size != 0) {
            hr = CLR_E_SERIALIZATION_VIOLATION;
            NANOCLR_LEAVE();
        }

        std::vector<rmt_item32_t> d(data.GetSize() / element_size);
        std::memcpy(d.data(), data.GetBuffer(), data.GetSize());

        nc->second.SendAsync(std::move(d));
    }
    MY_CLEANUP();
}

bool Transmitter::NativeGetTransmitIdleLevel(signed int channel, HRESULT &hr) {
    bool retVal = 0; 
    if (channel < 0) {
        hr = CLR_E_INDEX_OUT_OF_RANGE;
        NANOCLR_LEAVE();
    }
    {
        auto nc = nativechannels.find(CHANNEL(channel));
        if (nc == nativechannels.end()) {
            hr = CLR_E_OBJECT_DISPOSED;
            NANOCLR_LEAVE();
        }

        retVal = nc->second.GetTransmitIdleLevel();
    }
    MY_CLEANUP_D(retVal);
}

bool Transmitter::NativeIsTransmitIdleEnabled(signed int channel, HRESULT &hr) {
    bool retVal = 0; 
    if (channel < 0) {
        hr = CLR_E_INDEX_OUT_OF_RANGE;
        NANOCLR_LEAVE();
    }
    {
        auto nc = nativechannels.find(CHANNEL(channel));
        if (nc == nativechannels.end()) {
            hr = CLR_E_OBJECT_DISPOSED;
            NANOCLR_LEAVE();
        }

        retVal = nc->second.IsTransmitIdleEnabled();
    }
    MY_CLEANUP_D(retVal);
}

void Transmitter::NativeSetCarierMode(signed int channel, bool carier_en,
    unsigned short high_lvl, unsigned short low_level, bool carier_at_one, HRESULT &hr) {
    if (channel < 0) {
        hr = CLR_E_INDEX_OUT_OF_RANGE;
        NANOCLR_LEAVE();
    }
    {
        auto nc = nativechannels.find(CHANNEL(channel));
        if (nc == nativechannels.end()) {
            hr = CLR_E_OBJECT_DISPOSED;
            NANOCLR_LEAVE();
        }
        nc->second.SetCarierMode(carier_en, high_lvl, low_level, carier_at_one);
    }
    MY_CLEANUP();
}

void Transmitter::NativeSetTransmitIdleEnabled(signed int channel, bool enabled, HRESULT &hr) {
    if (channel < 0) {
        hr = CLR_E_INDEX_OUT_OF_RANGE;
        NANOCLR_LEAVE();
    }
    {
        auto nc = nativechannels.find(CHANNEL(channel));
        if (nc == nativechannels.end()) {
            hr = CLR_E_OBJECT_DISPOSED;
            NANOCLR_LEAVE();
        }
        nc->second.SetTransmitIdleEnabled(enabled);
    }
    MY_CLEANUP();
}

void Transmitter::NativeSetTransmitIdleLevel(signed int channel, bool idle_lvl, HRESULT &hr) {
    if (channel < 0) {
        hr = CLR_E_INDEX_OUT_OF_RANGE;
        NANOCLR_LEAVE();
    }
    {
        auto nc = nativechannels.find(CHANNEL(channel));
        if (nc == nativechannels.end()) {
            hr = CLR_E_OBJECT_DISPOSED;
            NANOCLR_LEAVE();
        }
        nc->second.SetTransmitIdleLevel(idle_lvl);
    }
    MY_CLEANUP();
}

signed int Transmitter::find_next_channel() {
    for (signed int ch = RMT_CHANNEL_0; ch < RMT_CHANNEL_MAX ; ++ch) {
        if (nativechannels.find(CHANNEL(ch)) == nativechannels.end()) {
            return ch;
        }
    }
    return -1;
}

void Transmitter::RMT_ISR(void *arg) {
    (void)arg;

    std::for_each(nativechannels.begin(), nativechannels.end(), 
        [](decltype(nativechannels)::iterator::value_type &pair) {
            auto channel = pair.first;
            auto &ctx = pair.second;
            if (isChannelHalfTransmitted(channel)) {
                ctx.halfTransmitted();
                resetHalfTransmittedChannel(channel);
            } else if (isChannelFinishedTransmission(channel)) {
                ctx.TransmissionFinished();
                resetFinishedTransmissionChannel(channel);
            }
    });
}

