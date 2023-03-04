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
../WcdmaToolsBackend/src/WcdmaToolsBackend/BtsLogPrint.cpp\
../WcdmaToolsBackend/src/WcdmaToolsBackend/BtsLogSorter.cpp\
../WcdmaToolsBackend/src/WcdmaToolsBackend/BtsLogTime.cpp\
../WcdmaToolsBackend/src/WcdmaToolsBackend/BtsPrintReaderWithRollback.cpp\
../../AprgCommon/AprgCommon/src/Common/Container/AlbaContainerHelper.cpp\
../../AprgCommon/AprgCommon/src/Common/File/AlbaFileReader.cpp\
../../AprgCommon/AprgCommon/src/Common/Math/Helpers/ComplexNumberHelpers.cpp\
../../AprgCommon/AprgCommon/src/Common/Math/Helpers/FractionHelpers.cpp\
../../AprgCommon/AprgCommon/src/Common/Math/Number/AlbaComplexNumber.cpp\
../../AprgCommon/AprgCommon/src/Common/Math/Number/AlbaNumber.cpp\
../../AprgCommon/AprgCommon/src/Common/Memory/AlbaMemoryBuffer.cpp\
../../AprgCommon/AprgCommon/src/Common/PathHandler/AlbaPathHandler.cpp\
../../AprgCommon/AprgCommon/src/Common/PathHandler/AlbaLocalPathHandler.cpp\
../../AprgCommon/AprgCommon/src/Common/Randomizer/AlbaSimpleRandomizer.cpp\
../../AprgCommon/AprgCommon/src/Common/Stream/AlbaStreamParameterReader.cpp\
../../AprgCommon/AprgCommon/src/Common/Stream/AlbaStreamParameterWriter.cpp\
../../AprgCommon/AprgCommon/src/Common/String/AlbaStringHelper.cpp\../../AprgCommon/AprgCommon/src/Common/Time/AlbaDateTime.cpp\
../../AprgCommon/AprgCommon/src/Common/Time/AlbaDateTimeHelper.cpp\
../../AprgCommon/AprgCommon/src/Common/Time/AlbaLocalTimeHelper.cpp\
../../AprgCommon/AprgCommon/srcWindows/Common/PathHandler/AlbaWindowsPathHandler.cpp\../../AprgCommon/AprgCommon/srcWindows/Common/Time/AlbaWindowsTimeHelper.cpp\
../../AprgCommon/AprgCommon/srcWindows/Common/Windows/AlbaWindowsHelper.cpp\
../../AprgFileExtractor/AprgFileExtractor/src/FileExtractor/AprgFileExtractor.cpp\
../../AprgGrepStringEvaluator/AprgGrepStringEvaluator/src/GrepStringEvaluator/AlbaGrepStringEvaluator.cpp\
../../AprgGrepStringEvaluator/AprgGrepStringEvaluator/src/GrepStringEvaluator/AlbaGrepStringEvaluatorPerformOperations.cpp\
../../AprgGrepStringEvaluator/AprgGrepStringEvaluator/src/GrepStringEvaluator/AlbaGrepStringEvaluatorTerm.cpp\
../../AprgGrepStringEvaluator/AprgGrepStringEvaluator/src/GrepStringEvaluator/AlbaGrepStringToken.cpp\
../../AprgProcessFiles/AprgProcessFiles/src/ProcessFiles/CropFile/AlbaCropFile.cpp\
../../AprgProcessFiles/AprgProcessFiles/src/ProcessFiles/GrepFile/AlbaGrepFile.cpp

