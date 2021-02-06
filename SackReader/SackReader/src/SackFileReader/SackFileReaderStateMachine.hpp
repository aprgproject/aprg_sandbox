#pragma once

#include <CommonTypes.hpp>
#include <Database.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <State/AlbaBaseStateMachine.hpp>

namespace alba
{

namespace SackFileReaderStateMachineNamespace
{

enum class State
{
    Idle,
    SharpDefineForMessageId,
    SharpDefineForConstant,
    TypedefKeyword,
    StructKeyword,
    EnumKeyword,
    UnionKeyword,
    AtDefDescription,
    AtStructDescription,
    AtEnumDescription,
    AtUnionDescription,
    AtParamDescription,
    AtTypedefDescription
};

//#define MAX_NR_OF_CODES 2                /* 3GPP 10 Nokia 2*/
enum class StateForConstant
{
    BeforeName,
    AfterNameBeforeValue
};

//@def MAX_NR_OF_CODES :                  3GPP 10 Nokia 2.
enum class StateForAtDefDescription
{
    BeforeName,
    AfterNameBeforeColon,
    AfterColon
};

/*
struct SWamUnit
{
    TBoard                    logUnitAddr;
    TCpu                      cpuAddr;
    u8                        pad1;
    u8                        numOfFspUnits;
    EControlUnitType          unitType;
    EAvailability             isUnitAvailable;
    EMcuSwDeployment          swDeployment;
};
typedef struct SWamUnit SWamUnit;
*/
enum class StateForStruct
{
    BeforeName,
    AfterName,
    AfterOpeningBraces,
};

enum class StateForStructAfterOpeningBraces
{
    BeforeParameterType,
    AfterParameterTypeBeforeParameterName,
    AfterParameterName,
    AfterOpeningBracket,
    AfterClosingBracket
};

//@param logUnitAddr                : logical unit address (e.g. WAM10)
enum class StateForAtParamDescription
{
    BeforeName,
    AfterNameBeforeColon,
    AfterColon
};

/*
typedef enum EHspaMapping
{
    EHspaMapping_EmptyValue            = 0,
    EHspaMapping_Fsm1                  = 1,
    EHspaMapping_Fsm2                  = 2,
    EHspaMapping_Subrack1              = 3,
    EHspaMapping_SubrackUltra          = 4
} EHspaMapping;
 */
enum class StateForEnum
{
    BeforeName,
    AfterName,
    AfterOpeningBraces,
};

enum class StateForEnumAfterOpeningBraces
{
    BeforeEnumParameterName,
    AfterEnumParameterNameBeforeEqualSymbol,
    AfterEqualSymbolBeforeValue,
    AfterValue
};

/*
typedef union
{
    SWamUnit           wamUnit;
    SWspUnit           wspUnit;
    SRxTxResource      rxTxResource;
} UConfigInfoElement;

union URxAntennaBusParameters
{
    SAntennaBusParametersForRfBus     paramsForRfBus;
    SAntennaPhysicalAddress           paramsForRp3;
};
typedef union URxAntennaBusParameters URxAntennaBusParameters;

typedef union UIpMacAddress
{
    SIpMacAddressV4 ipMacv4;
    SIpMacAddressV6 ipMacv6;
} UIpMacAddress;
*/
enum class StateForUnion
{
    BeforeName,
    AfterName,
    AfterOpeningBraces,
    AfterSemiColon,
};

enum class StateForUnionAfterOpeningBraces
{
    BeforeParameterType,
    AfterParameterTypeBeforeParameterName,
    AfterParameterName
};

//typedef u32 TSubrackNbr; /* subrack number*/
enum class StateForTypedef
{
    BeforeDerivedName,
    AfterDerivedNameBeforeName,
    AfterNameBeforeSemiColon,
};

/*
* @typedef TSubunits
*
* Description : Subunits in floating point format.
*
* Reference   : BTSOM IFS, < BTSOM IFS version >
*/
enum class StateForAtTypedefDescription
{
    BeforeName,
    AfterNameBeforeDescriptionKeyword,
    AfterDescriptionKeywordBeforeColon,
    AfterColon,
};

enum class ParameterDescriptionType
{
    None,
    Structure,
    Enum,
    Union
};


struct InputToken
{
    bool isInMultilineComment;
    bool isNotInComment;
    std::string token;
    std::string line;
};

struct InnerStates
{
    InnerStates();
    void reset();
    StateForConstant stateForConstant;
    StateForStruct stateForStruct;
    StateForStructAfterOpeningBraces stateForStructAfterOpeningBraces;
    StateForEnum stateForEnum;
    StateForEnumAfterOpeningBraces stateForEnumAfterOpeningBraces;
    StateForUnion stateForUnion;
    StateForUnionAfterOpeningBraces stateForUnionAfterOpeningBraces;
    StateForTypedef stateForTypedef;
    StateForAtDefDescription stateForAtDefDescription;
    StateForAtParamDescription stateForAtParamDescription;
    StateForAtTypedefDescription stateForAtTypedefDescription;
};




using BaseSackFileReaderStateMachine = AlbaBaseStateMachine<State, InputToken>;
class SackFileReaderStateMachine : public BaseSackFileReaderStateMachine
{
public:
    SackFileReaderStateMachine(Database & database, std::string const& fullPath);
    bool isNextLineNeeded() const;

