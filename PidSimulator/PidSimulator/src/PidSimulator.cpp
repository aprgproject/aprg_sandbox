#include "PidSimulator.hpp"

#include <AprgGraph.hpp>
#include <Math/AlbaMathHelper.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>

#include <cmath>


#include <Debug/AlbaDebug.hpp>

#define PID_RESULTS_DEFAULT_FILE APRG_DIR R"(PidSimulator\Results\Default24Bit.bmp)"
#define PID_RESULTS_DIR APRG_DIR R"(PidSimulator\Results\)"

using namespace alba::mathHelper;

namespace alba
{

PidSimulator::PidSimulator(stringHelper::strings const& argumentsInMain)
    : m_conf(argumentsInMain)
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
    for(unsigned int j = 0; j < m_conf.numberOfLoopsOfPeriodicInput; j++)
    {
        //go up
        unsigned int partOfSamples = m_conf.numberOfSamplesOfInputInOnePeriod/2;
        double slope = static_cast<double>(m_conf.amplitudeOfInput)/partOfSamples;
        for (unsigned int i = 0; i < partOfSamples; i++)
        {
            m_input.emplace_back((slope*i) + m_conf.addedOffsetOfInput);
        }
        //go down
        for (unsigned int i = 0; i < partOfSamples; i++)
        {
            m_input.emplace_back(m_conf.amplitudeOfInput -(slope*i) + m_conf.addedOffsetOfInput);
        }
    }
}

void PidSimulator::generateSineWavesForInput()
{
    for(unsigned int j = 0; j < m_conf.numberOfLoopsOfPeriodicInput; j++)
    {
        double angle = 0.0;
        for (unsigned int i = 0; i < m_conf.numberOfSamplesOfInputInOnePeriod; i++)
        {
            m_input.emplace_back((m_conf.amplitudeOfInput * sin(angle)) + m_conf.addedOffsetOfInput);
            angle += (2 * getPi()) / m_conf.numberOfSamplesOfInputInOnePeriod;
        }
    }
}

void PidSimulator::generateStepUpForInput()
{
    for(unsigned int j = 0; j < m_conf.numberOfLoopsOfPeriodicInput; j++)
    {
        //minimum
        unsigned int partOfSamples = m_conf.numberOfSamplesOfInputInOnePeriod/4;
        for (unsigned int i = 0; i < partOfSamples; i++)
        {
            m_input.emplace_back(m_conf.addedOffsetOfInput);
        }

        //slope up
        partOfSamples = m_conf.numberOfSamplesOfInputInOnePeriod/2;
        double angle = (getPi()/2.0)*3.0;
        unsigned int amp = ((m_conf.amplitudeOfInput-m_conf.addedOffsetOfInput) / 2);
        unsigned int tOffset = amp + m_conf.addedOffsetOfInput;
        for (unsigned int i = 0; i < partOfSamples; i++)
        {
            m_input.emplace_back((amp * sin(angle)) + tOffset);
            angle += (2 * getPi()) / m_conf.numberOfSamplesOfInputInOnePeriod;
        }

        //flat max
        partOfSamples = m_conf.numberOfSamplesOfInputInOnePeriod/4;
        for (unsigned int i = 0; i < partOfSamples; i++)
        {
            m_input.emplace_back(m_conf.amplitudeOfInput);
        }

    }
}

