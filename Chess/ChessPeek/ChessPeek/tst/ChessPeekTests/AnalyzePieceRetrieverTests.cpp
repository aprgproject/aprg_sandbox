#include <ChessPeek/ChessPieceRetriever.hpp>

#include <Common/Math/Helpers/DigitRelatedHelpers.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

using namespace alba::AprgBitmap;
using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace chess
{

namespace
{
using SetOfPieces = std::set<PieceColorAndType>;
using PointToSetOfPiecesMap = std::map<BitmapXY, SetOfPieces>;

void writeBottomRightBorder(
        BitmapSnippet & outputSnippet,
        BitmapXY const& deltaChessBoard)
{
    BitmapXY cellBottomRightCorner(deltaChessBoard/8U);
    for(unsigned int x=0; x<cellBottomRightCorner.getX(); x++)
    {
        outputSnippet.setPixelAt({x, cellBottomRightCorner.getY()}, 0x000000);
    }
    for(unsigned int y=0; y<cellBottomRightCorner.getY(); y++)
    {
        outputSnippet.setPixelAt({cellBottomRightCorner.getY(), y}, 0x000000);
    }
}

void checkChessCellForWhiteAndBlackPoints(
        PointToSetOfPiecesMap & whitePointsToUniquePiecesMap,
        PointToSetOfPiecesMap & blackPointsToUniquePiecesMap,
        ChessPieceRetriever const& retriever,
        BitmapSnippet const& inputSnippet,
        PieceColorAndType const piece,
        unsigned int const xIndex,
        unsigned int const yIndex)
{
    BitmapXYs whitePoints, blackPoints;
    retriever.retrieveWhiteOffsetPoints(whitePoints, inputSnippet, xIndex, yIndex);
    retriever.retrieveBlackOffsetPoints(blackPoints, inputSnippet, xIndex, yIndex);

    for(BitmapXY const& whitePoint : whitePoints)
    {
        whitePointsToUniquePiecesMap[whitePoint].emplace(piece);
    }
    for(BitmapXY const& blackPoint : blackPoints)
    {
        blackPointsToUniquePiecesMap[blackPoint].emplace(piece);
    }
}

void checkChessCellsForWhiteAndBlackPointsBlackUpWhiteDown(
        PointToSetOfPiecesMap & whitePointsToUniquePiecesMap,
        PointToSetOfPiecesMap & blackPointsToUniquePiecesMap,
        ChessPieceRetriever const& retriever,
        BitmapSnippet const& inputSnippet)
{
    checkChessCellForWhiteAndBlackPoints(whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet, PieceColorAndType::BlackKnight, 1U, 0U);
    checkChessCellForWhiteAndBlackPoints(whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet, PieceColorAndType::BlackBishop, 2U, 0U);
    checkChessCellForWhiteAndBlackPoints(whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet, PieceColorAndType::BlackQueen, 3U, 0U);
    checkChessCellForWhiteAndBlackPoints(whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet, PieceColorAndType::BlackKing, 4U, 0U);
    checkChessCellForWhiteAndBlackPoints(whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet, PieceColorAndType::BlackBishop, 5U, 0U);
    checkChessCellForWhiteAndBlackPoints(whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet, PieceColorAndType::BlackKnight, 6U, 0U);
    checkChessCellForWhiteAndBlackPoints(whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet, PieceColorAndType::BlackRook, 7U, 0U);
    checkChessCellForWhiteAndBlackPoints(whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet, PieceColorAndType::BlackPawn, 0U, 1U);
    checkChessCellForWhiteAndBlackPoints(whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet, PieceColorAndType::BlackPawn, 1U, 1U);
    checkChessCellForWhiteAndBlackPoints(whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet, PieceColorAndType::BlackPawn, 2U, 1U);
    checkChessCellForWhiteAndBlackPoints(whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet, PieceColorAndType::BlackPawn, 3U, 1U);
    checkChessCellForWhiteAndBlackPoints(whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet, PieceColorAndType::BlackPawn, 4U, 1U);
    checkChessCellForWhiteAndBlackPoints(whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet, PieceColorAndType::BlackPawn, 5U, 1U);
    checkChessCellForWhiteAndBlackPoints(whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet, PieceColorAndType::BlackPawn, 6U, 1U);
    checkChessCellForWhiteAndBlackPoints(whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet, PieceColorAndType::BlackPawn, 7U, 1U);
    checkChessCellForWhiteAndBlackPoints(whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet, PieceColorAndType::WhiteRook, 7U, 7U);
    checkChessCellForWhiteAndBlackPoints(whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet, PieceColorAndType::WhitePawn, 0U, 6U);
    checkChessCellForWhiteAndBlackPoints(whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet, PieceColorAndType::WhitePawn, 1U, 6U);
    checkChessCellForWhiteAndBlackPoints(whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet, PieceColorAndType::WhitePawn, 2U, 6U);
    checkChessCellForWhiteAndBlackPoints(whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet, PieceColorAndType::WhitePawn, 3U, 6U);
    checkChessCellForWhiteAndBlackPoints(whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet, PieceColorAndType::WhitePawn, 4U, 6U);
    checkChessCellForWhiteAndBlackPoints(whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet, PieceColorAndType::WhitePawn, 5U, 6U);
    checkChessCellForWhiteAndBlackPoints(whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet, PieceColorAndType::WhitePawn, 6U, 6U);
    checkChessCellForWhiteAndBlackPoints(whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet, PieceColorAndType::WhitePawn, 7U, 6U);
    checkChessCellForWhiteAndBlackPoints(whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet, PieceColorAndType::BlackRook, 0U, 0U);
    checkChessCellForWhiteAndBlackPoints(whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet, PieceColorAndType::WhiteRook, 0U, 7U);
    checkChessCellForWhiteAndBlackPoints(whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet, PieceColorAndType::WhiteKnight, 1U, 7U);
    checkChessCellForWhiteAndBlackPoints(whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet, PieceColorAndType::WhiteBishop, 2U, 7U);
    checkChessCellForWhiteAndBlackPoints(whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet, PieceColorAndType::WhiteQueen, 3U, 7U);
    checkChessCellForWhiteAndBlackPoints(whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet, PieceColorAndType::WhiteKing, 4U, 7U);
    checkChessCellForWhiteAndBlackPoints(whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet, PieceColorAndType::WhiteBishop, 5U, 7U);
    checkChessCellForWhiteAndBlackPoints(whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet, PieceColorAndType::WhiteKnight, 6U, 7U);
}

void printChessBitValuesWithBlackUpWhiteDown(
        ChessPieceRetriever const& retriever,
        BitmapSnippet const& inputSnippet)
{
    cout << "White pawn:   [" << retriever.getChessCellBitValue(inputSnippet, 0U, 6U).to_string() << "]" << endl;
    cout << "White pawn:   [" << retriever.getChessCellBitValue(inputSnippet, 1U, 6U).to_string() << "]" << endl;
    cout << "White pawn:   [" << retriever.getChessCellBitValue(inputSnippet, 2U, 6U).to_string() << "]" << endl;
    cout << "White pawn:   [" << retriever.getChessCellBitValue(inputSnippet, 3U, 6U).to_string() << "]" << endl;
    cout << "White pawn:   [" << retriever.getChessCellBitValue(inputSnippet, 4U, 6U).to_string() << "]" << endl;
    cout << "White pawn:   [" << retriever.getChessCellBitValue(inputSnippet, 5U, 6U).to_string() << "]" << endl;
    cout << "White pawn:   [" << retriever.getChessCellBitValue(inputSnippet, 6U, 6U).to_string() << "]" << endl;
    cout << "White pawn:   [" << retriever.getChessCellBitValue(inputSnippet, 7U, 6U).to_string() << "]" << endl;
    cout << "White rook:   [" << retriever.getChessCellBitValue(inputSnippet, 0U, 7U).to_string() << "]" << endl;
    cout << "White rook:   [" << retriever.getChessCellBitValue(inputSnippet, 7U, 7U).to_string() << "]" << endl;
    cout << "White knight: [" << retriever.getChessCellBitValue(inputSnippet, 1U, 7U).to_string() << "]" << endl;
    cout << "White knight: [" << retriever.getChessCellBitValue(inputSnippet, 6U, 7U).to_string() << "]" << endl;
    cout << "White bishop: [" << retriever.getChessCellBitValue(inputSnippet, 2U, 7U).to_string() << "]" << endl;
    cout << "White bishop: [" << retriever.getChessCellBitValue(inputSnippet, 5U, 7U).to_string() << "]" << endl;
    cout << "White queen:  [" << retriever.getChessCellBitValue(inputSnippet, 3U, 7U).to_string() << "]" << endl;
    cout << "White king:   [" << retriever.getChessCellBitValue(inputSnippet, 4U, 7U).to_string() << "]" << endl;
    cout << "Black pawn:   [" << retriever.getChessCellBitValue(inputSnippet, 0U, 1U).to_string() << "]" << endl;
    cout << "Black pawn:   [" << retriever.getChessCellBitValue(inputSnippet, 1U, 1U).to_string() << "]" << endl;
    cout << "Black pawn:   [" << retriever.getChessCellBitValue(inputSnippet, 2U, 1U).to_string() << "]" << endl;
    cout << "Black pawn:   [" << retriever.getChessCellBitValue(inputSnippet, 3U, 1U).to_string() << "]" << endl;
    cout << "Black pawn:   [" << retriever.getChessCellBitValue(inputSnippet, 4U, 1U).to_string() << "]" << endl;
    cout << "Black pawn:   [" << retriever.getChessCellBitValue(inputSnippet, 5U, 1U).to_string() << "]" << endl;
    cout << "Black pawn:   [" << retriever.getChessCellBitValue(inputSnippet, 6U, 1U).to_string() << "]" << endl;
    cout << "Black pawn:   [" << retriever.getChessCellBitValue(inputSnippet, 7U, 1U).to_string() << "]" << endl;
    cout << "Black rook:   [" << retriever.getChessCellBitValue(inputSnippet, 0U, 0U).to_string() << "]" << endl;
    cout << "Black rook:   [" << retriever.getChessCellBitValue(inputSnippet, 7U, 0U).to_string() << "]" << endl;
    cout << "Black knight: [" << retriever.getChessCellBitValue(inputSnippet, 1U, 0U).to_string() << "]" << endl;
    cout << "Black knight: [" << retriever.getChessCellBitValue(inputSnippet, 6U, 0U).to_string() << "]" << endl;
    cout << "Black bishop: [" << retriever.getChessCellBitValue(inputSnippet, 2U, 0U).to_string() << "]" << endl;
    cout << "Black bishop: [" << retriever.getChessCellBitValue(inputSnippet, 5U, 0U).to_string() << "]" << endl;
    cout << "Black queen:  [" << retriever.getChessCellBitValue(inputSnippet, 3U, 0U).to_string() << "]" << endl;
    cout << "Black king:   [" << retriever.getChessCellBitValue(inputSnippet, 4U, 0U).to_string() << "]" << endl;
}

unsigned int getLabelBasedOnSetOfPieces(SetOfPieces const& setOfPieces)
{
    unsigned int result(0U);
    for(PieceColorAndType const piece : setOfPieces)
    {
        result += static_cast<unsigned int>(piece)*13U;
    }
    return result;
}

uint32_t getLabelColor(unsigned int const label)
{
    unsigned int digits = getNumberOfBase10Digits(label);
    double newValue = (static_cast<double>(1)/label) * pow(10, digits+8);
    return static_cast<uint32_t>(newValue) % 0xFFFFFF;
}

uint32_t getLabelColor(SetOfPieces const& setOfPieces)
{
    return getLabelColor(getLabelBasedOnSetOfPieces(setOfPieces));
}

}

TEST(AnalyzePieceRetrieverTest, DISABLED_CheckChessBitValue_ForChessDotComUserVsUser)
{
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\ChessDotComUserVsUser\ChessDotComUserVsUser.bmp)");

    ChessPeekConfiguration configuration(ChessPeekConfigurationType::ChessDotComUserVsUser);
    Bitmap inputBitmap(inputFile.getFullPath());
    BitmapSnippet inputSnippet(inputBitmap.getSnippetReadFromFile(configuration.getTopLeftCorner(), configuration.getBottomRightCorner()));
    ChessPieceRetriever retriever(configuration);

    printChessBitValuesWithBlackUpWhiteDown(retriever, inputSnippet);
}

