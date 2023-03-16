#pragma once

#include <Common/Container/AlbaSingleton.hpp>
#include <Common/Utility/AlbaScopeGuard.hpp>

namespace alba
{

template <typename ConfigurationDetails>
ConfigurationDetails getDefaultConfigurationDetails()
{
    static_assert(sizeof(ConfigurationDetails) == -1, "Default configuration is not defined. This is needed in configuration holder.");
}

template <typename ConfigurationDetails>
class AlbaConfigurationHolder
        : public AlbaSingleton<AlbaConfigurationHolder<ConfigurationDetails>>
{
public:

    AlbaConfigurationHolder()
        : m_configurationDetails{getDefaultConfigurationDetails<ConfigurationDetails>()}
    {}

    AlbaConfigurationHolder(ConfigurationDetails const& configurationDetails)
        : m_configurationDetails{configurationDetails}
    {}

    ConfigurationDetails const& getConfigurationDetails()
    {
        return m_configurationDetails;
    }

    void setConfigurationDetails(
            ConfigurationDetails const& configurationDetails)
    {
        m_configurationDetails = configurationDetails;
    }

    void setConfigurationToDefault()
    {
        setConfigurationDetails(getDefaultConfigurationDetails<ConfigurationDetails>());
    }

protected:
    ConfigurationDetails m_configurationDetails;
};

template <typename ConfigurationDetails>
class AlbaConfigurationScopeObject
{
public:
    AlbaConfigurationScopeObject()
        : m_savedConfigurationDetails(
              AlbaConfigurationHolder<ConfigurationDetails>::getInstance().getConfigurationDetails())
        , m_scopeGuard([&]() noexcept {setInThisScopeTheValuesBack();})
    {}

    void setInThisScopeThisConfiguration(
            ConfigurationDetails const& configurationDetails) const
    {
        AlbaConfigurationHolder<ConfigurationDetails>::getInstance().setConfigurationDetails(configurationDetails);
    }

private:

    void setInThisScopeTheValuesBack() const noexcept // called in scope guard
    {
        AlbaConfigurationHolder<ConfigurationDetails>::getInstance().setConfigurationDetails(m_savedConfigurationDetails);
    }

    ConfigurationDetails m_savedConfigurationDetails;
    AlbaScopeGuard m_scopeGuard; // important to be after configuration details (for order of destruction)
};

} // namespace alba
