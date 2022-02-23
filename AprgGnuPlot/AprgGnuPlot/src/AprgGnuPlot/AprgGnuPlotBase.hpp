#pragma once

#include <Geometry/ThreeDimensions/Point.hpp>
#include <gnuplot-iostream.h>

#include <functional>

namespace alba
{

class AprgGnuPlotBase
{
public:
    using GraphingSteps=std::function<void(void)>;

    void setTitle(std::string const& title, std::string const& configurationString);
    void setXAxis(std::string const& xAxisName, std::string const& configurationString);
    void setYAxis(std::string const& yAxisName, std::string const& configurationString);
    void setZAxis(std::string const& zAxisName, std::string const& configurationString);
    void doGraphs(GraphingSteps const& graphingSteps);
protected:
    virtual void startGraph()=0;
    void endGraph();
    Gnuplot m_gnuPlot;
};

}
