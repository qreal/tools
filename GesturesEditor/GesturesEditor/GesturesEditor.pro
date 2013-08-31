#-------------------------------------------------
#
# Project created by QtCreator 2012-11-16T09:26:44
#
#-------------------------------------------------

QT       += core gui
QT       += xml
QT	 += widgets

TARGET = GesturesEditor
TEMPLATE = app


SOURCES += main.cpp\
		gestEdit.cpp \
	scene.cpp \
	item.cpp \
	line.cpp \
	rectangle.cpp \
	ellipse.cpp \
	xmlLoader.cpp \
    curve.cpp \
    parser.cpp

INCLUDEPATH += ../bin/include/qrutils

HEADERS  += gestEdit.h \
	scene.h \
	item.h \
	line.h \
	rectangle.h \
	ellipse.h \
	xmlLoader.h \
    curve.h \
    parser.h \
    utilsDeclSpec.h

FORMS    += gestEdit.ui

LIBS += -L../bin/debug -lqrutils
LIBS += -L../bin/debug -lqrkernel


