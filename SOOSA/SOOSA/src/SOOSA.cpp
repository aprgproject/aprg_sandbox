#include "SOOSA.hpp"

#include <Common/Bit/AlbaBitManipulation.hpp>
#include <Common/File/AlbaFileReader.hpp>
#include <Common/Math/Helpers/ComputationHelpers.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/Print/AlbaPrintFunctions.hpp>
#include <Common/User/AlbaUserInterface.hpp>
#include <Geometry/TwoDimensions/Circle.hpp>
#include <Geometry/TwoDimensions/TwoDimensionsHelper.hpp>
#include <Statistics/DataStatistics.hpp>
#include <Statistics/FrequencyStatistics.hpp>

#include <iostream>
#include <sstream>



#include <Common/Debug/AlbaDebug.hpp>

using namespace alba::AprgBitmap;
using namespace alba::mathHelper;
using namespace alba::TwoDimensions;
using namespace alba::TwoDimensions::twoDimensionsHelper;
using namespace alba::FrequencyStatistics;
using namespace alba::TwoDimensionsStatistics;
using namespace std;

namespace alba
{

namespace soosa
{

/*namespace // for debug
{
AlbaOptional<AprgBitmap::BitmapSnippet> s_debugSnippetOptional;

void enableDebugSnippet(Bitmap & bitmap)
{
    s_debugSnippetOptional.setConstReference(bitmap.getSnippetReadFromFileWholeBitmap());
}

void writePointInDebug(BitmapXY const& point, unsigned int const color)
{
    BitmapSnippet & debugSnippet(s_debugSnippetOptional.getReference());
    debugSnippet.setPixelAt(BitmapXY(point.getX(), point.getY()), color);
}

void writeLineInDebug(Line const& line, unsigned int const color)
{
    BitmapSnippet & debugSnippet(s_debugSnippetOptional.getReference());
    BitmapXY topLeft(0,0);
    BitmapXY bottomRight(debugSnippet.getConfiguration().getBitmapWidth()-1, debugSnippet.getConfiguration().getBitmapHeight()-1);

    Points points(line.getPoints(Point(topLeft.getX(), topLeft.getY()), Point(bottomRight.getX(), bottomRight.getY()), 1));
    for (Point point: points)
    {
        debugSnippet.setPixelAt(BitmapXY(point.getX(), point.getY()), color);
    }
}

void saveDebugSnippet(Bitmap & bitmap)
{
    BitmapSnippet const& debugSnippet(s_debugSnippetOptional.getConstReference());
    bitmap.setSnippetWriteToFile(debugSnippet);
}
}*/




SOOSA::FrequencyDatabase::FrequencyDatabase(unsigned int const numberOfQuestions, unsigned int const numberOfChoices)
    : m_numberOfQuestions(numberOfQuestions)
    , m_numberOfChoices(numberOfChoices)
{
    initialize();
}

void SOOSA::FrequencyDatabase::initialize()
{
    m_frequenciesOnQuestionByAnswer.clearAndResize(m_numberOfQuestions, m_numberOfChoices);
}

void SOOSA::FrequencyDatabase::addAnswer(unsigned int const questionNumber, unsigned int const answer)
{
    if(m_frequenciesOnQuestionByAnswer.isInside(questionNumber, answer))
    {
        m_frequenciesOnQuestionByAnswer.getEntryReference(questionNumber, answer)++;
    }
}

unsigned int SOOSA::FrequencyDatabase::getFrequencyOfAnswer(unsigned int const questionNumber, unsigned int const answer) const
{
    unsigned int frequency=0;
    if(m_frequenciesOnQuestionByAnswer.isInside(questionNumber, answer))
    {
        frequency = m_frequenciesOnQuestionByAnswer.getEntry(questionNumber, answer);
    }
    return frequency;
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

SOOSA::SOOSA(
        SoosaConfiguration const& soosaConfiguration,
        InputConfiguration const& inputConfiguration)
    : m_soosaConfiguration(soosaConfiguration)
    , m_inputConfiguration(inputConfiguration)
    , m_numberOfRespondents{}
    , m_questionToAnswersMap()
    , m_frequencyDatabase(m_inputConfiguration.getNumberOfQuestions(), m_soosaConfiguration.getNumberOfChoices())
{}

unsigned int SOOSA::getNumberOfAnswers() const
{
    return m_questionToAnswersMap.size();
}

unsigned int SOOSA::getAnswerToQuestion(unsigned int const questionNumber) const
{
    unsigned int result(0xFFFFFFFF);
    auto it = m_questionToAnswersMap.find(questionNumber);
    if(it != m_questionToAnswersMap.cend())
    {
        result = it->second;
    }
    return result;
}

void SOOSA::process()
{
    cout << "Survey Output Optical Scan Analyzer\n" << endl;
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

void SOOSA::processFile(string const& filePath)
{
    cout << endl << "processFile: [" << filePath << "]" << endl;

    Status::getInstance().clearErrors();
    Bitmap bitmap(filePath);
    BitmapSnippet globalSnippet(bitmap.getSnippetReadFromFileWholeBitmap());

    //enableDebugSnippet(bitmap); // debug

    Line leftLine, rightLine, topLine, bottomLine;
    leftLine = findLeftLine(globalSnippet);
    rightLine = findRightLine(globalSnippet);
    topLine = findTopLine(globalSnippet);
    bottomLine = findBottomLine(globalSnippet);
    cout << endl;

    if(m_inputConfiguration.getNumberOfColumns()==2)
    {
        processTwoColumns(globalSnippet, leftLine, rightLine, topLine, bottomLine);
    }
    else
    {
        processOneColumn(globalSnippet, leftLine, rightLine, topLine, bottomLine);
    }

    if(m_inputConfiguration.getNumberOfQuestions() != m_questionToAnswersMap.size())
    {
        performStepsWhenNumberOfAnswersNotEqualToNumberOfQuestions();
    }
    else
    {
        saveFrequencyDatabaseIfNoError();
    }

    //saveDebugSnippet(bitmap); // debug
}

void SOOSA::performStepsWhenNumberOfAnswersNotEqualToNumberOfQuestions() const
{
    cout << "Number of questions does not match the number of answers. Number of questions: " << m_inputConfiguration.getNumberOfQuestions()
         << " Number of answers: "<<m_questionToAnswersMap.size()<<"." << endl;

    stringstream ss;
    ss << "Number of questions does not match the number of answers. Number of questions: " << m_inputConfiguration.getNumberOfQuestions()
       << " Number of answers: "<<m_questionToAnswersMap.size()<<".";
    Status::getInstance().setError(ss.str());
}

void SOOSA::saveFrequencyDatabaseIfNoError(){
    if(Status::getInstance().isStatusNoError())
    {
        m_numberOfRespondents++;        for(unsigned int i=0; i<m_inputConfiguration.getNumberOfQuestions(); i++)
        {
            m_frequencyDatabase.addAnswer(i, getAnswerToQuestion(i)-1);
        }
    }
}

Line SOOSA::findLeftLine(BitmapSnippet const& snippet) const
{
    cout << "findLeftLine:" << endl;    RangeOfInts rangeForX(snippet.getTopLeftCorner().getX(), snippet.getBottomRightCorner().getX(), 1);
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
    Samples samples;
    for(unsigned int y=snippet.getTopLeftCorner().getY(); y<=snippet.getBottomRightCorner().getY(); y++)
    {
        AlbaValueRange<double> consecutiveBlackPixels;
        for(unsigned int x=rangeForX.getStartValue(); conditionForX(x, rangeForX.getEndValue()); x+=rangeForX.getInterval())
        {
            if(isBlackAt(snippet, BitmapXY(x, y)))
            {
                if(consecutiveBlackPixels.isEmpty())
                {
                    consecutiveBlackPixels.setStartValue((double)x);
                }
                consecutiveBlackPixels.setEndValue((double)x);
            }
            else if(!consecutiveBlackPixels.isEmpty())
            {
                samples.emplace_back(Sample{consecutiveBlackPixels.getMidpointValue(), (double)y});
                break;
            }
        }
    }
    return getLineModel(samples);
}

Line SOOSA::findHorizontalLine(BitmapSnippet const& snippet, RangeOfInts const& rangeForY) const
{
    RangeOfInts::TerminationCondition conditionForY(rangeForY.getTerminationCondition());
    Samples samples;
    for(unsigned int x=snippet.getTopLeftCorner().getX(); x<=snippet.getBottomRightCorner().getX(); x++)
    {
        AlbaValueRange<double> consecutiveBlackPixels;
        for(unsigned int y=rangeForY.getStartValue(); conditionForY(y, rangeForY.getEndValue()); y+=rangeForY.getInterval())
        {
            if(isBlackAt(snippet, BitmapXY(x, y)))
            {
                if(consecutiveBlackPixels.isEmpty())
                {
                    consecutiveBlackPixels.setStartValue((double)y);
                }
                consecutiveBlackPixels.setEndValue((double)y);
            }
            else if(!consecutiveBlackPixels.isEmpty())
            {
                samples.emplace_back(Sample{(double)x, consecutiveBlackPixels.getMidpointValue()});
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
    Samples samples;
    for(unsigned int y=snippet.getTopLeftCorner().getY(); y<=snippet.getBottomRightCorner().getY(); y++)
    {
        AlbaValueRange<double> consecutiveBlackPixels;
        double xInLine = round(startingLine.calculateXFromY(y));
        for(int x=(int)xInLine; conditionForX(x, rangeForX.getEndValue()); x+=rangeForX.getInterval())
        {
            if(isBlackAt(snippet, BitmapXY(x, y)))
            {
                if(consecutiveBlackPixels.isEmpty())
                {
                    consecutiveBlackPixels.setStartValue((double)x);
                }
                consecutiveBlackPixels.setEndValue((double)x);
            }
            else if(!consecutiveBlackPixels.isEmpty())
            {
                samples.emplace_back(Sample{consecutiveBlackPixels.getMidpointValue(), (double)y});
                break;
            }
        }
    }
    return getLineModel(samples);
}

Line SOOSA::getLineModel(Samples const & samples) const
{
    int const nonAllowableSquareErrorLimit = m_soosaConfiguration.getAcceptableLineDeviationForLineModelInPixels()
            * m_soosaConfiguration.getAcceptableLineDeviationForLineModelInPixels();

    LineModel lineModel;
    double maxSquareErrorInSamples(nonAllowableSquareErrorLimit);    Samples samplesForLineModeling(samples);
    while(maxSquareErrorInSamples>=nonAllowableSquareErrorLimit && samplesForLineModeling.size() > m_soosaConfiguration.getMinimumLineSamples())
    {
        lineModel = calculateLineModelUsingLeastSquares(samplesForLineModeling);        ValueToSampleMultimap squareErrorToSampleMultimap(getSquareErrorToSampleMultimap(samplesForLineModeling, lineModel));
        VectorOfDoubles acceptableSquareErrors(getAcceptableSquareErrorsUsingRetainRatio(squareErrorToSampleMultimap));
        if(acceptableSquareErrors.size() > m_soosaConfiguration.getMinimumLineSamples())
        {
            ValueToSampleMultimap::iterator itForErase = squareErrorToSampleMultimap.find(acceptableSquareErrors.back());
            squareErrorToSampleMultimap.erase(itForErase, squareErrorToSampleMultimap.end());
            acceptableSquareErrors.pop_back();
            updateSamplesForLineModelingFromSquareErrorToSampleMultimap(samplesForLineModeling, squareErrorToSampleMultimap);
            maxSquareErrorInSamples=acceptableSquareErrors.back();
        }
        else
        {
            break;
        }
    }
    if(samplesForLineModeling.size() < m_soosaConfiguration.getMinimumLineSamples())
    {
        stringstream ss;
        ss << "Line not found because not enough samples. Samples found for line modeling: " <<samplesForLineModeling.size()
           << " Minimum number of samples: " << m_soosaConfiguration.getMinimumLineSamples() << ".";
        Status::getInstance().setError(ss.str());
        cout << "getLineModel -> Not enough samples: " << samplesForLineModeling.size() << endl;
    }
    else
    {
        cout << "getLineModel -> Successful! Number of successful samples: " << samplesForLineModeling.size()
             << ", number of minimum samples: " << m_soosaConfiguration.getMinimumLineSamples() << endl;
        cout << "getLineModel -> Line model coordinates: a=" << lineModel.aCoefficient
             << " b=" << lineModel.bCoefficient
             << " c=" << lineModel.cCoefficient << endl;
    }
    return Line(lineModel.aCoefficient, lineModel.bCoefficient, lineModel.cCoefficient);
}

SOOSA::VectorOfDoubles SOOSA::getAcceptableSquareErrorsUsingRetainRatio(
        ValueToSampleMultimap const& squareErrorToSampleMultimap) const
{
    VectorOfDoubles squareErrors;
    unsigned int retainSize = m_soosaConfiguration.getRetainRatioForSquareErrorsInLineModel() * squareErrorToSampleMultimap.size();
    unsigned int count(0);
    for(auto const& squareErrorToSamplePair : squareErrorToSampleMultimap)
    {        squareErrors.emplace_back(squareErrorToSamplePair.first);
        if(count++ >= retainSize)
        {
            break;        }
    }
    return squareErrors;
}

void SOOSA::updateSamplesForLineModelingFromSquareErrorToSampleMultimap(
        Samples & samplesLineModeling,
        ValueToSampleMultimap const& squareErrorToSampleMultimap) const
{
    samplesLineModeling.clear();
    transform(squareErrorToSampleMultimap.cbegin(), squareErrorToSampleMultimap.cend(), back_inserter(samplesLineModeling),
              [](ValueToSamplePair const& squareErrorToSamplePair)
    {
        return squareErrorToSamplePair.second;
    });
}

void SOOSA::processTwoColumns(
        BitmapSnippet const& globalSnippet,
        Line const& leftLine,
        Line const& rightLine,
        Line const& topLine,
        Line const& bottomLine)
{
    cout << "Number of columns from template = 2" << endl;

    Point edgePoints[2][3];
    edgePoints[0][0] = getIntersectionOfTwoLines(leftLine, topLine);
    edgePoints[0][2] = getIntersectionOfTwoLines(rightLine, topLine);
    edgePoints[1][0] = getIntersectionOfTwoLines(leftLine, bottomLine);
    edgePoints[1][2] = getIntersectionOfTwoLines(rightLine, bottomLine);
    edgePoints[0][1] = getMidpoint(edgePoints[0][0], edgePoints[0][2]);
    edgePoints[1][1] = getMidpoint(edgePoints[1][0], edgePoints[1][2]);

    Line centerLine(edgePoints[0][1], edgePoints[1][1]);

    cout << "find center left line:" << endl;
    Line centerLeftLine = findRightLineUsingStartingLine(globalSnippet, centerLine);

    cout << "find center right line:" << endl;
    Line centerRightLine = findLeftLineUsingStartingLine(globalSnippet, centerLine);

    cout << endl << "Processing column 1:" << endl;
    processColumn(globalSnippet, leftLine, centerLeftLine, topLine, bottomLine, 1);

    cout << endl << "Processing column 2:" << endl;
    processColumn(globalSnippet, centerRightLine, rightLine, topLine, bottomLine, 2);
}

void SOOSA::processOneColumn(
        BitmapSnippet const& globalSnippet,
        Line const& leftLine,
        Line const& rightLine,
        Line const& topLine,
        Line const& bottomLine)
{
    cout << "Number of columns from template = 1" << endl;

    cout << "Processing column:" << endl;
    processColumn(globalSnippet, leftLine, rightLine, topLine, bottomLine, 1);
}

void SOOSA::processColumn(
        BitmapSnippet const& snippet,
        Line const& leftLine,        Line const& rightLine,
        Line const& topLine,
        Line const& bottomLine,
        unsigned int const columnNumber)
{    Point topLeft = getIntersectionOfTwoLines(leftLine, topLine);
    Point topRight = getIntersectionOfTwoLines(rightLine, topLine);
    Point bottomLeft = getIntersectionOfTwoLines(leftLine, bottomLine);
    Point bottomRight = getIntersectionOfTwoLines(rightLine, bottomLine);

    unsigned int numberQuestionsInColumn = m_inputConfiguration.getNumberOfQuestionsAtColumn(columnNumber);
    cout << "Processing left line of column:" << endl;
    QuestionBarCoordinates questionBarsOnTheLeft
            = getQuestionBarCoordinatesFromLine(snippet, leftLine, topLeft, bottomLeft, numberQuestionsInColumn);
    cout << "Processing right line of column:" << endl;
    QuestionBarCoordinates questionsBarsOnTheRight
            = getQuestionBarCoordinatesFromLine(snippet, rightLine, topRight, bottomRight, numberQuestionsInColumn);
    if(questionBarsOnTheLeft.size() == numberQuestionsInColumn && questionsBarsOnTheRight.size() == numberQuestionsInColumn)
    {
        processQuestions(snippet, questionBarsOnTheLeft, questionsBarsOnTheRight, columnNumber, numberQuestionsInColumn);
    }
    else
    {        stringstream ss;
        ss<< "Number of question coordinates does not match between columns. "
          << "Question bars at left line: " << questionBarsOnTheLeft.size()
          << "Question bars at right line: " << questionsBarsOnTheRight.size() << ".";        Status::getInstance().setError(ss.str());
        cout << "processColumn -> Questions coordinates does not match. "
             << "Left line: " << questionBarsOnTheLeft.size()
             << " Right Line: " <<questionsBarsOnTheRight.size()
             << " Number of questions in the column: " << numberQuestionsInColumn << endl;
    }
}

void SOOSA::processQuestions(
        BitmapSnippet const& snippet,
        QuestionBarCoordinates const& questionBarsOnTheLeft,
        QuestionBarCoordinates const& questionsBarsOnTheRight,
        unsigned int const columnNumber,
        unsigned int const numberQuestionsInColumn)
{
    for(unsigned int questionIndex=0; questionIndex<numberQuestionsInColumn; questionIndex++)
    {
        Answers answers = getAnswersAtQuestion(snippet, questionBarsOnTheLeft[questionIndex], questionsBarsOnTheRight[questionIndex]);
        if(answers.size() == 1)
        {
            cout << "processColumn -> Question number: " << questionIndex+1 << " Answer: " << answers.front() << endl;
            setAnswerToQuestionInColumn(columnNumber, questionIndex, answers.front());
        }
        else
        {
            stringstream ss;
            cout << "processColumn -> Problem locating answer in question number: " << questionIndex+1 << ", column number: " << columnNumber << endl;
            cout << "processColumn -> Answers: ";
            printParameter(cout, answers);
            cout << endl;
            ss << "Problem locating choices in a question. Question number: " << questionIndex+1 << " Answers: ";
            printParameter(ss, answers);
            ss << ".";
            Status::getInstance().setError(ss.str());
        }
    }
}

SOOSA::Answers SOOSA::getAnswersAtQuestion(
        BitmapSnippet const& snippet,
        QuestionBarCoordinate const& leftCoordinate,
        QuestionBarCoordinate const& rightCoordinate) const
{    Answers result;
    Point leftPoint = getMidpoint(leftCoordinate.first, leftCoordinate.second);
    Point rightPoint = getMidpoint(rightCoordinate.first, rightCoordinate.second);
    double leftBarHeight = getDistance(leftCoordinate.first, leftCoordinate.second);    double rightBarHeight = getDistance(rightCoordinate.first, rightCoordinate.second);
    double lowestHeightOfQuestion = min(leftBarHeight, rightBarHeight);
    double radius = lowestHeightOfQuestion * m_soosaConfiguration.getRatioOfBarHeightToDiameter()/2;
    unsigned int numberOfChoices = m_soosaConfiguration.getNumberOfChoices();
    for(unsigned int choiceIndex=0; choiceIndex<numberOfChoices; choiceIndex++ )
    {
        if(isChoiceShaded(snippet, leftPoint, rightPoint, choiceIndex, static_cast<unsigned int>(radius)))
        {
            result.emplace_back(numberOfChoices-choiceIndex);
        }
    }
    return result;
}

bool SOOSA::isChoiceShaded(
        BitmapSnippet const& snippet,
        Point const& leftPoint,
        Point const& rightPoint,
        unsigned int const choiceIndex,
        unsigned int const radius) const
{
    double choiceIndexRatio = (((double)choiceIndex*2)+1) / (m_soosaConfiguration.getNumberOfChoices()*2);
    double differenceFromLeftToRightInX = rightPoint.getX() - leftPoint.getX();
    double differenceFromLeftToRightInY = rightPoint.getY() - leftPoint.getY();
    Point centerOfCircle(leftPoint.getX()+(differenceFromLeftToRightInX*choiceIndexRatio), leftPoint.getY()+(differenceFromLeftToRightInY*choiceIndexRatio));
    unsigned int totalPoints(0), numberOfBlackPoints(0);
    Circle circle(centerOfCircle, radius);
    circle.traverseArea(1, [&](Point const& pointInCircle)
    {
        numberOfBlackPoints += (isBlackAt(snippet, convertToBitmapXY(pointInCircle))) ? 1 : 0;
        totalPoints++;
    });
    return ((double)numberOfBlackPoints/totalPoints) >= m_soosaConfiguration.getMinimumPercentageOfBlackPixelsForAFilledCircle();
}

SOOSA::QuestionBarCoordinates SOOSA::getQuestionBarCoordinatesFromLine(
        BitmapSnippet const& snippet,
        Line const& line,
        Point const& startPoint,
        Point const& endPoint,
        unsigned int const numberQuestionsInColumn) const
{
    QuestionBarCoordinates questionBarCoordinates;
    PointAndWidthPairs pointAndWidthPairs(getAcceptablePointAndWidthPairs(snippet, line, startPoint, endPoint));

    if(!pointAndWidthPairs.empty())
    {
        RangeOfDoubles minMaxCriteriaForBar(getMinMaxCriteriaForBar(pointAndWidthPairs));
        ALBA_PRINT2(minMaxCriteriaForBar.getMinimum(), minMaxCriteriaForBar.getMaximum());
        TwoDimensionKMeans barPointKMeans;
        retrieveBarPointsThatFitAndSaveToKMeans(barPointKMeans, pointAndWidthPairs, minMaxCriteriaForBar);
        ALBA_PRINT1(barPointKMeans.getSamples().size());
        removeIncorrectBarPointsBasedFromHeight(barPointKMeans, numberQuestionsInColumn);
        ALBA_PRINT1(barPointKMeans.getSamples().size());
        saveQuestionBarCoordinatesFromKMeansWithBarPoints(questionBarCoordinates, barPointKMeans, numberQuestionsInColumn);
        ALBA_PRINT1(questionBarCoordinates.size());
    }
    cout << "getQuestionBarCoordinatesFromLine -> Number of question bar coordinates: " << questionBarCoordinates.size() << endl;
    return questionBarCoordinates;
}

void SOOSA::retrieveBarPointsThatFitAndSaveToKMeans(
        TwoDimensionKMeans & barPointKMeans,
        PointAndWidthPairs const& pointAndWidthPairs,
        RangeOfDoubles const& minMaxCriteriaForBar) const
{
    for(PointAndWidthPair const& pointAndWidthPair : pointAndWidthPairs)
    {
        if(minMaxCriteriaForBar.isValueInsideInclusive(pointAndWidthPair.second))
        {
            barPointKMeans.addSample(convertToTwoDimensionSample(pointAndWidthPair.first));
        }
    }
}

void SOOSA::saveQuestionBarCoordinatesFromKMeansWithBarPoints(
        QuestionBarCoordinates & questionBarCoordinates,
        TwoDimensionKMeans const& barPointKMeans,
        unsigned int const numberQuestionsInColumn) const
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

SOOSA::RangeOfDoubles SOOSA::getMinMaxCriteriaForBar(
        PointAndWidthPairs const& pointAndWidthPairs) const
{
    RangeOfDoubles result;

    OneDimensionKMeans kMeansForWidths(getKMeansForWidths(pointAndWidthPairs));
    bool needsRemoval(true);
    while(needsRemoval)
    {
        OneDimensionKMeans::GroupOfSamples twoGroupsOfSamples(kMeansForWidths.getGroupOfSamplesUsingKMeans(2));
        OneDimensionStatistics firstGroupStatistics(twoGroupsOfSamples.at(0));
        OneDimensionStatistics secondGroupStatistics(twoGroupsOfSamples.at(1));
        double firstSdOverMean = firstGroupStatistics.getSampleStandardDeviation().getValueAt(0)/firstGroupStatistics.getMean().getValueAt(0);
        double secondSdOverMean = secondGroupStatistics.getSampleStandardDeviation().getValueAt(0)/secondGroupStatistics.getMean().getValueAt(0);

        needsRemoval = firstSdOverMean > m_soosaConfiguration.getAcceptableSdOverMeanDeviationForLine()
                || secondSdOverMean > m_soosaConfiguration.getAcceptableSdOverMeanDeviationForBar();
        if(needsRemoval)
        {
            kMeansForWidths.clear();
            addAndRetainWidthsIfPossible(kMeansForWidths, firstGroupStatistics, m_soosaConfiguration.getAcceptableSdOverMeanDeviationForLine());
            addAndRetainWidthsIfPossible(kMeansForWidths, secondGroupStatistics, m_soosaConfiguration.getAcceptableSdOverMeanDeviationForBar());
        }
        else
        {
            result = getMinMaxCriteriaForBar(firstGroupStatistics, secondGroupStatistics);
        }
    }

    return result;
}

SOOSA::RangeOfDoubles SOOSA::getMinMaxCriteriaForBar(
        OneDimensionStatistics & firstGroupStatistics,
        OneDimensionStatistics & secondGroupStatistics) const
{
    RangeOfDoubles result;
    if(firstGroupStatistics.getMean().getValueAt(0) > secondGroupStatistics.getMean().getValueAt(0))
    {
        result = getMinMaxRangeOfKMeansSamples(firstGroupStatistics.getSamples());
    }
    else
    {
        result = getMinMaxRangeOfKMeansSamples(secondGroupStatistics.getSamples());
    }
    return result;
}

SOOSA::OneDimensionKMeans SOOSA::getKMeansForWidths(
        PointAndWidthPairs const& pointAndWidthPairs) const
{
    OneDimensionKMeans result;
    for(PointAndWidthPair const& pointAndWidthPair : pointAndWidthPairs)
    {
        result.addSample(OneDimensionStatistics::Sample{pointAndWidthPair.second});
    }
    return result;
}

SOOSA::PointAndWidthPairs SOOSA::getAcceptablePointAndWidthPairs(        BitmapSnippet const& snippet,
        Line const& line,
        Point const& startPoint,
        Point const& endPoint) const{
    Points pointsInLine(line.getPoints(startPoint, endPoint, 1));
    PointAndWidthPairs pointAndWidthPairs;
    for(Point const& pointInLine : pointsInLine)
    {
        addPointAndWidthPairIfAcceptable(pointAndWidthPairs, snippet, line, pointInLine);
    }
    return pointAndWidthPairs;
}

void SOOSA::addPointAndWidthPairIfAcceptable(
        PointAndWidthPairs & pointAndWidthPairs,
        BitmapSnippet const& snippet,        Line const& line,
        Point const& pointInLine) const
{
    Point nearestBlackPoint(getNearestBlackPointFromLine(snippet, line, pointInLine));    Line perpendicularLine(getLineWithPerpendicularSlope(line, nearestBlackPoint));
    Point leftMostBlack(nearestBlackPoint);
    Point rightMostBlack(nearestBlackPoint);
    bool isBlack(true);
    for(unsigned int offset=1; offset<=m_soosaConfiguration.getMaximumLineAndBarWidth() && isBlack; offset++)
    {
        double possibleBlackPointInX = nearestBlackPoint.getX()-offset;
        Point possibleBlackPoint(possibleBlackPointInX, perpendicularLine.calculateYFromX(possibleBlackPointInX));
        isBlack = isBlackAt(snippet, convertToBitmapXY(possibleBlackPoint));
        if(isBlack)
        {
            leftMostBlack=possibleBlackPoint;
        }
    }
    isBlack = true;
    for(unsigned int offset=1; offset<=m_soosaConfiguration.getMaximumLineAndBarWidth() && isBlack; offset++)
    {
        double possibleBlackPointInX = nearestBlackPoint.getX()+offset;
        Point possibleBlackPoint(possibleBlackPointInX, perpendicularLine.calculateYFromX(possibleBlackPointInX));
        isBlack = isBlackAt(snippet, convertToBitmapXY(possibleBlackPoint));
        if(isBlack)
        {
            rightMostBlack=possibleBlackPoint;
        }
    }
    double width = getDistance(leftMostBlack, rightMostBlack);
    Point widthMidPoint = getMidpoint(leftMostBlack, rightMostBlack);
    double acceptableDistance = m_soosaConfiguration.getAcceptableDistanceOverWidthRatioFromWidthMidpoint() * width
            + m_soosaConfiguration.getAcceptableMinimumDistanceFromWidthMidpoint();
    double distanceFromLine = getDistance(pointInLine, widthMidPoint);
    if(distanceFromLine < acceptableDistance)
    {
        pointAndWidthPairs.emplace_back(pointInLine, width);
    }
}

Point SOOSA::getNearestBlackPointFromLine(BitmapSnippet const& snippet, Line const& line, Point const& pointInLine) const
{
    Point blackPoint;
    Line perpendicularLine(getLineWithPerpendicularSlope(line, pointInLine));
    for(unsigned int deviation=1; deviation<=m_soosaConfiguration.getMaximumLineAndBarWidth(); deviation++)
    {
        double lowerDeviatedInX = pointInLine.getX()-deviation;
        Point lowerDeviatedPoint(lowerDeviatedInX, perpendicularLine.calculateYFromX(lowerDeviatedInX));
        if(isBlackAt(snippet, convertToBitmapXY(lowerDeviatedPoint)))
        {
            blackPoint = lowerDeviatedPoint;
            break;
        }
        double higherDeviatedInX = pointInLine.getX()+deviation;
        Point higherDeviatedPoint(higherDeviatedInX, perpendicularLine.calculateYFromX(higherDeviatedInX));
        if(isBlackAt(snippet, convertToBitmapXY(higherDeviatedPoint)))
        {
            blackPoint = higherDeviatedPoint;
            break;
        }
    }
    return blackPoint;
}

void SOOSA::addAndRetainWidthsIfPossible(
        OneDimensionKMeans & kMeansForWidths,
        OneDimensionStatistics & groupStatistics,
        double const acceptableSdOverMeanDeviation) const
{
    OneDimensionKMeans::Samples const& group(groupStatistics.getSamples());
    double sdOverMean = groupStatistics.getSampleStandardDeviation().getValueAt(0)/groupStatistics.getMean().getValueAt(0);
    if(sdOverMean > acceptableSdOverMeanDeviation)
    {
        double widthMean = groupStatistics.getMean().getValueAt(0);
        multimap<double, double> deviationToWidthMultimap;
        for(OneDimensionKMeans::Sample const& widthSample : group)
        {
            double width(widthSample.getValueAt(0));
            deviationToWidthMultimap.emplace(getAbsoluteValue(width - widthMean), width);
        }

        unsigned int retainSize = m_soosaConfiguration.getRetainRatioForLineAndBar() * deviationToWidthMultimap.size();
        unsigned int count(0);
        for(auto const& deviationAndWidthPair : deviationToWidthMultimap)
        {
            kMeansForWidths.addSample(OneDimensionKMeans::Sample{deviationAndWidthPair.second});
            if(count++ >= retainSize)
            {
                break;
            }
        }
    }
    else
    {
        kMeansForWidths.addSamples(group);
    }
}

void SOOSA::removeIncorrectBarPointsBasedFromHeight(        TwoDimensionKMeans & barPointKMeans,
        unsigned int const numberQuestionsInColumn) const
{
    bool continueRemoval(true);    while(continueRemoval)
    {
        TwoDimensionKMeans::GroupOfSamples listOfGroupOfBarPoints(barPointKMeans.getGroupOfSamplesUsingKMeans(numberQuestionsInColumn));
        OneDimensionStatistics::Samples barHeights(getBarHeights(listOfGroupOfBarPoints));
        OneDimensionStatistics barHeightsStatistics(barHeights);
        double mean = barHeightsStatistics.getMean().getValueAt(0);
        double sd = barHeightsStatistics.getSampleStandardDeviation().getValueAt(0);
        double sdOverMean = sd/mean;
        continueRemoval = sdOverMean > m_soosaConfiguration.getAcceptableSdOverMeanDeviationForBarHeight();
        if(continueRemoval)
        {
            bool isFound(false);
            double largestDeviation(0);
            unsigned int indexToRemove(0);
            for(unsigned int groupIndex=0; groupIndex<listOfGroupOfBarPoints.size(); groupIndex++)
            {
                TwoDimensionKMeans::Samples const& currentGroup(listOfGroupOfBarPoints.at(groupIndex));
                if(!currentGroup.empty())
                {
                    double barHeight = getDistance(convertToPoint(currentGroup.front()), convertToPoint(currentGroup.back()));
                    double signedDeviation = barHeight-mean; // no absolute value because only positive deviation should be removed
                    if(largestDeviation == 0 || largestDeviation < signedDeviation)
                    {
                        isFound = true;
                        largestDeviation = signedDeviation;
                        indexToRemove = groupIndex;
                    }
                }
            }
            if(isFound)
            {
                continueRemoval = false;
                barPointKMeans.clear();
                for(unsigned int groupIndex=0; groupIndex<listOfGroupOfBarPoints.size(); groupIndex++)
                {
                    TwoDimensionKMeans::Samples const& barPointsSamples(listOfGroupOfBarPoints.at(groupIndex));
                    if(groupIndex == indexToRemove)
                    {
                        TwoDimensionStatistics barPointsStatistics(barPointsSamples);
                        Point center = convertToPoint(barPointsStatistics.getMean());

                        multimap<double, Point> deviationToPointMultimap;
                        for(TwoDimensionKMeans::Sample const& barPointsSample : barPointsSamples)
                        {
                            Point barPoint = convertToPoint(barPointsSample);
                            deviationToPointMultimap.emplace(getDistance(center, barPoint), barPoint);
                        }

                        Points acceptedBarPoints;
                        unsigned int retainSize = m_soosaConfiguration.getRetainRatioForBarHeight() * barPointsSamples.size();
                        for(auto const& deviationAndPointPair : deviationToPointMultimap)
                        {
                            acceptedBarPoints.emplace_back(deviationAndPointPair.second);
                            if(acceptedBarPoints.size() >= retainSize)
                            {
                                break;
                            }
                        }
                        sort(acceptedBarPoints.begin(), acceptedBarPoints.end(), [](Point const& point1, Point const& point2)
                        {
                            return point1.getY() < point2.getY();
                        });
                        for(Point const& acceptedBarPoint : acceptedBarPoints)
                        {
                            barPointKMeans.addSample(convertToTwoDimensionSample(acceptedBarPoint));
                        }
                        continueRemoval = acceptedBarPoints.size() != barPointsSamples.size();
                    }
                    else
                    {
                        barPointKMeans.addSamples(barPointsSamples);
                    }
                }
            }
        }
    }
}

SOOSA::OneDimensionStatistics::Samples SOOSA::getBarHeights(
        TwoDimensionKMeans::GroupOfSamples const & groupOfGroupOfBarPoints) const
{
    OneDimensionStatistics::Samples barHeights;
    for(TwoDimensionKMeans::Samples const& groupOfBarPoints : groupOfGroupOfBarPoints)
    {
        if(!groupOfBarPoints.empty())
        {
            double height = getDistance(convertToPoint(groupOfBarPoints.front()), convertToPoint(groupOfBarPoints.back()));
            barHeights.emplace_back(OneDimensionStatistics::Sample{(double)height});
        }
    }
    return barHeights;
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
        for(unsigned int i=0; i<m_inputConfiguration.getNumberOfQuestions(); i++)
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
        FrequencySamples samples;
        for(unsigned int answerIndex=0; answerIndex<m_soosaConfiguration.getNumberOfChoices(); answerIndex++)
        {
            samples[answerIndex+1] = m_frequencyDatabase.getFrequencyOfAnswer(questionIndex, answerIndex);
        }
        unsigned int numberOfSamplesForQuestion = calculateNumberOfSamples(samples);
        double median = calculateMedian(samples);
        if(questionIndex==m_inputConfiguration.getNumberOfQuestions()-1)
        {
            reportHtmlFileStream<<"<td style=\"text-align:left;padding:3px\"><b>"<<m_inputConfiguration.getQuestionAt(questionIndex)<<"</b></td>"<<endl;
        }
        else
        {
            reportHtmlFileStream<<"<td style=\"text-align:left;padding:3px\">"<<m_inputConfiguration.getQuestionAt(questionIndex)<<"</td>"<<endl;
        }
        for(unsigned int answer=m_soosaConfiguration.getNumberOfChoices(); answer>0; answer--)
        {
            reportHtmlFileStream<<"<td style=\"text-align:center;padding:3px\">"
                               <<getPrintableStringForPercentage(m_frequencyDatabase.getFrequencyOfAnswer(questionIndex, answer-1), numberOfSamplesForQuestion)
                              <<"</td>"<<endl;
        }
        reportHtmlFileStream<<"<td style=\"text-align:center;padding:3px\">"<<numberOfSamplesForQuestion<<"</td>"<<endl;
        reportHtmlFileStream<<"<td style=\"text-align:center;padding:3px\">"<<median<<"</td>"<<endl;

        unsigned int satisfactoryFrequency(0);
        for(unsigned int answer=m_soosaConfiguration.getNumberOfChoices(); answer>0; answer--)
        {
            if(answer>=m_inputConfiguration.getMinimumSatisfactoryScore())
            {
                satisfactoryFrequency += m_frequencyDatabase.getFrequencyOfAnswer(questionIndex, answer-1);
            }
        }
        reportHtmlFileStream << "<td style=\"text-align:center;padding:3px\">"
                            << getPrintableStringForPercentage(satisfactoryFrequency, numberOfSamplesForQuestion)
                          << "</td>"<<endl;
        reportHtmlFileStream<<"</tr>"<<endl;
    }
}

bool SOOSA::isBlackAt(BitmapSnippet const& snippet, BitmapXY const bitmapXy) const
{
    using BitColorManip = AlbaBitManipulation<uint32_t>;    uint32_t color = snippet.getColorAt(bitmapXy);
    uint32_t minColorIntensity = min(BitColorManip::getByteAt<0>(color), min(BitColorManip::getByteAt<1>(color), BitColorManip::getByteAt<2>(color)));

    return minColorIntensity < m_soosaConfiguration.getColorIntensityForWhite();}

BitmapXY SOOSA::convertToBitmapXY(Point const& point) const
{
    return BitmapXY((unsigned int)round(clampLowerBound(point.getX(), (double)0)), (unsigned int)round(clampLowerBound(point.getY(), (double)0)));
}

BitmapXY SOOSA::convertToBitmapXY(Sample const& sample) const
{
    return BitmapXY((unsigned int)round(clampLowerBound(sample.getValueAt(0), (double)0)), (unsigned int)round(clampLowerBound(sample.getValueAt(1), (double)0)));
}

Point SOOSA::convertToPoint(BitmapXY const& bitmapXY) const
{
    return Point((double)bitmapXY.getX(), (double)bitmapXY.getY());
}

Point SOOSA::convertToPoint(Sample const& sample) const
{
    return Point(sample.getValueAt(0), sample.getValueAt(1));
}

Sample SOOSA::convertToTwoDimensionSample(Point const& point) const
{
    return Sample{point.getX(), point.getY()};
}

SOOSA::RangeOfDoubles SOOSA::getMinMaxRangeOfKMeansSamples(OneDimensionKMeans::Samples const& samples) const
{
    DataCollection<double> collection;
    for(OneDimensionKMeans::Sample const& sample : samples)
    {
        collection.addData(sample.getValueAt(0));
    }
    return RangeOfDoubles(collection.getMinimum(), collection.getMaximum(), 1);
}

}

}