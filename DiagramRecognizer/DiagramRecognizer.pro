#-------------------------------------------------
#
# Project created by QtCreator 2011-10-12T15:01:38
#
#-------------------------------------------------

QT       += core gui

TARGET = DiagramRecognizer
TEMPLATE = app


SOURCES += main.cpp\
        diagramrecognizer.cpp \
    bitmap.cpp \
    diagram.cpp \
    formsegmentator.cpp \
    simpleformsinitializer.cpp \
    recognizers/rectanglegesturesmanager.cpp \
    recognizers/nearestposgridgesturesmanager.cpp \
    recognizers/mixedgesturesmanager.cpp

HEADERS  += diagramrecognizer.h \
    geometricForms.h \
    bitmap.h \
    diagram.h \
    formsegmentator.h \
    abstractRecognizer.h \
    simpleformsinitializer.h \
    recognizers/rectanglegesturesmanager.h \
    recognizers/nearestposgridgesturesmanager.h \
    recognizers/mixedgesturesmanager.h \
    recognizers/curveKeyBuilder.h

FORMS    += diagramrecognizer.ui
