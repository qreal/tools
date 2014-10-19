QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = trikTelemetry
TEMPLATE = app


SOURCES += main.cpp\
		mainWindow.cpp \
    communicator.cpp

HEADERS  += mainWindow.h \
    communicator.h

FORMS    += mainwindow.ui
