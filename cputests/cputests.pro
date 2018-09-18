QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../armsim/
SOURCES +=  tst_cputests.cpp \
    ../armsim/cpu.cpp \
    ../armsim/memory.cpp

HEADERS += \
    currenttime.h
