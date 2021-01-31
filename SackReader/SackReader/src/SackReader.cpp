#include "SackReader.hpp"

#include <File/AlbaFileReader.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <String/AlbaStringHelper.hpp>

#include <fstream>


#include <Debug/AlbaDebug.hpp>


using namespace alba::stringHelper;
using namespace std;

namespace alba
{

ostream& operator<<(ostream & out, ConstantDetails const& constantDetails)
{
    bool isExisting(false);
    isExisting = !constantDetails.name.empty();
    out << isExisting << endl;
    if(isExisting)
    {
        out << constantDetails.name << endl;
    }
    isExisting = !constantDetails.value.empty();
    out << isExisting << endl;
    if(isExisting)
    {
        out << constantDetails.value << endl;
    }
    isExisting = !constantDetails.description.empty();
    out << isExisting << endl;
    if(isExisting)
    {
        out << constantDetails.description << endl;
    }
    isExisting = !constantDetails.descriptionFromUser.empty();
    out << isExisting << endl;
    if(isExisting)
    {
        out << constantDetails.descriptionFromUser << endl;
    }
    return out;
}

istream& operator>>(istream & in, ConstantDetails& constantDetails)
{
    bool isExisting(false);
    in >> isExisting;
    if(isExisting)
    {
        while(in.peek()=='\r' || in.peek()=='\n') { in.ignore(1); }
        getline(in, constantDetails.name);
    }
    in >> isExisting;
    if(isExisting)
    {
        while(in.peek()=='\r' || in.peek()=='\n') { in.ignore(1); }
        getline(in, constantDetails.value);
    }
    in >> isExisting;
    if(isExisting)
    {
        while(in.peek()=='\r' || in.peek()=='\n') { in.ignore(1); }
        getline(in, constantDetails.description);
    }
    in >> isExisting;
    if(isExisting)
    {
        while(in.peek()=='\r' || in.peek()=='\n') { in.ignore(1); }
        getline(in, constantDetails.descriptionFromUser);
    }
    return in;
}

ostream& operator<<(ostream & out, EnumParameterDetails const& enumParameterDetails)
{
    bool isExisting(false);
    isExisting = !enumParameterDetails.name.empty();
    out << isExisting << endl;
    if(isExisting)
    {
        out << enumParameterDetails.name << endl;
    }
    isExisting = !enumParameterDetails.value.empty();
    out << isExisting << endl;
    if(isExisting)
    {
        out << enumParameterDetails.value << endl;
    }
    isExisting = !enumParameterDetails.description.empty();
    out << isExisting << endl;
    if(isExisting)
    {
        out << enumParameterDetails.description << endl;
    }
    isExisting = !enumParameterDetails.descriptionFromUser.empty();
    out << isExisting << endl;
    if(isExisting)
    {
        out << enumParameterDetails.descriptionFromUser << endl;
    }
    return out;
}

istream& operator>>(istream & in, EnumParameterDetails& enumParameterDetails)
{
    bool isExisting(false);
    in >> isExisting;
    if(isExisting)
    {
        while(in.peek()=='\r' || in.peek()=='\n') { in.ignore(1); }
        getline(in, enumParameterDetails.name);
    }
    in >> isExisting;
    if(isExisting)
    {
        while(in.peek()=='\r' || in.peek()=='\n') { in.ignore(1); }
        getline(in, enumParameterDetails.value);
    }
    in >> isExisting;
    if(isExisting)
    {
        while(in.peek()=='\r' || in.peek()=='\n') { in.ignore(1); }
        getline(in, enumParameterDetails.description);
    }
    in >> isExisting;
    if(isExisting)
    {
        while(in.peek()=='\r' || in.peek()=='\n') { in.ignore(1); }
        getline(in, enumParameterDetails.descriptionFromUser);
    }
    return in;
}

ostream& operator<<(ostream & out, EnumDetails const& enumDetails)
{
    bool isExisting(false);
    isExisting = !enumDetails.name.empty();
    out << isExisting << endl;
    if(isExisting)
    {
        out << enumDetails.name << endl;
    }
    out << enumDetails.parameters.size() << endl;
    for(EnumDetails::ParameterPair parameter : enumDetails.parameters)
    {
        out << parameter.second << endl;
    }
    return out;
}

istream& operator>>(istream & in, EnumDetails& enumDetails)
{
    bool isExisting(false);
    in >> isExisting;
    if(isExisting)
    {
        while(in.peek()=='\r' || in.peek()=='\n') { in.ignore(1); }
        getline(in, enumDetails.name);
    }
    unsigned int size(0);
    in >> size;
    for(unsigned int i=0; i<size; i++)
    {
        EnumParameterDetails enumParameterDetails;
        in >> enumParameterDetails;
        enumDetails.parameters.emplace(enumParameterDetails.name, enumParameterDetails);
    }
    return in;
}

ostream& operator<<(ostream & out, ParameterDetails const& parameterDetails)
{
    bool isExisting(false);
    isExisting = !parameterDetails.type.empty();
    out << isExisting << endl;
    if(isExisting)
    {
        out << parameterDetails.type << endl;
    }
    isExisting = !parameterDetails.name.empty();
    out << isExisting << endl;
    if(isExisting)
    {
        out << parameterDetails.name << endl;
    }
    isExisting = !parameterDetails.description.empty();
    out << isExisting << endl;
    if(isExisting)
    {
        out << parameterDetails.description << endl;
    }
    isExisting = !parameterDetails.descriptionFromUser.empty();
    out << isExisting << endl;
    if(isExisting)
    {
        out << parameterDetails.descriptionFromUser << endl;
    }
    out << parameterDetails.isAnArray << endl;
    isExisting = !parameterDetails.arraySize.empty();
    out << isExisting << endl;
    if(isExisting)
    {
        out << parameterDetails.arraySize;
    }
    return out;
}

istream& operator>>(istream & in, ParameterDetails& parameterDetails)
{
    bool isExisting(false);
    in >> isExisting;
    if(isExisting)
    {
        while(in.peek()=='\r' || in.peek()=='\n') { in.ignore(1); }
        getline(in, parameterDetails.type);
    }
    in >> isExisting;
    if(isExisting)
    {
        while(in.peek()=='\r' || in.peek()=='\n') { in.ignore(1); }
        getline(in, parameterDetails.name);
    }
    in >> isExisting;
    if(isExisting)
    {
        while(in.peek()=='\r' || in.peek()=='\n') { in.ignore(1); }
        getline(in, parameterDetails.description);
    }
    in >> isExisting;
    if(isExisting)
    {
        while(in.peek()=='\r' || in.peek()=='\n') { in.ignore(1); }
        getline(in, parameterDetails.descriptionFromUser);
    }
    in >> parameterDetails.isAnArray;
    in >> isExisting;
    if(isExisting)
    {
        while(in.peek()=='\r' || in.peek()=='\n') { in.ignore(1); }
        getline(in, parameterDetails.arraySize);
    }
    return in;
}

ostream& operator<<(ostream & out, StructureDetails const& structureDetails)
{
    bool isExisting(false);
    isExisting = !structureDetails.name.empty();
    out << isExisting << endl;
    if(isExisting)
    {
        out << structureDetails.name << endl;
    }
    out << structureDetails.parameters.size() << endl;
    for(std::pair<std::string, ParameterDetails> parameter : structureDetails.parameters)
    {
        out << parameter.second << endl;
    }
    return out;
}

istream& operator>>(istream & in, StructureDetails& structureDetails)
{
    bool isExisting(false);
    in >> isExisting;
    if(isExisting)
    {
        while(in.peek()=='\r' || in.peek()=='\n') { in.ignore(1); }
        getline(in, structureDetails.name);
    }
    unsigned int size(0);
    in >> size;
    for(unsigned int i=0; i<size; i++)
    {
        ParameterDetails parameterDetails;
        in >> parameterDetails;
        structureDetails.parameters.emplace(parameterDetails.name, parameterDetails);
    }
    return in;
}

SackReader::SackReader(string const& path)
    : m_path(path)
{
    m_path = AlbaLocalPathHandler(path).getFullPath();
}

void SackReader::checkAllFiles()
{
    AlbaLocalPathHandler pathHandler(m_path);
    ListOfPaths files;
    ListOfPaths directories;
    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);
    for(string const& file : files)
    {
        AlbaLocalPathHandler filePathHandler(file);
        string extension(filePathHandler.getExtension());
        if("c" == extension || "cpp" == extension || "h" == extension || "hpp" == extension || "sig" == extension)
        {
            m_fileToPathMap.emplace(filePathHandler.getFile(), filePathHandler.getFullPath());
        }
    }
}

