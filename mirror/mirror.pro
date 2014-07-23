QT += core
QT -= gui

TARGET = mirror

CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle

MOC_DIR = .moc
OBJECTS_DIR = .obj

TEMPLATE = app

HEADERS += \
	$$PWD/defines.h \
	$$PWD/argsParser.h \
	$$PWD/logEntry.h \
	$$PWD/worker.h \
	$$PWD/entryProcessor.h \
	$$PWD/os.h \

SOURCES += \
	$$PWD/main.cpp \
	$$PWD/argsParser.cpp \
	$$PWD/logEntry.cpp \
	$$PWD/entryProcessor.cpp \
	$$PWD/worker.cpp \

win32 {
	HEADERS += $$PWD/os/windows.h
	SOURCES += $$PWD/os/windows.cpp
}

unix {
	HEADERS += $$PWD/os/linux.h
	SOURCES += $$PWD/os/linux.cpp
}

macx {
	HEADERS += $$PWD/os/mac.h
	SOURCES += $$PWD/os/mac.cpp
}
