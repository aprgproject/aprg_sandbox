#include "UserIdentifiers.hpp"

#include <String/AlbaStringHelper.hpp>

using namespace std;

namespace alba
{

UserIdentifiers::UserIdentifiers()
{}

UserIdentifiers::UserIdentifiers(std::string const& lineInLogs)
{
    saveUserIndentfiers(lineInLogs);
}

void UserIdentifiers::saveUserIndentfiers(std::string const& lineInLogs)
{
    saveNbccId(lineInLogs);
    saveCrnccId(lineInLogs);
    saveTransactionId(lineInLogs);
}

bool UserIdentifiers::operator<(UserIdentifiers const& userIdentifiers) const
{
    bool result(false);
    if(m_nbccIdOptional && userIdentifiers.m_nbccIdOptional)
    {
        result = result || (m_nbccIdOptional.get() < userIdentifiers.m_nbccIdOptional.get());
    }
    else if(m_crnccIdOptional && userIdentifiers.m_crnccIdOptional)
    {
        result = result || (m_crnccIdOptional.get() < userIdentifiers.m_crnccIdOptional.get());
    }
    else if(m_transactionIdOptional && userIdentifiers.m_transactionIdOptional)
    {
        result = result || (m_transactionIdOptional.get() < userIdentifiers.m_transactionIdOptional.get());
    }
    return result;
}

bool UserIdentifiers::operator==(UserIdentifiers const& userIdentifiers) const
{
    bool result(false);
    if(m_nbccIdOptional.hasContent() == userIdentifiers.m_nbccIdOptional.hasContent()
            && m_crnccIdOptional.hasContent() == userIdentifiers.m_crnccIdOptional.hasContent()
            && m_transactionIdOptional.hasContent() == userIdentifiers.m_transactionIdOptional.hasContent())
    {
        if(m_nbccIdOptional && userIdentifiers.m_nbccIdOptional)
        {
            result = result || (m_nbccIdOptional.get() == userIdentifiers.m_nbccIdOptional.get());
        }
        if(m_crnccIdOptional && userIdentifiers.m_crnccIdOptional)
        {
            result = result || (m_crnccIdOptional.get() == userIdentifiers.m_crnccIdOptional.get());
        }
        if(m_transactionIdOptional && userIdentifiers.m_transactionIdOptional)
        {
            result = result || (m_transactionIdOptional.get() == userIdentifiers.m_transactionIdOptional.get());
        }
    }
    return result;
}


void UserIdentifiers::saveNbccId(std::string const& lineInLogs)
{
    unsigned int nbccid = stringHelper::convertStringToNumber<unsigned int>(stringHelper::getNumberAfterThisString(lineInLogs, "nbccid: "));
    unsigned int nbccId = stringHelper::convertStringToNumber<unsigned int>(stringHelper::getNumberAfterThisString(lineInLogs, "nbccId: "));
    if(nbccid>0)
    {
        m_nbccIdOptional.setValue(nbccid);
    }
    if(nbccId>0)
    {
        m_nbccIdOptional.setValue(nbccId);
    }
}

void UserIdentifiers::saveCrnccId(std::string const& lineInLogs)
{
    unsigned int crncId = stringHelper::convertStringToNumber<unsigned int>(stringHelper::getNumberAfterThisString(lineInLogs, "crncId: "));
    unsigned int crnccId = stringHelper::convertStringToNumber<unsigned int>(stringHelper::getNumberAfterThisString(lineInLogs, "crnccId: "));
    if(crncId>0)
    {
        m_crnccIdOptional.setValue(crncId);
    }
    if(crnccId>0)
    {
        m_crnccIdOptional.setValue(crnccId);
    }
}

void UserIdentifiers::saveTransactionId(std::string const& lineInLogs)
{
    unsigned int transactionId = stringHelper::convertStringToNumber<int>(stringHelper::getNumberAfterThisString(lineInLogs, "transactionId: "));
    if(transactionId>0)
    {
        m_transactionIdOptional.setValue(transactionId);
    }
}

unsigned int UserIdentifiers::getNbccId() const
{
    unsigned int result(0);
    if(m_nbccIdOptional)
    {
        result = m_nbccIdOptional.get();
    }
    return result;
}

unsigned int UserIdentifiers::getCrnccId() const
{
    unsigned int result(0);
    if(m_crnccIdOptional)
    {
        result = m_crnccIdOptional.get();
    }
    return result;
}

unsigned int UserIdentifiers::getTransactionId() const
{
    unsigned int result(0);
    if(m_transactionIdOptional)
    {
        result = m_transactionIdOptional.get();
    }
    return result;
}

}
