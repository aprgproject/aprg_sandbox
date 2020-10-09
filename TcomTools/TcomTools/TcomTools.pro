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
src/tcomtools.cpp\
../../AprgFileExtractor/AprgFileExtractor/src/AprgFileExtractor.cpp\
../../AprgCommon/AprgCommon/src/AlbaFileReader.cpp\
../../AprgCommon/AprgCommon/src/AlbaStringHelper.cpp\
../../AprgCommon/AprgCommon/src/GrepStringEvaluator/AlbaGrepStringEvaluator.cpp\
../../AprgCommon/AprgCommon/src/GrepStringEvaluator/AlbaGrepStringEvaluatorTerm.cpp\
../../AprgCommon/AprgCommon/src/PathHandlers/AlbaPathHandler.cpp\
../../AprgCommon/AprgCommon/src/PathHandlers/AlbaWindowsPathHandler.cpp

HEADERS += src/tcomtools.h\
src/TcomtoolsConfiguration.hpp\
../../AprgFileExtractor/AprgFileExtractor/src/AprgFileExtractor.hpp\
../../AprgCommon/AprgCommon/src/AlbaFileReader.hpp\
../../AprgCommon/AprgCommon/src/AlbaStringHelper.hpp\
../../AprgCommon/AprgCommon/src/GrepStringEvaluator/AlbaGrepStringEvaluator.hpp\
../../AprgCommon/AprgCommon/src/GrepStringEvaluator/AlbaGrepStringEvaluatorTerm.hpp\
../../AprgCommon/AprgCommon/src/PathHandlers/AlbaPathHandler.hpp\
../../AprgCommon/AprgCommon/src/PathHandlers/AlbaWindowsPathHandler.hpp

FORMS += src/tcomtools.ui

QMAKE_INCDIR += src\
../../AprgCommon/AprgCommon/src\
../../AprgCommon/AprgCommon/src/GrepStringEvaluator\
../../AprgCommon/AprgCommon/src/PathHandlers

DEFINES -= UNICODE

CONFIG += c++11