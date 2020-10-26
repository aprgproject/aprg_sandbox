#pragma once

#include <iostream>
#include <string>

using std::ostream;
using std::string;

namespace codeReview
{

class Finding
{
public:
    Finding(string const& fileLocator, string const& details)
        : m_fileLocator(fileLocator)
        , m_details(details)
        , m_hasTermsLocator(false)
    {}
    Finding(string const& fileLocator, string const& details, string const& locator)
        : m_fileLocator(fileLocator)
        , m_details(details)
        , m_termsLocator(locator)
        , m_hasTermsLocator(true)
    {}

    string getDetails() const
    {
        return m_details;
    }

    string getLocator() const
    {
        return m_termsLocator;
    }

    friend ostream & operator<<(ostream & out, Finding const& finding)
    {
        if(finding.m_hasTermsLocator)
        {
            return (out << "||" << finding.m_details << "||"
                    << "   Locator:||" << finding.m_termsLocator << "||"
                    << "   FileLocator:||" << finding.m_fileLocator << "||");
        }
        else
        {
            return (out << "||" << finding.m_details << "||"
                    << "   Locator:||" << finding.m_termsLocator << "||");
        }
    }
private:
    string m_fileLocator;
    string m_details;
    string m_termsLocator;
    bool m_hasTermsLocator;
};

}


