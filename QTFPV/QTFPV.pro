#-------------------------------------------------
#
# Project created by QtCreator 2015-02-08T12:29:58
#
#-------------------------------------------------
TARGET = QTFPV
TEMPLATE = app

# produce nice compilation output
CONFIG += silent

# Tell qmake to use pkg-config to find QtGStreamer.
CONFIG += link_pkgconfig

# Now tell qmake to link to QtGStreamer and also use its include path and Cflags.
contains(QT_VERSION, ^4\\..*) {
  PKGCONFIG += QtGStreamer-1.0 QtGStreamerUi-1.0 QtGStreamerUtils-1.0
}
contains(QT_VERSION, ^5\\..*) {
  PKGCONFIG += Qt5GStreamer-1.0 Qt5GStreamerUi-1.0
  QT += widgets
}

SOURCES += main.cpp\
    videodialog.cpp

HEADERS  += \
    videodialog.h

FORMS    += \
    videodialog.ui

# Recommended, to avoid possible issues with the "emit" keyword
# You can otherwise also define QT_NO_EMIT, but notice that this is not a documented Qt macro.
DEFINES += QT_NO_KEYWORDS
