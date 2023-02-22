#include <AprgGnuPlot/AprgGnuPlotBase.hpp>

using namespace std;

namespace alba
{

void AprgGnuPlotBase::setTitle(string const& title, string const& configurationString)
{
    m_gnuPlot << R"(set title ")" << title << " " << configurationString << "\n";
}

void AprgGnuPlotBase::setXAxis(string const& xAxisName, string const& configurationString)
{
    m_gnuPlot << R"(set xlabel ")" << xAxisName << " " << configurationString << "\n";
    m_gnuPlot << R"(set xtics font ",15")" << "\n";
}

void AprgGnuPlotBase::setYAxis(string const& yAxisName, string const& configurationString)
{
    m_gnuPlot << R"(set ylabel ")" << yAxisName << " " << configurationString << "\n";
    m_gnuPlot << R"(set ytics font ",15")" << "\n";
}

void AprgGnuPlotBase::setZAxis(string const& zAxisName, string const& configurationString)
{
    m_gnuPlot << R"(set zlabel ")" << zAxisName << " " << configurationString << "\n";
    m_gnuPlot << R"(set ztics font ",15")" << "\n";
}

void AprgGnuPlotBase::doGraphs(GraphingSteps const& graphingSteps){
    startGraph();
    graphingSteps();
    endGraph();}

void AprgGnuPlotBase::endGraph()
{
    m_gnuPlot << "\n";
}

}