QT += core gui xml
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = analysisApp
TEMPLATE = app


SOURCES += main.cpp \
	mainwindow.cpp \
	userAction/userAction.cpp \
	userAction/baseUserAction/baseUserActionsParser.cpp \
	userAction/baseUserAction/baseUserAction.cpp \
	userAction/complexUserAction/complexUserActionParser.cpp \
	userAction/complexUserAction/complexUserAction.cpp \
	userAction/complexUserAction/complexUserActionGenerator.cpp \
    	userAction/baseUserAction/BaseUserActionList.cpp \
	widgetItemProperty/widgetItemCustomProperty.cpp \
	widgetItemProperty/widgetItemCustomPropertyList.cpp \
	propertiesDialog.cpp \
	complexActionNameDialog.cpp \
	logParser.cpp \
	complexActionDialog.cpp \
    	findDialog.cpp


HEADERS  += mainwindow.h \
	userAction/userAction.h \
	userAction/baseUserAction/baseUserActionsParser.h \
	userAction/baseUserAction/baseUserAction.h \
	userAction/complexUserAction/complexUserActionParser.h \
	userAction/complexUserAction/complexUserAction.h \
	userAction/complexUserAction/complexUserActionGenerator.h \
    	userAction/baseUserAction/baseUserActionList.h \
	widgetItemProperty/widgetItemCustomProperty.h \
	widgetItemProperty/widgetItemCustomPropertyList.h \
	propertiesDialog.h \
	complexActionNameDialog.h \
	logParser.h \
	complexActionDialog.h \
    	findDialog.h


FORMS  += mainwindow.ui \
	propertiesDialog.ui \
    	complexActionNameDialog.ui \
   	complexActionDialog.ui \
    	findDialog.ui
