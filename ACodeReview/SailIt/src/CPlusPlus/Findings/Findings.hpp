#pragma once

#include "Finding.hpp"

#include <map>
#include <string>

using std::string;
using std::multimap;
using std::pair;

namespace codeReview
{
typedef multimap<int, Finding> MultiMapOfFindings;
typedef pair<int, Finding> FindingsPair;

class Findings
{
public:

    MultiMapOfFindings& getMultiMapOfFindingsReference();

    void printFindings(ostream& outputStream);
    void printFindings(ostream& outputStream, string const& details);

    void addFinding(unsigned int const lineNumber, string const& fileLocator, string const& content);
    void addFinding(unsigned int const lineNumber, string const& fileLocator, string const& content, string const& locator);
    void copyFindings(Findings& findings);
    void clear();
    void setFileName(string const& fileName);

private:
    MultiMapOfFindings m_findings;
    string m_fileName;
};

}
