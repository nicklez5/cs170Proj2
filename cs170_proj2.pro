TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        class_obj.cpp \
        database.cpp \
        main.cpp

HEADERS += \
    class_obj.h \
    database.h

DISTFILES +=
# remove possible other optimization flags
QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2 

# add the desired -O3 if not present
QMAKE_CXXFLAGS_RELEASE *= -O3
