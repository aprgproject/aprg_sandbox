#-------------------------------------------------
#
# Project created by QtCreator 2015-07-05T16:05:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WcdmaTools
TEMPLATE = app
CONFIG += static

QMAKE_CFLAGS += -static -static-libgcc -static-libstdc++
QMAKE_CXXFLAGS += -static -static-libgcc -static-libstdc++

SOURCES += \
src/main.cpp\
src/ProgressCounters.cpp\
src/ProgressBarThread.cpp\
src/StepHandler.cpp\
src/StepHandlerThread.cpp\
src/WcdmaTools.cpp\
src/WcdmaToolsConfiguration.cpp\
../WcdmaToolsBackend/src/BtsLogPrint.cpp\
../WcdmaToolsBackend/src/BtsLogSorter.cpp\
../WcdmaToolsBackend/src/BtsLogTime.cpp\
../WcdmaToolsBackend/src/BtsPrintReaderWithRollback.cpp\
../../AprgAlgorithm/AprgAlgorithm/src/GrepStringEvaluator/AlbaGrepStringEvaluator.cpp\
../../AprgAlgorithm/AprgAlgorithm/src/GrepStringEvaluator/AlbaGrepStringEvaluatorPerformOperations.cpp\
../../AprgAlgorithm/AprgAlgorithm/src/GrepStringEvaluator/AlbaGrepStringEvaluatorTerm.cpp\
../../AprgAlgorithm/AprgAlgorithm/src/GrepStringEvaluator/AlbaGrepStringToken.cpp\
../../AprgCommon/AprgCommon/src/File/AlbaFileParameterReader.cpp\
../../AprgCommon/AprgCommon/src/File/AlbaFileParameterWriter.cpp\
../../AprgCommon/AprgCommon/src/File/AlbaFileReader.cpp\
../../AprgCommon/AprgCommon/src/Math/AlbaMathHelper.cpp\
../../AprgCommon/AprgCommon/src/Math/Number/AlbaComplexNumber.cpp\
../../AprgCommon/AprgCommon/src/Math/Number/AlbaNumber.cpp\
../../AprgCommon/AprgCommon/src/Memory/AlbaMemoryBuffer.cpp\
../../AprgCommon/AprgCommon/src/Optional/AlbaOptional.cpp\
../../AprgCommon/AprgCommon/src/PathHandlers/AlbaPathHandler.cpp\
../../AprgCommon/AprgCommon/src/PathHandlers/AlbaLocalPathHandler.cpp\
../../AprgCommon/AprgCommon/src/Randomizer/AlbaRandomizer.cpp\
../../AprgCommon/AprgCommon/src/String/AlbaStringHelper.cpp\
../../AprgCommon/AprgCommon/src/Time/AlbaDateTime.cpp\
../../AprgCommon/AprgCommon/src/Time/AlbaDateTimeHelper.cpp\
../../AprgCommon/AprgCommon/src/Time/AlbaLocalTimeHelper.cpp\
../../AprgCommon/AprgCommon/srcWindows/PathHandlers/AlbaWindowsPathHandler.cpp\
../../AprgCommon/AprgCommon/srcWindows/Time/AlbaWindowsTimeHelper.cpp\
../../AprgCommon/AprgCommon/srcWindows/Windows/AlbaWindowsHelper.cpp\
../../AprgFileExtractor/AprgFileExtractor/src/AprgFileExtractor.cpp\
../../AprgProcessFiles/AprgProcessFiles/src/CropFile/AlbaCropFile.cpp\
../../AprgProcessFiles/AprgProcessFiles/src/GrepFile/AlbaGrepFile.cpp

HEADERS += \
src/ProgressCounters.hpp\
src/ProgressBarThread.hpp\
src/StepHandler.hpp\
src/StepHandlerThread.hpp\
src/WcdmaTools.h\
src/WcdmaToolsConfiguration.hpp\
../WcdmaToolsBackend/src/BtsLogPrint.hpp\
../WcdmaToolsBackend/src/BtsLogSorter.hpp\
../WcdmaToolsBackend/src/BtsLogSorterConfiguration.hpp\
../WcdmaToolsBackend/src/BtsLogTime.hpp\
../WcdmaToolsBackend/src/BtsPrintReaderWithRollback.hpp\
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
../../AprgCommon/AprgCommon/src/Time/AlbaLocalTimeHelper.hpp\
../../AprgCommon/AprgCommon/srcWindows/PathHandlers/AlbaWindowsPathHandler.hpp\
../../AprgCommon/AprgCommon/srcWindows/Time/AlbaWindowsTimeHelper.hpp\
../../AprgCommon/AprgCommon/srcWindows/Windows/AlbaWindowsHelper.hpp\
../../AprgFileExtractor/AprgFileExtractor/src/AprgFileExtractor.hpp\
../../AprgProcessFiles/AprgProcessFiles/src/CropFile/AlbaCropFile.hpp\
../../AprgProcessFiles/AprgProcessFiles/src/GrepFile/AlbaGrepFile.hpp

FORMS += src/WcdmaTools.ui

QMAKE_INCDIR += \
src\
../WcdmaToolsBackend/src\
../../AprgAlgorithm/AprgAlgorithm/src\
../../AprgCommon/AprgCommon/src\
../../AprgCommon/AprgCommon/srcWindows\
../../AprgFileExtractor/AprgFileExtractor/src\
../../AprgProcessFiles/AprgProcessFiles/src


win32 {
     QMAKE_LFLAGS += -Wl,-subsystem,windows -static -static-libgcc -static-libstdc++
}


DEFINES -= UNICODE
DEFINES += APRG_DIR=\\\"$$PWD/../../\\\"
DEFINES += PATH_OF_7Z_EXECUTABLE=\\\"$$PWD/../../AprgFileExtractor/7z32/7z.exe\\\"
DEFINES += PATH_OF_7Z_TEMP_FILE=\\\"$$PWD/../../AprgFileExtractor/7z32/TempFile.txt\\\"
DEFINES += OS_WINDOWS=\\\"WIN32\\\"
DEFINES += STATIC
DEFINES += "APRG_CODE_VERSION=\"\\\"$$system(svnversion -n)\\\"\""

CONFIG += c++11 console

RESOURCES += \
    resources.qrc

RC_FILE = icon/resource.rc

message($$DEFINES)
