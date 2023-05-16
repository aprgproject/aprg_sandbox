#include <ChessPeek/Book.hpp>
#include <ChessPeek/DatabaseDefinitions.hpp>
#include <ChessPeek/DetailsFromTheScreen.hpp>
#include <ChessUtilities/Board/Board.hpp>
#include <ChessUtilities/Board/BoardUtilities.hpp>
#include <ChessUtilities/Board/StreamOperators.hpp>
#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/PathHandler/AlbaWebPathHandler.hpp>
#include <Common/Print/AlbaPrintFunctions.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <ScreenMonitoring/AlbaLocalScreenMonitoring.hpp>
#include <UserAutomation/AlbaLocalUserAutomation.hpp>

#include <gtest/gtest.h>

#include <algorithm>
#include <ostream>
#include <thread>
#include <vector>

using namespace alba::stringHelper;
using namespace std;

namespace {
bool shouldStillRun = true;
}

namespace alba {

namespace chess {

namespace ChessPeek {

void trackKeyPressForDownloadMovesFromChessDotCom() {
    AlbaLocalUserAutomation userAutomation;
    while (shouldStillRun) {
        shouldStillRun = !userAutomation.isKeyPressed(VK_NUMLOCK);
        userAutomation.sleep(100);
    }
}

struct Paths {
    string url;
    string htmlFile;
    string dataFile;
    string linesFile;
    string lineNumberFile;
};

struct MoveInfo {
    string nextMove;
    string numberOfGames;
    string whiteWinPercentage;
    string drawPercentage;
    string blackWinPercentage;
};

using MoveInfos = std::vector<MoveInfo>;

struct WebPageInfo {
    string nameOfLine;
    MoveInfos moveInfos;
};

string getOneCharPiece(string const& pieceName) {
    string result;
    if ("knight" == pieceName) {
        result = "N";
    } else if ("bishop" == pieceName) {
        result = "B";
    } else if ("rook" == pieceName) {
        result = "R";
    } else if ("queen" == pieceName) {
        result = "Q";
    } else if ("king" == pieceName) {
        result = "K";
    }
    return result;
}

void clickWindow() {
    AlbaLocalUserAutomation userAutomation;
    userAutomation.doLeftClickAt(MousePosition(3750, 550));
}

void gotoWebPage(string const& url) {
    AlbaLocalUserAutomation userAutomation;
    userAutomation.pressKey(VK_CONTROL);
    userAutomation.pressKey('L');
    userAutomation.sleepWithRealisticDelay();

    userAutomation.releaseKey(VK_CONTROL);
    userAutomation.releaseKey('L');
    userAutomation.sleepWithRealisticDelay();

    userAutomation.setStringToClipboard(url);
    userAutomation.sleepWithRealisticDelay();

    userAutomation.pressKey(VK_CONTROL);
    userAutomation.pressKey('V');
    userAutomation.sleepWithRealisticDelay();

    userAutomation.releaseKey(VK_CONTROL);
    userAutomation.releaseKey('V');
    userAutomation.sleepWithRealisticDelay();

    userAutomation.typeKey(VK_RETURN);
    userAutomation.sleep(500);
}

bool performMovesAndReturnIfValid(strings const& line) {
    Configuration configuration(Configuration::Type::ChessDotComExplorer);
    DetailsFromTheScreen detailsFromScreen(configuration);
    AlbaLocalUserAutomation userAutomation;

    MousePosition topLeft(2245, 101);
    MousePosition bottomRight(3124, 980);
    Board updatedBoard(BoardOrientation::BlackUpWhiteDown);
    PieceColor currentColor = PieceColor::White;
    double deltaX = (bottomRight.getX() - topLeft.getX()) / 8;
    double deltaY = (bottomRight.getY() - topLeft.getY()) / 8;
    for (string const& moveString : line) {
        if (!shouldStillRun) {
            exit(0);
        }
        Move move = updatedBoard.getMoveUsingAlgebraicNotation(moveString, currentColor);
        if (areCoordinatesValid(move)) {
            int startX = round(topLeft.getX() + (move.first.getX() + 0.5) * deltaX);
            int startY = round(topLeft.getY() + (move.first.getY() + 0.5) * deltaY);
            int endX = round(topLeft.getX() + (move.second.getX() + 0.5) * deltaX);
            int endY = round(topLeft.getY() + (move.second.getY() + 0.5) * deltaY);

            userAutomation.setMousePosition(MousePosition(startX, startY));
            userAutomation.pressLeftButtonOnMouse();
            userAutomation.sleep(200);
            userAutomation.setMousePosition(MousePosition(endX, endY));
            userAutomation.sleep(200);
            userAutomation.releaseLeftButtonOnMouse();
            userAutomation.sleep(600);

            updatedBoard.move(move);
            currentColor = getOppositeColor(currentColor);

            detailsFromScreen.saveDetailsFromTheScreen();
            Board const& boardFromScreen(detailsFromScreen.getBoardWithContext().getBoard());
            if (boardFromScreen != updatedBoard) {
                cout << "Move does not match on the screen. Move: [" << moveString;
                cout << "] translated to: [" << move << "]" << endl;
                cout << "Expected board:" << endl;
                cout << updatedBoard << endl;
                cout << "Board on the screen:" << endl;
                cout << boardFromScreen << endl;
                return false;
            }
        } else {
            cout << "Invalid move found: [" << moveString;
            cout << "] translated to: [" << move << "]" << endl;
            return false;
        }
    }

    return true;
}

void deleteWebPageUntilItsDeleted(string const& htmlFile) {
    AlbaLocalPathHandler htmlFileHandler(htmlFile);
    while (htmlFileHandler.isFoundInLocalSystem()) {
        if (!shouldStillRun) {
            exit(0);
        }
        htmlFileHandler.deleteFile();
        Sleep(100);
        htmlFileHandler.reInput();
        if (htmlFileHandler.isFoundInLocalSystem()) {
            cout << "File still not deleted. Deleting again. File: [" << htmlFile << "]" << endl;
        }
    }
}

void saveWebPage(string const& htmlFile) {
    AlbaLocalUserAutomation userAutomation;
    userAutomation.pressKey(VK_CONTROL);
    userAutomation.pressKey('S');
    userAutomation.sleepWithRealisticDelay();

    userAutomation.releaseKey(VK_CONTROL);
    userAutomation.releaseKey('S');
    userAutomation.sleepWithRealisticDelay();

    userAutomation.setStringToClipboard(htmlFile);
    userAutomation.sleep(500);

    userAutomation.pressKey(VK_CONTROL);
    userAutomation.pressKey('V');
    userAutomation.sleepWithRealisticDelay();

    userAutomation.releaseKey(VK_CONTROL);
    userAutomation.releaseKey('V');
    userAutomation.sleepWithRealisticDelay();

    userAutomation.typeKey(VK_RETURN);
}

void typeEnter() {
    AlbaLocalUserAutomation userAutomation;
    userAutomation.typeKey(VK_RETURN);
}

void saveWebPageUntilItsDeleted(string const& htmlFile) {
    AlbaLocalPathHandler htmlFileHandler(htmlFile);
    while (!htmlFileHandler.isFoundInLocalSystem()) {
        if (!shouldStillRun) {
            exit(0);
        }
        saveWebPage(htmlFile);
        clickWindow();
        typeEnter();
        Sleep(500);
        htmlFileHandler.reInput();
        if (!htmlFileHandler.isFoundInLocalSystem()) {
            cout << "File still doesnt exist. Saving web page again. File: [" << htmlFile << "]" << endl;
        }
    }
}

void clickReset() {
    AlbaLocalUserAutomation userAutomation;
    userAutomation.doLeftClickAt(MousePosition(3426, 952));
}

string getStringInBetween(string_view mainString, string_view firstString, string_view secondString, int& index) {
    string result{};
    int indexToStart = index;
    int firstIndexOfFirstString = mainString.find(firstString, indexToStart);
    if (isNotNpos(firstIndexOfFirstString)) {
        int lastIndexOfFirstString = firstIndexOfFirstString + firstString.length();
        int firstIndexOfSecondString = mainString.find(secondString, lastIndexOfFirstString);
        if (isNotNpos(firstIndexOfSecondString)) {
            result = mainString.substr(lastIndexOfFirstString, firstIndexOfSecondString - lastIndexOfFirstString);
            index = firstIndexOfSecondString + secondString.length();
        }
    }
    return result;
}

string getStringInBetween(string_view mainString, string_view firstString, string_view secondString) {
    int tempIndex = 0;
    return getStringInBetween(mainString, firstString, secondString, tempIndex);
}

string removeHtmlTags(string const& mainString) {
    string withoutTags;
    string withTags = mainString;
    int firstIndexOfFirstString = withTags.find("<", 0);
    while (isNotNpos(firstIndexOfFirstString)) {
        if (!shouldStillRun) {
            exit(0);
        }
        int lastIndexOfFirstString = firstIndexOfFirstString + 1;
        int firstIndexOfSecondString = withTags.find(">", lastIndexOfFirstString);
        if (isNotNpos(firstIndexOfSecondString)) {
            int lastIndexOfSecondString = firstIndexOfSecondString + 1;
            withoutTags += withTags.substr(0, firstIndexOfFirstString);
            withTags = withTags.substr(lastIndexOfSecondString);
            firstIndexOfFirstString = withTags.find("<", 0);
        } else {
            break;
        }
    }
    return withoutTags + withTags;
}

bool readHtmlFileIfValid(WebPageInfo& pageInfo, string const& htmlFile) {
    bool result(false);
    ifstream inStream(htmlFile);
    AlbaFileReader fileReader(inStream);
    fileReader.setMaxBufferSize(100000);

    while (fileReader.isNotFinished()) {
        if (!shouldStillRun) {
            exit(0);
        }
        string line(fileReader.getLineAndIgnoreWhiteSpaces());
        int index = line.find(R"("eco-classifier-component sidebar-game-opening")");
        if (isNotNpos(index)) {
            result = true;
            int previousIndex{};
            pageInfo.nameOfLine =
                getStringInBetween(line, R"(<span class="eco-classifier-label"><!----> <span>)", R"(</span>)", index);
            do {
                if (!shouldStillRun) {
                    exit(0);
                }
                previousIndex = index;
                MoveInfo moveInfo{};
                moveInfo.nextMove = getStringInBetween(line, R"(<span class="move-san-san">)", R"(</span>)", index);
                if (moveInfo.nextMove.empty()) {
                    string prefix =
                        getStringInBetween(line, R"(<span class="move-san-figurine icon-font-chess )", R"(-)", index);
                    string suffix =
                        getStringInBetween(line, R"(<span class="move-san-afterfigurine">)", R"(</span>)", index);
                    moveInfo.nextMove = getOneCharPiece(prefix) + suffix;
                }
                moveInfo.numberOfGames = removeHtmlTags(
                    getStringInBetween(line, R"(<p class="suggested-moves-total-games">)", R"(</p>)", index));
                if (!moveInfo.numberOfGames.empty()) {
                    string moveList = getStringInBetween(
                        line, R"(<div class="suggested-moves-suggested-moves-list">)", R"(</div></li>)", index);
                    int moveListIndex = 0;
                    if (isStringFoundInsideTheOtherStringCaseSensitive(
                            moveList, R"("suggested-moves-suggested-white")")) {
                        moveInfo.whiteWinPercentage = getStringInBetween(
                            moveList, R"(<span class="suggested-moves-percent-label">)", R"(</span>)", moveListIndex);
                    }
                    if (isStringFoundInsideTheOtherStringCaseSensitive(
                            moveList, R"("suggested-moves-suggested-draw")")) {
                        moveInfo.drawPercentage = getStringInBetween(
                            moveList, R"(<span class="suggested-moves-percent-label">)", R"(</span>)", moveListIndex);
                    }
                    if (isStringFoundInsideTheOtherStringCaseSensitive(
                            moveList, R"("suggested-moves-suggested-black")")) {
                        moveInfo.blackWinPercentage = getStringInBetween(
                            moveList, R"(<span class="suggested-moves-percent-label">)", R"(</span>)", moveListIndex);
                    }
                } else {
                    moveInfo.numberOfGames = "1";
                    string moveList = getStringInBetween(
                        line, R"(<div class="suggested-moves-suggested-moves-list">)", R"(</div></li>)", index);
                    string oneMatch = getStringInBetween(
                        moveList, R"(<div class="suggested-moves-result suggested-moves-suggested-)", R"(</div>)");
                    if (oneMatch == R"(white">1-0)") {
                        moveInfo.whiteWinPercentage = "100%";
                    } else if (oneMatch == R"(black">0-1)") {
                        moveInfo.blackWinPercentage = "100%";
                    } else if (oneMatch == R"(draw">½-½)") {
                        moveInfo.drawPercentage = "100%";
                    }
                }

                if (!moveInfo.nextMove.empty()) {
                    pageInfo.moveInfos.emplace_back(moveInfo);
                }
            } while (previousIndex != index);
        }
    }
    return result;
}

