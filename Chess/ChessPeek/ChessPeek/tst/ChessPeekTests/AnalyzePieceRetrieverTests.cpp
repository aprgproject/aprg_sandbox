#include <Bitmap/Bitmap.hpp>
#include <ChessPeek/ChessPieceRetriever.hpp>
#include <ChessPeek/Utilities.hpp>
#include <Common/Math/Helpers/DigitRelatedHelpers.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

using namespace alba::AprgBitmap;
using namespace alba::mathHelper;
using namespace std;

namespace alba {

namespace chess {

namespace {
using SetOfPieces = std::set<PieceColorAndType>;
using PointToSetOfPiecesMap = std::map<XY, SetOfPieces>;

void writeBottomRightBorder(BitmapSnippet& outputSnippet, XY const& deltaChessBoard) {
    XY cellBottomRightCorner(deltaChessBoard / 8U);
    for (int x = 0; x < cellBottomRightCorner.getX(); x++) {
        outputSnippet.setPixelAt({x, cellBottomRightCorner.getY()}, 0x000000);
    }
    for (int y = 0; y < cellBottomRightCorner.getY(); y++) {
        outputSnippet.setPixelAt({cellBottomRightCorner.getY(), y}, 0x000000);
    }
}

void checkChessCellForWhiteAndBlackPoints(
    PointToSetOfPiecesMap& whitePointsToUniquePiecesMap, PointToSetOfPiecesMap& blackPointsToUniquePiecesMap,
    ChessPieceRetriever const& retriever, PieceColorAndType const piece, unsigned int const xIndex,
    unsigned int const yIndex) {
    XYs whitePoints, blackPoints;
    retriever.retrieveWhiteOffsetPoints(whitePoints, xIndex, yIndex);
    retriever.retrieveBlackOffsetPoints(blackPoints, xIndex, yIndex);

    for (XY const& whitePoint : whitePoints) {
        whitePointsToUniquePiecesMap[whitePoint].emplace(piece);
    }
    for (XY const& blackPoint : blackPoints) {
        blackPointsToUniquePiecesMap[blackPoint].emplace(piece);
    }
}

void checkChessCellsForWhiteAndBlackPointsBlackUpWhiteDown(
    PointToSetOfPiecesMap& whitePointsToUniquePiecesMap, PointToSetOfPiecesMap& blackPointsToUniquePiecesMap,
    ChessPieceRetriever const& retriever, BitmapSnippet const& inputSnippet) {
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::BlackKnight, 1U, 0U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::BlackBishop, 2U, 0U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::BlackQueen, 3U, 0U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::BlackKing, 4U, 0U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::BlackBishop, 5U, 0U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::BlackKnight, 6U, 0U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::BlackRook, 7U, 0U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::BlackPawn, 0U, 1U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::BlackPawn, 1U, 1U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::BlackPawn, 2U, 1U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::BlackPawn, 3U, 1U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::BlackPawn, 4U, 1U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::BlackPawn, 5U, 1U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::BlackPawn, 6U, 1U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::BlackPawn, 7U, 1U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::WhiteRook, 7U, 7U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::WhitePawn, 0U, 6U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::WhitePawn, 1U, 6U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::WhitePawn, 2U, 6U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::WhitePawn, 3U, 6U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::WhitePawn, 4U, 6U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::WhitePawn, 5U, 6U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::WhitePawn, 6U, 6U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::WhitePawn, 7U, 6U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::BlackRook, 0U, 0U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::WhiteRook, 0U, 7U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::WhiteKnight, 1U, 7U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::WhiteBishop, 2U, 7U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::WhiteQueen, 3U, 7U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::WhiteKing, 4U, 7U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::WhiteBishop, 5U, 7U);
    checkChessCellForWhiteAndBlackPoints(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, PieceColorAndType::WhiteKnight, 6U, 7U);
}

void printChessBitValuesWithBlackUpWhiteDown(ChessPieceRetriever const& retriever) {
    cout << "White pawn:   [" << retriever.getChessCellBitValue(0U, 6U).to_string() << "]\n";
    cout << "White pawn:   [" << retriever.getChessCellBitValue(1U, 6U).to_string() << "]\n";
    cout << "White pawn:   [" << retriever.getChessCellBitValue(2U, 6U).to_string() << "]\n";
    cout << "White pawn:   [" << retriever.getChessCellBitValue(3U, 6U).to_string() << "]\n";
    cout << "White pawn:   [" << retriever.getChessCellBitValue(4U, 6U).to_string() << "]\n";
    cout << "White pawn:   [" << retriever.getChessCellBitValue(5U, 6U).to_string() << "]\n";
    cout << "White pawn:   [" << retriever.getChessCellBitValue(6U, 6U).to_string() << "]\n";
    cout << "White pawn:   [" << retriever.getChessCellBitValue(7U, 6U).to_string() << "]\n";
    cout << "White rook:   [" << retriever.getChessCellBitValue(0U, 7U).to_string() << "]\n";
    cout << "White rook:   [" << retriever.getChessCellBitValue(7U, 7U).to_string() << "]\n";
    cout << "White knight: [" << retriever.getChessCellBitValue(1U, 7U).to_string() << "]\n";
    cout << "White knight: [" << retriever.getChessCellBitValue(6U, 7U).to_string() << "]\n";
    cout << "White bishop: [" << retriever.getChessCellBitValue(2U, 7U).to_string() << "]\n";
    cout << "White bishop: [" << retriever.getChessCellBitValue(5U, 7U).to_string() << "]\n";
    cout << "White queen:  [" << retriever.getChessCellBitValue(3U, 7U).to_string() << "]\n";
    cout << "White king:   [" << retriever.getChessCellBitValue(4U, 7U).to_string() << "]\n";
    cout << "Black pawn:   [" << retriever.getChessCellBitValue(0U, 1U).to_string() << "]\n";
    cout << "Black pawn:   [" << retriever.getChessCellBitValue(1U, 1U).to_string() << "]\n";
    cout << "Black pawn:   [" << retriever.getChessCellBitValue(2U, 1U).to_string() << "]\n";
    cout << "Black pawn:   [" << retriever.getChessCellBitValue(3U, 1U).to_string() << "]\n";
    cout << "Black pawn:   [" << retriever.getChessCellBitValue(4U, 1U).to_string() << "]\n";
    cout << "Black pawn:   [" << retriever.getChessCellBitValue(5U, 1U).to_string() << "]\n";
    cout << "Black pawn:   [" << retriever.getChessCellBitValue(6U, 1U).to_string() << "]\n";
    cout << "Black pawn:   [" << retriever.getChessCellBitValue(7U, 1U).to_string() << "]\n";
    cout << "Black rook:   [" << retriever.getChessCellBitValue(0U, 0U).to_string() << "]\n";
    cout << "Black rook:   [" << retriever.getChessCellBitValue(7U, 0U).to_string() << "]\n";
    cout << "Black knight: [" << retriever.getChessCellBitValue(1U, 0U).to_string() << "]\n";
    cout << "Black knight: [" << retriever.getChessCellBitValue(6U, 0U).to_string() << "]\n";
    cout << "Black bishop: [" << retriever.getChessCellBitValue(2U, 0U).to_string() << "]\n";
    cout << "Black bishop: [" << retriever.getChessCellBitValue(5U, 0U).to_string() << "]\n";
    cout << "Black queen:  [" << retriever.getChessCellBitValue(3U, 0U).to_string() << "]\n";
    cout << "Black king:   [" << retriever.getChessCellBitValue(4U, 0U).to_string() << "]\n";
}

unsigned int getLabelBasedOnSetOfPieces(SetOfPieces const& setOfPieces) {
    unsigned int result(0U);
    for (PieceColorAndType const piece : setOfPieces) {
        result += static_cast<unsigned int>(piece) * 13U;
    }
    return result;
}

uint32_t getLabelColor(unsigned int const label) {
    unsigned int digits = getNumberOfBase10Digits(label);
    double newValue = (static_cast<double>(1) / label) * pow(10, digits + 8);
    return static_cast<uint32_t>(newValue) % 0xFFFFFF;
}

uint32_t getLabelColor(SetOfPieces const& setOfPieces) {
    return getLabelColor(getLabelBasedOnSetOfPieces(setOfPieces));
}

}  // namespace

TEST(AnalyzePieceRetrieverTest, DISABLED_CheckChessBitValue_ForChessDotComVersus) {
    AlbaLocalPathHandler inputFile(APRG_DIR
                                   R"(\Chess\ChessPeek\Files\RetrieverBasis\ChessDotComVersus\ChessDotComVersus.bmp)");

    ChessPeekConfiguration configuration(ChessPeekConfigurationType::ChessDotComVersus);
    Bitmap inputBitmap(inputFile.getFullPath());
    BitmapSnippet inputSnippet(inputBitmap.getSnippetReadFromFile(
        convertToBitmapXY(configuration.getTopLeftOfBoard()),
        convertToBitmapXY(configuration.getBottomRightOfBoard())));
    ChessPieceRetriever retriever(configuration, inputSnippet);

    printChessBitValuesWithBlackUpWhiteDown(retriever);
}

TEST(AnalyzePieceRetrieverTest, DISABLED_CheckChessBitValue_ForChessDotComPuzzle) {
    AlbaLocalPathHandler inputFile(APRG_DIR
                                   R"(\Chess\ChessPeek\Files\RetrieverBasis\ChessDotComPuzzle\ChessDotComPuzzle.bmp)");

    ChessPeekConfiguration configuration(ChessPeekConfigurationType::ChessDotComPuzzle);
    Bitmap inputBitmap(inputFile.getFullPath());
    BitmapSnippet inputSnippet(inputBitmap.getSnippetReadFromFile(
        convertToBitmapXY(configuration.getTopLeftOfBoard()),
        convertToBitmapXY(configuration.getBottomRightOfBoard())));
    ChessPieceRetriever retriever(configuration, inputSnippet);

    printChessBitValuesWithBlackUpWhiteDown(retriever);
}

TEST(AnalyzePieceRetrieverTest, DISABLED_CheckChessBitValue_ForLichessVersus) {
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\LichessVersus\LichessVersus.bmp)");

