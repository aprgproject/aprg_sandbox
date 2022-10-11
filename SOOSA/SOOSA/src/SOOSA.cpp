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

#include <algorithm>
#include <iostream>
#include <sstream>

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
AlbaOptional<BitmapSnippet> s_debugSnippetOptional;

void enableDebugSnippet(Bitmap const& bitmap)
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

void saveDebugSnippet(Bitmap const& bitmap)
{
    Bitmap bitmapCopy(bitmap);
    BitmapSnippet const& debugSnippet(s_debugSnippetOptional.getConstReference());
    bitmapCopy.setSnippetWriteToFile(debugSnippet);
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

void SOOSA::FrequencyDatabase::addAnswer(unsigned int const questionIndex, unsigned int const answerIndex)
{
    if(m_frequenciesOnQuestionByAnswer.isInside(questionIndex, answerIndex))
    {
        m_frequenciesOnQuestionByAnswer.getEntryReference(questionIndex, answerIndex)++;
    }
}

unsigned int SOOSA::FrequencyDatabase::getFrequencyOfAnswer(unsigned int const questionIndex, unsigned int const answerIndex) const
{
    unsigned int frequency=0;
    if(m_frequenciesOnQuestionByAnswer.isInside(questionIndex, answerIndex))
    {
        frequency = m_frequenciesOnQuestionByAnswer.getEntry(questionIndex, answerIndex);
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

unsigned int SOOSA::getAnswerToQuestion(unsigned int const questionIndex) const
{
    unsigned int result(0);
    auto it = m_questionToAnswersMap.find(questionIndex);
    if(it != m_questionToAnswersMap.cend())
    {
        result = it->second;
    }
    return result;
}

void SOOSA::process()
{
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

    cout << endl;
    saveOutputHtmlFile(pathHandler.getFullPath());
}

void SOOSA::processDirectory(string const& directoryPath)
{
    cout << "processDirectory: [" << directoryPath << "]" << endl;
    AlbaLocalPathHandler directoryPathToBeProcessed(directoryPath);
    set<string> listOfFiles;
    set<string> listOfDirectories;
    directoryPathToBeProcessed.findFilesAndDirectoriesUnlimitedDepth("*.bmp", listOfFiles, listOfDirectories);

    for(string const& filePath : listOfFiles)
    {
        processFile(filePath);
        saveDataToCsvFile(filePath);
    }
}

void SOOSA::processFile(string const& filePath)
{
    cout << endl << "processFile: [" << filePath << "]" << endl;

    m_questionToAnswersMap.clear();
    Bitmap bitmap(filePath);
    if(bitmap.getConfiguration().isValid())
    {
        processBitmapFile(bitmap);
    }
    else
    {
        stringstream ss;
        ss << "File is an invalid bitmap.";
        Status::getInstance().setError(ss.str());
        cout << "File is an invalid bitmap so its ignored. File path: [" << bitmap.getConfiguration().getPath() << "]" << endl;
    }
}

void SOOSA::processBitmapFile(Bitmap const& bitmap)
{
    //enableDebugSnippet(bitmap); // debug

    Status::getInstance().clearErrors();
    BitmapSnippet globalSnippet(bitmap.getSnippetReadFromFileWholeBitmap());

    Line emptyLine;
    Line leftLine, rightLine, topLine, bottomLine;
    leftLine = findLeftLine(globalSnippet);
    rightLine = findRightLine(globalSnippet);
    topLine = findTopLine(globalSnippet);
    bottomLine = findBottomLine(globalSnippet);
    //writeLineInDebug(leftLine, 0x0000EE);
    //writeLineInDebug(rightLine, 0x0000EE);
    //writeLineInDebug(topLine, 0x0000EE);
    //writeLineInDebug(bottomLine, 0x0000EE);

    if(emptyLine != leftLine && emptyLine != rightLine && emptyLine != topLine && emptyLine != bottomLine)
    {
        if(m_inputConfiguration.getNumberOfColumns()==2)
        {
            processTwoColumns(globalSnippet, leftLine, rightLine, topLine, bottomLine);
        }
        else
        {
            processOneColumn(globalSnippet, leftLine, rightLine, topLine, bottomLine);
        }
        saveToFrequencyDatabase();
    }
    else
    {
        cout << "Lines are invalid. " << endl;
    }

    //saveDebugSnippet(bitmap); // debug
}

void SOOSA::saveToFrequencyDatabase()
{
    m_numberOfRespondents++;
    for(unsigned int i=0; i<m_inputConfiguration.getNumberOfQuestions(); i++)
    {
        m_frequencyDatabase.addAnswer(i, getAnswerToQuestion(i)-1);
    }
}

Line SOOSA::findLeftLine(BitmapSnippet const& snippet) const
{
    RangeOfInts rangeForX(snippet.getTopLeftCorner().getX(), snippet.getBottomRightCorner().getX(), 1);
    return findVerticalLine(snippet, rangeForX);
}

Line SOOSA::findRightLine(BitmapSnippet const& snippet) const
{
    RangeOfInts rangeForX(snippet.getBottomRightCorner().getX(), snippet.getTopLeftCorner().getX(), -1);
    return findVerticalLine(snippet, rangeForX);
}

Line SOOSA::findTopLine(BitmapSnippet const& snippet) const
{
    RangeOfInts rangeForY(snippet.getTopLeftCorner().getY(), snippet.getBottomRightCorner().getY(), 1);
    return findHorizontalLine(snippet, rangeForY);
}

Line SOOSA::findBottomLine(BitmapSnippet const& snippet) const
{
    RangeOfInts rangeForY(snippet.getBottomRightCorner().getY(), snippet.getTopLeftCorner().getY(), -1);
    return findHorizontalLine(snippet, rangeForY);
}

Line SOOSA::findVerticalLine(BitmapSnippet const& snippet, RangeOfInts const& rangeForX) const
{
    RangeOfInts::TerminationCondition conditionForX(rangeForX.getTerminationCondition());
    TwoDimensionSamples samples;
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
                samples.emplace_back(TwoDimensionSample{consecutiveBlackPixels.getMidpointValue(), (double)y});
                break;
            }
        }
    }
    return getLineModel(samples);
}

