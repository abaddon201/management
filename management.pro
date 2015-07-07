TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    server/main.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    include/server/internal/factory.h \
    include/server/internal/market.h \
    include/server/internal/player.h \
    include/server/internal/ruleset.h \
    include/server/internal/session.h \
    include/server/internal/storage.h

QMAKE_CXXFLAGS += -std=c++14

INCLUDEPATH+= include/server/internal
