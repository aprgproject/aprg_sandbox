#pragma once

#include <SoosaConfiguration.hpp>
#include <SoosaStatus.hpp>

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

    SOOSA(SoosaConfiguration const& configuration);
    void clearFrequencyDatabase();
    void saveFormDetailsFromUserInterface();
    void saveFormDetailsFromFormDetailsPath(std::string const& formDetailsFilePath);
    unsigned int getAnswerToQuestion(unsigned int const questionNumber) const;
private:
    std::string getCsvFileName(std::string const& path) const;
    std::string getReportHtmlFileName(std::string const& path) const;
    std::string getPrintableStringForPercentage(double const numerator, double const denominator) const;
    std::string getPathOfFormDetailsUsingUserInterface() const;
    void setAnswerToQuestion(unsigned int const columnNumber, unsigned int const questionOffset, unsigned int const answer);
    void addToFrequencyDatabase(unsigned int const questionNumber, unsigned int const answer);
    void saveDataToCsvFile(std::string const& processedFilePath);
    void saveHeadersToCsvFile();
    void saveOutputHtmlFile(std::string const& processedFilePath);
    SoosaConfiguration m_configuration;
    SoosaStatus m_status;
    std::map<unsigned int, unsigned int> m_questionToAnswersMap;
    std::map<unsigned int, std::array<unsigned int, 6>> m_questionToAnswerFrequencyMap;




//OLD WAY

    typedef struct DATAXYPAIR{
        int _x;
        int _y;    }PairXY;

    typedef struct DATA2BIT{
        int status; //if 0 then Empty, if 1 then points added, if 2 then allocated and ready to use        int xlow;
        int ylow;
        int xhigh;
        int yhigh;
        int xSizeBytesAllocated;
        int ySizeBytesAllocated;
        unsigned char* buf;
    }DataDigital;

    typedef struct BMPIMAGE2BIT{
        int xSize;
        int ySize;
        int rasterPad;
        int setColor;
        long rasterBegin;
        long numBytesOneRow;
        FILE* filePtr;
    }BmpImage;

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

    int m_frequencyDatabase[MAXQUESTIONSALL][6];
    int gddx, gddy;
    int G_x=-1, G_y=-1, G_value;


    void getChebyshevInt(ChebyshevCriterion* in_cc, int* arr, int num);
    void getChebyshevDouble(ChebyshevCriterion* in_cc, double* arr, int num);
    void getChebyshevFreqIndex(ChebyshevCriterion* in_cc, int* freqarr,int* indexarr, int start, int finish);
    inline int checkIfWithinImageBounds(PairXY in_point, int xSize, int ySize);
    inline int getValue(DataDigital* indata, int x, int y);
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
    long getImageInfo(FILE* inputFile, long offset, int numberOfChars);
    int openBmpImage(BmpImage* inBmpImage, char const* sbmp);
    inline void closeBmpImage(BmpImage* inBmpImage);
    int getDataFromBmp(BmpImage* inBmpImage,DataDigital* indata);
    inline int allocData(DataDigital* indata);    inline void deAllocData(DataDigital* indata);
    inline void cleanDataDigital(DataDigital* indata);
    inline void printDataDigitalBuffer(DataDigital* indata);
    inline void printDataDigitalProperty(DataDigital* indata);    void addPointToDataDigital(BmpImage* inBmpImage,DataDigital* indata, int xp, int yp);
    inline double checkIfShaded(DataDigital* indata,PairXY center, CircleCriterion circ, int ques, int col, int choice, PairXY point1, PairXY point2);
    inline int processOneQuestion(DataDigital* indata, PairXY point1, PairXY point2, int ques, int col, CircleCriterion circ);
    int processOneColumn(DataDigital* indata, PairXY* QuesArr1, PairXY* QuesArr2, int numQuestionsColumn, int columnNumber);
    inline int followLineGetLengthX(DataDigital* indata,PairXY start, PairXY p1);
    int findLineImageFromLeft(PairXY* in_line, int numsamplesize, unsigned char* in_buf,int xsizebytesallocated,PairXY inStart,PairXY inEnd);
    int findLineImageFromRight(PairXY* in_line, int numsamplesize, unsigned char* in_buf,int xsizebytesallocated,PairXY inStart,PairXY inEnd);
    int findLineImageFromTop(DataDigital* indata, PairXY* in_line, int numsamplesize, PairXY inStart,PairXY inEnd);
    int findLineImageFromBottom(DataDigital* indata, PairXY* in_line, int numsamplesize, PairXY inStart,PairXY inEnd);
    inline int getSlope(PairXY* in_samples,double* out_slope, int nsize, int type);
    inline double getBarHeight(PairXY point1,PairXY point2);
    inline void getBarHeightArr(PairXY* questionsCoor,double* barHeight, int nsize);
    inline double getIntercept(PairXY* in_samples,double slope, int nsize, int type);
    int removeOutliersFromLine(PairXY* lineSamples, double* invslope, ChebyshevCriterion* chebycriterion, int numLineSamples, int type);
    int removeOutliersFromLineSmart(PairXY* lineSamples, int numLineSamples, int numLineSamplesDesired, int type);
    void getQFindSamples(PairXY* qFindSamples, int numQFindSamples, PairXY start, PairXY finish, LineSlopeIntercept lsi, int barheightsamplepixels);
    int getBarWidthCorrectPoint(DataDigital* indata, double invslope, PairXY* io_point, int correctPoint);
    int barWidthGetCriterion(int *barWidth, int barWidthArrSize, ChebyshevCriterion* ccLine, ChebyshevCriterion* ccBar);
    void getQuestions(DataDigital* dd, PairXY* in_questions, int* in_numQuestion, PairXY* qFindSamples, int* qFindSamplesType, int* barWidth, int numQFindSamples, LineSlopeIntercept tslopeintercept, ChebyshevCriterion ccLine, ChebyshevCriterion ccBar);
    int getQuestionsFromLine(DataDigital* in_dd, PairXY* out_questions, int numExpectedQuestions, double* tdoublearr, LineSlopeIntercept tslopeintercept, PairXY tcornerup, PairXY tcornerdown, int barheightsamplepixels);
    void processOneFile(std::string const & fileName);
    void processDirectory(std::string const & directoryPath);
    bool isStatusNoError(SoosaStatus const status);

public:
    int process();};

}