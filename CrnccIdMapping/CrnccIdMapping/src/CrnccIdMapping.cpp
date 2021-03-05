#include "CrnccIdMapping.hpp"

std::array<TCRNCCommunicationContextId, MAX_USERS_IN_NODEB + 1> CrnccIdMapping::m_crnccIdMapping;

void CrnccIdMapping::set(TCRNCCommunicationContextId const crnccId, TNbccId const nbccId)
{
    m_crnccIdMapping[nbccId] = crnccId;
}

TNbccId CrnccIdMapping::get(TCRNCCommunicationContextId const crnccId)
{
    TNbccId nbccId = 0;
    for(u32 nbccIdIndex = 1; nbccIdIndex <= MAX_USERS_IN_NODEB; ++nbccIdIndex)
    {
        if(m_crnccIdMapping[nbccIdIndex] == crnccId)
        {
            nbccId = nbccIdIndex;
            break;
        }
    }

    return nbccId;
}

void setCrnccIdMapping(TCRNCCommunicationContextId const crnccId, TNbccId const nbccId)
{
    CrnccIdMapping::set(crnccId, nbccId);
}

TNbccId getNbccIdFromCrnccId(TCRNCCommunicationContextId const crnccId)
{
    return CrnccIdMapping::get(crnccId);
}
