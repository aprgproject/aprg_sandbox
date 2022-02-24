#include <Algorithm/LargeSorter/AlbaLargeSorter.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <Common/Time/AlbaLocalTimer.hpp>
#include <Common/User/AlbaUserInterface.hpp>

#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define ALBA_LARGE_SORTER_BLOCK_DIR APRG_DIR "AprgAlgorithm\\AprgAlgorithm\\tst\\FilesForTests\\LargeSorterTest\\blocks"

namespace alba
{

namespace algorithm
{

TEST(AlbaLargeSorterPriofileTest, DISABLED_FirstTest)
{
    unsigned int stringSize(200);
    AlbaLargeSorterConfiguration sorterConfiguration;
    sorterConfiguration.m_directoryForBlocks = AlbaLocalPathHandler(ALBA_LARGE_SORTER_BLOCK_DIR).getFullPath();
    sorterConfiguration.m_minimumNumberOfObjectsPerBlock = 1000;
    sorterConfiguration.m_maximumNumberOfObjectsPerBlock = 10000;
    sorterConfiguration.m_maximumNumberOfObjectsInMemory = 100000;
    sorterConfiguration.m_maximumFileStreams = 10;

    //AlbaUserInterface ui;
    //while(true)
    //{
        unsigned int sampleSize = 1280000;//(stringHelper::convertStringToNumber<unsigned int>(ui.getUserInput()));

        vector<string> samples;
        samples.resize(sampleSize);
        std::generate_n(samples.begin(), sampleSize, [&]()
        {
            return stringHelper::getRandomAlphaNumericString(stringSize);
        });

        AlbaLocalTimer timer;
        timer.resetTimer();
        AlbaLargeSorter<string> largeSorter(sorterConfiguration);
        for(string const& sample : samples)
        {
            largeSorter.add(sample);
        }
        timer.stopTimer();
        cout<<"Executed in "<<timer.getElapsedTimeInMilliseconds()<<" ms"<<endl;
    //}
}

}

}