    ChessPeekConfiguration configuration(ChessPeekConfigurationType::LichessVersus);
    Bitmap inputBitmap(inputFile.getFullPath());
    BitmapSnippet inputSnippet(inputBitmap.getSnippetReadFromFile(
        convertToBitmapXY(configuration.getTopLeftOfBoard()),
        convertToBitmapXY(configuration.getBottomRightOfBoard())));
    ChessPieceRetriever retriever(configuration, inputSnippet);

    printChessBitValuesWithBlackUpWhiteDown(retriever);
}

TEST(AnalyzePieceRetrieverTest, DISABLED_CheckChessBitValue_LichessStream) {
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\LichessStream\LichessStream.bmp)");

    ChessPeekConfiguration configuration(ChessPeekConfigurationType::LichessStream);
    Bitmap inputBitmap(inputFile.getFullPath());
    BitmapSnippet inputSnippet(inputBitmap.getSnippetReadFromFile(
        convertToBitmapXY(configuration.getTopLeftOfBoard()),
        convertToBitmapXY(configuration.getBottomRightOfBoard())));
    ChessPieceRetriever retriever(configuration, inputSnippet);

    printChessBitValuesWithBlackUpWhiteDown(retriever);
}

TEST(AnalyzePieceRetrieverTest, DISABLED_FindImportantPoints_ForChessDotComVersus) {
    AlbaLocalPathHandler inputFile(APRG_DIR
                                   R"(\Chess\ChessPeek\Files\RetrieverBasis\ChessDotComVersus\ChessDotComVersus.bmp)");
    AlbaLocalPathHandler outputFileForWhite(APRG_DIR
                                            R"(\Chess\ChessPeek\Files\RetrieverBasis\ChessDotComVersus\White.bmp)");
    AlbaLocalPathHandler outputFileForBlack(APRG_DIR
                                            R"(\Chess\ChessPeek\Files\RetrieverBasis\ChessDotComVersus\Black.bmp)");
    AlbaLocalPathHandler blankFile(APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\Blank.bmp)");
    blankFile.copyToNewFile(outputFileForWhite.getFullPath());
    blankFile.copyToNewFile(outputFileForBlack.getFullPath());

    ChessPeekConfiguration configuration(ChessPeekConfigurationType::ChessDotComVersus);
    Bitmap inputBitmap(inputFile.getFullPath());
    Bitmap outputBitmapForWhite(outputFileForWhite.getFullPath());
    Bitmap outputBitmapForBlack(outputFileForBlack.getFullPath());
    BitmapSnippet inputSnippet(inputBitmap.getSnippetReadFromFile(
        convertToBitmapXY(configuration.getTopLeftOfBoard()),
        convertToBitmapXY(configuration.getBottomRightOfBoard())));
    BitmapSnippet outputSnippetForWhite(outputBitmapForWhite.getSnippetReadFromFileWholeBitmap());
    BitmapSnippet outputSnippetForBlack(outputBitmapForBlack.getSnippetReadFromFileWholeBitmap());
    ChessPieceRetriever retriever(configuration, inputSnippet);
    PointToSetOfPiecesMap whitePointsToUniquePiecesMap;
    PointToSetOfPiecesMap blackPointsToUniquePiecesMap;
    XY deltaChessBoard = configuration.getBottomRightOfBoard() - configuration.getTopLeftOfBoard();

    checkChessCellsForWhiteAndBlackPointsBlackUpWhiteDown(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet);

    writeBottomRightBorder(outputSnippetForWhite, deltaChessBoard);
    writeBottomRightBorder(outputSnippetForBlack, deltaChessBoard);
    for (auto const& whitePointsAndUniquePiecesPair : whitePointsToUniquePiecesMap) {
        outputSnippetForWhite.setPixelAt(
            convertToBitmapXY(whitePointsAndUniquePiecesPair.first),
            getLabelColor(whitePointsAndUniquePiecesPair.second));
    }
    for (auto const& blackPointsAndUniquePiecesPair : blackPointsToUniquePiecesMap) {
        outputSnippetForBlack.setPixelAt(
            convertToBitmapXY(blackPointsAndUniquePiecesPair.first),
            getLabelColor(blackPointsAndUniquePiecesPair.second));
    }

    outputBitmapForWhite.setSnippetWriteToFile(outputSnippetForWhite);
    outputBitmapForBlack.setSnippetWriteToFile(outputSnippetForBlack);
}

