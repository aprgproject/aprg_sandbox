#pragma once

#include "CrawlMode.hpp"

namespace alba
{

class CrawlConfiguration
{
public:
    CrawlConfiguration(CrawlMode mode);
    bool isFileToBeDownloadUntilSuccessful() const;
    int getNumberOfRetries() const;
    double getMinimumFileSize() const;
private:
    bool m_isFileToBeDownloadUntilSuccessful;
    int m_numberOfRetries;
    double m_minimumFileSize;

};

}