void SackReader::saveDatabaseToFile(std::string const& path)
{
    ofstream fileStream(path);
    bool isExisting(false);
    isExisting = !m_path.empty();
    fileStream << isExisting << endl;
    if(isExisting)
    {
        fileStream << m_path << endl;
    }
    fileStream << m_fileToPathMap.size() << endl;
    for(FileToPathPair const& pair: m_fileToPathMap)
    {
        isExisting = !pair.first.empty();
        fileStream << isExisting << endl;
        if(isExisting)
        {
            fileStream << pair.first << endl;
        }
        isExisting = !pair.second.empty();
        fileStream << isExisting << endl;
        if(isExisting)
        {
            fileStream << pair.second << endl;
        }
    }
    fileStream << m_constantNameToConstantDetailsMap.size() << endl;
    for(ConstantNameToConstantDetailsPair const& pair: m_constantNameToConstantDetailsMap)
    {
        isExisting = !pair.first.empty();
        fileStream << isExisting << endl;
        if(isExisting)
        {
            fileStream << pair.first << endl;
        }
        fileStream << pair.second << endl;
    }
    fileStream << m_messageNameToStructureNameMap.size() << endl;
    for(MessageNameToStructureNamePair const& pair: m_messageNameToStructureNameMap)
    {
        isExisting = !pair.first.empty();
        fileStream << isExisting << endl;
        if(isExisting)
        {
            fileStream << pair.first << endl;
        }
        fileStream << pair.second << endl;
    }
    fileStream << m_structureNameToStructureDetailsMap.size() << endl;
    for(StructureNameToStructureDetailsPair const& pair: m_structureNameToStructureDetailsMap)
    {
        isExisting = !pair.first.empty();
        fileStream << isExisting << endl;
        if(isExisting)
        {
            fileStream << pair.first << endl;
        }
        fileStream << pair.second << endl;
    }
    fileStream << m_enumNameToEnumDetailsMap.size() << endl;
    for(EnumNameToEnumDetailsPair const& pair: m_enumNameToEnumDetailsMap)
    {
        isExisting = !pair.first.empty();
        fileStream << isExisting << endl;
        if(isExisting)
        {
            fileStream << pair.first << endl;
        }
        fileStream << pair.second << endl;
    }
}

