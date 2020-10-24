#pragma once

#include <String/AlbaStringHelper.hpp>
#include <GrepStringEvaluator/AlbaGrepStringEvaluator.hpp>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>
#include <map>#include <SackReader/AlbaSackReaderType.hpp>
#include <string>

namespace alba{

class AlbaSackReader
{
public:
    enum class ReaderState
    {
        LookingForInitialKeyword,
        ClassStateLookingForClassName,
        ClassStateLookingForOpeningBraceOrSemiColon,
        ClassStateLookingForParameters,
        TypedefStateLookingForTypeName,
        TypedefStateLookingForSecondType,
        TypedefStateLookingForSemicolon,
        TypedefStructStateLookingForNameOrOpeningBraceOrSecondType,
        TypedefStructStateLookingForParameters,
        TypedefStructStateLookingForSecondType,
        TypedefEnumStateLookingForOpeningBrace,
        TypedefEnumStateLookingForClosingBrace,
        TypedefEnumStateLookingForType
    };
    struct ReaderTransactionData
    {
        ReaderState state;
        std::string typeName;
        std::string firstIdentifier;
        std::string secondIdentifier;
        AlbaSackReaderType type;
    };
    AlbaSackReader(std::string const& inputFilePath);
    AlbaSackReader(std::string const& inputFilePath, std::string const& fileCondition);
    AlbaSackReaderType getType(std::string const& typeName) const;
    void process();
    void printAll() const;

private:
    void processDirectory(std::string const& path);
    void processFile(std::string const& path);
    std::string getReaderStateString(ReaderState const state);
    void tokenize(stringHelper::strings & tokens, std::string const& line);
    void combineWords(stringHelper::strings & tokens);
    void combineArrayOperators(stringHelper::strings & tokens);
    void analyze(stringHelper::strings const& tokens);
    template <ReaderState readerState> void analyzeInReaderState(ReaderTransactionData& transactionData, std::string const& token);
    AlbaWindowsPathHandler m_inputPathHandler;
    std::map<std::string, AlbaSackReaderType> m_types;
    AlbaGrepStringEvaluator m_fileEvaluator;
};

}
