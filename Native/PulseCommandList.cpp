#include "nanoFramework_Hardware_Esp32_RMT.h"
#include "PulseCommandList.h"

#include "PulseCommand.h"

#include <algorithm>
#include <cstring>

#include "soc/rmt_struct.h"

using namespace nanoFramework::Hardware::Esp32::RMT::Tx;

void PulseCommandList::NativeSerialiseTo( CLR_RT_HeapBlock* pMngObj, CLR_RT_TypedArray_UINT8 dest, HRESULT &hr )
{
    auto commands = Get_Commands(pMngObj);
    uint32_t size = commands->GetSize();
    if (dest.GetSize() < size * sizeof(rmt_item32_t)) {
        hr = CLR_E_BUFFER_TOO_SMALL;
        return;
    }

    for (uint32_t i = 0; i < size ; ++i) {
        CLR_RT_HeapBlock *cmd;
        commands->GetItem(i, cmd);
        PulseCommand::SerialiseTo(dest, i * sizeof(rmt_item32_t),
            PulseCommand::Get_mDuration1(cmd),
            PulseCommand::Get_mDuration2(cmd),
            PulseCommand::Get_level1(cmd),
            PulseCommand::Get_level2(cmd),
            hr
        );
    }
}