void SackReader::loadDatabaseFromFile(std::string const& path)
{
    ifstream fileStream(path);
    bool isExisting(false);
    unsigned int size(0);
    fileStream >> isExisting;
    if(isExisting)
    {
        while(fileStream.peek()=='\r' || fileStream.peek()=='\n') { fileStream.ignore(1); }
        getline(fileStream, m_path);
    }

    fileStream >> size;
    for(unsigned int i=0; i<size; i++)
    {
        FileToPathPair pair;
        fileStream >> isExisting;
        if(isExisting)
        {
            while(fileStream.peek()=='\r' || fileStream.peek()=='\n') { fileStream.ignore(1); }
            getline(fileStream, pair.first);
        }
        fileStream >> isExisting;
        if(isExisting)
        {
            while(fileStream.peek()=='\r' || fileStream.peek()=='\n') { fileStream.ignore(1); }
            getline(fileStream, pair.second);
        }
        m_fileToPathMap.emplace(pair);
    }

    fileStream >> size;
    for(unsigned int i=0; i<size; i++)
    {
        ConstantNameToConstantDetailsPair pair;
        fileStream >> isExisting;
        if(isExisting)
        {
            while(fileStream.peek()=='\r' || fileStream.peek()=='\n') { fileStream.ignore(1); }
            getline(fileStream, pair.first);
        }
        fileStream >> pair.second;
        m_constantNameToConstantDetailsMap.emplace(pair);
    }

    fileStream >> size;
    for(unsigned int i=0; i<size; i++)
    {
        MessageNameToStructureNamePair pair;
        fileStream >> isExisting;
        if(isExisting)
        {
            while(fileStream.peek()=='\r' || fileStream.peek()=='\n') { fileStream.ignore(1); }
            getline(fileStream, pair.first);
        }
        fileStream >> pair.second;
        m_messageNameToStructureNameMap.emplace(pair);
    }

    fileStream >> size;
    for(unsigned int i=0; i<size; i++)
    {
        StructureNameToStructureDetailsPair pair;
        fileStream >> isExisting;
        if(isExisting)
        {
            while(fileStream.peek()=='\r' || fileStream.peek()=='\n') { fileStream.ignore(1); }
            getline(fileStream, pair.first);
        }
        fileStream >> pair.second;
        m_structureNameToStructureDetailsMap.emplace(pair);
    }

    fileStream >> size;
    for(unsigned int i=0; i<size; i++)
    {
        EnumNameToEnumDetailsPair pair;
        fileStream >> isExisting;
        if(isExisting)
        {
            while(fileStream.peek()=='\r' || fileStream.peek()=='\n') { fileStream.ignore(1); }
            getline(fileStream, pair.first);
        }
        fileStream >> pair.second;
        m_enumNameToEnumDetailsMap.emplace(pair);
    }
}

