QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../armsim/
SOURCES +=  \
    ../armsim/instructionfactory.cpp \
    ../armsim/barrelshifter.cpp \
    ../armsim/immediateoperand.cpp \
    ../armsim/rotatedimmediateoperand.cpp \
    ../armsim/shiftedregisteroperand.cpp \
    ../armsim/immediateshiftedregisteroperand.cpp \
    ../armsim/registershiftedregisteroperand.cpp \
    ../armsim/registeroffsetoperand.cpp \
    ../armsim/loadstoremultipleinstruction.cpp \
    ../armsim/softwareinterruptinstruction.cpp \
    ../armsim/loadstoreinstruction.cpp \
    ../armsim/mulinstruction.cpp \
    ../armsim/dataprocessinginstruction.cpp \
    ../armsim/cpu.cpp \
    ../armsim/loader.cpp \
    ../armsim/memory.cpp \
    tst_loadertests.cpp
