#include <TwoDimensionsStatistics.hpp>

#include <algorithm>
#include <cmath>

namespace alba
{

TwoDimensionsStatistics::LineModel TwoDimensionsStatistics::calculateLineModelUsingLeastSquares(Samples const& samples)
{
    bool isDifferenceForXNotZero(false);
    bool isDifferenceForYNotZero(false);
    LineModel lineModel;
    Sample mean(Statistics::calculateMean(samples));
    for(Sample const& sample : samples)
    {
        double differenceInX(sample.getValueAt(0)-mean.getValueAt(0));
        double differenceInY(sample.getValueAt(1)-mean.getValueAt(1));
        isDifferenceForXNotZero = (differenceInX!=0)|isDifferenceForXNotZero;
        isDifferenceForYNotZero = (differenceInY!=0)|isDifferenceForYNotZero;
        lineModel.aCoefficient += differenceInX*differenceInY;
        lineModel.bCoefficient += differenceInX*differenceInX;
    }
    if(!isDifferenceForXNotZero && !isDifferenceForYNotZero)
    {
        lineModel.aCoefficient = 0;
        lineModel.bCoefficient = 0;
    }
    else if(!isDifferenceForXNotZero)
    {
        lineModel.aCoefficient = 1;
        lineModel.bCoefficient = 0;
    }
    else if(!isDifferenceForYNotZero)
    {
        lineModel.aCoefficient = 0;
        lineModel.bCoefficient = 1;
    }
    else
    {
        lineModel.aCoefficient *= -1/lineModel.bCoefficient;
        lineModel.bCoefficient = 1;
    }
    lineModel.cCoefficient = -1*(lineModel.bCoefficient*mean.getValueAt(1) + lineModel.aCoefficient*mean.getValueAt(0));
    return lineModel;
}

double TwoDimensionsStatistics::calculateSquareError(Sample const& sample, LineModel const& lineModel)
{
    return pow(lineModel.aCoefficient*sample.getValueAt(0) + lineModel.bCoefficient*sample.getValueAt(1) + lineModel.cCoefficient, 2);
}

void TwoDimensionsStatistics::sortSamplesBySquareError(Samples & samples, LineModel const& lineModel)
{
    std::sort(samples.begin(), samples.end(),[&](Sample const& sample1, Sample const& sample2)
    {
        return calculateSquareError(sample1, lineModel) < calculateSquareError(sample2, lineModel);
    });
}

}
