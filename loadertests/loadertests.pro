QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../armsim/
SOURCES +=  \
    ../armsim/instructions/instructionfactory.cpp \
    ../armsim/instructions/instruction.cpp \
    ../armsim/barrelshifter.cpp \
    ../armsim/instructions/immediateoperand.cpp \
    ../armsim/instructions/rotatedimmediateoperand.cpp \
    ../armsim/instructions/shiftedregisteroperand.cpp \
    ../armsim/instructions/immediateshiftedregisteroperand.cpp \
    ../armsim/instructions/registershiftedregisteroperand.cpp \
    ../armsim/instructions/registeroffsetoperand.cpp \
    ../armsim/instructions/loadstoremultipleinstruction.cpp \
    ../armsim/instructions/softwareinterruptinstruction.cpp \
    ../armsim/instructions/loadstoreinstruction.cpp \
    ../armsim/instructions/mulinstruction.cpp \
    ../armsim/instructions/dataprocessinginstruction.cpp \
    ../armsim/instructions/branchinstruction.cpp \
    ../armsim/instructions/branchandexchangeinstruction.cpp \
    ../armsim/instructions/statusregisterinstruction.cpp \
    ../armsim/cpu.cpp \
    ../armsim/loader.cpp \
    ../armsim/memory.cpp \
    ../armsim/registermemory.cpp \
    tst_loadertests.cpp
