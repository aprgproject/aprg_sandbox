#include "AprgGraph.hpp"

#include <Algebra/Solution/Solver/OneEquationOneVariable/OneEquationOneVariableEqualitySolver.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/PolynomialHelpers.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Geometry/TwoDimensions/Utilities/TwoDimensionsUtilities.hpp>

#include <algorithm>
#include <cmath>

using namespace std;

using namespace alba::algebra;
using namespace alba::AprgBitmap;
using namespace alba::TwoDimensions;
using namespace alba::TwoDimensions::twoDimensionsUtilities;

namespace alba
{

AprgGraph::AprgGraph(string const& bitmapPath, BitmapXY const& originInBitmap, BitmapDoubleXY const& magnification)
    : m_bitmap(bitmapPath)
    , m_bitmapSnippet(m_bitmap.getSnippetReadFromFileWholeBitmap())
    , m_originInBitmap(originInBitmap)
    , m_magnification(magnification)
    , m_lowestInterval(getLowestInterval())
    , m_realUpLeftPoint(convertBitmapXYToRealPoint(m_bitmap.getConfiguration().getUpLeftCornerPoint()))
    , m_realDownRightPoint(convertBitmapXYToRealPoint(m_bitmap.getConfiguration().getDownRightCornerPoint()))
{
    m_numberToStringConverter.setPrecision(5);
}

void AprgGraph::drawPoint(Point const& point, unsigned int const color)
{
    drawBitmapPointIfPossible(convertRealPointToBitmapPoint(point), color);
}

void AprgGraph::drawDiscontinuousPoints(Points const& points, unsigned int const color)
{
    for(Point const& point : points)
    {
        drawPoint(point, color);
    }
}

bool AprgGraph::isBitmapPointInTheBitmap(Point const& bitmapPoint)
{
    int bitmapPointInX = static_cast<int>(round(bitmapPoint.getX()));
    int bitmapPointInY = static_cast<int>(round(bitmapPoint.getY()));
    return m_bitmap.getConfiguration().isPositionWithinTheBitmap(bitmapPointInX, bitmapPointInY);
}

void AprgGraph::drawContinuousPoints(Points const& points, unsigned int const color)
{
    Points bitmapPointsInsideBitmap;
    Point previousBitmapPointNotOnTheBitmap;
    bool isPreviousBitmapPointOnTheBitmap(true);
    for(Point const& point : points)
    {
        Point bitmapPoint(convertRealPointToBitmapPoint(point));
        bool isCurrentBitmapPointOnTheBitmap=isBitmapPointInTheBitmap(bitmapPoint);
        if(isCurrentBitmapPointOnTheBitmap)
        {
            if(!isPreviousBitmapPointOnTheBitmap)
            {
                bitmapPointsInsideBitmap.emplace_back(previousBitmapPointNotOnTheBitmap); // add a before point to fully cover the graph
            }
            bitmapPointsInsideBitmap.emplace_back(bitmapPoint);
        }
        else
        {
            bitmapPointsInsideBitmap.emplace_back(bitmapPoint); // add a last point to fully cover the graph
            drawConnectedBitmapPointsIfPossible(bitmapPointsInsideBitmap, color);
            previousBitmapPointNotOnTheBitmap = bitmapPoint;
            bitmapPointsInsideBitmap.clear();
        }
        isPreviousBitmapPointOnTheBitmap = isCurrentBitmapPointOnTheBitmap;
    }
    if(!bitmapPointsInsideBitmap.empty())
    {
        drawConnectedBitmapPointsIfPossible(bitmapPointsInsideBitmap, color);
    }
}

void AprgGraph::drawLine(Line const& line, unsigned int const color)
{
    Points points(line.getPoints(m_realUpLeftPoint, m_realDownRightPoint, m_lowestInterval));
    drawDiscontinuousPoints(points, color);
}

void AprgGraph::drawCircle(Circle const& circle, unsigned int const color)
{
    Points points(circle.getLocus(m_lowestInterval));
    drawDiscontinuousPoints(points, color);
}

void AprgGraph::drawEllipse(Ellipse const& ellipse, unsigned int const color)
{
    Points points(ellipse.getPointsForCircumference(m_lowestInterval));
    drawDiscontinuousPoints(points, color);
}

void AprgGraph::drawHyperbola(Hyperbola const& hyperbola, unsigned int const color)
{
    Points points(hyperbola.getPointsForShape(m_lowestInterval));
    drawDiscontinuousPoints(points, color);
}

void AprgGraph::drawTermWithXYSubstitution(Term const& term, unsigned int const color)
{
    drawTermWithXSubstitution(term, color);
    drawTermWithYSubstitution(term, color);
}

void AprgGraph::drawEquationWithXYSubstitution(Equation const& equation, unsigned int const color)
{
    drawEquationWithXSubstitution(equation, color);
    drawEquationWithYSubstitution(equation, color);
}

void AprgGraph::drawGrid(BitmapDoubleXY const& gridInterval)
{
    if(0!=gridInterval.getX() && 0!=gridInterval.getY())
    {
        const unsigned int gridColor(0x00BBBBBB);
        const unsigned int mainColor(0x00000000);

        for(double x=gridInterval.getX(); x<=m_realDownRightPoint.getX(); x+=gridInterval.getX())
        {
            Points gridLine{Point(x, m_realUpLeftPoint.getY()), Point(x, m_realDownRightPoint.getY())};
            drawContinuousPoints(gridLine, gridColor);
            drawNumberLabel(LabelType::HorizontalLabel, convertRealPointToBitmapPoint(Point(x, 0)), x);
        }
        for(double x=-gridInterval.getX(); x>=m_realUpLeftPoint.getX(); x-=gridInterval.getX())
        {
            Points gridLine{Point(x, m_realUpLeftPoint.getY()), Point(x, m_realDownRightPoint.getY())};
            drawContinuousPoints(gridLine, gridColor);
            drawNumberLabel(LabelType::HorizontalLabel, convertRealPointToBitmapPoint(Point(x, 0)), x);
        }
        for(double y=-gridInterval.getY(); y>=m_realDownRightPoint.getY(); y-=gridInterval.getY())
        {
            Points gridLine{Point(m_realUpLeftPoint.getX(), y), Point(m_realDownRightPoint.getX(), y)};
            drawContinuousPoints(gridLine, gridColor);
            drawNumberLabel(LabelType::VerticalLabel, convertRealPointToBitmapPoint(Point(0, y)), y);
        }
        for(double y=gridInterval.getY(); y<=m_realUpLeftPoint.getY(); y+=gridInterval.getY())
        {
            Points gridLine{Point(m_realUpLeftPoint.getX(), y), Point(m_realDownRightPoint.getX(), y)};
            drawContinuousPoints(gridLine, gridColor);
            drawNumberLabel(LabelType::VerticalLabel, convertRealPointToBitmapPoint(Point(0, y)), y);
        }
        Points mainVerticalLine{Point(0, m_realUpLeftPoint.getY()), Point(0, m_realDownRightPoint.getY())};
        drawContinuousPoints(mainVerticalLine, mainColor);
        Points mainHorizontalLine{Point(m_realUpLeftPoint.getX(), 0), Point(m_realDownRightPoint.getX(), 0)};
        drawContinuousPoints(mainHorizontalLine, mainColor);
        drawNumberLabel(LabelType::OriginLabel, convertRealPointToBitmapPoint(Point(0, 0)), 0);
    }
}

void AprgGraph::drawFunctionUsingX(unsigned int const color, FunctionWithDoubles const& functionFromXToY)
{
    Points points;
    RangeWithDoubles xRange(m_realUpLeftPoint.getX(), m_realDownRightPoint.getX(), m_lowestInterval);
    xRange.traverse([&](double const xValue)
    {
        points.emplace_back(xValue, functionFromXToY(xValue));
    });
    drawContinuousPoints(points, color);
}

void AprgGraph::drawFunctionUsingY(unsigned int const color, FunctionWithDoubles const& functionFromYToX)
{
    Points points;
    RangeWithDoubles yRange(m_realUpLeftPoint.getY(), m_realDownRightPoint.getY(), m_lowestInterval);
    yRange.traverse([&](double const yValue)
    {
        points.emplace_back(functionFromYToX(yValue), yValue);
    });
    drawContinuousPoints(points, color);
}

void AprgGraph::drawNumberLabel(LabelType const labelType, Point const& bitmapPointNumberPosition, double const number)
{
    string label(m_numberToStringConverter.convertToString(number));
    unsigned int labelCharacterLength = label.length();
    unsigned int widthOfCharacter = 12;
    unsigned int heightOfCharacter = 20;
    int startPositionInX=0,  startPositionInY=0;
    int numberPositionInX = static_cast<int>(round(bitmapPointNumberPosition.getX()));
    int numberPositionInY = static_cast<int>(round(bitmapPointNumberPosition.getY()));
    if(LabelType::HorizontalLabel == labelType)
    {
        startPositionInX = numberPositionInX - (static_cast<int>(label.length()*widthOfCharacter/2));
        startPositionInY = numberPositionInY;
    }
    else if(LabelType::VerticalLabel == labelType)
    {
        startPositionInX = numberPositionInX;
        startPositionInY = numberPositionInY - (static_cast<int>(heightOfCharacter/2));
    }
    else if(LabelType::OriginLabel == labelType)
    {
        startPositionInX = numberPositionInX;
        startPositionInY = numberPositionInY;
    }
    for(unsigned int i=0; i<labelCharacterLength; i++)
    {
        drawCharacter(BitmapXY(startPositionInX+(i*widthOfCharacter), startPositionInY), label[i], 0x00000000);
    }
}

void  AprgGraph::drawCharacter(BitmapXY const& upLeftPoint, char const character, unsigned int const colorToWrite)
{
    string bitmapFilePathOfCharacter(getBitmapFilePathOfCharacter(character));
    Bitmap characterBitmap(bitmapFilePathOfCharacter);
    BitmapSnippet characterBitmapSnippet(characterBitmap.getSnippetReadFromFileWholeBitmap());

    characterBitmapSnippet.traverse([&](BitmapXY const& point, unsigned int const color)
    {
        if(color==0x00000000)
        {
            m_bitmapSnippet.setPixelAt(BitmapXY(upLeftPoint.getX()+point.getX(), upLeftPoint.getY()+point.getY()), colorToWrite);
        }
    });
}

void AprgGraph::saveChangesToBitmapFile()
{
    m_bitmap.setSnippetWriteToFile(m_bitmapSnippet);
}

string AprgGraph::getBitmapFilePathOfCharacter(char const character) const
{
    string filename("NotAValidFilename");
    if(stringHelper::isNumber(character))
    {
        filename = string(1, character);
    }
    else if('-' == character)
    {
        filename = "Dash";
    }
    else if('.' == character)
    {
        filename = "Period";
    }
    else if('E' == character || 'e' == character)
    {
        filename = "E";
    }
    filename+=".bmp";

#ifdef APRG_RELEASE
    //This is based on detectedPath (for release builds), there should be a common file for this (on pathhandlers maybe?)
    AlbaLocalPathHandler detectedPath(PathInitialValueSource::DetectedLocalPath);
    AlbaLocalPathHandler bitmapCharacterFile(detectedPath.getDirectory() + R"(BitmapCharacters/)"+filename);
    return bitmapCharacterFile.getFullPath();
#endif

#ifdef APRG_DEBUG
    //This is based on APRG (for debug builds), there should be a common for this (on pathhandlers maybe?)
    return  AlbaLocalPathHandler(string(APRG_DIR)+"/AprgGraph/BitmapCharacters/"+filename).getFullPath();
#endif
}

double AprgGraph::getLowestInterval() const
{
    return min(1/m_magnification.getX(), 1/m_magnification.getY());
}

Point AprgGraph::convertBitmapXYToRealPoint(BitmapXY const& bitmapPosition) const
{
    double xPosition = convertBitmapXCoordinateToRealXCoordinate(bitmapPosition.getX());
    double yPosition = convertBitmapYCoordinateToRealYCoordinate(bitmapPosition.getY());
    return Point(xPosition, yPosition);
}

Point AprgGraph::convertRealPointToBitmapPoint(Point const& realPosition) const
{
    double xPosition = static_cast<double>(convertRealXCoordinateToBitmapXCoordinate(realPosition.getX()));
    double yPosition = static_cast<double>(convertRealYCoordinateToBitmapYCoordinate(realPosition.getY()));
    return Point(xPosition, yPosition);
}

int AprgGraph::convertRealXCoordinateToBitmapXCoordinate(double const xCoordinate) const
{
    return static_cast<int>(round((xCoordinate*m_magnification.getX())+m_originInBitmap.getX()));
}

int AprgGraph::convertRealYCoordinateToBitmapYCoordinate(double const yCoordinate) const
{
    return static_cast<int>(round((-1*yCoordinate*m_magnification.getY())+m_originInBitmap.getY()));
}

double AprgGraph::convertBitmapXCoordinateToRealXCoordinate(double const xCoordinate) const
{
    return (xCoordinate-m_originInBitmap.getX())/m_magnification.getX();
}

double AprgGraph::convertBitmapYCoordinateToRealYCoordinate(double const yCoordinate) const
{
    return (yCoordinate-m_originInBitmap.getY())/(m_magnification.getY()*-1);
}

void AprgGraph::drawBitmapPointIfPossible(
        Point const& bitmapPoint,
        unsigned int const color)
{
    if(isBitmapPointInTheBitmap(bitmapPoint))
    {
        unsigned int confirmedX = static_cast<unsigned int>(round(bitmapPoint.getX()));
        unsigned int confirmedY = static_cast<unsigned int>(round(bitmapPoint.getY()));
        m_bitmapSnippet.setPixelAt(BitmapXY(confirmedX, confirmedY), color);
    }
}

void AprgGraph::drawConnectedBitmapPointsIfPossible(
        Points const& bitmapPoints,
        unsigned int const color)
{
    Points connectedBitmapPoints(getConnectedPointsUsingALine(bitmapPoints, 1));
    for(Point const& connectedBitmapPoint : connectedBitmapPoints)
    {
        drawBitmapPointIfPossible(connectedBitmapPoint, color);
    }
}



void AprgGraph::drawTermWithXSubstitution(Term const& term, unsigned int const color)
{
    Points points;
    RangeWithDoubles xRange(m_realUpLeftPoint.getX(), m_realDownRightPoint.getX(), m_lowestInterval);
    SubstitutionOfVariablesToValues substitution;
    xRange.traverse([&](double const xValue)
    {
        substitution.putVariableWithValue("x", xValue);
        Term substitutedTerm(substitution.performSubstitutionTo(term));
        if(substitutedTerm.isConstant())
        {
            points.emplace_back(xValue, substitutedTerm.getConstantConstReference().getNumberConstReference().getDouble());
        }
    });
    drawContinuousPoints(points, color);
}

void AprgGraph::drawTermWithYSubstitution(Term const& term, unsigned int const color)
{
    Points points;
    RangeWithDoubles yRange(m_realUpLeftPoint.getY(), m_realDownRightPoint.getY(), m_lowestInterval);
    SubstitutionOfVariablesToValues substitution;
    yRange.traverse([&](double const yValue)
    {
        substitution.putVariableWithValue("y", yValue);
        Term substitutedTerm(substitution.performSubstitutionTo(term));
        if(substitutedTerm.isConstant())
        {
            points.emplace_back(substitutedTerm.getConstantConstReference().getNumberConstReference().getDouble(), yValue);
        }
    });
    drawContinuousPoints(points, color);
}

void AprgGraph::drawEquationWithXSubstitution(Equation const& equation, unsigned int const color)
{
    Points points;
    RangeWithDoubles xRange(m_realUpLeftPoint.getX(), m_realDownRightPoint.getX(), m_lowestInterval);
    SubstitutionOfVariablesToValues substitution;
    xRange.traverse([&](double const xValue)
    {
        substitution.putVariableWithValue("x", xValue);
        Equation substitutedEquation(substitution.performSubstitutionTo(equation));
        OneEquationOneVariableEqualitySolver solver;
        SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(substitutedEquation));
        AlbaNumbers acceptedValues(solutionSet.getAcceptedValues());
        for(AlbaNumber const& acceptedValue : acceptedValues)
        {
            points.emplace_back(xValue, acceptedValue.getDouble());
        }
    });
    drawDiscontinuousPoints(points, color);
}

void AprgGraph::drawEquationWithYSubstitution(Equation const& equation, unsigned int const color)
{
    Points points;
    RangeWithDoubles yRange(m_realUpLeftPoint.getY(), m_realDownRightPoint.getY(), m_lowestInterval);
    SubstitutionOfVariablesToValues substitution;
    yRange.traverse([&](double const yValue)
    {
        substitution.putVariableWithValue("y", yValue);
        Equation substitutedEquation(substitution.performSubstitutionTo(equation));
        OneEquationOneVariableEqualitySolver solver;
        SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(substitutedEquation));
        AlbaNumbers acceptedValues(solutionSet.getAcceptedValues());
        for(AlbaNumber const& acceptedValue : acceptedValues)
        {
            points.emplace_back(acceptedValue.getDouble(), yValue);
        }
    });
    drawDiscontinuousPoints(points, color);
}


}
