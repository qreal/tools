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
	userAction/userActionProperty/duration.cpp \
	widgetItemProperty/widgetItemCustomProperty.cpp \
	widgetItemProperty/widgetItemCustomPropertyList.cpp \
	propertiesDialog.cpp \
	complexActionNameDialog.cpp \
	complexActionDialog.cpp \
	findDialog.cpp \
	userAction/complexUserAction/complexUserActionList.cpp \
	ruleElement.cpp \
    scenarioActionsStatusForm.cpp


HEADERS  += mainwindow.h \
	userAction/userAction.h \
	userAction/baseUserAction/baseUserActionsParser.h \
	userAction/baseUserAction/baseUserAction.h \
	userAction/complexUserAction/complexUserActionParser.h \
	userAction/complexUserAction/complexUserAction.h \
	userAction/complexUserAction/complexUserActionGenerator.h \
	userAction/baseUserAction/baseUserActionList.h \
	userAction/userActionProperty/duration.h \
	widgetItemProperty/widgetItemCustomProperty.h \
	widgetItemProperty/widgetItemCustomPropertyList.h \
	propertiesDialog.h \
	complexActionNameDialog.h \
	complexActionDialog.h \
	findDialog.h \
	userAction/complexUserAction/complexUserActionList.h \
	ruleElement.h \
    scenarioActionsStatusForm.h \
    constants.h


FORMS  += mainwindow.ui \
	propertiesDialog.ui \
	complexActionNameDialog.ui \
	complexActionDialog.ui \
	findDialog.ui \
    scenarioActionsStatusForm.ui
