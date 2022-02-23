#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/File/AlbaFileReader.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <UserAutomation/AlbaLocalUserAutomation.hpp>

#include <gtest/gtest.h>
#include <windows.h>

#include <sstream>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{

TEST(RealAutomationTest, DISABLED_TraverseTalonRoShops)//DISABLED_
{
    AlbaWindowsUserAutomation userAutomation;
    //AlbaLocalPathHandler itemDatabaseFolder(R"(C:\Users\detectivemark7\Desktop\RO\TalonRO\BuyingShops\)");
    AlbaLocalPathHandler itemDatabaseFolder(R"(C:\Users\detectivemark7\Desktop\RO\TalonRO\SellingShops\)");

    userAutomation.doLeftClickAt(MousePosition(2368,52));

    //string talonRoPath(R"(https://panel.talonro.com/whobuy/)");
    string talonRoPath(R"(https://panel.talonro.com/whosell/)");
    userAutomation.sleepWithRealisticDelay();
    userAutomation.typeKey(VK_DELETE);
    userAutomation.setStringToClipboard(talonRoPath);
    userAutomation.typeControlAndLetterSimultaneously('V');
    userAutomation.sleepWithRealisticDelay();
    userAutomation.typeKey(VK_RETURN);

    userAutomation.sleep(3000);

    for(unsigned int page=1; page<=1000; page++)
    {
        userAutomation.typeControlAndLetterSimultaneously('S');
        userAutomation.sleep(2000);

        stringstream fileName;
        fileName << "page_" << page << ".html";
        AlbaLocalPathHandler filePathHandler(itemDatabaseFolder.getFullPath() + fileName.str());
        userAutomation.setStringToClipboard(filePathHandler.getFullPath());
        userAutomation.typeControlAndLetterSimultaneously('V');
        userAutomation.sleepWithRealisticDelay();
        userAutomation.typeKey(VK_RETURN);
        userAutomation.sleepWithRealisticDelay();
        userAutomation.typeKey(VK_RETURN);
        userAutomation.sleepWithRealisticDelay();
        userAutomation.typeKey(VK_RETURN);
        userAutomation.sleepWithRealisticDelay();
        userAutomation.typeKey(VK_RETURN);

        userAutomation.sleep(2000);

        ifstream savedWebPage(filePathHandler.getFullPath());
        AlbaFileReader fileReader(savedWebPage);
        fileReader.setMaxBufferSize(100000);
        bool isNextDisabled(false);
        while(fileReader.isNotFinished())
        {
            string line(fileReader.getLineAndIgnoreWhiteSpaces());
            if(isStringFoundInsideTheOtherStringCaseSensitive(line, R"(class="paginate_button page-item next disabled")"))
            {
                isNextDisabled=true;
                break;
            }
        }
        if(isNextDisabled)
        {
            break;
        }
        else
        {
            userAutomation.doLeftClickAt(MousePosition(3398,514));
            userAutomation.doLeftClickAt(MousePosition(2368,52));
            userAutomation.sleep(2000);
        }
    }
}

TEST(RealAutomationTest, DISABLED_TraverseDatabaseOnRms)
{
    AlbaWindowsUserAutomation userAutomation;
    AlbaLocalPathHandler itemDatabaseFolder(R"(C:\Users\detectivemark7\Desktop\RO\RMS\MonsterDatabaseTraversal\)");

    for(char letter='a'; letter<='z'; letter++)
    {
        for(unsigned int pageNumber=1; pageNumber<=100; pageNumber++)
        {
            userAutomation.doLeftClickAt(MousePosition(2368,52));

            stringstream rmsPath;
            rmsPath << R"(https://ratemyserver.net/index.php?page=mob_db&list=1&letter=)" << letter << R"(&page_num=)" << pageNumber;
            userAutomation.sleepWithRealisticDelay();
            userAutomation.typeKey(VK_DELETE);
            userAutomation.setStringToClipboard(rmsPath.str());
            userAutomation.typeControlAndLetterSimultaneously('V');
            userAutomation.sleepWithRealisticDelay();
            userAutomation.typeKey(VK_RETURN);

            userAutomation.sleep(3000);

            userAutomation.typeControlAndLetterSimultaneously('S');
            stringstream fileName;
            fileName << "monsterWithLetter_" << letter << "_pageNumber_" << pageNumber << ".html";
            AlbaLocalPathHandler filePathHandler(itemDatabaseFolder.getFullPath() + fileName.str());
            userAutomation.setStringToClipboard(filePathHandler.getFullPath());
            userAutomation.typeControlAndLetterSimultaneously('V');
            userAutomation.sleepWithRealisticDelay();
            userAutomation.typeKey(VK_RETURN);
            userAutomation.sleepWithRealisticDelay();
            userAutomation.typeKey(VK_RETURN);
            userAutomation.sleepWithRealisticDelay();
            userAutomation.typeKey(VK_RETURN);
            userAutomation.sleepWithRealisticDelay();
            userAutomation.typeKey(VK_RETURN);

            ifstream savedWebPage(filePathHandler.getFullPath());
            AlbaFileReader fileReader(savedWebPage);
            bool isNextPageTextFound(false);
            while(fileReader.isNotFinished())
            {
                string line(fileReader.getLineAndIgnoreWhiteSpaces());
                if(isStringFoundInsideTheOtherStringCaseSensitive(line, R"(title="Next page")"))
                {
                    isNextPageTextFound=true;
                    break;
                }
            }
            if(!isNextPageTextFound)
            {
                break;
            }
        }
    }
}

