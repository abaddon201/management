#-------------------------------------------------
#
# Project created by QtCreator 2015-07-21T17:20:25
#
#-------------------------------------------------

QT       -= core gui

TARGET = gtest
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    gtest-all.cc

INCLUDEPATH+= include

unix {
    target.path = ../../libs
    INSTALLS += target
}
