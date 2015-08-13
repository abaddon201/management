#-------------------------------------------------
#
# Project created by QtCreator 2015-07-21T17:25:09
#
#-------------------------------------------------

QT       -= gui core

TARGET = tests
CONFIG   -= console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    market_test.cpp \
    ../../server/market.cpp \
    ../../server/session.cpp \
    ../../server/player.cpp \
    ../../server/ruleset.cpp \
    ../gtest/gtest_main.cc \
    session_test.cpp

INCLUDEPATH+= ../../include/server/internal ../../include/server
INCLUDEPATH+= ../gtest/include

QMAKE_CXXFLAGS += -std=c++14

macx {
QMAKE_CXXFLAGS += -stdlib=libc++
}

LIBS += ../../libs/libgtest.a
