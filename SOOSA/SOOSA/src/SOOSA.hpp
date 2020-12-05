#pragma once

#include <AprgBitmap.hpp>
#include <AprgBitmapSnippet.hpp>
#include <Container/AlbaRange.hpp>
#include <DataCollection.hpp>
#include <KMeansClustering.hpp>
#include <String/AlbaStringHelper.hpp>
#include <SoosaConfiguration.hpp>
#include <TwoDimensions/Line.hpp>
#include <TwoDimensionsStatistics.hpp>
#include <array>
#include <deque>
#include <fstream>#include <map>
#include <string>
#include <vector>

#define NUMBER_OF_CHOICES 5

namespace alba
{

class SOOSA
{
public:
    class FrequencyDatabase
    {
    public:
        FrequencyDatabase(unsigned int numberOfQuestions);
        void clear();
        void addAnswer(unsigned int const questionNumber, unsigned int const answer);
        unsigned int getFrequencyOfAnswer(unsigned int const questionNumber, unsigned int const answer) const;
    private:
        unsigned int m_numberOfQuestions;
        std::map<unsigned int, std::array<unsigned int, NUMBER_OF_CHOICES>> m_questionToAnswerFrequencyMap;
    };

    class PointAndWidth
    {
    public:
        PointAndWidth(Point const& point, double const width);
        Point getPoint() const;
        double getWidth() const;
    private:
        Point m_point;
        double m_width;
    };

    class StatusStatus
    {
        StatusStatus();
    public:
        static StatusStatus getInstance();
        std::string getSoosaStatus() const;
        void setError(std::string const& error);
        void clearErrors();
        bool isStatusNoError() const;
    private:
        alba::stringHelper::strings m_errors;
    };

    struct LineAndBarWidths    {
        double lineWidth;
        double barWidth;
    };
    using RangeOfInts = AlbaRange<int>;
    using RangeOfDoubles = AlbaRange<double>;
    using VectorOfDoubles = std::vector<double>;
    using QuestionBarCoordinate = std::pair<Point, Point>;
    using QuestionBarCoordinates = std::vector<QuestionBarCoordinate>;
    using VectorOfPointAndWidth = std::vector<PointAndWidth>;
    using OneDimensionKMeans = KMeansClustering<1>;
    using TwoDimensionKMeans = KMeansClustering<2>;
    using OneDimensionStatistics = DataStatistics<1>;
    using DequeOfPoints = std::deque<Point>;

    SOOSA(SoosaConfiguration const& configuration);
    unsigned int getNumberOfAnswers() const;
    unsigned int getAnswerToQuestion(unsigned int const questionNumber) const;
    void process();
private:
    std::string getCsvFileName(std::string const& path) const;
    std::string getReportHtmlFileName(std::string const& path) const;
    std::string getPrintableStringForPercentage(double const numerator, double const denominator) const;
    void setAnswerToQuestionInColumn(unsigned int const columnNumber, unsigned int const questionOffsetInColumn, unsigned int const answer);
    void saveDataToCsvFile(std::string const& processedFilePath) const;
    void saveHeadersToCsvFile() const;
    void saveOutputHtmlFile(std::string const& processedFilePath) const;
    void saveFrequencyDatabaseIfNoError();

    void processDirectory(std::string const & directoryPath);
    void processFile(std::string const & fileName);

    Line findLeftLine(AprgBitmapSnippet const& snippet) const;
    Line findRightLine(AprgBitmapSnippet const& snippet) const;
    Line findTopLine(AprgBitmapSnippet const& snippet) const;
    Line findBottomLine(AprgBitmapSnippet const& snippet) const;
    Line findVerticalLine(AprgBitmapSnippet const& snippet, RangeOfInts const& range) const;
    Line findHorizontalLine(AprgBitmapSnippet const& snippet, RangeOfInts const& range) const;
    Line findLeftLineUsingStartingLine(AprgBitmapSnippet const& snippet, Line startingLine) const;
    Line findRightLineUsingStartingLine(AprgBitmapSnippet const& snippet, Line startingLine) const;
    Line findVerticalLineUsingStartingLine(AprgBitmapSnippet const& snippet, Line startingLine, RangeOfInts const& rangeForX) const;
    Line getLineModel(TwoDimensionsStatistics::Samples const& samples) const;
    VectorOfDoubles getAcceptableSquareErrorsUsingKMeans(TwoDimensionsStatistics::ValueToSampleMultimap const& squareErrorToSampleMultimap) const;
    VectorOfDoubles getAcceptableSquareErrorsUsingRetainRatio(TwoDimensionsStatistics::ValueToSampleMultimap const& squareErrorToSampleMultimap) const;
    void updateSamplesForLineModelingFromSquareErrorToSampleMultimap(TwoDimensionsStatistics::Samples & samplesLineModeling, TwoDimensionsStatistics::ValueToSampleMultimap const& squareErrorToSampleMultimap) const;

