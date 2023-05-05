#-------------------------------------------------
#
# Project created by QtCreator 2023-05-04T09:00:05
#
#-------------------------------------------------

QT       += core
QT += network
QT       -= gui

TARGET = API_NUEVO_CONTROLADOR_V4
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    myudp.cpp

HEADERS += \
    variables.h \
    myudp.h
