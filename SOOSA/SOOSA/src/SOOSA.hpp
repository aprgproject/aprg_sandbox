#pragma once

#include <Bitmap/Bitmap.hpp>
#include <Bitmap/BitmapSnippet.hpp>
#include <Common/Container/AlbaValueRange.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <Geometry/TwoDimensions/Constructs/Line.hpp>
#include <Geometry/TwoDimensions/Constructs/Point.hpp>
#include <InputConfiguration.hpp>
#include <SoosaConfiguration.hpp>
#include <Statistics/DataCollection.hpp>#include <Statistics/KMeansClustering.hpp>
#include <Statistics/TwoDimensionsStatistics.hpp>

#include <array>#include <deque>
#include <fstream>
#include <map>
#include <string>
#include <vector>

namespace alba
{

namespace soosa
{

class SOOSA
{
public:
    class FrequencyDatabase
    {
    public:
        FrequencyDatabase(unsigned int const numberOfQuestions, unsigned int const numberOfChoices);
        void initialize();
        void addAnswer(unsigned int const questionIndex, unsigned int const answerIndex);
        unsigned int getFrequencyOfAnswer(unsigned int const questionIndex, unsigned int const answerIndex) const;
    private:
        unsigned int m_numberOfQuestions;
        unsigned int m_numberOfChoices;
        matrix::AlbaMatrix<unsigned int> m_frequenciesOnQuestionByAnswer;
    };

    class Status
    {
        Status();
    public:
        static Status getInstance();
        std::string getStatusString() const;
        void setError(std::string const& error);
        void clearErrors();
        bool isStatusNoError() const;
    private:
        alba::stringHelper::strings m_errors;
    };

    using Answers = std::vector<unsigned int>;
    using RangeOfInts = AlbaValueRange<int>;
    using RangeOfDoubles = AlbaValueRange<double>;
    using VectorOfDoubles = std::vector<double>;
    using Line = TwoDimensions::Line;
    using Point = TwoDimensions::Point;
    using Bitmap = AprgBitmap::Bitmap;
    using BitmapSnippet = AprgBitmap::BitmapSnippet;
    using BitmapXY = AprgBitmap::BitmapXY;
    using OneDimensionSample = DataSample<1U>;
    using TwoDimensionSample = DataSample<2U>;
    using OneDimensionSamples = std::vector<OneDimensionSample>;
    using TwoDimensionSamples = std::vector<TwoDimensionSample>;
    using GroupOfOneDimensionSamples = std::vector<OneDimensionSamples>;
    using GroupOfTwoDimensionSamples = std::vector<TwoDimensionSamples>;
    using ValueToTwoDimensionSampleMultimap = std::multimap<double, TwoDimensionSample>;
    using OneDimensionKMeans = KMeansClustering<1>;
    using TwoDimensionKMeans = KMeansClustering<2>;
    using OneDimensionStatistics = DataStatistics<1>;
    using TwoDimensionStatistics = DataStatistics<2>;
    using DoubleCollection = DataCollection<double>;
    using QuestionBarCoordinate = std::pair<Point, Point>;
    using QuestionBarCoordinates = std::vector<QuestionBarCoordinate>;
    using PointAndWidthPair = std::pair<Point, double>;
    using PointAndWidthPairs = std::vector<PointAndWidthPair>;
    using DequeOfPoints = std::deque<Point>;
    using EndPointIndexes=std::pair<unsigned int, unsigned int>;
    using CountToEndPointIndexesMultiMap=std::multimap<unsigned int, EndPointIndexes>;

    SOOSA(SoosaConfiguration const& soosaConfiguration, InputConfiguration const& inputConfiguration);
    unsigned int getNumberOfAnswers() const;
    unsigned int getAnswerToQuestion(unsigned int const questionIndex) const;
    void process();


private:

    void processDirectory(std::string const & directoryPath);
    void processFile(std::string const & filePath);
    void processBitmapFile(Bitmap const& bitmap);
    void performStepsWhenNumberOfAnswersNotEqualToNumberOfQuestions() const;
    void saveToFrequencyDatabase();

