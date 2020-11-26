#include "SOOSA.hpp"

#include <File/AlbaFileReader.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <String/AlbaStringHelper.hpp>
#include <User/AlbaUserInterface.hpp>
#include <Statistics/FrequencyStatistics.hpp>

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

#define FILE_PATH_BASIS_HTML APRG_DIR R"(SOOSA2014\basis.html)"
#define MAXSTR 500
#define MAXQUESTIONSCOOR 60 //2*30 -> MUST be twice of MAXQUESTIONS
#define SAMPLESLINETOALLOC 1000
#define ROBUSTSAMPLESLINE 1000
#define ROBUSTMINSAMPLESLINE 100
#define ROBUSTSAMPLESLINETOPBOTTOM 500
#define ROBUSTMINSAMPLESLINETOPBOTTOM 100
#define PIXELSPERPENLINE 100
#define PIXELSSEARCHSIZE 200//2*PIXELSPERPENLINE -> MUST be twice of PIXELSPERPENLINE
#define PIXELSCIRCLERADIUSHIGH 16
#define PIXELSCIRCLERADIUSLOW 10
#define PERCENTSHADED 60
#define PIXELSDIRTBLACKDOT 1 //1 black is considered dirt
#define PIXELSDIRTWHITEDOT 4 //4 white is considered dirt
#define STDDEVLOWEST 0.01
#define BARHEIGHTLOW 30
#define BARHEIGHTHIGH 80
#define ALLOWANCEMULT 3.5
#define CHEBYCHEVKVALUE 2.5
#define CHEBYCHEVKVALUEWIDTH 4
#define CHEBYCHEVKVALUEHEIGHT 4
#define CHEBYCHEVKVALUEQUES 1

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


//gawa struct for x y for points and slope
//gawa function search to right search to the left
//chebyshev
//k-mean cluster algo
//cache in DataDigital for continuous access

//malloc check
//getvalue check cache

//put in a function circle loop

using namespace std;

namespace alba
{

SOOSA::SOOSA(SoosaConfiguration const& configuration)
    : m_configuration(configuration)
{
    m_numberOfRespondents=0;
}

void SOOSA::clearFrequencyDatabase()
{
    for(unsigned int i=0; i<MAXQUESTIONSALL; i++)
    {
        for(unsigned int j=0; j<6; j++)
        {
            m_questionToAnswerFrequencyMap[i][j]=0;
        }
    }
}

unsigned int SOOSA::getNumberOfAnswers() const
{
    return m_questionToAnswersMap.size();
}

unsigned int SOOSA::getAnswerToQuestion(unsigned int const questionNumber) const
{
    return m_questionToAnswersMap.at(questionNumber);
}

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

void  SOOSA::addToFrequencyDatabase(unsigned int const questionNumber, unsigned int const answer)
{
    m_questionToAnswerFrequencyMap[questionNumber][answer]++;
}

void SOOSA::saveDataToCsvFile(string const& processedFilePath)
{
    ofstream outputCsvReportStream(getCsvFileName(m_configuration.getPath()), ofstream::app);
    ALBA_DEBUG_PRINT2(m_configuration.getNumberOfQuestions(), m_questionToAnswersMap.size());
    if(m_configuration.getNumberOfQuestions() != m_questionToAnswersMap.size())
    {
        m_status = SoosaStatus::AlgorithmError;
        ALBA_DEBUG_PRINT1((int)m_status);
    }
    if(isStatusNoError(m_status))
    {
        outputCsvReportStream<<processedFilePath<<",OK";
        for(unsigned int i=0;i<m_configuration.getNumberOfQuestions();i++)
        {
            outputCsvReportStream<<","<<getAnswerToQuestion(i);
            if(getAnswerToQuestion(i)<=5 && getAnswerToQuestion(i)>=1){addToFrequencyDatabase(i, getAnswerToQuestion(i)-1);}
        }
        outputCsvReportStream<<endl;
    }
    else
    {
        outputCsvReportStream<<processedFilePath<<","<<getString(m_status)<<endl;
    }
}

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
                FrequencyStatistics<double>::FrequencySamples samples;
                for(unsigned int answerIndex=0; answerIndex<5; answerIndex++)
                {
                    samples[answerIndex+1] = m_questionToAnswerFrequencyMap[questionIndex][answerIndex];
                }
                unsigned int numberOfSamplesForQuestion = FrequencyStatistics<double>::calculateNumberOfSamples(samples);
                double median = FrequencyStatistics<double>::calculateMedian(samples);
                if(questionIndex==m_configuration.getNumberOfQuestions()-1)
                {
                    reportHtmlFileStream<<"<td style=\"text-align:left;padding:3px\"><b>"<<m_configuration.getQuestionAt(questionIndex)<<"</b></td>"<<endl;
                }
                else
                {
                    reportHtmlFileStream<<"<td style=\"text-align:left;padding:3px\">"<<m_configuration.getQuestionAt(questionIndex)<<"</td>"<<endl;
                }
                reportHtmlFileStream<<"<td style=\"text-align:center;padding:3px\">"<<getPrintableStringForPercentage(m_questionToAnswerFrequencyMap[questionIndex][4],numberOfSamplesForQuestion)<<"</td>"<<endl;
                reportHtmlFileStream<<"<td style=\"text-align:center;padding:3px\">"<<getPrintableStringForPercentage(m_questionToAnswerFrequencyMap[questionIndex][3],numberOfSamplesForQuestion)<<"</td>"<<endl;
                reportHtmlFileStream<<"<td style=\"text-align:center;padding:3px\">"<<getPrintableStringForPercentage(m_questionToAnswerFrequencyMap[questionIndex][2],numberOfSamplesForQuestion)<<"</td>"<<endl;
                reportHtmlFileStream<<"<td style=\"text-align:center;padding:3px\">"<<getPrintableStringForPercentage(m_questionToAnswerFrequencyMap[questionIndex][1],numberOfSamplesForQuestion)<<"</td>"<<endl;
                reportHtmlFileStream<<"<td style=\"text-align:center;padding:3px\">"<<getPrintableStringForPercentage(m_questionToAnswerFrequencyMap[questionIndex][0],numberOfSamplesForQuestion)<<"</td>"<<endl;
                reportHtmlFileStream<<"<td style=\"text-align:center;padding:3px\">"<<numberOfSamplesForQuestion<<"</td>"<<endl;
                reportHtmlFileStream<<"<td style=\"text-align:center;padding:3px\">"<<median<<"</td>"<<endl;
                reportHtmlFileStream<<"<td style=\"text-align:center;padding:3px\">"<<getPrintableStringForPercentage(m_questionToAnswerFrequencyMap[questionIndex][4]+m_questionToAnswerFrequencyMap[questionIndex][3]+m_questionToAnswerFrequencyMap[questionIndex][2],numberOfSamplesForQuestion)<<"</td>"<<endl;
                reportHtmlFileStream<<"</tr>"<<endl;
            }
        }
        else
        {
            reportHtmlFileStream<<line<<endl;
        }
    }
}


