TEST(AnalyzePieceRetrieverTest, DISABLED_FindImportantPoints_ForChessDotComPuzzle) {
    AlbaLocalPathHandler inputFile(APRG_DIR
                                   R"(\Chess\ChessPeek\Files\RetrieverBasis\ChessDotComPuzzle\ChessDotComPuzzle.bmp)");
    AlbaLocalPathHandler outputFileForWhite(APRG_DIR
                                            R"(\Chess\ChessPeek\Files\RetrieverBasis\ChessDotComPuzzle\White.bmp)");
    AlbaLocalPathHandler outputFileForBlack(APRG_DIR
                                            R"(\Chess\ChessPeek\Files\RetrieverBasis\ChessDotComPuzzle\Black.bmp)");
    AlbaLocalPathHandler blankFile(APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\Blank.bmp)");
    blankFile.copyToNewFile(outputFileForWhite.getFullPath());
    blankFile.copyToNewFile(outputFileForBlack.getFullPath());

    ChessPeekConfiguration configuration(ChessPeekConfigurationType::ChessDotComPuzzle);
    Bitmap inputBitmap(inputFile.getFullPath());
    Bitmap outputBitmapForWhite(outputFileForWhite.getFullPath());
    Bitmap outputBitmapForBlack(outputFileForBlack.getFullPath());
    BitmapSnippet inputSnippet(inputBitmap.getSnippetReadFromFile(
        convertToBitmapXY(configuration.getTopLeftOfBoard()),
        convertToBitmapXY(configuration.getBottomRightOfBoard())));
    BitmapSnippet outputSnippetForWhite(outputBitmapForWhite.getSnippetReadFromFileWholeBitmap());
    BitmapSnippet outputSnippetForBlack(outputBitmapForBlack.getSnippetReadFromFileWholeBitmap());
    ChessPieceRetriever retriever(configuration, inputSnippet);
    PointToSetOfPiecesMap whitePointsToUniquePiecesMap;
    PointToSetOfPiecesMap blackPointsToUniquePiecesMap;
    XY deltaChessBoard = configuration.getBottomRightOfBoard() - configuration.getTopLeftOfBoard();

    checkChessCellsForWhiteAndBlackPointsBlackUpWhiteDown(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet);

    writeBottomRightBorder(outputSnippetForWhite, deltaChessBoard);
    writeBottomRightBorder(outputSnippetForBlack, deltaChessBoard);
    for (auto const& whitePointsAndUniquePiecesPair : whitePointsToUniquePiecesMap) {
        outputSnippetForWhite.setPixelAt(
            convertToBitmapXY(whitePointsAndUniquePiecesPair.first),
            getLabelColor(whitePointsAndUniquePiecesPair.second));
    }
    for (auto const& blackPointsAndUniquePiecesPair : blackPointsToUniquePiecesMap) {
        outputSnippetForBlack.setPixelAt(
            convertToBitmapXY(blackPointsAndUniquePiecesPair.first),
            getLabelColor(blackPointsAndUniquePiecesPair.second));
    }

    outputBitmapForWhite.setSnippetWriteToFile(outputSnippetForWhite);
    outputBitmapForBlack.setSnippetWriteToFile(outputSnippetForBlack);
}

