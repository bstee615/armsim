QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../armsim/
SOURCES +=  tst_instructiontests.cpp \
    ../armsim/cpu.cpp \
    ../armsim/instructions/instructionfactory.cpp \
    ../armsim/barrelshifter.cpp \
    ../armsim/instructions/instruction.cpp \
    ../armsim/instructions/loadstoreinstruction.cpp \
    ../armsim/instructions/loadstoremultipleinstruction.cpp \
    ../armsim/instructions/softwareinterruptinstruction.cpp \
    ../armsim/instructions/instructionoperand.cpp \
    ../armsim/instructions/dataprocessinginstruction.cpp \
    ../armsim/instructions/mulinstruction.cpp \
    ../armsim/instructions/immediateoperand.cpp \
    ../armsim/instructions/rotatedimmediateoperand.cpp \
    ../armsim/instructions/registershiftedregisteroperand.cpp \
    ../armsim/instructions/immediateshiftedregisteroperand.cpp \
    ../armsim/instructions/registeroffsetoperand.cpp \
    ../armsim/instructions/shiftedregisteroperand.cpp \
    ../armsim/memory.cpp