TEST(AnalyzePieceRetrieverTest, DISABLED_CheckChessBitValue_ForChessDotComUserVsComputer)
{
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\ChessDotComUserVsComputer\ChessDotComUserVsComputer.bmp)");

    ChessPeekConfiguration configuration(ChessPeekConfigurationType::ChessDotComUserVsComputer);
    Bitmap inputBitmap(inputFile.getFullPath());
    BitmapSnippet inputSnippet(inputBitmap.getSnippetReadFromFile(configuration.getTopLeftCorner(), configuration.getBottomRightCorner()));
    ChessPieceRetriever retriever(configuration);

    printChessBitValuesWithBlackUpWhiteDown(retriever, inputSnippet);
}

TEST(AnalyzePieceRetrieverTest, DISABLED_CheckChessBitValue_ForLichessDotOrg)
{
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\LichessDotOrg\LichessDotOrg.bmp)");

    ChessPeekConfiguration configuration(ChessPeekConfigurationType::LichessDotOrg);
    Bitmap inputBitmap(inputFile.getFullPath());
    BitmapSnippet inputSnippet(inputBitmap.getSnippetReadFromFile(configuration.getTopLeftCorner(), configuration.getBottomRightCorner()));
    ChessPieceRetriever retriever(configuration);

    printChessBitValuesWithBlackUpWhiteDown(retriever, inputSnippet);
}

