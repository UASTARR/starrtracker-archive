TEMPLATE = app
QT       += core gui
QT       += serialport
QT       += qml quick
QT       += quickwidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    src/graph/Graph.cpp \
    src/graph/qcustomplot.cpp \
    src/serial/gpsparser.cpp \
    src/serial/serialthread.cpp \
    ui/mainwindow.cpp \
    ui/qledlabel.cpp \
    ui/sensor.cpp

HEADERS += \
    src/graph/Graph.h \
    src/graph/qcustomplot.h \
    src/serial/gpsparser.h \
    src/serial/serialthread.h \
    src/serial/validgpsformats.h \
    ui/mainwindow.h \
    ui/qledlabel.h \
    ui/sensor.h

FORMS += \
    ui/mainwindow.ui \
    ui/sensor.ui

RESOURCES += \
    map.qrc
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

INCLUDEPATH += $$PWD

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=


