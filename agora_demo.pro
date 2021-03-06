#-------------------------------------------------
#
# Project created by QtCreator 2018-09-07T14:57:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = agora_demo
TEMPLATE = app


# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES *= AGORA_DEMO

INCLUDEPATH += $$PWD/base

OUTPUT_DIR=$$PWD/output
mac {
    PLATFORM_NAME = mac
    QT += macextras
    QMAKE_LFLAGS += -framework AppKit
    QMAKE_LFLAGS += -framework Carbon

}
CONFIG(debug, debug|release){
    DESTDIR  = $$OUTPUT_DIR/debug/$$PLATFORM_NAME/32bit
    OBJECTS_DIR = $$OUTPUT_DIR/$$TARGET/debug/obj
    MOC_DIR = $$OUTPUT_DIR/$$TARGET/debug/moc
    UI_DIR = $$OUTPUT_DIR/$$TARGET/debug/ui
    RCC_DIR = $$OUTPUT_DIR/$$TARGET/debug/rcc
}
CONFIG(release, debug|release){
    DESTDIR  = $$OUTPUT_DIR/release/$$PLATFORM_NAME/32bit
    OBJECTS_DIR = $$OUTPUT_DIR/$$TARGET/release/obj
    MOC_DIR = $$OUTPUT_DIR/$$TARGET/release/moc
    UI_DIR = $$OUTPUT_DIR/$$TARGET/release/ui
    RCC_DIR = $$OUTPUT_DIR/$$TARGET/release/rcc
}

INCLUDEPATH += agora/source
INCLUDEPATH += agora/source/Agora
#INCLUDEPATH += $$PWD/new

SOURCES += main.cpp\
    base/dclog.cpp \
    dialog.cpp \
    cagoraobject.cpp \
    cagoraeventhandler.cpp \
    base/cparamutils.cpp \
    base/cagorawidget.cpp \
    base/cagorawidget_mac.mm \
    base/cljagoralable.cpp

HEADERS  += base/dclog.h \
    base/dclogcontentdefine.h \
    base/clogsetting.h \
    dialog.h \
    cagoraobject.h \
    cagoraeventhandler.h \
    base/cparamutils.h \
    base/cagorawidget.h \
    base/cljagoralable.h

FORMS    += dialog.ui

include($$PWD/agora/agora.pri)
#include($$PWD/lj_agora.pri)