void PidSimulator::generateStepDownForInput()
{
    for(unsigned int j = 0; j < m_conf.numberOfLoopsOfPeriodicInput; j++)
    {
        //flat max
        unsigned int partOfSamples = m_conf.numberOfSamplesOfInputInOnePeriod/4;
        for (unsigned int i = 0; i < partOfSamples; i++)
        {
            m_input.emplace_back(m_conf.amplitudeOfInput);
        }

        //slope down
        partOfSamples = m_conf.numberOfSamplesOfInputInOnePeriod/2;
        double angle = (getPi()/4.0)*2.0;
        unsigned int amp = ((m_conf.amplitudeOfInput-m_conf.addedOffsetOfInput) / 2);
        unsigned int tOffset = amp + m_conf.addedOffsetOfInput;
        for (unsigned int i = 0; i < partOfSamples; i++)
        {
            m_input.emplace_back((amp * sin(angle)) + tOffset);
            angle += (2 * getPi()) / m_conf.numberOfSamplesOfInputInOnePeriod;
        }

        //minimum
        partOfSamples = m_conf.numberOfSamplesOfInputInOnePeriod/4;
        for (unsigned int i = 0; i < partOfSamples; i++)
        {
            m_input.emplace_back(m_conf.addedOffsetOfInput);
        }
    }
}

void PidSimulator::generateRandomForInput()
{
    for(unsigned int j = 0; j < m_conf.numberOfLoopsOfPeriodicInput; j++)
    {
        for (unsigned int i = 0; i < m_conf.numberOfSamplesOfInputInOnePeriod; i++)
        {
            m_input.emplace_back((rand() % m_conf.amplitudeOfInput) + m_conf.addedOffsetOfInput);
        }
    }
}

void PidSimulator::calculateAndGenerateOutputImage()
{
    int index = 0;
    int xRightMax=0, xLeftMax=0, yBottomMax=0, yTopMax=0;

    Points inputSeries;
    Points outputSeries;
    for(double const inputSample : m_input)
    {
        double pidOutput(calculatePid(inputSample, m_conf.targetInPidCalculation));
        inputSeries.emplace_back(static_cast<double>(index), inputSample);
        updateMaxPoints(static_cast<int>(index), static_cast<int>(inputSample), xLeftMax, xRightMax, yBottomMax, yTopMax);
        outputSeries.emplace_back(static_cast<double>(index), pidOutput);
        updateMaxPoints(static_cast<int>(index), static_cast<int>(pidOutput), xLeftMax, xRightMax, yBottomMax, yTopMax);
        index++;
    }

    ALBA_PRINT4(xLeftMax, xRightMax, yBottomMax, yTopMax);

    updateMaxWithBuffer(xLeftMax, xRightMax);
    updateMaxWithBuffer(yBottomMax, yTopMax);

    ALBA_PRINT4(xLeftMax, xRightMax, yBottomMax, yTopMax);

    AlbaLocalPathHandler defaultFile(PID_RESULTS_DEFAULT_FILE);
    AlbaLocalPathHandler graphOutputFile(PID_RESULTS_DIR R"(\Test.bmp)");
    graphOutputFile.deleteFile();
    defaultFile.copyToNewFile(graphOutputFile.getFullPath());

    AprgBitmap bitmap(graphOutputFile.getFullPath());
    AprgBitmapConfiguration configuration(bitmap.getConfiguration());
    calculateMagnificationAndOffset(xLeftMax, xRightMax, yBottomMax, yTopMax, configuration.getBitmapWidth(), configuration.getBitmapHeight());

    ALBA_PRINT4(m_xOffsetToGraph, m_yOffsetToGraph, m_xMagnificationToGraph, m_yMagnificationToGraph);

    ALBA_PRINT2(inputSeries.size(), outputSeries.size());
    AprgGraph graph(graphOutputFile.getFullPath(), BitmapXY(m_xOffsetToGraph, m_yOffsetToGraph), BitmapDoubleXY(m_xMagnificationToGraph, m_yMagnificationToGraph));
    graph.drawGrid(BitmapDoubleXY(m_xGridInterval, m_yGridInterval));
    graph.drawContinuousPoints(inputSeries, 0x000000FF);
    graph.drawContinuousPoints(outputSeries, 0x0000FF00);

    graph.saveChangesToBitmapFile();
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
    ALBA_PRINT2(m_xGridInterval, m_xMagnificationToGraph);
    ALBA_PRINT2(m_yGridInterval, m_yMagnificationToGraph);
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