void SackReader::loadOamTcomMessage()
{
    readFile("MessageId_OamAtm.sig");
    readFile("MessageId_OamTcom.sig");
    readFile("Oam_Atm.h");
    readFile("oam_tcom.h");

    for(MessageNameToStructureNamePair const& pair: m_messageNameToStructureNameMap)
    {
        if(!pair.second.empty())
        {
            string structureFileName(pair.second+".h");
            readStructureRecursion(structureFileName);
        }
    }
}

void SackReader::readStructureRecursion(string const& structureFileName)
{
    ALBA_PRINT1(structureFileName);
    readFile(structureFileName);
    AlbaLocalPathHandler pathHandler(structureFileName);
    for(StructureDetails::ParameterPair const& parameterPair: m_structureNameToStructureDetailsMap[pathHandler.getFilenameOnly()].parameters)
    {
        if(!parameterPair.second.type.empty())
        {
            string structureFileNameInStructure(parameterPair.second.type+".h");
            ALBA_PRINT1(structureFileNameInStructure);
            readStructureRecursion(structureFileNameInStructure);
        }
    }

}

void SackReader::readFile(string const& fileName)
{
    //this should be a class

    string fileFullPath(getFileFullPath(fileName));
    ifstream fileStream(fileFullPath);
    AlbaLocalPathHandler fileFullPathHandler(fileFullPath);
    AlbaFileReader fileReader(fileStream);
    unsigned int state=0;
    unsigned int innerState=0;
    unsigned int paramDescriptionState=0;
    string partialString;
    bool isSigFile = fileFullPathHandler.getExtension() == "sig";
    ConstantDetails commentDetails;
    StructureDetails structureDetails;
    ParameterDetails parameterDetails;
    EnumDetails enumDetails;
    EnumParameterDetails enumParameterDetails;
    unsigned int commentState=0;
    string arraySize;

    string previousStructureName;
    string previousEnumName;
    while(fileReader.isNotFinished())
    {
        string line(getStringWithoutRedundantWhiteSpace(fileReader.getLineAndIgnoreWhiteSpaces()));
        strings tokens;
        splitToStrings<SplitStringType::WithDelimeters>(tokens, line, " ()[]{};\r\n:;/*/,");

        if(commentState==2)
        {
            commentState=0;
        }

        for(string const& token : tokens)
        {
            if(commentState==0)
            {
                if(token=="/")
                {
                    commentState=1;
                }
            }
            else if(commentState==1)
            {
                if(token=="/")
                {
                    commentState=2; // ->//
                }
                else if(token=="*")
                {
                    commentState=3; // ->/*
                }
                else
                {
                    commentState=0;
                }
            }
            else if(commentState==3)
            {
                if(token=="*")
                {
                    commentState=4; // -> *
                }
                else
                {
                    commentState=3;
                }
            }
            else if(commentState==4)
            {
                if(token=="/")
                {
                    commentState=0; // -> */
                }
                else if(token=="*")
                {
                    commentState=4; // -> **
                }
                else
                {
                    commentState=3;
                }
            }
            bool isInSingleLineComment = commentState==2;
            bool isInMultilineComment = commentState==3 || commentState==4;
            bool isNotInComment = !isInSingleLineComment && !isInMultilineComment;
            if(state==0) //Idle state
            {
                if(token == "#define" && isNotInComment)
                {
                    if(isSigFile)
                    {
                        state=3;
                    }
                    else
                    {
                        state=1;
                    }
                }
                else if(token == "@def" && isInMultilineComment)
                {
                    state=2;
                }
                else if(token == "struct" && isNotInComment)
                {
                    state=4;
                }
                else if(token == "@param" && isInMultilineComment)
                {
                    state=5;
                }
                else if(token == "@struct" && isInMultilineComment)
                {
                    state=6;
                }
                else if(token == "@enum" && isInMultilineComment)
                {
                    state=7;
                }
                else if(token == "enum" && isNotInComment)
                {
                    state=8;
                }
                innerState=0;
            }
            else if(state == 1) //#define
            {
                if(!isWhiteSpace(token) && isNotInComment)
                {
                    if(innerState==0)
                    {
                        commentDetails.name = token;
                        innerState=1;
                    }
                    else if(innerState==1)
                    {
                        commentDetails.value = token;
                        innerState=0;
                        state=0;
                        m_constantNameToConstantDetailsMap[commentDetails.name].name = commentDetails.name;
                        m_constantNameToConstantDetailsMap[commentDetails.name].value = commentDetails.value;
                    }
                }
            }
            else if(state == 2) //@def
            {
                if(token == "@def" || token == "Additional")
                {
                    m_constantNameToConstantDetailsMap[commentDetails.name].name = commentDetails.name;
                    m_constantNameToConstantDetailsMap[commentDetails.name].description = getStringWithoutRedundantWhiteSpace(partialString);
                    partialString.clear();
                    innerState=0;
                    if(token == "Additional")
                    {
                        state=0;
                    }
                }
                else if(innerState==0)
                {
                    if(!isWhiteSpace(token))
                    {
                        commentDetails.name = token;
                        innerState=1;
                    }
                }
                else if(innerState==1)
                {
                    if(":" == token)
                    {
                        innerState=2;
                        partialString.clear();
                    }
                }
                else if(innerState==2)
                {
                    if("*" != token)
                    {
                        partialString+=token;
                    }
                }
            }
            else if(state == 3) //#define in sig file
            {
                if(!isWhiteSpace(token) && isNotInComment)
                {
                    if(innerState==0)
                    {
                        m_messageNameToStructureNameMap.emplace(token, getStringInBetweenTwoStrings(line, "/* !- SIGNO(struct ", ") -! */"));
                        state=0;
                        innerState=0;
                        break;
                    }
                }
            }
            else if(state == 4) //struct
            {
                if(!isWhiteSpace(token) && isNotInComment && token!="/")
                {
                    if(innerState==0)
                    {
                        structureDetails.name = token;
                        innerState=1;
                    }
                    else if(innerState==1)
                    {
                        if("{" == token)
                        {
                            innerState=2;
                        }
                        else if(";" == token)
                        {
                            structureDetails.clear();
                            state=0;
                            innerState=0;
                        }
                    }
                    else if(innerState>=2)
                    {
                        if("MESSAGEHEADER" == token)
                        {
                            structureDetails.isMessage = true;
                            break;
                        }
                        else if("}" == token)
                        {
                            previousStructureName=structureDetails.name;
                            structureDetails.clear();
                            state = 0;
                            innerState=0;
                        }
                        else if(";" == token)
                        {
                            innerState=2;
                            if(!parameterDetails.name.empty())
                            {
                                m_structureNameToStructureDetailsMap[structureDetails.name].parameters[parameterDetails.name].name = parameterDetails.name;
                                m_structureNameToStructureDetailsMap[structureDetails.name].parameters[parameterDetails.name].type = parameterDetails.type;
                                if(!arraySize.empty())
                                {
                                    m_structureNameToStructureDetailsMap[structureDetails.name].parameters[parameterDetails.name].isAnArray = true;
                                    m_structureNameToStructureDetailsMap[structureDetails.name].parameters[parameterDetails.name].arraySize = arraySize;
                                    arraySize.clear();
                                }
                                parameterDetails.clear();
                            }
                        }
                        else
                        {
                            if(innerState==2)
                            {
                                parameterDetails.type = token;
                                innerState = 3;
                            }
                            else if(innerState==3)
                            {
                                parameterDetails.name = token;
                                innerState = 4;
                            }
                            else if(innerState==4)
                            {
                                if("[" == token)
                                {
                                    innerState = 5;
                                }
                            }
                            else if(innerState==5)
                            {
                                if("]" == token)
                                {
                                    arraySize = partialString;
                                    partialString.clear();
                                    innerState = 6;
                                }
                                else
                                {
                                    partialString += token;
                                }
                            }
                        }
                    }
                }
            }
            else if(state == 5) //@param
            {
                if(token == "@param" || token == "Additional")
                {
                    if(paramDescriptionState==1)
                    {
                        m_structureNameToStructureDetailsMap[previousStructureName].parameters[parameterDetails.name].description = getStringWithoutRedundantWhiteSpace(partialString);
                    }
                    else if(paramDescriptionState==2)
                    {
                        m_enumNameToEnumDetailsMap[previousEnumName].parameters[parameterDetails.name].description = getStringWithoutRedundantWhiteSpace(partialString);
                    }

                    partialString.clear();
                    innerState=0;
                    if(token == "Additional")
                    {
                        paramDescriptionState=0;
                        state=0;
                    }
                }
                else if(innerState==0)
                {
                    if(!isWhiteSpace(token))
                    {
                        parameterDetails.name = token;
                        innerState=1;
                    }
                }
                else if(innerState==1)
                {
                    if(":" == token)
                    {
                        innerState=2;
                        partialString.clear();
                    }
                }
                else if(innerState==2)
                {
                    if("*" != token)
                    {
                        partialString+=token;
                    }
                }
            }
            else if(state == 6) //@struct
            {
                if(!isWhiteSpace(token) && isInMultilineComment)
                {
                    previousStructureName = token;
                    state=0;
                    paramDescriptionState=1;
                }
            }
            else if(state == 7) //@enum
            {
                if(!isWhiteSpace(token) && isInMultilineComment)
                {
                    previousEnumName = token;
                    state=0;
                    paramDescriptionState=2;
                }
            }
            else if(state == 8) //enum
            {
                if(!isWhiteSpace(token) && isNotInComment && token!="/")
                {
                    if(innerState==0)
                    {
                        enumDetails.name = token;
                        innerState=1;
                    }
                    else if(innerState==1)
                    {
                        if("{" == token)
                        {
                            innerState=2;
                        }
                        else if(";" == token)
                        {
                            enumDetails.clear();
                            state=0;
                            innerState=0;
                        }
                    }
                    else if(innerState>=2)
                    {
                        if("}" == token || "," == token)
                        {
                            innerState=2;
                            if(!enumParameterDetails.name.empty())
                            {
                                m_enumNameToEnumDetailsMap[enumDetails.name].parameters[enumParameterDetails.name].name = enumParameterDetails.name;
                                m_enumNameToEnumDetailsMap[enumDetails.name].parameters[enumParameterDetails.name].value = enumParameterDetails.value;
                                m_enumNameToEnumDetailsMap[enumDetails.name].parameters[enumParameterDetails.name].description = enumParameterDetails.description;
                                enumParameterDetails.clear();
                            }
                            if("}" == token)
                            {
                                previousEnumName=enumDetails.name;
                                enumDetails.clear();
                                state = 0;
                                innerState=0;
                            }
                        }
                        else
                        {
                            if(innerState==2)
                            {
                                enumParameterDetails.name = token;
                                innerState = 3;
                            }
                            else if(innerState==3)
                            {
                                if("=" == token)
                                {
                                    innerState = 4;
                                }
                            }
                            else if(innerState==4)
                            {
                                enumParameterDetails.value = token;
                                innerState = 5;
                            }
                        }
                    }
                }
            }
        }
    }
}

