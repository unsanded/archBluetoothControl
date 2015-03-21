TEMPLATE = app

QT += qml quick widgets dbus xml
QMAKE_CXXFLAGS += -std=c++11
SOURCES += main.cpp \
    device.cpp \
    devicemanager.cpp \
    bluetoothtrayicon.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    device.h \
    devicemanager.h \
    bluetoothtrayicon.h
