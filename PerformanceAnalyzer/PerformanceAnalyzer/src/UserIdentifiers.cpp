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
    bool result(true);
    unsigned int nbccId1(getNbccId());
    unsigned int nbccId2(userIdentifiers.getNbccId());
    unsigned int crnccId1(getCrnccId());
    unsigned int crnccId2(userIdentifiers.getCrnccId());
    unsigned int transactionId1(getTransactionId());
    unsigned int transactionId2(userIdentifiers.getTransactionId());
    if(nbccId1==nbccId2)
    {
        if(crnccId1==crnccId2)
        {
            result = transactionId1<transactionId2;
        }
        else
        {
            result = crnccId1<crnccId2;
        }
    }
    else
    {
        result = nbccId1<nbccId2;
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
