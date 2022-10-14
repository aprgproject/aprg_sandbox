#pragma once

#include "../Utilities.hpp"
#include "Findings/FindingsBuffer.hpp"
#include "Findings/FindingsToAdd.hpp"
#include "Loopers/Looper.hpp"

#include <Common/Container/AlbaOptional.hpp>

#include <string>
#include <unordered_map>
using std::string;

#define T(...) Term(__VA_ARGS__)#define TC(...) TermChecker(__VA_ARGS__)

//#define DBGFLAG 2
#if DBGFLAG == 3
    #define DBGPRINT1(...) cout<<__VA_ARGS__<<endl;
    #define DBGPRINT2(...) cout<<__VA_ARGS__<<endl;
    #define DBGPRINT3(...) cout<<__VA_ARGS__<<endl;
#elif DBGFLAG == 2
    #define DBGPRINT1(...) cout<<__VA_ARGS__<<endl;
    #define DBGPRINT2(...) cout<<__VA_ARGS__<<endl;
    #define DBGPRINT3(...)
#elif DBGFLAG == 1
    #define DBGPRINT1(...) cout<<__VA_ARGS__<<endl;
    #define DBGPRINT2(...)
    #define DBGPRINT3(...)
#else
    #define DBGPRINT1(...)
    #define DBGPRINT2(...)
    #define DBGPRINT3(...)
#endif

namespace codeReview
{

enum class MoveBackType
{
    Empty,
    GotoPreviousModifiedTerm
    //Thinkharder
};

enum class LooperConnector
{
    None,
    WhiteSpaceAndNewLine
};

class CPlusPlusDatabase;
class Findings;
class SailIt;
class CPlusPlusMacro;
class CPlusPlusFunction;
class CPlusPlusFunctionSignature;

class TermAnalyzer
{
    typedef unordered_map<int, VectorOfTerms> MapOfMacroUsageParameters;
    typedef unordered_map<string, CPlusPlusType> MapOfCPlusPlusTypesForTypedef;

public:
    explicit TermAnalyzer(DequeOfTerms& terms,  CPlusPlusDatabase& database, Findings& findings);
    explicit TermAnalyzer(DequeOfTerms& terms,  CPlusPlusDatabase& database, Findings& findings, SailIt& sailIt);
    void setFileName(string const& directory, string const& fileName);
    void analyze();

private:
    void analyzeThisScope(Looper const& startLooper);

    //Macros
    bool isModifiedDueToMacros(Looper const& startLooper);
    bool isModifiedDueToIncludeMacroWithAngleBrackets(Looper const& startLooper);
    bool isModifiedDueToIncludeMacroWithConstantString(Looper const& startLooper);
    bool isModifiedDueToDefineMacro(Looper const& startLooper);
    bool isModifiedDueToDefineMacroWithParameters(Looper const& startLooper, Looper const& afterIdentifierLooper, string const& macroName);
    bool isModifiedDueToDefineMacroWithNoParameters(Looper const& startLooper, Looper const& equivalentStartLooper, string const& macroName);
    bool isModifiedDueToUndefMacro(Looper const& startLooper);
    bool isModifiedDueToOtherMacros(Looper const& startLooper);
    void copyDatabaseOfIncludeFile(Looper const& startLooper, string const& includeFileName);
    bool isEndOfMacroFoundAndMoveLooper(Looper& movableLooper);
    bool hasTermsForMacro(Looper const& startLooper);
    void copyLooperSpanToVectorOfTermsForMacro(Looper const& startLooper, CPlusPlusMacro& cPlusPlusMacro);
    void checkMacroParameters(Looper const& startLooper, CPlusPlusMacro& cPlusPlusMacro);

    //Expressions
    void simplifyExpressions(Looper const& startLooper);
    void simplifyPrimitiveTypesForCurrentStatement(Looper const& startLooper);
    bool isModifiedDueToExpressions(Looper const& startLooper);
    bool isModifiedDueToScopeOperator(Looper const& startLooper);
    bool isModifiedDueToSuffixOperator(Looper const& startLooper);
    bool isModifiedDueToPeriodOperator(Looper const& startLooper);
    bool isModifiedDueToArrowOperator(Looper const& startLooper);
    bool isModifiedDueToFunctionCall(Looper const& startLooper);
    bool isModifiedDueToBracketOperator(Looper const& startLooper);
    bool isModifiedDueToRelationalPrefixOperator(Looper const& startLooper);
    bool isModifiedDueToIncrementDecrementPrefixOperator(Looper const& startLooper);
    bool isModifiedDueToIndirectionPrefixOperator(Looper const& startLooper);
    bool isModifiedDueToAddressOfPrefixOperator(Looper const& startLooper);
    bool isModifiedDueToPrefixOperator(Looper const& startLooper);
    bool isModifiedDueToBiDirectionalRelationalOperator(Looper const& startLooper);
    bool isModifiedDueToBiDirectionalOperator(Looper const& startLooper);
    bool isModifiedDueToParenthesesWithValue(Looper const& startLooper);
    bool isModifiedDueToTypeSimplification(Looper const& startLooper);
    bool isModifiedDueToMultipleTypes(Looper const& startLooper);
    bool isModifiedDueToTypeWithConstQualifier(Looper const& startLooper);
    bool isModifiedDueToTypeWithConstQualifierInvalidPosition(Looper const& startLooper);
    bool isModifiedDueToTypeWithDereferenceOperator(Looper const& startLooper);
    bool isModifiedDueToTypeWithPointerOperator(Looper const& startLooper);
    bool isModifiedDueToTypeWithExternKeyword(Looper const& startLooper);
    bool areTheTypesValidForCombination(CPlusPlusType const& type1, CPlusPlusType const& type2) const;

