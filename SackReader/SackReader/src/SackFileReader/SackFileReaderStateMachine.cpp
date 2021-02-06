#include "SackFileReaderStateMachine.hpp"

#include <String/AlbaStringHelper.hpp>


using namespace alba::stringHelper;
using namespace std;

namespace alba
{

namespace SackFileReaderStateMachineNamespace
{

InnerStates::InnerStates()
    : stateForConstant(StateForConstant::BeforeName)
    , stateForStruct(StateForStruct::BeforeName)
    , stateForStructAfterOpeningBraces(StateForStructAfterOpeningBraces::BeforeParameterType)
    , stateForEnum(StateForEnum::BeforeName)
    , stateForEnumAfterOpeningBraces(StateForEnumAfterOpeningBraces::BeforeEnumParameterName)
    , stateForUnion(StateForUnion::BeforeName)
    , stateForUnionAfterOpeningBraces(StateForUnionAfterOpeningBraces::BeforeParameterType)
    , stateForTypedef(StateForTypedef::BeforeDerivedName)
    , stateForAtDefDescription(StateForAtDefDescription::BeforeName)
    , stateForAtParamDescription(StateForAtParamDescription::BeforeName)
    , stateForAtTypedefDescription(StateForAtTypedefDescription::BeforeName)
{}

void InnerStates::reset()
{
    stateForConstant = StateForConstant::BeforeName;
    stateForStruct = StateForStruct::BeforeName;
    stateForStructAfterOpeningBraces = StateForStructAfterOpeningBraces::BeforeParameterType;
    stateForEnum = StateForEnum::BeforeName;
    stateForEnumAfterOpeningBraces = StateForEnumAfterOpeningBraces::BeforeEnumParameterName;
    stateForUnion = StateForUnion::BeforeName;
    stateForUnionAfterOpeningBraces = StateForUnionAfterOpeningBraces::BeforeParameterType;
    stateForTypedef = StateForTypedef::BeforeDerivedName;
    stateForAtDefDescription = StateForAtDefDescription::BeforeName;
    stateForAtParamDescription = StateForAtParamDescription::BeforeName;
    stateForAtTypedefDescription = StateForAtTypedefDescription::BeforeName;
}

SackFileReaderStateMachine::SackFileReaderStateMachine(Database & database, string const& fullPath)
    : BaseSackFileReaderStateMachine(State::Idle)
    , m_filePathHandler(fullPath)
    , m_isMessageIdFile(isStringFoundInsideTheOtherStringNotCaseSensitive(m_filePathHandler.getFilenameOnly(), "MessageId_"))
    , m_isNextLineNeeded(false)
    , m_pathFromIInterface(getCorrectPathWithReplacedSlashCharacters<'/'>(string(R"(\I_Interface\)") + getStringAfterThisString(m_filePathHandler.getFullPath(), R"(\I_Interface\)")))
    , m_database(database)
{}

bool SackFileReaderStateMachine::isNextLineNeeded() const
{
    return m_isNextLineNeeded;
}

void SackFileReaderStateMachine::processInput(InputToken const& inputToken)
{
    m_isNextLineNeeded = false;
    switch(m_state)
    {
    case State::Idle:
        processStateIdle(inputToken);
        break;
    case State::SharpDefineForConstant:
        processStateSharpDefineForConstant(inputToken);
        break;
    case State::SharpDefineForMessageId:
        processStateSharpDefineForMessageId(inputToken);
        break;
    case State::StructKeyword:
        processStateStructKeyword(inputToken);
        break;
    case State::EnumKeyword:
        processStateEnumKeyword(inputToken);
        break;
    case State::UnionKeyword:
        processStateUnionKeyword(inputToken);
        break;
    case State::TypedefKeyword:
        processStateTypedefKeyword(inputToken);
        break;
    case State::AtDefDescription:
        processStateAtDefDescription(inputToken);
        break;
    case State::AtStructDescription:
        processStateAtStructDescription(inputToken);
        break;
    case State::AtEnumDescription:
        processStateAtEnumDescription(inputToken);
        break;
    case State::AtUnionDescription:
        processStateAtUnionDescription(inputToken);
        break;
    case State::AtParamDescription:
        processStateAtParamDescription(inputToken);
        break;
    case State::AtTypedefDescription:
        processStateAtTypedefDescription(inputToken);
        break;
    default:
        assert(false);
        break;
    }
}

void SackFileReaderStateMachine::processEndOfLine()
{
    if(m_state == State::SharpDefineForConstant || m_state == State::SharpDefineForMessageId)
    {
        saveNextState(State::Idle);
    }
}


bool SackFileReaderStateMachine::isNotWhiteSpaceAndNotInComment(InputToken const& inputToken) const
{
    return !isWhiteSpace(inputToken.token) && inputToken.isNotInComment;
}

void SackFileReaderStateMachine::processStateIdle(InputToken const& inputToken)
{
    string const& token(inputToken.token);
    if(inputToken.isNotInComment)
    {
        if(token == "#define")
        {
            if(m_isMessageIdFile)
            {
                saveNextStateAndResetInnerStates(State::SharpDefineForMessageId);
            }
            else
            {
                saveNextStateAndResetInnerStates(State::SharpDefineForConstant);
            }
        }
        else if(token == "struct")
        {
            saveNextStateAndResetInnerStates(State::StructKeyword);
        }
        else if(token == "enum")
        {
            saveNextStateAndResetInnerStates(State::EnumKeyword);
        }
        else if(token == "union")
        {
            saveNextStateAndResetInnerStates(State::UnionKeyword);
        }
        else if(token == "typedef")
        {
            saveNextStateAndResetInnerStates(State::TypedefKeyword);
        }
    }
    else if(inputToken.isInMultilineComment)
    {
        if(token == "@def")
        {
            saveNextStateAndResetInnerStates(State::AtDefDescription);
        }
        else if(token == "@struct")
        {
            saveNextStateAndResetInnerStates(State::AtStructDescription);
        }
        else if(token == "@enum")
        {
            saveNextStateAndResetInnerStates(State::AtEnumDescription);
        }
        else if(token == "@Union")
        {
            saveNextStateAndResetInnerStates(State::AtUnionDescription);
        }
        else if(token == "@param")
        {
            saveNextStateAndResetInnerStates(State::AtParamDescription);
        }
        else if(token == "@typedef")
        {
            saveNextStateAndResetInnerStates(State::AtTypedefDescription);
        }
    }
}
void SackFileReaderStateMachine::processStateSharpDefineForMessageId(InputToken const& inputToken)
{
    string const& token(inputToken.token);
    if(isNotWhiteSpaceAndNotInComment(inputToken))
    {
        saveMessageToDatabase(token, getStringInBetweenTwoStrings(inputToken.line, "/* !- SIGNO(struct ", ") -! */"));
        m_isNextLineNeeded = true;
        saveNextState(State::Idle);
    }
}

void SackFileReaderStateMachine::processStateSharpDefineForConstant(InputToken const& inputToken)
{
    string const& token(inputToken.token);
    if(isNotWhiteSpaceAndNotInComment(inputToken))
    {
        if(StateForConstant::BeforeName == m_innerStates.stateForConstant)
        {
            m_constantDetails.name = token;
            m_innerStates.stateForConstant = StateForConstant::AfterNameBeforeValue;
        }
        else if(StateForConstant::AfterNameBeforeValue == m_innerStates.stateForConstant)
        {
            m_constantDetails.value = token;
            saveConstantToDatabase();
            saveNextState(State::Idle);
        }
    }
}

void SackFileReaderStateMachine::processStateStructKeyword(InputToken const& inputToken)
{
    string const& token(inputToken.token);
    if(isNotWhiteSpaceAndNotInComment(inputToken) && token!="/")
    {
        if(StateForStruct::BeforeName == m_innerStates.stateForStruct)
        {
            m_structureDetails.name = token;
            m_innerStates.stateForStruct=StateForStruct::AfterName;
        }
        else if(StateForStruct::AfterName == m_innerStates.stateForStruct)
        {
            if("{" == token)
            {
                m_innerStates.stateForStruct = StateForStruct::AfterOpeningBraces;
                m_innerStates.stateForStructAfterOpeningBraces = StateForStructAfterOpeningBraces::BeforeParameterType;
            }
            else if(";" == token)
            {
                m_structureDetails.clear();
                saveNextState(State::Idle);
            }
        }
        else if(StateForStruct::AfterOpeningBraces == m_innerStates.stateForStruct)
        {
            processStateForStructAfterOpeningBraces(token);
        }
    }
}

void SackFileReaderStateMachine::processStateForStructAfterOpeningBraces(string const& token)
{
    static string partialString;
    if("MESSAGEHEADER" == token)
    {
        saveStructureAsMessageStructureInDatabase();
        m_isNextLineNeeded = true;
    }
    else if("}" == token)
    {
        m_previousStructureName = m_structureDetails.name;
        m_parameterDescriptionType = ParameterDescriptionType::Structure;
        m_structureDetails.clear();
        saveNextState(State::Idle);
    }
    else if(";" == token)
    {
        m_innerStates.stateForStructAfterOpeningBraces = StateForStructAfterOpeningBraces::BeforeParameterType;
        saveParameterInStructureToDatabase();
    }
    else
    {
        if(StateForStructAfterOpeningBraces::BeforeParameterType == m_innerStates.stateForStructAfterOpeningBraces)
        {
            m_parameterDetails.type = token;
            m_innerStates.stateForStructAfterOpeningBraces = StateForStructAfterOpeningBraces::AfterParameterTypeBeforeParameterName;
        }
        else if(StateForStructAfterOpeningBraces::AfterParameterTypeBeforeParameterName == m_innerStates.stateForStructAfterOpeningBraces)
        {
            m_parameterDetails.name = token;
            m_innerStates.stateForStructAfterOpeningBraces = StateForStructAfterOpeningBraces::AfterParameterName;
        }
        else if(StateForStructAfterOpeningBraces::AfterParameterName == m_innerStates.stateForStructAfterOpeningBraces)
        {
            if("[" == token)
            {
                m_innerStates.stateForStructAfterOpeningBraces = StateForStructAfterOpeningBraces::AfterOpeningBracket;
            }
        }
        else if(StateForStructAfterOpeningBraces::AfterOpeningBracket == m_innerStates.stateForStructAfterOpeningBraces)
        {
            if("]" == token)
            {
                m_arraySize = partialString;
                partialString.clear();
                m_innerStates.stateForStructAfterOpeningBraces = StateForStructAfterOpeningBraces::AfterClosingBracket;
            }
            else
            {
                partialString += token;
            }
        }
    }
}

void SackFileReaderStateMachine::processStateEnumKeyword(InputToken const& inputToken)
{
    string const& token(inputToken.token);
    if(isNotWhiteSpaceAndNotInComment(inputToken) && token!="/")
    {
        if(StateForEnum::BeforeName == m_innerStates.stateForEnum)
        {
            m_enumDetails.name = token;
            m_innerStates.stateForEnum = StateForEnum::AfterName;
        }
        else if(StateForEnum::AfterName == m_innerStates.stateForEnum)
        {
            if("{" == token)
            {
                m_innerStates.stateForEnum = StateForEnum::AfterOpeningBraces;
            }
            else if(";" == token)
            {
                m_enumDetails.clear();
                saveNextState(State::Idle);
            }
        }
        else if(StateForEnum::AfterOpeningBraces == m_innerStates.stateForEnum)
        {
            processStateForEnumAfterOpeningBraces(token);
        }
    }
}

void SackFileReaderStateMachine::processStateForEnumAfterOpeningBraces(string const& token)
{
    if("}" == token || "," == token)
    {
        m_innerStates.stateForEnumAfterOpeningBraces = StateForEnumAfterOpeningBraces::BeforeEnumParameterName;
        if(!m_enumParameterDetails.name.empty())
        {
            saveParameterInEnumToDatabase();
            m_enumParameterDetails.clear();
        }
        if("}" == token)
        {
            m_previousEnumName = m_enumDetails.name;
            m_parameterDescriptionType = ParameterDescriptionType::Enum;
            m_enumDetails.clear();
            saveNextState(State::Idle);
        }
    }
    else
    {
        if(StateForEnumAfterOpeningBraces::BeforeEnumParameterName == m_innerStates.stateForEnumAfterOpeningBraces)
        {
            m_enumParameterDetails.name = token;
            m_innerStates.stateForEnumAfterOpeningBraces = StateForEnumAfterOpeningBraces::AfterEnumParameterNameBeforeEqualSymbol;
        }
        else if(StateForEnumAfterOpeningBraces::AfterEnumParameterNameBeforeEqualSymbol == m_innerStates.stateForEnumAfterOpeningBraces)
        {
            if("=" == token)
            {
                m_innerStates.stateForEnumAfterOpeningBraces = StateForEnumAfterOpeningBraces::AfterEqualSymbolBeforeValue;
            }
        }
        else if(StateForEnumAfterOpeningBraces::AfterEqualSymbolBeforeValue == m_innerStates.stateForEnumAfterOpeningBraces)
        {
            m_enumParameterDetails.value = token;
            m_innerStates.stateForEnumAfterOpeningBraces = StateForEnumAfterOpeningBraces::AfterValue;
        }
    }
}

void SackFileReaderStateMachine::processStateUnionKeyword(InputToken const& inputToken)
{
    string const& token(inputToken.token);
    if(isNotWhiteSpaceAndNotInComment(inputToken) && token!="/")
    {
        if(StateForUnion::BeforeName == m_innerStates.stateForUnion)
        {
            if("{" == token)
            {
                m_unionDetails.name = m_filePathHandler.getFilenameOnly();
                m_innerStates.stateForUnion = StateForUnion::AfterOpeningBraces;
                m_innerStates.stateForUnionAfterOpeningBraces = StateForUnionAfterOpeningBraces::BeforeParameterType;
            }
            else
            {
                m_unionDetails.name = token;
                m_innerStates.stateForUnion = StateForUnion::AfterName;
            }
        }
        else if(StateForUnion::AfterName == m_innerStates.stateForUnion)
        {
            if("{" == token)
            {
                m_innerStates.stateForUnion = StateForUnion::AfterOpeningBraces;
                m_innerStates.stateForUnionAfterOpeningBraces = StateForUnionAfterOpeningBraces::BeforeParameterType;
            }
            else if(";" == token)
            {
                m_unionDetails.clear();
                saveNextState(State::Idle);
            }
        }
        else if(StateForUnion::AfterOpeningBraces == m_innerStates.stateForUnion)
        {
            processStateForUnionAfterOpeningBraces(token);
        }
    }
}

void SackFileReaderStateMachine::processStateForUnionAfterOpeningBraces(string const& token)
{
    if("}" == token)
    {
        m_previousUnionName = m_unionDetails.name;
        m_parameterDescriptionType = ParameterDescriptionType::Union;
        m_unionDetails.clear();
        saveNextState(State::Idle);
    }
    else if(";" == token)
    {
        m_innerStates.stateForUnionAfterOpeningBraces = StateForUnionAfterOpeningBraces::BeforeParameterType;
        saveParameterInUnionToDatabase();
    }
    else
    {
        if(StateForUnionAfterOpeningBraces::BeforeParameterType == m_innerStates.stateForUnionAfterOpeningBraces)
        {
            m_parameterDetails.type = token;
            m_innerStates.stateForUnionAfterOpeningBraces = StateForUnionAfterOpeningBraces::AfterParameterTypeBeforeParameterName;
        }
        else if(StateForUnionAfterOpeningBraces::AfterParameterTypeBeforeParameterName == m_innerStates.stateForUnionAfterOpeningBraces)
        {
            m_parameterDetails.name = token;
            m_innerStates.stateForUnionAfterOpeningBraces = StateForUnionAfterOpeningBraces::AfterParameterName;
        }
    }
}

void SackFileReaderStateMachine::processStateTypedefKeyword(InputToken const& inputToken)
{
    string const& token(inputToken.token);
    if(isNotWhiteSpaceAndNotInComment(inputToken))
    {
        if("struct" == token)
        {
            saveNextStateAndResetInnerStates(State::StructKeyword);
        }
        else if("union" == token)
        {
            saveNextStateAndResetInnerStates(State::UnionKeyword);
        }
        else if("enum" == token)
        {
            saveNextStateAndResetInnerStates(State::EnumKeyword);
        }
        else if(StateForTypedef::BeforeDerivedName == m_innerStates.stateForTypedef)
        {
            m_typedefDetails.typedefDerivedName = token;
            m_innerStates.stateForTypedef = StateForTypedef::AfterDerivedNameBeforeName;
        }
        else if(StateForTypedef::AfterDerivedNameBeforeName == m_innerStates.stateForTypedef)
        {
            m_typedefDetails.name = token;
            m_innerStates.stateForTypedef = StateForTypedef::AfterNameBeforeSemiColon;
        }
        else if(StateForTypedef::AfterNameBeforeSemiColon == m_innerStates.stateForTypedef)
        {
            if(";" == token)
            {
                saveTypedefToDatabase();
                saveNextState(State::Idle);
            }
        }
    }
}

void SackFileReaderStateMachine::processStateAtDefDescription(InputToken const& inputToken)
{
    static string partialString;
    string const& token(inputToken.token);
    if(inputToken.isInMultilineComment)
    {
        if(token == "@def" || token == "Additional" || token == "Definition")
        {
            saveConstantDescriptionToDatabase(partialString);
            partialString.clear();
            m_innerStates.stateForAtDefDescription = StateForAtDefDescription::BeforeName;
            if(token == "Additional" || token == "Definition")
            {
                saveNextState(State::Idle);
            }
        }
        else if(StateForAtDefDescription::BeforeName == m_innerStates.stateForAtDefDescription)
        {
            if(!isWhiteSpace(token))
            {
                m_constantDetails.name = token;
                m_innerStates.stateForAtDefDescription = StateForAtDefDescription::AfterNameBeforeColon;
            }
        }
        else if(StateForAtDefDescription::AfterNameBeforeColon == m_innerStates.stateForAtDefDescription)
        {
            if(":" == token)
            {
                partialString.clear();
                m_innerStates.stateForAtDefDescription = StateForAtDefDescription::AfterColon;
            }
        }
        else if(StateForAtDefDescription::AfterColon == m_innerStates.stateForAtDefDescription)
        {
            if("*" != token)
            {
                partialString+=token;
            }
        }
    }
    else
    {
        saveNextState(State::Idle);
    }
}

void SackFileReaderStateMachine::processStateAtStructDescription(InputToken const& inputToken)
{
    string const& token(inputToken.token);
    if(inputToken.isInMultilineComment)
    {
        if(!isWhiteSpace(token))
        {
            m_previousStructureName = token;
            m_parameterDescriptionType = ParameterDescriptionType::Structure;
            saveNextState(State::Idle);
        }
    }
    else
    {
        saveNextState(State::Idle);
    }
}

void SackFileReaderStateMachine::processStateAtEnumDescription(InputToken const& inputToken)
{
    string const& token(inputToken.token);
    if(inputToken.isInMultilineComment)
    {
        if(!isWhiteSpace(token))
        {
            m_previousEnumName = token;
            m_parameterDescriptionType = ParameterDescriptionType::Enum;
            saveNextState(State::Idle);
        }
    }
    else
    {
        saveNextState(State::Idle);
    }
}

void SackFileReaderStateMachine::processStateAtUnionDescription(InputToken const& inputToken)
{
    string const& token(inputToken.token);
    if(inputToken.isInMultilineComment)
    {
        if(!isWhiteSpace(token))
        {
            m_previousUnionName = token;
            m_parameterDescriptionType = ParameterDescriptionType::Union;
            saveNextState(State::Idle);
        }
    }
    else
    {
        saveNextState(State::Idle);
    }
}

void SackFileReaderStateMachine::processStateAtParamDescription(InputToken const& inputToken)
{
    static string partialString;
    string const& token(inputToken.token);
    if(inputToken.isInMultilineComment)
    {
        if(token == "@param" || token == "Additional" || token == "Definition")
        {
            saveParameterDescriptionToDatabase(partialString);
            partialString.clear();
            m_innerStates.stateForAtParamDescription = StateForAtParamDescription::BeforeName;
            if(token == "Additional" || token == "Definition")
            {
                m_parameterDescriptionType = ParameterDescriptionType::None;
                saveNextState(State::Idle);
            }
        }
        else if(StateForAtParamDescription::BeforeName == m_innerStates.stateForAtParamDescription)
        {
            if(!isWhiteSpace(token))
            {
                m_parameterDetails.name = token;
                m_innerStates.stateForAtParamDescription = StateForAtParamDescription::AfterNameBeforeColon;
            }
        }
        else if(StateForAtParamDescription::AfterNameBeforeColon == m_innerStates.stateForAtParamDescription)
        {
            if(":" == token)
            {
                partialString.clear();
                m_innerStates.stateForAtParamDescription = StateForAtParamDescription::AfterColon;
            }
        }
        else if(StateForAtParamDescription::AfterColon == m_innerStates.stateForAtParamDescription)
        {
            if("*" != token)
            {
                partialString+=token;
            }
        }
    }
    else
    {
        saveNextState(State::Idle);
    }
}
void SackFileReaderStateMachine::processStateAtTypedefDescription(InputToken const& inputToken)
{
    static string partialString;
    string const& token(inputToken.token);
    if(inputToken.isInMultilineComment)
    {
        if(token == "@typedef" || token == "Reference")
        {
            saveTypedefDescriptionToDatabase(partialString);
            partialString.clear();
            m_innerStates.stateForAtTypedefDescription = StateForAtTypedefDescription::BeforeName;
            if(token == "Reference")
            {
                saveNextState(State::Idle);
            }
        }
        else if(StateForAtTypedefDescription::BeforeName == m_innerStates.stateForAtTypedefDescription)
        {
            if(!isWhiteSpace(token))
            {
                m_typedefDetails.name = token;
                m_innerStates.stateForAtTypedefDescription = StateForAtTypedefDescription::AfterNameBeforeDescriptionKeyword;
            }
        }
        else if(StateForAtTypedefDescription::AfterNameBeforeDescriptionKeyword == m_innerStates.stateForAtTypedefDescription)
        {
            if("Description" == token)
            {
                m_innerStates.stateForAtTypedefDescription = StateForAtTypedefDescription::AfterDescriptionKeywordBeforeColon;
            }
        }
        else if(StateForAtTypedefDescription::AfterDescriptionKeywordBeforeColon == m_innerStates.stateForAtTypedefDescription)
        {
            if(":" == token)
            {
                partialString.clear();
                m_innerStates.stateForAtTypedefDescription = StateForAtTypedefDescription::AfterColon;
            }
        }
        else if(StateForAtTypedefDescription::AfterColon == m_innerStates.stateForAtTypedefDescription)
        {
            if("*" != token)
            {
                partialString+=token;
            }
        }
    }
    else
    {
        saveNextState(State::Idle);
    }
}

void SackFileReaderStateMachine::saveNextStateAndResetInnerStates(State const& state)
{
    m_innerStates.reset();
    saveNextState(state);
}

void SackFileReaderStateMachine::saveMessageToDatabase(string const& token, string const& structureName)
{
    m_database.messageNameToMessageDetailsMap[token].name = token;
    m_database.messageNameToMessageDetailsMap[token].structureName = structureName;
    m_database.messageNameToMessageDetailsMap[token].path = m_pathFromIInterface;
}

void SackFileReaderStateMachine::saveConstantToDatabase()
{
    m_database.constantNameToConstantDetailsMap[m_constantDetails.name].name = m_constantDetails.name;
    m_database.constantNameToConstantDetailsMap[m_constantDetails.name].value = m_constantDetails.value;
    m_database.constantNameToConstantDetailsMap[m_constantDetails.name].path = m_pathFromIInterface;
}

void SackFileReaderStateMachine::saveStructureAsMessageStructureInDatabase()
{
    m_database.structureNameToStructureDetailsMap[m_structureDetails.name].isMessage = true;
}

void SackFileReaderStateMachine::saveParameterInStructureToDatabase()
{
    if(!m_parameterDetails.name.empty())
    {
        m_database.structureNameToStructureDetailsMap[m_structureDetails.name].name = m_structureDetails.name;
        m_database.structureNameToStructureDetailsMap[m_structureDetails.name].path = m_pathFromIInterface;
        if(!m_database.doesThisStructureAndParameterExistsInVector(m_structureDetails.name, m_parameterDetails.name))
        {
            m_database.structureNameToStructureDetailsMap[m_structureDetails.name].parametersWithCorrectOrder.emplace_back(m_parameterDetails.name);
        }
        m_database.structureNameToStructureDetailsMap[m_structureDetails.name].parameters[m_parameterDetails.name].name = m_parameterDetails.name;
        m_database.structureNameToStructureDetailsMap[m_structureDetails.name].parameters[m_parameterDetails.name].type = m_parameterDetails.type;
        if(!m_arraySize.empty())
        {
            m_database.structureNameToStructureDetailsMap[m_structureDetails.name].parameters[m_parameterDetails.name].isAnArray = true;
            m_database.structureNameToStructureDetailsMap[m_structureDetails.name].parameters[m_parameterDetails.name].arraySize = m_arraySize;
            m_arraySize.clear();
        }
        m_parameterDetails.clear();
    }
}

void SackFileReaderStateMachine::saveParameterInUnionToDatabase()
{
    if(!m_parameterDetails.name.empty())
    {
        m_database.unionNameToUnionDetailsMap[m_unionDetails.name].name = m_unionDetails.name;
        m_database.unionNameToUnionDetailsMap[m_unionDetails.name].path = m_pathFromIInterface;
        if(!m_database.doesThisUnionAndParameterExistsInVector(m_unionDetails.name, m_parameterDetails.name))
        {
            m_database.unionNameToUnionDetailsMap[m_unionDetails.name].parametersWithCorrectOrder.emplace_back(m_parameterDetails.name);
        }
        m_database.unionNameToUnionDetailsMap[m_unionDetails.name].parameters[m_parameterDetails.name].name = m_parameterDetails.name;
        m_database.unionNameToUnionDetailsMap[m_unionDetails.name].parameters[m_parameterDetails.name].type = m_parameterDetails.type;
        m_database.unionNameToUnionDetailsMap[m_unionDetails.name].path = m_pathFromIInterface;
        m_parameterDetails.clear();
    }
}

void SackFileReaderStateMachine::saveParameterInEnumToDatabase()
{
    m_database.enumNameToEnumDetailsMap[m_enumDetails.name].name = m_enumDetails.name;
    m_database.enumNameToEnumDetailsMap[m_enumDetails.name].path = m_pathFromIInterface;
    m_database.enumNameToEnumDetailsMap[m_enumDetails.name].parameters[m_enumParameterDetails.name].name = m_enumParameterDetails.name;
    m_database.enumNameToEnumDetailsMap[m_enumDetails.name].parameters[m_enumParameterDetails.name].value = m_enumParameterDetails.value;
    m_database.enumNameToEnumDetailsMap[m_enumDetails.name].parameters[m_enumParameterDetails.name].description = m_enumParameterDetails.description;
}

void SackFileReaderStateMachine::saveConstantDescriptionToDatabase(string const& partialString)
{
    m_database.constantNameToConstantDetailsMap[m_constantDetails.name].name = m_constantDetails.name;
    m_database.constantNameToConstantDetailsMap[m_constantDetails.name].description = getStringWithoutRedundantWhiteSpace(partialString);
}

void SackFileReaderStateMachine::saveParameterDescriptionToDatabase(string const& partialString)
{
    if(ParameterDescriptionType::Structure == m_parameterDescriptionType)
    {
        if(m_database.doesThisStructureAndParameterExists(m_previousStructureName, m_parameterDetails.name))
        {
            m_database.structureNameToStructureDetailsMap[m_previousStructureName].parameters[m_parameterDetails.name].description = getStringWithoutRedundantWhiteSpace(partialString);
        }
    }
    else if(ParameterDescriptionType::Enum == m_parameterDescriptionType)
    {
        if(m_database.doesThisEnumAndParameterExists(m_previousEnumName, m_parameterDetails.name))
        {
            m_database.enumNameToEnumDetailsMap[m_previousEnumName].parameters[m_parameterDetails.name].description = getStringWithoutRedundantWhiteSpace(partialString);
        }
        string anotherParameterName = m_previousEnumName+"_"+m_parameterDetails.name;
        if(m_database.doesThisEnumAndParameterExists(m_previousEnumName, anotherParameterName))
        {
            m_database.enumNameToEnumDetailsMap[m_previousEnumName].parameters[anotherParameterName].description = getStringWithoutRedundantWhiteSpace(partialString);
        }
    }
    else if(ParameterDescriptionType::Union == m_parameterDescriptionType)
    {
        if(m_database.doesThisUnionAndParameterExists(m_previousUnionName, m_parameterDetails.name))
        {
            m_database.unionNameToUnionDetailsMap[m_previousUnionName].parameters[m_parameterDetails.name].description = getStringWithoutRedundantWhiteSpace(partialString);
        }
    }
}

void SackFileReaderStateMachine::saveTypedefToDatabase()
{
    m_database.typedefNameToTypedefDetailsMap[m_typedefDetails.name].name = m_typedefDetails.name;
    m_database.typedefNameToTypedefDetailsMap[m_typedefDetails.name].typedefDerivedName = m_typedefDetails.typedefDerivedName;
    m_database.typedefNameToTypedefDetailsMap[m_typedefDetails.name].path = m_pathFromIInterface;
}

void SackFileReaderStateMachine::saveTypedefDescriptionToDatabase(string const& partialString)
{
    m_database.typedefNameToTypedefDetailsMap[m_typedefDetails.name].name = m_typedefDetails.name;
    m_database.typedefNameToTypedefDetailsMap[m_typedefDetails.name].description = getStringWithoutRedundantWhiteSpace(partialString);
}


}


}//namespace alba