TEST(AnalyzePieceRetrieverTest, DISABLED_FindImportantPoints_ForChessDotComUserVsUser)
{
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\ChessDotComUserVsUser\ChessDotComUserVsUser.bmp)");
    AlbaLocalPathHandler outputFileForWhite(APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\ChessDotComUserVsUser\White.bmp)");
    AlbaLocalPathHandler outputFileForBlack(APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\ChessDotComUserVsUser\Black.bmp)");
    AlbaLocalPathHandler blackFile(APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\Blank.bmp)");
    blackFile.copyToNewFile(outputFileForWhite.getFullPath());
    blackFile.copyToNewFile(outputFileForBlack.getFullPath());

    ChessPeekConfiguration configuration(ChessPeekConfigurationType::ChessDotComUserVsUser);
    Bitmap inputBitmap(inputFile.getFullPath());
    Bitmap outputBitmapForWhite(outputFileForWhite.getFullPath());
    Bitmap outputBitmapForBlack(outputFileForBlack.getFullPath());
    BitmapSnippet inputSnippet(inputBitmap.getSnippetReadFromFile(configuration.getTopLeftCorner(), configuration.getBottomRightCorner()));
    BitmapSnippet outputSnippetForWhite(outputBitmapForWhite.getSnippetReadFromFileWholeBitmap());
    BitmapSnippet outputSnippetForBlack(outputBitmapForBlack.getSnippetReadFromFileWholeBitmap());
    ChessPieceRetriever retriever(configuration);
    PointToSetOfPiecesMap whitePointsToUniquePiecesMap;
    PointToSetOfPiecesMap blackPointsToUniquePiecesMap;
    BitmapXY deltaChessBoard = configuration.getBottomRightCorner() - configuration.getTopLeftCorner();

    checkChessCellsForWhiteAndBlackPointsBlackUpWhiteDown(whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet);

    writeBottomRightBorder(outputSnippetForWhite, deltaChessBoard);
    writeBottomRightBorder(outputSnippetForBlack, deltaChessBoard);
    for(auto const& whitePointsAndUniquePiecesPair : whitePointsToUniquePiecesMap)
    {
        outputSnippetForWhite.setPixelAt(whitePointsAndUniquePiecesPair.first, getLabelColor(whitePointsAndUniquePiecesPair.second));
    }
    for(auto const& blackPointsAndUniquePiecesPair : blackPointsToUniquePiecesMap)
    {
        outputSnippetForBlack.setPixelAt(blackPointsAndUniquePiecesPair.first, getLabelColor(blackPointsAndUniquePiecesPair.second));
    }

    outputBitmapForWhite.setSnippetWriteToFile(outputSnippetForWhite);
    outputBitmapForBlack.setSnippetWriteToFile(outputSnippetForBlack);
}

