TEMPLATE = app
QT       += core gui
QT       += serialport
QT       += qml quick
QT       += quickwidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
#    src/RocketMath.cpp \
#    src/map/FlightTrajectory.cpp \
#    src/map/Position.cpp \
#    src/map/position.cpp \
    src/graph/Graph.cpp \
    src/graph/qcustomplot.cpp \
    src/serial/gpsparser.cpp \
    src/serial/serialthread.cpp \
    ui/mainwindow.cpp \
    ui/sensor.cpp

HEADERS += \
#    src/RocketMath.h \
#    src/map/FlightTrajectory.h \
#    src/map/Position.h \
#    src/map/position.h \
    src/graph/Graph.h \
    src/graph/qcustomplot.h \
    src/serial/gpsparser.h \
    src/serial/serialthread.h \
    src/serial/validgpsformats.h \
    ui/mainwindow.h \
    ui/sensor.h

FORMS += \
    ui/mainwindow.ui \
    ui/sensor.ui

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = /usr/lib/x86_64-linux-gnu/qt5/qml

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += $$PWD

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
