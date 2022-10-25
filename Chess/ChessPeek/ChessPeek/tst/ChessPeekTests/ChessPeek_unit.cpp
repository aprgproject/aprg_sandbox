#include <ChessPeek/ChessPeek.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace std;

namespace alba
{

namespace chess
{

TEST(ChessPeekTest, CheckScreenAndSaveDetailsWorks)
{
    ChessPeek chessPeek;

    chessPeek.checkScreenAndSaveDetails();
}

TEST(ChessPeekTest, StartNewAnalysisUsingEngineWorks)
{
    ChessPeek chessPeek;

    chessPeek.startAnalysisUsingEngine();
    Sleep(10000);
}

TEST(ChessPeekTest, RunOneIterationWorks)
{
    ChessPeek chessPeek;

    chessPeek.runOneIteration();
    Sleep(10000);
}

TEST(ChessPeekTest, RunForeverWorks)
{
    ChessPeek chessPeek;

    chessPeek.runForever();
}

}

}
