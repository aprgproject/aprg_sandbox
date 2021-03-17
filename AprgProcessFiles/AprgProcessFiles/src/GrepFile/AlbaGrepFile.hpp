#pragma once

#include <GrepStringEvaluator/AlbaGrepStringEvaluator.hpp>
#include <Optional/AlbaOptional.hpp>

#include <functional>
#include <string>

namespace alba
{

class AlbaGrepFile
{
public:
    using UpdateFunctionWithPercentage = std::function<void(double)>;

    AlbaGrepFile(std::string const& lineCondition);
    AlbaGrepFile(std::string const& lineCondition, UpdateFunctionWithPercentage const& function);
    bool isOutputFileWritten() const;
    void processFile(std::string const& inputFilePath, std::string const& outputFilePath);
    AlbaGrepStringEvaluator& getGrepEvaluator();
private:
    void updateAfterOneIteration(double const percentage);
    bool m_isOutputFileWritten;
    AlbaGrepStringEvaluator m_lineGrepEvaluator;
    AlbaOptional<UpdateFunctionWithPercentage const&> m_updateFunctionAfterOneIterationOptional;
};

}
