#include <NsapHelper.hpp>
#include <algorithm>
#include <ArraySize.hpp>
#include <cstdio>

namespace CommonClassLib
{

inline u8 CNsapHelper::getIpByte(TTransportLayerAddress const& nsap, u8 const index)
{
    return nsap[IP_NSAP_OFFSET + index];
}

std::string CNsapHelper::convertNsapToIpv4(TTransportLayerAddress const& nsap)
{
    u8 const MAX_IPV4_STRING_LENGTH = 16;
    char buffer[MAX_IPV4_STRING_LENGTH] = {'\0'};

    std::snprintf(buffer, MAX_IPV4_STRING_LENGTH, "%hhu.%hhu.%hhu.%hhu",
      getIpByte(nsap,0), getIpByte(nsap,1), getIpByte(nsap,2), getIpByte(nsap,3));

    return std::string(buffer);
}

std::string CNsapHelper::convertNsapToIpv6(TTransportLayerAddress const& nsap)
{

    u8 const MAX_IPV6_STRING_LENGTH = 40;
    char buffer[MAX_IPV6_STRING_LENGTH] = {'\0'};

    std::snprintf(
      buffer,
      MAX_IPV6_STRING_LENGTH,
      "%02hhX%02hhX:%02hhX%02hhX:%02hhX%02hhX:%02hhX%02hhX:%02hhX%02hhX:%02hhX%02hhX:%02hhX%02hhX:%02hhX%02hhX",
      getIpByte(nsap,0), getIpByte(nsap,1),
      getIpByte(nsap,2), getIpByte(nsap,3),
      getIpByte(nsap,4), getIpByte(nsap,5),
      getIpByte(nsap,6), getIpByte(nsap,7),
      getIpByte(nsap,8), getIpByte(nsap,9),
      getIpByte(nsap,10), getIpByte(nsap,11),
      getIpByte(nsap,12), getIpByte(nsap,13),
      getIpByte(nsap,14), getIpByte(nsap,15));

    return std::string(buffer);
}

void CNsapHelper::convertNsapToIPv4(TTransportLayerAddress const& nsap, u8 *const destination)
{
    if(destination != nullptr)
    {
        std::copy_n(&nsap[IP_NSAP_OFFSET], IPV4_SIZE , destination);
    }
}

void CNsapHelper::convertNsapToIPv6(TTransportLayerAddress const& nsap, u8 *const destination)
{
    if(destination != nullptr)
    {
        std::copy_n(&nsap[IP_NSAP_OFFSET], IPV6_SIZE , destination);
    }
}

void CNsapHelper::convertIPv4toNsap(u8 const *const ipv4, TTransportLayerAddress& nsap)
{
    std::fill_n(nsap, arraySize(nsap), 0);
    if(ipv4 != nullptr)
    {
        nsap[AFI_OFFSET] = AUTHORITY_FORMAT_IDENTIFIER;
        nsap[ICP_OFFSET] = ICP_IPV4;
        std::copy_n(ipv4, IPV4_SIZE, &nsap[IP_NSAP_OFFSET]);
    }
}

void CNsapHelper::convertIPv6toNsap(u8 const *const ipv6, TTransportLayerAddress& nsap)
{
    std::fill_n(nsap, arraySize(nsap), 0);
    if(ipv6 != nullptr)
    {
        nsap[AFI_OFFSET] = AUTHORITY_FORMAT_IDENTIFIER;
        nsap[ICP_OFFSET] = ICP_IPV6;
        std::copy_n(ipv6, IPV6_SIZE, &nsap[IP_NSAP_OFFSET]);
    }
}

bool CNsapHelper::isIpv6(TTransportLayerAddress const &nsap)
{
    return nsap[ICP_OFFSET] == ICP_IPV6;
}

std::string CNsapHelper::convertNsapToIp(TTransportLayerAddress const& nsap)
{
    if(nsap[AFI_OFFSET] != AUTHORITY_FORMAT_IDENTIFIER)
    {
      return std::string("");
    }
    return isIpv6(nsap) ? convertNsapToIpv6(nsap) : convertNsapToIpv4(nsap);
}

}
