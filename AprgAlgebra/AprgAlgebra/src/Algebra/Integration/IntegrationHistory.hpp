#pragma once

#include <Container/AlbaSingleton.hpp>

namespace alba
{

namespace algebra
{

enum class IntegrationPurpose
{
    NotSet,
    IntegrationByParts,
    Trigonometric,
    Substitution,
    NoChange
};

class IntegrationHistory : public AlbaSingleton<IntegrationHistory>
{
private:
    IntegrationHistory(IntegrationHistory const&) = delete;
    IntegrationHistory & operator = (IntegrationHistory const&) = delete;

public:
    IntegrationHistory();
    IntegrationPurpose getLastIntegrationPurpose() const;

    void setLastIntegrationPurpose(IntegrationPurpose const purpose);
    void clear();

private:
    IntegrationPurpose m_lastIntegrationPurpose;
};

}

}