    //Statements
    bool isModifiedDueToStatements(Looper const& startLooper);
    bool isModifiedDueToVariableDeclaration(Looper const& startLooper);
    bool isModifiedDueToCStyleArrayDeclaration(Looper const& startLooper);
    bool isModifiedDueToAssignment(Looper const& startLooper);
    bool isModifiedDueToRValueCanBeALine(Looper const& startLooper);
    bool isModifiedDueToUsingNamespaceKeyword(Looper const& startLooper);
    bool isModifiedDueToTypeDefStatement(Looper const& startLooper);
    bool isModifiedDueToTypeDefWithNormalParameters(Looper const& startLooper, Looper const& nextLooper);
    bool isModifiedDueToTypeDefWithStructAndBracesCStyleStatement(Looper const& startLooper, Looper const& nextLooper);
    bool areVariableFoundForVariableDeclarationAndMoveLooper(Looper& movableLooper, VectorOfStrings& variableNames);
    bool areTypesFoundForTypedefThenFillAndMoveLooper(Looper& movableLooper, CPlusPlusType const& type, MapOfCPlusPlusTypesForTypedef& typeMap);

    //ControlStructures
    bool isModifiedDueToControlStructures(Looper const& startLooper);
    bool isModifiedDueToIfClauseAndMoveLooper(Looper const& startLooper);
    bool isModifiedDueToElseIfClauseAndMoveLooper(Looper const& startLooper);
    bool isModifiedDueToElseClauseAndMoveLooper(Looper const& startLooper);
    bool isModifiedDueToIfElseIfChainClause(Looper const& startLooper);
    bool isModifiedDueToIfElseChainStopClause(Looper const& startLooper);
    bool isModifiedDueToWhileLoopAndMoveLooper(Looper const& startLooper);
    template <class Container> bool isModifiedDueToOneConditionConstructAndMoveLooper(Looper const& startLooper, Container const& expectedTerms, TermType const newTermType);

    //Functions
    bool isModifiedDueToFunctions(Looper const& startLooper);
    bool isModifiedDueToFunctionDeclaration(Looper const& startLooper);
    bool isModifiedDueToFunctionDefinition(Looper const& startLooper);
    void fillFunctionSignatureFromFunctionDeclaration(Looper const& startLooper, CPlusPlusFunctionSignature& cPlusPlusFunctionSignature);
    void fillFunctionSignatureFromFunctionCall(Looper const& startLooper, CPlusPlusFunctionSignature& cPlusPlusFunctionSignature);

    //Classes
    bool isModifiedDueToClasses(Looper const& startLooper);
    bool isModifiedDueToClassDeclaration(Looper const& startLooper);
    bool isModifiedDueToClassDefinition(Looper const& startLooper);
    bool isModifiedDueToCStyleStructDefinition(Looper const& startLooper);
    bool isModifiedDueToCStyleStructArrayDefinition(Looper const& startLooper);

    //Namespaces
    bool isModifiedDueToNamespaces(Looper const& startLooper);
    bool isModifiedDueToNamespaceDefinition(Looper const& startLooper);
    bool isModifiedDueToExternBlock(Looper const& startLooper);

    //SharedSimplifiers
    void checkCondition(Looper const& startLooper);
    bool isClosingPartnerFoundAndMoveLooper(Looper& movableLooper, string const& openingOperator, string const& closingOperator);
    template <LooperConnector looperConnector> void connectLooper(Looper&);

    //Modifiers
    bool isModifiedDueToUpdatedIdentifiers(Looper const& startLooper, LooperIndex& previousUpdatedIndexForMacro, LooperIndex& previousUpdatedIndexForOthers);
    void combineToASingleTerm(Looper const& startLooper, Looper const& endLooper, TermType const termType);
    void combineToASingleTermWithValueType(Looper const& startLooper, Looper const& endLooper, TermType const termType, CPlusPlusType const& valueType);
    void replaceLooperContentsWithASingleTerm(Looper const& startLooper, Looper const& endLooper, Term const& term);
    void eraseTermAndSetModifiedFlag(Looper const& eraseLooper);
    void eraseTermsAndSetModifiedFlag(Looper const& eraseLooper);
    void replaceTermWithMacroEquivalent(Looper const& replaceLooper, CPlusPlusMacro& cPlusPlusMacro);
    void replaceTermWithMacroEquivalent(Looper const& eraseLooper, Looper const& parameterLooper, CPlusPlusMacro& cPlusPlusMacro);
    void checkMacroUsageParameters(Looper const& parameterLooper, CPlusPlusMacro& cPlusPlusMacro, MapOfMacroUsageParameters& macroUsageParameters);
    void clearFlagsForAnotherIteration();