TEST(AnalyzePieceRetrieverTest, DISABLED_FindImportantPoints_ForChessDotComUserVsComputer)
{
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\ChessDotComUserVsComputer\ChessDotComUserVsComputer.bmp)");
    AlbaLocalPathHandler outputFileForWhite(APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\ChessDotComUserVsComputer\White.bmp)");
    AlbaLocalPathHandler outputFileForBlack(APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\ChessDotComUserVsComputer\Black.bmp)");
    AlbaLocalPathHandler blackFile(APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\Blank.bmp)");
    blackFile.copyToNewFile(outputFileForWhite.getFullPath());
    blackFile.copyToNewFile(outputFileForBlack.getFullPath());

    ChessPeekConfiguration configuration(ChessPeekConfigurationType::ChessDotComUserVsComputer);
    Bitmap inputBitmap(inputFile.getFullPath());
    Bitmap outputBitmapForWhite(outputFileForWhite.getFullPath());
    Bitmap outputBitmapForBlack(outputFileForBlack.getFullPath());
    BitmapSnippet inputSnippet(inputBitmap.getSnippetReadFromFile(configuration.getTopLeftCorner(), configuration.getBottomRightCorner()));
    BitmapSnippet outputSnippetForWhite(outputBitmapForWhite.getSnippetReadFromFileWholeBitmap());
    BitmapSnippet outputSnippetForBlack(outputBitmapForBlack.getSnippetReadFromFileWholeBitmap());
    ChessPieceRetriever retriever(configuration);
    PointToSetOfPiecesMap whitePointsToUniquePiecesMap;
    PointToSetOfPiecesMap blackPointsToUniquePiecesMap;
    BitmapXY deltaChessBoard = configuration.getBottomRightCorner() - configuration.getTopLeftCorner();

    checkChessCellsForWhiteAndBlackPointsBlackUpWhiteDown(whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet);

    writeBottomRightBorder(outputSnippetForWhite, deltaChessBoard);
    writeBottomRightBorder(outputSnippetForBlack, deltaChessBoard);
    for(auto const& whitePointsAndUniquePiecesPair : whitePointsToUniquePiecesMap)
    {
        outputSnippetForWhite.setPixelAt(whitePointsAndUniquePiecesPair.first, getLabelColor(whitePointsAndUniquePiecesPair.second));
    }
    for(auto const& blackPointsAndUniquePiecesPair : blackPointsToUniquePiecesMap)
    {
        outputSnippetForBlack.setPixelAt(blackPointsAndUniquePiecesPair.first, getLabelColor(blackPointsAndUniquePiecesPair.second));
    }

    outputBitmapForWhite.setSnippetWriteToFile(outputSnippetForWhite);
    outputBitmapForBlack.setSnippetWriteToFile(outputSnippetForBlack);
}