TEST(RealAutomationTest, DISABLED_NormalizeAudioForMp3Files)
{
    AlbaWindowsUserAutomation userAutomation;
    AlbaLocalPathHandler mp3FilesPathHandler(R"(N:\MUSIC\111_DoAutomationHere)");

    while(1)
    {
        if(userAutomation.isLetterPressed('s'))  //s for start
        {
            ListOfPaths filePaths;
            ListOfPaths directoryPaths;
            mp3FilesPathHandler.findFilesAndDirectoriesOneDepth("*.*", filePaths, directoryPaths);

            for(string const& filePath : filePaths)
            {

                AlbaLocalPathHandler filePathHandler(filePath);
                if(filePathHandler.getExtension() == "mp3" && filePathHandler.getFileSizeEstimate() < 100000000) //100MB
                {
                    //close previous file
                    userAutomation.typeControlAndLetterSimultaneously('W');
                    userAutomation.sleep(1000);
                    userAutomation.typeKey(VK_RIGHT);
                    userAutomation.typeKey(VK_RETURN);
                    userAutomation.sleep(2000);

                    //open file
                    userAutomation.typeControlAndLetterSimultaneously('O');
                    userAutomation.sleep(1000);

                    //paste file name
                    userAutomation.setStringToClipboard(filePathHandler.getFile());
                    userAutomation.typeControlAndLetterSimultaneously('V');

                    //type enter key
                    userAutomation.typeKey(VK_RETURN);

                    //wait for the file to load
                    userAutomation.sleep(10000);

                    //select all track
                    userAutomation.typeControlAndLetterSimultaneously('A');

                    //click effect
                    userAutomation.doDoubleLeftClickAt(MousePosition(344,33));

                    //click normalization
                    userAutomation.doDoubleLeftClickAt(MousePosition(433, 443));

                    //type enter key
                    userAutomation.typeKey(VK_RETURN);

                    //wait for normalization process
                    userAutomation.sleep(10000);

                    //export
                    userAutomation.pressDownKey(VK_CONTROL);
                    userAutomation.pressDownKey(VK_SHIFT);
                    userAutomation.pressDownKey('E');
                    userAutomation.sleepWithRealisticDelay();
                    userAutomation.pressUpKey('E');
                    userAutomation.pressUpKey(VK_SHIFT);
                    userAutomation.pressUpKey(VK_CONTROL);
                    userAutomation.sleep(2000);

                    //type enter key multiple times
                    userAutomation.sleep(1000);
                    userAutomation.typeKey(VK_RETURN); // save
                    userAutomation.sleep(1000);
                    userAutomation.typeKey('Y'); //yes to replace
                    userAutomation.sleep(1000);
                    userAutomation.doDoubleLeftClickAt(MousePosition(1074,687)); //click ok
                    userAutomation.typeKey(VK_RIGHT); //type right to avoid stop button

                    //wait for export process
                    userAutomation.sleep(15000);

                    //type enter key multiple times to ensure everything is closed
                    userAutomation.sleep(250);
                    userAutomation.typeKey(VK_RETURN);
                    userAutomation.sleep(250);
                    userAutomation.typeKey(VK_RETURN);
                    userAutomation.sleep(250);
                    userAutomation.typeKey(VK_RETURN);
                    userAutomation.sleep(250);
                    userAutomation.typeKey(VK_RETURN);

                    //close file
                    userAutomation.typeControlAndLetterSimultaneously('W');
                    userAutomation.sleep(1000);
                    userAutomation.typeKey(VK_RIGHT);
                    userAutomation.typeKey(VK_RETURN);
                    userAutomation.sleep(2000);

                    //break;
                }
                else
                {
                    cout << "Ignored file: " << filePath << ": size: " << filePathHandler.getFileSizeEstimate() << endl;
                }
            }
            break;
        }
        Sleep(100);
    }
}

}
