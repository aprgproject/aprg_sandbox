#include "AlbaSackReader.hpp"

#include <Common/File/AlbaFileReader.hpp>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

namespace alba {

AlbaSackReader::AlbaSackReader(string const& filePath) : m_inputPathHandler(filePath), m_fileEvaluator(string()) {}

AlbaSackReader::AlbaSackReader(string const& filePath, string const& fileCondition)
    : m_inputPathHandler(filePath), m_fileEvaluator(fileCondition) {}

AlbaSackReaderType AlbaSackReader::getType(string const& typeName) const {
    AlbaSackReaderType type;
    if (m_types.find(typeName) != m_types.end()) {
        type = m_types.at(typeName);
    }
    return type;
}

void AlbaSackReader::process() {
    if (m_inputPathHandler.isDirectory()) {
        processDirectory(m_inputPathHandler.getFullPath());
    } else {
        processFile(m_inputPathHandler.getFullPath());
    }
}

void AlbaSackReader::printAll() const {
    for (auto const& type : m_types) {
        cout << "Type:" << type.first << "\n";
        type.second.printAll();
        cout << "\n";
    }
}

void AlbaSackReader::processDirectory(string const& path) {
    set<string> listOfFiles;
    set<string> listOfDirectories;
    AlbaLocalPathHandler(path).findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectories);
    for (string const& filePath : listOfFiles) {
        processFile(filePath);
    }
}

void AlbaSackReader::processFile(string const& path) {
    AlbaLocalPathHandler filePathHandler(path);
    stringHelper::strings tokens;
    if (m_fileEvaluator.isInvalid() || m_fileEvaluator.evaluate(filePathHandler.getFile())) {
        cout << "ProcessFile: " << path << "\n";
        ifstream inputLogFileStream(filePathHandler.getFullPath());
        AlbaFileReader fileReader(inputLogFileStream);
        while (fileReader.isNotFinished()) {
            string line(fileReader.getLineAndIgnoreWhiteSpaces());
            tokenize(tokens, line);
        }
    }
    combineWords(tokens);
    combineArrayOperators(tokens);
    analyze(tokens);
}

string AlbaSackReader::getReaderStateString(ReaderState const state) {
#define GET_ENUM_STRING(en) \
    case en:                \
        return #en;

    switch (state) {
        GET_ENUM_STRING(ReaderState::LookingForInitialKeyword)
        GET_ENUM_STRING(ReaderState::ClassStateLookingForClassName)
        GET_ENUM_STRING(ReaderState::ClassStateLookingForOpeningBraceOrSemiColon)
        GET_ENUM_STRING(ReaderState::ClassStateLookingForParameters)
        GET_ENUM_STRING(ReaderState::TypedefStateLookingForTypeName)
        GET_ENUM_STRING(ReaderState::TypedefStateLookingForSecondType)
        GET_ENUM_STRING(ReaderState::TypedefStateLookingForSemicolon)
        GET_ENUM_STRING(ReaderState::TypedefStructStateLookingForNameOrOpeningBraceOrSecondType)
        GET_ENUM_STRING(ReaderState::TypedefStructStateLookingForParameters)
        GET_ENUM_STRING(ReaderState::TypedefStructStateLookingForSecondType)
        GET_ENUM_STRING(ReaderState::TypedefEnumStateLookingForOpeningBrace)
        GET_ENUM_STRING(ReaderState::TypedefEnumStateLookingForClosingBrace)
        GET_ENUM_STRING(ReaderState::TypedefEnumStateLookingForType)
    }
    return string();
#undef GET_ENUM_STRING
}

void AlbaSackReader::tokenize(stringHelper::strings& tokens, string const& line) {
    stringHelper::strings tokensInLine;
    stringHelper::splitToStrings<stringHelper::SplitStringType::WithDelimeters>(tokensInLine, line, " \t\n\r;{}[]");
    copy(tokensInLine.begin(), tokensInLine.end(), back_inserter(tokens));
}

