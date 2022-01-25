#include <Math/AlbaMathHelper.hpp>
#include <TwoDimensionsStatistics.hpp>

#include <algorithm>
#include <cmath>

namespace alba
{

TwoDimensionsStatistics::LineModel TwoDimensionsStatistics::calculateLineModelUsingLeastSquares(Samples const& samples)
{
    bool areAllDifferenceForXZero(true);
    bool areAllDifferenceForYZero(true);
    double xMinusXmeanSquared(0); //Xi-mean(X)
    double yMinusYmeanSquared(0); //Yi-mean(Y)
    double xMinusXmeanTimesYMinusYmean(0);// (Xi-mean(X))*(Yi-mean(Y))
    LineModel lineModel;
    Statistics statistics(samples);
    Sample mean(statistics.getMean());    for(Sample const& sample : samples)
    {
        double differenceInMeanInX(sample.getValueAt(0)-mean.getValueAt(0));
        double differenceInMeanInY(sample.getValueAt(1)-mean.getValueAt(1));
        areAllDifferenceForXZero = areAllDifferenceForXZero && (differenceInMeanInX==0);
        areAllDifferenceForYZero = areAllDifferenceForYZero && (differenceInMeanInY==0);
        xMinusXmeanSquared += (differenceInMeanInX*differenceInMeanInX);
        yMinusYmeanSquared += (differenceInMeanInY*differenceInMeanInY);
        xMinusXmeanTimesYMinusYmean += differenceInMeanInX*differenceInMeanInY;
    }
    if(areAllDifferenceForXZero && areAllDifferenceForYZero)
    {
        lineModel.aCoefficient = 0;
        lineModel.bCoefficient = 0;
    }
    else if(areAllDifferenceForXZero)
    {
        lineModel.aCoefficient = 1;
        lineModel.bCoefficient = 0;
    }
    else if(areAllDifferenceForYZero)
    {
        lineModel.aCoefficient = 0;
        lineModel.bCoefficient = 1;    }
    else
    {
        double slopeInX(xMinusXmeanTimesYMinusYmean/xMinusXmeanSquared);        double slopeInY(xMinusXmeanTimesYMinusYmean/yMinusYmeanSquared);
        if(mathHelper::getAbsoluteValue(slopeInY)<mathHelper::getAbsoluteValue(slopeInX))
        {
            lineModel.aCoefficient = 1;
            lineModel.bCoefficient = -slopeInY;
        }
        else
        {
            lineModel.aCoefficient = -slopeInX;
            lineModel.bCoefficient = 1;
        }
    }
    lineModel.cCoefficient = -1*(lineModel.aCoefficient*mean.getValueAt(0)+lineModel.bCoefficient*mean.getValueAt(1));
    return lineModel;
}

double TwoDimensionsStatistics::calculateSquareError(Sample const& sample, LineModel const& lineModel)
{
    return pow(lineModel.aCoefficient*sample.getValueAt(0) + lineModel.bCoefficient*sample.getValueAt(1) + lineModel.cCoefficient, 2);
}

TwoDimensionsStatistics::ValueToSampleMultimap TwoDimensionsStatistics::getSquareErrorToSampleMultimap(Samples & samples, LineModel const& lineModel)
{
    ValueToSampleMultimap squareErrorAndSampleMultimap;
    for(Sample const& sample : samples)
    {
        squareErrorAndSampleMultimap.emplace(calculateSquareError(sample, lineModel), sample);
    }
    return squareErrorAndSampleMultimap;
}

}
