#pragma once

#include <Geometry/ThreeDimensions/Point.hpp>
#include <gnuplot-iostream.h>

namespace alba{

class AprgGnuPlotBase
{
public:
    void setTitle(std::string const& title, std::string const& configurationString);
    void setXAxis(std::string const& xAxisName, std::string const& configurationString);
    void setYAxis(std::string const& yAxisName, std::string const& configurationString);
    void setZAxis(std::string const& zAxisName, std::string const& configurationString);
    virtual void startGraph()=0;
    void endGraph();
protected:
    Gnuplot m_gnuPlot;
};

}
