#pragma once

#include <AprgBitmap.hpp>
#include <AprgBitmapSnippet.hpp>
#include <Container/AlbaRange.hpp>
#include <SoosaConfiguration.hpp>
#include <SoosaStatus.hpp>
#include <TwoDimensions/Line.hpp>
#include <TwoDimensionsStatistics.hpp>

#include <array>
#include <fstream>
#include <map>
#include <string>
#include <vector>

#define MAXQUESTIONS 30
#define MAXQUESTIONSALL 60

namespace alba
{

class SOOSA
{
//NEW WAY:
public:
    class FrequencyDatabase
    {
    public:
        FrequencyDatabase(unsigned int numberOfQuestions);
        void clear();
        void addAnswer(unsigned int const questionNumber, unsigned int const answer);
        unsigned int getFrequencyOfAnswer(unsigned int const questionNumber, unsigned int const answer);
    private:
        unsigned int m_numberOfQuestions;
        std::map<unsigned int, std::array<unsigned int, 5>> m_questionToAnswerFrequencyMap;
    };
    using BitmapRange = AlbaRange<int>;

    SOOSA(SoosaConfiguration const& configuration);
    unsigned int getNumberOfAnswers() const;
    unsigned int getAnswerToQuestion(unsigned int const questionNumber) const;
private:
    std::string getCsvFileName(std::string const& path) const;
    std::string getReportHtmlFileName(std::string const& path) const;
    std::string getPrintableStringForPercentage(double const numerator, double const denominator) const;
    void setAnswerToQuestionInColumn(unsigned int const columnNumber, unsigned int const questionOffsetInColumn, unsigned int const answer);
    void saveDataToCsvFile(std::string const& processedFilePath);
    void saveHeadersToCsvFile();
    void saveOutputHtmlFile(std::string const& processedFilePath);
    Line findLeftLine(AprgBitmapSnippet const& snippet);
    Line findRightLine(AprgBitmapSnippet const& snippet);
    Line findTopLine(AprgBitmapSnippet const& snippet);
    Line findBottomLine(AprgBitmapSnippet const& snippet);
    Line findVerticalLine(AprgBitmapSnippet const& snippet, BitmapRange const& range1, BitmapRange const& range2);
    Line findHorizontalLine(AprgBitmapSnippet const& snippet, BitmapRange const& range1, BitmapRange const& range2);
    Line getLineModel(TwoDimensionsStatistics::Samples & samples);
    SoosaConfiguration m_configuration;
    SoosaStatus m_status;
    unsigned int m_numberOfRespondents;
    std::map<unsigned int, unsigned int> m_questionToAnswersMap;
    FrequencyDatabase m_frequencyDatabase;





//OLD WAY

    typedef struct DATAXYPAIR{
        int _x;
        int _y;
    }PairXY;

    typedef struct CHEBYCHEVCRITERION{
        double mean;
        double stddev;
    }ChebyshevCriterion;

    typedef struct CIRCLECRITERION{
        int radius;
        int diameter;
        int radiussquared;
    }CircleCriterion;

    typedef struct SLOPEANDINTERCEPT{
        double slope;
        double intercept;
    }LineSlopeIntercept;

    int gddx, gddy;


    void getChebyshevInt(ChebyshevCriterion* in_cc, int* arr, int num);
    void getChebyshevDouble(ChebyshevCriterion* in_cc, double* arr, int num);
    void getChebyshevFreqIndex(ChebyshevCriterion* in_cc, int* freqarr,int* indexarr, int start, int finish);
    inline int checkIfWithinImageBounds(PairXY in_point, int xSize, int ySize);
    inline int absValInt(int in);
    inline double absValDouble(double in);
    inline double getKFromChebyshev(ChebyshevCriterion cc, double in);
    inline int roundOffSignRobust(double in);
    inline int rasterRound(double in);
    inline int roundDown(double in);
    inline PairXY createXY(int x, int y);
    inline PairXY getMidpoint(PairXY P1, PairXY P2);
    inline PairXY transposePoint(PairXY inpoint, int xorigin, int yorigin);
    inline LineSlopeIntercept transposeLine(LineSlopeIntercept inlsi, int slopetype, int xorigin, int yorigin);
    inline PairXY findIntersection(LineSlopeIntercept verticalLine, LineSlopeIntercept horizontalLine);
    inline void assignCircleCriterion(CircleCriterion* circ, int radius);
    inline void assignMidCircleCriterion(CircleCriterion* circ, CircleCriterion* c1, CircleCriterion* c2, int type);
    inline double checkIfShaded(AprgBitmapSnippet const& snippet, PairXY center, CircleCriterion circ);
    inline int processOneQuestion(AprgBitmapSnippet const& snippet, PairXY point1, PairXY point2, int ques, int col, CircleCriterion circ);
    int processOneColumn(AprgBitmapSnippet const& snippet, PairXY* QuesArr1, PairXY* QuesArr2, int numQuestionsColumn, int columnNumber);
    inline int followLineGetLengthX(AprgBitmapSnippet const& snippet, PairXY start, PairXY p1);
    int findLineImageFromLeft(AprgBitmapSnippet const& snippet, PairXY* in_line, int numberOfSamples, PairXY inStart, PairXY inEnd);
    int findLineImageFromRight(AprgBitmapSnippet const& snippet, PairXY* in_line, int numberOfSamples, PairXY inStart, PairXY inEnd);
    int findLineImageFromTop(AprgBitmapSnippet const& snippet, PairXY* in_line, int numberOfSamples, PairXY inStart, PairXY inEnd);
    int findLineImageFromBottom(AprgBitmapSnippet const& snippet, PairXY* in_line, int numsamplesize, PairXY inStart,PairXY inEnd);
    inline int getSlope(PairXY* in_samples,double* out_slope, int nsize, int type);
    inline double getBarHeight(PairXY point1,PairXY point2);
    inline void getBarHeightArr(PairXY* questionsCoor,double* barHeight, int nsize);
    inline double getIntercept(PairXY* in_samples,double slope, int nsize, int type);
    int removeOutliersFromLine(PairXY* lineSamples, double* invslope, ChebyshevCriterion* chebycriterion, int numLineSamples, int type);
    int removeOutliersFromLineSmart(PairXY* lineSamples, int numLineSamples, int numLineSamplesDesired, int type);
    void getQFindSamples(PairXY* qFindSamples, int numQFindSamples, PairXY start, PairXY finish, LineSlopeIntercept lsi, int barheightsamplepixels);
    int getBarWidthCorrectPoint(AprgBitmapSnippet const& snippet, double invslope, PairXY* io_point, int correctPoint);
    int barWidthGetCriterion(int *barWidth, int barWidthArrSize, ChebyshevCriterion* ccLine, ChebyshevCriterion* ccBar);
    void getQuestions(AprgBitmapSnippet const& snippet, PairXY* in_questions, int* in_numQuestion, PairXY* qFindSamples, int* qFindSamplesType, int* barWidth, int numQFindSamples, LineSlopeIntercept tslopeintercept, ChebyshevCriterion ccLine, ChebyshevCriterion ccBar);
    int getQuestionsFromLine(AprgBitmapSnippet const& snippet, PairXY* out_questions, int numExpectedQuestions, double* tdoublearr, LineSlopeIntercept tslopeintercept, PairXY tcornerup, PairXY tcornerdown, int barheightsamplepixels);
    void processOneFile(std::string const & fileName);
    void processDirectory(std::string const & directoryPath);
    bool isStatusNoError(SoosaStatus const status);

public:
    int process();
};

}