Line SOOSA::findHorizontalLine(BitmapSnippet const& snippet, RangeOfInts const& rangeForY) const
{
    RangeOfInts::TerminationCondition conditionForY(rangeForY.getTerminationCondition());
    TwoDimensionSamples samples;
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
                samples.emplace_back(TwoDimensionSample{(double)x, consecutiveBlackPixels.getMidpointValue()});
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
    TwoDimensionSamples samples;
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
                samples.emplace_back(TwoDimensionSample{consecutiveBlackPixels.getMidpointValue(), (double)y});
                break;
            }
        }
    }
    return getLineModel(samples);
}

Line SOOSA::getLineModel(TwoDimensionSamples const & samples) const
{
    int const nonAllowableSquareErrorLimit = m_soosaConfiguration.getAcceptableLineDeviationForLineModelInPixels()
            * m_soosaConfiguration.getAcceptableLineDeviationForLineModelInPixels();

    LineModel lineModel;
    TwoDimensionSamples samplesForLineModeling(samples);
    bool continueRemoval(true);
    while(continueRemoval)
    {
        lineModel = calculateLineModelUsingLeastSquares(samplesForLineModeling);
        ValueToTwoDimensionSampleMultimap squareErrorToSampleMultimap = getSquareErrorToSampleMultimap(samplesForLineModeling, lineModel);
        DoubleCollection acceptableSquareErrorCollection = getAcceptableSquareErrorCollectionUsingRemovalRatio(squareErrorToSampleMultimap);

        continueRemoval = acceptableSquareErrorCollection.getCount() > m_soosaConfiguration.getMinimumLineSamples()
                && acceptableSquareErrorCollection.getMaximum() >= nonAllowableSquareErrorLimit;

        if(continueRemoval)
        {
            unsigned int sizeBefore = samplesForLineModeling.size();
            updateSamplesForLineModeling(samplesForLineModeling, squareErrorToSampleMultimap, acceptableSquareErrorCollection.getMaximum());
            continueRemoval = sizeBefore > samplesForLineModeling.size();
        }
    }
    if(samplesForLineModeling.size() < m_soosaConfiguration.getMinimumLineSamples())
    {
        stringstream ss;
        ss << "Line not found because not enough samples. Samples found for line modeling: " <<samplesForLineModeling.size()
           << " Minimum number of samples: " << m_soosaConfiguration.getMinimumLineSamples() << ".";
        Status::getInstance().setError(ss.str());
        cout << "Line not found because not enough samples. Samples found: " << samplesForLineModeling.size() << endl;
    }
    return Line(lineModel.aCoefficient, lineModel.bCoefficient, lineModel.cCoefficient);
}

