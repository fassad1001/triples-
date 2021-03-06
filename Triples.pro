#-------------------------------------------------
#
# Project created by QtCreator 2014-06-11T11:05:00
#
#-------------------------------------------------

QT       += core testlib
QT       += sql

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
    BenchmarkResult.cpp \
    Ontology.cpp \
    TOntology.cpp \
    Class.cpp \
    OntologyBuilder.cpp \
    TOntologyBuilder.cpp \
    OntologyGenerator.cpp \
    OntologyBenchmark.cpp \
    OntologyDataBaseInterface.cpp \
    TOntologyDataBaseInterface.cpp \
    OntologyDataBaseReader.cpp \
    TOntologyDataBaseReader.cpp \
    OntologyDataBaseWriter.cpp \
    TOntologyDataBaseWriter.cpp

HEADERS += \
    Triple.h \
    TTriples.h \
    TripleStorage.h \
    Pair.h \
    TPair.h \
    TTripleStorage.h \
    BenchmarkResult.h \
    Ontology.h \
    TOntology.h \
    Class.h \
    OntologyBuilder.h \
    TOntologyBuilder.h \
    OntologyGenerator.h \
    OntologyBenchmark.h \
    OntologyDataBaseInterface.h \
    TOntologyDataBaseInterface.h \
    OntologyDataBaseReader.h \
    TOntologyDataBaseReader.h \
    OntologyDataBaseWriter.h \
    TOntologyDataBaseWriter.h
