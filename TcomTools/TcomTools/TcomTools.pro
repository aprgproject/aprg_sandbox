#-------------------------------------------------
#
# Project created by QtCreator 2015-07-05T16:05:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TcomTools
TEMPLATE = app


SOURCES += src/main.cpp\
src/StepHandler.cpp\
src/TcomTools.cpp\
src/TcomToolsConfiguration.cpp\
../../AprgFileExtractor/AprgFileExtractor/src/AprgFileExtractor.cpp\
../../AprgCommon/AprgCommon/src/AlbaFileReader.cpp\../../AprgCommon/AprgCommon/src/AlbaStringHelper.cpp\
../../AprgCommon/AprgCommon/src/GrepStringEvaluator/AlbaGrepStringEvaluator.cpp\
../../AprgCommon/AprgCommon/src/GrepStringEvaluator/AlbaGrepStringEvaluatorTerm.cpp\
../../AprgCommon/AprgCommon/src/PathHandlers/AlbaPathHandler.cpp\../../AprgCommon/AprgCommon/src/PathHandlers/AlbaWindowsPathHandler.cpp\
../TcomToolsBackend/src/BtsLogPrint.cpp\
../TcomToolsBackend/src/BtsLogSorter.cpp\
../TcomToolsBackend/src/BtsLogTime.cpp

HEADERS += src/StepHandler.hpp\
src/TcomTools.h\
src/TcomToolsConfiguration.hpp\
../../AprgFileExtractor/AprgFileExtractor/src/AprgFileExtractor.hpp\
../../AprgCommon/AprgCommon/src/AlbaFileReader.hpp\../../AprgCommon/AprgCommon/src/AlbaStringHelper.hpp\
../../AprgCommon/AprgCommon/src/GrepStringEvaluator/AlbaGrepStringEvaluator.hpp\
../../AprgCommon/AprgCommon/src/GrepStringEvaluator/AlbaGrepStringEvaluatorTerm.hpp\
../../AprgCommon/AprgCommon/src/PathHandlers/AlbaPathHandler.hpp\../../AprgCommon/AprgCommon/src/PathHandlers/AlbaWindowsPathHandler.hpp\
../TcomToolsBackend/src/BtsLogPrint.hpp\
../TcomToolsBackend/src/BtsLogSorter.hpp\
../TcomToolsBackend/src/BtsLogTime.hpp

FORMS += src/TcomTools.ui

QMAKE_INCDIR += src\
../../AprgFileExtractor/AprgFileExtractor/src\../../AprgCommon/AprgCommon/src\
../TcomToolsBackend/src

DEFINES -= UNICODE

CONFIG += c++11 console