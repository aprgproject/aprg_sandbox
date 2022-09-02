#pragma once

#include <Common/User/AlbaUserInterface.hpp>
#include <InputConfiguration.hpp>

#include <string>

namespace alba
{

namespace soosa
{

class UserInterface
{
public:
    InputConfiguration getSavedConfiguration() const;
    void askUserForMainDetails();
    void askUserForFormDetails();
private:
    std::string askUserForPathOfFormDetailToRead(std::string const& formDetailsDirectoryPath);
    void saveFormDetailsFromFormDetailPath(std::string const& formDetailsFilePath);
    InputConfiguration m_savedConfiguration;
    AlbaUserInterface m_userInterface;
};

}

}