HEADERS += \
src/ProgressCounters.hpp\
src/ProgressBarThread.hpp\
src/StepHandler.hpp\
src/StepHandlerThread.hpp\
src/WcdmaTools.h\
src/WcdmaToolsConfiguration.hpp\
../WcdmaToolsBackend/src/WcdmaToolsBackend/BtsLogPrint.hpp\
../WcdmaToolsBackend/src/WcdmaToolsBackend/BtsLogSorter.hpp\
../WcdmaToolsBackend/src/WcdmaToolsBackend/BtsLogSorterConfiguration.hpp\
../WcdmaToolsBackend/src/WcdmaToolsBackend/BtsLogTime.hpp\
../WcdmaToolsBackend/src/WcdmaToolsBackend/BtsPrintReaderWithRollback.hpp\
../../AprgCommon/AprgCommon/src/Common/Container/AlbaContainerHelper.hpp\
../../AprgCommon/AprgCommon/src/Common/File/AlbaFileReader.hpp\
../../AprgCommon/AprgCommon/src/Common/Math/Helpers/ComplexNumberHelpers.hpp\
../../AprgCommon/AprgCommon/src/Common/Math/Helpers/FractionHelpers.hpp\
../../AprgCommon/AprgCommon/src/Common/Math/Number/AlbaComplexNumber.hpp\
../../AprgCommon/AprgCommon/src/Common/Math/Number/AlbaNumber.hpp\
../../AprgCommon/AprgCommon/src/Common/Memory/AlbaMemoryBuffer.hpp\
../../AprgCommon/AprgCommon/src/Common/PathHandler/AlbaPathHandler.hpp\
../../AprgCommon/AprgCommon/src/Common/PathHandler/AlbaLocalPathHandler.hpp\
../../AprgCommon/AprgCommon/src/Common/Randomizer/AlbaSimpleRandomizer.hpp\
../../AprgCommon/AprgCommon/src/Common/Stream/AlbaStreamParameterReader.hpp\
../../AprgCommon/AprgCommon/src/Common/Stream/AlbaStreamParameterWriter.hpp\
../../AprgCommon/AprgCommon/src/Common/String/AlbaStringHelper.hpp\../../AprgCommon/AprgCommon/src/Common/Time/AlbaDateTime.hpp\
../../AprgCommon/AprgCommon/src/Common/Time/AlbaDateTimeHelper.hpp\
../../AprgCommon/AprgCommon/src/Common/Time/AlbaDateTimeConstants.hpp\
../../AprgCommon/AprgCommon/src/Common/Time/AlbaLocalTimeHelper.hpp\../../AprgCommon/AprgCommon/srcWindows/Common/PathHandler/AlbaWindowsPathHandler.hpp\
../../AprgCommon/AprgCommon/srcWindows/Common/Time/AlbaWindowsTimeHelper.hpp\
../../AprgCommon/AprgCommon/srcWindows/Common/Windows/AlbaWindowsHelper.hpp\
../../AprgFileExtractor/AprgFileExtractor/src/FileExtractor/AprgFileExtractor.hpp\
../../AprgGrepStringEvaluator/AprgGrepStringEvaluator/src/GrepStringEvaluator/AlbaGrepStringEvaluator.hpp\
../../AprgGrepStringEvaluator/AprgGrepStringEvaluator/src/GrepStringEvaluator/AlbaGrepStringEvaluatorPerformOperations.hpp\
../../AprgGrepStringEvaluator/AprgGrepStringEvaluator/src/GrepStringEvaluator/AlbaGrepStringEvaluatorTerm.hpp\
../../AprgGrepStringEvaluator/AprgGrepStringEvaluator/src/GrepStringEvaluator/AlbaGrepStringOperatorType.hpp\
../../AprgGrepStringEvaluator/AprgGrepStringEvaluator/src/GrepStringEvaluator/AlbaGrepStringToken.hpp\
../../AprgProcessFiles/AprgProcessFiles/src/ProcessFiles/CropFile/AlbaCropFile.hpp\
../../AprgProcessFiles/AprgProcessFiles/src/ProcessFiles/GrepFile/AlbaGrepFile.hpp

FORMS += src/WcdmaTools.ui

QMAKE_INCDIR += \
src\
../WcdmaToolsBackend/src\
../../AprgAlgorithm/AprgAlgorithm/src\
../../AprgCommon/AprgCommon/src\
../../AprgCommon/AprgCommon/srcWindows\
../../AprgFileExtractor/AprgFileExtractor/src\
../../AprgGrepStringEvaluator/AprgGrepStringEvaluator/src\
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