void AlbaSackReader::combineWords(stringHelper::strings& tokens) {
    vector<string> tokensToCombine = {"unsigned char",   "signed char",        "unsigned int",     "signed int",
                                      "short int",       "unsigned short int", "signed short int", "long int",
                                      "signed long int", "unsigned long int",  "long double"};

    struct TokenAndIndex {
        unsigned int index;
        string token;
    };
    vector<TokenAndIndex> recentWords;
    for (unsigned int i = 0; i < tokens.size(); i++) {
        string token(tokens[i]);
        if (stringHelper::isIdentifier(token)) {
            TokenAndIndex tokenAndIndex{};
            tokenAndIndex.index = i;
            tokenAndIndex.token = token;
            recentWords.emplace_back(tokenAndIndex);
            int lastIndex = static_cast<int>(recentWords.size()) - 1;
            if (lastIndex >= 2) {
                string lastThreeWords = recentWords[lastIndex - 2].token + " " + recentWords[lastIndex - 1].token +
                                        " " + recentWords[lastIndex].token;
                if (tokensToCombine.end() !=
                    std::find(tokensToCombine.begin(), tokensToCombine.end(), lastThreeWords)) {
                    tokens.erase(
                        tokens.begin() + recentWords[lastIndex - 2].index,
                        tokens.begin() + recentWords[lastIndex].index + 1);
                    tokens.insert(tokens.begin() + recentWords[lastIndex - 2].index, lastThreeWords);
                    i = recentWords[lastIndex - 2].index;
                    recentWords.clear();
                    continue;
                }
            }
            if (lastIndex >= 1) {
                string lastTwoWords = recentWords[lastIndex - 1].token + " " + recentWords[lastIndex].token;
                if (tokensToCombine.end() != std::find(tokensToCombine.begin(), tokensToCombine.end(), lastTwoWords)) {
                    tokens.erase(
                        tokens.begin() + recentWords[lastIndex - 1].index,
                        tokens.begin() + recentWords[lastIndex].index + 1);
                    tokens.insert(tokens.begin() + recentWords[lastIndex - 1].index, lastTwoWords);
                    i = recentWords[lastIndex - 1].index;
                    recentWords.clear();
                    continue;
                }
            }
        } else if (!stringHelper::isWhiteSpace(token)) {
            recentWords.clear();
        }
    }
}

void AlbaSackReader::combineArrayOperators(stringHelper::strings& tokens) {
    unsigned int state = 0;
    unsigned int nonWhiteSpaceIndex = 0;
    unsigned int closingBracketIndex = 0;
    for (unsigned int i = 0; i < tokens.size(); i++) {
        string token(tokens[i]);
        if (0 == state) {
            if ('[' == token[0]) {
                state = 1;
            } else if (!stringHelper::isWhiteSpace(token)) {
                nonWhiteSpaceIndex = i;
            }
        } else if (1 == state) {
            if (']' == token[0]) {
                closingBracketIndex = i;
                string combinedArrayString = accumulate(
                    tokens.begin() + nonWhiteSpaceIndex, tokens.begin() + closingBracketIndex + 1, string(),
                    [&](string const& partialResult, string const& currentToken) {
                        string nextResult = partialResult;
                        if (!stringHelper::isWhiteSpace(currentToken)) {
                            nextResult += currentToken;
                        }
                        return nextResult;
                    });
                tokens.erase(tokens.begin() + nonWhiteSpaceIndex, tokens.begin() + closingBracketIndex + 1);
                tokens.insert(tokens.begin() + nonWhiteSpaceIndex, combinedArrayString);
                i = nonWhiteSpaceIndex;
                state = 0;
                continue;
            }
        }
    }
}

template <>
void AlbaSackReader::analyzeInReaderState<AlbaSackReader::ReaderState::LookingForInitialKeyword>(
    AlbaSackReader::ReaderTransactionData& transactionData, string const& token) {
    if ("struct" == token || "class" == token || "typedef" == token) {
        transactionData.typeName.clear();
        transactionData.firstIdentifier.clear();
        transactionData.secondIdentifier.clear();
        transactionData.type.clear();
    }
    if ("struct" == token || "class" == token) {
        transactionData.state = ReaderState::ClassStateLookingForClassName;
    } else if ("typedef" == token) {
        transactionData.state = ReaderState::TypedefStateLookingForTypeName;
    }
}

