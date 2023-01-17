#include <ChessPeek/ChessPeek.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace std;

namespace alba
{

namespace chess
{

TEST(ChessPeekTest, DISABLED_SaveBitmapOnScreenWorks)
{
    ChessPeek chessPeek;

    chessPeek.saveBitmapOnScreen();
}

TEST(ChessPeekTest, DISABLED_CheckScreenAndSaveDetailsWorks)
{
    ChessPeek chessPeek;

    chessPeek.checkScreenAndSaveDetails();
}

TEST(ChessPeekTest, DISABLED_StartNewAnalysisUsingEngineWorks)
{
    ChessPeek chessPeek;
    chessPeek.startEngineAnalysisOfNewPosition();
    Sleep(10000);
}

TEST(ChessPeekTest, DISABLED_RunOneIterationWorks)
{
    ChessPeek chessPeek;
    chessPeek.runOneIteration();
    Sleep(10000);
}

TEST(ChessPeekTest, DISABLED_RunForeverWorks)
{
    ChessPeek chessPeek;
    chessPeek.runForever();
}
}

}