SOOSA::DoubleCollection SOOSA::getAcceptableSquareErrorCollectionUsingRemovalRatio(
        ValueToTwoDimensionSampleMultimap const& squareErrorToSampleMultimap) const
{
    DoubleCollection squareErrorCollection;
    unsigned int removalSize = ceil(m_soosaConfiguration.getRemovalRatioForSquareErrorsInLineModel() * squareErrorToSampleMultimap.size());
    unsigned int retainSize = clampHigherBound(squareErrorToSampleMultimap.size() - removalSize, squareErrorToSampleMultimap.size());
    unsigned int count = 0;
    for(auto const& squareErrorToSamplePair : squareErrorToSampleMultimap)
    {
        squareErrorCollection.addData(squareErrorToSamplePair.first);
        if(count++ >= retainSize)
        {
            break;
        }
    }
    return squareErrorCollection;
}

void SOOSA::updateSamplesForLineModeling(
        TwoDimensionSamples & samplesLineModeling,
        ValueToTwoDimensionSampleMultimap const& squareErrorToSampleMultimap,
        double const maxAcceptableSquareError) const
{
    samplesLineModeling.clear();
    for(auto const& squareErrorToSamplePair : squareErrorToSampleMultimap)
    {
        if(squareErrorToSamplePair.first <= maxAcceptableSquareError)
        {
            samplesLineModeling.emplace_back(squareErrorToSamplePair.second);
        }
        else
        {
            break;
        }
    }
}

void SOOSA::processTwoColumns(
        BitmapSnippet const& globalSnippet,
        Line const& leftLine,
        Line const& rightLine,
        Line const& topLine,
        Line const& bottomLine)
{
    Point edgePoints[2][3];
    edgePoints[0][0] = getIntersectionOfTwoLines(leftLine, topLine);
    edgePoints[0][2] = getIntersectionOfTwoLines(rightLine, topLine);
    edgePoints[1][0] = getIntersectionOfTwoLines(leftLine, bottomLine);
    edgePoints[1][2] = getIntersectionOfTwoLines(rightLine, bottomLine);
    edgePoints[0][1] = getMidpoint(edgePoints[0][0], edgePoints[0][2]);
    edgePoints[1][1] = getMidpoint(edgePoints[1][0], edgePoints[1][2]);

    Line centerLine(edgePoints[0][1], edgePoints[1][1]);
    Line centerLeftLine = findRightLineUsingStartingLine(globalSnippet, centerLine);
    Line centerRightLine = findLeftLineUsingStartingLine(globalSnippet, centerLine);
    //writeLineInDebug(centerLeftLine, 0x0000EE);
    //writeLineInDebug(centerRightLine, 0x0000EE);

    unsigned int questionNumber(1);
    processColumn(questionNumber, globalSnippet, leftLine, centerLeftLine, topLine, bottomLine, 1);
    processColumn(questionNumber, globalSnippet, centerRightLine, rightLine, topLine, bottomLine, 2);
}

void SOOSA::processOneColumn(
        BitmapSnippet const& globalSnippet,
        Line const& leftLine,
        Line const& rightLine,
        Line const& topLine,
        Line const& bottomLine)
{
    unsigned int questionNumber(1);
    processColumn(questionNumber, globalSnippet, leftLine, rightLine, topLine, bottomLine, 1);
}

void SOOSA::processColumn(
        unsigned int & questionNumber,
        BitmapSnippet const& snippet,
        Line const& leftLine,
        Line const& rightLine,
        Line const& topLine,
        Line const& bottomLine,
        unsigned int const columnNumber)
{
    Point topLeft = getIntersectionOfTwoLines(leftLine, topLine);
    Point topRight = getIntersectionOfTwoLines(rightLine, topLine);
    Point bottomLeft = getIntersectionOfTwoLines(leftLine, bottomLine);
    Point bottomRight = getIntersectionOfTwoLines(rightLine, bottomLine);

    unsigned int numberQuestionsInColumn = m_inputConfiguration.getNumberOfQuestionsAtColumn(columnNumber);
    QuestionBarCoordinates questionBarsOnTheLeft
            = getQuestionBarCoordinatesFromLine(snippet, leftLine, topLeft, bottomLeft, numberQuestionsInColumn);
    QuestionBarCoordinates questionsBarsOnTheRight
            = getQuestionBarCoordinatesFromLine(snippet, rightLine, topRight, bottomRight, numberQuestionsInColumn);
    if(questionBarsOnTheLeft.size() == numberQuestionsInColumn && questionsBarsOnTheRight.size() == numberQuestionsInColumn)
    {
        processQuestions(questionNumber, snippet, questionBarsOnTheLeft, questionsBarsOnTheRight, columnNumber, numberQuestionsInColumn);
    }
    else
    {
        stringstream ss;
        ss<< "Number of question coordinates does not match between columns. "
          << "Question bars at left line: " << questionBarsOnTheLeft.size()
          << "Question bars at right line: " << questionsBarsOnTheRight.size() << ".";


        Status::getInstance().setError(ss.str());
        cout << "Questions bars does not match. "
             << " Questions bars on left line: " << questionBarsOnTheLeft.size()
             << " Questions bars on right Line: " <<questionsBarsOnTheRight.size()
             << " Number of questions from template: " << numberQuestionsInColumn << endl;
    }
}

