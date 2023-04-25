#include "AlbaCropFile.hpp"

#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <fstream>
#include <iostream>

using namespace std;

namespace alba {

AlbaCropFile::AlbaCropFile(string const& prioritizedLineCondition, double const cropSize)
    : m_isOutputFileWritten(false),
      m_cropSize(cropSize),
      m_prioritizedLineEvaluator(prioritizedLineCondition),
      m_updateFunctionAfterOneIterationOptional() {}

AlbaCropFile::AlbaCropFile(
    string const& prioritizedLineCondition, double const cropSize,
    UpdateFunctionWithPercentage const& updateFunctionAfterOneIteration)
    : m_isOutputFileWritten(false),
      m_cropSize(cropSize),
      m_prioritizedLineEvaluator(prioritizedLineCondition),
      m_updateFunctionAfterOneIterationOptional(updateFunctionAfterOneIteration) {}

bool AlbaCropFile::isOutputFileWritten() const { return m_isOutputFileWritten; }

void AlbaCropFile::processFile(string const& inputFilePath, string const& outputFilePath) {
    m_isOutputFileWritten = false;
    AlbaLocalPathHandler inputPathHandler(inputFilePath);
    AlbaLocalPathHandler outputPathHandler(outputFilePath);

    double foundLocation(getLocationOfPrioritizedPrint(inputPathHandler.getFullPath()));
    if (foundLocation >= 0) {
        performCropForFile(inputPathHandler.getFullPath(), outputPathHandler.getFullPath(), foundLocation);
    } else {
        cout << "CropFile: Crop process did not proceed. Prioritized line not found."
             << "\n";
    }
    updateAfterOneIteration(100);
}

double AlbaCropFile::getLocationOfPrioritizedPrint(string const& inputFilePath) {
    double foundLocation(-1);
    ifstream inputFileStream(inputFilePath);
    AlbaFileReader fileReader(inputFileStream);
    double sizeOfFile = fileReader.getFileSize();
    while (fileReader.isNotFinished()) {
        double currentLocation = fileReader.getCurrentLocation();
        string lineInFile(fileReader.getLineAndIgnoreWhiteSpaces());
        if (m_prioritizedLineEvaluator.evaluate(lineInFile)) {
            cout << "CropFile: Found the prioritized line in input file. Line: " << lineInFile << "\n";
            foundLocation = currentLocation;
            break;
        }
        if (fileReader.isNotFinished()) {
            updateAfterOneIteration(fileReader.getCurrentLocation() * 50 / sizeOfFile);
        }
    }
    return foundLocation;
}

void AlbaCropFile::performCropForFile(
    string const& inputFilePath, string const& outputFilePath, double const foundLocation) {
    ifstream inputFileStream(inputFilePath);
    ofstream outputFileStream(outputFilePath);

    AlbaFileReader fileReader(inputFileStream);
    LocationsInFile locations(getLocationsInFile(foundLocation, fileReader.getFileSize()));
    inputFileStream.clear();
    fileReader.moveLocation(static_cast<unsigned long long>(locations.startLocation));

    double locationDifference = locations.endLocation - locations.startLocation;
    while (fileReader.isNotFinished()) {
        double currentLocation = fileReader.getCurrentLocation();
        string lineInFile(fileReader.getLineAndIgnoreWhiteSpaces());
        if (currentLocation < locations.endLocation) {
            m_isOutputFileWritten = true;
            outputFileStream << lineInFile << "\n";
        } else {
            break;
        }
        if (fileReader.isNotFinished()) {
            updateAfterOneIteration(50 + (currentLocation - locations.startLocation) * 50 / locationDifference);
        }
    }
}

AlbaCropFile::LocationsInFile AlbaCropFile::getLocationsInFile(
    double const foundLocation, double const fileSize) const {
    LocationsInFile locations{};
    locations.startLocation = foundLocation - (m_cropSize / 2);
    locations.endLocation = foundLocation + (m_cropSize / 2);
    double overFlowOnTheLeft = -locations.startLocation;
    double overFlowOnTheRight = locations.endLocation - fileSize;
    if (overFlowOnTheLeft > 0 || overFlowOnTheRight > 0) {
        if (overFlowOnTheLeft < 0 && overFlowOnTheRight + overFlowOnTheLeft <= 0) {
            locations.startLocation -= overFlowOnTheRight;
            locations.endLocation -= overFlowOnTheRight;
        } else if (overFlowOnTheRight < 0 && overFlowOnTheRight + overFlowOnTheLeft <= 0) {
            locations.startLocation += overFlowOnTheLeft;
            locations.endLocation += overFlowOnTheLeft;
        } else {
            locations.startLocation = 0;
            locations.endLocation = fileSize;
        }
    }
    return locations;
}

void AlbaCropFile::updateAfterOneIteration(double const percentage) {
    if (m_updateFunctionAfterOneIterationOptional) {
        m_updateFunctionAfterOneIterationOptional.value()(percentage);
    }
}

}  // namespace alba
