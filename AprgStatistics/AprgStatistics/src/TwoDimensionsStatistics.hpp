#pragma once

#include <DataSample.hpp>
#include <DataStatistics.hpp>

namespace alba
{

namespace TwoDimensionsStatistics
{
    using Sample = DataSample<2>;
    using Statistics = DataStatistics<2>;
    using Samples = std::vector<Sample>;
    struct LineModel
    {
        double aCoefficient;
        double bCoefficient;
        double cCoefficient;
        LineModel()  : aCoefficient(0) , bCoefficient(0) , cCoefficient(0) {}
        LineModel(double a, double b, double c)  : aCoefficient(a) , bCoefficient(b) , cCoefficient(c) {}
    };

    LineModel calculateLineModelUsingLeastSquares(Samples const& samples);
    double calculateSquareError(Sample const& sample, LineModel const& lineModel);
    void sortSamplesBySquareError(Samples & samples, LineModel const& lineModel);
}

}