string SackReader::getFileFullPath(string const& fileName) const
{
    string result;
    if(m_fileToPathMap.find(fileName)!=m_fileToPathMap.cend())
    {
        result = m_fileToPathMap.at(fileName);
    }
    return result;
}

ConstantDetails SackReader::getConstantDetails(string const& constantName) const
{
    ConstantDetails result;
    if(m_constantNameToConstantDetailsMap.find(constantName)!=m_constantNameToConstantDetailsMap.cend())
    {
        result = m_constantNameToConstantDetailsMap.at(constantName);
    }
    return result;
}

string SackReader::getMessageStructure(string const& messageName) const
{
    string result;
    if(m_messageNameToStructureNameMap.find(messageName)!=m_messageNameToStructureNameMap.cend())
    {
        result = m_messageNameToStructureNameMap.at(messageName);
    }
    return result;
}

ParameterDetails SackReader::getParameterDetails(string const& structureName, string const& parameterName) const
{
    ParameterDetails result;
    if(m_structureNameToStructureDetailsMap.find(structureName)!=m_structureNameToStructureDetailsMap.cend())
    {
        StructureDetails const & structureDetails = m_structureNameToStructureDetailsMap.at(structureName);
        StructureDetails::ParameterMap const & parameters(structureDetails.parameters);
        if(parameters.find(parameterName)!=parameters.cend())
        {
            result = parameters.at(parameterName);
        }
    }
    return result;
}

EnumParameterDetails SackReader::getEnumParameterDetails(string const& enumName, string const& enumParameterName) const
{
    EnumParameterDetails result;
    if(m_enumNameToEnumDetailsMap.find(enumName)!=m_enumNameToEnumDetailsMap.cend())
    {
        EnumDetails const & enumDetails = m_enumNameToEnumDetailsMap.at(enumName);
        EnumDetails::ParameterMap const & parameters(enumDetails.parameters);
        if(parameters.find(enumParameterName)!=parameters.cend())
        {
            result = parameters.at(enumParameterName);
        }
    }
    return result;
}



}