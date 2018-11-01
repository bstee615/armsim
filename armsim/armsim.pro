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
    cpu.cpp \
    loader.cpp \
    memory.cpp \
    computer.cpp \
    filewriter.cpp \
    barrelshifter.cpp \
    ui/addbreakpointpopup.cpp \
    ui/computerwidget.cpp \
    ui/disassemblywidget.cpp \
    ui/flagswidget.cpp \
    ui/hexspinbox.cpp \
    ui/loaderwidget.cpp \
    ui/mainwindow.cpp \
    ui/memorywidget.cpp \
    ui/registerswidget.cpp \
    ui/runcontrolswidget.cpp \
    ui/stackwidget.cpp \
    ui/terminalwidget.cpp \
    main.cpp \
    instructions/dataprocessinginstruction.cpp \
    instructions/immediateoperand.cpp \
    instructions/immediateshiftedregisteroperand.cpp \
    instructions/instruction.cpp \
    instructions/instructionfactory.cpp \
    instructions/instructionoperand.cpp \
    instructions/loadstoreinstruction.cpp \
    instructions/loadstoremultipleinstruction.cpp \
    instructions/mulinstruction.cpp \
    instructions/registeroffsetoperand.cpp \
    instructions/registershiftedregisteroperand.cpp \
    instructions/rotatedimmediateoperand.cpp \
    instructions/shiftedregisteroperand.cpp \
    instructions/softwareinterruptinstruction.cpp \
    instructions/branchinstruction.cpp

HEADERS += \
    options.h \
    elf.h \
    errorhandler.h \
    memorytypes.h \
    cpu.h \
    loader.h \
    memory.h \
    computer.h \
    computerthreads.h \
    filewriter.h \
    barrelshifter.h \
    computer.h \
    ui/addbreakpointpopup.h \
    ui/computerwidget.h \
    ui/disassemblywidget.h \
    ui/flagswidget.h \
    ui/hexspinbox.h \
    ui/loaderwidget.h \
    ui/mainwindow.h \
    ui/memorywidget.h \
    ui/registerswidget.h \
    ui/runcontrolswidget.h \
    ui/stackwidget.h \
    ui/terminalwidget.h \
    testfiles.h \
    instructions/dataprocessinginstruction.h \
    instructions/immediateoperand.h \
    instructions/immediateshiftedregisteroperand.h \
    instructions/instruction.h \
    instructions/instructionfactory.h \
    instructions/instructionoperand.h \
    instructions/instructionutils.h \
    instructions/loadstoreinstruction.h \
    instructions/loadstoremultipleinstruction.h \
    instructions/mulinstruction.h \
    instructions/registeroffsetoperand.h \
    instructions/registershiftedregisteroperand.h \
    instructions/rotatedimmediateoperand.h \
    instructions/shiftedregisteroperand.h \
    instructions/softwareinterruptinstruction.h \
    instructions/branchinstruction.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    ui/addbreakpointpopup.ui \
    ui/disassemblywidget.ui \
    ui/flagswidget.ui \
    ui/loaderwidget.ui \
    ui/mainwindow.ui \
    ui/memorywidget.ui \
    ui/registerswidget.ui \
    ui/runcontrolswidget.ui \
    ui/stackwidget.ui \
    ui/terminalwidget.ui
