#-------------------------------------------------
#
# Project created by QtCreator 2014-06-11T11:05:00
#
#-------------------------------------------------

QT       += core testlib

QT       -= gui

TARGET = Triples
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    Triple.cpp \
    TTriples.cpp \
    TripleStorage.cpp \
    Pair.cpp \
    TPair.cpp \
    TTripleStorage.cpp \
    BenchmarkResult.cpp

HEADERS += \
    Triple.h \
    TTriples.h \
    TripleStorage.h \
    Pair.h \
    TPair.h \
    TTripleStorage.h \
    BenchmarkResult.h