    void processInput(InputToken const& inputToken);
    void processEndOfLine();

private:
    bool isNotWhiteSpaceAndNotInComment(InputToken const& inputToken) const;
    void processStateIdle(InputToken const& inputToken);
    void processStateSharpDefineForMessageId(InputToken const& inputToken);
    void processStateSharpDefineForConstant(InputToken const& inputToken);
    void processStateStructKeyword(InputToken const& inputToken);
    void processStateForStructAfterOpeningBraces(std::string const& token);
    void processStateEnumKeyword(InputToken const& inputToken);
    void processStateForEnumAfterOpeningBraces(std::string const& token);
    void processStateUnionKeyword(InputToken const& inputToken);
    void processStateForUnionAfterOpeningBraces(std::string const& token);
    void processStateTypedefKeyword(InputToken const& inputToken);
    void processStateAtDefDescription(InputToken const& inputToken);
    void processStateAtStructDescription(InputToken const& inputToken);
    void processStateAtEnumDescription(InputToken const& inputToken);
    void processStateAtUnionDescription(InputToken const& inputToken);
    void processStateAtParamDescription(InputToken const& inputToken);
    void processStateAtTypedefDescription(InputToken const& inputToken);
    void saveNextStateAndResetInnerStates(State const& state);
    void saveMessageToDatabase(std::string const& token, std::string const& structureName);
    void saveConstantToDatabase();
    void saveStructureAsMessageStructureInDatabase();
    void saveParameterInUnionToDatabase();
    void saveParameterInStructureToDatabase();
    void saveParameterInEnumToDatabase();
    void saveConstantDescriptionToDatabase(std::string const& partialString);
    void saveParameterDescriptionToDatabase(std::string const& partialString);
    void saveTypedefToDatabase();
    void saveTypedefDescriptionToDatabase(std::string const& partialString);
    AlbaLocalPathHandler m_filePathHandler;
    bool m_isMessageIdFile;
    bool m_isNextLineNeeded;
    InnerStates m_innerStates;
    std::string m_pathFromIInterface;
    std::string m_arraySize;
    std::string m_previousStructureName;
    std::string m_previousEnumName;
    std::string m_previousUnionName;
    ConstantDetails m_constantDetails;
    TypedefDetails m_typedefDetails;
    StructureDetails m_structureDetails;
    UnionDetails m_unionDetails;
    ParameterDetails m_parameterDetails;
    EnumDetails m_enumDetails;
    EnumParameterDetails m_enumParameterDetails;
    ParameterDescriptionType m_parameterDescriptionType;
    Database & m_database;
};

}

}//namespace alba
