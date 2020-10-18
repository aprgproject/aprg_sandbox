#pragma once

#include <AlbaOptional.hpp>
#include "CrawlMode.hpp"

namespace aprgWebCrawler
{

struct DownloadLowSpeedLimitConfiguration
{
    int m_lowSpeedLimit;
    int m_lowSpeedTime;
};
typedef alba::AlbaOptional<DownloadLowSpeedLimitConfiguration> DownloadLowSpeedLimitConfigurationOptional;

class CrawlConfiguration
{
public:    CrawlConfiguration(CrawlMode mode);
    bool isFileToBeDownloadUntilSuccessful() const;
    int getNumberOfRetries() const;
    double getMinimumFileSize() const;
    DownloadLowSpeedLimitConfigurationOptional getDownloadLowSpeedLimitConfigurationOptional() const;

private:
    bool m_isFileToBeDownloadUntilSuccessful;
    int m_numberOfRetries;
    double m_minimumFileSize;
    DownloadLowSpeedLimitConfigurationOptional m_lowSpeedLimitOptional;
};

}