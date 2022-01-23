#include <AprgGnuPlotBase.hpp>

using namespace std;

namespace alba
{

void AprgGnuPlotBase::setTitle(string const& title, string const& configurationString)
{
    m_gnuPlot << R"(set title ")" << title << " " << configurationString << endl;
}

void AprgGnuPlotBase::setXAxis(string const& xAxisName, string const& configurationString)
{
    m_gnuPlot << R"(set xlabel ")" << xAxisName << " " << configurationString << endl;
    m_gnuPlot << R"(set xtics font ",15")" << endl;
}

void AprgGnuPlotBase::setYAxis(string const& yAxisName, string const& configurationString)
{
    m_gnuPlot << R"(set ylabel ")" << yAxisName << " " << configurationString << endl;
    m_gnuPlot << R"(set ytics font ",15")" << endl;
}

void AprgGnuPlotBase::setZAxis(string const& zAxisName, string const& configurationString)
{
    m_gnuPlot << R"(set zlabel ")" << zAxisName << " " << configurationString << endl;
    m_gnuPlot << R"(set ztics font ",15")" << endl;
}

void AprgGnuPlotBase::endGraph()
{
    m_gnuPlot << endl;
}

}
