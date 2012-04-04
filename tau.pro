# Copyright 2010 Brian F. Allen (vector@acm.org). All rights reserved.

SOURCES += 	robot.cpp \
			tau.cpp \
			OdeRobot.cpp \
			TauRobot.cpp 

HEADERS +=	OdeRobot.hpp \
			TauRobot.hpp \
			TauSystemIncludes.hpp \
			robot.hpp \
            tau.hpp 

INCLUDEPATH += /opt/local/include/ /opt/local/include/eigen2
INCLUDEPATH += /usr/local/include /usr/local/include/eigen2

QMAKE_CXXFLAGS += -pedantic -W -Wall -Wextra -Wno-unused-variable -Wno-unused-parameter
# -Wshadow -Wstrict-overflow=5 -Wwrite-strings

TEMPLATE = lib
QT -= gui core
CONFIG += debug x86_64
#CONFIG += static
CONFIG += staticlib
#CONFIG += lib_bundle
CONFIG += warn_on

VERSION = 0.1.1

CONFIG -= x86 #app_bundle

TARGET = tau
unix: LIBS += -lode -L/opt/local/lib -L/usr/local/lib

DEFINES += dDOUBLE
