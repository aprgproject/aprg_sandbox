#include "SOOSA.hpp"

#include <File/AlbaFileReader.hpp>
#include <FrequencyStatistics.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <String/AlbaStringHelper.hpp>
#include <User/AlbaUserInterface.hpp>

#include <Debug/AlbaDebug.hpp>
#include <sstream>
#include <iostream>
//OLD HEADERS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

//#define DBGFLAG 1
//#define LOPFLAG 1
//#define CIRFLAG 1

#define NUMBER_OF_SLICES_IN_FIND_LINE 100


#define FILE_PATH_BASIS_HTML APRG_DIR R"(SOOSA2014\basis.html)"
#define MAXQUESTIONSCOOR 60 //2*30 -> MUST be twice of MAXQUESTIONS
#define SAMPLESLINETOALLOC 1000#define ROBUSTSAMPLESLINE 1000
#define ROBUSTMINSAMPLESLINE 100
#define ROBUSTSAMPLESLINETOPBOTTOM 500
#define ROBUSTMINSAMPLESLINETOPBOTTOM 100#define PIXELSPERPENLINE 100
#define PIXELSSEARCHSIZE 200//2*PIXELSPERPENLINE -> MUST be twice of PIXELSPERPENLINE
#define PIXELSCIRCLERADIUSHIGH 16
#define PIXELSCIRCLERADIUSLOW 10
#define PERCENTSHADED 60
#define PIXELSDIRTBLACKDOT 1 //1 black is considered dirt
#define PIXELSDIRTWHITEDOT 4 //4 white is considered dirt
#define STDDEVLOWEST 0.01
#define BARHEIGHTLOW 30
#define BARHEIGHTHIGH 80
#define CHEBYCHEVKVALUE 2.5
#define CHEBYCHEVKVALUEWIDTH 4

#ifdef  CIRFLAG
#define CIRPRINT(...) printf(__VA_ARGS__);
#else
#define CIRPRINT(...)
#endif
#ifdef  LOPFLAG
#define LOPPRINT(...) printf(__VA_ARGS__);
#else
#define LOPPRINT(...)
#endif
#ifdef  DBGFLAG
#define DBGPRINT(...) printf(__VA_ARGS__);
#else
#define DBGPRINT(...)
#endif
#define INFPRINT(...)  printf(__VA_ARGS__);
#define CSVPRINT(...) fprintf(m_csvFile, __VA_ARGS__);

using namespace std;
using namespace alba::TwoDimensionsStatistics;

