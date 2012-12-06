#-------------------------------------------------
#
# Project created by QtCreator 2011-10-12T15:01:38
#
#-------------------------------------------------

QT       += core gui

TARGET = DiagramRecognizer
TEMPLATE = app


SOURCES += main.cpp\
    bitmap.cpp \
    output.cpp \
    component.cpp \
    diagramRecognizer.cpp \
    formSegmentator.cpp \
    simpleFormsInitializer.cpp \
    recognizers/mixedGesturesManager.cpp \
    recognizers/nearestPosGridGesturesManager.cpp \
    recognizers/rectangleGesturesManager.cpp \
    mainWindow.cpp

HEADERS  += \
    geometricForms.h \
    bitmap.h \
    abstractRecognizer.h \
    recognizers/curveKeyBuilder.h \
    output.h \
    component.h \
    figure.h \
    edge.h \
    diagramRecognizer.h \
    formSegmentator.h \
    simpleFormsInitializer.h \
    recognizers/mixedGesturesManager.h \
    recognizers/nearestPosGridGesturesmanager.h \
    recognizers/rectangleGesturesManager.h \
    mainWindow.h

FORMS    += \
    mainWindow.ui

OTHER_FILES += \
    readme.txt \
    Conception.jpg
