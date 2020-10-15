#include "CrawlConfiguration.hpp"

namespace alba
{

CrawlConfiguration::CrawlConfiguration(CrawlMode mode)
{
    switch(mode)
    {
    case CrawlMode::ChiaAnime:
        m_isFileToBeDownloadUntilSuccessful=true;
        m_numberOfRetries = 0;
        m_minimumFileSize = 1000000;
    case CrawlMode::Gehen:
        m_isFileToBeDownloadUntilSuccessful=false;
        m_numberOfRetries = 10;
        m_minimumFileSize = 10000;
        break;
    case CrawlMode::GuroManga:
        m_isFileToBeDownloadUntilSuccessful=true;
        m_numberOfRetries = 0;
        m_minimumFileSize = 10000;
        break;
    case CrawlMode::HBrowse:
        m_isFileToBeDownloadUntilSuccessful=true;
        m_numberOfRetries = 0;
        m_minimumFileSize = 10000;
        break;
    case CrawlMode::Hentai2Read:
        m_isFileToBeDownloadUntilSuccessful=true;
        m_numberOfRetries = 0;
        m_minimumFileSize = 10000;
        break;
    case CrawlMode::Mangafox:
        m_isFileToBeDownloadUntilSuccessful=true;
        m_numberOfRetries = 0;
        m_minimumFileSize = 10000;
        break;
    case CrawlMode::MangafoxWithVolume:
        m_isFileToBeDownloadUntilSuccessful=true;
        m_numberOfRetries = 0;
        m_minimumFileSize = 10000;
        break;
    case CrawlMode::Mangahere:
        m_isFileToBeDownloadUntilSuccessful=true;
        m_numberOfRetries = 0;
        m_minimumFileSize = 10000;
        break;
    case CrawlMode::MangaPark:
        m_isFileToBeDownloadUntilSuccessful=true;
        m_numberOfRetries = 0;
        m_minimumFileSize = 10000;
        break;
    case CrawlMode::Y8:
        m_isFileToBeDownloadUntilSuccessful=true;
        m_numberOfRetries = 0;
        m_minimumFileSize = 10000;
        break;
    case CrawlMode::Youtube:
        m_isFileToBeDownloadUntilSuccessful=true;
        m_numberOfRetries = 0;
        m_minimumFileSize = 1000000;
        break;
    case CrawlMode::Empty:
    case CrawlMode::Unknown:
        break;
    }
}

bool CrawlConfiguration::isFileToBeDownloadUntilSuccessful() const
{
    return m_isFileToBeDownloadUntilSuccessful;
}

int CrawlConfiguration::getNumberOfRetries() const
{
    return m_numberOfRetries;
}

double CrawlConfiguration::getMinimumFileSize() const
{
    return m_minimumFileSize;
}

}
