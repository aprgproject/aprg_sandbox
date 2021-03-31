#include <AlbaLocalUserAutomation.hpp>

#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <Debug/AlbaDebug.hpp>

#include <gtest/gtest.h>

#include <windows.h>

using namespace alba;
using namespace std;

TEST(RealAutomationTest, NormalizeAudioForMp3Files) //DISABLED_
{
    AlbaWindowsUserAutomation userAutomation;
    AlbaLocalPathHandler mp3FilesPathHandler(R"(N:\MUSIC\AnimeSongs2)");

    while(1)
    {        if(userAutomation.isLetterPressed('s'))  //s for start
        {
            ListOfPaths filePaths;
            ListOfPaths directoryPaths;            mp3FilesPathHandler.findFilesAndDirectoriesOneDepth("*.*", filePaths, directoryPaths);

            for(string const& filePath : filePaths)
            {

                AlbaLocalPathHandler filePathHandler(filePath);
                if(filePathHandler.getExtension() == "mp3" && filePathHandler.getFileSizeEstimate() < 100000000) //100MB
                {
                    //close previous file
                    userAutomation.typeControlAndLetterSimultaneously('W');                    userAutomation.typeKey(VK_RIGHT);
                    userAutomation.typeKey(VK_RETURN);

                    //open file                    userAutomation.typeControlAndLetterSimultaneously('O');
                    userAutomation.sleep(1000);

                    //paste file name
                    userAutomation.setStringToClipboard(filePathHandler.getFile());
                    userAutomation.typeControlAndLetterSimultaneously('V');

                    //type enter key
                    userAutomation.typeKey(VK_RETURN);

                    //wait for the file to load
                    userAutomation.sleep(20000);

                    //select all track
                    userAutomation.typeControlAndLetterSimultaneously('A');
                    //click effect
                    userAutomation.doDoubleLeftClickAt(MousePosition(344,33));
                    //click normalization
                    userAutomation.doDoubleLeftClickAt(MousePosition(433, 443));

                    //type enter key
                    userAutomation.typeKey(VK_RETURN);

                    //wait for normalization process
                    userAutomation.sleep(20000);

                    //export
                    userAutomation.pressDownKey(VK_CONTROL);                    userAutomation.pressDownKey(VK_SHIFT);
                    userAutomation.pressDownKey('E');
                    userAutomation.sleepWithRealisticDelay();
                    userAutomation.pressUpKey('E');                    userAutomation.pressUpKey(VK_SHIFT);
                    userAutomation.pressUpKey(VK_CONTROL);

                    //type enter key
                    userAutomation.sleep(1000);
                    userAutomation.typeKey(VK_RETURN);
                    userAutomation.sleep(1000);
                    userAutomation.typeKey(VK_RETURN);
                    userAutomation.sleep(1000);

                    //wait for export process
                    userAutomation.sleep(20000);

                    //close file
                    userAutomation.typeControlAndLetterSimultaneously('W');                    userAutomation.typeKey(VK_RIGHT);
                    userAutomation.typeKey(VK_RETURN);

                    //break;                }
                else
                {
                    ALBA_PRINT2(filePath, filePathHandler.getFileSizeEstimate());
                }
            }
            break;
        }
        Sleep(100);
    }

}
