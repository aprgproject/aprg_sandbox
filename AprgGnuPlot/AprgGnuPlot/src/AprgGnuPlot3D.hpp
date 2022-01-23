#pragma once

#include <AprgGnuPlotBase.hpp>
#include <ThreeDimensions/Point.hpp>

namespace alba
{

class AprgGnuPlot3D : public AprgGnuPlotBase
{
public:
    using PointInGraph = std::pair<std::pair<double, double>, double>;
    using PointsInGraph = std::vector<PointInGraph>;

    static PointInGraph getPoint(double const x, double const y, double const z);

    void startGraph() override;
    void graph(PointsInGraph const& points, std::string const& graphName, std::string const& configurationString);
    void graph(ThreeDimensions::Points const& geometryPoints, std::string const& graphName, std::string const& configurationString);
};

}
