//remove this

using TCRNCCommunicationContextId = unsigned int;
using TNbccId = unsigned int;
constexpr unsigned int MAX_USERS_IN_NODEB = 2500;

//remove this


#pragma once

//#include <TCRNCCommunicationContextId.h>
//#include <TNbccId.h>

#ifdef __cplusplus
//#include <DOpenIUBCommonDefs.h>

#include <array>


class CrnccIdMapping
{
public:
    static void set(TCRNCCommunicationContextId const crnccId, TNbccId const nbccId);
    static TNbccId get(TCRNCCommunicationContextId const crnccId);
private:
    static std::array<TCRNCCommunicationContextId, MAX_USERS_IN_NODEB + 1> m_crnccIdMapping;
};


extern "C"
{
void setCrnccIdMapping(TCRNCCommunicationContextId const crnccId, TNbccId const nbccId);
TNbccId getNbccIdFromCrnccId(TCRNCCommunicationContextId const crnccId);
}

#else

void setCrnccIdMapping(TCRNCCommunicationContextId const crnccId, TNbccId const nbccId);
TNbccId getNbccIdFromCrnccId(TCRNCCommunicationContextId const crnccId);

#endif
