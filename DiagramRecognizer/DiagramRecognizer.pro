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
    paintmanager.cpp \
    diagram.cpp \
    formsegmentator.cpp

HEADERS  += diagramrecognizer.h \
    geometricForms.h \
    bitmap.h \
    paintmanager.h \
    diagram.h \
    formsegmentator.h

FORMS    += diagramrecognizer.ui