void SOOSA::processQuestions(
        unsigned int & questionNumber,
        BitmapSnippet const& snippet,
        QuestionBarCoordinates const& questionBarsOnTheLeft,
        QuestionBarCoordinates const& questionsBarsOnTheRight,
        unsigned int const columnNumber,
        unsigned int const numberQuestionsInColumn)
{
    for(unsigned int questionInColumnIndex=0; questionInColumnIndex<numberQuestionsInColumn; questionInColumnIndex++)
    {
        Answers answers = getAnswersAtQuestion(snippet, questionBarsOnTheLeft[questionInColumnIndex], questionsBarsOnTheRight[questionInColumnIndex]);
        if(answers.size() == 1)
        {
            //cout << "In question number " << questionNumber
            //     << ", the question is [" << m_inputConfiguration.getQuestionAt(questionNumber-1)
            //     << "] the answer is " << answers.front() << "." << endl;
            setAnswerToQuestionInColumn(columnNumber, questionInColumnIndex, answers.front());
        }
        else
        {
            cout << "In question number " << questionNumber
                 << ", the question is [" << m_inputConfiguration.getQuestionAt(questionNumber-1)
                 << "]" <<  endl;
            cout << "There is problem locating only one answer. The list of answers: ";
            printParameter(cout, answers);
            cout << "." << endl;
            stringstream ss;
            ss << "There is problem locating only one answer in column number: " << columnNumber << ", column question number: " << questionInColumnIndex+1
               << ". Answers: ";
            printParameter(ss, answers);
            ss << ".";
            Status::getInstance().setError(ss.str());
        }
        questionNumber++;
    }
}

SOOSA::Answers SOOSA::getAnswersAtQuestion(
        BitmapSnippet const& snippet,
        QuestionBarCoordinate const& leftCoordinate,
        QuestionBarCoordinate const& rightCoordinate) const
{
    Answers answers;
    Point leftPoint = getMidpoint(leftCoordinate.first, leftCoordinate.second);
    Point rightPoint = getMidpoint(rightCoordinate.first, rightCoordinate.second);
    double radiusForChoiceChecking = getRadiusForChoiceChecking(leftCoordinate, rightCoordinate);
    unsigned int numberOfChoices = m_soosaConfiguration.getNumberOfChoices();

    OneDimensionSamples shadePercentagesSamples;
    multimap<double, unsigned int> shadePercentageToChoiceMap;
    for(unsigned int choiceIndex=0; choiceIndex<numberOfChoices; choiceIndex++)
    {
        double shadePercentage = getShadePercentage(snippet, leftPoint, rightPoint, radiusForChoiceChecking, choiceIndex);
        shadePercentagesSamples.emplace_back(OneDimensionSample{shadePercentage});
        shadePercentageToChoiceMap.emplace(shadePercentage, numberOfChoices-choiceIndex);
    }

    OneDimensionStatistics shadePercentagesStatistics(shadePercentagesSamples);
    double sd = shadePercentagesStatistics.getSampleStandardDeviation().getValueAt(0);
    double mean = shadePercentagesStatistics.getMean().getValueAt(0);
    double relativeLimit = mean + sd/2; // must be an outlier and positive deviation

    for(auto const& shadePercentageAndChoicePair : shadePercentageToChoiceMap)
    {
        double shadePercentage = shadePercentageAndChoicePair.first;
        if(shadePercentage > relativeLimit
                && shadePercentage >= m_soosaConfiguration.getMinimumPercentageOfBlackPixelsForAFilledCircle())
        {
            answers.emplace_back(shadePercentageAndChoicePair.second);
        }
    }
    sort(answers.begin(), answers.end(), [](unsigned int const answer1, unsigned int const answer2)
    {
        return answer1 > answer2;
    });
    return answers;
}

double SOOSA::getShadePercentage(
        BitmapSnippet const& snippet,
        Point const& leftPoint,
        Point const& rightPoint,
        double const radius,
        unsigned int const choiceIndex) const
{
    unsigned int totalPoints(0), numberOfBlackPoints(0);
    Point centerOfCircle = getCenterOfCircleForChoiceChecking(snippet, leftPoint, rightPoint, radius, choiceIndex);
    Circle circle(centerOfCircle, radius);
    circle.traverseArea(1, [&](Point const& pointInCircle)
    {
        //if(!isBlackAt(snippet, convertToBitmapXY(pointInCircle)))
        //{
        //    writePointInDebug(convertToBitmapXY(pointInCircle), 0xA1BA00);
        //}
        numberOfBlackPoints += (isBlackAt(snippet, convertToBitmapXY(pointInCircle))) ? 1 : 0;
        totalPoints++;
    });    return static_cast<double>(numberOfBlackPoints)/totalPoints;
}