    void processColumn(AprgBitmapSnippet const& snippet, Line const& leftLine, Line const& rightLine, unsigned int const columnNumber);
    unsigned int getAnswerToQuestion(AprgBitmapSnippet const& snippet, QuestionBarCoordinate const& leftCoordinate, QuestionBarCoordinate const& rightCoordinate) const;
    bool isChoiceShaded(AprgBitmapSnippet const& snippet, Point const& leftPoint, Point const& rightPoint, unsigned int const choiceIndex, unsigned int const radius) const;
    QuestionBarCoordinates getQuestionBarCoordinatesFromLine(AprgBitmapSnippet const& snippet, Line const& line, unsigned int const numberQuestionsInColumn) const;
    bool isWithinLineDeviation(double const lineWidthAverage, double const currentWidth) const;
    bool isWithinBarDeviation(double const barWidthAverage, double const currentWidth) const;
    VectorOfPointAndWidth getPointsAndWidths(AprgBitmapSnippet const& snippet, Line const& line) const;
    LineAndBarWidths getAverageLineAndBarWidthUsingKMeans(VectorOfPointAndWidth const& widthToSampleUnorderedMultimap) const;
    TwoDimensionsStatistics::ValueToSampleMultimap getWidthToSampleMultimap(VectorOfPointAndWidth const& widthToSampleUnorderedMultimap) const;
    void initializeWidthsForKMeans(OneDimensionKMeans & kMeans, TwoDimensionsStatistics::ValueToSampleMultimap const& widthToSampleMultimap) const;
    void removeDeviatedWidthsUsingKMeans(OneDimensionKMeans & kMeans, TwoDimensionsStatistics::ValueToSampleMultimap const& widthToSampleMultimap) const;
    void addWidthToKMeansIfNeeded(OneDimensionKMeans & kMeans, OneDimensionKMeans::Samples const& groupOfSamples, TwoDimensionsStatistics::ValueToSampleMultimap const& widthToSampleMultimap, unsigned int const minimumGroupSize) const;
    RangeOfDoubles getMinMaxRangeFromKMeansSamples(OneDimensionKMeans::Samples const& samples) const;
    Points getNearestBlackPointsFromLine(AprgBitmapSnippet const& snippet, Line const& line) const;
    Point getNearestBlackPointFromLine(AprgBitmapSnippet const& snippet, Line const& line, Point const& point) const;
    double getBarWidthFromBlackPoint(AprgBitmapSnippet const& snippet, Line const& line, Point const& blackPoint) const;
    void initializeKMeansWithBarPoints(TwoDimensionKMeans & barPointKMeans, VectorOfPointAndWidth const& pointsAndWidths, LineAndBarWidths const& widthAverages) const;
    void saveHeightDetailsFromBarPoints(TwoDimensionKMeans::GroupOfSamples const& groupOfGroupOfBarPoints, OneDimensionStatistics::Samples & barHeights, DataCollection<double> & heightCollection) const;
    void removeIncorrectBarPointsWithKMeans(TwoDimensionKMeans & barPointKMeans, TwoDimensionKMeans & barPointKMeansForCalculation, unsigned int const numberQuestionsInColumn, double const totalHeight) const;
    void removeIncorrectBarPointsByHeight(TwoDimensionKMeans & barPointKMeans, TwoDimensionKMeans & barPointKMeansForCalculation, DataCollection<double> const& heightCollection, TwoDimensionKMeans::GroupOfSamples const& groupOfGroupOfBarPoints) const;
    void adjustHeightUntilTargetHeight(DequeOfPoints & dequeWithHighestHeight, DataCollection<double> const& heightCollection, double height) const;
    void saveQuestionBarCoordinatesFromKMeansWithBarPoints(TwoDimensionKMeans const& barPointKMeans, QuestionBarCoordinates & questionBarCoordinates, unsigned int const numberQuestionsInColumn) const;
    void writeLineInBitmap(AprgBitmap & bitmap, Line const& line) const;
    BitmapXY convertToBitmapXY(Point const& point) const;
    BitmapXY convertToBitmapXY(TwoDimensionsStatistics::Sample const& sample) const;
    Point convertToPoint(BitmapXY const& bitmapXY) const;
    Point convertToPoint(TwoDimensionsStatistics::Sample const& sample) const;
    TwoDimensionsStatistics::Sample convertToTwoDimensionSample(Point const& point) const;

    SoosaConfiguration m_configuration;
    unsigned int m_numberOfRespondents;
    std::map<unsigned int, unsigned int> m_questionToAnswersMap;
    FrequencyDatabase m_frequencyDatabase;
};

}