    //TemplateFunctions
    template<LooperConnector looperConnector, class Container> bool isSingleLineComparisonSatisfiedThenMoveLooper(Looper& movableLooper, Container const& expectedTerms);
    template<LooperConnector looperConnector, class Container> bool isMultiLineComparisonSatisfiedThenMoveLooper(Looper& movableLooper, Container const& expectedTerms);
    template<typename ExpectedTermsIteratorType> bool isTheMismatchWithWhiteSpaceAndMoveLooper(Looper& movableLooper, ExpectedTermsIteratorType& itExpected);
    template<typename ExpectedTermsIteratorType> bool isTheMismatchWithNewLineAndMoveLooper(Looper& movableLooper, ExpectedTermsIteratorType& itExpected);
    template<typename ExpectedTermsIteratorType> bool isTheMismatchWithIgnorableTermAndMoveLooper(Looper& movableLooper, ExpectedTermsIteratorType& itExpected);
    template <LooperConnector looperConnector> bool isBothBracketsFoundAndMoveLoopers(Looper const& startLooper, Looper& afterOpeningBracket, Looper& afterClosingBracket);
    template <LooperConnector looperConnector> bool isBothParenthesesFoundAndMoveLoopers(Looper const& startLooper, Looper& afterOpeningParenthesis, Looper& afterClosingParenthesis);
    template <LooperConnector looperConnector> bool isBothAngleBracketsFoundAndMoveLoopers(Looper const& startLooper, Looper& afterOpeningParenthesis, Looper& afterClosingParenthesis);
    template <LooperConnector looperConnector> bool isBothBracesFoundAndMoveLoopers(Looper const& startLooper, Looper& afterOpeningBraces, Looper& afterClosingBraces);
    template <LooperConnector looperConnector> bool isBothBracesFoundWithSemicolonAndMoveLoopers(Looper const& startLooper, Looper& afterOpeningBraces, Looper& afterClosingBraces, Looper& afterSemiColon);
    template <LooperConnector looperConnector> bool isSemiColonFoundAndMoveLooper(Looper& afterSemiColon);
    template<class Container> VectorOfTerms getTerms(Looper const& startLooper, Container const& expectedTerms);
    template <FindingsToAdd findingsToAdd> void incrementLooperIfWhiteSpaceForMacro(Looper& movableLooper);
    template <FindingsToAdd findingsToAdd> void incrementLooperIfWhiteSpaceAndOneNewLine(Looper& movableLooper);
    template <FindingsToAdd findingsToAdd> void incrementLooperIfWhiteSpaceAndNewLine(Looper& movableLooper);
    template <FindingsToAdd findingsToAdd> void decrementLooperIfWhiteSpaceAndNewLine(Looper& movableLooper);

    //Findings
    void addFinding(string const& fileLocator, string const& content, Looper const& findingLooper);
    template <FindingsToAdd findingsToAdd> void addFindingsForExpectedNewLineIfNeeded(Looper const&);
    template <FindingsToAdd findingsToAdd> void addFindingsForUnexpectedWhiteSpaceIfNeeded(Looper const&);
    template <FindingsToAdd findingsToAdd> void addFindingsForUnexpectedNewLineIfNeeded(Looper const&);

    bool isModifiedDueToCStyleStruct(Looper const& startLooper);
    bool isSingleLineOrMultiLineComment(Looper const& startLooper);
    bool isUnexpectedWhiteSpace(Looper const& startLooper);
    bool isUnexpectedNewLine(Looper const& startLooper);
    void addFindingForUnprocessedFirstTerm(Looper const& startLooper);
    void updateAfterOneIteration(Looper& movableLooper, LooperIndex& previousModifiedIndex);
    bool isStringFoundInLooper(Looper const& startLooper, string const& stringToCompare);
    bool isStringFoundInMacro(string const& macroName, string const& stringToCompare);
    void moveLooperToPreviousModifiedIndex(Looper& movableLooper, LooperIndex const previousModifiedIndex);
    string getLocatorString(Looper const& startLooper);
    string accumulateLooperContentsToString(Looper const& startLooper);
    string accumulateLooperContentsToPrintableString(Looper const& startLooper);

    DequeOfTerms& m_terms;
    CPlusPlusDatabase& m_database;
    Findings& m_findings;
    FindingsBuffer m_findingsBuffer;
    alba::AlbaOptional <SailIt&> m_optionalSailIt;
    bool m_isTermsModified;
    ModifyDetails m_modifyDetails;
    MoveBackType m_moveBackType;
    string m_baseDirectory;
    string m_fileName;
    unsigned int m_uniqueFileId;
};

}// namespace codeReview
