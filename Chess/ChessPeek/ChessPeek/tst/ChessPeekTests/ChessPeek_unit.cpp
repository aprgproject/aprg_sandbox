#include <ChessPeek/ChessPeek.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace std;

namespace alba
{

namespace chess
{

namespace
{
string getDisplayableString(uint64_t const value)
{
    string bitsetString(bitset<64>(value).to_string());
    return string("0B") + bitsetString.substr(0, 8)
            + "_" + bitsetString.substr(8, 8)
            + "_" + bitsetString.substr(16, 8)
            + "_" + bitsetString.substr(24, 8)
            + "_" + bitsetString.substr(32, 8)
            + "_" + bitsetString.substr(40, 8)
            + "_" + bitsetString.substr(48, 8)
            + "_" + bitsetString.substr(56, 8);
}
}

TEST(ChessPeekTest, CheckScreenAndSaveDetailsWorks)
{
    ChessPeek chessPeek;

    chessPeek.checkScreenAndSaveDetails();
}

TEST(ChessPeekTest, StartNewAnalysisUsingEngineWorks)
{
    ChessPeek chessPeek;

    chessPeek.startNewAnalysisUsingEngine();
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

TEST(ChessPeekTest, SavePiecesValueFromMatrixFromBasisBitmap)
{
    ChessPeek chessPeek;
    chessPeek.checkScreenAndSaveDetails();

    ChessPeek::ChessCellBitValueMatrix matrix(chessPeek.getChessCellBitValueMatrix());

    cout << "black rook   in white square : [" << getDisplayableString(matrix.getEntry(0, 0)) << "]" << endl;
    cout << "black knight in black square : [" << getDisplayableString(matrix.getEntry(1, 0)) << "]" << endl;
    cout << "black bishop in white square : [" << getDisplayableString(matrix.getEntry(2, 0)) << "]" << endl;
    cout << "black queen  in black square : [" << getDisplayableString(matrix.getEntry(3, 0)) << "]" << endl;
    cout << "black king   in white square : [" << getDisplayableString(matrix.getEntry(4, 0)) << "]" << endl;
    cout << "black bishop in black square : [" << getDisplayableString(matrix.getEntry(5, 0)) << "]" << endl;
    cout << "black knight in white square : [" << getDisplayableString(matrix.getEntry(6, 0)) << "]" << endl;
    cout << "black rook   in black square : [" << getDisplayableString(matrix.getEntry(7, 0)) << "]" << endl;

    cout << "black pawn   in black square : [" << getDisplayableString(matrix.getEntry(0, 1)) << "]" << endl;
    cout << "black pawn   in white square : [" << getDisplayableString(matrix.getEntry(1, 1)) << "]" << endl;
    cout << "black pawn   in black square : [" << getDisplayableString(matrix.getEntry(2, 1)) << "]" << endl;
    cout << "black pawn   in white square : [" << getDisplayableString(matrix.getEntry(3, 1)) << "]" << endl;
    cout << "black pawn   in black square : [" << getDisplayableString(matrix.getEntry(4, 1)) << "]" << endl;
    cout << "black pawn   in white square : [" << getDisplayableString(matrix.getEntry(5, 1)) << "]" << endl;
    cout << "black pawn   in black square : [" << getDisplayableString(matrix.getEntry(6, 1)) << "]" << endl;
    cout << "black pawn   in white square : [" << getDisplayableString(matrix.getEntry(7, 1)) << "]" << endl;

    cout << "white pawn   in white square : [" << getDisplayableString(matrix.getEntry(0, 6)) << "]" << endl;
    cout << "white pawn   in black square : [" << getDisplayableString(matrix.getEntry(1, 6)) << "]" << endl;
    cout << "white pawn   in white square : [" << getDisplayableString(matrix.getEntry(2, 6)) << "]" << endl;
    cout << "white pawn   in black square : [" << getDisplayableString(matrix.getEntry(3, 6)) << "]" << endl;
    cout << "white pawn   in white square : [" << getDisplayableString(matrix.getEntry(4, 6)) << "]" << endl;
    cout << "white pawn   in black square : [" << getDisplayableString(matrix.getEntry(5, 6)) << "]" << endl;
    cout << "white pawn   in white square : [" << getDisplayableString(matrix.getEntry(6, 6)) << "]" << endl;
    cout << "white pawn   in black square : [" << getDisplayableString(matrix.getEntry(7, 6)) << "]" << endl;

    cout << "white rook   in black square : [" << getDisplayableString(matrix.getEntry(0, 7)) << "]" << endl;
    cout << "white knight in white square : [" << getDisplayableString(matrix.getEntry(1, 7)) << "]" << endl;
    cout << "white bishop in black square : [" << getDisplayableString(matrix.getEntry(2, 7)) << "]" << endl;
    cout << "white queen  in white square : [" << getDisplayableString(matrix.getEntry(3, 7)) << "]" << endl;
    cout << "white king   in black square : [" << getDisplayableString(matrix.getEntry(4, 7)) << "]" << endl;
    cout << "white bishop in white square : [" << getDisplayableString(matrix.getEntry(5, 7)) << "]" << endl;
    cout << "white knight in black square : [" << getDisplayableString(matrix.getEntry(6, 7)) << "]" << endl;
    cout << "white rook   in white square : [" << getDisplayableString(matrix.getEntry(7, 7)) << "]" << endl;


    cout << "EmptySpace1                  : [" << getDisplayableString(matrix.getEntry(4, 4)) << "]" << endl;
    cout << "EmptySpace2                  : [" << getDisplayableString(matrix.getEntry(4, 5)) << "]" << endl;
    cout << "EmptySpace3                  : [" << getDisplayableString(matrix.getEntry(5, 4)) << "]" << endl;
    cout << "EmptySpace4                  : [" << getDisplayableString(matrix.getEntry(5, 5)) << "]" << endl;
}

TEST(ChessPeekTest, SavePiecesValueFromMatrixFromSpecialBitmap)
{
    ChessPeek chessPeek;
    chessPeek.checkScreenAndSaveDetails();

    ChessPeek::ChessCellBitValueMatrix matrix(chessPeek.getChessCellBitValueMatrix());
    cout << "white queen  in white square : [" << getDisplayableString(matrix.getEntry(5, 4)) << "]" << endl;
}

}

}
