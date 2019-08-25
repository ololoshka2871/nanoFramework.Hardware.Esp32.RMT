#include "nanoFramework_Hardware_Esp32_RMT.h"
#include "PulseCommand.h"

#include "soc/rmt_struct.h"

#include <cstring>

using namespace nanoFramework::Hardware::Esp32::RMT::Tx;

void PulseCommand::SerialiseTo( CLR_RT_TypedArray_UINT8 buf, signed int offset, unsigned short duration1, unsigned short duration2, bool level1, bool level2, HRESULT &hr )
{
    (void)hr;
    auto dest = &(buf.GetBuffer()[offset]);
    rmt_item32_t item{duration1, level1, duration2, level2};
    std::memcpy(dest, &item, sizeof(rmt_item32_t));
}

