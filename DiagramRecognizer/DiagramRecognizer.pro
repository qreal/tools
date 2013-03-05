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
    formSegmentator.cpp \
    simpleFormsInitializer.cpp \
    recognizers/mixedGesturesManager.cpp \
    recognizers/nearestPosGridGesturesManager.cpp \
    recognizers/rectangleGesturesManager.cpp \
    diagramMainWIndow.cpp

HEADERS  += \
    geometricForms.h \
    bitmap.h \
    abstractRecognizer.h \
    recognizers/curveKeyBuilder.h \
    output.h \
    component.h \
    figure.h \
    edge.h \
    formSegmentator.h \
    simpleFormsInitializer.h \
    recognizers/mixedGesturesManager.h \
    recognizers/nearestPosGridGesturesmanager.h \
    recognizers/rectangleGesturesManager.h \
    diagramMainWindow.h

FORMS    += \
    mainWindow.ui

OTHER_FILES += \
    readme.txt \
    Conception.jpg
