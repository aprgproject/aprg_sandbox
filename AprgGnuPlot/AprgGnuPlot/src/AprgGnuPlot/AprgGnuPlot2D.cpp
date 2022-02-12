#include <AprgGnuPlot/AprgGnuPlot2D.hpp>

using namespace alba::TwoDimensions;
using namespace std;
namespace alba
{

void AprgGnuPlot2D::startGraph()
{
    m_gnuPlot << "plot ";
}

void AprgGnuPlot2D::graph(PointsInGraph const& points, string const& graphName, string const& configurationString)
{
    m_gnuPlot << m_gnuPlot.binFile1d(points, "record")
              << " " << configurationString
              << " title '" << graphName <<"'";
    m_gnuPlot << ", ";
}

void AprgGnuPlot2D::graph(TwoDimensions::Points const& geometryPoints, string const& graphName, string const& configurationString)
{
    PointsInGraph points;
    for(unsigned int i=0; i<geometryPoints.size(); i++)
    {
        points.emplace_back(make_pair(geometryPoints[i].getX(), geometryPoints[i].getY()));
    }
    graph(points, graphName, configurationString);
}

}
