#pragma once

#include <AprgGnuPlotBase.hpp>
#include <TwoDimensions/Point.hpp>

namespace alba
{

class AprgGnuPlot2D : public AprgGnuPlotBase
{
public:
    using PointInGraph = std::pair<double, double>;
    using PointsInGraph = std::vector<PointInGraph>;

    void startGraph() override;
    void graph(PointsInGraph const& points, std::string const& graphName, std::string const& configurationString);
    void graph(TwoDimensions::Points const& geometryPoints, std::string const& graphName, std::string const& configurationString);
};

}
