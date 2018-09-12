QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../armsim/
SOURCES +=  tst_loadertests.cpp \
    ../armsim/loader.cpp \
    ../armsim/memory.cpp
