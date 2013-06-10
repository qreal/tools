TEMPLATE = lib

DEFINES += TRIKCONTROL_LIBRARY

CONFIGURATION = debug

DESTDIR = $$CONFIGURATION/bin

OBJECTS_DIR = $$CONFIGURATION/.obj
MOC_DIR = $$CONFIGURATION/.moc
RCC_DIR = $$CONFIGURATION/.moc

INCLUDEPATH = include/trikControl

HEADERS += \
	include/trikControl/brick.h \
	include/trikControl/motor.h \
	include/trikControl/sensor.h \
	include/trikControl/declSpec.h \

SOURCES += \
	src/brick.cpp \
	src/motor.cpp \
	src/sensor.cpp \
