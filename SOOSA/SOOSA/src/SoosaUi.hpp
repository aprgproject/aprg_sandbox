#pragma once

#include <SoosaConfiguration.hpp>
#include <User/AlbaUserInterface.hpp>

#include <string>
namespace alba
{
class SoosaUi
{
public:
    SoosaConfiguration getSavedConfiguration() const;
    void askUserForMainDetails();
    void askUserForFormDetails();
private:
    void saveFormDetailsFromFormDetailPath(std::string const& formDetailsFilePath);
    std::string askUserForPathOfFormDetailToRead(std::string const& formDetailsDirectoryPath);
    SoosaConfiguration m_savedConfiguration;
    AlbaUserInterface m_userInterface;
};

}
