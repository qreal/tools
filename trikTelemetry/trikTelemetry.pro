QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = trikTelemetry
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
	mainWindow.cpp \
	communicator.cpp \
	sensorsList.cpp \
	sensors3dList.cpp

HEADERS  += mainWindow.h \
	communicator.h \
	sensorData.h \
	sensorsList.h \
	sensors3dList.h

FORMS    += mainwindow.ui

TRANSLATIONS = trikTelemetry_ru.ts
