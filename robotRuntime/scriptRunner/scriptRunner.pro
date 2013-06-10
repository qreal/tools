TEMPLATE = app
QT += script
CONFIG += console

CONFIGURATION = debug

DESTDIR = $$CONFIGURATION/bin

INCLUDEPATH = ../trikControl/include

LIBS += -L../trikControl/$$CONFIGURATION/bin -ltrikControl

OBJECTS_DIR = $$CONFIGURATION/.obj
MOC_DIR = $$CONFIGURATION/.moc
RCC_DIR = $$CONFIGURATION/.moc

HEADERS += \
	scriptableParts.h \

SOURCES += \
	main.cpp \
	scriptableParts.cpp \

QMAKE_POST_LINK = "cmd /C \" xcopy ..\\trikControl\\$$CONFIGURATION\\bin $$CONFIGURATION\\bin /s /e /q /y /i\""
