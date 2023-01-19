#pragma once

#include <AprgGnuPlot/AprgGnuPlotBase.hpp>
#include <Geometry/TwoDimensions/Constructs/Point.hpp>

namespace alba
{

class AprgGnuPlot2D : public AprgGnuPlotBase
{
public:
    using PointInGraph = std::pair<double, double>;
    using PointsInGraph = std::vector<PointInGraph>;

    void graph(PointsInGraph const& points, std::string const& graphName, std::string const& configurationString);
    void graph(TwoDimensions::Points const& geometryPoints, std::string const& graphName, std::string const& configurationString);
protected:
    void startGraph() override;
};

}
