TEMPLATE = app
QT += script
CONFIG += console

TARGET = robotRuntime

DESTDIR = bin

OBJECTS_DIR = .obj
MOC_DIR = .moc
RCC_DIR = .moc

HEADERS += \
	robotModel.h \

SOURCES += \
	main.cpp \
	robotModel.cpp \