void savePageInfoToDataFile(strings const& currentLine, string const& dataFile, WebPageInfo const& pageInfo) {
    ofstream outStream(dataFile, ofstream::app);
    outStream << "Line: [";
    for (string const& move : currentLine) {
        outStream << move << ",";
    }
    outStream << "]\n";
    outStream << "NameOfLine: [" << pageInfo.nameOfLine << "]\n";
    outStream << "NumberOfNextMoves: [" << pageInfo.moveInfos.size() << "]\n";
    for (MoveInfo const& moveInfo : pageInfo.moveInfos) {
        outStream << "NextMove: [" << moveInfo.nextMove << "]\n";
        outStream << "NumberOfGames: [" << moveInfo.numberOfGames << "]\n";
        outStream << "WhiteWinPercentage: [" << moveInfo.whiteWinPercentage << "]\n";
        outStream << "DrawPercentage: [" << moveInfo.drawPercentage << "]\n";
        outStream << "BlackWinPercentage: [" << moveInfo.blackWinPercentage << "]\n";
    }
    outStream.flush();
}

int getLineNumber(string const& lineNumberFile) {
    int result{};
    ifstream inStream(lineNumberFile);
    inStream >> result;
    return result;
}

void setLineNumber(string const& lineNumberFile, int const lineNumber) {
    ofstream outStream(lineNumberFile);
    outStream << lineNumber << "\n";
}

