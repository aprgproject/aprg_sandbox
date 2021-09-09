#include "PidSimulator.hpp"

#include <AprgGraph.hpp>
#include <Bitmap/Bitmap.hpp>
#include <Math/AlbaMathHelper.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>

#include <algorithm>
#include <cmath>
#include <iostream>

using namespace alba::AprgBitmap;
using namespace alba::mathHelper;
using namespace alba::TwoDimensions;
using namespace std;

namespace alba
{

PidSimulator::PidSimulator(stringHelper::strings const& argumentsInMain)
    : m_conf(argumentsInMain)
    , m_xMagnificationToGraph(0)
    , m_yMagnificationToGraph(0)
    , m_xOffsetToGraph(0)
    , m_yOffsetToGraph(0)
    , m_xGridInterval(0)
    , m_yGridInterval(0)
    , m_inputSample()
    , m_randomizer()
{}

double PidSimulator::calculatePid(double const input, double const target)
{
    //https://en.wikipedia.org/wiki/PID_controller

    static double integral = 0;
    static double derivative = 0;
    static double lastError = 0;

    double error = target - input;
    double pwm = 0;

    integral += error;
    derivative = error - lastError;
    pwm = (m_conf.kd * error) + (m_conf.ki * integral) + (m_conf.kp * derivative);

    lastError = error;

    return pwm;
}

void PidSimulator::generateInput()
{
    if("sine" == m_conf.inputType)
    {
        generateSineWavesForInput();
    }
    else if("triangle" == m_conf.inputType)
    {
        generateTriangleWavesForInput();
    }
    else if("stepUp" == m_conf.inputType)
    {
        generateStepUpForInput();
    }
    else if("stepDown" == m_conf.inputType)
    {
        generateStepDownForInput();
    }
    else if("random" == m_conf.inputType)
    {
        generateRandomForInput();
    }
}

void PidSimulator::generateTriangleWavesForInput()
{
    for(unsigned int j = 0; j < m_conf.numberOfLoopsOfPeriodicInputDemand; j++)
    {
        //go up
        unsigned int partOfSamples = m_conf.numberOfSamplesOfInputDemandInOnePeriod/2;
        double slope = static_cast<double>(m_conf.amplitudeOfInputDemand)/partOfSamples;
        for (unsigned int i = 0; i < partOfSamples; i++)
        {
            m_inputSample.emplace_back((slope*i) + m_conf.addedOffsetOfInputDemand);
        }
        //go down
        for (unsigned int i = 0; i < partOfSamples; i++)
        {
            m_inputSample.emplace_back(m_conf.amplitudeOfInputDemand -(slope*i) + m_conf.addedOffsetOfInputDemand);
        }
    }
}

void PidSimulator::generateSineWavesForInput()
{
    for(unsigned int j = 0; j < m_conf.numberOfLoopsOfPeriodicInputDemand; j++)
    {
        double angle = 0.0;
        for (unsigned int i = 0; i < m_conf.numberOfSamplesOfInputDemandInOnePeriod; i++)
        {
            m_inputSample.emplace_back((m_conf.amplitudeOfInputDemand * sin(angle)) + m_conf.addedOffsetOfInputDemand);
            angle += (2 * getPi()) / m_conf.numberOfSamplesOfInputDemandInOnePeriod;
        }
    }
}

void PidSimulator::generateStepUpForInput()
{
    for(unsigned int j = 0; j < m_conf.numberOfLoopsOfPeriodicInputDemand; j++)
    {
        //minimum
        unsigned int partOfSamples = m_conf.numberOfSamplesOfInputDemandInOnePeriod/2;
        for (unsigned int i = 0; i < partOfSamples; i++)
        {
            m_inputSample.emplace_back(m_conf.addedOffsetOfInputDemand);
        }

        //maximum
        for (unsigned int i = 0; i < partOfSamples; i++)
        {
            m_inputSample.emplace_back(m_conf.amplitudeOfInputDemand+m_conf.addedOffsetOfInputDemand);
        }
    }
}

void PidSimulator::generateStepDownForInput()
{
    for(unsigned int j = 0; j < m_conf.numberOfLoopsOfPeriodicInputDemand; j++)
    {
        //maximum
        unsigned int partOfSamples = m_conf.numberOfSamplesOfInputDemandInOnePeriod/2;
        for (unsigned int i = 0; i < partOfSamples; i++)
        {
            m_inputSample.emplace_back(m_conf.amplitudeOfInputDemand+m_conf.addedOffsetOfInputDemand);
        }

        //minimum
        for (unsigned int i = 0; i < partOfSamples; i++)
        {
            m_inputSample.emplace_back(m_conf.addedOffsetOfInputDemand);
        }

    }
}

void PidSimulator::generateRandomForInput()
{
    m_randomizer.resetRandomSeed();
    for(unsigned int j = 0; j < m_conf.numberOfLoopsOfPeriodicInputDemand; j++)
    {
        for (unsigned int i = 0; i < m_conf.numberOfSamplesOfInputDemandInOnePeriod; i++)
        {
            m_inputSample.emplace_back(m_randomizer.getRandomValueInUniformDistribution(0, static_cast<int>(m_conf.amplitudeOfInputDemand)) + m_conf.addedOffsetOfInputDemand);
        }
    }
}

double PidSimulator::computeFromMachsModel(double const inputDemandSample, double const psuedoMaxTxPower, double & adjustedDemand)
{
    double result(0);
    if("MachsModel1" == m_conf.machsModelType)
    {
        result = computeFromMachsModel1(inputDemandSample, psuedoMaxTxPower, adjustedDemand);
    }
    else if("MachsModel2" == m_conf.machsModelType)
    {
        result = computeFromMachsModel2(inputDemandSample, psuedoMaxTxPower, adjustedDemand);
    }
    return result;
}

double PidSimulator::computeFromMachsModel1(double const inputDemandSample, double const psuedoMaxTxPower, double & adjustedDemand)
{
    double newDemand = inputDemandSample+adjustedDemand;
    double machsOutput = min(psuedoMaxTxPower, newDemand);
    adjustedDemand = max(newDemand-psuedoMaxTxPower, static_cast<double>(0));
    return machsOutput;
}

double PidSimulator::computeFromMachsModel2(double const inputDemandSample, double const psuedoMaxTxPower, double & adjustedDemand)
{
    adjustedDemand=0;
    return min(psuedoMaxTxPower, inputDemandSample);
}

void PidSimulator::calculateAndGenerateOutputImage()
{
    int index = 0, xRightMax=0, xLeftMax=0, yBottomMax=0, yTopMax=0;
    double tcomReceivedPowerFromMachs = m_conf.maxCellTxPower, adjustedDemand = 0;
    Points targetSeries, inputDemandSeries, pseudoMaxTxPowerSeries, tcomReceivedPowerFromMachsSeries, adjustedDemandSeries;
    for(double const inputDemandSample : m_inputSample)
    {
        double pidOutput(calculatePid(tcomReceivedPowerFromMachs, m_conf.targetInPidCalculation));
        double psuedoMaxTxPower = min(pidOutput, m_conf.maxCellTxPower);
        targetSeries.emplace_back(static_cast<double>(index), m_conf.targetInPidCalculation);
        inputDemandSeries.emplace_back(static_cast<double>(index), inputDemandSample);
        pseudoMaxTxPowerSeries.emplace_back(static_cast<double>(index), psuedoMaxTxPower);
        tcomReceivedPowerFromMachsSeries.emplace_back(static_cast<double>(index), tcomReceivedPowerFromMachs);
        adjustedDemandSeries.emplace_back(static_cast<double>(index), adjustedDemand);
        updateMaxPoints(static_cast<int>(index), static_cast<int>(m_conf.targetInPidCalculation), xLeftMax, xRightMax, yBottomMax, yTopMax);
        updateMaxPoints(static_cast<int>(index), static_cast<int>(inputDemandSample), xLeftMax, xRightMax, yBottomMax, yTopMax);
        updateMaxPoints(static_cast<int>(index), static_cast<int>(psuedoMaxTxPower), xLeftMax, xRightMax, yBottomMax, yTopMax);
        updateMaxPoints(static_cast<int>(index), static_cast<int>(psuedoMaxTxPower), xLeftMax, xRightMax, yBottomMax, yTopMax);
        updateMaxPoints(static_cast<int>(index), static_cast<int>(tcomReceivedPowerFromMachs), xLeftMax, xRightMax, yBottomMax, yTopMax);
        //Remove adjusted demand //updateMaxPoints(static_cast<int>(index), static_cast<int>(adjustedDemand), xLeftMax, xRightMax, yBottomMax, yTopMax);
        tcomReceivedPowerFromMachs = computeFromMachsModel(inputDemandSample, psuedoMaxTxPower, adjustedDemand);
        index++;
    }

    updateAllMaxWithBuffer(xLeftMax, xRightMax, yBottomMax, yTopMax);
    cout << "max list:[" << xLeftMax << ", " << xRightMax << ", " << yBottomMax << ", " << yTopMax << "]" << endl;

    AlbaLocalPathHandler detectedPath(PathInitialValueSource::DetectedLocalPath);
    AlbaLocalPathHandler defaultFile(detectedPath.getDirectory() + R"(Default24Bit.bmp)");
    cout << "defaultFile:[" << defaultFile.getFullPath() << "]" << endl;
    if(defaultFile.isFoundInLocalSystem())
    {
        AlbaLocalPathHandler graphOutputFile(defaultFile.getDirectory() + R"(\graph.bmp)");
        cout << "graphOutputFile:[" << graphOutputFile.getFullPath() << "]" << endl;
        graphOutputFile.deleteFile();
        defaultFile.copyToNewFile(graphOutputFile.getFullPath());

        Bitmap bitmap(graphOutputFile.getFullPath());
        BitmapConfiguration configuration(bitmap.getConfiguration());
        calculateMagnificationAndOffset(xLeftMax, xRightMax, yBottomMax, yTopMax, configuration.getBitmapWidth(), configuration.getBitmapHeight());
        cout << "offset:[" << m_xOffsetToGraph << ", " << m_yOffsetToGraph << "] magnification:[" << m_xMagnificationToGraph << ", " << m_yMagnificationToGraph << "]" << endl;

        AprgGraph graph(graphOutputFile.getFullPath(), BitmapXY(m_xOffsetToGraph, m_yOffsetToGraph), BitmapDoubleXY(m_xMagnificationToGraph, m_yMagnificationToGraph));
        graph.drawGrid(BitmapDoubleXY(m_xGridInterval, m_yGridInterval));
        graph.drawContinuousPoints(targetSeries, 0x00444444);
        graph.drawContinuousPoints(inputDemandSeries, 0x000000FF);
        graph.drawContinuousPoints(pseudoMaxTxPowerSeries, 0x0000FF00);
        graph.drawContinuousPoints(tcomReceivedPowerFromMachsSeries, 0x00FF0000);
        //Remove adjusted demand //graph.drawContinuousPoints(adjustedDemandSeries, 0x00008888);

        graph.saveChangesToBitmapFile();
    }
    else
    {
        cout << "The default bitmap file was not found. The default file location:  [" << defaultFile.getFullPath() << "]" << endl;
    }
}

void PidSimulator::updateAllMaxWithBuffer(int& xLeftMax, int& xRightMax, int& yBottomMax, int& yTopMax)
{
    updateMaxWithBuffer(xLeftMax, xRightMax);
    updateMaxWithBuffer(yBottomMax, yTopMax);
}

void PidSimulator::updateMaxWithBuffer(int& lowerValue, int& higherValue)
{
    const double hardBuffer = 5;
    int difference = higherValue - lowerValue;
    double increase = static_cast<double>(difference)*0.1;
    if(increase<hardBuffer)
    {
        increase = hardBuffer;
    }
    lowerValue = static_cast<int>(lowerValue - increase);
    higherValue = static_cast<int>(higherValue + increase);
}

void PidSimulator::calculateMagnificationAndOffset(
        double const xLeftMax,
        double const xRightMax,
        double const yBottomMax,
        double const yTopMax,
        double const bitmapSizeInX,
        double const bitmapSizeInY)
{
    m_xMagnificationToGraph = bitmapSizeInX/(xRightMax-xLeftMax);
    int xOffsetGraph = static_cast<int>(round(-1*m_xMagnificationToGraph*xLeftMax));
    if(xOffsetGraph<0)
    {
        m_xOffsetToGraph = 0;
    }
    else
    {
        m_xOffsetToGraph = static_cast<unsigned int>(xOffsetGraph);
    }
    m_yMagnificationToGraph = bitmapSizeInY/(yTopMax-yBottomMax);
    int yOffsetGraph = static_cast<int>(round(1*m_yMagnificationToGraph*yTopMax));
    if(yOffsetGraph<0)
    {
        m_yOffsetToGraph = 0;
    }
    else
    {
        m_yOffsetToGraph = static_cast<unsigned int>(yOffsetGraph);
    }
    m_xGridInterval = static_cast<double>(pow(10, 2+round(log10(1/m_xMagnificationToGraph))));
    m_yGridInterval = static_cast<double>(pow(10, 2+round(log10(1/m_yMagnificationToGraph))));
}

void PidSimulator::updateMaxPoints(
        int const xCoordinate,
        int const yCoordinate,
        int & xLeftMax,
        int & xRightMax,
        int & yBottomMax,
        int & yTopMax)
{
    updateRightMax(xRightMax, xCoordinate);
    updateLeftMax(xLeftMax, xCoordinate);
    updateTopMax(yTopMax, yCoordinate);
    updateBottomMax(yBottomMax, yCoordinate);
}

void PidSimulator::updateRightMax(int & xRightMax, int const xCoordinate)
{
    int const hardMax=2000;
    if(xCoordinate<=hardMax && xRightMax<xCoordinate)
    {
        xRightMax=xCoordinate;
    }
}

void PidSimulator::updateLeftMax(int & xLeftMax, int const xCoordinate)
{
    int const hardMax=-2000;
    if(xCoordinate>=hardMax && xLeftMax>xCoordinate)
    {
        xLeftMax=xCoordinate;
    }
}

void PidSimulator::updateTopMax(int & yTopMax, int const yCoordinate)
{
    int const hardMax=2000;
    if(yCoordinate<=hardMax && yTopMax<yCoordinate)
    {
        yTopMax=yCoordinate;
    }
}

void PidSimulator::updateBottomMax(int & yBottomMax, int const yCoordinate)
{
    int const hardMax=-2000;
    if(yCoordinate>=hardMax && yBottomMax>yCoordinate)
    {
        yBottomMax=yCoordinate;
    }
}

}
