#-------------------------------------------------
#
# Project created by QtCreator 2018-09-03T15:35:51
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = armsim
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11 console

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    hexspinbox.cpp \
    loaderwidget.cpp \
    loader.cpp \
    memory.cpp \
    cpu.cpp \
    computer.cpp \
    terminalwidget.cpp \
    memorywidget.cpp \
    flagswidget.cpp \
    registerswidget.cpp \
    disassemblywidget.cpp \
    stackwidget.cpp \
    computerwidget.cpp \
    runcontrolswidget.cpp \
    addbreakpointpopup.cpp \
    filewriter.cpp

HEADERS += \
        mainwindow.h \
    hexspinbox.h \
    loaderwidget.h \
    options.h \
    loader.h \
    elf.h \
    errorhandler.h \
    memory.h \
    cpu.h \
    computer.h \
    terminalwidget.h \
    memorywidget.h \
    flagswidget.h \
    registerswidget.h \
    disassemblywidget.h \
    stackwidget.h \
    computerwidget.h \
    runcontrolswidget.h \
    computerthreads.h \
    addbreakpointpopup.h \
    filewriter.h

FORMS += \
        mainwindow.ui \
    loaderwidget.ui \
    terminalwidget.ui \
    memorywidget.ui \
    flagswidget.ui \
    registerswidget.ui \
    disassemblywidget.ui \
    stackwidget.ui \
    runcontrolswidget.ui \
    addbreakpointpopup.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
