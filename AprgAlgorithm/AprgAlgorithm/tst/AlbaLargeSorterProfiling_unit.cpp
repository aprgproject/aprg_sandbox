#include <LargeSorter/AlbaLargeSorter.hpp>

#include <String/AlbaStringHelper.hpp>
#include <Timer/AlbaLocalTimer.hpp>
#include <User/AlbaUserInterface.hpp>

#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace alba;
using namespace std;

#define ALBA_LARGE_SORTER_BLOCK_DIR APRG_DIR "AprgAlgorithm\\AprgAlgorithm\\tst\\FilesForTests\\LargeSorterTest\\blocks"

TEST(AlbaLargeSorterPriofileTest, DISABLED_FirstTest)
{
    unsigned int stringSize(200);
    AlbaLargeSorterConfiguration sorterConfiguration;
    sorterConfiguration.m_directoryForBlocks = ALBA_LARGE_SORTER_BLOCK_DIR;
    sorterConfiguration.m_minimumNumberOfObjectsPerBlock = 10000;
    sorterConfiguration.m_maximumNumberOfObjectsPerBlock = 10000;
    sorterConfiguration.m_maximumNumberOfObjectsInMemory = 1000;
    sorterConfiguration.m_maximumFileStreams = 10;

    AlbaUserInterface ui;
    while(1)
    {
        unsigned int sampleSize(stringHelper::convertStringToNumber<unsigned int>(ui.getUserInput()));

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
    }
}