namespace alba
{

SOOSA::FrequencyDatabase::FrequencyDatabase(unsigned int numberOfQuestions)
    : m_numberOfQuestions(numberOfQuestions)
{
    clear();
}

void SOOSA::FrequencyDatabase::clear()
{
    for(unsigned int i=0; i<m_numberOfQuestions; i++)
    {
        for(unsigned int j=0; j<5; j++)
        {
            m_questionToAnswerFrequencyMap[i][j]=0;
        }    }
}

void SOOSA::FrequencyDatabase::addAnswer(unsigned int const questionNumber, unsigned int const answer)
{
    if(questionNumber<m_numberOfQuestions && answer<=4)
    {
        m_questionToAnswerFrequencyMap[questionNumber][answer]++;
    }
}

unsigned int SOOSA::FrequencyDatabase::getFrequencyOfAnswer(unsigned int const questionNumber, unsigned int const answer)
{
    unsigned int frequency=0;
    if(questionNumber<m_numberOfQuestions && answer<=4)
    {
        frequency = m_questionToAnswerFrequencyMap[questionNumber][answer];
    }
    return frequency;
}

SOOSA::SOOSA(SoosaConfiguration const& configuration)
    : m_configuration(configuration)
    , m_frequencyDatabase(m_configuration.getNumberOfQuestions())
{
    m_numberOfRespondents=0;
}

unsigned int SOOSA::getNumberOfAnswers() const
{
    return m_questionToAnswersMap.size();}

unsigned int SOOSA::getAnswerToQuestion(unsigned int const questionNumber) const
{
    return m_questionToAnswersMap.at(questionNumber);}

string SOOSA::getCsvFileName(string const& path) const
{
    return AlbaLocalPathHandler(path).getDirectory()+"PSS_Report_"+m_configuration.getArea()+"_"+m_configuration.getPeriod()+".csv";
}

string SOOSA::getReportHtmlFileName(string const& path) const
{
    return AlbaLocalPathHandler(path).getDirectory()+"PSS_Report_"+m_configuration.getArea()+"_"+m_configuration.getPeriod()+".html";
}

string SOOSA::getPrintableStringForPercentage(double const numerator, double const denominator) const
{
    stringstream ss;
    ss.precision(5);
    if(denominator==0)
    {
        ss << " - ";
    }
    else
    {
        ss << (numerator/denominator*100) << "%";
    }
    return ss.str();
}

void SOOSA::setAnswerToQuestionInColumn(unsigned int const columnNumber, unsigned int const questionOffsetInColumn, unsigned int const answer)
{
    m_questionToAnswersMap[m_configuration.getQuestionNumberInColumn(columnNumber, questionOffsetInColumn)] = answer;
}


void SOOSA::saveDataToCsvFile(string const& processedFilePath)
{    ofstream outputCsvReportStream(getCsvFileName(m_configuration.getPath()), ofstream::app);
    if(m_configuration.getNumberOfQuestions() != m_questionToAnswersMap.size())
    {
        m_status = SoosaStatus::AlgorithmError;    }
    if(isStatusNoError(m_status))
    {
        outputCsvReportStream<<processedFilePath<<",OK";
        for(unsigned int i=0;i<m_configuration.getNumberOfQuestions();i++)
        {
            outputCsvReportStream<<","<<getAnswerToQuestion(i);
            m_frequencyDatabase.addAnswer(i, getAnswerToQuestion(i)-1);
        }
        outputCsvReportStream<<endl;
    }    else
    {
        outputCsvReportStream<<processedFilePath<<","<<getString(m_status)<<endl;
    }}

void SOOSA::saveHeadersToCsvFile()
{
    ofstream outputCsvReportStream(getCsvFileName(m_configuration.getPath()));
    outputCsvReportStream << "FILE,STATUS";
    for(unsigned int i=0; i<m_configuration.getNumberOfQuestions(); i++)
    {
        outputCsvReportStream<<",Question_"<<i+1;
    }
    outputCsvReportStream<<endl;
}

void SOOSA::saveOutputHtmlFile(string const& processedFilePath)
{
    cout<<"saveOutputHtmlFile"<<endl;

    ifstream htmlBasisFileStream(FILE_PATH_BASIS_HTML);
    AlbaFileReader htmlBasisFileReader(htmlBasisFileStream);
    ofstream reportHtmlFileStream(getReportHtmlFileName(processedFilePath));
    reportHtmlFileStream.precision(5);
    while(htmlBasisFileReader.isNotFinished())
    {
        string line(htmlBasisFileReader.getLineAndIgnoreWhiteSpaces());
        if(line == "@AAA@")
        {
            reportHtmlFileStream<<m_configuration.getArea();
        }
        else if(line == "@PPP@")
        {
            reportHtmlFileStream<<m_configuration.getPeriod();
        }
        else if(line == "@LLL@")
        {
            reportHtmlFileStream<<"<h2>Number of Respondents: "<<m_numberOfRespondents<<"</h2>"<<endl;
            reportHtmlFileStream<<"<h2>Average Discharges per Month: "<<m_configuration.getDischarge()<<"</h2>"<<endl;
            double dischargeValue(m_configuration.getDischarge());
            reportHtmlFileStream<<"<h2>Percentage of respondents to discharges: "<<getPrintableStringForPercentage(m_numberOfRespondents, dischargeValue)<<"</h2>"<<endl;
        }
        else if(line == "@TTT@")
        {
            for(unsigned int questionIndex=0; questionIndex<m_configuration.getNumberOfQuestions(); questionIndex++)
            {
                reportHtmlFileStream<<"<tr>"<<endl;
                FrequencyStatistics::FrequencySamples samples;
                for(unsigned int answerIndex=0; answerIndex<5; answerIndex++)
                {
                    samples[answerIndex+1] = m_frequencyDatabase.getFrequencyOfAnswer(questionIndex, answerIndex);
                }
                unsigned int numberOfSamplesForQuestion = FrequencyStatistics::calculateNumberOfSamples(samples);
                double median = FrequencyStatistics::calculateMedian(samples);
                if(questionIndex==m_configuration.getNumberOfQuestions()-1)
                {
                    reportHtmlFileStream<<"<td style=\"text-align:left;padding:3px\"><b>"<<m_configuration.getQuestionAt(questionIndex)<<"</b></td>"<<endl;                }
                else
                {
                    reportHtmlFileStream<<"<td style=\"text-align:left;padding:3px\">"<<m_configuration.getQuestionAt(questionIndex)<<"</td>"<<endl;
                }
                reportHtmlFileStream<<"<td style=\"text-align:center;padding:3px\">"<<getPrintableStringForPercentage(m_frequencyDatabase.getFrequencyOfAnswer(questionIndex, 4),numberOfSamplesForQuestion)<<"</td>"<<endl;
                reportHtmlFileStream<<"<td style=\"text-align:center;padding:3px\">"<<getPrintableStringForPercentage(m_frequencyDatabase.getFrequencyOfAnswer(questionIndex, 3),numberOfSamplesForQuestion)<<"</td>"<<endl;
                reportHtmlFileStream<<"<td style=\"text-align:center;padding:3px\">"<<getPrintableStringForPercentage(m_frequencyDatabase.getFrequencyOfAnswer(questionIndex, 2),numberOfSamplesForQuestion)<<"</td>"<<endl;
                reportHtmlFileStream<<"<td style=\"text-align:center;padding:3px\">"<<getPrintableStringForPercentage(m_frequencyDatabase.getFrequencyOfAnswer(questionIndex, 1),numberOfSamplesForQuestion)<<"</td>"<<endl;
                reportHtmlFileStream<<"<td style=\"text-align:center;padding:3px\">"<<getPrintableStringForPercentage(m_frequencyDatabase.getFrequencyOfAnswer(questionIndex, 0),numberOfSamplesForQuestion)<<"</td>"<<endl;
                reportHtmlFileStream<<"<td style=\"text-align:center;padding:3px\">"<<numberOfSamplesForQuestion<<"</td>"<<endl;
                reportHtmlFileStream<<"<td style=\"text-align:center;padding:3px\">"<<median<<"</td>"<<endl;
                reportHtmlFileStream<<"<td style=\"text-align:center;padding:3px\">"<<getPrintableStringForPercentage(m_frequencyDatabase.getFrequencyOfAnswer(questionIndex, 4)+m_frequencyDatabase.getFrequencyOfAnswer(questionIndex, 3)+m_frequencyDatabase.getFrequencyOfAnswer(questionIndex, 2),numberOfSamplesForQuestion)<<"</td>"<<endl;
                reportHtmlFileStream<<"</tr>"<<endl;
            }
        }        else
        {
            reportHtmlFileStream<<line<<endl;
        }
    }
}

Line SOOSA::findLeftLine(AprgBitmapSnippet const& snippet)
{
    unsigned int incrementInY(snippet.getDeltaY()/NUMBER_OF_SLICES_IN_FIND_LINE);
    BitmapRange rangeForX(snippet.getTopLeftCorner().getX(), snippet.getBottomRightCorner().getX(), 1);
    BitmapRange rangeForY(snippet.getTopLeftCorner().getY(), snippet.getBottomRightCorner().getY(), incrementInY);

    return findVerticalLine(snippet, rangeForX, rangeForY);
}

Line SOOSA::findRightLine(AprgBitmapSnippet const& snippet)
{
    unsigned int incrementInY(snippet.getDeltaY()/NUMBER_OF_SLICES_IN_FIND_LINE);
    BitmapRange rangeForX(snippet.getBottomRightCorner().getX(), snippet.getTopLeftCorner().getX(), -1);
    BitmapRange rangeForY(snippet.getTopLeftCorner().getY(), snippet.getBottomRightCorner().getY(), incrementInY);

    return findVerticalLine(snippet, rangeForX, rangeForY);
}

Line SOOSA::findTopLine(AprgBitmapSnippet const& snippet)
{
    unsigned int incrementInX(snippet.getDeltaX()/NUMBER_OF_SLICES_IN_FIND_LINE);
    BitmapRange rangeForX(snippet.getTopLeftCorner().getX(), snippet.getBottomRightCorner().getX(), incrementInX);
    BitmapRange rangeForY(snippet.getTopLeftCorner().getY(), snippet.getBottomRightCorner().getY(), 1);

    return findHorizontalLine(snippet, rangeForY, rangeForX);
}

Line SOOSA::findBottomLine(AprgBitmapSnippet const& snippet)
{
    unsigned int incrementInX(snippet.getDeltaY()/NUMBER_OF_SLICES_IN_FIND_LINE);
    BitmapRange rangeForX(snippet.getTopLeftCorner().getX(), snippet.getBottomRightCorner().getX(), incrementInX);
    BitmapRange rangeForY(snippet.getBottomRightCorner().getY(), snippet.getTopLeftCorner().getY(), -1);

    return findHorizontalLine(snippet, rangeForY, rangeForX);
}

Line SOOSA::findVerticalLine(AprgBitmapSnippet const& snippet, BitmapRange const& rangeForX, BitmapRange const& rangeForY)
{
    BitmapRange::TerminationCondition conditionForX(rangeForX.getTerminationCondition());
    BitmapRange::TerminationCondition conditionForY(rangeForY.getTerminationCondition());
    Samples samples;
    for(unsigned int y=rangeForY.getStartValue(); conditionForY(y, rangeForY.getEndValue()); y+=rangeForY.getInterval())
    {
        bool isBlackEncountered(false);
        for(unsigned int x=rangeForX.getStartValue(); conditionForX(x, rangeForX.getEndValue()); x+=rangeForX.getInterval())
        {
            BitmapXY bitmapPoint(x, y);
            Sample samplePoint{(double) x, (double) y};
            if(snippet.isBlackAt(bitmapPoint))
            {
                samples.emplace_back(samplePoint);
                isBlackEncountered=true;
            }
            else if(isBlackEncountered)
            {
                break;
            }
        }
    }
    return getLineModel(samples);
}

Line SOOSA::findHorizontalLine(AprgBitmapSnippet const& snippet, BitmapRange const& rangeForX, BitmapRange const& rangeForY)
{
    ALBA_PRINT1(rangeForX.getDisplayableString());
    ALBA_PRINT1(rangeForY.getDisplayableString());
    BitmapRange::TerminationCondition conditionForX(rangeForX.getTerminationCondition());
    BitmapRange::TerminationCondition conditionForY(rangeForY.getTerminationCondition());
    Samples samples;
    for(unsigned int x=rangeForX.getStartValue(); conditionForX(x, rangeForX.getEndValue()); x+=rangeForX.getInterval())
    {
        bool isBlackEncountered(false);
        for(unsigned int y=rangeForY.getStartValue(); conditionForY(y, rangeForY.getEndValue()); y+=rangeForY.getInterval())
        {
            BitmapXY bitmapPoint(x, y);
            Sample samplePoint{(double) x, (double) y};
            if(snippet.isBlackAt(bitmapPoint))
            {
                samples.emplace_back(samplePoint);
                isBlackEncountered=true;
            }
            else if(isBlackEncountered)
            {
                break;
            }
        }
    }
    return getLineModel(samples);
}

Line SOOSA::getLineModel(Samples & samples)
{
    int const nonAllowableSquareErrorLimit(4);
    double const samplesRetainRatio(0.90);

    LineModel lineModel;
    double maxSquareErrorInSamples(nonAllowableSquareErrorLimit);
    while (maxSquareErrorInSamples>=nonAllowableSquareErrorLimit && samples.size() > 2)
    {
        lineModel = calculateLineModelUsingLeastSquares(samples);
        sortSamplesBySquareError(samples, lineModel);
        maxSquareErrorInSamples = calculateSquareError(samples.back(), lineModel);
        ALBA_PRINT1(maxSquareErrorInSamples);
        ALBA_PRINT1(samples.size());
        ALBA_PRINT1(samples.size()*samplesRetainRatio);
        if(maxSquareErrorInSamples>=nonAllowableSquareErrorLimit)
        {
            unsigned int totalSamples(samples.size());
            samples.erase(samples.begin()+((unsigned int)(totalSamples*samplesRetainRatio)), samples.end());
        }
    }
    return Line(lineModel.aCoefficient, lineModel.bCoefficient, lineModel.cCoefficient);
}


void writeLineInBitmap(AprgBitmap & bitmap, Line const& line)
{
    ALBA_PRINT3(line.getACoefficient(), line.getBCoefficient(), line.getCCoefficient());

    BitmapSignedXY topLeft(-1,-100);
    BitmapSignedXY bottomRight(3195,3967);

    ALBA_PRINT2(topLeft.getDisplayableString(), bottomRight.getDisplayableString());
    AprgBitmapSnippet snippet(bitmap.getSnippetReadFromFileWithOutOfRangeCoordinates(topLeft.getX(), topLeft.getY(), bottomRight.getX(), bottomRight.getY()));
    Points points(line.getPoints(Point(topLeft.getX(), topLeft.getY()), Point(bottomRight.getX(), bottomRight.getY()), 1));
    for (Point point: points)
    {
        snippet.setPixelAt(BitmapXY(point.getX(), point.getY()), 0x00EE0000);
    }
    bitmap.setSnippetWriteToFile(snippet);
}























void SOOSA::getChebyshevInt(ChebyshevCriterion* in_cc, int* arr, int num)
{
    int i;    double mean=0, stddev=0;
    for(i=0; i<num; i++){
        LOPPRINT("  FUNCLOOP:getChebyshevInt[i=%d]->(arr[i]=%d|mean=%lf)\n",i,arr[i],mean);
        mean=mean+arr[i];    }
    mean=mean/num;
    for(i=0; i<num; i++){
        LOPPRINT("  FUNCLOOP:getChebyshevInt[i=%d]->(arr[i]=%d|stddev=%lf)\n",i,arr[i],stddev);
        stddev=stddev+pow(arr[i]-mean,2);
    }
    stddev=stddev/num;
    stddev=sqrt(stddev);
    in_cc->mean=mean;
    in_cc->stddev=stddev;
    DBGPRINT("  FUNC:getChebyshevInt(mean=%lf|stddev=%lf)\n",in_cc->mean,in_cc->stddev);
}

void SOOSA::getChebyshevDouble(ChebyshevCriterion* in_cc, double* arr, int num)
{
    int i;
    double mean=0, stddev=0;
    for(i=0; i<num; i++){
        LOPPRINT("  FUNCLOOP:getChebyshevDouble[i=%d]->(arr[i]=%lf|mean=%lf)\n",i,arr[i],mean);
        mean=mean+arr[i];
    }
    mean=mean/num;
    for(i=0; i<num; i++){
        LOPPRINT("  FUNCLOOP:getChebyshevDouble[i=%d]->(arr[i]=%lf|stddev=%lf)\n",i,arr[i],stddev);
        stddev=stddev+pow(arr[i]-mean,2);
    }
    stddev=stddev/num;
    stddev=sqrt(stddev);
    in_cc->mean=mean;
    in_cc->stddev=stddev;
    DBGPRINT("  FUNC:getChebyshevDouble(mean=%lf|stddev=%lf)\n",in_cc->mean,in_cc->stddev);
}

void SOOSA::getChebyshevFreqIndex(ChebyshevCriterion* in_cc, int* freqarr,int* indexarr, int start, int finish)
{
    int i,numofitems=0;
    double mean=0, stddev=0;
    for(i=start; i<finish; i++){
        LOPPRINT("  FUNCLOOP:getChebyshevFreqIndex[i=%d]->(indexarr[i]=%d|freqarr[i]=%d|mean=%lf)\n",i,indexarr[i],freqarr[i],mean);
        mean = mean+(indexarr[i]*freqarr[i]);
        numofitems = numofitems + freqarr[i];
    }
    mean=mean/numofitems;
    for(i=start; i<finish; i++){
        LOPPRINT("  FUNCLOOP:getChebyshevFreqIndex[i=%d]->(indexarr[i]=%d|freqarr[i]=%d|stddev=%lf)\n",i,indexarr[i],freqarr[i],stddev);
        stddev=stddev+pow(indexarr[i]-mean,2)*freqarr[i];
    }
    stddev=stddev/numofitems;
    stddev=sqrt(stddev);
    in_cc->mean=mean;
    in_cc->stddev=stddev;
    DBGPRINT("  FUNC:getChebyshevFreqIndex(mean=%lf|stddev=%lf)\n",in_cc->mean,in_cc->stddev);
}

inline int SOOSA::checkIfWithinImageBounds(PairXY in_point, int xSize, int ySize)
{
    if(in_point._x<0 || in_point._y<0 || in_point._x>xSize || in_point._y>ySize){return 1;}
    return 0;
}

inline int SOOSA::absValInt(int in)
{
    if(in<0){
        LOPPRINT("  FUNC:absValInt(%d)->ret=%d\n",in,in*-1);
        return in*-1;
    }
    LOPPRINT("  FUNC:absValInt(%d)->ret=%d\n",in,in);
    return in;
}

inline double SOOSA::absValDouble(double in)
{
    if(in<0){
        LOPPRINT("  FUNC:absValDouble(%lf)->ret=%lf\n",in,in*-1);
        return in*-1;
    }
    LOPPRINT("  FUNC:absValDouble(%lf)->ret=%lf\n",in,in);
    return in;
}

inline double SOOSA::getKFromChebyshev(ChebyshevCriterion cc, double in)
{
    if(cc.stddev<STDDEVLOWEST)
    {
        return absValDouble((in-cc.mean)/STDDEVLOWEST);
    }
    return absValDouble((in-cc.mean)/cc.stddev);
}

inline int SOOSA::roundOffSignRobust(double in)
{
    double absDou=absValDouble(in);
    int sign;
    if(in<0){sign=-1;}else{sign=1;}
    if(absDou-(int)absDou>=0.5){absDou=absDou+1;}
    LOPPRINT("  FUNC:roundOffSignRobust(%lf)->ret=%d\n",in,(((int)absDou)*sign));
    return (((int)absDou)*sign);
}

inline int SOOSA::rasterRound(double in)
{
    if(in-(int)in>0){
        LOPPRINT("  FUNC:rasterRound(%lf)->ret=%d\n",in,(int)in+1);
        return (int)in+1;
    }
    LOPPRINT("  FUNC:rasterRound(%lf)->ret=%d\n",in,(int)in);
    return (int)in;
}

inline int SOOSA::roundDown(double in)
{
    if(in-(int)in>0){
        LOPPRINT("  FUNC:roundDown(%lf)->ret=%d\n",in,(int)in);
        return (int)in;
    }
    LOPPRINT("  FUNC:roundDown(%lf)->ret=%d\n",in,(int)in);
    return (int)in;
}

inline SOOSA::PairXY SOOSA::createXY(int x, int y)
{
    PairXY t1;t1._x=x;t1._y=y;return t1;
}

inline SOOSA::PairXY SOOSA::getMidpoint(PairXY P1, PairXY P2)
{
    PairXY outpoint;
    outpoint._x=roundOffSignRobust(((double)P1._x+P2._x)/2);
    outpoint._y=roundOffSignRobust(((double)P1._y+P2._y)/2);
    LOPPRINT("  FUNC:getMidpoint(%d,%d),(%d,%d)->(%d,%d)\n",P1._x,P1._y,P2._x,P2._y,outpoint._x,outpoint._y);
    return outpoint;
}

inline SOOSA::PairXY SOOSA::transposePoint(PairXY inpoint, int xorigin, int yorigin)
{
    PairXY outpoint;
    LOPPRINT("  FUNC:transposePoint(%d,%d),(%d,%d)\n",inpoint._x,inpoint._y,xorigin,yorigin);
    outpoint._x=(inpoint._x)-xorigin;
    outpoint._y=(inpoint._y)-yorigin;
    return outpoint;
}

inline SOOSA::LineSlopeIntercept SOOSA::transposeLine(LineSlopeIntercept inlsi, int slopetype, int xorigin, int yorigin)
{
    LineSlopeIntercept outlsi;
    outlsi.intercept = 0; outlsi.slope = 0;
    if(slopetype==0){//vertical line
        outlsi.intercept = inlsi.intercept-xorigin+(inlsi.slope*yorigin);
        outlsi.slope = inlsi.slope;
    }else if(slopetype==1){//horizontal line
        outlsi.intercept = inlsi.intercept-yorigin+(inlsi.slope*xorigin);
        outlsi.slope = inlsi.slope;
    }
    return outlsi;
}

inline SOOSA::PairXY SOOSA::findIntersection(LineSlopeIntercept verticalLine, LineSlopeIntercept horizontalLine)
{
    PairXY outpoint;
    outpoint._x=roundOffSignRobust(((verticalLine.slope*horizontalLine.intercept)+verticalLine.intercept)/(1-(horizontalLine.slope*verticalLine.slope)));
    outpoint._y=roundOffSignRobust(((horizontalLine.slope*verticalLine.intercept)+horizontalLine.intercept)/(1-(horizontalLine.slope*verticalLine.slope)));
    return outpoint;
}

inline void SOOSA::assignCircleCriterion(CircleCriterion* circ, int radius)
{
    circ->radius=radius;
    circ->diameter=radius*2;
    circ->radiussquared=pow(radius,2);
}

inline void SOOSA::assignMidCircleCriterion(CircleCriterion* circ, CircleCriterion* c1, CircleCriterion* c2, int type)
{
    int radius;
    if(type==1){radius=roundOffSignRobust(((double)c1->radius+c2->radius)/2);}
    else{radius=roundDown(((double)c1->radius+c2->radius)/2);}
    circ->radius=radius;
    circ->diameter=radius*2;
    circ->radiussquared=pow(radius,2);
}


inline double SOOSA::checkIfShaded(AprgBitmapSnippet const& snippet, PairXY center, CircleCriterion circ)
{
    int startx,starty,incx,incy,diameter;
    int countall,countblack;
    int noChange,type,moved;
    double scorePercent,maxScorePercent;
    noChange=0;
    type=0; moved=0;
    scorePercent=0; maxScorePercent=0;
    while(noChange!=0x1111){
        if(type>=5){type=1;noChange=0;}
        if(type==1){ center._x=center._x+1;
        }else if(type==2){ center._y=center._y+1;
        }else if(type==3){ center._y=center._y-1;
        }else if(type==4){ center._x=center._x-1;
        }
        startx = center._x-circ.radius;
        starty = center._y-circ.radius;
        diameter = circ.diameter;
        countall=0;countblack=0;
        for(incy=0;incy<=diameter;incy++){
            for(incx=0;incx<=diameter;incx++){
                if(pow(incx-circ.radius,2)+pow(incy-circ.radius,2)<=circ.radiussquared){
                    countall++;
                    if(snippet.isBlackAt(BitmapXY(startx+incx+gddx, starty+incy+gddy))){
                        countblack++;CIRPRINT("X");
                    }else{CIRPRINT("-");}
                }else{CIRPRINT("_");}
            }CIRPRINT("\n");
        }
        scorePercent = (double)countblack/countall*100;
        if(type==0){maxScorePercent=scorePercent;}
        if(maxScorePercent<scorePercent){
            moved=1;
        }else{
            if(type==1){ center._x=center._x-1;
            }else if(type==2){ center._y=center._y-1;
            }else if(type==3){ center._y=center._y+1;
            }else if(type==4){ center._x=center._x+1;
            }
        }
        if(moved==0){
            if(type==1){ noChange=noChange|0x0001;
            }else if(type==2){ noChange=noChange|0x0010;
            }else if(type==3){ noChange=noChange|0x0100;
            }else if(type==4){ noChange=noChange|0x1000;
            }
        }
        CIRPRINT("CircleCenter:(%d,%d)\n",center._x+gddx,center._y+gddy);
        CIRPRINT("PointLeft:(%d,%d) PointRight:(%d,%d)\n",point1._x+gddx,point1._y+gddy,point2._x+gddx,point2._y+gddy);
        CIRPRINT("[type:%d|noChange:%4X|moved:%d]->[ScorePercent=%lf | maxScorePercent=%lf]\n",type,noChange,moved,scorePercent,maxScorePercent);
        if(maxScorePercent<scorePercent){
            maxScorePercent=scorePercent;
        }else{
            moved=0;
            type++;
        }
        if(maxScorePercent>=PERCENTSHADED){break;}
    }
#ifdef CIRFLAG
    fclose(circlefile);
#endif
    DBGPRINT("  FUNC:checkIfShaded out=%3.2lf\n",((double)countblack/countall*100));
    return maxScorePercent;
}

inline int SOOSA::processOneQuestion(AprgBitmapSnippet const& snippet, PairXY point1, PairXY point2, int ques, int col, CircleCriterion circ)
{
    DBGPRINT("  FUNC:processOneQuestion point1(%d,%d) point2(%d,%d)\n",point1._x+gddx,point1._y+gddy,point2._x+gddx,point2._y+gddy);
    PairXY temppoint;
    int t1,tch;
    double dtemp;
    tch=0;
    for(t1=0;t1<5;t1++){
        dtemp = (((double)t1*2)+1)/10;
        CIRPRINT("DTEMP:%lf (%d + %d)\n",dtemp,point1._x+gddx,roundOffSignRobust(((double)point2._x-point1._x)*dtemp));
        CIRPRINT("POINT1:(%d,%d)\n",point1._x+gddx,point1._y+gddy);
        CIRPRINT("POINT2:(%d,%d)\n",point2._x+gddx,point2._y+gddy);
        temppoint._x = point1._x+ roundOffSignRobust(((double)point2._x-point1._x)*dtemp);
        temppoint._y = point1._y+ roundOffSignRobust(((double)point2._y-point1._y)*dtemp);
        CIRPRINT("TPOINT:(%d,%d)\n",temppoint._x+gddx,temppoint._y+gddy);
        dtemp = checkIfShaded(snippet, temppoint,circ);
        LOPPRINT("  FUNCLOOP:processOneQuestion (x=%d,y=%d,t1=%d)->%lf\n",temppoint._x+gddx,temppoint._y+gddy,t1,dtemp);
        if(dtemp>PERCENTSHADED){
            if(tch==0)
            {
                tch=5-t1;
            }else
            {
                cout<<"WARN: Multiple answers in ques#="<<ques<<" column="<<col<<" r="<<circ.radius<<". Answers: "<<tch<<" and "<<5-t1<<endl;
                return 6;
            }
        }
    }
#ifdef CIRFLAG
    fclose(circlefile);
#endif
    if(tch!=0){
        return tch;
    }else
    {
        cout<<"WARN: No answer in ques#="<<ques<<" column="<<col<<" r="<<circ.radius<<endl;
        return 0;
    }
}

int SOOSA::processOneColumn(AprgBitmapSnippet const& snippet, PairXY* QuesArr1, PairXY* QuesArr2, int numQuestionsColumn, int columnNumber)
{
    int t1, t2, iteration, tchoice;
    PairXY point1, point2;
    int xlow=gddx, ylow=gddy;
    CircleCriterion circhighest, circlowest, clow, chigh, currentcirc;
    assignCircleCriterion(&circhighest,PIXELSCIRCLERADIUSHIGH);
    assignCircleCriterion(&circlowest,PIXELSCIRCLERADIUSLOW);
    assignMidCircleCriterion(&currentcirc,&circlowest,&circhighest,1);

    t2=0;
    DBGPRINT("  FUNC:processOneColumn low(x=%d,y=%d)\n",gddx,gddy);
    tchoice=0;
    for(t1=0;t1<numQuestionsColumn;t1++){
        point1 = getMidpoint(QuesArr1[t2],QuesArr1[t2+1]);
        point2 = getMidpoint(QuesArr2[t2],QuesArr2[t2+1]);
        LOPPRINT("  FUNCLOOP:processOneColumn point1(x=%d,y=%d) point1(x=%d,y=%d)\n",point1._x,point1._y,point2._x,point2._y);
        point1 = transposePoint(point1,xlow,ylow);
        point2 = transposePoint(point2,xlow,ylow);
        clow=circlowest; chigh=circhighest;
        iteration=0;
        do
        {
            tchoice = processOneQuestion(snippet, point1, point2, t1+1, columnNumber,currentcirc);
            LOPPRINT("  FUNCLOOPX:processOneColumn tchoice=%d r=%d\n",tchoice,currentcirc.radius);
            if(tchoice==0){
                chigh=currentcirc;
                assignMidCircleCriterion(&currentcirc,&clow,&chigh,0);
                LOPPRINT("INFO:Retrying with more lenient parameters-> ques#=%d r=%d\n",t1+1,currentcirc.radius);
            }else if(tchoice==6){
                clow=currentcirc;
                assignMidCircleCriterion(&currentcirc,&clow,&chigh,1);
                LOPPRINT("INFO:Retrying with more strict parameters-> ques#=%d r=%d\n",t1+1,currentcirc.radius);
            }else{iteration=-1;
                break;
            }
            iteration++;
        }
        while (currentcirc.radius!=circlowest.radius && currentcirc.radius!=circhighest.radius && iteration<5);
        if(iteration!=-1)
        {
            cout<<"ERROR: Error in question number="<<t1+1<<" column="<<columnNumber<<" r="<<currentcirc.radius<<endl;
            //return 1;
        }
        cout<<"Question number="<<t1+1<<" column="<<columnNumber<<" -> choice="<<tchoice<<" r="<<currentcirc.radius<<endl;
        if(columnNumber==1)
        {
            if(tchoice>=1 && tchoice<=5)
            {
                setAnswerToQuestionInColumn(1, t1, tchoice);
            }
            else
            {
                setAnswerToQuestionInColumn(1, t1, 0);
            }
        }else if(columnNumber==2)
        {
            if(tchoice>=1 && tchoice<=5)
            {
                setAnswerToQuestionInColumn(2, t1, tchoice);
            }
            else
            {
                setAnswerToQuestionInColumn(2, t1, 0);
            }
        }
        t2=t2+2;
    }
    return 0;
}

inline int SOOSA::followLineGetLengthX(AprgBitmapSnippet const& snippet, PairXY start, PairXY p1)
{
    //p2 and p3 are opposite directions, use states to dont go backwards
    int state,x,y,pty;
    LOPPRINT("  FUNC:followLineGetLengthX Start(%d|%d) P1(%d|%d) P3(%d|%d)\n",start._x+gddx,start._y+gddy,p1._x+gddx,p1._y+gddy);
    x=start._x; y=start._y; pty=0; state=0;

    while(snippet.isPositionInside(BitmapXY(x+gddx,y-1+gddy)))
    {
        LOPPRINT("  FUNCLOOP:followLineGetLengthX(x=%d|y=%d|pt=%d)\n",x+gddx,y+gddy,pty);
        if(pty>=PIXELSPERPENLINE)
        {
            break;
            LOPPRINT("  FUNCLOOP:followLineGetLengthX->(pty=%d) |Perpendicular line exit\n",pty);
        }
        else if(snippet.isBlackAt(BitmapXY(x+p1._x+gddx,y+p1._y+gddy)))
        {
            x=x+p1._x;
            y=y+p1._y;
            state = 1;
            pty=pty+1;
            LOPPRINT("  FUNCLOOP:followLineGetLengthX->(Follow P1:(%d,%d)\n",x+gddx,y+gddy);
        }
        else if(state==1)
        {
            while(snippet.isPositionInside(BitmapXY(x+gddx,y-1+gddy)) && snippet.isBlackAt(BitmapXY(x+gddx,y-1+gddy)))
            {
                y=y-1;
            }
            state=2;
            LOPPRINT("  FUNCLOOP:followLineGetLengthX->(Find TOP:(%d,%d)\n",x+gddx,y+gddy);
        }
        else if(state==2 && snippet.isBlackAt(BitmapXY(x+gddx,y+1+gddy)))
        {
            y=y+1;
            LOPPRINT("  FUNCLOOP:followLineGetLengthX->(Go Down(%d,%d)\n",x+gddx,y+gddy);
        }
        else
        {
            break;
        }
    }
    LOPPRINT("  FUNC:followLineGetLengthX->(out=%d)\n",pty);
    return pty;
}

int SOOSA::findLineImageFromLeft(AprgBitmapSnippet const& snippet, PairXY* in_line, int numberOfSamples, PairXY inStart, PairXY inEnd)
{
    int lineSamples,pt,ptwhite,lineSamplesSaved;
    lineSamplesSaved=0;
    DBGPRINT("  FUNC:findLineImageFromLeft(startx=%d|starty=%d|endx=%d|endy=%d)\n",inStart._x+gddx,inStart._y+gddy,inEnd._x+gddx,inEnd._y+gddy);
    for(lineSamples=0;lineSamples<numberOfSamples;lineSamples++)
    {
        in_line[lineSamplesSaved]._x = roundOffSignRobust((double)(inEnd._x-inStart._x)*lineSamples/(numberOfSamples))+inStart._x;
        in_line[lineSamplesSaved]._y = roundOffSignRobust((double)(inEnd._y-inStart._y)*lineSamples/(numberOfSamples))+inStart._y;
        LOPPRINT("  FUNCLOOP:findLineImageFromLeft[lt=%d|x=%d|y=%d]\n",lineSamples,in_line[lineSamplesSaved]._x+gddx,in_line[lineSamplesSaved]._y+gddy);
        pt = 0;
        ptwhite=0;
        unsigned int yInSnippet = in_line[lineSamplesSaved]._y+gddy;
        for(unsigned int xInSnippet=in_line[lineSamplesSaved]._x+gddx; xInSnippet<snippet.getBottomRightCorner().getX(); xInSnippet++)
        {
            if(pt>=PIXELSPERPENLINE)
            {
                break;
            }
            if(snippet.isBlackAt(BitmapXY(xInSnippet, yInSnippet)))
            {
                pt=pt+1;
                ptwhite=0;
            }
            else if(pt>PIXELSDIRTBLACKDOT && ptwhite>=PIXELSDIRTWHITEDOT)
            {
                pt=pt-ptwhite;
                in_line[lineSamplesSaved]._x = roundOffSignRobust(xInSnippet-gddx-1-pt+(((double)pt)/2)-ptwhite );//minus-1 to get last white
                LOPPRINT("  FUNCLOOPXXX:findLineImageFromLeft Successful->[x=%d|y=%d]\n",in_line[lineSamplesSaved]._x+gddx,in_line[lineSamplesSaved]._y+gddy);
                lineSamplesSaved++;
                break;
            }
            else
            {
                if(ptwhite<PIXELSDIRTWHITEDOT && pt>0)
                {
                    ptwhite++;
                    pt++;
                }
                else
                {
                    pt=0;//if dirt encountered clear once white again
                }
            }
        }
    }
#ifdef  DBGFLAG
    for(lineSamples=0;lineSamples<lineSamplesSaved;lineSamples++){//lineSamples
        DBGPRINT("  FUNCOUT:findLineImageFromLeft[%d]->[x=%d|y=%d]\n",lineSamples,in_line[lineSamples]._x+gddx,in_line[lineSamples]._y+gddy);
    }
#endif
    return lineSamplesSaved;
}

int SOOSA::findLineImageFromRight(AprgBitmapSnippet const& snippet, PairXY* in_line, int numberOfSamples, PairXY inStart, PairXY inEnd)
{
    int lineSamples,pt,ptwhite,lineSamplesSaved;
    lineSamplesSaved=0;
    DBGPRINT("  FUNC:findLineImageFromRight(startx=%d|starty=%d|endx=%d|endy=%d)\n",inStart._x+gddx,inStart._y+gddy,inEnd._x+gddx,inEnd._y+gddy);
    for(lineSamples=0;lineSamples<numberOfSamples;lineSamples++)
    {
        in_line[lineSamplesSaved]._x = roundOffSignRobust((double)(inEnd._x-inStart._x)*lineSamples/(numberOfSamples))+inStart._x;
        in_line[lineSamplesSaved]._y = roundOffSignRobust((double)(inEnd._y-inStart._y)*lineSamples/(numberOfSamples))+inStart._y;
        LOPPRINT("  FUNCLOOP:findLineImageFromRight[lt=%d|x=%d|y=%d]\n",lineSamples,in_line[lineSamplesSaved]._x+gddx,in_line[lineSamplesSaved]._y+gddy);
        pt = 0;
        ptwhite=0;
        unsigned int yInSnippet = in_line[lineSamplesSaved]._y+gddy;
        for(unsigned int xInSnippet=in_line[lineSamplesSaved]._x+gddx; xInSnippet>0; xInSnippet--)
        {
            if(pt>=PIXELSPERPENLINE)
            {
                break;
            }
            if(snippet.isBlackAt(BitmapXY(xInSnippet, yInSnippet)))
            {
                pt=pt+1;
                ptwhite=0;
            }
            else if(pt>PIXELSDIRTBLACKDOT && ptwhite>=PIXELSDIRTWHITEDOT)
            {
                pt=pt-ptwhite;
                in_line[lineSamplesSaved]._x = roundOffSignRobust(xInSnippet-gddx +(((double)pt)/2)+ptwhite);
                LOPPRINT("  FUNCLOOPXXX:findLineImageFromRight Successful->[x=%d|y=%d]\n",in_line[lineSamplesSaved]._x+gddx,in_line[lineSamplesSaved]._y+gddy);
                lineSamplesSaved++;
                break;
            }
            else
            {
                if(ptwhite<PIXELSDIRTWHITEDOT && pt>0)
                {
                    ptwhite++;
                    pt++;
                }
                else
                {
                    pt=0;//if dirt encountered clear once white again
                }
            }
        }
    }
#ifdef  DBGFLAG
    for(lineSamples=0;lineSamples<lineSamplesSaved;lineSamples++){//lineSamples
        DBGPRINT("  FUNCOUT:findLineImageFromRight[%d]->[x=%d|y=%d]\n",lineSamples,in_line[lineSamples]._x+gddx,in_line[lineSamples]._y+gddy);
    }
#endif
    return lineSamplesSaved;
}

int SOOSA::findLineImageFromTop(AprgBitmapSnippet const& snippet, PairXY* in_line, int numberOfSamples, PairXY inStart, PairXY inEnd)
{
    int lineSamples,lineSamplesSaved,pt,iy,pty;
    lineSamplesSaved=0;
    DBGPRINT("  FUNC:findLineImageFromTop(startx=%d|starty=%d|endx=%d|endy=%d)\n",inStart._x+gddx,inStart._y+gddy,inEnd._x+gddx,inEnd._y+gddy);
    for(lineSamples=0;lineSamples<numberOfSamples;lineSamples++)
    {
        in_line[lineSamplesSaved]._x = roundOffSignRobust((double)(inEnd._x-inStart._x)*lineSamples/(numberOfSamples))+inStart._x;
        in_line[lineSamplesSaved]._y = roundOffSignRobust((double)(inEnd._y-inStart._y)*lineSamples/(numberOfSamples))+inStart._y;
        pt = 0;
        LOPPRINT("  FUNCLOOP:findLineImageFromTop[lt=%d|x=%d|y=%d]\n",lineSamples,in_line[lineSamplesSaved]._x+gddx,in_line[lineSamplesSaved]._y+gddy);
        for(iy=in_line[lineSamplesSaved]._y; iy<(int)snippet.getBottomRightCorner().getY(); iy++)
        {
            LOPPRINT("  FUNCLOOPXXX:findLineImageFromTop[x=%d,y=%d|pt=%d|dummy=%d|mask=%d]->bit=%d\n",in_line[lineSamplesSaved]._x+gddx,iy+gddy,pt,dummy,mask,(dummy&mask)==0x00);
            if(pt>=PIXELSPERPENLINE)
            {
                break;
            }
            if(snippet.isBlackAt(BitmapXY(in_line[lineSamplesSaved]._x+gddx, iy+gddy)))
            {
                    pt=pt+1;
            }
            else if(pt>PIXELSDIRTBLACKDOT)
            {
                in_line[lineSamplesSaved]._y = roundOffSignRobust( iy-1-pt+(((double)pt)/2) );//minus-1 to get last white
                pty=1+followLineGetLengthX(snippet,createXY(in_line[lineSamplesSaved]._x,in_line[lineSamplesSaved]._y), createXY(1,0) );
                pty=pty+followLineGetLengthX(snippet,createXY(in_line[lineSamplesSaved]._x,in_line[lineSamplesSaved]._y), createXY(-1,0) );
                if(pty>=PIXELSPERPENLINE)
                {
                    LOPPRINT("  FUNCLOOPXXX:findLineImageFromTop Successful->[x=%d|y=%d]\n",in_line[lineSamplesSaved]._x+gddx,in_line[lineSamplesSaved]._y+gddy);
                    lineSamplesSaved++;
                    break;
                }
                else
                {
                    pt=0;
                }
            }
            else
            {
                pt=0;//if dirt encountered clear once white again
            }
        }
    }
#ifdef  DBGFLAG
    for(lineSamples=0;lineSamples<lineSamplesSaved;lineSamples++){//lineSamples
        DBGPRINT("  FUNCOUT:findLineImageFromTop[%d]->[x=%d|y=%d]\n",lineSamples,in_line[lineSamples]._x+gddx,in_line[lineSamples]._y+gddy);
    }
#endif
    return lineSamplesSaved;
}

int SOOSA::findLineImageFromBottom(AprgBitmapSnippet const& snippet, PairXY* in_line, int numsamplesize, PairXY inStart,PairXY inEnd)
{
    int lineSamples,lineSamplesSaved,pt,iy,pty;
    lineSamplesSaved=0;
    DBGPRINT("  FUNC:findLineImageFromBottom(startx=%d|starty=%d|endx=%d|endy=%d)\n",inStart._x+gddx,inStart._y+gddy,inEnd._x+gddx,inEnd._y+gddy);
    for(lineSamples=0;lineSamples<numsamplesize;lineSamples++)
    {
        in_line[lineSamplesSaved]._x = roundOffSignRobust((double)(inEnd._x-inStart._x)*lineSamples/(numsamplesize))+inStart._x;
        in_line[lineSamplesSaved]._y = roundOffSignRobust((double)(inEnd._y-inStart._y)*lineSamples/(numsamplesize))+inStart._y;
        pt = 0;
        LOPPRINT("  FUNCLOOP:findLineImageFromBottom[lt=%d|x=%d|y=%d]\n",lineSamples,in_line[lineSamplesSaved]._x+gddx,in_line[lineSamplesSaved]._y+gddy);
        for(iy=in_line[lineSamplesSaved]._y; iy>=0; iy--)
        {
            LOPPRINT("  FUNCLOOPXXX:findLineImageFromBottom[x=%d,y=%d|pt=%d|dummy=%d|mask=%d]->bit=%d\n",in_line[lineSamplesSaved]._x+gddx,iy+gddy,pt,dummy,mask,(dummy&mask)==0x00);
            if(pt>=PIXELSPERPENLINE)
            {
                break;
            }
            if(snippet.isBlackAt(BitmapXY(in_line[lineSamplesSaved]._x+gddx, iy+gddy)))
            {
                pt=pt+1;
            }
            else if(pt>PIXELSDIRTBLACKDOT)
            {
                in_line[lineSamplesSaved]._y = roundOffSignRobust( iy+(((double)pt)/2) );//minus-1 to get last white
                pty=1+followLineGetLengthX(snippet, createXY(in_line[lineSamplesSaved]._x,in_line[lineSamplesSaved]._y), createXY(1,0) );
                pty=pty+followLineGetLengthX(snippet, createXY(in_line[lineSamplesSaved]._x,in_line[lineSamplesSaved]._y), createXY(-1,0) );
                if(pty>=PIXELSPERPENLINE)
                {
                    LOPPRINT("  FUNCLOOPXXX:findLineImageFromBottom Successful->[x=%d|y=%d]\n",in_line[lineSamplesSaved]._x+gddx,in_line[lineSamplesSaved]._y+gddy);
                    lineSamplesSaved++;
                    break;
                }
                else
                {
                    pt=0;
                }
            }
            else
            {
                pt=0;//if dirt encountered clear once white again
            }

        }
    }
#ifdef  DBGFLAG
    for(lineSamples=0;lineSamples<lineSamplesSaved;lineSamples++){//lineSamples
        DBGPRINT("  FUNCOUT:findLineImageFromBottom[%d]->[x=%d|y=%d]\n",lineSamples,in_line[lineSamples]._x+gddx,in_line[lineSamples]._y+gddy);
    }
#endif
    return lineSamplesSaved;
}

inline int SOOSA::getSlope(PairXY* in_samples,double* out_slope, int nsize, int type)//type=0 is yline, type=1 is xline
{
    int i;
    if(type==0){
        for(i=1;i<nsize;i++){
            if(in_samples[i]._y==in_samples[i-1]._y){return 1;}
            out_slope[i-1]=((double)in_samples[i]._x-in_samples[i-1]._x)/((double)in_samples[i]._y-in_samples[i-1]._y);
            LOPPRINT("  FUNCLOOP:getSlope(%d)[ x[i]=%d|y[i]=%d|x[i-1]=%d|y[i-1]=%d ]->slope=%lf\n",i,in_samples[i]._x+gddx,in_samples[i]._y+gddy,in_samples[i-1]._x+gddx,in_samples[i-1]._y+gddy,out_slope[i-1]);
        }
    }else if(type==1){
        for(i=1;i<nsize;i++){
            if(in_samples[i]._x==in_samples[i-1]._x){return 1;}
            out_slope[i-1]=((double)in_samples[i]._y-in_samples[i-1]._y)/((double)in_samples[i]._x-in_samples[i-1]._x);
            LOPPRINT("  FUNCLOOP:getSlope(%d)[ x[i]=%d|y[i]=%d|x[i-1]=%d|y[i-1]=%d ]->slope=%lf\n",i,in_samples[i]._x+gddx,in_samples[i]._y+gddy,in_samples[i-1]._x+gddx,in_samples[i-1]._y+gddy,out_slope[i-1]);
        }
    }else{
        return 1;
    }
    return 0;
}
inline double SOOSA::getBarHeight(PairXY point1,PairXY point2)
{
    double barHeight;
    barHeight=pow((double)point1._x-point2._x,2) + pow((double)point1._y-point2._y,2);
    barHeight=sqrt(barHeight);
    return barHeight;
}

inline void SOOSA::getBarHeightArr(PairXY* questionsCoor,double* barHeight, int nsize)
{
    int i,j;
    for(i=0;i<nsize;i=i+2){
        j=i/2;
        barHeight[j]=getBarHeight(questionsCoor[i+1],questionsCoor[i]);
        LOPPRINT("  FUNCLOOP:getBarHeightArr(j=%d|barHeight=%lf) [%d]->(%ld|%ld) [%d]->(%ld|%ld)\n",j,barHeight[j],i,questionsCoor[i]._x+gddx,questionsCoor[i]._y+gddy,i+1,questionsCoor[i+1]._x+gddx,questionsCoor[i+1]._y+gddy);
    }
}

inline double SOOSA::getIntercept(PairXY* in_samples,double slope, int nsize, int type)
{
    int i;
    double intercept=0;
    DBGPRINT("  FUNC:getIntercept(slope=%lf)\n",slope);
    if(type==0){
        for(i=0;i<nsize;i++){
            LOPPRINT("  FUNCLOOP:getIntercept(%d)[x[i]=%d|y[i]=%d]->xintercept=%lf\n",i,in_samples[i]._x+gddx,in_samples[i]._y+gddy,intercept);
            intercept=intercept+in_samples[i]._x-(slope*in_samples[i]._y);
        }
        intercept=intercept/nsize;
        DBGPRINT("  FUNC:getIntercept->ret=%lf  |xIntercept\n",intercept+gddx);
    }else if(type==1){
        for(i=0;i<nsize;i++){
            LOPPRINT("  FUNCLOOP:getIntercept(%d)[x[i]=%d|y[i]=%d]->yintercept=%lf\n",i,in_samples[i]._x+gddx,in_samples[i]._y+gddy,intercept);
            intercept=intercept+in_samples[i]._y-(slope*in_samples[i]._x);
        }
        intercept=intercept/nsize;
        DBGPRINT("  FUNC:getIntercept->ret=%lf  |yIntercept\n",intercept+gddx);
    }
    return intercept;
}

int SOOSA::removeOutliersFromLine(PairXY* lineSamples, double* invslope, ChebyshevCriterion* chebycriterion, int numLineSamples, int type)
{
    int t1,t2;
    int* scoretoremove=NULL;
    scoretoremove = (int*)malloc(numLineSamples*sizeof(int));
    if(scoretoremove==NULL){return 0;}
    ChebyshevCriterion cc;
    t2=numLineSamples;
    do{
        //Remove Outliers
        numLineSamples=t2;
        getSlope(lineSamples,invslope,numLineSamples,type);
        getChebyshevDouble(&cc, invslope, numLineSamples-1);
        DBGPRINT("  FUNC:removeOutliersFromLine(slopeMean=%lf|slopeStdDev=%lf)\n",cc.mean,cc.stddev);
        for(t1=0;t1<numLineSamples;t1++){scoretoremove[t1]=0;}//clear array
        for(t1=0;t1<numLineSamples-1;t1++){
            LOPPRINT("  FUNCLOOP:removeOutliersFromLine[t1=%d|(x=%d,y=%d)]->slopeMean:%lf, deviate(k):%lf\n",t1,lineSamples[t1]._x+gddx,lineSamples[t1]._y+gddy,invslope[t1],getKFromChebyshev(cc,invslope[t1]));
            if(getKFromChebyshev(cc,invslope[t1])>CHEBYCHEVKVALUE){
                scoretoremove[t1]=1;scoretoremove[t1+1]=1;
                LOPPRINT("  FUNCLOOP:removeOutliersFromLine[t1=%d|(x=%d,y=%d)]->deviate(k)=%lf |  delete this, too much deviation\n",t1,lineSamples[t1]._x+gddx,lineSamples[t1]._y+gddy,getKFromChebyshev(cc,invslope[t1]));
                LOPPRINT("  FUNCLOOP:removeOutliersFromLine[t1=%d|(x=%d,y=%d)] |  delete this too, too much deviation\n",t1+1,lineSamples[t1+1]._x+gddx,lineSamples[t1+1]._y+gddy);
            }
        }
        t2=0;
        for(t1=0;t1<numLineSamples;t1++){
            if(scoretoremove[t1]==0){
                LOPPRINT("  FUNCLOOP:removeOutliersFromLine(SuccessfulLineSamples)-> (t2=%d|(x=%d|y=%d))\n",t2,lineSamples[t2]._x+gddx,lineSamples[t2]._y+gddy);
                lineSamples[t2]=lineSamples[t1]; t2++;
            }
        }
    }while(t2!=numLineSamples);
    *chebycriterion = cc;
#ifdef DBGFLAG
    for(t1=0;t1<numLineSamples;t1++){//lineSamples
        DBGPRINT("  FUNCOUT:removeOutliersFromLine[%d]->[x=%d|y=%d]\n",t1,lineSamples[t1]._x+gddx,lineSamples[t1]._y+gddy);
    }
#endif
    free(scoretoremove);
    scoretoremove=NULL;
    return numLineSamples;
}

int SOOSA::removeOutliersFromLineSmart(PairXY* lineSamples, int numLineSamples, int numLineSamplesDesired, int type)
{
    int t1, t1max;
    double maxDistance,tempDistance;
    double total_x, total_y, total_xy, total_x2, m_least_squares, b_least_squares;
    for(; numLineSamplesDesired<numLineSamples; numLineSamples--){//Remove Outliers
        //linear regression
        total_x=0; total_y=0; total_xy=0; total_x2=0;
        for(t1=0;t1<numLineSamples;t1++){
            if(type==0){
                total_x = total_x+lineSamples[t1]._y;
                total_y = total_y+lineSamples[t1]._x;
                total_xy = total_xy+(lineSamples[t1]._x*lineSamples[t1]._y);
                total_x2 = total_x2+(lineSamples[t1]._y*lineSamples[t1]._y);
            }else{
                total_x = total_x+lineSamples[t1]._x;
                total_y = total_y+lineSamples[t1]._y;
                total_xy = total_xy+(lineSamples[t1]._x*lineSamples[t1]._y);
                total_x2 = total_x2+(lineSamples[t1]._x*lineSamples[t1]._x);
            }
        }
        m_least_squares = ((total_xy*numLineSamples)-(total_x*total_y))/((total_x2*numLineSamples)-(total_x*total_x));
        b_least_squares = (total_y/numLineSamples)-((total_x/numLineSamples)*m_least_squares);

        DBGPRINT("  FUNC:removeOutliersFromLineSmart(slope(m_least_squares)=%lf | intercept(b_least_squares)=%lf)\n",m_least_squares,b_least_squares);
        maxDistance=0;
        t1max=0;
        for(t1=0;t1<numLineSamples;t1++){
            if(type==0){
                tempDistance = absValDouble((m_least_squares*lineSamples[t1]._y)+b_least_squares-lineSamples[t1]._x);
            }else{
                tempDistance = absValDouble((m_least_squares*lineSamples[t1]._x)+b_least_squares-lineSamples[t1]._y);
            }
            LOPPRINT("  FUNCLOOP:removeOutliersFromLineSmart[t1=%d|(x=%d,y=%d)]->slope:%lf, intercept:%lf, tempDistance:%lf, maxDistance:%lf\n",t1,lineSamples[t1]._x+gddx,lineSamples[t1]._y+gddy,m_least_squares,b_least_squares,tempDistance,maxDistance);
            if(tempDistance > maxDistance){
                //DBGPRINT("  FUNC:removeOutliersFromLineSmart MAXCHANGE[t1=%d|(x=%d,y=%d)]->tempDistance=%lf\n",t1max,lineSamples[t1max]._x+gddx,lineSamples[t1max]._y+gddy,tempDistance);
                maxDistance = tempDistance;
                t1max=t1;
            }
        }
        DBGPRINT("  FUNC:removeOutliersFromLineSmart REMOVED[t1=%d|(x=%d,y=%d)]->maxDistance=%lf\n",t1max,lineSamples[t1max]._x+gddx,lineSamples[t1max]._y+gddy,maxDistance);
        for(t1=t1max;t1+1<numLineSamples;t1++){
            lineSamples[t1]=lineSamples[t1+1];
        }
    }
#ifdef DBGFLAG
    for(t1=0;t1<numLineSamples;t1++){//lineSamples
        DBGPRINT("  FUNCOUT:removeOutliersFromLineSmart[%d]->[x=%d|y=%d]\n",t1,lineSamples[t1]._x+gddx,lineSamples[t1]._y+gddy);
    }
#endif
    return numLineSamples;
}

void SOOSA::getQFindSamples(PairXY* qFindSamples, int numQFindSamples, PairXY start, PairXY finish, LineSlopeIntercept lsi, int barheightsamplepixels)
{
    int t1,ytemp;
    qFindSamples[0]=start;
    ytemp=start._y;
    DBGPRINT("  FUNC:getQFindSamples start(%d|%d) finish(%d|%d)\n",start._x+gddx,start._y+gddy,finish._x+gddx,finish._y+gddy);
    DBGPRINT("  FUNC:getQFindSamples start(%d|%d) |  start with startSample\n",start._x+gddx,start._y+gddy);
    for(t1=1;t1<numQFindSamples-1;t1++){
        ytemp=ytemp+barheightsamplepixels;
        qFindSamples[t1]._y=ytemp;
        qFindSamples[t1]._x=roundOffSignRobust((((double)ytemp)*lsi.slope)+lsi.intercept);
        LOPPRINT("  FUNCLOOP:getQFindSamples [t1=%d]->(quesx=%d,quesy=%d)\n",t1,qFindSamples[t1]._x+gddx,qFindSamples[t1]._y+gddy);
    }
    qFindSamples[t1]=finish;
    DBGPRINT("  FUNC:getQFindSamples [t1=%d]finish(%d|%d)->(quesx=%d,quesy=%d)  |finish with finishSample\n",t1,finish._x+gddx,finish._y+gddy,qFindSamples[t1]._x+gddx,qFindSamples[t1]._y+gddy);
#ifdef DBGFLAG
    for(t1=0;t1<numQFindSamples;t1++){//lineSamples
        DBGPRINT("  FUNCOUT:getQFindSamples[%d]->[x=%d|y=%d]\n",t1,qFindSamples[t1]._x+gddx,qFindSamples[t1]._y+gddy);
    }
#endif
}

int SOOSA::getBarWidthCorrectPoint(AprgBitmapSnippet const& snippet, double invslope, PairXY* io_point, int correctPoint)
{
    int tx,ty,width=0,whiteWidth;
    PairXY tpoint,point,blackPoint,minx,maxx;
    point=*io_point;
    tpoint=point;minx=tpoint;maxx=tpoint;
    blackPoint = point;
    if(!snippet.isBlackAt(BitmapXY(point._x+gddx,point._y+gddy))){
        //Find the first black
        for(tx=1;tx<PIXELSPERPENLINE;tx++){
            ty=roundOffSignRobust(-1*invslope*(tx));
            tpoint._x=point._x+tx; tpoint._y=point._y+ty;
            //ALBA_DEBUG_PRINT2(tpoint._x+gddx, tpoint._y+gddy);
            if(snippet.isBlackAt(BitmapXY(tpoint._x+gddx,tpoint._y+gddy))){ blackPoint._x=tpoint._x; blackPoint._y=tpoint._y; width=1;break; }
            LOPPRINT("  FUNCLOOP:getBarWidthCorrectPoint FindFirstBlack [tpointx=%d|tpointy=%d]->(tvalue=%X)\n",tpoint._x+gddx,tpoint._y+gddy,tvalue);
            tpoint._x=point._x-tx; tpoint._y=point._y-ty;
            LOPPRINT("  FUNCLOOP:getBarWidthCorrectPoint FindFirstBlack [tpointx=%d|tpointy=%d]->(tvalue=%X)\n",tpoint._x+gddx,tpoint._y+gddy,tvalue);
            //ALBA_DEBUG_PRINT2(tpoint._x+gddx, tpoint._y+gddy);
            if(snippet.isBlackAt(BitmapXY(tpoint._x+gddx,tpoint._y+gddy))){ blackPoint._x=tpoint._x; blackPoint._y=tpoint._y; width=1;break; }
        }
    }else{
        width=1;
    }
    whiteWidth=0;
    for(tx=1;tx<PIXELSPERPENLINE;tx++){
        ty=roundOffSignRobust(-1*invslope*(tx));
        tpoint._x=blackPoint._x+tx; tpoint._y=blackPoint._y+ty;
        LOPPRINT("  FUNCLOOP:getBarWidthCorrectPoint [tpointx=%d|tpointy=%d]->(tvalue=%X)->(width=%d)\n",tpoint._x+gddx,tpoint._y+gddy,tvalue,width);
        //ALBA_DEBUG_PRINT2(tpoint._x+gddx, tpoint._y+gddy);
        if(snippet.isBlackAt(BitmapXY(tpoint._x+gddx,tpoint._y+gddy))){width=width+whiteWidth+1; whiteWidth=0;}
        else{ if(whiteWidth>=PIXELSDIRTWHITEDOT){break;} whiteWidth++;}
    }
    maxx._x=blackPoint._x+tx; maxx._y=blackPoint._y+ty;
    whiteWidth=0;
    for(tx=1;tx<PIXELSPERPENLINE;tx++){
        ty=roundOffSignRobust(-1*invslope*(tx));
        tpoint._x=blackPoint._x-tx; tpoint._y=blackPoint._y-ty;
        LOPPRINT("  FUNCLOOP:getBarWidthCorrectPoint [tpointx=%d|tpointy=%d]->(tvalue=%X)->(width=%d)\n",tpoint._x+gddx,tpoint._y+gddy,tvalue,width);
        //ALBA_DEBUG_PRINT2(tpoint._x+gddx, tpoint._y+gddy);
        if(snippet.isBlackAt(BitmapXY(tpoint._x+gddx,tpoint._y+gddy))){width=width+whiteWidth+1; whiteWidth=0;}
        else{ if(whiteWidth>=PIXELSDIRTWHITEDOT){break;} whiteWidth++;}
    }
    minx._x=blackPoint._x-tx; minx._y=blackPoint._y-ty;

    LOPPRINT("  FUNC:getBarWidthCorrectPoint (%d,%d)->(width=%d)\n",io_point->_x+gddx,io_point->_y+gddy,width);
    if(width>=PIXELSPERPENLINE || width<=PIXELSDIRTBLACKDOT){return 0;}
    if(correctPoint==1){
        (*io_point) = getMidpoint(minx,maxx);
        LOPPRINT("  FUNCOUT:getBarWidthCorrectPoint(minx=%d|miny=%d|maxx=%d|maxy=%d) OUT->(iopointx=%d,iopointy=%d)\n",minx._x+gddx,minx._y+gddy,maxx._x+gddx,maxx._y+gddy,io_point->_x+gddx,io_point->_y+gddy);
    }
    return width;
}

int SOOSA::barWidthGetCriterion(int *barWidth, int barWidthArrSize, ChebyshevCriterion* ccLine, ChebyshevCriterion* ccBar)
{
    int t1,t2,maxBarWidth,numOfWidths;
    int* freqBarWidth=NULL;
    int* indexBarWidth=NULL;
    ChebyshevCriterion cc;
    maxBarWidth=0;
    for(t1=0;t1<barWidthArrSize;t1++){
        if(maxBarWidth<barWidth[t1]){
            maxBarWidth=barWidth[t1];
            LOPPRINT("  FUNCLOOP:barWidthGetCriterion(maxBarWidth=%d)\n",maxBarWidth);
        }
    }
    indexBarWidth = (int*) malloc(maxBarWidth*sizeof(int));
    freqBarWidth = (int*) malloc(maxBarWidth*sizeof(int));
    if(indexBarWidth==NULL || freqBarWidth==NULL){
        if(indexBarWidth!=NULL){free(indexBarWidth);indexBarWidth=NULL;}
        if(freqBarWidth!=NULL){free(freqBarWidth);freqBarWidth=NULL;}
        DBGPRINT("  FUNCOUT:barWidthGetCriterion(indexBarWidth=%X|freqBarWidth=%X)\n",indexBarWidth,freqBarWidth);
        return 1;
    }
    numOfWidths=0;
    //for(t1=0;t1<numOfWidths;t1++){indexBarWidth[t1]=0;freqBarWidth[t1]=0;} //NOT NEEDED GUESS WHY?
    for(t1=0;t1<barWidthArrSize;t1++){
        if(barWidth[t1]==0){continue;}
        for(t2=0;t2<numOfWidths;t2++){
            if(barWidth[t1]==indexBarWidth[t2]){freqBarWidth[t2]++; break;}
        }
        if(t2==numOfWidths){
            for(t2=numOfWidths;t2>0;t2--){
                if(barWidth[t1]>indexBarWidth[t2-1]){break;}
                freqBarWidth[t2]=freqBarWidth[t2-1];
                indexBarWidth[t2]=indexBarWidth[t2-1];
            }
            freqBarWidth[t2]=1;
            indexBarWidth[t2]=barWidth[t1];
            numOfWidths++;
        }
        LOPPRINT("  FUNCLOOP:barWidthGetCriterion(t2=%d)->(indexBarWidth=%d|freqBarWidth=%d)\n",t2,indexBarWidth[t2],freqBarWidth[t2]);
    }
#ifdef DBGFLAG
    for(t2=0;t2<numOfWidths;t2++){//lineSamples
        DBGPRINT("  FUNCOUT:barWidthGetCriterion KmeansArray[%d]->(indexBarWidth=%d|freqBarWidth=%d)\n",t2,indexBarWidth[t2],freqBarWidth[t2]);
    }
#endif
    //Kmeans Algorithm
    double mean1, mean2;
    int tot1,tot2,kmeansindex,isChanged;
    for(t2=1;t2<numOfWidths-1;t2++){
        mean1=0;tot1=0;
        for(t1=0;t1<t2;t1++){
            mean1=mean1+(indexBarWidth[t1]*freqBarWidth[t1]);
            tot1=tot1+freqBarWidth[t1];
            LOPPRINT("  FUNCLOOP:barWidthGetCriterion-KMeansAlgorithmMean1(KMeansIndex=%d|t1=%d)->(total1=%lf|num1=%d)\n",t2,t1,mean1,tot1);
        }
        mean1=mean1/tot1;
        DBGPRINT("  FUNC:barWidthGetCriterion-KMeansAlgorithmMean1(KMeansIndex=%d|t1=%d)->(mean1=%lf|num1=%d)\n",t2,t1,mean1,tot1);
        mean2=0;tot2=0;
        for(t1=t2;t1<numOfWidths;t1++){
            mean2=mean2+(indexBarWidth[t1]*freqBarWidth[t1]);
            tot2=tot2+freqBarWidth[t1];
            LOPPRINT("  FUNCLOOP:barWidthGetCriterion-KMeansAlgorithmMean2(KMeansIndex=%d|t1=%d)->(total2=%lf|num2=%d)\n",t2,t1,mean2,tot2);
        }
        mean2=mean2/tot2;
        DBGPRINT("  FUNC:barWidthGetCriterion-KMeansAlgorithmMean2(KMeansIndex=%d|t1=%d)->(mean2=%lf|num2=%d)\n",t2,t1,mean2,tot2);
        DBGPRINT("  FUNC:barWidthGetCriterion-KMeansAlgorithmToAnalyze(KMeansIndex=%d|t1=%d)->(mean1=%lf|num1=%d|mean2=%lf|num2=%d)\n",t2,t1,mean1,tot1,mean2,tot2);
        DBGPRINT("  FUNC:barWidthGetCriterion-KMeansAlgorithmDeviationFromMean(KMeansIndex=%d|t1=%d)->(mean1=%lf|mean2=%lf|deviationfrom1=%lf|deviationfrom2=%lf)\n",t2,t1,mean1,mean2,absValDouble(indexBarWidth[t2]-mean1),absValDouble(indexBarWidth[t2]-mean2));
        if(absValDouble(indexBarWidth[t2]-mean2)<absValDouble(indexBarWidth[t2]-mean1)){
            break;
        }
    }
    kmeansindex=t2;
    DBGPRINT("  FUNCOUT:barWidthGetCriterion-KMeansAlgorithm(FinalKMeansIndex=%d)\n",kmeansindex);


    isChanged=1;
    while(isChanged==1){
        isChanged=0;
        getChebyshevFreqIndex(&cc, freqBarWidth, indexBarWidth, 0,kmeansindex);
        for(t1=0;t1<kmeansindex;t1++){
            if(freqBarWidth[t1]==0){continue;}
            LOPPRINT("  FUNCLOOP:barWidthGetCriterion-Line(BarWidth=%d|Freq=%d)->(Mean=%lf|StdDev=%lf|deviate(k)=%lf)\n",indexBarWidth[t1],freqBarWidth[t1],cc.mean,cc.stddev,getKFromChebyshev(cc,indexBarWidth[t1]));
            if(getKFromChebyshev(cc,indexBarWidth[t1])>CHEBYCHEVKVALUEWIDTH){
                LOPPRINT("  FUNCLOOP:barWidthGetCriterion-Line(BarWidth=%d|Freq=%d)->(Mean=%lf|StdDev=%lf|deviate(k)=%lf) |  delete this, too much deviation\n",indexBarWidth[t1],freqBarWidth[t1],cc.mean,cc.stddev,getKFromChebyshev(cc,indexBarWidth[t1]));
                freqBarWidth[t1]=0;
                isChanged=1;
            }
        }
    }
    getChebyshevFreqIndex(&cc, freqBarWidth, indexBarWidth, 0,kmeansindex);
    DBGPRINT("  FUNCOUT:barWidthGetCriterion-Line(FinalLineMean:%lf, FinalLineStdDev:%lf\n",cc.mean,cc.stddev);
    *ccLine=cc;

    isChanged=1;
    while(isChanged==1){
        isChanged=0;
        getChebyshevFreqIndex(&cc, freqBarWidth, indexBarWidth,kmeansindex,numOfWidths);
        for(t1=kmeansindex;t1<numOfWidths;t1++){
            if(freqBarWidth[t1]==0){continue;}
            LOPPRINT("  FUNCLOOP:barWidthGetCriterion-Bar (BarWidth=%d|Freq=%d)->(Mean=%lf|StdDev=%lf|deviate(k)=%lf)\n",indexBarWidth[t1],freqBarWidth[t1],cc.mean,cc.stddev,getKFromChebyshev(cc,indexBarWidth[t1]));
            if(getKFromChebyshev(cc,indexBarWidth[t1])>CHEBYCHEVKVALUEWIDTH){
                LOPPRINT("  FUNCLOOP:barWidthGetCriterion-Bar (BarWidth=%d|Freq=%d)->(Mean=%lf|StdDev=%lf|deviate(k)=%lf) |  delete this, too much deviation\n",indexBarWidth[t1],freqBarWidth[t1],cc.mean,cc.stddev,getKFromChebyshev(cc,indexBarWidth[t1]));
                freqBarWidth[t1]=0;
                isChanged=1;
            }
        }
    }
    getChebyshevFreqIndex(&cc, freqBarWidth, indexBarWidth,kmeansindex,numOfWidths);
    DBGPRINT("  FUNCOUT:barWidthGetCriterion-Bar (FinalBarMean:%lf, FinalBarStdDev:%lf\n",cc.mean,cc.stddev);
    *ccBar=cc;

    free(freqBarWidth);freqBarWidth=NULL;
    free(indexBarWidth);indexBarWidth=NULL;
    return 0;
}

void SOOSA::getQuestions(AprgBitmapSnippet const& snippet, PairXY* in_questions, int* in_numQuestion, PairXY* qFindSamples, int* qFindSamplesType, int* barWidth, int numQFindSamples, LineSlopeIntercept tslopeintercept, ChebyshevCriterion ccLine, ChebyshevCriterion ccBar)
{
    int t1,t2,numQuestion=0,type,prevtype,twidth,numImptCoor,numBarHeightArr,saved;
    double tdouble,tempBarHeight;
    int* barHeightArr;
    int correctPosition,limitY;
    ChebyshevCriterion cc;
    PairXY prevpair,bgnpair,endpair,tmppair;
    PairXY bgnpair2,endpair2;
    prevtype = 0;
    prevpair = qFindSamples[0];
    numImptCoor=0;
    for(t1=0;t1<numQFindSamples;t1++){
        if(barWidth[t1]<=PIXELSDIRTBLACKDOT){
            type=0;
            DBGPRINT("  FUNC:getQuestions[%d]->(%d,%d):( BARWIDTH=%d |LineDeviation(k)=%lf|BarDeviation(k)=%lf|AcceptableK=%d) [Dirt] [ptype:%d,type:%d]\n",
            t1,qFindSamples[t1]._x+gddx,qFindSamples[t1]._y+gddy,barWidth[t1],getKFromChebyshev(ccLine,barWidth[t1]),getKFromChebyshev(ccBar,barWidth[t1]),CHEBYCHEVKVALUEWIDTH,prevtype,type);
        }else if(getKFromChebyshev(ccLine,barWidth[t1])<CHEBYCHEVKVALUEWIDTH){
            type=1;
            DBGPRINT("  FUNC:getQuestions[%d]->(%d,%d):( BARWIDTH=%d |LineDeviation(k)=%lf|BarDeviation(k)=%lf|AcceptableK=%d) [Line] [ptype:%d,type:%d]\n",
            t1,qFindSamples[t1]._x+gddx,qFindSamples[t1]._y+gddy,barWidth[t1],getKFromChebyshev(ccLine,barWidth[t1]),getKFromChebyshev(ccBar,barWidth[t1]),CHEBYCHEVKVALUEWIDTH,prevtype,type);
        }else if(getKFromChebyshev(ccBar,barWidth[t1])<CHEBYCHEVKVALUEWIDTH){
            type=2;
            DBGPRINT("  FUNC:getQuestions[%d]->(%d,%d):( BARWIDTH=%d |LineDeviation(k)=%lf|BarDeviation(k)=%lf|AcceptableK=%d) [Bar] [ptype:%d,type:%d]\n",
            t1,qFindSamples[t1]._x+gddx,qFindSamples[t1]._y+gddy,barWidth[t1],getKFromChebyshev(ccLine,barWidth[t1]),getKFromChebyshev(ccBar,barWidth[t1]),CHEBYCHEVKVALUEWIDTH,prevtype,type);
        }else{
            type=0;
            DBGPRINT("  FUNC:getQuestions[%d]->(%d,%d):( BARWIDTH=%d |LineDeviation(k)=%lf|BarDeviation(k)=%lf|AcceptableK=%d) [No Class] [ptype:%d,type:%d]\n",
            t1,qFindSamples[t1]._x+gddx,qFindSamples[t1]._y+gddy,barWidth[t1],getKFromChebyshev(ccLine,barWidth[t1]),getKFromChebyshev(ccBar,barWidth[t1]),CHEBYCHEVKVALUEWIDTH,prevtype,type);
        }
        if(prevtype==0 && type==0 && t1!=0){//both no class case
            bgnpair = prevpair;
            endpair = qFindSamples[t1];
            bgnpair2._x=endpair._x-bgnpair._x; bgnpair2._y=endpair._y-bgnpair._y;
            limitY=0;
            t2=1;
            while(t2<bgnpair2._y){
                tmppair._x = roundOffSignRobust(((double)t2*bgnpair2._x/bgnpair2._y)+bgnpair._x);
                tmppair._y = roundOffSignRobust(bgnpair._y+t2);
                twidth = getBarWidthCorrectPoint(snippet, tslopeintercept.slope, &tmppair, 0);
                DBGPRINT("  FUNC:getQuestions-NoClassToNoClass[(%d,%d),(%d,%d)]->temppair(%d,%d)|twidth:%d\n",
                bgnpair._x+gddx,bgnpair._y+gddy,endpair._x+gddx,endpair._y+gddy,tmppair._x+gddx,tmppair._y+gddy,twidth);
                if(twidth<=PIXELSDIRTBLACKDOT){//assume line
                }else if(getKFromChebyshev(ccLine,twidth)<CHEBYCHEVKVALUEWIDTH){
                    qFindSamples[t1] = tmppair;
                    barWidth[t1]=twidth;
                    limitY=1;
                    break;
                }else if(getKFromChebyshev(ccBar,twidth)<CHEBYCHEVKVALUEWIDTH){
                    qFindSamples[t1] = tmppair;
                    barWidth[t1]=twidth;
                    limitY=1;
                    break;
                }
                t2=t2+1;
            }
            if(limitY==1){
                t1=t1-1;
                continue;
            }
        }else if((prevtype==0 && type==2) || (prevtype==1 && type==2)){
            bgnpair = prevpair;
            endpair = qFindSamples[t1];
            limitY=endpair._y-bgnpair._y;
            correctPosition=1;
            while(limitY>1){
                bgnpair2 = bgnpair; endpair2 = endpair;
                tmppair = getMidpoint(bgnpair2,endpair2);
                twidth = getBarWidthCorrectPoint(snippet, tslopeintercept.slope, &tmppair, correctPosition);
                DBGPRINT("  FUNC:getQuestions-LineToBar[(%d,%d),(%d,%d)]->temppair(%d,%d)|twidth:%d\n",
                bgnpair._x+gddx,bgnpair._y+gddy,endpair._x+gddx,endpair._y+gddy,tmppair._x+gddx,tmppair._y+gddy,twidth);
                if(twidth<=PIXELSDIRTBLACKDOT){//assume line
                    bgnpair2 = tmppair;
                }else if(getKFromChebyshev(ccLine,twidth)<CHEBYCHEVKVALUEWIDTH){
                    bgnpair2 = tmppair;
                }else if(getKFromChebyshev(ccBar,twidth)<CHEBYCHEVKVALUEWIDTH){
                    endpair2 = tmppair;
                }else{//assume line
                    bgnpair2 = tmppair;
                }
                if(endpair2._y-bgnpair2._y<limitY){
                    bgnpair = bgnpair2; endpair = endpair2; limitY=endpair._y-bgnpair._y;
                    correctPosition=1;
                }else{
                    correctPosition=0;
                }
            }
            qFindSamples[numImptCoor] = endpair;
            qFindSamplesType[numImptCoor] = 1; //line to bar
            numImptCoor++;
        }else if((prevtype==2 && type==0) || (prevtype==2 && type==1)){
            bgnpair = prevpair;
            endpair = qFindSamples[t1];
            limitY=endpair._y-bgnpair._y;
            correctPosition=1;
            while(endpair._y-bgnpair._y>1){
                bgnpair2 = bgnpair; endpair2 = endpair;
                tmppair = getMidpoint(bgnpair2,endpair2);
                twidth = getBarWidthCorrectPoint(snippet, tslopeintercept.slope, &tmppair, correctPosition);
                DBGPRINT("  FUNC:getQuestions-BarToLine[(%d,%d),(%d,%d)]->temppair(%d,%d)|twidth:%d\n",
                bgnpair._x+gddx,bgnpair._y+gddy,endpair._x+gddx,endpair._y+gddy,tmppair._x+gddx,tmppair._y+gddy,twidth);
                if(twidth<=PIXELSDIRTBLACKDOT){//assume line
                    endpair2 = tmppair;
                }else if(getKFromChebyshev(ccLine,twidth)<CHEBYCHEVKVALUEWIDTH){
                    endpair2 = tmppair;
                }else if(getKFromChebyshev(ccBar,twidth)<CHEBYCHEVKVALUEWIDTH){
                    bgnpair2 = tmppair;
                }else{//assume line
                    endpair2 = tmppair;
                }
                if(endpair2._y-bgnpair2._y<limitY){
                    bgnpair = bgnpair2; endpair = endpair2; limitY=endpair._y-bgnpair._y;
                    correctPosition=1;
                }else{
                    correctPosition=0;
                }
            }
            qFindSamples[numImptCoor] = bgnpair;
            qFindSamplesType[numImptCoor] = 2; //bar to line
            numImptCoor++;
        }
        if(t1==numQFindSamples-1 && type==2){ //last bar
            qFindSamples[numImptCoor] = qFindSamples[t1]; //add point if last bar
            qFindSamplesType[numImptCoor] = 2;
            numImptCoor++;
        }
        prevpair = qFindSamples[t1];
        prevtype = type;
    }

    //Get Bar Height
    barHeightArr=(int*)malloc(numImptCoor*sizeof(int));
    if(barHeightArr==NULL)
    {
        cout<<"ERROR: Error in allocating barHeightArr array."<<endl;
        return;
    }

    numBarHeightArr=0;
    saved=0;
    prevpair = qFindSamples[0];
    for(t1=0;t1<numImptCoor;t1++){
        DBGPRINT("  FUNC:getQuestions barHeightArr[%d]|type:%d->(%d,%d)\n",t1,qFindSamplesType[t1],qFindSamples[t1]._x+gddx,qFindSamples[t1]._y+gddy);
        if(qFindSamplesType[t1]==1){ prevpair = qFindSamples[t1]; saved=1;
        }else if(qFindSamplesType[t1]==2 && saved==1){
            tempBarHeight = getBarHeight(qFindSamples[t1],prevpair);
            if (BARHEIGHTLOW<tempBarHeight && BARHEIGHTHIGH>tempBarHeight){
                DBGPRINT("  FUNC:getQuestions barHeightArr[%d]|type:%d->[numBar:%d](%d-%d=%d)\n",t1,qFindSamplesType[t1],numBarHeightArr,qFindSamples[t1]._y+gddy,prevpair._y+gddy,qFindSamples[t1]._y-prevpair._y);
                barHeightArr[numBarHeightArr++] = (int)tempBarHeight;
            }
        }
    }
    getChebyshevInt(&cc, barHeightArr, numBarHeightArr);
    prevpair = qFindSamples[0];
    numQuestion=0;
    for(t1=0;t1<numImptCoor;t1++){
        if(qFindSamplesType[t1]==1){
            prevpair = qFindSamples[t1];
            DBGPRINT("  FUNC:getQuestions[%d](%d,%d) Type:1 \n",t1,qFindSamples[t1]._x+gddx,qFindSamples[t1]._y+gddy);
            tdouble = BARHEIGHTHIGH-BARHEIGHTLOW;// assign properlimit;
            saved=0;
            for(t2=t1+1;t2<numImptCoor;t2++){
                tempBarHeight = getBarHeight(qFindSamples[t2],prevpair);
                DBGPRINT("  FUNC:getQuestions[%d]->(height=%lf)<(%lf):(MeanBarHeight=%lf)\n",t2,tempBarHeight,tdouble,cc.mean);
                if(qFindSamplesType[t2]==2 && BARHEIGHTLOW<tempBarHeight && BARHEIGHTHIGH>tempBarHeight && absValDouble(tempBarHeight-cc.mean)<tdouble){
                    DBGPRINT("  FUNC:getQuestions[%d] Question endpoint candidate (%d,%d)(%d,%d)->height(%d):(Mean(k)=%lf)\n",
                    t2,prevpair._x+gddx,prevpair._y+gddy,qFindSamples[t2]._x+gddx,qFindSamples[t2]._y+gddy,tempBarHeight,cc.mean);
                    in_questions[numQuestion]._x=prevpair._x; in_questions[numQuestion]._y=prevpair._y;
                    in_questions[numQuestion+1]._x=qFindSamples[t2]._x; in_questions[numQuestion+1]._y=qFindSamples[t2]._y;
                    tdouble = absValDouble(tempBarHeight-cc.mean);
                    t1=t2;
                    saved=1;
                }
                if(tempBarHeight>BARHEIGHTHIGH){ break;}
            }
            if(saved==1){
                DBGPRINT("  FUNC:getQuestions: Endpoint ADDED\n");
                numQuestion=numQuestion+2;
            }
        }
    }

    free(barHeightArr);barHeightArr=NULL;

#ifdef DBGFLAG
    for(t1=0;t1<numQuestion;t1++){//lineSamples
        DBGPRINT("FUNCOUT:getQuestions[%d]->[x=%d|y=%d]\n",t1,in_questions[t1]._x+gddx,in_questions[t1]._y+gddy);
    }
#endif
    *in_numQuestion=numQuestion;
}

int SOOSA::getQuestionsFromLine(AprgBitmapSnippet const& snippet, PairXY* out_questions, int numExpectedQuestions, double* tdoublearr, LineSlopeIntercept tslopeintercept, PairXY tcornerup, PairXY tcornerdown, int barheightsamplepixels)
{
    ChebyshevCriterion ccLine,ccBar;
    PairXY* qFindSamples=NULL;
    int* barWidth=NULL;
    int* qFindSamplesType=NULL;
    int numQFindSamples, numQuestionsCoor;
    int t1=0,fail=0;
    do{
        numQFindSamples = rasterRound(((double)tcornerdown._y-tcornerup._y)/barheightsamplepixels)+1;
        if(numQFindSamples<numExpectedQuestions)
        {
            cout<<"ERROR: Number of QFindSamples is not enough."<<endl;
            fail=1;
            break;
        }
        qFindSamples=(PairXY*)malloc(numQFindSamples*sizeof(PairXY));
        if(qFindSamples==NULL)
        {
            cout<<"ERROR: Error in allocating qFindSamples array."<<endl;
            fail=1;
            break;
        }
        qFindSamplesType=(int*)malloc(numQFindSamples*sizeof(PairXY));
        if(qFindSamplesType==NULL)
        {
            cout<<"ERROR: Error in allocating qFindSamplesType array."<<endl;
            fail=1;
            break;
        }
        getQFindSamples(qFindSamples, numQFindSamples, tcornerup, tcornerdown, tslopeintercept, barheightsamplepixels);
        barWidth=(int*)malloc(numQFindSamples*sizeof(int));
        if(barWidth==NULL)
        {
            cout<<"ERROR: Error in allocating BarWidth array."<<endl;
            fail=1;
            break;
        }
        for(t1=0;t1<numQFindSamples;t1++){barWidth[t1] = getBarWidthCorrectPoint(snippet, tslopeintercept.slope, &(qFindSamples[t1]),1);}
        if(barWidthGetCriterion(barWidth, numQFindSamples, &ccLine, &ccBar)==1)
        {
            cout<<"ERROR: Error in allocating IndexBarWidth and FreqBarWidth array."<<endl;
            fail=1;
            break;
        }
        getQuestions(snippet, out_questions, &numQuestionsCoor, qFindSamples, qFindSamplesType, barWidth, numQFindSamples, tslopeintercept, ccLine, ccBar);
        free(barWidth);barWidth=NULL;
        free(qFindSamples);qFindSamples=NULL;
        free(qFindSamplesType);qFindSamplesType=NULL;
        if(numQuestionsCoor%2==1)
        {
            cout<<"ERROR: Error in finding questions. Odd number of coordinates for the bars."<<endl;
            fail=1;
            break;
        }
        if(numExpectedQuestions*2!=numQuestionsCoor)
        {
            cout<<"ERROR: Number of questions does not match with expected number"<<endl;
            fail=1;
            break;
        }
        getBarHeightArr(out_questions,tdoublearr, numQuestionsCoor);
        for(t1=0;t1<numExpectedQuestions;t1++)
        {
            DBGPRINT("  FUNCOUT:getQuestionsFromLine(BarHeight)[%d] -> ( barHeight=%lf)\n",t1,tdoublearr[t1]);
            if(!(BARHEIGHTLOW<tdoublearr[t1] && BARHEIGHTHIGH>tdoublearr[t1])){ fail=1;break;}
        }
        if(fail==1)
        {
            cout<<"ERROR: Error in finding questions. Invalid BarHeightFound."<<endl;
            fail=1;
            break;
        }
        for(t1=0;t1<numQuestionsCoor;t1++)
        {
            DBGPRINT("  FUNCOUT:getQuestionsFromLine[%d] -> (x=%d,y=%d)\n",(t1/2)+1,out_questions[t1]._x+gddx,out_questions[t1]._y+gddy);
            out_questions[t1]._x=out_questions[t1]._x+gddx; out_questions[t1]._y=out_questions[t1]._y+gddy;
        }
    }
    while(0);
    if(qFindSamples!=NULL)
    {
        free(qFindSamples);
        qFindSamples=NULL;
    }
    if(qFindSamplesType!=NULL)
    {
        free(qFindSamplesType);
        qFindSamplesType=NULL;
    }
    if(barWidth!=NULL)
    {
        free(barWidth);
        barWidth=NULL;
    }
    return fail;
}



void SOOSA::processOneFile(string const& filePath)
{
    cout<<"processOneFile: ["<<filePath<<"]"<<endl;
    m_status = SoosaStatus::NoError;

    //newway

    AprgBitmap bitmap(filePath);
    unsigned int bitmapWidth(bitmap.getConfiguration().getBitmapWidth());
    unsigned int bitmapHeight(bitmap.getConfiguration().getBitmapHeight());
    ChebyshevCriterion ccSlope;
    if(bitmapWidth<=PIXELSPERPENLINE || bitmapHeight<=PIXELSPERPENLINE){
        cout<<"ERROR: BMP File is too small ("<<PIXELSPERPENLINE<<" pixels by "<<PIXELSPERPENLINE<<" pixels only)."<<endl;
        m_status = SoosaStatus::BitmapError;
        return;
    }

    //forfaster
    int barheightsamplepixels = 10;
    int xsearchsize = bitmapWidth/8;
    int ysearchsize = bitmapHeight/8;

    LineSlopeIntercept leftline, rightline, topline, bottomline, centerleftline, centerrightline, templine;
    PairXY uplfcorner, uprtcorner, dnlfcorner, dnrtcorner, upcenter, dncenter;
    PairXY temppoint1,temppoint2;
    PairXY lineSamples[SAMPLESLINETOALLOC];
    PairXY Q1[MAXQUESTIONSCOOR],Q2[MAXQUESTIONSCOOR],Q3[MAXQUESTIONSCOOR],Q4[MAXQUESTIONSCOOR];
    int numLineSamples,maxLineSamples;
    double tdoublearr[SAMPLESLINETOALLOC];
    bool isFinishedSuccessfully(false);

    while(!isFinishedSuccessfully)//Two Tries only
    {
        maxLineSamples=ROBUSTSAMPLESLINE;
        //Left Line
        cout<<"INFO: Finding left line. NumOfSamples="<<maxLineSamples<<endl;
        gddx=0;
        gddy=0;
        AprgBitmapSnippet snippet(bitmap.getSnippetReadFromFile(BitmapXY(gddx, gddy), BitmapXY(xsearchsize,bitmapHeight-1)));

        writeLineInBitmap(bitmap, findLeftLine(snippet));

        numLineSamples = findLineImageFromLeft(snippet, lineSamples, maxLineSamples, createXY(0,0), createXY(0,bitmapHeight-1));
        DBGPRINT("INFO: BlackSamples=%d\n",numLineSamples);
        numLineSamples = removeOutliersFromLine(lineSamples, tdoublearr, &ccSlope, numLineSamples, 0);        DBGPRINT("INFO: SucessfulSamples=%d\n",numLineSamples);
        if(ROBUSTMINSAMPLESLINE>numLineSamples)
        {
            cout<<"ERROR: Error in finding the line. Number of samples is not enough (numLineSamples="<<numLineSamples<<")."<<endl;            break;
        }
        if(getSlope(lineSamples,tdoublearr,numLineSamples, 0)==1)
        {
            cout<<"ERROR: Invalid Slope."<<endl;
            break;
        }
        getChebyshevDouble(&ccSlope, tdoublearr, numLineSamples-1);
        leftline.intercept=getIntercept(lineSamples,ccSlope.mean,numLineSamples,0);
        leftline.slope=ccSlope.mean;
        leftline = transposeLine(leftline,0,-1*gddx,-1*gddy);
        //Right Line
        cout<<"INFO: Finding right line. NumOfSamples="<<maxLineSamples<<endl;
        snippet.clear();
        gddx=bitmapWidth-1-xsearchsize;
        gddy=0;
        snippet = bitmap.getSnippetReadFromFile(BitmapXY(gddx, gddy), BitmapXY(bitmapWidth-1, bitmapHeight-1));

        writeLineInBitmap(bitmap, findRightLine(snippet));

        numLineSamples = findLineImageFromRight(snippet, lineSamples, maxLineSamples, createXY(xsearchsize-1,0),createXY(xsearchsize-1,bitmapHeight-1));
        DBGPRINT("INFO: BlackSamples=%d\n",numLineSamples);
        numLineSamples = removeOutliersFromLine(lineSamples, tdoublearr, &ccSlope, numLineSamples, 0);        DBGPRINT("INFO: SucessfulSamples=%d\n",numLineSamples);
        if(ROBUSTMINSAMPLESLINE>numLineSamples)
        {
            cout<<"ERROR: Error in finding the line. Number of samples is not enough (numLineSamples="<<numLineSamples<<")."<<endl;            break;
        }
        if(getSlope(lineSamples,tdoublearr,numLineSamples, 0)==1)
        {
            cout<<"ERROR: Invalid Slope."<<endl;
            break;
        }
        getChebyshevDouble(&ccSlope, tdoublearr, numLineSamples-1);
        rightline.intercept=getIntercept(lineSamples,ccSlope.mean,numLineSamples,0);
        rightline.slope=ccSlope.mean;
        rightline = transposeLine(rightline,0,-1*gddx,-1*gddy);
        maxLineSamples=ROBUSTSAMPLESLINETOPBOTTOM;
        //Top Line
        cout<<"INFO: Finding top line. NumOfSamples="<<maxLineSamples<<endl;
        snippet.clear();
        gddx=0;
        gddy=0;
        snippet = bitmap.getSnippetReadFromFile(BitmapXY(gddx, gddy), BitmapXY(bitmapWidth-1,ysearchsize));

        writeLineInBitmap(bitmap, findTopLine(snippet));

        numLineSamples = findLineImageFromTop(snippet, lineSamples, maxLineSamples, createXY(0,0), createXY(bitmapWidth-1,0));
        DBGPRINT("INFO: BlackPerpendicularSamples=%d\n",numLineSamples);
        numLineSamples = removeOutliersFromLine(lineSamples, tdoublearr, &ccSlope, numLineSamples, 1);        DBGPRINT("INFO: SucessfulSamples=%d\n",numLineSamples);
        if(ROBUSTMINSAMPLESLINETOPBOTTOM>numLineSamples)
        {
            cout<<"ERROR: Error in finding the line. Number of samples is not enough (numLineSamples="<<numLineSamples<<")."<<endl;            break;
        }
        if(getSlope(lineSamples,tdoublearr,numLineSamples, 1)==1)
        {
            cout<<"ERROR: Invalid Slope."<<endl;
            break;
        }
        getChebyshevDouble(&ccSlope, tdoublearr, numLineSamples-1);
        topline.intercept=getIntercept(lineSamples,ccSlope.mean,numLineSamples,1);
        topline.slope=ccSlope.mean;
        topline = transposeLine(topline,1,-1*gddx,-1*gddy);
        maxLineSamples=ROBUSTSAMPLESLINETOPBOTTOM;
        //Bottom Line
        cout<<"INFO: Finding bottom line. NumOfSamples="<<maxLineSamples<<endl;
        snippet.clear();
        gddx=0;
        gddy=bitmapHeight-1-ysearchsize;
        snippet = bitmap.getSnippetReadFromFile(BitmapXY(gddx, gddy), BitmapXY(bitmapWidth-1,bitmapHeight-1));

        writeLineInBitmap(bitmap, findBottomLine(snippet));

        numLineSamples = findLineImageFromBottom(snippet, lineSamples, maxLineSamples, createXY(0,ysearchsize-1),createXY(bitmapWidth-1,ysearchsize-1));
        DBGPRINT("INFO: BlackPerpendicularSamples=%d\n",numLineSamples);
        numLineSamples = removeOutliersFromLine(lineSamples, tdoublearr, &ccSlope, numLineSamples, 1);        DBGPRINT("INFO: SucessfulSamples=%d\n",numLineSamples);
        if(ROBUSTMINSAMPLESLINETOPBOTTOM>numLineSamples)
        {
            cout<<"ERROR: Error in finding the line. Number of samples is not enough (numLineSamples="<<numLineSamples<<")."<<endl;            break;
        }
        if(getSlope(lineSamples,tdoublearr,numLineSamples, 1)==1)
        {
            cout<<"ERROR: Invalid Slope."<<endl;
            break;
        }
        getChebyshevDouble(&ccSlope, tdoublearr, numLineSamples-1);
        bottomline.intercept=getIntercept(lineSamples,ccSlope.mean,numLineSamples,1);
        bottomline.slope=ccSlope.mean;
        bottomline = transposeLine(bottomline,1,-1*gddx,-1*gddy);

        DBGPRINT("INFO: LeftLine (slope=%lf|intercept=%lf)\n",leftline.slope,leftline.intercept);
        DBGPRINT("INFO: RightLine (slope=%lf|intercept=%lf)\n",rightline.slope,rightline.intercept);
        DBGPRINT("INFO: TopLine (slope=%lf|intercept=%lf)\n",topline.slope,topline.intercept);
        DBGPRINT("INFO: BottomLine (slope=%lf|intercept=%lf)\n",bottomline.slope,bottomline.intercept);
        uplfcorner = findIntersection(leftline,topline);
        uprtcorner = findIntersection(rightline,topline);
        dnlfcorner = findIntersection(leftline,bottomline);
        dnrtcorner = findIntersection(rightline,bottomline);
        upcenter = getMidpoint(uplfcorner,uprtcorner);
        dncenter = getMidpoint(dnlfcorner,dnrtcorner);
        DBGPRINT("INFO: UpLeftCorner (x=%d,y=%d)\n",uplfcorner._x,uplfcorner._y);
        DBGPRINT("INFO: UpRightCorner (x=%d,y=%d)\n",uprtcorner._x,uprtcorner._y);
        DBGPRINT("INFO: DownLeftCorner (x=%d,y=%d)\n",dnlfcorner._x,dnlfcorner._y);
        DBGPRINT("INFO: DownRightCorner (x=%d,y=%d)\n",dnrtcorner._x,dnrtcorner._y);
        if(checkIfWithinImageBounds(uplfcorner,bitmapWidth-1,bitmapHeight-1)==1)
        {
            cout<<"ERROR: Invalid UpLeftCorner point."<<endl;
            break;
        }
        if(checkIfWithinImageBounds(uprtcorner,bitmapWidth-1,bitmapHeight-1)==1)
        {
            cout<<"ERROR: Invalid UpRightCorner point."<<endl;
            break;
        }
        if(checkIfWithinImageBounds(dnlfcorner,bitmapWidth-1,bitmapHeight-1)==1)
        {
            cout<<"ERROR: Invalid DownLeftCorner point."<<endl;
            break;
        }
        if(checkIfWithinImageBounds(dnrtcorner,bitmapWidth-1,bitmapHeight-1)==1)
        {
            cout<<"ERROR: Invalid DownRightCorner point."<<endl;
            break;
        }
        barheightsamplepixels=10;
        snippet.clear();
        BitmapSignedXY topLeftCorner(uplfcorner._x-PIXELSSEARCHSIZE,uplfcorner._y-PIXELSSEARCHSIZE);
        topLeftCorner.saveMinimumXAndY(BitmapSignedXY(uplfcorner._x+PIXELSSEARCHSIZE,uplfcorner._y+PIXELSSEARCHSIZE));
        topLeftCorner.saveMinimumXAndY(BitmapSignedXY(dnlfcorner._x-PIXELSSEARCHSIZE,dnlfcorner._y-PIXELSSEARCHSIZE));
        topLeftCorner.saveMinimumXAndY(BitmapSignedXY(dnlfcorner._x+PIXELSSEARCHSIZE,dnlfcorner._y+PIXELSSEARCHSIZE));
        BitmapSignedXY bottomLeftCorner(uplfcorner._x-PIXELSSEARCHSIZE,uplfcorner._y-PIXELSSEARCHSIZE);
        bottomLeftCorner.saveMaximumXAndY(BitmapSignedXY(uplfcorner._x+PIXELSSEARCHSIZE,uplfcorner._y+PIXELSSEARCHSIZE));
        bottomLeftCorner.saveMaximumXAndY(BitmapSignedXY(dnlfcorner._x-PIXELSSEARCHSIZE,dnlfcorner._y-PIXELSSEARCHSIZE));
        bottomLeftCorner.saveMaximumXAndY(BitmapSignedXY(dnlfcorner._x+PIXELSSEARCHSIZE,dnlfcorner._y+PIXELSSEARCHSIZE));
        BitmapSignedXY topRightCorner(uprtcorner._x-PIXELSSEARCHSIZE,uprtcorner._y-PIXELSSEARCHSIZE);
        topRightCorner.saveMinimumXAndY(BitmapSignedXY(uprtcorner._x+PIXELSSEARCHSIZE,uprtcorner._y+PIXELSSEARCHSIZE));
        topRightCorner.saveMinimumXAndY(BitmapSignedXY(dnrtcorner._x-PIXELSSEARCHSIZE,dnrtcorner._y-PIXELSSEARCHSIZE));
        topRightCorner.saveMinimumXAndY(BitmapSignedXY(dnrtcorner._x+PIXELSSEARCHSIZE,dnrtcorner._y+PIXELSSEARCHSIZE));
        BitmapSignedXY bottomRightCorner(uprtcorner._x-PIXELSSEARCHSIZE,uprtcorner._y-PIXELSSEARCHSIZE);
        bottomRightCorner.saveMaximumXAndY(BitmapSignedXY(uprtcorner._x+PIXELSSEARCHSIZE,uprtcorner._y+PIXELSSEARCHSIZE));
        bottomRightCorner.saveMaximumXAndY(BitmapSignedXY(dnrtcorner._x-PIXELSSEARCHSIZE,dnrtcorner._y-PIXELSSEARCHSIZE));
        bottomRightCorner.saveMaximumXAndY(BitmapSignedXY(dnrtcorner._x+PIXELSSEARCHSIZE,dnrtcorner._y+PIXELSSEARCHSIZE));
        gddx=topLeftCorner.getX();
        gddy=topLeftCorner.getY();
        snippet = bitmap.getSnippetReadFromFileWithOutOfRangeCoordinates(gddx, gddy, bottomLeftCorner.getX(), bottomLeftCorner.getY());
        //Q1
        temppoint1 = transposePoint(uplfcorner,gddx,gddy);
        temppoint2 = transposePoint(dnlfcorner,gddx,gddy);
        templine=transposeLine(leftline,0,gddx,gddy);
        if(getQuestionsFromLine(snippet, Q1,m_configuration.getNumberOfQuestionsAtColumn(1),tdoublearr,templine,temppoint1,temppoint2,barheightsamplepixels)==1)
        {
            cout<<"ERROR: Error in finding questions in left line."<<endl;
            break;
        }
        //Q4

        snippet.clear();
        gddx=topRightCorner.getX();
        gddy=topRightCorner.getY();
        snippet = bitmap.getSnippetReadFromFileWithOutOfRangeCoordinates(gddx, gddy, bottomRightCorner.getX(), bottomRightCorner.getY());
        temppoint1 = transposePoint(uprtcorner,gddx,gddy);
        temppoint2 = transposePoint(dnrtcorner,gddx,gddy);
        templine=transposeLine(rightline,0,gddx,gddy);
        if(getQuestionsFromLine(snippet, Q4,m_configuration.getNumberOfQuestionsAtColumn(2),tdoublearr,templine,temppoint1,temppoint2,barheightsamplepixels)==1)
        {
            cout<<"ERROR: Error in finding questions in right line."<<endl;
            break;
        }
        if(m_configuration.getNumberOfColumns()==2)
        {
            temppoint1=getMidpoint(uplfcorner,upcenter);
            temppoint2=getMidpoint(upcenter,uprtcorner);
            BitmapSignedXY topLeftCornerMidPoint(temppoint1._x,temppoint1._y-PIXELSSEARCHSIZE);
            BitmapSignedXY bottomRightCornerMidPoint(temppoint1._x,temppoint1._y-PIXELSSEARCHSIZE);
            topLeftCornerMidPoint.saveMinimumXAndY(BitmapSignedXY(temppoint2._x,temppoint2._y-PIXELSSEARCHSIZE));
            bottomRightCornerMidPoint.saveMaximumXAndY(BitmapSignedXY(temppoint2._x,temppoint2._y-PIXELSSEARCHSIZE));

            temppoint1=getMidpoint(dnlfcorner,dncenter);
            temppoint2=getMidpoint(dncenter,dnrtcorner);

            topLeftCornerMidPoint.saveMinimumXAndY(BitmapSignedXY(temppoint1._x,temppoint1._y+PIXELSSEARCHSIZE));
            topLeftCornerMidPoint.saveMinimumXAndY(BitmapSignedXY(temppoint2._x,temppoint2._y+PIXELSSEARCHSIZE));
            bottomRightCornerMidPoint.saveMaximumXAndY(BitmapSignedXY(temppoint1._x,temppoint1._y+PIXELSSEARCHSIZE));
            bottomRightCornerMidPoint.saveMaximumXAndY(BitmapSignedXY(temppoint2._x,temppoint2._y+PIXELSSEARCHSIZE));

            snippet.clear();
            gddx=topLeftCornerMidPoint.getX();
            gddy=topLeftCornerMidPoint.getY();
            snippet = bitmap.getSnippetReadFromFileWithOutOfRangeCoordinates(gddx, gddy, bottomRightCornerMidPoint.getX(), bottomRightCornerMidPoint.getY());

            maxLineSamples=ROBUSTSAMPLESLINE;
            //center left line
            temppoint1 = transposePoint(upcenter,gddx,gddy);
            temppoint2 = transposePoint(dncenter,gddx,gddy);
            cout<<"INFO: Finding center left line. NumOfSamples="<<maxLineSamples<<endl;
            numLineSamples = findLineImageFromRight(snippet, lineSamples, maxLineSamples, temppoint1, temppoint2);
            DBGPRINT("INFO: BlackSamples=%d\n",numLineSamples);
            numLineSamples = removeOutliersFromLine(lineSamples, tdoublearr, &ccSlope, numLineSamples, 0);
            DBGPRINT("INFO: SucessfulSamples=%d\n",numLineSamples);
            if(ROBUSTMINSAMPLESLINE>numLineSamples)
            {
                cout<<"ERROR: Error in finding the line. Number of samples is not enough (numLineSamples="<<numLineSamples<<")."<<endl;
                break;
            }
            if(getSlope(lineSamples,tdoublearr,numLineSamples, 0)==1)
            {
                cout<<"ERROR: Invalid Slope."<<endl;
                break;
            }
            getChebyshevDouble(&ccSlope, tdoublearr, numLineSamples-1);
            centerleftline.intercept=getIntercept(lineSamples,ccSlope.mean,numLineSamples,0);
            centerleftline.slope=ccSlope.mean;
            centerleftline=transposeLine(centerleftline,0,-1*gddx,-1*gddy);
            //Q2
            temppoint1 = findIntersection(centerleftline,topline);temppoint1 = transposePoint(temppoint1,gddx,gddy);
            temppoint2 = findIntersection(centerleftline,bottomline);temppoint2 = transposePoint(temppoint2,gddx,gddy);
            templine = transposeLine(centerleftline,0,gddx,gddy);
            if(getQuestionsFromLine(snippet,Q2,m_configuration.getNumberOfQuestionsAtColumn(1),tdoublearr,templine,temppoint1,temppoint2,barheightsamplepixels)==1)
            {
                cout<<"ERROR: Error in finding questions in center left line."<<endl;
                break;
            }
            //center right line
            temppoint1 = transposePoint(upcenter,gddx,gddy);
            temppoint2 = transposePoint(dncenter,gddx,gddy);
            cout<<"INFO: Finding center right line. NumOfSamples="<<maxLineSamples<<endl;
            numLineSamples = findLineImageFromLeft(snippet, lineSamples, maxLineSamples, temppoint1, temppoint2);
            DBGPRINT("INFO: BlackSamples=%d\n",numLineSamples);
            numLineSamples = removeOutliersFromLine(lineSamples, tdoublearr, &ccSlope, numLineSamples, 0);
            DBGPRINT("INFO: SucessfulSamples=%d\n",numLineSamples);
            if(ROBUSTMINSAMPLESLINE>numLineSamples)
            {
                cout<<"ERROR: Error in finding the line. Number of samples is not enough (numLineSamples="<<numLineSamples<<")."<<endl;
                break;
            }
            if(getSlope(lineSamples,tdoublearr,numLineSamples, 0)==1)
            {
                cout<<"ERROR: Invalid Slope."<<endl;
                break;
            }
            getChebyshevDouble(&ccSlope, tdoublearr, numLineSamples-1);
            centerrightline.intercept=getIntercept(lineSamples,ccSlope.mean,numLineSamples,0);
            centerrightline.slope=ccSlope.mean;
            centerrightline=transposeLine(centerrightline,0,-1*gddx,-1*gddy);
            //Q3
            temppoint1 = findIntersection(centerrightline,topline);temppoint1 = transposePoint(temppoint1,gddx,gddy);
            temppoint2 = findIntersection(centerrightline,bottomline);temppoint2 = transposePoint(temppoint2,gddx,gddy);
            templine = transposeLine(centerrightline,0,gddx,gddy);
            if(getQuestionsFromLine(snippet ,Q3,m_configuration.getNumberOfQuestionsAtColumn(2),tdoublearr,templine,temppoint1,temppoint2,barheightsamplepixels)==1)
            {
                cout<<"ERROR: Error in finding questions in center right line."<<endl;
                break;
            }
        }
        if(m_configuration.getNumberOfColumns()==2){
            //COL1
            BitmapSignedXY topLeftCornerColumn1(uplfcorner._x,uplfcorner._y);
            BitmapSignedXY bottomRightCornerColumn1(uplfcorner._x,uplfcorner._y);
            topLeftCornerColumn1.saveMinimumXAndY(BitmapSignedXY(upcenter._x,upcenter._y));
            topLeftCornerColumn1.saveMinimumXAndY(BitmapSignedXY(dnlfcorner._x,dnlfcorner._y));
            topLeftCornerColumn1.saveMinimumXAndY(BitmapSignedXY(dncenter._x,dncenter._y));
            bottomRightCornerColumn1.saveMaximumXAndY(BitmapSignedXY(upcenter._x,upcenter._y));
            bottomRightCornerColumn1.saveMaximumXAndY(BitmapSignedXY(dnlfcorner._x,dnlfcorner._y));
            bottomRightCornerColumn1.saveMaximumXAndY(BitmapSignedXY(dncenter._x,dncenter._y));

            snippet.clear();
            gddx=topLeftCornerColumn1.getX();
            gddy=topLeftCornerColumn1.getY();
            snippet = bitmap.getSnippetReadFromFileWithOutOfRangeCoordinates(gddx, gddy, bottomRightCornerColumn1.getX(), bottomRightCornerColumn1.getY());

            if(processOneColumn(snippet, Q1, Q2, m_configuration.getNumberOfQuestionsAtColumn(1), 1))
            {
                cout<<"ERROR: Error in finding number circles."<<endl;
                break;
            }
            //COL2
            BitmapSignedXY topLeftCornerColumn2(upcenter._x,upcenter._y);
            BitmapSignedXY bottomRightCornerColumn2(upcenter._x,upcenter._y);
            topLeftCornerColumn2.saveMinimumXAndY(BitmapSignedXY(dncenter._x,dncenter._y));
            topLeftCornerColumn2.saveMinimumXAndY(BitmapSignedXY(uprtcorner._x,uprtcorner._y));
            topLeftCornerColumn2.saveMinimumXAndY(BitmapSignedXY(dnrtcorner._x,dnrtcorner._y));
            bottomRightCornerColumn2.saveMaximumXAndY(BitmapSignedXY(dncenter._x,dncenter._y));
            bottomRightCornerColumn2.saveMaximumXAndY(BitmapSignedXY(uprtcorner._x,uprtcorner._y));
            bottomRightCornerColumn2.saveMaximumXAndY(BitmapSignedXY(dnrtcorner._x,dnrtcorner._y));

            snippet.clear();
            gddx=topLeftCornerColumn2.getX();
            gddy=topLeftCornerColumn2.getY();
            snippet = bitmap.getSnippetReadFromFileWithOutOfRangeCoordinates(gddx, gddy, bottomRightCornerColumn2.getX(), bottomRightCornerColumn2.getY());

            if(processOneColumn(snippet, Q3, Q4, m_configuration.getNumberOfQuestionsAtColumn(2), 2))
            {
                cout<<"ERROR: Error in finding number circles."<<endl;
                break;
            }
        }else if(m_configuration.getNumberOfColumns()==1){
            //SINGLE COLUMN
            BitmapSignedXY topLeftCornerColumn1(uplfcorner._x,uplfcorner._y);
            BitmapSignedXY bottomRightCornerColumn1(uplfcorner._x,uplfcorner._y);
            topLeftCornerColumn1.saveMinimumXAndY(BitmapSignedXY(dnlfcorner._x,dnlfcorner._y));
            topLeftCornerColumn1.saveMinimumXAndY(BitmapSignedXY(uprtcorner._x,uprtcorner._y));
            topLeftCornerColumn1.saveMinimumXAndY(BitmapSignedXY(dnrtcorner._x,dnrtcorner._y));
            bottomRightCornerColumn1.saveMaximumXAndY(BitmapSignedXY(dnlfcorner._x,dnlfcorner._y));
            bottomRightCornerColumn1.saveMaximumXAndY(BitmapSignedXY(uprtcorner._x,uprtcorner._y));
            bottomRightCornerColumn1.saveMaximumXAndY(BitmapSignedXY(dnrtcorner._x,dnrtcorner._y));

            snippet.clear();
            gddx=topLeftCornerColumn1.getX();
            gddy=topLeftCornerColumn1.getY();
            snippet = bitmap.getSnippetReadFromFileWithOutOfRangeCoordinates(gddx, gddy, bottomRightCornerColumn1.getX(), bottomRightCornerColumn1.getY());

            if(processOneColumn(snippet, Q1, Q4, m_configuration.getNumberOfQuestionsAtColumn(1), 1))
            {
                cout<<"ERROR: Error in finding number circles."<<endl;
                break;
            }
        }
        isFinishedSuccessfully=true;
    }
    cout<<"DONE!"<<endl;
    if(!isFinishedSuccessfully)
    {
        m_numberOfRespondents++;
        m_status = SoosaStatus::AlgorithmError;
        return;
    }
}

bool SOOSA::isStatusNoError(SoosaStatus const status)
{
    return status == SoosaStatus::NoError;
}

void SOOSA::processDirectory(string const& directoryPath)
{
    cout<<"processDirectory: ["<<directoryPath<<"]"<<endl;

    AlbaLocalPathHandler directoryPathToBeProcessed(directoryPath);
    set<string> listOfFiles;
    set<string> listOfDirectories;
    directoryPathToBeProcessed.findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectories);

    for(string const& filePath : listOfFiles)
    {
        processOneFile(filePath);
        saveDataToCsvFile(filePath);
    }
}

int SOOSA::process()
{
    cout<<"SOOSA2014 - Survey Output Optical Scan Analyzer\n\n"<<endl;
    cout<<"Path: "<<m_configuration.getPath()<<endl;
    cout<<"Area: "<<m_configuration.getArea()<<endl;
    cout<<"Period: "<<m_configuration.getPeriod()<<endl;
    cout<<"Discharge: "<<m_configuration.getDischarge()<<endl;
    cout<<"NumberOfQuestions: "<<m_configuration.getNumberOfQuestions()<<endl;
    cout<<"NumberOColumns: "<<m_configuration.getNumberOfColumns()<<endl;


    AlbaLocalPathHandler pathHandler(m_configuration.getPath());

    saveHeadersToCsvFile();
    if(pathHandler.isDirectory())    {
        processDirectory(pathHandler.getFullPath());
    }
    else    {
        processOneFile(pathHandler.getFullPath());
        saveDataToCsvFile(pathHandler.getFullPath());
    }
    saveOutputHtmlFile(pathHandler.getFullPath());

    return 0;
}


}