double SOOSA::getRadiusForChoiceChecking(        QuestionBarCoordinate const& leftCoordinate,
        QuestionBarCoordinate const& rightCoordinate) const
{
    double leftBarHeight = getDistance(leftCoordinate.first, leftCoordinate.second);
    double rightBarHeight = getDistance(rightCoordinate.first, rightCoordinate.second);
    double lowestHeightOfQuestion = min(leftBarHeight, rightBarHeight);
    return lowestHeightOfQuestion * m_soosaConfiguration.getBarHeightToDiameterMultiplier()/2;
}

Point SOOSA::getCenterOfCircleForChoiceChecking(
        BitmapSnippet const& snippet,
        Point const& leftPoint,
        Point const& rightPoint,
        double const radius,
        unsigned int const choiceIndex) const
{
    double choiceIndexRatio = (((double)choiceIndex*2)+1) / (m_soosaConfiguration.getNumberOfChoices()*2);
    double differenceFromLeftToRightInX = rightPoint.getX() - leftPoint.getX();
    double differenceFromLeftToRightInY = rightPoint.getY() - leftPoint.getY();
    Point originalCenter(leftPoint.getX()+(differenceFromLeftToRightInX*choiceIndexRatio), leftPoint.getY()+(differenceFromLeftToRightInY*choiceIndexRatio));
    Point result = originalCenter;

    unsigned int numberOfBlackPoints(1), previousNumberOfBlackPoints(0);
    while(previousNumberOfBlackPoints < numberOfBlackPoints
          && getDistance(originalCenter, result) < radius)
    {
        Circle circle(result, radius);
        TwoDimensionSamples blackPointSamples{convertToTwoDimensionSample(result)};
        circle.traverseArea(1, [&](Point const& pointInCircle)
        {
            if(isBlackAt(snippet, convertToBitmapXY(pointInCircle)))
            {
                blackPointSamples.emplace_back(convertToTwoDimensionSample(pointInCircle));
            }
        });
        TwoDimensionStatistics blackPointStatistics(blackPointSamples);
        result = convertToPoint(blackPointStatistics.getMean());
        previousNumberOfBlackPoints = numberOfBlackPoints;
        numberOfBlackPoints = blackPointSamples.size();
    }
    return result;
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
        TwoDimensionKMeans kMeansForBarPoints;
        retrieveBarPointsThatFitAndSaveToKMeans(kMeansForBarPoints, pointAndWidthPairs, minMaxCriteriaForBar);
        removeIncorrectBarPointsBasedFromHeight(kMeansForBarPoints, numberQuestionsInColumn);
        saveQuestionBarCoordinatesFromKMeansWithBarPoints(questionBarCoordinates, kMeansForBarPoints, numberQuestionsInColumn);
    }
    return questionBarCoordinates;
}

void SOOSA::retrieveBarPointsThatFitAndSaveToKMeans(
        TwoDimensionKMeans & kMeansForBarPoints,
        PointAndWidthPairs const& pointAndWidthPairs,
        RangeOfDoubles const& minMaxCriteriaForBar) const
{
    for(PointAndWidthPair const& pointAndWidthPair : pointAndWidthPairs)
    {
        if(minMaxCriteriaForBar.isValueInsideInclusive(pointAndWidthPair.second))
        {
            kMeansForBarPoints.addSample(convertToTwoDimensionSample(pointAndWidthPair.first));
        }
    }
}

void SOOSA::saveQuestionBarCoordinatesFromKMeansWithBarPoints(
        QuestionBarCoordinates & questionBarCoordinates,
        TwoDimensionKMeans const& kMeansForBarPoints,
        unsigned int const numberQuestionsInColumn) const
{
    GroupOfTwoDimensionSamples groupOfBarPoints(kMeansForBarPoints.getGroupOfSamplesUsingKMeans(numberQuestionsInColumn));
    for(TwoDimensionSamples const& barPoints : groupOfBarPoints)
    {
        if(!barPoints.empty())
        {
            //for(TwoDimensionSample const& barPoint : barPoints)
            //{
            //    writePointInDebug(convertToBitmapXY(barPoint), 0x00EE00);
            //}
            //writePointInDebug(convertToBitmapXY(barPoints.front()), 0xEE0000);
            //writePointInDebug(convertToBitmapXY(barPoints.back()), 0xEE0000);
            questionBarCoordinates.emplace_back(QuestionBarCoordinate(convertToPoint(barPoints.front()), convertToPoint(barPoints.back())));
        }
    }
}