strings getLineOfMoves(string const& lineFile, int const lineNumber) {
    strings result;
    ifstream inStream(lineFile);
    AlbaFileReader fileReader(inStream);
    int i = 1;
    while (fileReader.isNotFinished()) {
        if (!shouldStillRun) {
            exit(0);
        }
        if (i < lineNumber) {
            fileReader.skipLine();
            i++;
        } else if (i == lineNumber) {
            string lineString = fileReader.getLineAndIgnoreWhiteSpaces();
            splitToStrings<SplitStringType::WithoutDelimeters>(result, lineString, ",");
            break;
        } else {
            break;
        }
    }
    return result;
}

void saveLine(ofstream& outStream, strings const& line) {
    ostream_iterator<string> outputIterator(outStream, ",");
    copy(line.cbegin(), line.cend(), outputIterator);
    outStream << "\n";
}

void saveNewLinesInPageInfoToLineFile(strings const& currentLine, string const& lineFile, WebPageInfo const& pageInfo) {
    ofstream outStream(lineFile, ofstream::app);
    strings newLine(currentLine);
    for (MoveInfo const& moveInfo : pageInfo.moveInfos) {
        newLine.emplace_back(moveInfo.nextMove);

        saveLine(outStream, newLine);

        newLine.pop_back();
    }
}

