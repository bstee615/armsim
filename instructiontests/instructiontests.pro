QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../armsim/
SOURCES +=  tst_instructiontests.cpp \
    ../armsim/cpu.cpp \
    ../armsim/instructionfactory.cpp \
    ../armsim/barrelshifter.cpp \
    ../armsim/instruction.cpp \
    ../armsim/loadstoreinstruction.cpp \
    ../armsim/loadstoremultipleinstruction.cpp \
    ../armsim/softwareinterruptinstruction.cpp \
    ../armsim/instructionoperand.cpp \
    ../armsim/dataprocessinginstruction.cpp \
    ../armsim/mulinstruction.cpp \
    ../armsim/immediateoperand.cpp \
    ../armsim/rotatedimmediateoperand.cpp \
    ../armsim/registershiftedregisteroperand.cpp \
    ../armsim/immediateshiftedregisteroperand.cpp \
    ../armsim/registeroffsetoperand.cpp \
    ../armsim/shiftedregisteroperand.cpp \
    ../armsim/memory.cpp
