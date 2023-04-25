#pragma once

namespace alba {

using u32 = unsigned int;
using u16 = unsigned short int;

struct MccMncPair {
    u16 mcc;
    u16 mnc;
};

MccMncPair convertPlmnIdToMccMnc(u32 const plmnId);

}  // namespace alba
