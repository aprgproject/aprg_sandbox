/*
 * NsapHelper.hpp
 *
 *  Created on: Feb 16, 2016
 *      Author: Ancha
 */

#ifndef NsapHelper
#define NsapHelper

#include <TTransportLayerAddress.h>
#include <string>
#include <glo_def.h>

namespace CommonClassLib
{
class CNsapHelper
{
private:

    static const u32 AUTHORITY_FORMAT_IDENTIFIER = 0x35;
    static const u32 ICP_IPV4 = 1;
    static const u32 ICP_IPV6 = 0;
    static const u32 IP_NSAP_OFFSET = 3;
    static const u32 ICP_OFFSET = 2;
    static const u32 AFI_OFFSET = 0;

    static inline u8 getIpByte(TTransportLayerAddress const& nsap, u8 const index);
    static std::string convertNsapToIpv4(TTransportLayerAddress const& nsap);
    static std::string convertNsapToIpv6(TTransportLayerAddress const& nsap);

public:
    static const u32 IPV4_SIZE = 4;
    static const u32 IPV6_SIZE = 16;
    static const u8  IP_ADDRESS_LENGTH = 39;

    static void convertNsapToIPv4(TTransportLayerAddress const& nsap, u8 *const destination);
    static void convertNsapToIPv6(TTransportLayerAddress const& nsap, u8 *const destination);
    static void convertIPv4toNsap(u8 const *const ipv4, TTransportLayerAddress& nsap);
    static void convertIPv6toNsap(u8 const *const ipv6, TTransportLayerAddress& nsap);
    static bool isIpv6(TTransportLayerAddress const& nsap);
    static std::string convertNsapToIp(TTransportLayerAddress const& nsap);

};

}
#endif