SOOSA::RangeOfDoubles SOOSA::getMinMaxCriteriaForBar(
        PointAndWidthPairs const& pointAndWidthPairs) const
{
    RangeOfDoubles result;
    OneDimensionKMeans kMeansForWidths(getKMeansForWidths(pointAndWidthPairs));
    bool continueRemoval(true);
    while(continueRemoval)
    {
        GroupOfOneDimensionSamples twoGroupsOfSamples(kMeansForWidths.getGroupOfSamplesUsingKMeans(2));
        OneDimensionStatistics firstGroupStatistics(twoGroupsOfSamples.at(0));
        OneDimensionStatistics secondGroupStatistics(twoGroupsOfSamples.at(1));
        double firstSdOverMean = firstGroupStatistics.getSampleStandardDeviation().getValueAt(0)/firstGroupStatistics.getMean().getValueAt(0);
        double secondSdOverMean = secondGroupStatistics.getSampleStandardDeviation().getValueAt(0)/secondGroupStatistics.getMean().getValueAt(0);

        continueRemoval = firstSdOverMean > m_soosaConfiguration.getAcceptableSdOverMeanDeviationForLine()
                || secondSdOverMean > m_soosaConfiguration.getAcceptableSdOverMeanDeviationForBar();
        if(continueRemoval)
        {
            unsigned int sizeBefore = kMeansForWidths.getSamples().size();
            kMeansForWidths.clear();
            addAndRetainWidthsIfPossible(kMeansForWidths, firstGroupStatistics, m_soosaConfiguration.getAcceptableSdOverMeanDeviationForLine());
            addAndRetainWidthsIfPossible(kMeansForWidths, secondGroupStatistics, m_soosaConfiguration.getAcceptableSdOverMeanDeviationForBar());
            continueRemoval = sizeBefore > kMeansForWidths.getSamples().size();
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
        result = getMinMaxRangeOfSamples(firstGroupStatistics.getSamples());
    }
    else
    {
        result = getMinMaxRangeOfSamples(secondGroupStatistics.getSamples());
    }
    return result;
}

SOOSA::OneDimensionKMeans SOOSA::getKMeansForWidths(
        PointAndWidthPairs const& pointAndWidthPairs) const
{
    OneDimensionKMeans result;
    for(PointAndWidthPair const& pointAndWidthPair : pointAndWidthPairs)
    {
        result.addSample(OneDimensionSample{pointAndWidthPair.second});
    }
    return result;
}

SOOSA::PointAndWidthPairs SOOSA::getAcceptablePointAndWidthPairs(
        BitmapSnippet const& snippet,
        Line const& line,
        Point const& startPoint,
        Point const& endPoint) const
{
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
        BitmapSnippet const& snippet,
        Line const& line,
        Point const& pointInLine) const
{
    Point nearestBlackPoint(getNearestBlackPointFromLine(snippet, line, pointInLine));
    Line perpendicularLine(getLineWithPerpendicularSlope(line, nearestBlackPoint));
    unsigned int maxLineAndBarWidth = getMaximumLineAndBarWidth(snippet);
    Point leftMostBlack = getLeftOrRightMostBlackPoint(snippet, nearestBlackPoint, perpendicularLine, maxLineAndBarWidth, 1);
    Point rightMostBlack = getLeftOrRightMostBlackPoint(snippet, nearestBlackPoint, perpendicularLine, maxLineAndBarWidth, -1);

    double width = getDistance(leftMostBlack, rightMostBlack);
    Point widthMidPoint = getMidpoint(leftMostBlack, rightMostBlack);
    double acceptableDistance = m_soosaConfiguration.getAcceptableDistanceOverWidthRatioFromWidthMidpoint() * width
            + m_soosaConfiguration.getAcceptableMinimumDistanceFromWidthMidpoint();
    double distanceFromWidthMidpoint = getDistance(pointInLine, widthMidPoint);

    if(distanceFromWidthMidpoint < acceptableDistance)
    {
        pointAndWidthPairs.emplace_back(pointInLine, width);
    }
}

Point SOOSA::getLeftOrRightMostBlackPoint(
        BitmapSnippet const& snippet,
        Point const& nearestBlackPoint,
        Line const& perpendicularLine,
        unsigned int const maxLineAndBarWidth,
        int const sign) const
{
    Point result(nearestBlackPoint);
    unsigned int blackCount = m_soosaConfiguration.getLineBarWidthSearchInitialBlackPointsValue();
    unsigned int totalCount = m_soosaConfiguration.getLineBarWidthSearchInitialBlackPointsValue();
    bool shouldContinue(true);
    for(unsigned int offset=1; offset<=maxLineAndBarWidth && shouldContinue; offset++)
    {
        double possibleBlackPointInX = nearestBlackPoint.getX() + (static_cast<int>(offset)*sign);
        Point possibleBlackPoint(possibleBlackPointInX, perpendicularLine.calculateYFromX(possibleBlackPointInX));
        if(isBlackAt(snippet, convertToBitmapXY(possibleBlackPoint)))
        {
            result = possibleBlackPoint;
            blackCount++;
        }
        totalCount++;
        shouldContinue = m_soosaConfiguration.getLineBarWidthSearchAcceptedRunningBlackRatio() <= static_cast<double>(blackCount)/totalCount;
    }
    return result;
}

Point SOOSA::getNearestBlackPointFromLine(BitmapSnippet const& snippet, Line const& line, Point const& pointInLine) const
{
    Point blackPoint;
    Line perpendicularLine(getLineWithPerpendicularSlope(line, pointInLine));
    unsigned int maxLineAndBarWidth = getMaximumLineAndBarWidth(snippet);
    for(unsigned int deviation=1; deviation<=maxLineAndBarWidth; deviation++)
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
    OneDimensionSamples const& widthSamples(groupStatistics.getSamples());
    double sdOverMean = groupStatistics.getSampleStandardDeviation().getValueAt(0)/groupStatistics.getMean().getValueAt(0);
    if(sdOverMean > acceptableSdOverMeanDeviation)
    {
        double widthMean = groupStatistics.getMean().getValueAt(0);
        multimap<double, double> deviationToWidthMultimap;
        for(OneDimensionSample const& widthSample : widthSamples)
        {
            double width(widthSample.getValueAt(0));
            deviationToWidthMultimap.emplace(getAbsoluteValue(width - widthMean), width);
        }

        unsigned int removalSize = ceil(m_soosaConfiguration.getRemovalRatioForLineAndBar() * deviationToWidthMultimap.size());
        unsigned int retainSize = clampHigherBound(deviationToWidthMultimap.size() - removalSize, deviationToWidthMultimap.size());
        unsigned int count(0);
        for(auto const& deviationAndWidthPair : deviationToWidthMultimap)
        {
            kMeansForWidths.addSample(OneDimensionSample{deviationAndWidthPair.second});
            if(count++ >= retainSize)
            {
                break;
            }
        }
    }
    else
    {
        kMeansForWidths.addSamples(widthSamples);
    }
}

void SOOSA::removeIncorrectBarPointsBasedFromHeight(
        TwoDimensionKMeans & kMeansForBarPoints,
        unsigned int const numberQuestionsInColumn) const
{
    unsigned int countForPrint(0);
    bool continueRemoval(true);
    while(continueRemoval)
    {
        GroupOfTwoDimensionSamples listOfGroupOfBarPoints(kMeansForBarPoints.getGroupOfSamplesUsingKMeans(numberQuestionsInColumn));
        OneDimensionSamples barHeights(getBarHeights(listOfGroupOfBarPoints));
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
                TwoDimensionSamples const& barPoints(listOfGroupOfBarPoints.at(groupIndex));
                if(!barPoints.empty())
                {
                    double signedDeviation = getHeight(barPoints) - mean; // no absolute value because only positive deviation should be removed
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
                unsigned int sizeBefore = kMeansForBarPoints.getSamples().size();
                kMeansForBarPoints.clear();
                addAndRetainBarPointsIfPossible(kMeansForBarPoints, listOfGroupOfBarPoints, indexToRemove);
                continueRemoval = sizeBefore > kMeansForBarPoints.getSamples().size();
            }
        }
        if(countForPrint == 20)
        {
            cout << "SOOSA is having a hard time figuring out the heights of each questions bar (form might be invalid)."
                 << " This may take a lot of time but it will finish." << endl;
        }
        countForPrint++;
    }
}

