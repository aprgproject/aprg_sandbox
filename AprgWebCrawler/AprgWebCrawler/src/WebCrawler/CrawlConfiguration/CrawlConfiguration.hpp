#pragma once

#include <Common/Optional/AlbaOptional.hpp>
#include <WebCrawler/CrawlMode.hpp>

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
public:
    CrawlConfiguration(CrawlMode const mode);
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
