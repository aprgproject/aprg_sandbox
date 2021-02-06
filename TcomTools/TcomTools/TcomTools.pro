#-------------------------------------------------
#
# Project created by QtCreator 2015-07-05T16:05:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TcomTools
TEMPLATE = app
CONFIG += staticlib

SOURCES += \
src/main.cpp\
src/ProgressCounters.cpp\
src/ProgressBarThread.cpp\
src/StepHandler.cpp\
src/StepHandlerThread.cpp\
src/TcomTools.cpp\
src/TcomToolsConfiguration.cpp\
../TcomToolsBackend/src/BtsLogPrint.cpp\
../TcomToolsBackend/src/BtsLogSorter.cpp\
../TcomToolsBackend/src/BtsLogTime.cpp\
../TcomToolsBackend/src/BtsPrintReaderWithRollback.cpp\
../../AprgAlgorithm/AprgAlgorithm/src/GrepStringEvaluator/AlbaGrepStringEvaluator.cpp\
../../AprgAlgorithm/AprgAlgorithm/src/GrepStringEvaluator/AlbaGrepStringEvaluatorPerformOperations.cpp\
../../AprgAlgorithm/AprgAlgorithm/src/GrepStringEvaluator/AlbaGrepStringEvaluatorTerm.cpp\
../../AprgAlgorithm/AprgAlgorithm/src/GrepStringEvaluator/AlbaGrepStringToken.cpp\
../../AprgCommon/AprgCommon/src/File/AlbaFileParameterReader.cpp\
../../AprgCommon/AprgCommon/src/File/AlbaFileParameterWriter.cpp\
../../AprgCommon/AprgCommon/src/File/AlbaFileReader.cpp\
../../AprgCommon/AprgCommon/src/Memory/AlbaMemoryBuffer.cpp\
../../AprgCommon/AprgCommon/src/Optional/AlbaOptional.cpp\
../../AprgCommon/AprgCommon/src/PathHandlers/AlbaPathHandler.cpp\
../../AprgCommon/AprgCommon/src/PathHandlers/AlbaLocalPathHandler.cpp\
../../AprgCommon/AprgCommon/src/Randomizer/AlbaRandomizer.cpp\
../../AprgCommon/AprgCommon/src/String/AlbaStringHelper.cpp\
../../AprgCommon/AprgCommon/src/Time/AlbaDateTime.cpp\
../../AprgCommon/AprgCommon/src/Time/AlbaDateTimeHelper.cpp\
../../AprgCommon/AprgCommon/srcWindows/PathHandlers/AlbaWindowsPathHandler.cpp\
../../AprgCommon/AprgCommon/srcWindows/Windows/AlbaWindowsHelper.cpp\
../../AprgFileExtractor/AprgFileExtractor/src/AprgFileExtractor.cpp

HEADERS += \
src/ProgressCounters.hpp\
src/ProgressBarThread.hpp\
src/StepHandler.hpp\
src/StepHandlerThread.hpp\
src/TcomTools.h\
src/TcomToolsConfiguration.hpp\
../TcomToolsBackend/src/BtsLogPrint.hpp\
../TcomToolsBackend/src/BtsLogSorter.hpp\
../TcomToolsBackend/src/BtsLogSorterConfiguration.hpp\
../TcomToolsBackend/src/BtsLogTime.hpp\
../TcomToolsBackend/src/BtsPrintReaderWithRollback.hpp\
../../AprgAlgorithm/AprgAlgorithm/src/ExpressionEvaluator/ExpressionEvaluator.hpp\
../../AprgAlgorithm/AprgAlgorithm/src/GrepStringEvaluator/AlbaGrepStringEvaluator.hpp\
../../AprgAlgorithm/AprgAlgorithm/src/GrepStringEvaluator/AlbaGrepStringEvaluatorPerformOperations.hpp\
../../AprgAlgorithm/AprgAlgorithm/src/GrepStringEvaluator/AlbaGrepStringEvaluatorTerm.hpp\
../../AprgAlgorithm/AprgAlgorithm/src/GrepStringEvaluator/AlbaGrepStringOperatorType.hpp\
../../AprgAlgorithm/AprgAlgorithm/src/GrepStringEvaluator/AlbaGrepStringToken.hpp\
../../AprgCommon/AprgCommon/src/File/AlbaFileParameterReader.hpp\
../../AprgCommon/AprgCommon/src/File/AlbaFileParameterWriter.hpp\
../../AprgCommon/AprgCommon/src/File/AlbaFileReader.hpp\
../../AprgCommon/AprgCommon/src/Memory/AlbaMemoryBuffer.hpp\
../../AprgCommon/AprgCommon/src/Optional/AlbaOptional.hpp\
../../AprgCommon/AprgCommon/src/PathHandlers/AlbaPathHandler.hpp\
../../AprgCommon/AprgCommon/src/PathHandlers/AlbaLocalPathHandler.hpp\
../../AprgCommon/AprgCommon/src/Randomizer/AlbaRandomizer.hpp\
../../AprgCommon/AprgCommon/src/String/AlbaStringHelper.hpp\
../../AprgCommon/AprgCommon/src/Time/AlbaDateTime.hpp\
../../AprgCommon/AprgCommon/src/Time/AlbaDateTimeHelper.hpp\
../../AprgCommon/AprgCommon/src/Time/AlbaDateTimeConstants.hpp\
../../AprgCommon/AprgCommon/srcWindows/PathHandlers/AlbaWindowsPathHandler.hpp\
../../AprgCommon/AprgCommon/srcWindows/Windows/AlbaWindowsHelper.hpp\
../../AprgFileExtractor/AprgFileExtractor/src/AprgFileExtractor.hpp

FORMS += src/TcomTools.ui

QMAKE_INCDIR += \
src\
../TcomToolsBackend/src\
../../AprgFileExtractor/AprgFileExtractor/src\
../../AprgAlgorithm/AprgAlgorithm/src\
../../AprgCommon/AprgCommon/src\
../../AprgCommon/AprgCommon/srcWindows


win32 {
     QMAKE_LFLAGS += -Wl,-subsystem,windows
}

message(APRG_DIR=\\\"$$PWD/../../\\\")

DEFINES -= UNICODE
DEFINES += APRG_DIR=\\\"$$PWD/../../\\\"
DEFINES += PATH_OF_7Z_EXECUTABLE=\\\"$$PWD/../../AprgFileExtractor/7z32/7z.exe\\\"
DEFINES += PATH_OF_7Z_TEMP_FILE=\\\"$$PWD/../../AprgFileExtractor/7z32/TempFile.txt\\\"
DEFINES += OS_WINDOWS=\\\"WIN32\\\"

CONFIG += c++11 console