void saveSkippedLineAtTheEndOfLineFile(strings const& skippedLine, string const& lineFile) {
    ofstream outStream(lineFile, ofstream::app);
    saveLine(outStream, skippedLine);
}

bool shouldIncludeLine(strings const& currentLine, Book const& book) {
    // uncomment this once 4 moves are done
    /*bool result(false);
    constexpr int MIN_NUMBER_OF_GAMES = 10000;

    Board updatedBoard(BoardOrientation::BlackUpWhiteDown);
    PieceColor currentColor = PieceColor::White;
    int size = currentLine.size();
    int index{};
    for (string const& moveString : currentLine) {
        if (index != size - 1) {
            Move move = updatedBoard.getMoveUsingAlgebraicNotation(moveString, currentColor);
            if (areCoordinatesValid(move)) {
                updatedBoard.move(move);
                currentColor = getOppositeColor(currentColor);
            } else {
                cout << "Logic error. Not a valid move in [shouldIncludeLine()]. Move: [" << moveString;
                cout << "] translated to: [" << move << "]" << endl;
                cout << "Exiting." << endl;
                exit(0);
            }
        }
        index++;
    }
    auto lineDetailOptional = book.getLine(updatedBoard);
    if (lineDetailOptional) {
        auto const& lineDetail(lineDetailOptional.value());
        if (lineDetail.totalNumberOfGames > MIN_NUMBER_OF_GAMES) {
            result = true;
        } else {
            cout << "Skip this line because the number of games(" << lineDetail.totalNumberOfGames;
            cout << ") is less than the minimum(" << MIN_NUMBER_OF_GAMES << ")" << endl;
        }
    }
    return result;*/

    return true;
}

