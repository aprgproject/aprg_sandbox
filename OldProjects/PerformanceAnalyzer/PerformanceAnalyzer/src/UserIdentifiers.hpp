#pragma once

#include <Common/Optional/AlbaOptional.hpp>

#include <string>

namespace alba
{

struct UserIdentifiers
{
    UserIdentifiers();
    UserIdentifiers(std::string const& lineInLogs);
    void saveUserIndentfiers(std::string const& lineInLogs);
    bool operator<(UserIdentifiers const& userIdentifiers) const;
    unsigned int getNbccId() const;
    unsigned int getCrnccId() const;
    unsigned int getTransactionId() const;
private:
    void saveNbccId(std::string const& lineInLogs);
    void saveCrnccId(std::string const& lineInLogs);
    void saveTransactionId(std::string const& lineInLogs);
    AlbaOptional<unsigned int> m_nbccIdOptional;
    AlbaOptional<unsigned int> m_crnccIdOptional;
    AlbaOptional<unsigned int> m_transactionIdOptional;
};

}