template <>
void AlbaSackReader::analyzeInReaderState<AlbaSackReader::ReaderState::ClassStateLookingForClassName>(
    AlbaSackReader::ReaderTransactionData& transactionData, string const& token) {
    if (stringHelper::isIdentifier(token)) {
        transactionData.typeName = token;
        transactionData.state = ReaderState::ClassStateLookingForOpeningBraceOrSemiColon;
    }
}

template <>
void AlbaSackReader::analyzeInReaderState<AlbaSackReader::ReaderState::ClassStateLookingForOpeningBraceOrSemiColon>(
    AlbaSackReader::ReaderTransactionData& transactionData, string const& token) {
    if (";" == token) {
        m_types[transactionData.typeName].copyContents(transactionData.type);
        transactionData.state = ReaderState::LookingForInitialKeyword;
    } else if ("{" == token) {
        transactionData.state = ReaderState::ClassStateLookingForParameters;
    }
}

template <>
void AlbaSackReader::analyzeInReaderState<AlbaSackReader::ReaderState::ClassStateLookingForParameters>(
    AlbaSackReader::ReaderTransactionData& transactionData, string const& token) {
    if (stringHelper::isIdentifier(token)) {
        transactionData.firstIdentifier = transactionData.secondIdentifier;
        transactionData.secondIdentifier = token;
    } else if (";" == token) {
        transactionData.type.addParameter(
            AlbaSackReaderParameter(transactionData.firstIdentifier, transactionData.secondIdentifier));
        transactionData.firstIdentifier.clear();
        transactionData.secondIdentifier.clear();
    } else if ("}" == token) {
        m_types[transactionData.typeName].copyContents(transactionData.type);
        transactionData.state = ReaderState::LookingForInitialKeyword;
    }
}

template <>
void AlbaSackReader::analyzeInReaderState<AlbaSackReader::ReaderState::TypedefStateLookingForTypeName>(
    AlbaSackReader::ReaderTransactionData& transactionData, string const& token) {
    if ("enum" == token) {
        transactionData.state = ReaderState::TypedefEnumStateLookingForOpeningBrace;
    } else if ("struct" == token) {
        transactionData.state = ReaderState::TypedefStructStateLookingForNameOrOpeningBraceOrSecondType;
    } else if ("union" == token) {
        transactionData.type.setAsUnion();
        transactionData.state = ReaderState::TypedefStructStateLookingForNameOrOpeningBraceOrSecondType;
    } else if (stringHelper::isIdentifier(token)) {
        transactionData.typeName = token;
        transactionData.state = ReaderState::TypedefStateLookingForSecondType;
    }
}

template <>
void AlbaSackReader::analyzeInReaderState<AlbaSackReader::ReaderState::TypedefStateLookingForSecondType>(
    AlbaSackReader::ReaderTransactionData& transactionData, string const& token) {
    if (stringHelper::isIdentifier(token)) {
        transactionData.firstIdentifier = token;
        transactionData.state = ReaderState::TypedefStateLookingForSemicolon;
    }
}

template <>
void AlbaSackReader::analyzeInReaderState<AlbaSackReader::ReaderState::TypedefStateLookingForSemicolon>(
    AlbaSackReader::ReaderTransactionData& transactionData, string const& token) {
    if (";" == token) {
        transactionData.type.addOtherTypeName(transactionData.firstIdentifier);
        m_types[transactionData.typeName].copyContents(transactionData.type);
        m_types[transactionData.firstIdentifier].addOtherTypeName(transactionData.typeName);
        transactionData.state = ReaderState::LookingForInitialKeyword;
    }
}

template <>
void AlbaSackReader::analyzeInReaderState<
    AlbaSackReader::ReaderState::TypedefStructStateLookingForNameOrOpeningBraceOrSecondType>(
    AlbaSackReader::ReaderTransactionData& transactionData, string const& token) {
    if ("{" == token) {
        transactionData.state = ReaderState::TypedefStructStateLookingForParameters;
    } else if (";" == token) {
        m_types[transactionData.typeName].copyContents(transactionData.type);
        transactionData.state = ReaderState::LookingForInitialKeyword;
    } else if (stringHelper::isIdentifier(token)) {
        transactionData.typeName = token;
    }
}

