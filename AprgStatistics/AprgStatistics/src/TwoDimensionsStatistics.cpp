#include <TwoDimensionsStatistics.hpp>

#include <Math/AlbaMathHelper.hpp>

#include <algorithm>
#include <cmath>

#include <Debug/AlbaDebug.hpp>

namespace alba
{

TwoDimensionsStatistics::LineModel TwoDimensionsStatistics::calculateLineModelUsingLeastSquares(Samples const& samples)
{
    bool isDifferenceForXNotZero(false);
    bool isDifferenceForYNotZero(false);
    double xMinusXmeanSquared(0); //Xi-mean(X)
    double yMinusYmeanSquared(0); //Yi-mean(Y)
    double xMinusXmeanTimesYMinusYmean(0);// (Xi-mean(X))*(Yi-mean(Y))

    LineModel lineModel;
    Sample mean(Statistics::calculateMean(samples));
    for(Sample const& sample : samples)
    {
        double differenceInMeanInX(sample.getValueAt(0)-mean.getValueAt(0));
        double differenceInMeanInY(sample.getValueAt(1)-mean.getValueAt(1));
        isDifferenceForXNotZero = (differenceInMeanInX!=0)|isDifferenceForXNotZero;
        isDifferenceForYNotZero = (differenceInMeanInY!=0)|isDifferenceForYNotZero;
        xMinusXmeanSquared += (differenceInMeanInX*differenceInMeanInX);
        yMinusYmeanSquared += (differenceInMeanInY*differenceInMeanInY);
        xMinusXmeanTimesYMinusYmean += differenceInMeanInX*differenceInMeanInY;
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
        double slopeInX(xMinusXmeanTimesYMinusYmean/xMinusXmeanSquared);
        double slopeInY(xMinusXmeanTimesYMinusYmean/yMinusYmeanSquared);
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

void TwoDimensionsStatistics::sortSamplesBySquareError(Samples & samples, LineModel const& lineModel)
{
    std::sort(samples.begin(), samples.end(),[&](Sample const& sample1, Sample const& sample2)
    {
        return calculateSquareError(sample1, lineModel) < calculateSquareError(sample2, lineModel);
    });
}

}