void SOOSA::addAndRetainBarPointsIfPossible(
        TwoDimensionKMeans & kMeansForBarPoints,
        GroupOfTwoDimensionSamples const& listOfGroupOfBarPoints,
        unsigned int const indexToRemove) const
{
    for(unsigned int groupIndex=0; groupIndex<listOfGroupOfBarPoints.size(); groupIndex++)
    {
        TwoDimensionSamples const& barPointsSamples(listOfGroupOfBarPoints.at(groupIndex));
        if(groupIndex == indexToRemove)
        {
            TwoDimensionStatistics barPointsStatistics(barPointsSamples);
            Point center = convertToPoint(barPointsStatistics.getMean());

            multimap<double, Point> deviationToPointMultimap;
            for(TwoDimensionSample const& barPointsSample : barPointsSamples)
            {
                Point barPoint = convertToPoint(barPointsSample);
                deviationToPointMultimap.emplace(getDistance(center, barPoint), barPoint);
            }

            Points acceptedBarPoints;
            unsigned int removalSize = ceil(m_soosaConfiguration.getRemovalRatioForBarHeight() * barPointsSamples.size());
            unsigned int retainSize = clampHigherBound(barPointsSamples.size() - removalSize, barPointsSamples.size());
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
                kMeansForBarPoints.addSample(convertToTwoDimensionSample(acceptedBarPoint));
            }
        }
        else
        {
            kMeansForBarPoints.addSamples(barPointsSamples);
        }
    }
}

