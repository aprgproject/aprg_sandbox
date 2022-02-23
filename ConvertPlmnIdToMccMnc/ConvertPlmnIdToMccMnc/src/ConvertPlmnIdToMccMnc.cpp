#include "ConvertPlmnIdToMccMnc.hpp"

#include <Common/Bit/AlbaBitManipulation.hpp>

using BitManipulator = alba::AlbaBitManipulation<alba::u32>;
namespace alba
{
/*MccMncPair convertPlmnIdToMccMnc(u32 const plmnId)
{
    constexpr unsigned char fillerDigitValue = 0x0F;
    using BitManipulator = AlbaBitManipulation<u32>;
    u16 mcc = BitManipulator::concatenateNibbles(BitManipulator::getNibbleAt<2>(plmnId), BitManipulator::getNibbleAt<5>(plmnId), BitManipulator::getNibbleAt<4>(plmnId));
    u16 mnc = BitManipulator::concatenateNibbles(BitManipulator::getNibbleAt<0>(plmnId), BitManipulator::getNibbleAt<1>(plmnId), BitManipulator::getNibbleAt<3>(plmnId));
    if(BitManipulator::getNibbleAt<0>(mnc) == fillerDigitValue)
    {
        mnc = BitManipulator::shiftNibblesToTheRight<1>(mnc);
    }
    return MccMncPair{mcc, mnc};
}
*/

MccMncPair convertPlmnIdToMccMnc(u32 const plmnId)
{
    constexpr unsigned char fillerDigitValue = 0x0F;
    u16 mcc = BitManipulator::getNibbleAt<2>(plmnId)*100 + BitManipulator::getNibbleAt<5>(plmnId)*10 + BitManipulator::getNibbleAt<4>(plmnId);
    u16 mnc = 0;
    if(BitManipulator::getNibbleAt<3>(plmnId) == fillerDigitValue)
    {
        mnc = BitManipulator::getNibbleAt<0>(plmnId)*10 + BitManipulator::getNibbleAt<1>(plmnId);
    }
    else
    {
        mnc = BitManipulator::getNibbleAt<0>(plmnId)*100 + BitManipulator::getNibbleAt<1>(plmnId)*10 + BitManipulator::getNibbleAt<3>(plmnId);
    }
    return MccMncPair{mcc, mnc};
}

}