TEST(AnalyzePieceRetrieverTest, DISABLED_FindImportantPoints_ForLichessVersus) {
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\LichessVersus\LichessVersus.bmp)");
    AlbaLocalPathHandler outputFileForWhite(APRG_DIR
                                            R"(\Chess\ChessPeek\Files\RetrieverBasis\LichessVersus\White.bmp)");
    AlbaLocalPathHandler outputFileForBlack(APRG_DIR
                                            R"(\Chess\ChessPeek\Files\RetrieverBasis\LichessVersus\Black.bmp)");
    AlbaLocalPathHandler blankFile(APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\Blank.bmp)");
    blankFile.copyToNewFile(outputFileForWhite.getFullPath());
    blankFile.copyToNewFile(outputFileForBlack.getFullPath());

    ChessPeekConfiguration configuration(ChessPeekConfigurationType::LichessVersus);
    Bitmap inputBitmap(inputFile.getFullPath());
    Bitmap outputBitmapForWhite(outputFileForWhite.getFullPath());
    Bitmap outputBitmapForBlack(outputFileForBlack.getFullPath());
    BitmapSnippet inputSnippet(inputBitmap.getSnippetReadFromFile(
        convertToBitmapXY(configuration.getTopLeftOfBoard()),
        convertToBitmapXY(configuration.getBottomRightOfBoard())));
    BitmapSnippet outputSnippetForWhite(outputBitmapForWhite.getSnippetReadFromFileWholeBitmap());
    BitmapSnippet outputSnippetForBlack(outputBitmapForBlack.getSnippetReadFromFileWholeBitmap());
    ChessPieceRetriever retriever(configuration, inputSnippet);
    PointToSetOfPiecesMap whitePointsToUniquePiecesMap;
    PointToSetOfPiecesMap blackPointsToUniquePiecesMap;
    XY deltaChessBoard = configuration.getBottomRightOfBoard() - configuration.getTopLeftOfBoard();

    checkChessCellsForWhiteAndBlackPointsBlackUpWhiteDown(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet);

    writeBottomRightBorder(outputSnippetForWhite, deltaChessBoard);
    writeBottomRightBorder(outputSnippetForBlack, deltaChessBoard);
    for (auto const& whitePointsAndUniquePiecesPair : whitePointsToUniquePiecesMap) {
        outputSnippetForWhite.setPixelAt(
            convertToBitmapXY(whitePointsAndUniquePiecesPair.first),
            getLabelColor(whitePointsAndUniquePiecesPair.second));
    }
    for (auto const& blackPointsAndUniquePiecesPair : blackPointsToUniquePiecesMap) {
        outputSnippetForBlack.setPixelAt(
            convertToBitmapXY(blackPointsAndUniquePiecesPair.first),
            getLabelColor(blackPointsAndUniquePiecesPair.second));
    }

    outputBitmapForWhite.setSnippetWriteToFile(outputSnippetForWhite);
    outputBitmapForBlack.setSnippetWriteToFile(outputSnippetForBlack);
}

