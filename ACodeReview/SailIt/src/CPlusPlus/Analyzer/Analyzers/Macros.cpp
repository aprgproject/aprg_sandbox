#include "../../../SailIt.hpp"
#include "../../Database/CPlusPlusDatabase.hpp"
#include "../../Term/TermChecker.hpp"
#include "../Findings/TemporaryFindings.hpp"
#include "../TermAnalyzer.hpp"
#include "../TermAnalyzerTemplateFunctions.hpp"

#include <array>
#include <iostream>

using namespace std;
using namespace alba::stringHelper;

namespace codeReview
{

bool TermAnalyzer::isModifiedDueToMacros(Looper const& startLooper)
{
    DBGPRINT1("isModifiedDueToMacros");
    bool isModified = true;
    if(isModifiedDueToIncludeMacroWithAngleBrackets(startLooper));
    else if(isModifiedDueToIncludeMacroWithConstantString(startLooper));
    else if(isModifiedDueToDefineMacro(startLooper));
    else if(isModifiedDueToUndefMacro(startLooper));
    else if(isModifiedDueToOtherMacros(startLooper));
    else
    {
        isModified = false;
    }
    return isModified;
}

bool TermAnalyzer::isModifiedDueToIncludeMacroWithAngleBrackets(Looper const& startLooper)
{
    DBGPRINT2("isModifiedDueToIncludeMacroWithAngleBrackets");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<Term, 2> const expectedTerms{T(TermType::Macro, "#include"), T(TermType::WhiteSpace)};
    if(isSingleLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, expectedTerms))
    {
        Looper afterOpeningAngleBracket(compareLooper);
        Looper afterClosingAngleBracket(compareLooper);
        if(isBothAngleBracketsFoundAndMoveLoopers<LooperConnector::WhiteSpaceAndNewLine>(compareLooper, afterOpeningAngleBracket, afterClosingAngleBracket))
        {
            string includeFileName(accumulateLooperContentsToString(Looper(afterOpeningAngleBracket, afterClosingAngleBracket-1)));
            incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::ExpectsNewLineAndUnexpectsWhiteSpace>(afterClosingAngleBracket);
            copyDatabaseOfIncludeFile(afterOpeningAngleBracket, includeFileName);
            m_database.addIncludeFile(includeFileName);
            temporaryFindings.copyCurrentFindings(m_findings);
            combineToASingleTerm(startLooper, afterClosingAngleBracket, TermType::ProcessedTerm);
            return true;
        }
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToIncludeMacroWithConstantString(Looper const& startLooper)
{
    DBGPRINT2("isModifiedDueToIncludeMacroWithConstantString");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<Term, 3> const expectedTerms{T(TermType::Macro, "#include"), T(TermType::WhiteSpace), T(TermType::Constant_String)};
    if(isSingleLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, expectedTerms))
    {
        VectorOfTerms terms(getTerms(startLooper, expectedTerms));
        string includeFileName(getStringWithoutQuotations(terms[2].getString()));
        incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::ExpectsNewLineAndUnexpectsWhiteSpace>(compareLooper);
        copyDatabaseOfIncludeFile(startLooper+2, includeFileName);
        m_database.addIncludeFile(includeFileName);
        temporaryFindings.copyCurrentFindings(m_findings);
        combineToASingleTerm(startLooper, compareLooper, TermType::ProcessedTerm);
        return true;
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToDefineMacro(Looper const& startLooper)
{
    DBGPRINT2("isModifiedDueToDefineMacro");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<Term, 3> const expectedTerms{T(TermType::Macro, "#define"), T(TermType::WhiteSpace), T(TermType::Identifier)};
    if(isSingleLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, expectedTerms))
    {
        VectorOfTerms terms(getTerms(startLooper, expectedTerms));
        string macroName(getStringWithoutQuotations(terms[2].getString()));
        Looper afterIdentifier(compareLooper);
        incrementLooperIfWhiteSpaceForMacro<FindingsToAdd::None>(afterIdentifier);
        bool isModified = true;
        if(isModifiedDueToDefineMacroWithParameters(startLooper, afterIdentifier, macroName));
        else if(isModifiedDueToDefineMacroWithNoParameters(startLooper, afterIdentifier, macroName));
        else
        {
            isModified = false;
        }
        if(isModified)
        {
            temporaryFindings.copyCurrentFindings(m_findings);
        }
        return isModified;
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToDefineMacroWithParameters(Looper const& startLooper, Looper const& afterIdentifierLooper, string const& macroName)
{
    DBGPRINT2("isModifiedDueToDefineMacroWithParameters");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper afterOpeningParenthesis(afterIdentifierLooper);
    Looper afterClosingParenthesis(afterIdentifierLooper);
    if(isBothParenthesesFoundAndMoveLoopers<LooperConnector::WhiteSpaceAndNewLine>(afterIdentifierLooper, afterOpeningParenthesis, afterClosingParenthesis))
    {
        Looper afterClosingParenthesisAndWhiteSpace(afterClosingParenthesis);
        incrementLooperIfWhiteSpaceForMacro<FindingsToAdd::None>(afterClosingParenthesisAndWhiteSpace);
        Looper afterNewLineLooper(afterClosingParenthesisAndWhiteSpace);
        if(isEndOfMacroFoundAndMoveLooper(afterNewLineLooper))
        {
            Looper macroEquivalentLooper(afterClosingParenthesisAndWhiteSpace, afterNewLineLooper-1);
            if(hasTermsForMacro(macroEquivalentLooper))
            {
                if(isStringFoundInLooper(macroEquivalentLooper, macroName))
                {
                    addFinding(constructFileLocator(__FILE__, __LINE__), "Cannot add macro:"+macroName+". Macro name is used in macro equivalent.", startLooper);
                }
                else
                {
                    m_database.addMacro(macroName);
                    CPlusPlusMacro& cPlusPlusMacro = m_database.getMacroReference(macroName);
                    checkMacroParameters(Looper(afterOpeningParenthesis, afterClosingParenthesis-1), cPlusPlusMacro);
                    copyLooperSpanToVectorOfTermsForMacro(macroEquivalentLooper, cPlusPlusMacro);
                }
                temporaryFindings.copyCurrentFindings(m_findings);
                combineToASingleTerm(startLooper, afterNewLineLooper, TermType::ProcessedTerm);
                return true;
            }
        }
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToDefineMacroWithNoParameters(Looper const& startLooper, Looper const& afterIdentifierLooper, string const& macroName)
{
    DBGPRINT2("isModifiedDueToDefineMacroWithNoParameters");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper afterNewLineLooper(afterIdentifierLooper);
    if(isEndOfMacroFoundAndMoveLooper(afterNewLineLooper))
    {
        Looper macroEquivalentLooper(afterIdentifierLooper, afterNewLineLooper-1);
        if(isStringFoundInLooper(macroEquivalentLooper, macroName))
        {
            addFinding(constructFileLocator(__FILE__, __LINE__), "Cannot add macro:"+macroName+". Macro name is used in macro equivalent.", startLooper);
        }
        else
        {
            m_database.addMacro(macroName);
            copyLooperSpanToVectorOfTermsForMacro(macroEquivalentLooper, m_database.getMacroReference(macroName));
        }
        temporaryFindings.copyCurrentFindings(m_findings);
        combineToASingleTerm(startLooper, afterNewLineLooper, TermType::ProcessedTerm);
        return true;
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToUndefMacro(Looper const& startLooper)
{
    DBGPRINT2("isModifiedDueToUndefMacro");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<Term, 3> const expectedTerms{T(TermType::Macro, "#undef"), T(TermType::WhiteSpace),
                T(TermType::Identifier)};
    if(isSingleLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, expectedTerms))
    {
        incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::ExpectsNewLineAndUnexpectsWhiteSpace>(compareLooper);
        VectorOfTerms terms(getTerms(startLooper, expectedTerms));
        string macroName(getStringWithoutQuotations(terms[2].getString()));
        m_database.removeMacro(macroName);
        temporaryFindings.copyCurrentFindings(m_findings);
        combineToASingleTerm(startLooper, compareLooper, TermType::ProcessedTerm);
        return true;
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToOtherMacros(Looper const& startLooper)
{
    DBGPRINT2("isModifiedDueToExtraMacros");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<TermChecker, 1> const termCheckers{TC(TermCheckerType::isOtherMacro)};
    if(isSingleLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, termCheckers))
    {
        Looper afterNewLineLooper(compareLooper);
        if(isEndOfMacroFoundAndMoveLooper(afterNewLineLooper))
        {
            temporaryFindings.copyCurrentFindings(m_findings);
            combineToASingleTerm(startLooper, afterNewLineLooper, TermType::ProcessedTerm);
            return true;
        }
    }
    return false;
}

void TermAnalyzer::copyDatabaseOfIncludeFile(Looper const& startLooper, string const& includeFileName)
{
    DBGPRINT2("copyDatabaseOfIncludeFile");
    if(m_optionalSailIt)
    {
        SailIt& sailIt = m_optionalSailIt.get();
        FileDirectoryDatabase& fileDirectoryDatabase = sailIt.getFileDirectoryDatabaseReference();
        if(fileDirectoryDatabase.isFileIncluded(m_baseDirectory, includeFileName))
        {
            string fullPath = fileDirectoryDatabase.getFullPathOfFile(m_baseDirectory, includeFileName);
            sailIt.addCPlusPlusDatabaseReferenceForThisFileIfNeeded(fullPath);
            CPlusPlusDatabase& copyThis = sailIt.getCPlusPlusDatabaseReferenceForThisFile(fullPath);
            for(auto const& type : copyThis.getTypesReference())
            {
                cout<<"Types: "<<m_fileName<<" :: "<<includeFileName<<" :: "<<type.first<<endl;
            }
            m_database.copyContentsOf(copyThis);
        }
        else
        {
            addFinding(constructFileLocator(__FILE__, __LINE__), "Include file:"+includeFileName+" is not found.", startLooper);
        }
    }
}

bool TermAnalyzer::isEndOfMacroFoundAndMoveLooper(Looper& movableLooper)
{
    DBGPRINT2("isNewLineFoundAndMoveLooperForMacro");
    Looper searchLooper(movableLooper);
    Term newLine(TermType::NewLine);
    Term backSlash(TermType::Operator, "\\");
    bool backSlashFound(false);
    while(searchLooper.isNotFinished())
    {
        if(backSlash == searchLooper.getContentReference())
        {
            backSlashFound = true;
        }
        else if(newLine == searchLooper.getContentReference())
        {
            if(!backSlashFound)
            {
                movableLooper.setCurrentIndex(searchLooper);
                movableLooper++;
                return true;
            }
            backSlashFound=false;
        }
        searchLooper++;
    }
    return false;
}

bool TermAnalyzer::hasTermsForMacro(Looper const& startLooper)
{
    DBGPRINT2("hasTermsForMacro");
    Looper copyLooper(startLooper);
    Term backSlash(TermType::Operator, "\\");
    while(copyLooper.isNotFinished())
    {
        Term& term = copyLooper.getContentReference();
        if(!(backSlash == term || CheckerHelpers::isIgnorable(term)))
        {
            return true;
        }
        copyLooper++;
    }
    return false;
}

void TermAnalyzer::copyLooperSpanToVectorOfTermsForMacro(Looper const& startLooper, CPlusPlusMacro& cPlusPlusMacro)
{
    DBGPRINT2("copyLooperSpanToVectorOfTermsForMacro");
    Looper copyLooper(startLooper);
    Term backSlash(TermType::Operator, "\\");
    VectorOfStrings& macroParameters = cPlusPlusMacro.getMacroParameters();
    int macroParameterSize = macroParameters.size();
    int positionIndex = 0;
    while(copyLooper.isNotFinished())
    {
        Term& term = copyLooper.getContentReference();
        if(backSlash != term)
        {
            if(TermType::Identifier == term.getTermType())
            {
                for(int parameterIndex=0; parameterIndex<macroParameterSize; parameterIndex++)
                {
                    if(macroParameters[parameterIndex] == term.getString())
                    {
                        cPlusPlusMacro.mapThisPositionToThisParameter(positionIndex, parameterIndex);
                    }
                }
            }
            if(!CheckerHelpers::isIgnorable(term))
            {
                cPlusPlusMacro.addMacroEquivalent(term);
                positionIndex++;
            }
        }
        copyLooper++;
    }
}

void TermAnalyzer::checkMacroParameters(Looper const& startLooper, CPlusPlusMacro& cPlusPlusMacro)
{
    array<Term, 3> const nextArgumentForm{T(TermType::Identifier), T(TermType::Operator, ","), T(TermType::WhiteSpace)};
    array<Term, 1> const lastArgumentForm{T(TermType::Identifier)};
    array<Term, 3> const variadicArgumentForm{T(TermType::Operator, "."), T(TermType::Operator, "."), T(TermType::Operator, ".")};
    VectorOfStrings& macroParameters = cPlusPlusMacro.getMacroParameters();
    Looper parameterLooper(startLooper);
    simplifyExpressions(startLooper);
    while (parameterLooper.isNotFinished())
    {
        Looper firstTermLooper(parameterLooper);
        if(isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::WhiteSpaceAndNewLine>(parameterLooper, nextArgumentForm))
        {
            macroParameters.push_back(firstTermLooper.getContentReference().getString());
        }
        else if(isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::WhiteSpaceAndNewLine>(parameterLooper, lastArgumentForm))
        {
            macroParameters.push_back(firstTermLooper.getContentReference().getString());
            break;
        }
        else if(isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::WhiteSpaceAndNewLine>(parameterLooper, variadicArgumentForm))
        {
            macroParameters.push_back("__VA_ARGS__");
            cPlusPlusMacro.setVariadicParameterIndex(macroParameters.size()-1);
            break;
        }
        else
        {
            addFinding(constructFileLocator(__FILE__, __LINE__), "Unprocessed term in macro parameters", parameterLooper);
            break;
        }
    }
    incrementLooperIfWhiteSpaceAndNewLine<FindingsToAdd::UnexpectsNewLineAndUnexpectsWhiteSpace>(parameterLooper);
    if(parameterLooper.isNotFinished())
    {
        addFinding(constructFileLocator(__FILE__, __LINE__), "Incorrect macro parameters", parameterLooper);
    }
}


}// namespace codeReview


