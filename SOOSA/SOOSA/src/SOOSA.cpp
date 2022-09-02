#include "SOOSA.hpp"

#include <Common/File/AlbaFileReader.hpp>
#include <Common/Math/Helpers/ComputationHelpers.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/User/AlbaUserInterface.hpp>
#include <Geometry/TwoDimensions/Circle.hpp>
#include <Geometry/TwoDimensions/TwoDimensionsHelper.hpp>
#include <Statistics/DataStatistics.hpp>
#include <Statistics/FrequencyStatistics.hpp>

#include <iostream>
#include <sstream>

#define NUMBER_OF_CHOICES 5
#define ALLOWABLE_LINE_DEVIATION_FOR_LINE_MODEL 2
#define ALLOWABLE_HALF_LINE_WIDTH_DEVIATION 2
#define ALLOWABLE_HALF_BAR_WIDTH_DEVIATION 4#define ALLOWABLE_LINE_WIDTH_DEVIATION ALLOWABLE_HALF_LINE_WIDTH_DEVIATION*2
#define ALLOWABLE_BAR_WIDTH_DEVIATION ALLOWABLE_HALF_BAR_WIDTH_DEVIATION*2
#define ALLOWABLE_BAR_HEIGHT_DEVIATION 10
#define MINIMUM_NUMBER_OF_LINE_SAMPLES 10#define RETAIN_RATIO_FOR_DEVIATION 0.90
#define MAXIMUM_BAR_WIDTH 500
#define MINIMUM_NUMBER_OF_BAR_WIDTHS_TO_BE_A_BAR 20
#define BAR_HEIGHT_TO_DIAMETER_RATIO 0.5
#define MINIMUM_PERCENTAGE_OF_BLACK_POINTS_FOR_FILLED_CIRCLE 0.7

using namespace alba::AprgBitmap;
using namespace alba::mathHelper;
using namespace alba::TwoDimensions;
using namespace std;

namespace alba
{

namespace soosa
{

SOOSA::FrequencyDatabase::FrequencyDatabase(unsigned int numberOfQuestions)
    : m_numberOfQuestions(numberOfQuestions)
{
    initialize();
}

void SOOSA::FrequencyDatabase::initialize()
{
    m_frequenciesOnQuestionByAnswer.clearAndResize(m_numberOfQuestions, NUMBER_OF_CHOICES);
}

void SOOSA::FrequencyDatabase::addAnswer(unsigned int const questionNumber, unsigned int const answer){
    if(questionNumber<m_numberOfQuestions && answer<=4)
    {
        m_frequenciesOnQuestionByAnswer.getEntryReference(questionNumber, answer)++;
    }
}
unsigned int SOOSA::FrequencyDatabase::getFrequencyOfAnswer(unsigned int const questionNumber, unsigned int const answer) const
{
    unsigned int frequency=0;
    if(questionNumber<m_numberOfQuestions && answer<=4)
    {
        frequency = m_frequenciesOnQuestionByAnswer.getEntry(questionNumber, answer);
    }
    return frequency;
}
SOOSA::PointAndWidth::PointAndWidth(Point const& point, double const width)
    : m_point(point), m_width(width)
{}
Point SOOSA::PointAndWidth::getPoint() const
{
    return m_point;
}

double SOOSA::PointAndWidth::getWidth() const
{
    return m_width;
}

SOOSA::Status::Status()
{}

SOOSA::Status SOOSA::Status::getInstance()
{
    static Status instance;
    return instance;
}

string SOOSA::Status::getStatusString() const
{
    string result;
    if(!m_errors.empty())
    {
        result = stringHelper::combineStrings(m_errors, " ");
    }
    else
    {
        result = "No errors encountered.";
    }
    return result;
}

void SOOSA::Status::setError(string const& error)
{
    m_errors.emplace_back(error);
}

void SOOSA::Status::clearErrors()
{
    m_errors.clear();
}

bool SOOSA::Status::isStatusNoError() const
{
    return m_errors.empty();
}

SOOSA::SOOSA(InputConfiguration const& configuration)
    : m_inputConfiguration(configuration)
    , m_numberOfRespondents{}
    , m_questionToAnswersMap()
    , m_frequencyDatabase(m_inputConfiguration.getNumberOfQuestions())
{}

unsigned int SOOSA::getNumberOfAnswers() const
{
    return m_questionToAnswersMap.size();
}

unsigned int SOOSA::getAnswerToQuestion(unsigned int const questionNumber) const
{
    return m_questionToAnswersMap.at(questionNumber);
}

void SOOSA::process()
{
    cout << "SOOSA2014 - Survey Output Optical Scan Analyzer\n" << endl;
    cout << "Input path: " << m_inputConfiguration.getPath() << endl;
    cout << "Area: " << m_inputConfiguration.getArea() << endl;
    cout << "Period: " << m_inputConfiguration.getPeriod() << endl;
    cout << "Discharge: " << m_inputConfiguration.getDischarge() << endl;
    cout << "Minimum satisfactory score (inclusive): " << m_inputConfiguration.getMinimumSatisfactoryScore() << endl;
    cout << "NumberOfQuestions: " << m_inputConfiguration.getNumberOfQuestions() << endl;
    cout << "NumberOColumns: " << m_inputConfiguration.getNumberOfColumns() << endl;

    AlbaLocalPathHandler pathHandler(m_inputConfiguration.getPath());

    saveHeadersToCsvFile();
    if(pathHandler.isDirectory())
    {
        processDirectory(pathHandler.getFullPath());
    }
    else
    {
        processFile(pathHandler.getFullPath());
        saveDataToCsvFile(pathHandler.getFullPath());
    }
    saveOutputHtmlFile(pathHandler.getFullPath());
}

void SOOSA::processDirectory(string const& directoryPath)
{
    cout << "processDirectory: [" << directoryPath << "]" << endl;
    AlbaLocalPathHandler directoryPathToBeProcessed(directoryPath);
    set<string> listOfFiles;
    set<string> listOfDirectories;
    directoryPathToBeProcessed.findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectories);

