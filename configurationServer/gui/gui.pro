#-------------------------------------------------
#
# Project created by QtCreator 2014-07-03T12:21:10
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
    preferencesDialog.cpp \
    preferencesPages/behaviourPage.cpp \
    preferencesPages/debuggerPage.cpp \
    preferencesPages/editorPage.cpp \
    preferencesPages/featuresPage.cpp \
    preferencesPages/miscellaniousPage.cpp \
    qrkernel/ids.cpp \
    qrkernel/settingsManager.cpp \
    qrkernel/timeMeasurer.cpp \
    qrkernel/version.cpp \
    qrutils/qRealFileDialog.cpp \
    brandManager/brandManager.cpp \
    hotKeyManager/hotKeyManager.cpp \
    hotKeyManager/hotKeyManagerPage.cpp \
    hotKeyManager/shortcutEdit.cpp \
    qrutils/qRealDialog.cpp \
    widget.cpp

HEADERS  += \
    preferencesDialog.h \
    preferencesPages/behaviourPage.h \
    preferencesPages/debuggerPage.h \
    preferencesPages/editorPage.h \
    preferencesPages/featuresPage.h \
    preferencesPages/miscellaniousPage.h \
    preferencesPages/preferencesPage.h \
    qrkernel/definitions.h \
    qrkernel/ids.h \
    qrkernel/kernelDeclSpec.h \
    qrkernel/roles.h \
    qrkernel/settingsManager.h \
    qrkernel/timeMeasurer.h \
    qrkernel/version.h \
    qrutils/qRealFileDialog.h \
    brandManager/brandManager.h \
    brandManager/fonts.h \
    brandManager/styles.h \
    hotKeyManager/hotKeyManager.h \
    hotKeyManager/hotKeyManagerPage.h \
    hotKeyManager/shortcutEdit.h \
    qrutils/qRealDialog.h \
    widget.h \
    ui_widget.h

FORMS    += \
    preferencesDialog.ui \
    preferencesPages/behaviourPage.ui \
    preferencesPages/debuggerPage.ui \
    preferencesPages/editorPage.ui \
    preferencesPages/featuresPage.ui \
    preferencesPages/miscellaniousPage.ui \
    hotKeyManager/hotKeyManagerPage.ui \
    widget.ui

SUBDIRS += \
    qrkernel/qrkernel.pro

OTHER_FILES +=

RESOURCES +=
