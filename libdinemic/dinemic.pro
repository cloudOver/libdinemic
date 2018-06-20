TEMPLATE = lib
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

DEFINES += DINEMIC_BUILD=true

INCLUDEPATH += ../
INCLUDEPATH += ../include

SOURCES += \
    store/redisdriver.cpp \
    store/memorydriver.cpp \
    store/storeinterface.cpp \
    sync/syncinterface.cpp \
    sync/dummysync.cpp \
    sync/redissync.cpp \
    sync/zeromqsync.cpp \
    utils.cpp \
    dfield.cpp \
    dmodel.cpp \
    dheaders.cpp \
    daction.cpp \
    dapp.cpp \
    dconfig.cpp \
    dcrypt.cpp \
    dexception.cpp \
    dapphelpers.cpp \
    logger.cpp

HEADERS += \
    store/redisdriver.h \
    store/memorydriver.h \
    store/storeinterface.h \
    sync/syncinterface.h \
    sync/dummysync.h \
    sync/redissync.h \
    sync/zeromqsync.h \
    utils.h \
    daction.h \
    dapp.h \
    dconfig.h \
    dcrypt.h \
    dexception.h \
    dfield.h \
    dheaders.h \
    dmodel.h \
    dapphelpers.h \
    logger.h \
    version.h


LIBS += -L/usr/lib/x86_64-linux-gnu/
LIBS += -L/usr/local/lib/
LIBS += -L/usr/local/Cellar/boost/1.60.0_2/lib/
LIBS += -L/usr/local/Cellar/hiredis/0.13.3/lib/
LIBS += -L/usr/local/Cellar/libevent/2.0.22/lib/
LIBS += -L/usr/local/Cellar/zeromq/4.1.4/lib/
LIBS += -L/usr/local/Cellar/libsodium/1.0.12/lib/
LIBS += -lboost_regex -lboost_filesystem -lboost_system -ldl  -lutil -lm
LIBS += -lcurl -lzmq -levent -lhiredis -lsodium -lpthread

INCLUDEPATH += /usr/local/include/
INCLUDEPATH += /usr/local/Cellar/boost/1.60.0_2/include/
INCLUDEPATH += /usr/local/Cellar/hiredis/0.13.3/include/
INCLUDEPATH += /usr/local/Cellar/libevent/2.0.22/include/