template <>
void AlbaSackReader::analyzeInReaderState<AlbaSackReader::ReaderState::TypedefStructStateLookingForParameters>(
    AlbaSackReader::ReaderTransactionData& transactionData, string const& token) {
    if (stringHelper::isIdentifier(token)) {
        transactionData.firstIdentifier = transactionData.secondIdentifier;
        transactionData.secondIdentifier = token;
    } else if (";" == token) {
        transactionData.type.addParameter(
            AlbaSackReaderParameter(transactionData.firstIdentifier, transactionData.secondIdentifier));
        transactionData.firstIdentifier.clear();
        transactionData.secondIdentifier.clear();
    } else if ("}" == token) {
        transactionData.state = ReaderState::TypedefStructStateLookingForSecondType;
    }
}

template <>
void AlbaSackReader::analyzeInReaderState<AlbaSackReader::ReaderState::TypedefStructStateLookingForSecondType>(
    AlbaSackReader::ReaderTransactionData& transactionData, string const& token) {
    if (stringHelper::isIdentifier(token)) {
        transactionData.typeName = token;
    } else if (";" == token) {
        m_types[transactionData.typeName].copyContents(transactionData.type);
        transactionData.state = ReaderState::LookingForInitialKeyword;
    }
}

template <>
void AlbaSackReader::analyzeInReaderState<AlbaSackReader::ReaderState::TypedefEnumStateLookingForOpeningBrace>(
    AlbaSackReader::ReaderTransactionData& transactionData, string const& token) {
    if ("{" == token) {
        transactionData.state = ReaderState::TypedefEnumStateLookingForClosingBrace;
    }
}

template <>
void AlbaSackReader::analyzeInReaderState<AlbaSackReader::ReaderState::TypedefEnumStateLookingForClosingBrace>(
    AlbaSackReader::ReaderTransactionData& transactionData, string const& token) {
    if ("}" == token) {
        transactionData.state = ReaderState::TypedefEnumStateLookingForType;
    }
}

template <>
void AlbaSackReader::analyzeInReaderState<AlbaSackReader::ReaderState::TypedefEnumStateLookingForType>(
    AlbaSackReader::ReaderTransactionData& transactionData, string const& token) {
    if (stringHelper::isIdentifier(token)) {
        m_types[token].copyContents(transactionData.type);
        transactionData.state = ReaderState::LookingForInitialKeyword;
    }
}

void AlbaSackReader::analyze(stringHelper::strings const& tokens) {
    ReaderTransactionData transactionData;
    transactionData.state = ReaderState::LookingForInitialKeyword;
    for (string const& token : tokens) {
        // cout<<"analyze -> state: "<<getReaderStateString(transactionData.state)<<"
        // typeName:["<<transactionData.typeName<<"] token:["<<token<<"]\n";

#define HANDLE_READER_STATE(en)                           \
    case en:                                              \
        analyzeInReaderState<en>(transactionData, token); \
        break;

        switch (transactionData.state) {
            HANDLE_READER_STATE(ReaderState::LookingForInitialKeyword)
            HANDLE_READER_STATE(ReaderState::ClassStateLookingForClassName)
            HANDLE_READER_STATE(ReaderState::ClassStateLookingForOpeningBraceOrSemiColon)
            HANDLE_READER_STATE(ReaderState::ClassStateLookingForParameters)
            HANDLE_READER_STATE(ReaderState::TypedefStateLookingForTypeName)
            HANDLE_READER_STATE(ReaderState::TypedefStateLookingForSecondType)
            HANDLE_READER_STATE(ReaderState::TypedefStateLookingForSemicolon)
            HANDLE_READER_STATE(ReaderState::TypedefStructStateLookingForNameOrOpeningBraceOrSecondType)
            HANDLE_READER_STATE(ReaderState::TypedefStructStateLookingForParameters)
            HANDLE_READER_STATE(ReaderState::TypedefStructStateLookingForSecondType)
            HANDLE_READER_STATE(ReaderState::TypedefEnumStateLookingForOpeningBrace)
            HANDLE_READER_STATE(ReaderState::TypedefEnumStateLookingForClosingBrace)
            HANDLE_READER_STATE(ReaderState::TypedefEnumStateLookingForType)
        }
#undef HANDLE_READER_STATE
    }
}

}  // namespace alba
