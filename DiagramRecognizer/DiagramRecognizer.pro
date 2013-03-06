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
    newfigure.cpp \
    eItems.cpp \
    segmentator.cpp \
    connectedComponent.cpp \
    graph.cpp

HEADERS  += \
    geometricForms.h \
    bitmap.h \
    abstractRecognizer.h \
    recognizers/curveKeyBuilder.h \
    output.h \
    component.h \
    diagramRecognizer.h \
    formSegmentator.h \
    simpleFormsInitializer.h \
    recognizers/mixedGesturesManager.h \
    recognizers/nearestPosGridGesturesmanager.h \
    recognizers/rectangleGesturesManager.h \
    eItems.h \
    segmentator.h \
    connectedComponent.h \
    graph.h

FORMS    +=

OTHER_FILES += \
    readme.txt \
    Conception.jpg
