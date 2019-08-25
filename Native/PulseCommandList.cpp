#include "nanoFramework_Hardware_Esp32_RMT.h"
#include "PulseCommandList.h"

#include "PulseCommand.h"

#include <algorithm>

#include "soc/rmt_struct.h"

using namespace nanoFramework::Hardware::Esp32::RMT::Tx;

std::map<CLR_RT_HeapBlock*, std::list<CLR_RT_HeapBlock*>> PulseCommandList::commandListsByMngObj;

static void block_gc(CLR_RT_HeapBlock* element) {
    element->MarkForcedAlive();
}

static void release_gc(std::list<CLR_RT_HeapBlock*>& elements) {
    std::for_each(elements.begin(), elements.end(), [](CLR_RT_HeapBlock* element) {
        element->UnmarkForcedAlive();
    });
}

void PulseCommandList::NativeCommandAdd( CLR_RT_HeapBlock* pMngObj, CLR_RT_HeapBlock* command, HRESULT &hr )
{
    auto it = commandListsByMngObj.find(pMngObj);
    if (it == commandListsByMngObj.end()) {
        hr = CLR_E_OBJECT_DISPOSED;
        return;
    }

    block_gc(command);
    it->second.emplace_back(command);
}

void PulseCommandList::NativeFree( CLR_RT_HeapBlock* pMngObj, HRESULT &hr )
{
    auto it = commandListsByMngObj.find(pMngObj);
    if (it == commandListsByMngObj.end()) {
        hr = CLR_E_OBJECT_DISPOSED;
        return;
    }

    release_gc(it->second);
    commandListsByMngObj.erase(it);
    /*
    {
        char buf[128];
        sprintf(buf, "Free(0x%X)\n", (uint)pMngObj);
        CLR_Debug::Emit( buf, -1 );
    }
    */
}

signed int PulseCommandList::NativeGetCommandCount( CLR_RT_HeapBlock* pMngObj, HRESULT &hr )
{
    auto it = commandListsByMngObj.find(pMngObj);
    if (it == commandListsByMngObj.end()) {
        hr = CLR_E_OBJECT_DISPOSED;
        return 0;
    } 
    return it->second.size();
}

void PulseCommandList::NativeInit( CLR_RT_HeapBlock* pMngObj, HRESULT &hr )
{
    auto res = commandListsByMngObj.emplace(std::piecewise_construct,
                         std::forward_as_tuple(pMngObj),
                         std::forward_as_tuple());
    hr = res.second ? S_OK : CLR_E_BUSY;
    /*
    {
        char buf[128];
        sprintf(buf, "new(0x%X)\n", (uint)pMngObj);
        CLR_Debug::Emit( buf, -1 );
    }
    */
}

CLR_RT_HeapBlock* PulseCommandList::NativeLastCommand( CLR_RT_HeapBlock* pMngObj, HRESULT &hr )
{
    auto it = commandListsByMngObj.find(pMngObj);
    if (it == commandListsByMngObj.end()) {
        hr = CLR_E_OBJECT_DISPOSED;
        return 0;
    } 
    if (it->second.empty()) {
        return nullptr;
    } 

    return it->second.back();
}

void PulseCommandList::NativeSerialiseTo( CLR_RT_HeapBlock* pMngObj, CLR_RT_TypedArray_UINT8 dest, HRESULT &hr )
{
    auto it = commandListsByMngObj.find(pMngObj);
    if (it == commandListsByMngObj.end()) {
        hr = CLR_E_OBJECT_DISPOSED;
        return;
    }
    auto lst = it->second;

    if (dest.GetSize() < lst.size() * sizeof(rmt_item32_t)) {
        hr = CLR_E_BUFFER_TOO_SMALL;
        return;
    }

    auto cit = lst.cbegin();
    auto cite = lst.cend();
    for (int i = 0; cit != cite; ++cit, i += sizeof(rmt_item32_t)) {
        auto &cmd = *cit;
        PulseCommand::SerialiseTo(dest, i,
            PulseCommand::Get_mDuration1(cmd),
            PulseCommand::Get_mDuration2(cmd),
            PulseCommand::Get_level1(cmd),
            PulseCommand::Get_level2(cmd),
            hr
        );
    }
}