    // find line
    Line findLeftLine(BitmapSnippet const& snippet) const;
    Line findRightLine(BitmapSnippet const& snippet) const;
    Line findTopLine(BitmapSnippet const& snippet) const;
    Line findBottomLine(BitmapSnippet const& snippet) const;
    Line findVerticalLine(BitmapSnippet const& snippet, RangeOfInts const& range) const;
    Line findHorizontalLine(BitmapSnippet const& snippet, RangeOfInts const& range) const;
    Line findLeftLineUsingStartingLine(BitmapSnippet const& snippet, Line const& startingLine) const;
    Line findRightLineUsingStartingLine(BitmapSnippet const& snippet, Line const& startingLine) const;
    Line findVerticalLineUsingStartingLine(BitmapSnippet const& snippet, Line const& startingLine, RangeOfInts const& rangeForX) const;

    // Line modeling functions
    Line getLineModel(TwoDimensionSamples const& samples) const;
    DoubleCollection getAcceptableSquareErrorCollectionUsingRemovalRatio(ValueToTwoDimensionSampleMultimap const& squareErrorToSampleMultimap) const;
    void updateSamplesForLineModeling(TwoDimensionSamples & samplesLineModeling, ValueToTwoDimensionSampleMultimap const& squareErrorToSampleMultimap, double const maxAcceptableSquareError) const;

    // Column functions
    void processTwoColumns(BitmapSnippet const& globalSnippet, Line const& leftLine, Line const& rightLine, Line const& topLine, Line const& bottomLine);
    void processOneColumn(BitmapSnippet const& globalSnippet, Line const& leftLine, Line const& rightLine, Line const& topLine, Line const& bottomLine);
    void processColumn(unsigned int & questionNumber, BitmapSnippet const& snippet, Line const& leftLine, Line const& rightLine, Line const& topLine, Line const& bottomLine, unsigned int const columnNumber);
    void processQuestions(unsigned int & questionNumber, BitmapSnippet const& snippet, QuestionBarCoordinates const& questionBarsOnTheLeft, QuestionBarCoordinates const& questionsBarsOnTheRight, unsigned int const columnNumber, unsigned int const numberQuestionsInColumn);
    Answers getAnswersAtQuestion(BitmapSnippet const& snippet, QuestionBarCoordinate const& leftCoordinate, QuestionBarCoordinate const& rightCoordinate) const;
    double getShadePercentage(BitmapSnippet const& snippet, Point const& leftPoint, Point const& rightPoint, double const radius, unsigned int const choiceIndex) const;
    double getRadiusForChoiceChecking(QuestionBarCoordinate const& leftCoordinate, QuestionBarCoordinate const& rightCoordinate) const;
    Point getCenterOfCircleForChoiceChecking(BitmapSnippet const& snippet, Point const& leftPoint, Point const& rightPoint, double const radius, unsigned int const choiceIndex) const;
    QuestionBarCoordinates getQuestionBarCoordinatesFromLine(BitmapSnippet const& snippet, Line const& line, Point const& startPoint, Point const& endPoint, unsigned int const numberQuestionsInColumn) const;
    void retrieveBarPointsThatFitAndSaveToKMeans(TwoDimensionKMeans & kMeansForBarPoints, PointAndWidthPairs const& pointsAndWidths, RangeOfDoubles const& minMaxCriteriaForBar) const;
    void saveQuestionBarCoordinatesFromKMeansWithBarPoints(QuestionBarCoordinates & questionBarCoordinates, TwoDimensionKMeans const& kMeansForBarPoints, unsigned int const numberQuestionsInColumn) const;