void SOOSA::getChebyshevInt(ChebyshevCriterion* in_cc, int* arr, int num)
{
    int i;
    double mean=0, stddev=0;
    for(i=0; i<num; i++){
        LOPPRINT("  FUNCLOOP:getChebyshevInt[i=%d]->(arr[i]=%d|mean=%lf)\n",i,arr[i],mean);
        mean=mean+arr[i];
    }
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

inline int SOOSA::getValue(DataDigital* indata, int x, int y)
{
    if(x<0 || y<0 || x>=(indata->xSizeBytesAllocated*8) || y>=(indata->ySizeBytesAllocated)){
        LOPPRINT("  FUNC:getValue(x=%d|y=%d|xalloc:%d|yalloc:%d)->ret=0  |Out of Bounds\n",x+gddx,y+gddy,indata->xSizeBytesAllocated,indata->ySizeBytesAllocated);
        return 0;
    }
    if(G_x==x>>3 && G_y==y){
        if(((G_value<<(x%8))&0x80)==0){
            LOPPRINT("  FUNC:getValue(x=%d|y=%d)->(G_x=%d,G_y=%d,G_value=%x) ret=1  |Valid value from global cache\n",x+gddx,y+gddy,G_x,G_y,G_value);
            return 1;
        }else{
            LOPPRINT("  FUNC:getValue(x=%d|y=%d)->(G_x=%d,G_y=%d,G_value=%x) ret=0  |Valid value from global cache\n",x+gddx,y+gddy,G_x,G_y,G_value);
            return 0;
        };
    }
    G_x=x>>3;G_y=y;
    G_value = indata->buf[G_x+(G_y*(indata->xSizeBytesAllocated))];
    if(((G_value<<(x%8))&0x80)==0){
        LOPPRINT("  FUNC:getValue(x=%d|y=%d)->(G_x=%d,G_y=%d,G_value=%x) ret=1  |Valid value from data access\n",x+gddx,y+gddy,G_x,G_y,G_value);
        return 1;
    }else{
        LOPPRINT("  FUNC:getValue(x=%d|y=%d)->(G_x=%d,G_y=%d,G_value=%x) ret=0  |Valid value from data access\n",x+gddx,y+gddy,G_x,G_y,G_value);
        return 0;
    };
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

long SOOSA::getImageInfo(FILE* inputFile, long offset, int numberOfChars)
{
    unsigned char *ptrC;
    long value=0L;
    unsigned char dummy;
    int i;

    dummy = '0'; ptrC = &dummy;

    fseek(inputFile, offset, SEEK_SET);

    for(i=1; i<=numberOfChars; i++)
    {
        fread(ptrC, sizeof(char), 1, inputFile);
        value = (long)(value + (*ptrC)*(pow(256, (i-1))));
    }

    return(value);

}

int SOOSA::openBmpImage(BmpImage* inBmpImage, char const* sbmp)
{

    FILE* bmpInput = NULL;
    inBmpImage->filePtr = NULL;
    char signature[2]; /* Signature of the Image File BM = BMP */
    int nRows, nCols; /* Row and Column size of the Image */
    int xpixpeRm, ypixpeRm; /* Pixel/m */
    long nColors; /* BMP number of colors */
    long fileSize; /* BMP file size */
    long vectorSize; /* BMP's raster data in number of bytes */
    int nBits; /* # of BIts per Pixel */
    int rasterOffset; /* Beginning of the Raster Data */
    int setColor;
    int nRasterPad;
    int i;

    if ((bmpInput = fopen(sbmp, "r+b")) == NULL)
    {
        cout<<"ERROR: Cannot read BMP file. File exit."<<endl;
        return 1;
    }

    for(i=0; i<2; i++)
    {
        signature[i] = (char)getImageInfo(bmpInput, (long)i, 1);
    }
    if ((signature[0] == 'B') && (signature[1] == 'M')) {
        DBGPRINT("It is verified that the Image is in Bitmap format\n");
    }else
    {
        cout<<"ERROR: The image is not in bitmap format. File exit."<<endl;
        return 2;
    }

    /* Read BMP bits/pixel at byte #28 */
    nBits = (int)getImageInfo(bmpInput, 28, 2);
    DBGPRINT("The Image is \t%d-bit\n", nBits);

    if(nBits!=1)
    {
        cout<<"ERROR: The Image is not a 1-bit Bitmap. Pls resave this bitmap. File exit."<<endl;
        return 3;
    }
    /* Position of First Raster Data at byte # 10*/
    rasterOffset = (int)getImageInfo(bmpInput, 10, 4);
    inBmpImage->rasterBegin = rasterOffset;
    DBGPRINT("The beginning of the Raster Data \nis at \t\t%d byte\n", rasterOffset);

    /* Read BMP file size at byte # 2 */
    fileSize = getImageInfo(bmpInput, 2, 4);
    DBGPRINT("File size is \t%ld byte\n", fileSize);

    /* Read BMP width at byte #18 */
    nCols = (int)getImageInfo(bmpInput, 18, 4);
    DBGPRINT("Width: \t\t%d\n", nCols);
    inBmpImage->xSize=nCols;

    /* Read BMP height at byte #22 */
    nRows = (int)getImageInfo(bmpInput, 22, 4);
    DBGPRINT("Height: \t%d\n", nRows);
    inBmpImage->ySize=nRows;
    /* # of Pixels in a meter in x direction at byte # 38 */
    xpixpeRm = (int)getImageInfo(bmpInput, 38, 4);
    DBGPRINT("Image has \t%d pixels per m in x-dir.\n", xpixpeRm);

    /* # of Pixels in a meter in y direction at byte # 42 */
    ypixpeRm = getImageInfo(bmpInput, 42, 4);
    DBGPRINT("Image has \t%d pixels per m in y-dir.\n", ypixpeRm);

    nRasterPad=( 4-(rasterRound((double)nCols/8)%4) ) % 4;
    inBmpImage->rasterPad = nRasterPad;
    DBGPRINT("Raster pad is %d.\n", nRasterPad);

    /* Read number of colors at byte #46 */
    nColors = pow(2L,nBits);
    DBGPRINT("There are \t%ld number of Colors \n", nColors);

    vectorSize = (long)((long)nCols*(long)nRows);
    DBGPRINT("Vector Size is \t%ld\n", vectorSize);

    setColor = (int)getImageInfo(bmpInput, 54, 1);

    if(setColor==0xFF){
        DBGPRINT("Setcolor is White\n");
        setColor=0;
    }else{
        DBGPRINT("Setcolor is Black\n");
        setColor=1;
    }
    inBmpImage->setColor = setColor;

    inBmpImage->numBytesOneRow = rasterRound((double)nCols/8) + nRasterPad;
    DBGPRINT("Number of bytes for one row is \t%ld\n", inBmpImage->numBytesOneRow);

    inBmpImage->filePtr=bmpInput;
    return 0;
} /* end of main */

inline void SOOSA::closeBmpImage(BmpImage* inBmpImage)
{
    if(inBmpImage->filePtr!=NULL){
        fclose(inBmpImage->filePtr);
    }
    inBmpImage->filePtr = NULL;
}

int SOOSA::getDataFromBmp(BmpImage* inBmpImage,DataDigital* indata)
{
    if(indata->status!=2){return 1;}
    unsigned char *ptrC;
    int x, xsizebytes=indata->xSizeBytesAllocated;
    int y, ylow=indata->ylow, yhigh=indata->yhigh;
    int ysize=inBmpImage->ySize, nbor = inBmpImage->numBytesOneRow;
    int rasterBegin = inBmpImage->rasterBegin;
    FILE* t1fileaddress = inBmpImage->filePtr;
    long offset;
    int i;
    DBGPRINT("  FUNC:getDataFromBmp(LOW(%d,%d) to HIGH(%d,%d))  |Transferring data from BMP to DataDigital.\n", indata->xlow,indata->ylow,indata->xhigh,indata->yhigh);

    if(inBmpImage->setColor==1){
        x=indata->xlow/8;
        for(y=ylow; y<=yhigh; y++){
            offset = rasterBegin+(nbor*(ysize-y-1))+x;
            ptrC = &(indata->buf[(y-ylow)*xsizebytes]);
            fseek(t1fileaddress, offset, SEEK_SET);
            LOPPRINT("  FUNCLOOP:getDataFromBmp[x=%d|y=%d]->(offset=%ld | nbor=%d)\n",x,y,offset,nbor);
            fread(ptrC, sizeof(char), xsizebytes, t1fileaddress);
        }
    }else{
        x=indata->xlow/8;
        for(y=ylow; y<=yhigh; y++){
            offset = rasterBegin+(nbor*(ysize-y-1))+x;
            ptrC = &(indata->buf[(y-ylow)*xsizebytes]);
            fseek(t1fileaddress, offset, SEEK_SET);
            LOPPRINT("  FUNCLOOP:getDataFromBmp[x=%d|y=%d]->(offset=%ld | nbor=%d)\n",x,y,offset,nbor);
            fread(ptrC, sizeof(char), xsizebytes, t1fileaddress);
            for(i=0; i<xsizebytes; i++){ptrC[i]=(ptrC[i])^(0xFF);}
        }
    }
    DBGPRINT("  FUNCOUT:getDataFromBmp(LOW(%d,%d) to HIGH(%d,%d))  |Transferred data from BMP to DataDigital.\n", indata->xlow,indata->ylow,indata->xhigh,indata->yhigh);
    indata->status=3;
#ifdef  DBGFLAG
    gddx=indata->xlow;
    gddy=indata->ylow;
    DBGPRINT("  FUNCOUT:getDataFromBmp[gddx=%d|gddy=%d]\n",gddx,gddy);
#endif
    return 0;
}

inline int SOOSA::allocData(DataDigital* indata)
{
    if(indata->status!=1){return 1;}
    indata->xSizeBytesAllocated=(indata->xhigh-indata->xlow+1)/8;
    indata->ySizeBytesAllocated=(indata->yhigh-indata->ylow)+1;
    indata->buf = (unsigned char*)malloc((indata->xSizeBytesAllocated)*(indata->ySizeBytesAllocated)*sizeof(char));
    if(indata->buf==NULL){return 1;}
    indata->status=2;
    return 0;
}

inline void SOOSA::deAllocData(DataDigital* indata)
{
    if(indata->status<2){return;}
    if(indata->buf!=NULL){free(indata->buf);}
    indata->buf = NULL;
    indata->xSizeBytesAllocated=0;indata->ySizeBytesAllocated=0;
    indata->status=0;
}

inline void SOOSA::cleanDataDigital(DataDigital* indata)
{
    if(indata->buf!=NULL){free(indata->buf);}
    indata->buf = NULL;
    indata->xSizeBytesAllocated=0;indata->ySizeBytesAllocated=0;
    indata->status=0;
}

inline void SOOSA::printDataDigitalBuffer(DataDigital* indata)
{
    if(indata->status!=3){return;}
#ifdef  DBGFLAG
    FILE* bufferprint = NULL;
    if ((bufferprint = fopen("BUFFERTEST.TXT", "w")) == NULL){
        cout<<"ERROR: Cannot write to BUFFER.TXT. File exit."<<endl;
        return;
    }
    int x, y, m;
    unsigned char tbuf;
    for(y=0;y<indata->ySizeBytesAllocated;y++){
        for(x=0;x<indata->xSizeBytesAllocated;x++){
            tbuf = indata->buf[(y*indata->xSizeBytesAllocated)+x];
            for(m=0;m<8;m++){
                if((tbuf&0x80)==0x80){fprintf(bufferprint,"_");
                }else{fprintf(bufferprint,"X");
                }
                tbuf = tbuf<<1;
            }
        }
        fprintf(bufferprint,"\n");
    }
    fclose(bufferprint);
    bufferprint=NULL;
#endif
}

inline void SOOSA::printDataDigitalProperty(DataDigital* indata)
{
    DBGPRINT("\n");
    if(indata->status==0)
    {
        cout<<"DDINFO: DataDigital Status: IDLE"<<endl;
    }
    else if(indata->status==1)
    {
        cout<<"DDINFO: DataDigital Status: POINTS ADDED"<<endl;
    }
    else if(indata->status==2)
    {
        cout<<"DDINFO: DataDigital Status: ALLOCATED"<<endl;
    }
    else if(indata->status==3)
    {
        cout<<"DDINFO: DataDigital Status: DATA TRANSFERRED, Ready To Use"<<endl;
    }
    cout<<"DDINFO: DataDigital Status: Lowest: ("<<indata->xlow<<","<<indata->ylow<<") "<<endl;
    cout<<"DDINFO: Highest: ("<<indata->xhigh<<","<<indata->yhigh<<") "<<endl;
    cout<<"DDINFO: SizeAllocated: ("<<indata->xSizeBytesAllocated<<","<<indata->ySizeBytesAllocated<<") "<<endl;
    cout<<"DDINFO: Address: "<<(unsigned int)(indata->buf)<<endl;
    DBGPRINT("\n");
}

void SOOSA::addPointToDataDigital(BmpImage* inBmpImage,DataDigital* indata, int xp, int yp)
{
    DBGPRINT("  FUNC:addPointToDataDigital(xp=%d|yp=%d|xsize=%d|ysize=%d)\n",xp,yp,inBmpImage->xSize,inBmpImage->ySize);
    if(xp<0){xp=0;}
    if(yp<0){yp=0;}
    if(xp>=inBmpImage->xSize){xp=inBmpImage->xSize-1;}
    if(yp>=inBmpImage->ySize){yp=inBmpImage->ySize-1;}


    if(indata->status==0){
        indata->xlow=(xp>>3)<<3;indata->xhigh=(((xp>>3)+1)<<3)-1;
        indata->ylow=yp;indata->yhigh=yp;
        indata->status=1;
        DBGPRINT("  FUNC:addPointToDataDigital(status=%d)  |First Point\n",indata->status);
        return;
    }
    if(xp<indata->xlow){indata->xlow=(xp>>3)<<3;
    }else if(xp>indata->xhigh){indata->xhigh = (((xp>>3)+1)<<3)-1;//=(xrem>0) ? xp+8-xrem : xp;
    }
    if(yp<indata->ylow){indata->ylow=yp;
    }else if(yp>indata->yhigh){indata->yhigh=yp;
    }
    DBGPRINT("  FUNC:addPointToDataDigital(LOW(%d,%d) to HIGH(%d,%d))\n", indata->xlow,indata->ylow,indata->xhigh,indata->yhigh);
}

inline double SOOSA::checkIfShaded(DataDigital* indata,PairXY center, CircleCriterion circ, int ques, int col, int choice, PairXY point1, PairXY point2)
{
    int startx,starty,incx,incy,diameter;
    int countall,countblack;
    int noChange,type,moved;
    double scorePercent,maxScorePercent;
#ifdef CIRFLAG
    char tempstr[MAXSTR];
    sprintf(tempstr,"CIR_COL%d_QUES%d_R%d_choice%d.txt",col,ques,circ.radius,choice);
    circlefile=NULL;
    if ((circlefile = fopen(tempstr, "w")) == NULL)
    {
        cout<<"ERROR: Error in circle log file."<<endl;
        return 1;
    }
#endif
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
                    if(getValue(indata,startx+incx,starty+incy)){
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

inline int SOOSA::processOneQuestion(DataDigital* indata, PairXY point1, PairXY point2, int ques, int col, CircleCriterion circ)
{
    DBGPRINT("  FUNC:processOneQuestion point1(%d,%d) point2(%d,%d)\n",point1._x+gddx,point1._y+gddy,point2._x+gddx,point2._y+gddy);
    PairXY temppoint;
    int t1,tch;
    double dtemp;
    tch=0;
#ifdef CIRFLAG
    char tempstr[MAXSTR];
    FILE* circlefile = NULL;
    sprintf(tempstr,"CIR_COL%d_QUES%d.txt",col,ques);
    if ((circlefile = fopen(tempstr, "w")) == NULL)
    {
        cout<<"ERROR: Error in circle log file."<<endl;
        return 1;
    }
#endif
    for(t1=0;t1<5;t1++){
        dtemp = (((double)t1*2)+1)/10;
        CIRPRINT("DTEMP:%lf (%d + %d)\n",dtemp,point1._x+gddx,roundOffSignRobust(((double)point2._x-point1._x)*dtemp));
        CIRPRINT("POINT1:(%d,%d)\n",point1._x+gddx,point1._y+gddy);
        CIRPRINT("POINT2:(%d,%d)\n",point2._x+gddx,point2._y+gddy);
        temppoint._x = point1._x+ roundOffSignRobust(((double)point2._x-point1._x)*dtemp);
        temppoint._y = point1._y+ roundOffSignRobust(((double)point2._y-point1._y)*dtemp);
        CIRPRINT("TPOINT:(%d,%d)\n",temppoint._x+gddx,temppoint._y+gddy);
        dtemp = checkIfShaded(indata,temppoint,circ,ques,col,5-t1, point1, point2);
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

int SOOSA::processOneColumn(DataDigital* indata, PairXY* QuesArr1, PairXY* QuesArr2, int numQuestionsColumn, int columnNumber)
{
    int t1, t2, iteration, tchoice;
    PairXY point1, point2;
    int xlow=indata->xlow, ylow=indata->ylow;
    CircleCriterion circhighest, circlowest, clow, chigh, currentcirc;
    assignCircleCriterion(&circhighest,PIXELSCIRCLERADIUSHIGH);
    assignCircleCriterion(&circlowest,PIXELSCIRCLERADIUSLOW);
    assignMidCircleCriterion(&currentcirc,&circlowest,&circhighest,1);

    t2=0;
    DBGPRINT("  FUNC:processOneColumn low(x=%d,y=%d)\n",indata->xlow,indata->ylow);
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
            tchoice = processOneQuestion(indata, point1, point2, t1+1, columnNumber,currentcirc);
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

inline int SOOSA::followLineGetLengthXNew(AprgBitmapSnippet const& snippet, PairXY start, PairXY p1)
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

inline int SOOSA::followLineGetLengthX(DataDigital* indata,PairXY start, PairXY p1)
{
    //p2 and p3 are opposite directions, use states to dont go backwards
    int state,x,y,pty;
    LOPPRINT("  FUNC:followLineGetLengthX Start(%d|%d) P1(%d|%d) P3(%d|%d)\n",start._x+gddx,start._y+gddy,p1._x+gddx,p1._y+gddy);
    x=start._x; y=start._y; pty=0; state=0;
    while(1){
        LOPPRINT("  FUNCLOOP:followLineGetLengthX(x=%d|y=%d|pt=%d)\n",x+gddx,y+gddy,pty);
        if(pty>=PIXELSPERPENLINE){break;
            LOPPRINT("  FUNCLOOP:followLineGetLengthX->(pty=%d) |Perpendicular line exit\n",pty);
        }else if(getValue(indata,x+p1._x,y+p1._y)==1){x=x+p1._x; y=y+p1._y; state = 1; pty=pty+1;
            LOPPRINT("  FUNCLOOP:followLineGetLengthX->(Follow P1:(%d,%d)\n",x+gddx,y+gddy);
        }else if(state==1){while(getValue(indata,x,y-1)==1){y=y-1;} state=2;
            LOPPRINT("  FUNCLOOP:followLineGetLengthX->(Find TOP:(%d,%d)\n",x+gddx,y+gddy);
        }else if(state==2 && getValue(indata,x,y+1)==1){y=y+1;
            LOPPRINT("  FUNCLOOP:followLineGetLengthX->(Go Down(%d,%d)\n",x+gddx,y+gddy);
        }else{ break;
        }
    }
    LOPPRINT("  FUNC:followLineGetLengthX->(out=%d)\n",pty);
    return pty;
}

int SOOSA::findLineImageFromLeftNew(AprgBitmapSnippet const& snippet, PairXY* in_line, int numberOfSamples, PairXY inStart, PairXY inEnd)
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

int SOOSA::findLineImageFromLeft(PairXY* in_line, int numsamplesize, unsigned char* in_buf,int xsizebytesallocated,PairXY inStart,PairXY inEnd)
{
    int xt,yt,lt,mt,pt,ptwhite,lt_success;
    unsigned char dummy,mask;
    lt_success=0;
    DBGPRINT("  FUNC:findLineImageFromLeft(startx=%d|starty=%d|endx=%d|endy=%d)\n",inStart._x+gddx,inStart._y+gddy,inEnd._x+gddx,inEnd._y+gddy);
    for(lt=0;lt<numsamplesize;lt++){//lineSamples
        in_line[lt_success]._x = roundOffSignRobust((double)(inEnd._x-inStart._x)*lt/(numsamplesize))+inStart._x;
        in_line[lt_success]._y = roundOffSignRobust((double)(inEnd._y-inStart._y)*lt/(numsamplesize))+inStart._y;
        LOPPRINT("  FUNCLOOP:findLineImageFromLeft[lt=%d|x=%d|y=%d]\n",lt,in_line[lt_success]._x+gddx,in_line[lt_success]._y+gddy);
        yt = in_line[lt_success]._y*xsizebytesallocated;
        pt = 0;
        ptwhite=0;
        mt=in_line[lt_success]._x%8;
        for(xt=in_line[lt_success]._x/8;xt<xsizebytesallocated;xt++){//linebyteloop
            dummy = in_buf[yt+xt];
            for(;mt<8;mt++){//linebitloop
                mask=0x80>>mt;
                LOPPRINT("  FUNCLOOPXXX:findLineImageFromLeft[x=%d|y=%d|mt=%d|pt=%d]->dummy=%X|mask%X|bit=%d\n",(xt*8)+mt+gddx,in_line[lt_success]._y+gddy,mt,pt,dummy,mask,(dummy&mask)==0x00);
                if(pt>=PIXELSPERPENLINE){xt=xsizebytesallocated;break;}
                if((dummy&mask)==0x00){//black
                    pt=pt+1;
                    ptwhite=0;
                }else if(pt>PIXELSDIRTBLACKDOT && ptwhite>=PIXELSDIRTWHITEDOT){
                    pt=pt-ptwhite;
                    in_line[lt_success]._x = roundOffSignRobust( (xt*8)+mt-1-pt+(((double)pt)/2)-ptwhite );//minus-1 to get last white
                    LOPPRINT("  FUNCLOOPXXX:findLineImageFromLeft Successful->[x=%d|y=%d]\n",in_line[lt_success]._x+gddx,in_line[lt_success]._y+gddy);
                    xt=xsizebytesallocated;
                    lt_success++;
                    break;
                }else{
                    if(ptwhite<PIXELSDIRTWHITEDOT && pt>0){//consider white dirt
                        ptwhite++;
                        pt++;
                    }else{
                        pt=0;//if dirt encountered clear once white again
                    }
                }
            }
            mt=0;
        }
    }
#ifdef  DBGFLAG
    for(lt=0;lt<lt_success;lt++){//lineSamples
        DBGPRINT("  FUNCOUT:findLineImageFromLeft[%d]->[x=%d|y=%d]\n",lt,in_line[lt]._x+gddx,in_line[lt]._y+gddy);
    }
#endif
    return lt_success;

}

int SOOSA::findLineImageFromRightNew(AprgBitmapSnippet const& snippet, PairXY* in_line, int numberOfSamples, PairXY inStart, PairXY inEnd)
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
        for(unsigned int xInSnippet=in_line[lineSamplesSaved]._x+gddx; xInSnippet>=0; xInSnippet--)
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

int SOOSA::findLineImageFromRight(PairXY* in_line, int numsamplesize, unsigned char* in_buf,int xsizebytesallocated,PairXY inStart,PairXY inEnd)
{
    int xt,yt,lt,mt,pt,ptwhite,lt_success;
    unsigned char dummy,mask;
    lt_success=0;
    DBGPRINT("  FUNC:findLineImageFromRight(startx=%d|starty=%d|endx=%d|endy=%d)\n",inStart._x+gddx,inStart._y+gddy,inEnd._x+gddx,inEnd._y+gddy);
    for(lt=0;lt<numsamplesize;lt++){//lineSamples
        in_line[lt_success]._x = roundOffSignRobust((double)(inEnd._x-inStart._x)*lt/(numsamplesize))+inStart._x;
        in_line[lt_success]._y = roundOffSignRobust((double)(inEnd._y-inStart._y)*lt/(numsamplesize))+inStart._y;
        yt = in_line[lt_success]._y*xsizebytesallocated;
        pt = 0;
        ptwhite=0;
        mt=in_line[lt_success]._x%8;
        LOPPRINT("  FUNCLOOP:findLineImageFromRight[lt=%d|x=%d|y=%d]\n",lt,in_line[lt_success]._x+gddx,in_line[lt_success]._y+gddy);
        for(xt=in_line[lt_success]._x/8;xt>=0;xt--){//linebyteloop
            dummy = in_buf[yt+xt];
            for(;mt>=0;mt--){//linebitloop
                mask=0x80>>mt;
                LOPPRINT("  FUNCLOOPXXX:findLineImageFromRight[x=%d|y=%d|mt=%d|pt=%d]->bit=%d\n",(xt*8)+mt+gddx,in_line[lt_success]._y+gddy,mt,pt,(dummy&mask)==0x00);
                if(pt>=PIXELSPERPENLINE){xt=-1;break;}
                if((dummy&mask)==0x00){//black
                    pt=pt+1;
                    ptwhite=0;
                }else if(pt>PIXELSDIRTBLACKDOT && ptwhite>=PIXELSDIRTWHITEDOT){
                    pt=pt-ptwhite;
                    in_line[lt_success]._x =roundOffSignRobust( (xt*8)+mt+(((double)pt)/2)+ptwhite );
                    LOPPRINT("  FUNCLOOPXXX:findLineImageFromRight Successful->[x=%d|y=%d]\n",in_line[lt_success]._x+gddx,in_line[lt_success]._y+gddy);
                    xt=-1;
                    lt_success++;
                    break;
                }else{
                    if(ptwhite<PIXELSDIRTWHITEDOT && pt>0){//consider white dirt
                        ptwhite++;
                        pt++;
                    }else{
                        pt=0;//if dirt encountered clear once white again
                    }
                }
            }
            mt=7;
        }
    }
#ifdef  DBGFLAG
    for(lt=0;lt<lt_success;lt++){//lineSamples
        DBGPRINT("  FUNCOUT:findLineImageFromRight[%d]->[x=%d|y=%d]\n",lt,in_line[lt]._x+gddx,in_line[lt]._y+gddy);
    }
#endif
    return lt_success;
}

int SOOSA::findLineImageFromTopNew(AprgBitmapSnippet const& snippet, PairXY* in_line, int numberOfSamples, PairXY inStart, PairXY inEnd)
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
        for(iy=in_line[lineSamplesSaved]._y; iy<snippet.getBottomRightCorner().getY(); iy++)
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
                pty=1+followLineGetLengthXNew(snippet,createXY(in_line[lineSamplesSaved]._x,in_line[lineSamplesSaved]._y), createXY(1,0) );
                pty=pty+followLineGetLengthXNew(snippet,createXY(in_line[lineSamplesSaved]._x,in_line[lineSamplesSaved]._y), createXY(-1,0) );
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

int SOOSA::findLineImageFromTop(DataDigital* indata, PairXY* in_line, int numsamplesize, PairXY inStart,PairXY inEnd)
{
    int xt,yt,lt,lt_success,pt,iy,pty;
    int xsizebytesallocated, ysizebytesallocated;
    xsizebytesallocated = indata->xSizeBytesAllocated;
    ysizebytesallocated = indata->ySizeBytesAllocated;
    unsigned char dummy,mask;
    lt_success=0;
    DBGPRINT("  FUNC:findLineImageFromTop(startx=%d|starty=%d|endx=%d|endy=%d)\n",inStart._x+gddx,inStart._y+gddy,inEnd._x+gddx,inEnd._y+gddy);
    for(lt=0;lt<numsamplesize;lt++){//lineSamples
        in_line[lt_success]._x = roundOffSignRobust((double)(inEnd._x-inStart._x)*lt/(numsamplesize))+inStart._x;
        in_line[lt_success]._y = roundOffSignRobust((double)(inEnd._y-inStart._y)*lt/(numsamplesize))+inStart._y;
        xt = in_line[lt_success]._x/8;
        mask=0x80>>(in_line[lt_success]._x%8);
        pt = 0;
        DBGPRINT("  FUNCLOOP:findLineImageFromTop[lt=%d|x=%d|y=%d]\n",lt,in_line[lt_success]._x+gddx,in_line[lt_success]._y+gddy);
        for(iy=in_line[lt_success]._y; iy<ysizebytesallocated; iy++){//linebyteloop
            yt=(iy*xsizebytesallocated);
            dummy = indata->buf[yt+xt];
            LOPPRINT("  FUNCLOOPXXX:findLineImageFromTop[x=%d,y=%d|pt=%d|dummy=%d|mask=%d]->bit=%d\n",in_line[lt_success]._x+gddx,iy+gddy,pt,dummy,mask,(dummy&mask)==0x00);
            if(pt>=PIXELSPERPENLINE){break;}
            if((dummy&mask)==0x00){//black
                    pt=pt+1;
            }else if(pt>PIXELSDIRTBLACKDOT){
                in_line[lt_success]._y = roundOffSignRobust( iy-1-pt+(((double)pt)/2) );//minus-1 to get last white
                pty=1+followLineGetLengthX(indata,createXY(in_line[lt_success]._x,in_line[lt_success]._y), createXY(1,0) );
                pty=pty+followLineGetLengthX(indata,createXY(in_line[lt_success]._x,in_line[lt_success]._y), createXY(-1,0) );
                if(pty>=PIXELSPERPENLINE){
                    LOPPRINT("  FUNCLOOPXXX:findLineImageFromTop Successful->[x=%d|y=%d]\n",in_line[lt_success]._x+gddx,in_line[lt_success]._y+gddy);
                    lt_success++;
                    break;
                }else{
                    pt=0;
                }
            }else{
                pt=0;//if dirt encountered clear once white again
            }

        }
    }
#ifdef  DBGFLAG
    for(lt=0;lt<lt_success;lt++){//lineSamples
        DBGPRINT("  FUNCOUT:findLineImageFromTop[%d]->[x=%d|y=%d]\n",lt,in_line[lt]._x+gddx,in_line[lt]._y+gddy);
    }
#endif
    return lt_success;
}
int SOOSA::findLineImageFromBottomNew(AprgBitmapSnippet const& snippet, PairXY* in_line, int numsamplesize, PairXY inStart,PairXY inEnd)
{
    int lineSamples,lineSamplesSaved,pt,iy,pty;
    unsigned char dummy,mask;
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
                pty=1+followLineGetLengthXNew(snippet, createXY(in_line[lineSamplesSaved]._x,in_line[lineSamplesSaved]._y), createXY(1,0) );
                pty=pty+followLineGetLengthXNew(snippet, createXY(in_line[lineSamplesSaved]._x,in_line[lineSamplesSaved]._y), createXY(-1,0) );
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

int SOOSA::findLineImageFromBottom(DataDigital* indata, PairXY* in_line, int numsamplesize, PairXY inStart,PairXY inEnd)
{
    int xt,yt,lt,lt_success,pt,iy,pty;
    int xsizebytesallocated, ysizebytesallocated;
    xsizebytesallocated = indata->xSizeBytesAllocated;
    ysizebytesallocated = indata->ySizeBytesAllocated;
    unsigned char dummy,mask;
    lt_success=0;
    DBGPRINT("  FUNC:findLineImageFromBottom(startx=%d|starty=%d|endx=%d|endy=%d)\n",inStart._x+gddx,inStart._y+gddy,inEnd._x+gddx,inEnd._y+gddy);
    for(lt=0;lt<numsamplesize;lt++){//lineSamples
        in_line[lt_success]._x = roundOffSignRobust((double)(inEnd._x-inStart._x)*lt/(numsamplesize))+inStart._x;
        in_line[lt_success]._y = roundOffSignRobust((double)(inEnd._y-inStart._y)*lt/(numsamplesize))+inStart._y;
        xt = in_line[lt_success]._x/8;
        mask=0x80>>(in_line[lt_success]._x%8);
        pt = 0;
        LOPPRINT("  FUNCLOOP:findLineImageFromBottom[lt=%d|x=%d|y=%d]\n",lt,in_line[lt_success]._x+gddx,in_line[lt_success]._y+gddy);
        for(iy=in_line[lt_success]._y; iy>=0; iy--){//linebyteloop
            yt=(iy*xsizebytesallocated);
            dummy = indata->buf[yt+xt];
            LOPPRINT("  FUNCLOOPXXX:findLineImageFromBottom[x=%d,y=%d|pt=%d|dummy=%d|mask=%d]->bit=%d\n",in_line[lt_success]._x+gddx,iy+gddy,pt,dummy,mask,(dummy&mask)==0x00);
            if(pt>=PIXELSPERPENLINE){break;}
            if((dummy&mask)==0x00){//black
                pt=pt+1;
            }else if(pt>PIXELSDIRTBLACKDOT){
                in_line[lt_success]._y = roundOffSignRobust( iy+(((double)pt)/2) );//minus-1 to get last white
                pty=1+followLineGetLengthX(indata,createXY(in_line[lt_success]._x,in_line[lt_success]._y), createXY(1,0) );
                pty=pty+followLineGetLengthX(indata,createXY(in_line[lt_success]._x,in_line[lt_success]._y), createXY(-1,0) );
                if(pty>=PIXELSPERPENLINE){
                    LOPPRINT("  FUNCLOOPXXX:findLineImageFromBottom Successful->[x=%d|y=%d]\n",in_line[lt_success]._x+gddx,in_line[lt_success]._y+gddy);
                    lt_success++;
                    break;
                }else{
                    pt=0;
                }
            }else {
                pt=0;//if dirt encountered clear once white again
            }

        }
    }
#ifdef  DBGFLAG
    for(lt=0;lt<lt_success;lt++){//lineSamples
        DBGPRINT("  FUNCOUT:findLineImageFromBottom[%d]->[x=%d|y=%d]\n",lt,in_line[lt]._x+gddx,in_line[lt]._y+gddy);
    }
#endif
    return lt_success;
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

int SOOSA::getBarWidthCorrectPoint(DataDigital* indata, double invslope, PairXY* io_point, int correctPoint)
{
    int tx,ty,width=0,whiteWidth,tvalue;
    PairXY tpoint,point,blackPoint,minx,maxx;
    point=*io_point;
    tpoint=point;minx=tpoint;maxx=tpoint;
    tvalue = getValue(indata,point._x,point._y);
    blackPoint = point;
    if(tvalue==0){
        //Find the first black
        for(tx=1;tx<PIXELSPERPENLINE;tx++){
            ty=roundOffSignRobust(-1*invslope*(tx));
            tpoint._x=point._x+tx; tpoint._y=point._y+ty;
            tvalue = getValue(indata,tpoint._x,tpoint._y);
            if(tvalue==1){ blackPoint._x=tpoint._x; blackPoint._y=tpoint._y; width=1;break; }
            LOPPRINT("  FUNCLOOP:getBarWidthCorrectPoint FindFirstBlack [tpointx=%d|tpointy=%d]->(tvalue=%X)\n",tpoint._x+gddx,tpoint._y+gddy,tvalue);
            tpoint._x=point._x-tx; tpoint._y=point._y-ty;
            tvalue = getValue(indata,tpoint._x,tpoint._y);
            LOPPRINT("  FUNCLOOP:getBarWidthCorrectPoint FindFirstBlack [tpointx=%d|tpointy=%d]->(tvalue=%X)\n",tpoint._x+gddx,tpoint._y+gddy,tvalue);
            if(tvalue==1){ blackPoint._x=tpoint._x; blackPoint._y=tpoint._y; width=1;break; }
        }
    }else{
        width=1;
    }
    whiteWidth=0;
    for(tx=1;tx<PIXELSPERPENLINE;tx++){
        ty=roundOffSignRobust(-1*invslope*(tx));
        tpoint._x=blackPoint._x+tx; tpoint._y=blackPoint._y+ty;
        tvalue = getValue(indata,tpoint._x,tpoint._y);
        LOPPRINT("  FUNCLOOP:getBarWidthCorrectPoint [tpointx=%d|tpointy=%d]->(tvalue=%X)->(width=%d)\n",tpoint._x+gddx,tpoint._y+gddy,tvalue,width);
        if(tvalue==1){width=width+whiteWidth+1; whiteWidth=0;}
        else{ if(whiteWidth>=PIXELSDIRTWHITEDOT){break;} whiteWidth++;}
    }
    maxx._x=blackPoint._x+tx; maxx._y=blackPoint._y+ty;
    whiteWidth=0;
    for(tx=1;tx<PIXELSPERPENLINE;tx++){
        ty=roundOffSignRobust(-1*invslope*(tx));
        tpoint._x=blackPoint._x-tx; tpoint._y=blackPoint._y-ty;
        tvalue = getValue(indata,tpoint._x,tpoint._y);
        LOPPRINT("  FUNCLOOP:getBarWidthCorrectPoint [tpointx=%d|tpointy=%d]->(tvalue=%X)->(width=%d)\n",tpoint._x+gddx,tpoint._y+gddy,tvalue,width);
        if(tvalue==1){width=width+whiteWidth+1; whiteWidth=0;}
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

int SOOSA::getBarWidthCorrectPointNew(AprgBitmapSnippet const& snippet, double invslope, PairXY* io_point, int correctPoint)
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
            if(snippet.isBlackAt(BitmapXY(tpoint._x+gddx,tpoint._y+gddy))){ blackPoint._x=tpoint._x; blackPoint._y=tpoint._y; width=1;break; }
            LOPPRINT("  FUNCLOOP:getBarWidthCorrectPoint FindFirstBlack [tpointx=%d|tpointy=%d]->(tvalue=%X)\n",tpoint._x+gddx,tpoint._y+gddy,tvalue);
            tpoint._x=point._x-tx; tpoint._y=point._y-ty;
            LOPPRINT("  FUNCLOOP:getBarWidthCorrectPoint FindFirstBlack [tpointx=%d|tpointy=%d]->(tvalue=%X)\n",tpoint._x+gddx,tpoint._y+gddy,tvalue);
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
        if(snippet.isBlackAt(BitmapXY(tpoint._x+gddx,tpoint._y+gddy))){width=width+whiteWidth+1; whiteWidth=0;}
        else{ if(whiteWidth>=PIXELSDIRTWHITEDOT){break;} whiteWidth++;}
    }
    maxx._x=blackPoint._x+tx; maxx._y=blackPoint._y+ty;
    whiteWidth=0;
    for(tx=1;tx<PIXELSPERPENLINE;tx++){
        ty=roundOffSignRobust(-1*invslope*(tx));
        tpoint._x=blackPoint._x-tx; tpoint._y=blackPoint._y-ty;
        LOPPRINT("  FUNCLOOP:getBarWidthCorrectPoint [tpointx=%d|tpointy=%d]->(tvalue=%X)->(width=%d)\n",tpoint._x+gddx,tpoint._y+gddy,tvalue,width);
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
    int t1,t2,maxBarWidth,numOfWidths;    int* freqBarWidth=NULL;
    int* indexBarWidth=NULL;
    ChebyshevCriterion cc;
    maxBarWidth=0;    for(t1=0;t1<barWidthArrSize;t1++){
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

void SOOSA::getQuestions(DataDigital* in_data, PairXY* in_questions, int* in_numQuestion, PairXY* qFindSamples, int* qFindSamplesType, int* barWidth, int numQFindSamples, LineSlopeIntercept tslopeintercept, ChebyshevCriterion ccLine, ChebyshevCriterion ccBar)
{
    int t1,t2,numQuestion=0,type,prevtype,twidth,numImptCoor,numBarHeightArr,saved;
    double tdouble,tempBarHeight;    int* barHeightArr;
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
                twidth = getBarWidthCorrectPoint(in_data, tslopeintercept.slope, &tmppair, 0);
                DBGPRINT("  FUNC:getQuestions-NoClassToNoClass[(%d,%d),(%d,%d)]->temppair(%d,%d)|twidth:%d\n",
                bgnpair._x+gddx,bgnpair._y+gddy,endpair._x+gddx,endpair._y+gddy,tmppair._x+gddx,tmppair._y+gddy,twidth);
                if(twidth<=PIXELSDIRTBLACKDOT){//assume line                }else if(getKFromChebyshev(ccLine,twidth)<CHEBYCHEVKVALUEWIDTH){
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
                twidth = getBarWidthCorrectPoint(in_data, tslopeintercept.slope, &tmppair, correctPosition);
                DBGPRINT("  FUNC:getQuestions-LineToBar[(%d,%d),(%d,%d)]->temppair(%d,%d)|twidth:%d\n",
                bgnpair._x+gddx,bgnpair._y+gddy,endpair._x+gddx,endpair._y+gddy,tmppair._x+gddx,tmppair._y+gddy,twidth);
                if(twidth<=PIXELSDIRTBLACKDOT){//assume line                    bgnpair2 = tmppair;
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
                twidth = getBarWidthCorrectPoint(in_data, tslopeintercept.slope, &tmppair, correctPosition);
                DBGPRINT("  FUNC:getQuestions-BarToLine[(%d,%d),(%d,%d)]->temppair(%d,%d)|twidth:%d\n",
                bgnpair._x+gddx,bgnpair._y+gddy,endpair._x+gddx,endpair._y+gddy,tmppair._x+gddx,tmppair._y+gddy,twidth);
                if(twidth<=PIXELSDIRTBLACKDOT){//assume line                    endpair2 = tmppair;
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

void SOOSA::getQuestionsNew(AprgBitmapSnippet const& snippet, PairXY* in_questions, int* in_numQuestion, PairXY* qFindSamples, int* qFindSamplesType, int* barWidth, int numQFindSamples, LineSlopeIntercept tslopeintercept, ChebyshevCriterion ccLine, ChebyshevCriterion ccBar)
{
    int t1,t2,numQuestion=0,type,prevtype,twidth,numImptCoor,numBarHeightArr,saved;
    double tdouble,tempBarHeight;    int* barHeightArr;
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
                twidth = getBarWidthCorrectPointNew(snippet, tslopeintercept.slope, &tmppair, 0);
                DBGPRINT("  FUNC:getQuestions-NoClassToNoClass[(%d,%d),(%d,%d)]->temppair(%d,%d)|twidth:%d\n",
                bgnpair._x+gddx,bgnpair._y+gddy,endpair._x+gddx,endpair._y+gddy,tmppair._x+gddx,tmppair._y+gddy,twidth);
                if(twidth<=PIXELSDIRTBLACKDOT){//assume line                }else if(getKFromChebyshev(ccLine,twidth)<CHEBYCHEVKVALUEWIDTH){
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
                twidth = getBarWidthCorrectPointNew(snippet, tslopeintercept.slope, &tmppair, correctPosition);
                DBGPRINT("  FUNC:getQuestions-LineToBar[(%d,%d),(%d,%d)]->temppair(%d,%d)|twidth:%d\n",
                bgnpair._x+gddx,bgnpair._y+gddy,endpair._x+gddx,endpair._y+gddy,tmppair._x+gddx,tmppair._y+gddy,twidth);
                if(twidth<=PIXELSDIRTBLACKDOT){//assume line                    bgnpair2 = tmppair;
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
                twidth = getBarWidthCorrectPointNew(snippet, tslopeintercept.slope, &tmppair, correctPosition);
                DBGPRINT("  FUNC:getQuestions-BarToLine[(%d,%d),(%d,%d)]->temppair(%d,%d)|twidth:%d\n",
                bgnpair._x+gddx,bgnpair._y+gddy,endpair._x+gddx,endpair._y+gddy,tmppair._x+gddx,tmppair._y+gddy,twidth);
                if(twidth<=PIXELSDIRTBLACKDOT){//assume line                    endpair2 = tmppair;
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

int SOOSA::getQuestionsFromLineNew(AprgBitmapSnippet const& snippet, PairXY* out_questions, int numExpectedQuestions, double* tdoublearr, LineSlopeIntercept tslopeintercept, PairXY tcornerup, PairXY tcornerdown, int barheightsamplepixels)
{
    ChebyshevCriterion ccLine,ccBar,ccBarHeight;
    PairXY* qFindSamples=NULL;    int* barWidth=NULL;
    int* qFindSamplesType=NULL;
    int numQFindSamples, numQuestionsCoor;
    int t1=0,fail=0;
    double temp;
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
        for(t1=0;t1<numQFindSamples;t1++){barWidth[t1] = getBarWidthCorrectPointNew(snippet, tslopeintercept.slope, &(qFindSamples[t1]),1);}
        if(barWidthGetCriterion(barWidth, numQFindSamples, &ccLine, &ccBar)==1)
        {
            cout<<"ERROR: Error in allocating IndexBarWidth and FreqBarWidth array."<<endl;
            fail=1;
            break;
        }
        getQuestionsNew(snippet, out_questions, &numQuestionsCoor, qFindSamples, qFindSamplesType, barWidth, numQFindSamples, tslopeintercept, ccLine, ccBar);
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

int SOOSA::getQuestionsFromLine(DataDigital* in_dd, PairXY* out_questions, int numExpectedQuestions, double* tdoublearr, LineSlopeIntercept tslopeintercept, PairXY tcornerup, PairXY tcornerdown, int barheightsamplepixels)
{
    ChebyshevCriterion ccLine,ccBar,ccBarHeight;    PairXY* qFindSamples=NULL;
    int* barWidth=NULL;
    int* qFindSamplesType=NULL;
    int numQFindSamples, numQuestionsCoor;
    int t1=0,fail=0;
    double temp;
    do{
        numQFindSamples = rasterRound(((double)tcornerdown._y-tcornerup._y)/barheightsamplepixels)+1;
        if(numQFindSamples<numExpectedQuestions)        {
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
        for(t1=0;t1<numQFindSamples;t1++){barWidth[t1] = getBarWidthCorrectPoint(in_dd, tslopeintercept.slope, &(qFindSamples[t1]),1);}
        if(barWidthGetCriterion(barWidth, numQFindSamples, &ccLine, &ccBar)==1)
        {
            cout<<"ERROR: Error in allocating IndexBarWidth and FreqBarWidth array."<<endl;
            fail=1;
            break;
        }
        getQuestions(in_dd, out_questions, &numQuestionsCoor, qFindSamples, qFindSamplesType, barWidth, numQFindSamples, tslopeintercept, ccLine, ccBar);
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
            out_questions[t1]._x=out_questions[t1]._x+in_dd->xlow; out_questions[t1]._y=out_questions[t1]._y+in_dd->ylow;
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

void SOOSA::processOneFileOld(string const& fileName)
{
    /*cout<<"processOneFile: ["<<fileName<<"]"<<endl;
    m_status = SoosaStatus::NoError;

    BmpImage img;
    DataDigital dd;
    ChebyshevCriterion ccSlope;
    dd.buf = NULL;//IMPT
    dd.status=0;
    if(openBmpImage(&img,fileName.c_str())){
        cout<<"ERROR: Error in Reading BMP File. BMP File: ["<<fileName<<"]"<<endl;
        closeBmpImage(&img);
        m_status = SoosaStatus::BitmapError;
        return;
    }
    if(img.xSize<=PIXELSPERPENLINE || img.ySize<=PIXELSPERPENLINE){
        cout<<"ERROR: BMP File is too small ("<<PIXELSPERPENLINE<<" pixels by "<<PIXELSPERPENLINE<<" pixels only)."<<endl;
        closeBmpImage(&img);
        m_status = SoosaStatus::BitmapError;
        return;
    }

    //forfaster
    int barheightsamplepixels = 10;
    int xsearchsize = img.xSize/8;
    int ysearchsize = img.ySize/8;

    LineSlopeIntercept leftline, rightline, topline, bottomline, centerleftline, centerrightline, templine;
    PairXY uplfcorner, uprtcorner, dnlfcorner, dnrtcorner, upcenter, dncenter;
    PairXY temppoint1,temppoint2,temppoint3;
    PairXY lineSamples[SAMPLESLINETOALLOC];
    PairXY Q1[MAXQUESTIONSCOOR],Q2[MAXQUESTIONSCOOR],Q3[MAXQUESTIONSCOOR],Q4[MAXQUESTIONSCOOR];
    int numLineSamples,maxLineSamples;
    double tdoublearr[SAMPLESLINETOALLOC];
    int t1, algoTries;

    algoTries=0;
    while(algoTries<2)//Two Tries only
    {
        cleanDataDigital(&dd);
        if(algoTries==0)
        {
            maxLineSamples=SAMPLESLINE;
            //Left Line
            cout<<"INFO: Finding left line. NumOfSamples="<<maxLineSamples<<endl;
            addPointToDataDigital(&img,&dd,0,0); addPointToDataDigital(&img,&dd,xsearchsize,img.ySize-1);
            if(allocData(&dd)==1)
            {
                cout<<"ERROR: Error in allocating data for image buffer."<<endl;
                algoTries++;
                continue;
            }
            if(getDataFromBmp(&img,&dd)==1)
            {
                cout<<"ERROR: Error in transferring data to image buffer."<<endl;
                algoTries++;
                continue;
            }
            //printDataDigitalBuffer(&dd);
            numLineSamples = findLineImageFromLeft(lineSamples,maxLineSamples, dd.buf, dd.xSizeBytesAllocated,createXY(0,0),createXY(0,img.ySize-1));
            DBGPRINT("INFO: BlackSamples=%d\n",numLineSamples);
            numLineSamples = removeOutliersFromLine(lineSamples, tdoublearr, &ccSlope, numLineSamples, 0);
            DBGPRINT("INFO: SucessfulSamples=%d\n",numLineSamples);
            if(MINSAMPLESLINE>numLineSamples)
            {
                cout<<"ERROR: Error in finding the line. Number of samples is not enough (numLineSamples="<<numLineSamples<<")."<<endl;
                algoTries++;
                continue;
            }
            if(getSlope(lineSamples,tdoublearr,numLineSamples, 0)==1)
            {
                cout<<"ERROR: Invalid Slope."<<endl;
                algoTries++;
                continue;
            }
            getChebyshevDouble(&ccSlope, tdoublearr, numLineSamples-1);
            leftline.intercept=getIntercept(lineSamples,ccSlope.mean,numLineSamples,0);
            leftline.slope=ccSlope.mean;
            leftline = transposeLine(leftline,0,-1*dd.xlow,-1*dd.ylow);
            deAllocData(&dd);
            //Right Line
            cout<<"INFO: Finding right line. NumOfSamples="<<maxLineSamples<<endl;
            addPointToDataDigital(&img,&dd,img.xSize-1-xsearchsize,0); addPointToDataDigital(&img,&dd,img.xSize-1,img.ySize-1);
            if(allocData(&dd)==1)
            {
                cout<<"ERROR: Error in allocating data for image buffer."<<endl;
                algoTries++;
                continue;
            }
            if(getDataFromBmp(&img,&dd)==1)
            {
                cout<<"ERROR: Error in transferring data to image buffer.\n"<<endl;
                algoTries++;
                continue;
            }
            //printDataDigitalBuffer(&dd);
            numLineSamples = findLineImageFromRight(lineSamples,maxLineSamples, dd.buf, dd.xSizeBytesAllocated,createXY(xsearchsize-1,0),createXY(xsearchsize-1,img.ySize-1));
            DBGPRINT("INFO: BlackSamples=%d\n",numLineSamples);
            numLineSamples = removeOutliersFromLine(lineSamples, tdoublearr, &ccSlope, numLineSamples, 0);
            DBGPRINT("INFO: SucessfulSamples=%d\n",numLineSamples);
            if(MINSAMPLESLINE>numLineSamples)
            {
                cout<<"ERROR: Error in finding the line. Number of samples is not enough (numLineSamples="<<numLineSamples<<")."<<endl;
                algoTries++;
                continue;
            }
            if(getSlope(lineSamples,tdoublearr,numLineSamples, 0)==1)
            {
                cout<<"ERROR: Invalid Slope."<<endl;
                algoTries++;
                continue;
            }
            getChebyshevDouble(&ccSlope, tdoublearr, numLineSamples-1);
            rightline.intercept=getIntercept(lineSamples,ccSlope.mean,numLineSamples,0);
            rightline.slope=ccSlope.mean;
            rightline = transposeLine(rightline,0,-1*dd.xlow,-1*dd.ylow);
            deAllocData(&dd);
            maxLineSamples=SAMPLESLINETOPBOTTOM;
            //Top Line
            cout<<"INFO: Finding top line. NumOfSamples="<<maxLineSamples<<endl;
            addPointToDataDigital(&img,&dd,0,0); addPointToDataDigital(&img,&dd,img.xSize-1,ysearchsize);
            if(allocData(&dd)==1)
            {
                cout<<"ERROR: Error in allocating data for image buffer."<<endl;
                algoTries++;
                continue;
            }
            if(getDataFromBmp(&img,&dd)==1)
            {
                cout<<"ERROR: Error in transferring data to image buffer."<<endl;
                algoTries++;
                continue;
            }
            //printDataDigitalBuffer(&dd);
            numLineSamples = findLineImageFromTop(&dd, lineSamples,maxLineSamples, createXY(0,0),createXY(img.xSize-1,0));
            DBGPRINT("INFO: BlackPerpendicularSamples=%d\n",numLineSamples);
            numLineSamples = removeOutliersFromLine(lineSamples, tdoublearr, &ccSlope, numLineSamples, 1);
            DBGPRINT("INFO: SucessfulSamples=%d\n",numLineSamples);
            if(MINSAMPLESLINETOPBOTTOM>numLineSamples)
            {
                cout<<"ERROR: Error in finding the line. Number of samples is not enough (numLineSamples="<<numLineSamples<<")."<<endl;
                algoTries++;
                continue;
            }
            if(getSlope(lineSamples,tdoublearr,numLineSamples, 1)==1)
            {
                cout<<"ERROR: Invalid Slope."<<endl;
                algoTries++;
                continue;
            }
            getChebyshevDouble(&ccSlope, tdoublearr, numLineSamples-1);
            topline.intercept=getIntercept(lineSamples,ccSlope.mean,numLineSamples,1);
            topline.slope=ccSlope.mean;
            topline = transposeLine(topline,1,-1*dd.xlow,-1*dd.ylow);
            deAllocData(&dd);
            //Bottom Line
            cout<<"INFO: Finding bottom line. NumOfSamples="<<maxLineSamples<<endl;
            addPointToDataDigital(&img,&dd,0,img.ySize-1-ysearchsize); addPointToDataDigital(&img,&dd,img.xSize-1,img.ySize-1);
            if(allocData(&dd)==1)
            {
                cout<<"ERROR: Error in allocating data for image buffer."<<endl;
                algoTries++;
                continue;
            }
            if(getDataFromBmp(&img,&dd)==1)
            {
                cout<<"ERROR: Error in transferring data to image buffer."<<endl;
                algoTries++;
                continue;
            }
            //printDataDigitalBuffer(&dd);
            numLineSamples = findLineImageFromBottom(&dd, lineSamples,maxLineSamples, createXY(0,ysearchsize-1),createXY(img.xSize-1,ysearchsize-1));
            DBGPRINT("INFO: BlackPerpendicularSamples=%d\n",numLineSamples);
            numLineSamples = removeOutliersFromLine(lineSamples, tdoublearr, &ccSlope, numLineSamples, 1);
            DBGPRINT("INFO: SucessfulSamples=%d\n",numLineSamples);
            if(MINSAMPLESLINETOPBOTTOM>numLineSamples)
            {
                cout<<"ERROR: Error in finding the line. Number of samples is not enough (numLineSamples="<<numLineSamples<<")."<<endl;
                algoTries++;
                continue;
            }
            if(getSlope(lineSamples,tdoublearr,numLineSamples, 1)==1)
            {
                cout<<"ERROR: Invalid Slope."<<endl;
                algoTries++;
                continue;
            }
            getChebyshevDouble(&ccSlope, tdoublearr, numLineSamples-1);
            bottomline.intercept=getIntercept(lineSamples,ccSlope.mean,numLineSamples,1);
            bottomline.slope=ccSlope.mean;
            bottomline = transposeLine(bottomline,1,-1*dd.xlow,-1*dd.ylow);
            deAllocData(&dd);
        }
        else if(algoTries==1)
        {
            cout<<"\nINFO: Retesting with more robust parameters"<<endl;
            maxLineSamples=ROBUSTSAMPLESLINE;
            cout<<"INFO: Allocating whole Image. This may take a lot of resources and time"<<endl;
            addPointToDataDigital(&img,&dd,0,0); addPointToDataDigital(&img,&dd,img.xSize-1,img.ySize-1);
            if(allocData(&dd)==1)
            {
                cout<<"ERROR: Error in allocating data for image buffer."<<endl;
                algoTries++;
                continue;
            }
            if(getDataFromBmp(&img,&dd)==1)
            {
                cout<<"ERROR: Error in transferring data to image buffer."<<endl;
                algoTries++;
                continue;
            }
            //Left Line
            cout<<"INFO: Finding left line. NumOfSamples="<<maxLineSamples<<endl;
            numLineSamples = findLineImageFromLeft(lineSamples,maxLineSamples, dd.buf, dd.xSizeBytesAllocated,createXY(0,0),createXY(0,img.ySize-1));
            DBGPRINT("INFO: BlackSamples=%d\n",numLineSamples);
            numLineSamples = removeOutliersFromLineSmart(lineSamples, numLineSamples, ROBUSTMINSAMPLESLINE, 0);
            DBGPRINT("INFO: SucessfulSamples=%d\n",numLineSamples);
            if(ROBUSTMINSAMPLESLINE>numLineSamples)
            {
                cout<<"ERROR: Error in finding the line. Number of samples is not enough (numLineSamples="<<numLineSamples<<")."<<endl;
                algoTries++;
                continue;
            }
            if(getSlope(lineSamples,tdoublearr,numLineSamples, 0)==1)
            {
                cout<<"ERROR: Invalid Slope."<<endl;
                algoTries++;
                continue;
            }
            getChebyshevDouble(&ccSlope, tdoublearr, numLineSamples-1);
            leftline.intercept=getIntercept(lineSamples,ccSlope.mean,numLineSamples,0);
            leftline.slope=ccSlope.mean;
            //Right Line
            cout<<"INFO: Finding right line. NumOfSamples="<<maxLineSamples<<endl;
            numLineSamples = findLineImageFromRight(lineSamples,maxLineSamples, dd.buf, dd.xSizeBytesAllocated,createXY(img.xSize-1,0),createXY(img.xSize-1,img.ySize-1));
            DBGPRINT("INFO: BlackSamples=%d\n",numLineSamples);
            numLineSamples = removeOutliersFromLineSmart(lineSamples, numLineSamples, ROBUSTMINSAMPLESLINE, 0);
            DBGPRINT("INFO: SucessfulSamples=%d\n",numLineSamples);
            if(ROBUSTMINSAMPLESLINE>numLineSamples)
            {
                cout<<"ERROR: Error in finding the line. Number of samples is not enough (numLineSamples="<<numLineSamples<<")."<<endl;
                algoTries++;
                continue;
            }
            if(getSlope(lineSamples,tdoublearr,numLineSamples, 0)==1)
            {
                cout<<"ERROR: Invalid Slope."<<endl;
                algoTries++;
                continue;
            }
            getChebyshevDouble(&ccSlope, tdoublearr, numLineSamples-1);
            rightline.intercept=getIntercept(lineSamples,ccSlope.mean,numLineSamples,0);
            rightline.slope=ccSlope.mean;
            maxLineSamples=ROBUSTSAMPLESLINETOPBOTTOM;
            //Top Line
            cout<<"INFO: Finding top line. NumOfSamples="<<maxLineSamples<<endl;
            numLineSamples = findLineImageFromTop(&dd, lineSamples,maxLineSamples, createXY(0,0),createXY(img.xSize-1,0));
            DBGPRINT("INFO: BlackPerpendicularSamples=%d\n",numLineSamples);
            numLineSamples = removeOutliersFromLineSmart(lineSamples, numLineSamples, ROBUSTMINSAMPLESLINETOPBOTTOM, 1);
            DBGPRINT("INFO: SucessfulSamples=%d\n",numLineSamples);
            if(ROBUSTMINSAMPLESLINETOPBOTTOM>numLineSamples)
            {
                cout<<"ERROR: Error in finding the line. Number of samples is not enough (numLineSamples="<<numLineSamples<<")."<<endl;
                algoTries++;
                continue;
            }
            if(getSlope(lineSamples,tdoublearr,numLineSamples, 1)==1)
            {
                cout<<"ERROR: Invalid Slope."<<endl;
                algoTries++;
                continue;
            }
            getChebyshevDouble(&ccSlope, tdoublearr, numLineSamples-1);
            topline.intercept=getIntercept(lineSamples,ccSlope.mean,numLineSamples,1);
            topline.slope=ccSlope.mean;
            //Bottom Line
            cout<<"INFO: Finding bottom line. NumOfSamples="<<maxLineSamples<<endl;
            numLineSamples = findLineImageFromBottom(&dd, lineSamples,maxLineSamples, createXY(0,img.ySize-1),createXY(img.xSize-1,img.ySize-1));
            DBGPRINT("INFO: BlackPerpendicularSamples=%d\n",numLineSamples);
            numLineSamples = removeOutliersFromLineSmart(lineSamples, numLineSamples, ROBUSTMINSAMPLESLINETOPBOTTOM, 1);
            DBGPRINT("INFO: SucessfulSamples=%d\n",numLineSamples);
            if(ROBUSTMINSAMPLESLINETOPBOTTOM>numLineSamples)
            {
                cout<<"ERROR: Error in finding the line. Number of samples is not enough (numLineSamples="<<numLineSamples<<")."<<endl;
                algoTries++;
                continue;
            }
            if(getSlope(lineSamples,tdoublearr,numLineSamples, 1)==1)
            {
                cout<<"ERROR: Invalid Slope."<<endl;
                algoTries++;
                continue;
            }
            getChebyshevDouble(&ccSlope, tdoublearr, numLineSamples-1);
            bottomline.intercept=getIntercept(lineSamples,ccSlope.mean,numLineSamples,1);
            bottomline.slope=ccSlope.mean;
        }

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
        if(checkIfWithinImageBounds(uplfcorner,img.xSize-1,img.ySize-1)==1)
        {
            cout<<"ERROR: Invalid UpLeftCorner point."<<endl;
            algoTries++;
            continue;
        }
        if(checkIfWithinImageBounds(uprtcorner,img.xSize-1,img.ySize-1)==1)
        {
            cout<<"ERROR: Invalid UpRightCorner point."<<endl;
            algoTries++;
            continue;
        }
        if(checkIfWithinImageBounds(dnlfcorner,img.xSize-1,img.ySize-1)==1)
        {
            cout<<"ERROR: Invalid DownLeftCorner point."<<endl;
            algoTries++;
            continue;
        }
        if(checkIfWithinImageBounds(dnrtcorner,img.xSize-1,img.ySize-1)==1)
        {
            cout<<"ERROR: Invalid DownRightCorner point."<<endl;
            algoTries++;
            continue;
        }
        if(algoTries==0){
            barheightsamplepixels=10;
            //Q1
            addPointToDataDigital(&img,&dd,uplfcorner._x-PIXELSSEARCHSIZE,uplfcorner._y-PIXELSSEARCHSIZE);
            addPointToDataDigital(&img,&dd,uplfcorner._x+PIXELSSEARCHSIZE,uplfcorner._y+PIXELSSEARCHSIZE);
            addPointToDataDigital(&img,&dd,dnlfcorner._x-PIXELSSEARCHSIZE,dnlfcorner._y-PIXELSSEARCHSIZE);
            addPointToDataDigital(&img,&dd,dnlfcorner._x+PIXELSSEARCHSIZE,dnlfcorner._y+PIXELSSEARCHSIZE);
            if(allocData(&dd)==1)
            {
                cout<<"ERROR: Error in allocating data for image buffer."<<endl;
                algoTries++;
                continue;
            }
            if(getDataFromBmp(&img,&dd)==1)
            {
                cout<<"ERROR: Error in transferring data to image buffer."<<endl;
                algoTries++;
                continue;
            }
            temppoint1 = transposePoint(uplfcorner,dd.xlow,dd.ylow);
            temppoint2 = transposePoint(dnlfcorner,dd.xlow,dd.ylow);
            templine=transposeLine(leftline,0,dd.xlow,dd.ylow);
            if(getQuestionsFromLine(&dd,Q1,m_configuration.getNumberOfQuestionsAtColumn(1),tdoublearr,templine,temppoint1,temppoint2,barheightsamplepixels)==1)
            {
                cout<<"ERROR: Error in finding questions in left line."<<endl;
                algoTries++;
                continue;
            }
            deAllocData(&dd);
            //Q4
            addPointToDataDigital(&img,&dd,uprtcorner._x-PIXELSSEARCHSIZE,uprtcorner._y-PIXELSSEARCHSIZE);
            addPointToDataDigital(&img,&dd,uprtcorner._x+PIXELSSEARCHSIZE,uprtcorner._y+PIXELSSEARCHSIZE);
            addPointToDataDigital(&img,&dd,dnrtcorner._x-PIXELSSEARCHSIZE,dnrtcorner._y-PIXELSSEARCHSIZE);
            addPointToDataDigital(&img,&dd,dnrtcorner._x+PIXELSSEARCHSIZE,dnrtcorner._y+PIXELSSEARCHSIZE);
            if(allocData(&dd)==1)
            {
                cout<<"ERROR: Error in allocating data for image buffer."<<endl;
                algoTries++;
                continue;
            }
            if(getDataFromBmp(&img,&dd)==1)
            {
                cout<<"ERROR: Error in transferring data to image buffer."<<endl;
                algoTries++;
                continue;
            }
            temppoint1 = transposePoint(uprtcorner,dd.xlow,dd.ylow);
            temppoint2 = transposePoint(dnrtcorner,dd.xlow,dd.ylow);
            templine=transposeLine(rightline,0,dd.xlow,dd.ylow);
            if(getQuestionsFromLine(&dd,Q4,m_configuration.getNumberOfQuestionsAtColumn(2),tdoublearr,templine,temppoint1,temppoint2,barheightsamplepixels)==1)
            {
                cout<<"ERROR: Error in finding questions in right line."<<endl;
                algoTries++;
                continue;
            }
            deAllocData(&dd);
            if(m_configuration.getNumberOfColumns()==2){
                temppoint1=getMidpoint(uplfcorner,upcenter);
                temppoint2=getMidpoint(upcenter,uprtcorner);
                addPointToDataDigital(&img,&dd,temppoint1._x,temppoint1._y-PIXELSSEARCHSIZE);
                addPointToDataDigital(&img,&dd,temppoint2._x,temppoint2._y-PIXELSSEARCHSIZE);
                temppoint1=getMidpoint(dnlfcorner,dncenter);
                temppoint2=getMidpoint(dncenter,dnrtcorner);
                addPointToDataDigital(&img,&dd,temppoint1._x,temppoint1._y+PIXELSSEARCHSIZE);
                addPointToDataDigital(&img,&dd,temppoint2._x,temppoint2._y+PIXELSSEARCHSIZE);
                if(allocData(&dd)==1)
                {
                    cout<<"ERROR: Error in allocating data for image buffer."<<endl;
                    algoTries++;
                    continue;
                }
                if(getDataFromBmp(&img,&dd)==1)
                {
                    cout<<"ERROR: Error in transferring data to image buffer."<<endl;
                    algoTries++;
                    continue;
                }
                maxLineSamples=SAMPLESLINE;
                //center left line
                temppoint1 = transposePoint(upcenter,dd.xlow,dd.ylow);
                temppoint2 = transposePoint(dncenter,dd.xlow,dd.ylow);
                cout<<"INFO: Finding center left line. NumOfSamples="<<maxLineSamples<<endl;
                numLineSamples = findLineImageFromRight(lineSamples,maxLineSamples, dd.buf, dd.xSizeBytesAllocated,temppoint1,temppoint2);
                DBGPRINT("INFO: BlackSamples=%d\n",numLineSamples);
                numLineSamples = removeOutliersFromLine(lineSamples, tdoublearr, &ccSlope, numLineSamples, 0);
                DBGPRINT("INFO: SucessfulSamples=%d\n",numLineSamples);
                if(MINSAMPLESLINE>numLineSamples)
                {
                    cout<<"ERROR: Error in finding the line. Number of samples is not enough (numLineSamples="<<numLineSamples<<")."<<endl;
                    algoTries++;
                    continue;
                }
                if(getSlope(lineSamples,tdoublearr,numLineSamples, 0)==1)
                {
                    cout<<"ERROR: Invalid Slope."<<endl;
                    algoTries++;
                    continue;
                }
                getChebyshevDouble(&ccSlope, tdoublearr, numLineSamples-1);
                centerleftline.intercept=getIntercept(lineSamples,ccSlope.mean,numLineSamples,0);
                centerleftline.slope=ccSlope.mean;
                centerleftline=transposeLine(centerleftline,0,-1*dd.xlow,-1*dd.ylow);
                //Q2
                temppoint1 = findIntersection(centerleftline,topline);temppoint1 = transposePoint(temppoint1,dd.xlow,dd.ylow);
                temppoint2 = findIntersection(centerleftline,bottomline);temppoint2 = transposePoint(temppoint2,dd.xlow,dd.ylow);
                templine = transposeLine(centerleftline,0,dd.xlow,dd.ylow);
                if(getQuestionsFromLine(&dd,Q2,m_configuration.getNumberOfQuestionsAtColumn(1),tdoublearr,templine,temppoint1,temppoint2,barheightsamplepixels)==1)
                {
                    cout<<"ERROR: Error in finding questions in center left line."<<endl;
                    algoTries++;
                    continue;
                }
                //center right line
                temppoint1 = transposePoint(upcenter,dd.xlow,dd.ylow);
                temppoint2 = transposePoint(dncenter,dd.xlow,dd.ylow);
                cout<<"INFO: Finding center right line. NumOfSamples="<<maxLineSamples<<endl;
                numLineSamples = findLineImageFromLeft(lineSamples,maxLineSamples, dd.buf, dd.xSizeBytesAllocated,temppoint1,temppoint2);
                DBGPRINT("INFO: BlackSamples=%d\n",numLineSamples);
                numLineSamples = removeOutliersFromLine(lineSamples, tdoublearr, &ccSlope, numLineSamples, 0);
                DBGPRINT("INFO: SucessfulSamples=%d\n",numLineSamples);
                if(MINSAMPLESLINE>numLineSamples)
                {
                    cout<<"ERROR: Error in finding the line. Number of samples is not enough (numLineSamples="<<numLineSamples<<")."<<endl;
                    algoTries++;
                    continue;
                }
                if(getSlope(lineSamples,tdoublearr,numLineSamples, 0)==1)
                {
                    cout<<"ERROR: Invalid Slope."<<endl;
                    algoTries++;
                    continue;
                }
                getChebyshevDouble(&ccSlope, tdoublearr, numLineSamples-1);
                centerrightline.intercept=getIntercept(lineSamples,ccSlope.mean,numLineSamples,0);
                centerrightline.slope=ccSlope.mean;
                centerrightline=transposeLine(centerrightline,0,-1*dd.xlow,-1*dd.ylow);
                //Q3
                temppoint1 = findIntersection(centerrightline,topline);temppoint1 = transposePoint(temppoint1,dd.xlow,dd.ylow);
                temppoint2 = findIntersection(centerrightline,bottomline);temppoint2 = transposePoint(temppoint2,dd.xlow,dd.ylow);
                templine = transposeLine(centerrightline,0,dd.xlow,dd.ylow);
                if(getQuestionsFromLine(&dd,Q3,m_configuration.getNumberOfQuestionsAtColumn(2),tdoublearr,templine,temppoint1,temppoint2,barheightsamplepixels)==1)
                {
                    cout<<"ERROR: Error in finding questions in center right line."<<endl;
                    algoTries++;
                    continue;
                }
                deAllocData(&dd);
            }
        }else if(algoTries==1){
            barheightsamplepixels=5;
            //Q1
            if(getQuestionsFromLine(&dd,Q1,m_configuration.getNumberOfQuestionsAtColumn(1),tdoublearr,leftline,uplfcorner,dnlfcorner,barheightsamplepixels)==1)
            {
                cout<<"ERROR: Error in finding questions in left line."<<endl;
                algoTries++;
                continue;
            }
            //Q4
            if(getQuestionsFromLine(&dd,Q4,m_configuration.getNumberOfQuestionsAtColumn(2),tdoublearr,rightline,uprtcorner,dnrtcorner,barheightsamplepixels)==1)
            {
                cout<<"ERROR: Error in finding questions in right line."<<endl;
                algoTries++;
                continue;
            }
            if(m_configuration.getNumberOfColumns()==2){
                maxLineSamples=ROBUSTSAMPLESLINE;
                //center left line
                cout<<"INFO: Finding center left line. NumOfSamples="<<numLineSamples<<endl;
                numLineSamples = findLineImageFromRight(lineSamples,maxLineSamples, dd.buf, dd.xSizeBytesAllocated,upcenter,dncenter);
                DBGPRINT("INFO: BlackSamples=%d\n",numLineSamples);
                numLineSamples = removeOutliersFromLineSmart(lineSamples, numLineSamples, ROBUSTMINSAMPLESLINE, 0);
                DBGPRINT("INFO: SucessfulSamples=%d\n",numLineSamples);
                if(ROBUSTMINSAMPLESLINE>numLineSamples)
                {
                    cout<<"ERROR: Error in finding the line. Number of samples is not enough (numLineSamples="<<numLineSamples<<")."<<endl;
                    algoTries++;
                    continue;
                }
                if(getSlope(lineSamples,tdoublearr,numLineSamples, 0)==1)
                {
                    cout<<"ERROR: Invalid Slope."<<endl;
                    algoTries++;
                    continue;
                }
                getChebyshevDouble(&ccSlope, tdoublearr, numLineSamples-1);
                centerleftline.intercept=getIntercept(lineSamples,ccSlope.mean,numLineSamples,0);
                centerleftline.slope=ccSlope.mean;
                //Q2
                temppoint1 = findIntersection(centerleftline,topline);
                temppoint2 = findIntersection(centerleftline,bottomline);
                if(getQuestionsFromLine(&dd,Q2,m_configuration.getNumberOfQuestionsAtColumn(1),tdoublearr,centerleftline,temppoint1,temppoint2,barheightsamplepixels)==1)
                {
                    cout<<"ERROR: Error in finding questions in center left line."<<endl;
                    algoTries++;
                    continue;
                }
                //center right line
                cout<<"INFO: Finding center right line. NumOfSamples="<<maxLineSamples<<endl;
                numLineSamples = findLineImageFromLeft(lineSamples,maxLineSamples, dd.buf, dd.xSizeBytesAllocated,upcenter,dncenter);
                DBGPRINT("INFO: BlackSamples=%d\n",numLineSamples);
                numLineSamples = removeOutliersFromLineSmart(lineSamples, numLineSamples, ROBUSTMINSAMPLESLINE, 0);
                DBGPRINT("INFO: SucessfulSamples=%d\n",numLineSamples);
                if(ROBUSTMINSAMPLESLINE>numLineSamples)
                {
                    cout<<"ERROR: Error in finding the line. Number of samples is not enough (numLineSamples="<<numLineSamples<<")."<<endl;
                    algoTries++;
                    continue;
                }
                if(getSlope(lineSamples,tdoublearr,numLineSamples, 0)==1)
                {
                    cout<<"ERROR: Invalid Slope."<<endl;
                    algoTries++;
                    continue;
                }
                getChebyshevDouble(&ccSlope, tdoublearr, numLineSamples-1);
                centerrightline.intercept=getIntercept(lineSamples,ccSlope.mean,numLineSamples,0);
                centerrightline.slope=ccSlope.mean;
                //Q3
                temppoint1 = findIntersection(centerrightline,topline);
                temppoint2 = findIntersection(centerrightline,bottomline);
                if(getQuestionsFromLine(&dd,Q3,m_configuration.getNumberOfQuestionsAtColumn(2),tdoublearr,centerrightline,temppoint1,temppoint2,barheightsamplepixels)==1)
                {
                    cout<<"ERROR: Error in finding questions in center right line."<<endl;
                    algoTries++;
                    continue;
                }
            }
        }
        if(algoTries==0){
            if(m_configuration.getNumberOfColumns()==2){
                //COL1
                addPointToDataDigital(&img,&dd,uplfcorner._x,uplfcorner._y);
                addPointToDataDigital(&img,&dd,dnlfcorner._x,dnlfcorner._y);
                addPointToDataDigital(&img,&dd,upcenter._x,upcenter._y);
                addPointToDataDigital(&img,&dd,dncenter._x,dncenter._y);
                if(allocData(&dd)==1)
                {
                    cout<<"ERROR: Error in allocating data for image buffer."<<endl;
                    algoTries++;
                    continue;
                }
                if(getDataFromBmp(&img,&dd)==1)
                {
                    cout<<"ERROR: Error in transferring data for image buffer."<<endl;
                    algoTries++;
                    continue;
                }
                if(processOneColumn(&dd, Q1, Q2, m_configuration.getNumberOfQuestionsAtColumn(1), 1))
                {
                    cout<<"ERROR: Error in finding number circles."<<endl;
                    algoTries++;
                    continue;
                }
                deAllocData(&dd);
                //COL2
                addPointToDataDigital(&img,&dd,upcenter._x,upcenter._y);
                addPointToDataDigital(&img,&dd,dncenter._x,dncenter._y);
                addPointToDataDigital(&img,&dd,uprtcorner._x,uprtcorner._y);
                addPointToDataDigital(&img,&dd,dnrtcorner._x,dnrtcorner._y);
                if(allocData(&dd)==1)
                {
                    cout<<"ERROR: Error in allocating data for image buffer."<<endl;
                    algoTries++;
                    continue;
                }
                if(getDataFromBmp(&img,&dd)==1)
                {
                    cout<<"ERROR: Error in transferring data for image buffer."<<endl;
                    algoTries++;
                    continue;
                }
                if(processOneColumn(&dd, Q3, Q4, m_configuration.getNumberOfQuestionsAtColumn(2), 2))
                {
                    cout<<"ERROR: Error in finding number circles."<<endl;
                    algoTries++;
                    continue;
                }
                deAllocData(&dd);
            }else if(m_configuration.getNumberOfColumns()==1){
                //SINGLE COLUMN
                addPointToDataDigital(&img,&dd,uplfcorner._x,uplfcorner._y);
                addPointToDataDigital(&img,&dd,dnlfcorner._x,dnlfcorner._y);
                addPointToDataDigital(&img,&dd,uprtcorner._x,uprtcorner._y);
                addPointToDataDigital(&img,&dd,dnrtcorner._x,dnrtcorner._y);
                if(allocData(&dd)==1)
                {
                    cout<<"ERROR: Error in allocating data for image buffer."<<endl;
                    algoTries++;
                    continue;
                }
                if(getDataFromBmp(&img,&dd)==1)
                {
                    cout<<"ERROR: Error in transferring data for image buffer."<<endl;
                    algoTries++;
                    continue;
                }
                printDataDigitalBuffer(&dd);
                if(processOneColumn(&dd, Q1, Q4, m_configuration.getNumberOfQuestionsAtColumn(1), 1))
                {
                    cout<<"ERROR: Error in finding number circles."<<endl;
                    algoTries++;
                    continue;
                }
                deAllocData(&dd);
            }
            algoTries=3;
        }else if(algoTries==1){
            if(m_configuration.getNumberOfColumns()==2){
                //COL1
                if(processOneColumn(&dd, Q1, Q2, m_configuration.getNumberOfQuestionsAtColumn(1), 1))
                {
                    cout<<"ERROR: Error in finding number circles."<<endl;
                    algoTries++;
                    continue;
                }
                //COL2
                if(processOneColumn(&dd, Q3, Q4, m_configuration.getNumberOfQuestionsAtColumn(2), 2))
                {
                    cout<<"ERROR: Error in finding number circles."<<endl;
                    algoTries++;
                    continue;
                }
            }else if(m_configuration.getNumberOfColumns()==1){
                //SINGLE COLUMN
                if(processOneColumn(&dd, Q1, Q4, m_configuration.getNumberOfQuestionsAtColumn(1), 1))
                {
                    cout<<"ERROR: Error in finding number circles."<<endl;
                    algoTries++;
                    continue;
                }
            }
            algoTries=3;
            deAllocData(&dd);
        }
        algoTries++;
    }//two tries
    cout<<"DONE!"<<endl;
    if(algoTries==2)
    {
        m_status = SoosaStatus::AlgorithmError;
        return;
    }
    m_numberOfRespondents++;
    cleanDataDigital(&dd);
    closeBmpImage(&img);
*/
}

void SOOSA::processOneFile(string const& filePath)
{
    cout<<"processOneFile: ["<<filePath<<"]"<<endl;
    m_status = SoosaStatus::NoError;

    //newway

    AprgBitmap bitmap(filePath);

    BmpImage img;
    DataDigital dd;
    ChebyshevCriterion ccSlope;
    dd.buf = NULL;//IMPT
    dd.status=0;
    if(openBmpImage(&img,filePath.c_str())){
        cout<<"ERROR: Error in Reading BMP File. BMP File: ["<<filePath<<"]"<<endl;
        closeBmpImage(&img);
        m_status = SoosaStatus::BitmapError;
        return;
    }
    if(img.xSize<=PIXELSPERPENLINE || img.ySize<=PIXELSPERPENLINE){
        cout<<"ERROR: BMP File is too small ("<<PIXELSPERPENLINE<<" pixels by "<<PIXELSPERPENLINE<<" pixels only)."<<endl;
        closeBmpImage(&img);
        m_status = SoosaStatus::BitmapError;
        return;
    }

    //forfaster
    int barheightsamplepixels = 10;
    int xsearchsize = img.xSize/8;
    int ysearchsize = img.ySize/8;

    LineSlopeIntercept leftline, rightline, topline, bottomline, centerleftline, centerrightline, templine;
    PairXY uplfcorner, uprtcorner, dnlfcorner, dnrtcorner, upcenter, dncenter;
    PairXY temppoint1,temppoint2,temppoint3;
    PairXY lineSamples[SAMPLESLINETOALLOC];
    PairXY Q1[MAXQUESTIONSCOOR],Q2[MAXQUESTIONSCOOR],Q3[MAXQUESTIONSCOOR],Q4[MAXQUESTIONSCOOR];
    int numLineSamples,maxLineSamples;
    double tdoublearr[SAMPLESLINETOALLOC];
    int t1, isFinishedSuccessfully(false);

    while(!isFinishedSuccessfully)//Two Tries only
    {
        cleanDataDigital(&dd);
        maxLineSamples=ROBUSTSAMPLESLINE;
        //Left Line
        cout<<"INFO: Finding left line. NumOfSamples="<<maxLineSamples<<endl;
        gddx=0;
        gddy=0;
        AprgBitmapSnippet snippet(bitmap.getSnippetReadFromFile(BitmapXY(gddx, gddy), BitmapXY(xsearchsize,img.ySize-1)));
        numLineSamples = findLineImageFromLeftNew(snippet, lineSamples, maxLineSamples, createXY(0,0), createXY(0,img.ySize-1));
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
        leftline.intercept=getIntercept(lineSamples,ccSlope.mean,numLineSamples,0);
        leftline.slope=ccSlope.mean;
        leftline = transposeLine(leftline,0,-1*gddx,-1*gddy);
        //Right Line
        cout<<"INFO: Finding right line. NumOfSamples="<<maxLineSamples<<endl;
        snippet.clear();
        gddx=img.xSize-1-xsearchsize;
        gddy=0;
        snippet = bitmap.getSnippetReadFromFile(BitmapXY(gddx, gddy), BitmapXY(img.xSize-1, img.ySize-1));
        numLineSamples = findLineImageFromRightNew(snippet, lineSamples, maxLineSamples, createXY(xsearchsize-1,0),createXY(xsearchsize-1,img.ySize-1));
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
        rightline.intercept=getIntercept(lineSamples,ccSlope.mean,numLineSamples,0);
        rightline.slope=ccSlope.mean;
        rightline = transposeLine(rightline,0,-1*gddx,-1*gddy);
        maxLineSamples=ROBUSTSAMPLESLINETOPBOTTOM;
        //Top Line
        cout<<"INFO: Finding top line. NumOfSamples="<<maxLineSamples<<endl;
        snippet.clear();
        gddx=0;
        gddy=0;
        snippet = bitmap.getSnippetReadFromFile(BitmapXY(gddx, gddy), BitmapXY(img.xSize-1,ysearchsize));
        numLineSamples = findLineImageFromTopNew(snippet, lineSamples, maxLineSamples, createXY(0,0), createXY(img.xSize-1,0));
        DBGPRINT("INFO: BlackPerpendicularSamples=%d\n",numLineSamples);
        numLineSamples = removeOutliersFromLine(lineSamples, tdoublearr, &ccSlope, numLineSamples, 1);
        DBGPRINT("INFO: SucessfulSamples=%d\n",numLineSamples);
        if(ROBUSTMINSAMPLESLINETOPBOTTOM>numLineSamples)
        {
            cout<<"ERROR: Error in finding the line. Number of samples is not enough (numLineSamples="<<numLineSamples<<")."<<endl;
            break;
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
        gddy=img.ySize-1-ysearchsize;
        snippet = bitmap.getSnippetReadFromFile(BitmapXY(gddx, gddy), BitmapXY(img.xSize-1,img.ySize-1));

        numLineSamples = findLineImageFromBottomNew(snippet, lineSamples, maxLineSamples, createXY(0,ysearchsize-1),createXY(img.xSize-1,ysearchsize-1));
        DBGPRINT("INFO: BlackPerpendicularSamples=%d\n",numLineSamples);
        numLineSamples = removeOutliersFromLine(lineSamples, tdoublearr, &ccSlope, numLineSamples, 1);
        DBGPRINT("INFO: SucessfulSamples=%d\n",numLineSamples);
        if(ROBUSTMINSAMPLESLINETOPBOTTOM>numLineSamples)
        {
            cout<<"ERROR: Error in finding the line. Number of samples is not enough (numLineSamples="<<numLineSamples<<")."<<endl;
            break;
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
        if(checkIfWithinImageBounds(uplfcorner,img.xSize-1,img.ySize-1)==1)
        {
            cout<<"ERROR: Invalid UpLeftCorner point."<<endl;
            break;
        }
        if(checkIfWithinImageBounds(uprtcorner,img.xSize-1,img.ySize-1)==1)
        {
            cout<<"ERROR: Invalid UpRightCorner point."<<endl;
            break;
        }
        if(checkIfWithinImageBounds(dnlfcorner,img.xSize-1,img.ySize-1)==1)
        {
            cout<<"ERROR: Invalid DownLeftCorner point."<<endl;
            break;
        }
        if(checkIfWithinImageBounds(dnrtcorner,img.xSize-1,img.ySize-1)==1)
        {
            cout<<"ERROR: Invalid DownRightCorner point."<<endl;
            break;
        }
        barheightsamplepixels=10;
        snippet.clear();
        BitmapSignedXY topLeftCorner(uplfcorner._x-PIXELSSEARCHSIZE,uplfcorner._y-PIXELSSEARCHSIZE);
        topLeftCorner.saveAsTopLeftCorner(BitmapSignedXY(uplfcorner._x+PIXELSSEARCHSIZE,uplfcorner._y+PIXELSSEARCHSIZE));
        topLeftCorner.saveAsTopLeftCorner(BitmapSignedXY(dnlfcorner._x-PIXELSSEARCHSIZE,dnlfcorner._y-PIXELSSEARCHSIZE));
        topLeftCorner.saveAsTopLeftCorner(BitmapSignedXY(dnlfcorner._x+PIXELSSEARCHSIZE,dnlfcorner._y+PIXELSSEARCHSIZE));
        BitmapSignedXY bottomRightCorner(uplfcorner._x-PIXELSSEARCHSIZE,uplfcorner._y-PIXELSSEARCHSIZE);
        bottomRightCorner.saveAsBottomRightCorner(BitmapSignedXY(uplfcorner._x+PIXELSSEARCHSIZE,uplfcorner._y+PIXELSSEARCHSIZE));
        bottomRightCorner.saveAsBottomRightCorner(BitmapSignedXY(dnlfcorner._x-PIXELSSEARCHSIZE,dnlfcorner._y-PIXELSSEARCHSIZE));
        bottomRightCorner.saveAsBottomRightCorner(BitmapSignedXY(dnlfcorner._x+PIXELSSEARCHSIZE,dnlfcorner._y+PIXELSSEARCHSIZE));
        topLeftCorner.setNegativeToZero();

        gddx=topLeftCorner.getX();
        gddy=topLeftCorner.getY();
        snippet = bitmap.getSnippetReadFromFile(BitmapXY(topLeftCorner.getX(), topLeftCorner.getY()), BitmapXY(bottomRightCorner.getX(), bottomRightCorner.getY()));
        //Q1
        temppoint1 = transposePoint(uplfcorner,dd.xlow,dd.ylow);
        temppoint2 = transposePoint(dnlfcorner,dd.xlow,dd.ylow);
        templine=transposeLine(leftline,0,dd.xlow,dd.ylow);
        if(getQuestionsFromLineNew(snippet, Q1,m_configuration.getNumberOfQuestionsAtColumn(1),tdoublearr,templine,temppoint1,temppoint2,barheightsamplepixels)==1)
        {
            cout<<"ERROR: Error in finding questions in left line."<<endl;
            break;
        }
        //Q4
        addPointToDataDigital(&img,&dd,uprtcorner._x-PIXELSSEARCHSIZE,uprtcorner._y-PIXELSSEARCHSIZE);
        addPointToDataDigital(&img,&dd,uprtcorner._x+PIXELSSEARCHSIZE,uprtcorner._y+PIXELSSEARCHSIZE);        addPointToDataDigital(&img,&dd,dnrtcorner._x-PIXELSSEARCHSIZE,dnrtcorner._y-PIXELSSEARCHSIZE);
        addPointToDataDigital(&img,&dd,dnrtcorner._x+PIXELSSEARCHSIZE,dnrtcorner._y+PIXELSSEARCHSIZE);
        if(allocData(&dd)==1)
        {            cout<<"ERROR: Error in allocating data for image buffer."<<endl;
            break;
        }
        if(getDataFromBmp(&img,&dd)==1)
        {
            cout<<"ERROR: Error in transferring data to image buffer."<<endl;
            break;
        }
        temppoint1 = transposePoint(uprtcorner,dd.xlow,dd.ylow);
        temppoint2 = transposePoint(dnrtcorner,dd.xlow,dd.ylow);
        templine=transposeLine(rightline,0,dd.xlow,dd.ylow);
        if(getQuestionsFromLine(&dd,Q4,m_configuration.getNumberOfQuestionsAtColumn(2),tdoublearr,templine,temppoint1,temppoint2,barheightsamplepixels)==1)
        {
            cout<<"ERROR: Error in finding questions in right line."<<endl;
            break;
        }
        deAllocData(&dd);
        if(m_configuration.getNumberOfColumns()==2)
        {
            temppoint1=getMidpoint(uplfcorner,upcenter);
            temppoint2=getMidpoint(upcenter,uprtcorner);
            addPointToDataDigital(&img,&dd,temppoint1._x,temppoint1._y-PIXELSSEARCHSIZE);
            addPointToDataDigital(&img,&dd,temppoint2._x,temppoint2._y-PIXELSSEARCHSIZE);
            temppoint1=getMidpoint(dnlfcorner,dncenter);
            temppoint2=getMidpoint(dncenter,dnrtcorner);
            addPointToDataDigital(&img,&dd,temppoint1._x,temppoint1._y+PIXELSSEARCHSIZE);
            addPointToDataDigital(&img,&dd,temppoint2._x,temppoint2._y+PIXELSSEARCHSIZE);
            if(allocData(&dd)==1)
            {
                cout<<"ERROR: Error in allocating data for image buffer."<<endl;
                break;
            }
            if(getDataFromBmp(&img,&dd)==1)
            {
                cout<<"ERROR: Error in transferring data to image buffer."<<endl;
                break;
            }
            maxLineSamples=ROBUSTSAMPLESLINE;
            //center left line
            temppoint1 = transposePoint(upcenter,dd.xlow,dd.ylow);
            temppoint2 = transposePoint(dncenter,dd.xlow,dd.ylow);
            cout<<"INFO: Finding center left line. NumOfSamples="<<maxLineSamples<<endl;
            numLineSamples = findLineImageFromRight(lineSamples,maxLineSamples, dd.buf, dd.xSizeBytesAllocated,temppoint1,temppoint2);
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
            centerleftline=transposeLine(centerleftline,0,-1*dd.xlow,-1*dd.ylow);
            //Q2
            temppoint1 = findIntersection(centerleftline,topline);temppoint1 = transposePoint(temppoint1,dd.xlow,dd.ylow);
            temppoint2 = findIntersection(centerleftline,bottomline);temppoint2 = transposePoint(temppoint2,dd.xlow,dd.ylow);
            templine = transposeLine(centerleftline,0,dd.xlow,dd.ylow);
            if(getQuestionsFromLine(&dd,Q2,m_configuration.getNumberOfQuestionsAtColumn(1),tdoublearr,templine,temppoint1,temppoint2,barheightsamplepixels)==1)
            {
                cout<<"ERROR: Error in finding questions in center left line."<<endl;
                break;
            }
            //center right line
            temppoint1 = transposePoint(upcenter,dd.xlow,dd.ylow);
            temppoint2 = transposePoint(dncenter,dd.xlow,dd.ylow);
            cout<<"INFO: Finding center right line. NumOfSamples="<<maxLineSamples<<endl;
            numLineSamples = findLineImageFromLeft(lineSamples,maxLineSamples, dd.buf, dd.xSizeBytesAllocated,temppoint1,temppoint2);
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
            centerrightline=transposeLine(centerrightline,0,-1*dd.xlow,-1*dd.ylow);
            //Q3
            temppoint1 = findIntersection(centerrightline,topline);temppoint1 = transposePoint(temppoint1,dd.xlow,dd.ylow);
            temppoint2 = findIntersection(centerrightline,bottomline);temppoint2 = transposePoint(temppoint2,dd.xlow,dd.ylow);
            templine = transposeLine(centerrightline,0,dd.xlow,dd.ylow);
            if(getQuestionsFromLine(&dd,Q3,m_configuration.getNumberOfQuestionsAtColumn(2),tdoublearr,templine,temppoint1,temppoint2,barheightsamplepixels)==1)
            {
                cout<<"ERROR: Error in finding questions in center right line."<<endl;
                break;
            }
            deAllocData(&dd);
        }
        if(m_configuration.getNumberOfColumns()==2){
            //COL1
            addPointToDataDigital(&img,&dd,uplfcorner._x,uplfcorner._y);
            addPointToDataDigital(&img,&dd,dnlfcorner._x,dnlfcorner._y);
            addPointToDataDigital(&img,&dd,upcenter._x,upcenter._y);
            addPointToDataDigital(&img,&dd,dncenter._x,dncenter._y);
            if(allocData(&dd)==1)
            {
                cout<<"ERROR: Error in allocating data for image buffer."<<endl;
                break;
            }
            if(getDataFromBmp(&img,&dd)==1)
            {
                cout<<"ERROR: Error in transferring data for image buffer."<<endl;
                break;
            }
            if(processOneColumn(&dd, Q1, Q2, m_configuration.getNumberOfQuestionsAtColumn(1), 1))
            {
                cout<<"ERROR: Error in finding number circles."<<endl;
                break;
            }
            deAllocData(&dd);
            //COL2
            addPointToDataDigital(&img,&dd,upcenter._x,upcenter._y);
            addPointToDataDigital(&img,&dd,dncenter._x,dncenter._y);
            addPointToDataDigital(&img,&dd,uprtcorner._x,uprtcorner._y);
            addPointToDataDigital(&img,&dd,dnrtcorner._x,dnrtcorner._y);
            if(allocData(&dd)==1)
            {
                cout<<"ERROR: Error in allocating data for image buffer."<<endl;
                break;
            }
            if(getDataFromBmp(&img,&dd)==1)
            {
                cout<<"ERROR: Error in transferring data for image buffer."<<endl;
                break;
            }
            if(processOneColumn(&dd, Q3, Q4, m_configuration.getNumberOfQuestionsAtColumn(2), 2))
            {
                cout<<"ERROR: Error in finding number circles."<<endl;
                break;
            }
            deAllocData(&dd);
        }else if(m_configuration.getNumberOfColumns()==1){
            //SINGLE COLUMN
            addPointToDataDigital(&img,&dd,uplfcorner._x,uplfcorner._y);
            addPointToDataDigital(&img,&dd,dnlfcorner._x,dnlfcorner._y);
            addPointToDataDigital(&img,&dd,uprtcorner._x,uprtcorner._y);
            addPointToDataDigital(&img,&dd,dnrtcorner._x,dnrtcorner._y);
            if(allocData(&dd)==1)
            {
                cout<<"ERROR: Error in allocating data for image buffer."<<endl;
                break;
            }
            if(getDataFromBmp(&img,&dd)==1)
            {
                cout<<"ERROR: Error in transferring data for image buffer."<<endl;
                break;
            }
            printDataDigitalBuffer(&dd);
            if(processOneColumn(&dd, Q1, Q4, m_configuration.getNumberOfQuestionsAtColumn(1), 1))
            {
                cout<<"ERROR: Error in finding number circles."<<endl;
                break;
            }
            deAllocData(&dd);
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
    cleanDataDigital(&dd);
    closeBmpImage(&img);
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
    clearFrequencyDatabase();

    saveHeadersToCsvFile();
    if(pathHandler.isDirectory())
    {
        processDirectory(pathHandler.getFullPath());
    }
    else
    {
        processOneFile(pathHandler.getFullPath());
        saveDataToCsvFile(pathHandler.getFullPath());
    }
    saveOutputHtmlFile(pathHandler.getFullPath());

    return 0;
}


}