SOOSA::OneDimensionSamples SOOSA::getBarHeights(
        GroupOfTwoDimensionSamples const& groupOfBarPoints) const
{
    OneDimensionSamples barHeights;
    for(TwoDimensionSamples const& barPoints : groupOfBarPoints)
    {
        if(!barPoints.empty())
        {
            barHeights.emplace_back(OneDimensionSample{getHeight(barPoints)});
        }
    }
    return barHeights;
}

double SOOSA::getHeight(TwoDimensionSamples const& barPoints) const
{
    return getDistance(convertToPoint(barPoints.front()), convertToPoint(barPoints.back()));
}

string SOOSA::getCsvFilePath(string const& path) const
{
    return AlbaLocalPathHandler(path).getDirectory()+"PSS_Report_"+m_inputConfiguration.getArea()+"_"+m_inputConfiguration.getPeriod()+".csv";
}

string SOOSA::getReportHtmlFilePath(string const& path) const
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
    m_questionToAnswersMap[m_inputConfiguration.getQuestionIndexInColumn(columnNumber, questionOffsetInColumn)] = answer;
}


void SOOSA::saveDataToCsvFile(string const& processedFilePath)  const
{
    ofstream outputCsvReportStream(getCsvFilePath(m_inputConfiguration.getPath()), ofstream::app);
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
    ofstream outputCsvReportStream(getCsvFilePath(m_inputConfiguration.getPath()));
    outputCsvReportStream << "FILE,STATUS";
    for(unsigned int i=0; i<m_inputConfiguration.getNumberOfQuestions(); i++)
    {
        outputCsvReportStream << ",Question_" << i+1;
    }
    outputCsvReportStream << endl;
}

void SOOSA::saveOutputHtmlFile(string const& processedFilePath) const
{
    AlbaLocalPathHandler basisHtmlPath(PathInitialValueSource::DetectedLocalPath);
    basisHtmlPath.input(basisHtmlPath.getDirectory() + "basis.html");
    ifstream htmlBasisFileStream(basisHtmlPath.getFullPath());
    if(htmlBasisFileStream.is_open())
    {
        AlbaFileReader htmlBasisFileReader(htmlBasisFileStream);
        string outputHtmlFilePath = getReportHtmlFilePath(processedFilePath);
        ofstream reportHtmlFileStream(outputHtmlFilePath);
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
        cout << "The data is saved to the output html file. File path : [" << outputHtmlFilePath << "]" << endl;
    }
    else
    {
        cout << "Cannot save to output html file because basis cannot be opened." << endl;
        cout << "Basis html path: [" << basisHtmlPath.getFullPath() << "]" << endl;
        cout << "Basis html can be found on local system: [" << basisHtmlPath.isFoundInLocalSystem() << "]" << endl;
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
    using BitColorManip = AlbaBitManipulation<uint32_t>;
    uint32_t color = snippet.getColorAt(bitmapXy);
    uint32_t minColorIntensity = min(BitColorManip::getByteAt<0>(color), min(BitColorManip::getByteAt<1>(color), BitColorManip::getByteAt<2>(color)));

    return minColorIntensity < m_soosaConfiguration.getColorIntensityForWhite();
}

unsigned int SOOSA::getMaximumLineAndBarWidth(BitmapSnippet const& snippet) const
{
    return m_soosaConfiguration.getBitmapWidthToBarWidthMultiplier() * snippet.getConfiguration().getBitmapWidth();
}

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

SOOSA::RangeOfDoubles SOOSA::getMinMaxRangeOfSamples(OneDimensionSamples const& samples) const
{
    DoubleCollection collection;
    for(OneDimensionSample const& sample : samples)
    {
        collection.addData(sample.getValueAt(0));
    }
    return RangeOfDoubles(collection.getMinimum(), collection.getMaximum(), 1);
}

}

}