TEST(AnalyzePieceRetrieverTest, DISABLED_FindImportantPoints_ForLichessStream) {
    AlbaLocalPathHandler inputFile(APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\LichessStream\LichessStream.bmp)");
    AlbaLocalPathHandler outputFileForWhite(APRG_DIR
                                            R"(\Chess\ChessPeek\Files\RetrieverBasis\LichessStream\White.bmp)");
    AlbaLocalPathHandler outputFileForBlack(APRG_DIR
                                            R"(\Chess\ChessPeek\Files\RetrieverBasis\LichessStream\Black.bmp)");
    AlbaLocalPathHandler blankFile(APRG_DIR R"(\Chess\ChessPeek\Files\RetrieverBasis\Blank.bmp)");
    blankFile.copyToNewFile(outputFileForWhite.getFullPath());
    blankFile.copyToNewFile(outputFileForBlack.getFullPath());

    ChessPeekConfiguration configuration(ChessPeekConfigurationType::LichessVersus);
    Bitmap inputBitmap(inputFile.getFullPath());
    Bitmap outputBitmapForWhite(outputFileForWhite.getFullPath());
    Bitmap outputBitmapForBlack(outputFileForBlack.getFullPath());
    BitmapSnippet inputSnippet(inputBitmap.getSnippetReadFromFile(
        convertToBitmapXY(configuration.getTopLeftOfBoard()),
        convertToBitmapXY(configuration.getBottomRightOfBoard())));
    BitmapSnippet outputSnippetForWhite(outputBitmapForWhite.getSnippetReadFromFileWholeBitmap());
    BitmapSnippet outputSnippetForBlack(outputBitmapForBlack.getSnippetReadFromFileWholeBitmap());
    ChessPieceRetriever retriever(configuration, inputSnippet);
    PointToSetOfPiecesMap whitePointsToUniquePiecesMap;
    PointToSetOfPiecesMap blackPointsToUniquePiecesMap;
    XY deltaChessBoard = configuration.getBottomRightOfBoard() - configuration.getTopLeftOfBoard();

    checkChessCellsForWhiteAndBlackPointsBlackUpWhiteDown(
        whitePointsToUniquePiecesMap, blackPointsToUniquePiecesMap, retriever, inputSnippet);

    writeBottomRightBorder(outputSnippetForWhite, deltaChessBoard);
    writeBottomRightBorder(outputSnippetForBlack, deltaChessBoard);
    for (auto const& whitePointsAndUniquePiecesPair : whitePointsToUniquePiecesMap) {
        outputSnippetForWhite.setPixelAt(
            convertToBitmapXY(whitePointsAndUniquePiecesPair.first),
            getLabelColor(whitePointsAndUniquePiecesPair.second));
    }
    for (auto const& blackPointsAndUniquePiecesPair : blackPointsToUniquePiecesMap) {
        outputSnippetForBlack.setPixelAt(
            convertToBitmapXY(blackPointsAndUniquePiecesPair.first),
            getLabelColor(blackPointsAndUniquePiecesPair.second));
    }

    outputBitmapForWhite.setSnippetWriteToFile(outputSnippetForWhite);
    outputBitmapForBlack.setSnippetWriteToFile(outputSnippetForBlack);
}

}  // namespace chess

}  // namespace alba