    for(string const& filePath : listOfFiles)
    {
        processFile(filePath);
        saveDataToCsvFile(filePath);
    }
}

string SOOSA::getCsvFileName(string const& path) const
{
    return AlbaLocalPathHandler(path).getDirectory()+"PSS_Report_"+m_inputConfiguration.getArea()+"_"+m_inputConfiguration.getPeriod()+".csv";
}

string SOOSA::getReportHtmlFileName(string const& path) const
{
    return AlbaLocalPathHandler(path).getDirectory()+"PSS_Report_"+m_inputConfiguration.getArea()+"_"+m_inputConfiguration.getPeriod()+".html";
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
    m_questionToAnswersMap[m_inputConfiguration.getQuestionNumberInColumn(columnNumber, questionOffsetInColumn)] = answer;
}


void SOOSA::saveDataToCsvFile(string const& processedFilePath)  const
{
    ofstream outputCsvReportStream(getCsvFileName(m_inputConfiguration.getPath()), ofstream::app);
    if(Status::getInstance().isStatusNoError())
    {
        outputCsvReportStream<<processedFilePath<<",OK";
        for(unsigned int i=0;i<m_inputConfiguration.getNumberOfQuestions();i++)
        {
            outputCsvReportStream<<","<<getAnswerToQuestion(i);
        }
        outputCsvReportStream<<endl;
    }
    else
    {
        outputCsvReportStream<<processedFilePath<<","<<Status::getInstance().getStatusString()<<endl;
    }
}

void SOOSA::saveHeadersToCsvFile() const
{
    ofstream outputCsvReportStream(getCsvFileName(m_inputConfiguration.getPath()));
    outputCsvReportStream << "FILE,STATUS";
    for(unsigned int i=0; i<m_inputConfiguration.getNumberOfQuestions(); i++)
    {
        outputCsvReportStream << ",Question_" << i+1;
    }
    outputCsvReportStream << endl;
}

void SOOSA::saveOutputHtmlFile(string const& processedFilePath) const
{
    cout << "saveOutputHtmlFile -> saving data to output html file" << endl;
    AlbaLocalPathHandler basisHtmlPath(PathInitialValueSource::DetectedLocalPath);
    basisHtmlPath.input(basisHtmlPath.getDirectory() + "basis.html");
    ifstream htmlBasisFileStream(basisHtmlPath.getFullPath());
    if(htmlBasisFileStream.is_open())
    {
        AlbaFileReader htmlBasisFileReader(htmlBasisFileStream);
        ofstream reportHtmlFileStream(getReportHtmlFileName(processedFilePath));
        reportHtmlFileStream.precision(5);
        while(htmlBasisFileReader.isNotFinished())
        {
            string line(htmlBasisFileReader.getLineAndIgnoreWhiteSpaces());
            if(line == "@TITLE@")
            {
                reportHtmlFileStream<<m_inputConfiguration.getFormDetailsTitle()<<endl;
            }
            else if(line == "@AREA@")
            {
                reportHtmlFileStream<<m_inputConfiguration.getArea()<<endl;
            }
            else if(line == "@PERIOD@")
            {
                reportHtmlFileStream<<m_inputConfiguration.getPeriod()<<endl;
            }
            else if(line == "@SUMMARY@")
            {
                reportHtmlFileStream << "<h2>Number of Respondents: " << m_numberOfRespondents<<"</h2>" << endl;
                reportHtmlFileStream << "<h2>Average Discharges per Month: " << m_inputConfiguration.getDischarge() << "</h2>" << endl;
                double dischargeValue(m_inputConfiguration.getDischarge());
                reportHtmlFileStream
                        << "<h2>Percentage of respondents to discharges: "
                        << getPrintableStringForPercentage(m_numberOfRespondents, dischargeValue)
                        << "</h2>" << endl;
            }
            else if(line == "@TABLE@")
            {
                saveTableToOutputHtmlFile(reportHtmlFileStream);
            }
            else
            {
                reportHtmlFileStream << line << endl;
            }
        }
        cout << "saveOutputHtmlFile -> successful!" << endl;
    }
    else
    {
        cout << "saveOutputHtmlFile -> cannot save to output html file because basis cannot be opened." << endl;
        cout << "saveOutputHtmlFile -> basis html path: [" << basisHtmlPath.getFullPath() << "]" << endl;
        cout << "saveOutputHtmlFile -> basis html can be found on local system: [" << basisHtmlPath.isFoundInLocalSystem() << "]" << endl;
    }
}

void SOOSA::saveTableToOutputHtmlFile(ofstream & reportHtmlFileStream) const
{
    for(unsigned int questionIndex=0; questionIndex<m_inputConfiguration.getNumberOfQuestions(); questionIndex++)
    {
        reportHtmlFileStream<<"<tr>"<<endl;
        FrequencyStatistics::FrequencySamples samples;
        for(unsigned int answerIndex=0; answerIndex<NUMBER_OF_CHOICES; answerIndex++)
        {
            samples[answerIndex+1] = m_frequencyDatabase.getFrequencyOfAnswer(questionIndex, answerIndex);
        }
        unsigned int numberOfSamplesForQuestion = FrequencyStatistics::calculateNumberOfSamples(samples);
        double median = FrequencyStatistics::calculateMedian(samples);
        if(questionIndex==m_inputConfiguration.getNumberOfQuestions()-1)
        {
            reportHtmlFileStream<<"<td style=\"text-align:left;padding:3px\"><b>"<<m_inputConfiguration.getQuestionAt(questionIndex)<<"</b></td>"<<endl;
        }
        else
        {
            reportHtmlFileStream<<"<td style=\"text-align:left;padding:3px\">"<<m_inputConfiguration.getQuestionAt(questionIndex)<<"</td>"<<endl;
        }
        for(unsigned int answer=NUMBER_OF_CHOICES; answer>0; answer--)
        {
            reportHtmlFileStream<<"<td style=\"text-align:center;padding:3px\">"<<getPrintableStringForPercentage(m_frequencyDatabase.getFrequencyOfAnswer(questionIndex, answer-1), numberOfSamplesForQuestion)<<"</td>"<<endl;
        }
        reportHtmlFileStream<<"<td style=\"text-align:center;padding:3px\">"<<numberOfSamplesForQuestion<<"</td>"<<endl;
        reportHtmlFileStream<<"<td style=\"text-align:center;padding:3px\">"<<median<<"</td>"<<endl;

        unsigned int satisfactoryFrequency(0U);
        for(unsigned int answer=NUMBER_OF_CHOICES; answer>0U; answer--)
        {
            if(answer>=m_inputConfiguration.getMinimumSatisfactoryScore())
            {
                satisfactoryFrequency += m_frequencyDatabase.getFrequencyOfAnswer(questionIndex, answer-1);
            }
        }
        reportHtmlFileStream<<"<td style=\"text-align:center;padding:3px\">"<<getPrintableStringForPercentage(satisfactoryFrequency, numberOfSamplesForQuestion)<<"</td>"<<endl;
        reportHtmlFileStream<<"</tr>"<<endl;
    }
}

void SOOSA::saveFrequencyDatabaseIfNoError()
{
    if(Status::getInstance().isStatusNoError())
    {
        m_numberOfRespondents++;
        for(unsigned int i=0;i<m_inputConfiguration.getNumberOfQuestions();i++)
        {
            m_frequencyDatabase.addAnswer(i, getAnswerToQuestion(i)-1);
        }
    }
}

void SOOSA::processFile(string const& filePath)
{
    cout << endl;
    cout << "processFile: [" << filePath << "]" << endl;
    Status::getInstance().clearErrors();

    Bitmap bitmap(filePath);
    BitmapSnippet globalSnippet(bitmap.getSnippetReadFromFileWholeBitmap());

    Line leftLine, rightLine, topLine, bottomLine, centerLeftLine, centerRightLine;
    leftLine = findLeftLine(globalSnippet);
    rightLine = findRightLine(globalSnippet);
    topLine = findTopLine(globalSnippet);
    bottomLine = findBottomLine(globalSnippet);
    cout << endl;

    Point edgePoints[2][3];
    edgePoints[0][0] = twoDimensionsHelper::getIntersectionOfTwoLines(leftLine, topLine);
    edgePoints[0][2] = twoDimensionsHelper::getIntersectionOfTwoLines(rightLine, topLine);
    edgePoints[1][0] = twoDimensionsHelper::getIntersectionOfTwoLines(leftLine, bottomLine);
    edgePoints[1][2] = twoDimensionsHelper::getIntersectionOfTwoLines(rightLine, bottomLine);
    edgePoints[0][1] = twoDimensionsHelper::getMidpoint(edgePoints[0][0], edgePoints[0][2]);
    edgePoints[1][1] = twoDimensionsHelper::getMidpoint(edgePoints[1][0], edgePoints[1][2]);

    if(m_inputConfiguration.getNumberOfColumns()==2)
    {
        cout << "Number of columns from template = 2" << endl;
        Line centerLine(edgePoints[0][1], edgePoints[1][1]);
        cout << "find center left line:" << endl;
        centerLeftLine = findRightLineUsingStartingLine(globalSnippet, centerLine);
        cout << "find center right line:" << endl;
        centerRightLine = findLeftLineUsingStartingLine(globalSnippet, centerLine);
        cout << endl;
        cout << "Processing column 1:" << endl;
        processColumn(globalSnippet, leftLine, centerLeftLine, 1);
        cout << endl;
        cout << "Processing column 2:" << endl;
        processColumn(globalSnippet, centerRightLine, rightLine, 2);
    }
    else
    {
        cout << "Number of columns from template = 1" << endl;
        cout << "Processing column:" << endl;
        processColumn(globalSnippet, leftLine, rightLine, 1);
    }
    if(m_inputConfiguration.getNumberOfQuestions() != m_questionToAnswersMap.size())
    {
        cout << "Number of questions does not match the number of answers. Number of questions: " << m_inputConfiguration.getNumberOfQuestions()
           << " Number of answers: "<<m_questionToAnswersMap.size()<<".";

        stringstream ss;
        ss << "Number of questions does not match the number of answers. Number of questions: " << m_inputConfiguration.getNumberOfQuestions()
           << " Number of answers: "<<m_questionToAnswersMap.size()<<".";
        Status::getInstance().setError(ss.str());
    }
    saveFrequencyDatabaseIfNoError();
}

Line SOOSA::findLeftLine(BitmapSnippet const& snippet) const
{
    cout << "findLeftLine:" << endl;
    RangeOfInts rangeForX(snippet.getTopLeftCorner().getX(), snippet.getBottomRightCorner().getX(), 1);
    return findVerticalLine(snippet, rangeForX);
}

Line SOOSA::findRightLine(BitmapSnippet const& snippet) const
{
    cout << "findRightLine:" << endl;
    RangeOfInts rangeForX(snippet.getBottomRightCorner().getX(), snippet.getTopLeftCorner().getX(), -1);
    return findVerticalLine(snippet, rangeForX);
}

Line SOOSA::findTopLine(BitmapSnippet const& snippet) const
{
    cout << "findTopLine:" << endl;
    RangeOfInts rangeForY(snippet.getTopLeftCorner().getY(), snippet.getBottomRightCorner().getY(), 1);
    return findHorizontalLine(snippet, rangeForY);
}

Line SOOSA::findBottomLine(BitmapSnippet const& snippet) const
{
    cout << "findBottomLine:" << endl;
    RangeOfInts rangeForY(snippet.getBottomRightCorner().getY(), snippet.getTopLeftCorner().getY(), -1);
    return findHorizontalLine(snippet, rangeForY);
}

Line SOOSA::findVerticalLine(BitmapSnippet const& snippet, RangeOfInts const& rangeForX) const
{
    RangeOfInts::TerminationCondition conditionForX(rangeForX.getTerminationCondition());
    TwoDimensionsStatistics::Samples samples;
    for(unsigned int y=snippet.getTopLeftCorner().getY(); y<=snippet.getBottomRightCorner().getY(); y++)
    {
        AlbaValueRange<double> consecutiveBlackPixels;
        for(unsigned int x=rangeForX.getStartValue(); conditionForX(x, rangeForX.getEndValue()); x+=rangeForX.getInterval())
        {
            if(snippet.isBlackAt(BitmapXY(x, y)))
            {
                if(consecutiveBlackPixels.isEmpty())
                {
                    consecutiveBlackPixels.setStartValue((double)x);
                }
                consecutiveBlackPixels.setEndValue((double)x);
            }
            else if(!consecutiveBlackPixels.isEmpty())
            {
                samples.emplace_back(TwoDimensionsStatistics::Sample{consecutiveBlackPixels.getMidpointValue(), (double)y});
                break;
            }
        }
    }
    return getLineModel(samples);
}

Line SOOSA::findHorizontalLine(BitmapSnippet const& snippet, RangeOfInts const& rangeForY) const
{
    RangeOfInts::TerminationCondition conditionForY(rangeForY.getTerminationCondition());
    TwoDimensionsStatistics::Samples samples;
    for(unsigned int x=snippet.getTopLeftCorner().getX(); x<=snippet.getBottomRightCorner().getX(); x++)
    {
        AlbaValueRange<double> consecutiveBlackPixels;
        for(unsigned int y=rangeForY.getStartValue(); conditionForY(y, rangeForY.getEndValue()); y+=rangeForY.getInterval())
        {
            if(snippet.isBlackAt(BitmapXY(x, y)))
            {
                if(consecutiveBlackPixels.isEmpty())
                {
                    consecutiveBlackPixels.setStartValue((double)y);
                }
                consecutiveBlackPixels.setEndValue((double)y);
            }
            else if(!consecutiveBlackPixels.isEmpty())
            {
                samples.emplace_back(TwoDimensionsStatistics::Sample{(double)x, consecutiveBlackPixels.getMidpointValue()});
                break;
            }
        }
    }
    return getLineModel(samples);
}

Line SOOSA::findLeftLineUsingStartingLine(BitmapSnippet const& snippet, Line const& startingLine) const
{
    RangeOfInts rangeForX(snippet.getTopLeftCorner().getX(), snippet.getBottomRightCorner().getX(), 1);
    return findVerticalLineUsingStartingLine(snippet, startingLine, rangeForX);
}

Line SOOSA::findRightLineUsingStartingLine(BitmapSnippet const& snippet, Line const& startingLine) const
{
    RangeOfInts rangeForX(snippet.getBottomRightCorner().getX(), snippet.getTopLeftCorner().getX(), -1);
    return findVerticalLineUsingStartingLine(snippet, startingLine, rangeForX);
}

Line SOOSA::findVerticalLineUsingStartingLine(BitmapSnippet const& snippet, Line const& startingLine, RangeOfInts const& rangeForX) const
{
    RangeOfInts::TerminationCondition conditionForX(rangeForX.getTerminationCondition());
    TwoDimensionsStatistics::Samples samples;
    for(unsigned int y=snippet.getTopLeftCorner().getY(); y<=snippet.getBottomRightCorner().getY(); y++)
    {
        AlbaValueRange<double> consecutiveBlackPixels;
        double xInLine = round(startingLine.calculateXFromY(y));
        for(int x=(int)xInLine; conditionForX(x, rangeForX.getEndValue()); x+=rangeForX.getInterval())
        {
            if(snippet.isBlackAt(BitmapXY(x, y)))
            {
                if(consecutiveBlackPixels.isEmpty())
                {
                    consecutiveBlackPixels.setStartValue((double)x);
                }
                consecutiveBlackPixels.setEndValue((double)x);
            }
            else if(!consecutiveBlackPixels.isEmpty())
            {
                samples.emplace_back(TwoDimensionsStatistics::Sample{consecutiveBlackPixels.getMidpointValue(), (double)y});
                break;
            }
        }
    }
    return getLineModel(samples);
}

Line SOOSA::getLineModel(TwoDimensionsStatistics::Samples const & samples) const
{
    int const nonAllowableSquareErrorLimit(ALLOWABLE_LINE_DEVIATION_FOR_LINE_MODEL*ALLOWABLE_LINE_DEVIATION_FOR_LINE_MODEL);

    TwoDimensionsStatistics::LineModel lineModel;
    double maxSquareErrorInSamples(nonAllowableSquareErrorLimit);
    TwoDimensionsStatistics::Samples samplesForLineModeling(samples);
    while(maxSquareErrorInSamples>=nonAllowableSquareErrorLimit && samplesForLineModeling.size() > MINIMUM_NUMBER_OF_LINE_SAMPLES)
    {
        lineModel = TwoDimensionsStatistics::calculateLineModelUsingLeastSquares(samplesForLineModeling);
        TwoDimensionsStatistics::ValueToSampleMultimap squareErrorToSampleMultimap(getSquareErrorToSampleMultimap(samplesForLineModeling, lineModel));
        VectorOfDoubles acceptableSquareErrors(getAcceptableSquareErrorsUsingRetainRatio(squareErrorToSampleMultimap));
        if(acceptableSquareErrors.size() > MINIMUM_NUMBER_OF_LINE_SAMPLES)
        {
            TwoDimensionsStatistics::ValueToSampleMultimap::iterator itForErase = squareErrorToSampleMultimap.find(acceptableSquareErrors.back());
            squareErrorToSampleMultimap.erase(itForErase, squareErrorToSampleMultimap.end());
            acceptableSquareErrors.pop_back();
            updateSamplesForLineModelingFromSquareErrorToSampleMultimap(samplesForLineModeling, squareErrorToSampleMultimap);
            maxSquareErrorInSamples=acceptableSquareErrors.back();
        }
        else
        {
            break;
        }
        //cout << "getLineModel -> samples: " << samplesForLineModeling.size() << endl;
    }
    if(samplesForLineModeling.size() < MINIMUM_NUMBER_OF_LINE_SAMPLES)
    {
        stringstream ss;
        ss<<"Line not found because not enough samples. Samples found for line modeling: "<<samplesForLineModeling.size()<<" Minimum number of samples: "<<MINIMUM_NUMBER_OF_LINE_SAMPLES<<".";
        Status::getInstance().setError(ss.str());
        cout << "getLineModel -> Not enough samples: " << samplesForLineModeling.size() << endl;
    }
    else
    {
        cout << "getLineModel -> Successful! Number of successful samples: " << samplesForLineModeling.size()
           << ", number of minimum samples: " << MINIMUM_NUMBER_OF_LINE_SAMPLES << endl;
        cout << "getLineModel -> Line model coordinates: a=" << lineModel.aCoefficient
             << " b=" << lineModel.bCoefficient
             << " c=" << lineModel.cCoefficient << endl;
    }
    return Line(lineModel.aCoefficient, lineModel.bCoefficient, lineModel.cCoefficient);
}

SOOSA::VectorOfDoubles SOOSA::getAcceptableSquareErrorsUsingKMeans(TwoDimensionsStatistics::ValueToSampleMultimap const& squareErrorToSampleMultimap) const
{
    // not active anymore
    VectorOfDoubles squareErrors;
    OneDimensionKMeans kMeansForSquareErrors;
    for(auto const& squareErrorToSamplePair : squareErrorToSampleMultimap)
    {
        kMeansForSquareErrors.addSample(OneDimensionKMeans::Sample{squareErrorToSamplePair.first});
    }
    OneDimensionKMeans::GroupOfSamples groupOfSamples(kMeansForSquareErrors.getGroupOfSamplesUsingKMeans(2));
    transform(groupOfSamples[0].cbegin(), groupOfSamples[0].cend(), back_inserter(squareErrors), [](OneDimensionKMeans::Sample const& sample)
    {
        return sample.getValueAt(0);
    });
    return squareErrors;
}

SOOSA::VectorOfDoubles SOOSA::getAcceptableSquareErrorsUsingRetainRatio(TwoDimensionsStatistics::ValueToSampleMultimap const& squareErrorToSampleMultimap) const
{
    VectorOfDoubles squareErrors;
    unsigned int retainedSize(RETAIN_RATIO_FOR_DEVIATION*squareErrorToSampleMultimap.size());
    unsigned int count(0);
    for(auto const& squareErrorToSamplePair : squareErrorToSampleMultimap)
    {
        squareErrors.emplace_back(squareErrorToSamplePair.first);
        if(count++ >= retainedSize)
        {
            break;
        }
    }
    return squareErrors;
}

void SOOSA::updateSamplesForLineModelingFromSquareErrorToSampleMultimap(TwoDimensionsStatistics::Samples & samplesLineModeling, TwoDimensionsStatistics::ValueToSampleMultimap const& squareErrorToSampleMultimap) const
{
    samplesLineModeling.clear();
    transform(squareErrorToSampleMultimap.cbegin(), squareErrorToSampleMultimap.cend(), back_inserter(samplesLineModeling), [](TwoDimensionsStatistics::ValueToSamplePair const& squareErrorToSamplePair)
    {
        return squareErrorToSamplePair.second;
    });
}

void SOOSA::processColumn(BitmapSnippet const& snippet, Line const& leftLine, Line const& rightLine, unsigned int const columnNumber)
{
    unsigned int numberQuestionsInColumn = m_inputConfiguration.getNumberOfQuestionsAtColumn(columnNumber);
    cout << "Processing left line of column:" << endl;
    QuestionBarCoordinates questionBarCoordinatesForLeftLine(getQuestionBarCoordinatesFromLine(snippet, leftLine, numberQuestionsInColumn));
    cout << "Processing right line of column:" << endl;
    QuestionBarCoordinates questionBarCoordinatesForRightLine(getQuestionBarCoordinatesFromLine(snippet, rightLine, numberQuestionsInColumn));
    if(questionBarCoordinatesForLeftLine.size() == numberQuestionsInColumn && questionBarCoordinatesForRightLine.size() == numberQuestionsInColumn)
    {
        for(unsigned int questionIndex=0; questionIndex<numberQuestionsInColumn; questionIndex++)
        {
            unsigned int answer(getAnswerToQuestion(snippet, questionBarCoordinatesForLeftLine[questionIndex], questionBarCoordinatesForRightLine[questionIndex]));
            if(answer==0)
            {
                cout << "processColumn -> Problem locating choice in question number: " << questionIndex+1 << ", column number: " << columnNumber << endl;
                stringstream ss;
                ss << "Problem locating choices in a question. Question number: " << questionIndex+1 << ".";
                Status::getInstance().setError(ss.str());
            }
            else
            {
                cout << "processColumn -> Question number: " << questionIndex+1 << " Answer: " << answer << endl;
            }
            setAnswerToQuestionInColumn(columnNumber, questionIndex, answer);
        }
    }
    else
    {
        stringstream ss;
        ss<<"Number of question coordinates does not match between columns. Question bars at left line: "<<questionBarCoordinatesForLeftLine.size()<<"Question bars at right line: "<<questionBarCoordinatesForRightLine.size()<<".";
        Status::getInstance().setError(ss.str());
        cout << "processColumn -> Questions coordinates does not match. Left line: " << questionBarCoordinatesForLeftLine.size()
             << " Right Line: " <<questionBarCoordinatesForRightLine.size()
             << " Number of questions in the column: " << numberQuestionsInColumn << endl;
    }
}

unsigned int SOOSA::getAnswerToQuestion(BitmapSnippet const& snippet, QuestionBarCoordinate const& leftCoordinate, QuestionBarCoordinate const& rightCoordinate) const
{
    Point leftPoint(twoDimensionsHelper::getMidpoint(leftCoordinate.first, leftCoordinate.second));
    Point rightPoint(twoDimensionsHelper::getMidpoint(rightCoordinate.first, rightCoordinate.second));
    double leftBarHeight(twoDimensionsHelper::getDistance(leftCoordinate.first, leftCoordinate.second));
    double rightBarHeight(twoDimensionsHelper::getDistance(rightCoordinate.first, rightCoordinate.second));
    double lowestHeightOfQuestion(min(leftBarHeight, rightBarHeight));
    double radius(lowestHeightOfQuestion*BAR_HEIGHT_TO_DIAMETER_RATIO/2);
    unsigned int shadedChoice=0;
    bool isTwoChoicesShaded(false);
    for(unsigned int choiceIndex=0; choiceIndex<NUMBER_OF_CHOICES; choiceIndex++ )
    {
        if(isChoiceShaded(snippet, leftPoint, rightPoint, choiceIndex, static_cast<unsigned int>(radius)))
        {
            isTwoChoicesShaded = (shadedChoice!=0) ? true : isTwoChoicesShaded;
            shadedChoice = choiceIndex+1;
        }
    }
    if(isTwoChoicesShaded)
    {
        shadedChoice=0;
    }
    unsigned int midpointChoice((NUMBER_OF_CHOICES+1)/2);
    return midpointChoice-(shadedChoice-midpointChoice);
}

bool SOOSA::isChoiceShaded(BitmapSnippet const& snippet, Point const& leftPoint, Point const& rightPoint, unsigned int const choiceIndex, unsigned int const radius) const
{
    double choiceIndexRatio((((double)choiceIndex*2)+1)/(NUMBER_OF_CHOICES*2));
    double differenceFromLeftToRightInX(rightPoint.getX()-leftPoint.getX());
    double differenceFromLeftToRightInY(rightPoint.getY()-leftPoint.getY());
    Point centerOfCircle(leftPoint.getX()+(differenceFromLeftToRightInX*choiceIndexRatio), leftPoint.getY()+(differenceFromLeftToRightInY*choiceIndexRatio));
    unsigned int totalPoints(0), numberOfBlackPoints(0);
    Circle circle(centerOfCircle, radius);
    circle.traverseArea(1, [&](Point const& pointInCircle)
    {
        numberOfBlackPoints += (snippet.isBlackAt(convertToBitmapXY(pointInCircle))) ? 1 : 0;
        totalPoints++;
    });
    return ((double)numberOfBlackPoints/totalPoints) >= MINIMUM_PERCENTAGE_OF_BLACK_POINTS_FOR_FILLED_CIRCLE;
}

SOOSA::QuestionBarCoordinates SOOSA::getQuestionBarCoordinatesFromLine(BitmapSnippet const& snippet, Line const& line, unsigned int const numberQuestionsInColumn) const
{
    QuestionBarCoordinates questionBarCoordinates;
    VectorOfPointAndWidth pointsAndWidths(getPointsAndWidths(snippet, line));
    if(!pointsAndWidths.empty())
    {
        LineAndBarWidths widthAverages(getAverageLineAndBarWidthUsingKMeans(pointsAndWidths));
        TwoDimensionKMeans barPointKMeans, barPointKMeansForCalculation;
        initializeKMeansWithBarPoints(barPointKMeansForCalculation, pointsAndWidths, widthAverages);
        removeIncorrectBarPointsWithKMeans(barPointKMeans, barPointKMeansForCalculation, numberQuestionsInColumn, twoDimensionsHelper::getDistance(pointsAndWidths.front().getPoint(), pointsAndWidths.back().getPoint()));
        saveQuestionBarCoordinatesFromKMeansWithBarPoints(barPointKMeans, questionBarCoordinates, numberQuestionsInColumn);
    }
    cout << "getQuestionBarCoordinatesFromLine -> Number of question bar coordinates: " << questionBarCoordinates.size() << endl;
    return questionBarCoordinates;
}

bool SOOSA::isWithinLineDeviation(double const lineWidthAverage, double const currentWidth) const
{
    return getAbsoluteValue(lineWidthAverage-currentWidth) <= ALLOWABLE_HALF_LINE_WIDTH_DEVIATION;
}

bool SOOSA::isWithinBarDeviation(double const barWidthAverage, double const currentWidth) const
{
    return getAbsoluteValue(barWidthAverage-currentWidth) <= ALLOWABLE_HALF_BAR_WIDTH_DEVIATION;
}

SOOSA::VectorOfPointAndWidth SOOSA::getPointsAndWidths(BitmapSnippet const& snippet, Line const& line) const
{
    Points nearestBlackPointsFromLine(getNearestBlackPointsFromLine(snippet, line));
    VectorOfPointAndWidth pointsAndWidths;
    for(Point const& point : nearestBlackPointsFromLine)
    {
        double barWidth(getBarWidthFromBlackPoint(snippet, line, point));
        pointsAndWidths.emplace_back(point, barWidth);
    }
    return pointsAndWidths;
}

SOOSA::LineAndBarWidths SOOSA::getAverageLineAndBarWidthUsingKMeans(VectorOfPointAndWidth const& pointsAndWidths) const
{
    LineAndBarWidths widthAverages{};
    OneDimensionKMeans kMeansForWidths;
    TwoDimensionsStatistics::ValueToSampleMultimap widthToSampleMultimap(getWidthToSampleMultimap(pointsAndWidths));
    initializeWidthsForKMeans(kMeansForWidths, widthToSampleMultimap);
    while(!kMeansForWidths.getSamples().empty())
    {
        //cout<<"getAverageLineAndBarWidthUsingKMeans -> samples: "<<kMeansForWidths.getSamples().size()<<endl;
        OneDimensionKMeans::GroupOfSamples twoGroupsOfSamples(kMeansForWidths.getGroupOfSamplesUsingKMeans(2));
        RangeOfDoubles minMaxFromFirstGroup(getMinMaxRangeFromKMeansSamples(twoGroupsOfSamples[0]));
        RangeOfDoubles minMaxFromSecondGroup(getMinMaxRangeFromKMeansSamples(twoGroupsOfSamples[1]));
        if(minMaxFromFirstGroup.getDelta() <= ALLOWABLE_LINE_WIDTH_DEVIATION && minMaxFromSecondGroup.getDelta() <= ALLOWABLE_BAR_WIDTH_DEVIATION)
        {
            widthAverages.lineWidth = minMaxFromFirstGroup.getMidpointValue();
            widthAverages.barWidth = minMaxFromSecondGroup.getMidpointValue();
            break;
        }
        else
        {
            removeDeviatedWidthsUsingKMeans(kMeansForWidths, widthToSampleMultimap);
        }
    }
    cout<<"getAverageLineAndBarWidthUsingKMeans -> line width: "<<widthAverages.lineWidth<<" bar width: "<<widthAverages.barWidth<<endl;
    return widthAverages;
}

TwoDimensionsStatistics::ValueToSampleMultimap SOOSA::getWidthToSampleMultimap(VectorOfPointAndWidth const& pointsAndWidths) const
{
    TwoDimensionsStatistics::ValueToSampleMultimap widthToSampleMultimap;
    for(PointAndWidth const& pointAndWidth : pointsAndWidths)
    {
        widthToSampleMultimap.emplace(pointAndWidth.getWidth(), convertToTwoDimensionSample(pointAndWidth.getPoint()));
    }
    return widthToSampleMultimap;
}

void SOOSA::initializeWidthsForKMeans(OneDimensionKMeans & kMeansForWidths, TwoDimensionsStatistics::ValueToSampleMultimap const& widthToSampleMultimap) const
{
    for(auto const& widthToSamplePair : widthToSampleMultimap)
    {
        kMeansForWidths.addSample(OneDimensionKMeans::Sample{widthToSamplePair.first});
    }
}

void SOOSA::removeDeviatedWidthsUsingKMeans(OneDimensionKMeans & kMeansForWidths, TwoDimensionsStatistics::ValueToSampleMultimap const& widthToSampleMultimap) const
{
    OneDimensionKMeans::GroupOfSamples groupsOfSamples(kMeansForWidths.getGroupOfSamplesUsingKMeans(5));
    kMeansForWidths.clear();
    set<unsigned int> groupSizes;
    groupSizes.emplace(groupsOfSamples[0].size());
    groupSizes.emplace(groupsOfSamples[1].size());
    groupSizes.emplace(groupsOfSamples[2].size());
    groupSizes.emplace(groupsOfSamples[3].size());
    groupSizes.emplace(groupsOfSamples[4].size());
    auto groupSizeIterator = groupSizes.begin();
    groupSizeIterator++;
    unsigned int minimumGroupSize(*groupSizeIterator);
    addWidthToKMeansIfNeeded(kMeansForWidths, groupsOfSamples[0], widthToSampleMultimap, minimumGroupSize);
    addWidthToKMeansIfNeeded(kMeansForWidths, groupsOfSamples[1], widthToSampleMultimap, minimumGroupSize);
    addWidthToKMeansIfNeeded(kMeansForWidths, groupsOfSamples[2], widthToSampleMultimap, minimumGroupSize);
    addWidthToKMeansIfNeeded(kMeansForWidths, groupsOfSamples[3], widthToSampleMultimap, minimumGroupSize);
    addWidthToKMeansIfNeeded(kMeansForWidths, groupsOfSamples[4], widthToSampleMultimap, minimumGroupSize);
}

void SOOSA::addWidthToKMeansIfNeeded(OneDimensionKMeans & kMeans, OneDimensionKMeans::Samples const& groupOfSamples, TwoDimensionsStatistics::ValueToSampleMultimap const& widthToSampleMultimap, unsigned int const minimumGroupSize) const
{
    if(groupOfSamples.size() > minimumGroupSize)
    {
        RangeOfDoubles minMaxFromGroupInThreeGroups(getMinMaxRangeFromKMeansSamples(groupOfSamples));
        for(auto const& widthSamplePair : widthToSampleMultimap)
        {
            if(minMaxFromGroupInThreeGroups.isValueInsideInclusive(widthSamplePair.first))
            {
                kMeans.addSample(OneDimensionKMeans::Sample{widthSamplePair.first});
            }
        }
    }
}

SOOSA::RangeOfDoubles SOOSA::getMinMaxRangeFromKMeansSamples(OneDimensionKMeans::Samples const& samples) const
{
    DataCollection<double> collection;
    for(OneDimensionKMeans::Sample const& sample : samples)
    {
        collection.addData(sample.getValueAt(0));
    }
    return RangeOfDoubles(collection.getMinimum(), collection.getMaximum(), 1);
}

Points SOOSA::getNearestBlackPointsFromLine(BitmapSnippet const& snippet, Line const& line) const
{
    Points linePoints(line.getPoints(convertToPoint(snippet.getTopLeftCorner()), convertToPoint(snippet.getBottomRightCorner()), 1));
    Points nearestBlackPointsFromLine;
    for(Point const& point : linePoints)
    {
        if(snippet.isBlackAt(convertToBitmapXY(point)))
        {
            nearestBlackPointsFromLine.emplace_back(point);
        }
        else
        {
            Point blackPoint(getNearestBlackPointFromLine(snippet, line, point));
            if(!blackPoint.isEmpty())
            {
                nearestBlackPointsFromLine.emplace_back(blackPoint);
            }
        }
    }
    return nearestBlackPointsFromLine;
}

Point SOOSA::getNearestBlackPointFromLine(BitmapSnippet const& snippet, Line const& line, Point const& point) const
{
    Point blackPoint;
    Line perpendicularLine(twoDimensionsHelper::getLineWithPerpendicularSlope(line, point));
    for(unsigned int deviation=1; deviation<=ALLOWABLE_HALF_LINE_WIDTH_DEVIATION; deviation++)
    {
        double lowerDeviatedInX = point.getX()-deviation;
        Point lowerDeviatedPoint(lowerDeviatedInX, perpendicularLine.calculateYFromX(lowerDeviatedInX));
        if(snippet.isBlackAt(convertToBitmapXY(lowerDeviatedPoint)))
        {
            blackPoint = lowerDeviatedPoint;
            break;
        }
        double higherDeviatedInX = point.getX()+deviation;
        Point higherDeviatedPoint(higherDeviatedInX, perpendicularLine.calculateYFromX(higherDeviatedInX));
        if(snippet.isBlackAt(convertToBitmapXY(higherDeviatedPoint)))
        {
            blackPoint = higherDeviatedPoint;
            break;
        }
    }
    return blackPoint;
}

double SOOSA::getBarWidthFromBlackPoint(BitmapSnippet const& snippet, Line const& line, Point const& blackPoint) const
{
    Line perpendicularLine(twoDimensionsHelper::getLineWithPerpendicularSlope(line, blackPoint));
    Point leftMostBlack(blackPoint);
    Point rightMostBlack(blackPoint);
    bool isBlack(true);
    for(unsigned int offset=1; offset<=MAXIMUM_BAR_WIDTH && isBlack; offset++)
    {
        double possibleBlackPointInX = blackPoint.getX()-offset;
        Point possibleBlackPoint(possibleBlackPointInX, perpendicularLine.calculateYFromX(possibleBlackPointInX));
        isBlack = snippet.isBlackAt(convertToBitmapXY(possibleBlackPoint));
        if(isBlack)
        {
            leftMostBlack=possibleBlackPoint;
        }
    }
    isBlack = true;
    for(unsigned int offset=1; offset<=MAXIMUM_BAR_WIDTH && isBlack; offset++)
    {
        double possibleBlackPointInX = blackPoint.getX()+offset;
        Point possibleBlackPoint(possibleBlackPointInX, perpendicularLine.calculateYFromX(possibleBlackPointInX));
        isBlack = snippet.isBlackAt(convertToBitmapXY(possibleBlackPoint));
        if(isBlack)
        {
            rightMostBlack=possibleBlackPoint;
        }
    }
    return twoDimensionsHelper::getDistance(leftMostBlack, rightMostBlack);
}

void SOOSA::initializeKMeansWithBarPoints(TwoDimensionKMeans & barPointKMeans, VectorOfPointAndWidth const& pointsAndWidths, LineAndBarWidths const& widthAverages) const
{
    for(PointAndWidth const& pointAndWidth : pointsAndWidths)
    {
        if(isWithinBarDeviation(widthAverages.barWidth, pointAndWidth.getWidth()))
        {
            barPointKMeans.addSample(convertToTwoDimensionSample(pointAndWidth.getPoint()));
        }
    }
}

void SOOSA::removeIncorrectBarPointsWithKMeans(TwoDimensionKMeans & barPointKMeans, TwoDimensionKMeans & barPointKMeansForCalculation, unsigned int const numberQuestionsInColumn, double const totalHeight) const
{
    bool isBarPointsNeedToBeDecreased(true);
    OneDimensionStatistics::Sample previousStandardDeviationOfHeight{(double)totalHeight};
    while(isBarPointsNeedToBeDecreased)
    {
        TwoDimensionKMeans::GroupOfSamples groupOfGroupOfBarPoints(barPointKMeansForCalculation.getGroupOfSamplesUsingKMeans(numberQuestionsInColumn));
        OneDimensionStatistics::Samples barHeights;
        DataCollection<double> heightCollection;
        saveHeightDetailsFromBarPoints(groupOfGroupOfBarPoints, barHeights, heightCollection);

        OneDimensionStatistics barHeightsStatistics(barHeights);
        OneDimensionStatistics::Sample standardDeviationOfHeight(barHeightsStatistics.getSampleStandardDeviation());
        if(previousStandardDeviationOfHeight.getValueAt(0)<standardDeviationOfHeight.getValueAt(0))
        {
            isBarPointsNeedToBeDecreased = false;
        }
        if(isBarPointsNeedToBeDecreased)
        {
            previousStandardDeviationOfHeight = standardDeviationOfHeight;
            removeIncorrectBarPointsByHeight(barPointKMeans, barPointKMeansForCalculation, heightCollection, groupOfGroupOfBarPoints);
        }
    }
}

void SOOSA::saveHeightDetailsFromBarPoints(TwoDimensionKMeans::GroupOfSamples const & groupOfGroupOfBarPoints, OneDimensionStatistics::Samples & barHeights, DataCollection<double> & heightCollection) const
{
    for(TwoDimensionKMeans::Samples const& groupOfBarPoints : groupOfGroupOfBarPoints)
    {
        if(!groupOfBarPoints.empty())
        {
            double height(twoDimensionsHelper::getDistance(convertToPoint(groupOfBarPoints.front()), convertToPoint(groupOfBarPoints.back())));
            heightCollection.addData(height);
            barHeights.emplace_back(OneDimensionStatistics::Sample{(double)height});
        }
    }
}

void SOOSA::removeIncorrectBarPointsByHeight(TwoDimensionKMeans & barPointKMeans, TwoDimensionKMeans & barPointKMeansForCalculation, DataCollection<double> const& heightCollection, TwoDimensionKMeans::GroupOfSamples const& groupOfGroupOfBarPoints) const
{
    barPointKMeans.clear();
    barPointKMeansForCalculation.clear();
    double deltaToMax(heightCollection.getMaximum() - heightCollection.getAverage());
    double deltaToMin(heightCollection.getAverage() - heightCollection.getMinimum());
    bool isMinimumToBeRemoved(deltaToMin>deltaToMax);
    for(TwoDimensionKMeans::Samples const& groupOfBarPoints : groupOfGroupOfBarPoints)
    {
        if(!groupOfBarPoints.empty())
        {
            double height(twoDimensionsHelper::getDistance(convertToPoint(groupOfBarPoints.front()), convertToPoint(groupOfBarPoints.back())));
            barPointKMeans.addSamples(groupOfBarPoints);
            if(isMinimumToBeRemoved && height == heightCollection.getMinimum())
            {
                //do nothing
            }
            else if(!isMinimumToBeRemoved && height == heightCollection.getMaximum())
            {
                DequeOfPoints dequeWithHighestHeight;
                transform(groupOfBarPoints.cbegin(), groupOfBarPoints.cend(), back_inserter(dequeWithHighestHeight), [&](TwoDimensionKMeans::Sample const& sample)
                {
                    return convertToPoint(sample);
                });
                adjustHeightUntilTargetHeight(dequeWithHighestHeight, heightCollection, height);
                for(Point const& point : dequeWithHighestHeight)
                {
                    barPointKMeansForCalculation.addSample(convertToTwoDimensionSample(point));
                }
            }
            else
            {
                barPointKMeansForCalculation.addSamples(groupOfBarPoints);
            }
        }
    }
}

void SOOSA::adjustHeightUntilTargetHeight(DequeOfPoints & dequeWithHighestHeight, DataCollection<double> const& heightCollection, double const height) const
{
    double adjustedHeight = height;
    double targetHeight = heightCollection.getAverage();
    while(adjustedHeight > targetHeight && dequeWithHighestHeight.size() > 2)
    {
        double heightWithoutTop(twoDimensionsHelper::getDistance(*(dequeWithHighestHeight.begin()+1), dequeWithHighestHeight.back()));
        double heightWithoutBottom(twoDimensionsHelper::getDistance(dequeWithHighestHeight.front(), *(dequeWithHighestHeight.cend()-1)));
        if(getAbsoluteValue(heightWithoutTop-heightWithoutBottom) < ALLOWABLE_BAR_HEIGHT_DEVIATION)
        {
            dequeWithHighestHeight.pop_front();
            dequeWithHighestHeight.pop_back();
        }
        if(heightWithoutTop < heightWithoutBottom)
        {
            dequeWithHighestHeight.pop_front();
        }
        else
        {
            dequeWithHighestHeight.pop_back();
        }
        adjustedHeight = twoDimensionsHelper::getDistance(dequeWithHighestHeight.front(), dequeWithHighestHeight.back());
    }
}

void SOOSA::saveQuestionBarCoordinatesFromKMeansWithBarPoints(TwoDimensionKMeans const& barPointKMeans, QuestionBarCoordinates & questionBarCoordinates, unsigned int const numberQuestionsInColumn) const
{
    TwoDimensionKMeans::GroupOfSamples groupOfGroupOfBarPoints(barPointKMeans.getGroupOfSamplesUsingKMeans(numberQuestionsInColumn));
    for(TwoDimensionKMeans::Samples const& groupOfBarPoints : groupOfGroupOfBarPoints)
    {
        if(!groupOfBarPoints.empty())
        {
            questionBarCoordinates.emplace_back(QuestionBarCoordinate(convertToPoint(groupOfBarPoints.front()), convertToPoint(groupOfBarPoints.back())));
        }
    }
}

void SOOSA::writeLineInBitmap(Bitmap & bitmap, Line const& line) const
{
    BitmapXY topLeft(0,0);
    BitmapXY bottomRight(bitmap.getConfiguration().getBitmapWidth()-1, bitmap.getConfiguration().getBitmapHeight()-1);

    BitmapSnippet snippet(bitmap.getSnippetReadFromFileWholeBitmap());
    Points points(line.getPoints(Point(topLeft.getX(), topLeft.getY()), Point(bottomRight.getX(), bottomRight.getY()), 1));
    for (Point point: points)
    {
        snippet.setPixelAt(BitmapXY(point.getX(), point.getY()), 0x00EE0000);
    }

    bitmap.setSnippetWriteToFile(snippet);
}

BitmapXY SOOSA::convertToBitmapXY(Point const& point) const
{
    return BitmapXY((unsigned int)round(clampLowerBound(point.getX(), (double)0)), (unsigned int)round(clampLowerBound(point.getY(), (double)0)));
}

BitmapXY SOOSA::convertToBitmapXY(TwoDimensionsStatistics::Sample const& sample) const
{
    return BitmapXY((unsigned int)round(clampLowerBound(sample.getValueAt(0), (double)0)), (unsigned int)round(clampLowerBound(sample.getValueAt(1), (double)0)));
}

Point SOOSA::convertToPoint(BitmapXY const& bitmapXY) const
{
    return Point((double)bitmapXY.getX(), (double)bitmapXY.getY());
}

Point SOOSA::convertToPoint(TwoDimensionsStatistics::Sample const& sample) const
{
    return Point(sample.getValueAt(0), sample.getValueAt(1));
}

TwoDimensionsStatistics::Sample SOOSA::convertToTwoDimensionSample(Point const& point) const
{
    return TwoDimensionsStatistics::Sample{point.getX(), point.getY()};
}

}

}
