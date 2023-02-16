#pragma once

#include <optional>
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
    std::optional<unsigned int> m_nbccIdOptional;
    std::optional<unsigned int> m_crnccIdOptional;
    std::optional<unsigned int> m_transactionIdOptional;
};

}