    // Widths functions
    RangeOfDoubles getMinMaxCriteriaForBar(PointAndWidthPairs const& pointAndWidthPairs) const;
    RangeOfDoubles getMinMaxCriteriaForBar(OneDimensionStatistics & firstGroupStatistics, OneDimensionStatistics & secondGroupStatistics) const;
    OneDimensionKMeans getKMeansForWidths(PointAndWidthPairs const& pointAndWidthPairs) const;
    PointAndWidthPairs getAcceptablePointAndWidthPairs(BitmapSnippet const& snippet, Line const& line, Point const& startPoint, Point const& endPoint) const;
    Point getNearestBlackPointFromLine(BitmapSnippet const& snippet, Line const& line, Point const& pointInLine) const;
    Point getLeftOrRightMostBlackPoint(BitmapSnippet const& snippet, Point const& nearestBlackPoint, Line const& perpendicularLine, unsigned int const maxLineAndBarWidth, int const sign) const;
    void addAndRetainWidthsIfPossible(OneDimensionKMeans & kMeansForWidths, OneDimensionStatistics & groupStatistics, double const acceptableSdOverMeanDeviation) const;
    void addPointAndWidthPairIfAcceptable(PointAndWidthPairs & pointAndWidthPairs, BitmapSnippet const& snippet, Line const& line, Point const& blackPoint) const;

    // Height functions
    void removeBarPointsWithFewHeightPoints(TwoDimensionKMeans & kMeansForBarPoints, unsigned int const numberQuestionsInColumn) const;
    CountToEndPointIndexesMultiMap getHeightPointsCountToEndPointIndexesMultimap(TwoDimensionKMeans& kMeansForBarPoints) const;
    double getMaximumDistanceForBetweenBarHeights(double const previousHeight) const;
    void removeBarPointsWithFewHeightPointsCount(TwoDimensionKMeans & kMeansForBarPoints, unsigned int const numberQuestionsInColumn, CountToEndPointIndexesMultiMap const& countToEndPointsIndexesMultiMap) const;
    void removeBarPointsToGetConsistentHeight(TwoDimensionKMeans & kMeansForBarPoints, unsigned int const numberQuestionsInColumn) const;
    void addAndRetainBarPointsIfPossible(TwoDimensionKMeans & kMeansForBarPoints, GroupOfTwoDimensionSamples const& listOfGroupOfBarPoints, unsigned int const indexToRemove) const;
    OneDimensionSamples getBarHeights(GroupOfTwoDimensionSamples const& groupOfBarPoints) const;
    double getHeight(TwoDimensionSamples const& barPoints) const;

    // output related functions
    std::string getCsvFilePath(std::string const& path) const;
    std::string getReportHtmlFilePath(std::string const& path) const;
    std::string getPrintableStringForPercentage(double const numerator, double const denominator) const;
    void setAnswerToQuestionInColumn(unsigned int const columnNumber, unsigned int const questionOffsetInColumn, unsigned int const answer);
    void saveDataToCsvFile(std::string const& processedFilePath) const;
    void saveHeadersToCsvFile() const;
    void saveOutputHtmlFile(std::string const& processedFilePath) const;
    void saveTableToOutputHtmlFile(std::ofstream & reportHtmlFileStream) const;

    // utilities
    bool isBlackAt(BitmapSnippet const& snippet, BitmapXY const bitmapXy) const;
    unsigned int getMaximumLineAndBarWidth(BitmapSnippet const& snippet) const;
    BitmapXY convertToBitmapXY(Point const& point) const;
    BitmapXY convertToBitmapXY(TwoDimensionSample const& sample) const;
    Point convertToPoint(BitmapXY const& bitmapXY) const;
    Point convertToPoint(TwoDimensionSample const& sample) const;
    TwoDimensionSample convertToTwoDimensionSample(Point const& point) const;
    RangeOfDoubles getMinMaxRangeOfSamples(OneDimensionSamples const& samples) const;

    SoosaConfiguration m_soosaConfiguration;
    InputConfiguration m_inputConfiguration;
    unsigned int m_numberOfRespondents;
    std::map<unsigned int, unsigned int> m_questionToAnswersMap;
    FrequencyDatabase m_frequencyDatabase;
};

}

}
