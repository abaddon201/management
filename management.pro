TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    server/player.cpp \
    server/market.cpp \
    server/session.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    server/player.h \
    server/market.h \
    server/session.h

