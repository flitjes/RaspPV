#-------------------------------------------------
#
# Project created by QtCreator 2015-02-08T12:29:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Tell qmake to use pkg-config to find QtGStreamer.
CONFIG += link_pkgconfig

# Now tell qmake to link to QtGStreamer and also use its include path and Cflags.
contains(QT_VERSION, ^4\\..*) {
  PKGCONFIG += QtGStreamer-0.10 QtGStreamerUi-0.10
}

TARGET = QTFPV
TEMPLATE = app


SOURCES += main.cpp\
        fpvgui.cpp

HEADERS  += fpvgui.h

FORMS    += fpvgui.ui
