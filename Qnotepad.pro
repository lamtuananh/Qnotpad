#-------------------------------------------------
#
# Project created by QtCreator 2016-09-26T08:04:56
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qnotepad
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        mywindow.cpp \
    mysyntaxhighlighter.cpp \
    codeedit.cpp \
    linenumberarea.cpp \
    myfiledialog.cpp

HEADERS  += mainwindow.h \
        mywindow.h \
    mysyntaxhighlighter.h \
    codeedit.h \
    linenumberarea.h \
    myfiledialog.h

FORMS    += mainwindow.ui

RESOURCES += \
    appresources.qrc
