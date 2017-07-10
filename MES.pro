#-------------------------------------------------
#
# Project created by QtCreator 2016-11-09T20:18:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MES
TEMPLATE = app
CONFIG += console


SOURCES += main.cpp\
        mainwindow.cpp \
    fertigungsauftrag.cpp \
    produktbeschreibung.cpp \
    bearbeitungsstatus.cpp \
    auftragsverwaltung.cpp \
    fertigungsauftragdialog.cpp \
    mesmqttnode.cpp \
    rfidtag.cpp \
    mesrfidtag.cpp \
    mqttnode.cpp

HEADERS  += mainwindow.h \
    fertigungsauftrag.h \
    produktbeschreibung.h \
    bearbeitungsstatus.h \
    auftragsverwaltung.h \
    fertigungsauftragdialog.h \
    mqttnode.h \
    mesmqttnode.h \
    rfidtag.h \
    mesrfidtag.h

FORMS    += mainwindow.ui \
    fertigungsauftragdialog.ui

RESOURCES += \
    mes.qrc
INCLUDEPATH += D:\\Vorlesungen\\SWT-SP1\\Prototyping\\MQTT\\inc
LIBS += -LD:\\Vorlesungen\\SWT-SP1\\Prototyping\\MQTT\\lib \
        libpaho-mqtt3c.dll