void doOnePage(strings const& currentLine, Paths const& paths) {
    WebPageInfo pageInfo;

    bool isProcessed(false);
    while (!isProcessed) {
        if (!shouldStillRun) {
            exit(0);
        }
        clickWindow();
        clickReset();
        isProcessed = performMovesAndReturnIfValid(currentLine);
        if (!isProcessed) {
            cout << "Problem in performing moves. Trying to do all the process again." << endl;
            continue;
        }
        deleteWebPageUntilItsDeleted(paths.htmlFile);
        saveWebPageUntilItsDeleted(paths.htmlFile);

        isProcessed = readHtmlFileIfValid(pageInfo, paths.htmlFile);
        if (!isProcessed) {
            cout << "File is not valid. Trying to do all the process again. File: [" << paths.htmlFile << "]" << endl;
        }
    }

    savePageInfoToDataFile(currentLine, paths.dataFile, pageInfo);
    saveNewLinesInPageInfoToLineFile(currentLine, paths.linesFile, pageInfo);
}

void doAllPagesRecursively(Paths const& paths) {
    thread trackKeyPressForDownloadMovesFromChessDotComThread(trackKeyPressForDownloadMovesFromChessDotCom);
    AlbaLocalPathHandler chessDotComBookDatabase(APRG_DIR CHESS_PEEK_CHESS_DOT_COM_BOOK_DATABASE);
    Book book;
    book.loadDatabaseFrom(chessDotComBookDatabase.getFullPath());

    clickWindow();
    gotoWebPage(paths.url);

    int lineNumber = getLineNumber(paths.lineNumberFile);
    strings currentLine = getLineOfMoves(paths.linesFile, lineNumber);
    while (shouldStillRun && !currentLine.empty()) {
        cout << "lineNumber: [" << lineNumber << "] currentLine:[";
        printParameter(cout, currentLine);
        cout << "]" << endl;

        if (shouldIncludeLine(currentLine, book)) {
            doOnePage(currentLine, paths);
        } else {
            cout << "Skipping line." << endl;
            saveSkippedLineAtTheEndOfLineFile(currentLine, paths.linesFile);
        }
        lineNumber++;
        setLineNumber(paths.lineNumberFile, lineNumber);
        currentLine = getLineOfMoves(paths.linesFile, lineNumber);
    }

    trackKeyPressForDownloadMovesFromChessDotComThread.join();
}

TEST(DownloadMovesFromChessDotComTest, DISABLED_DoAllPagesRecursivelyWorks) {
    // To reinitialize:
    // ChessDotComMoves should be deleted or empty
    // ChessDotComLines should be deleted or empty
    // ChessDotComLineNumber has to contain 0

    AlbaWebPathHandler explorerUrl(R"(https://www.chess.com/explorer)");
    AlbaLocalPathHandler tempHtmlFile(APRG_DIR R"(\Chess\ChessPeek\Files\ChessDotComAutomation\temp.html)");
    AlbaLocalPathHandler dataFile(APRG_DIR
                                  R"(\Chess\ChessPeek\Files\ChessDotComAutomation\ChessDotComDataFromSite.txt)");
    AlbaLocalPathHandler linesFile(APRG_DIR R"(\Chess\ChessPeek\Files\ChessDotComAutomation\ChessDotComLines.txt)");
    AlbaLocalPathHandler lineNumberFile(APRG_DIR
                                        R"(\Chess\ChessPeek\Files\ChessDotComAutomation\ChessDotComLineNumber.txt)");

    doAllPagesRecursively(Paths{
        explorerUrl.getFullPath(), tempHtmlFile.getFullPath(), dataFile.getFullPath(), linesFile.getFullPath(),
        lineNumberFile.getFullPath()});
}

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
