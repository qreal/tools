QT += core gui xml
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = analysisApp
TEMPLATE = app

R_HOME = $$system(R RHOME)

RRPATH = -Wl,-rpath,$$R_HOME/lib

RCPPFLAGS = $$system($$R_HOME/bin/R CMD config --cppflags)
RLDFLAGS = $$system($$R_HOME/bin/R CMD config --ldflags)
RBLAS = $$system($$R_HOME/bin/R CMD config BLAS_LIBS)
RLAPACK = $$system($$R_HOME/bin/R CMD config LAPACK_LIBS)

RCPPINCL = $$system($$R_HOME/bin/Rscript -e \"Rcpp:::CxxFlags()\")

RCPPLIBS = $$system($$R_HOME/bin/Rscript -e \'Rcpp:::LdFlags\(\)\')

RCPPWARNING = -Wno-unused-parameter
RINSIDEINCL = $$system($$R_HOME/bin/Rscript -e \'RInside:::CxxFlags\(\)\')
RINSIDELIBS = $$system($$R_HOME/bin/Rscript -e \'RInside:::LdFlags\(\)\')

QMAKE_CXXFLAGS += $$RCPPWARNING $$RCPPFLAGS $$RCPPINCL $$RINSIDEINCL
QMAKE_LFLAGS += $$RLDFLAGS $$RBLAS $$RLAPACK $$RCPPLIBS $$RINSIDELIBS
QMAKE_LIBS += $$RLDFLAGS $$RBLAS $$RLAPACK $$RINSIDELIBS $$RCPPLIBS

INCLUDEPATH += $$R_HOME/include
INCLUDEPATH += "C:\\tmp\\R\\R-3.1.0\\include"
INCLUDEPATH += C:\\Users\\me\\Documents\\R\\win-library\\3.1\\Rcpp\\include
INCLUDEPATH += C:\\Users\\me\\Documents\R\\win-library\\3.1\\RInside\\include

LIBS += -LC:\Program\ Files\R\R-3.1.0\bin\x64 -lR
LIBS += -LC:\Users\me\Documents\R\win-library\3.1\Rcpp\lib\x64 -lRcpp
LIBS += -LC:\Users\me\Documents\R\win-library\3.1\RInside\lib\x64 -lRInside

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