TEST(AnalyzePieceRetrieverTest, DISABLED_FindImportantPoints_ForLichessDotOrg)
{
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\LichessDotOrg\LichessDotOrg.bmp)");
    AlbaLocalPathHandler outputFileForWhite(APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\LichessDotOrg\White.bmp)");
    AlbaLocalPathHandler outputFileForBlack(APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\LichessDotOrg\Black.bmp)");
    AlbaLocalPathHandler blackFile(APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\Blank.bmp)");
    blackFile.copyToNewFile(outputFileForWhite.getFullPath());
    blackFile.copyToNewFile(outputFileForBlack.getFullPath());

    ChessPeekConfiguration configuration(ChessPeekConfigurationType::LichessDotOrg);
    Bitmap inputBitmap(inputFile.getFullPath());
    Bitmap outputBitmapForWhite(outputFileForWhite.getFullPath());
    Bitmap outputBitmapForBlack(outputFileForBlack.getFullPath());
    BitmapSnippet inputSnippet(inputBitmap.getSnippetReadFromFile(configuration.getTopLeftCorner(), configuration.getBottomRightCorner()));
    BitmapSnippet outputSnippetForWhite(outputBitmapForWhite.getSnippetReadFromFileWholeBitmap());
    BitmapSnippet outputSnippetForBlack(outputBitmapForBlack.getSnippetReadFromFileWholeBitmap());
    ChessPieceRetriever retriever(configuration);
    PointToSetOfPiecesMap whitePointsToUniquePiecesMap;
    PointToSetOfPiecesMap blackPointsToUniquePiecesMap;
    BitmapXY deltaChessBoard = configuration.getBottomRightCorner() - configuration.getTopLeftCorner();

    checkChessCellsForWhiteAndBlackPointsBlackUpWhiteDown(whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet);

    writeBottomRightBorder(outputSnippetForWhite, deltaChessBoard);
    writeBottomRightBorder(outputSnippetForBlack, deltaChessBoard);
    for(auto const& whitePointsAndUniquePiecesPair : whitePointsToUniquePiecesMap)
    {
        outputSnippetForWhite.setPixelAt(whitePointsAndUniquePiecesPair.first, getLabelColor(whitePointsAndUniquePiecesPair.second));
    }
    for(auto const& blackPointsAndUniquePiecesPair : blackPointsToUniquePiecesMap)
    {
        outputSnippetForBlack.setPixelAt(blackPointsAndUniquePiecesPair.first, getLabelColor(blackPointsAndUniquePiecesPair.second));
    }

    outputBitmapForWhite.setSnippetWriteToFile(outputSnippetForWhite);
    outputBitmapForBlack.setSnippetWriteToFile(outputSnippetForBlack);
}

}

}
