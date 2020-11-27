#pragma once

#include <DataSample.hpp>
#include <DataStatistics.hpp>

namespace alba
{

template <typename DataType>
class TwoDimensionsStatistics
{
public:
    using Sample = DataSample<DataType, 2>;
    using Statistics = DataStatistics<DataType, 2>;
    using Samples = std::vector<Sample>;
    struct LineModel
    {
        DataType aCoefficient;
        DataType bCoefficient;
        DataType cCoefficient;
        LineModel()
            : aCoefficient(0)
            , bCoefficient(0)
            , cCoefficient(0)
        {}
    };

    static LineModel calculateLineModelUsingLeastSquares(Samples const& samples)
    {
        LineModel line;
        Sample mean(Statistics::calculateMean(samples));
        for(Sample const& sample : samples)
        {
            DataType differenceInX(sample.getValueAt(0)-mean.getValueAt(0));
            DataType differenceInY(sample.getValueAt(1)-mean.getValueAt(1));
            if(differenceInX == 0)
            {
                line.aCoefficient += differenceInY;
                line.bCoefficient += differenceInX;
            }
            else
            {
                line.aCoefficient += differenceInX*differenceInY;
                line.bCoefficient += differenceInX*differenceInX;
            }
        }
        line.aCoefficient *= -1;
        line.cCoefficient = mean.getValueAt(1) - line.aCoefficient*mean.getValueAt(0);
        return line;
    }

};

}
