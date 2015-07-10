TEMPLATE = app
CONFIG += console
CONFIG += c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    server/main.cpp \
    server/session.cpp \
    server/market.cpp \
    server/ruleset.cpp \
    server/player.cpp \
    server/server.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    include/server/internal/factory.h \
    include/server/internal/market.h \
    include/server/internal/player.h \
    include/server/internal/ruleset.h \
    include/server/internal/session.h \
    include/server/internal/storage.h \
    include/server/internal/server.h \
    include/rapidjson/error/en.h \
    include/rapidjson/error/error.h \
    include/rapidjson/internal/biginteger.h \
    include/rapidjson/internal/diyfp.h \
    include/rapidjson/internal/dtoa.h \
    include/rapidjson/internal/ieee754.h \
    include/rapidjson/internal/itoa.h \
    include/rapidjson/internal/meta.h \
    include/rapidjson/internal/pow10.h \
    include/rapidjson/internal/stack.h \
    include/rapidjson/internal/strfunc.h \
    include/rapidjson/internal/strtod.h \
    include/rapidjson/msinttypes/inttypes.h \
    include/rapidjson/msinttypes/stdint.h \
    include/rapidjson/allocators.h \
    include/rapidjson/document.h \
    include/rapidjson/encodedstream.h \
    include/rapidjson/encodings.h \
    include/rapidjson/filereadstream.h \
    include/rapidjson/filewritestream.h \
    include/rapidjson/memorybuffer.h \
    include/rapidjson/memorystream.h \
    include/rapidjson/pointer.h \
    include/rapidjson/prettywriter.h \
    include/rapidjson/rapidjson.h \
    include/rapidjson/reader.h \
    include/rapidjson/stringbuffer.h \
    include/rapidjson/writer.h \
    include/server/rapidjson/error/en.h \
    include/server/rapidjson/error/error.h \
    include/server/rapidjson/internal/biginteger.h \
    include/server/rapidjson/internal/diyfp.h \
    include/server/rapidjson/internal/dtoa.h \
    include/server/rapidjson/internal/ieee754.h \
    include/server/rapidjson/internal/itoa.h \
    include/server/rapidjson/internal/meta.h \
    include/server/rapidjson/internal/pow10.h \
    include/server/rapidjson/internal/stack.h \
    include/server/rapidjson/internal/strfunc.h \
    include/server/rapidjson/internal/strtod.h \
    include/server/rapidjson/msinttypes/inttypes.h \
    include/server/rapidjson/msinttypes/stdint.h \
    include/server/rapidjson/allocators.h \
    include/server/rapidjson/document.h \
    include/server/rapidjson/encodedstream.h \
    include/server/rapidjson/encodings.h \
    include/server/rapidjson/filereadstream.h \
    include/server/rapidjson/filewritestream.h \
    include/server/rapidjson/memorybuffer.h \
    include/server/rapidjson/memorystream.h \
    include/server/rapidjson/pointer.h \
    include/server/rapidjson/prettywriter.h \
    include/server/rapidjson/rapidjson.h \
    include/server/rapidjson/reader.h \
    include/server/rapidjson/stringbuffer.h \
    include/server/rapidjson/writer.h


QMAKE_CXXFLAGS += -std=c++14 -stdlib=libc++

INCLUDEPATH+= include/server/
