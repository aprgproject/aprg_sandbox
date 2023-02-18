#include "Findings.hpp"

#include <iostream>
#include <string>

using namespace std;

namespace codeReview
{

MultiMapOfFindings& Findings::getMultiMapOfFindingsReference()
{
    return m_findings;
}

void Findings::printFindings(ostream& outputStream)
{
    //output iterator?
    for (auto& finding : m_findings)
    {
        outputStream<<"Finding "<<m_fileName<<"["<<finding.first<<"] -> "<<finding.second<<"\n";
    }
}
void Findings::printFindings(ostream& outputStream, string const& details)
{
    for (auto& finding : m_findings)
    {
        if(details == finding.second.getDetails())
        {
            outputStream<<"Finding "<<m_fileName<<"["<<finding.first<<"] -> "<<finding.second<<"\n";
        }
    }
}
void Findings::addFinding(unsigned int const lineNumber, string const& fileLocator, string const& content)
{
    m_findings.emplace(lineNumber, Finding(fileLocator, content));}

void Findings::addFinding(unsigned int const lineNumber, string const& fileLocator, string const& content, string const& locator)
{
    m_findings.emplace(lineNumber, Finding(fileLocator, content, locator));
}

void Findings::copyFindings(Findings& findings){
    for (FindingsPair finding : findings.m_findings)
    {
        m_findings.emplace(finding.first, finding.second);
    }
}

void Findings::clear()
{
    m_findings.clear();
}

void Findings::setFileName(string const& fileName)
{
    m_fileName = fileName;
}

}
