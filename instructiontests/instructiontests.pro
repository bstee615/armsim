QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../armsim/
SOURCES +=  tst_instructiontests.cpp \
    ../armsim/barrelshifter.cpp \
    ../armsim/dataprocessinginstruction.cpp \
    ../armsim/mulinstruction.cpp \
    ../armsim/rotatedimmediateoperand.cpp \
    ../armsim/registershiftedregisteroperand.cpp \
    ../armsim/immediateshiftedregisteroperand.cpp \
    ../armsim/shiftedregisteroperand.cpp \
    ../armsim/memory.cpp
