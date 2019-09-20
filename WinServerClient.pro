QT += core widgets network

TEMPLATE = app
TARGET = WinServerClient

INCLUDE = include
SRC = src
UI = ui

INCLUDEPATH += $${INCLUDE}

SOURCES += $${SRC}/main.cpp

HEADERS += $${INCLUDE}/QClient.h
SOURCES += $${SRC}/QClient.cpp

HEADERS += $${INCLUDE}/QNetworkHandler.h
SOURCES += $${SRC}/QNetworkHandler.cpp

FORMS += $${UI}/MainWidget.ui
