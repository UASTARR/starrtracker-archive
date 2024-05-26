/********************************************************************************
** Form generated from reading UI file 'sensor.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENSOR_H
#define UI_SENSOR_H

#include <QtCore/QVariant>
#include <QtQuickWidgets/QQuickWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <src/graph/qcustomplot.h>
#include "ui/qledlabel.h"

QT_BEGIN_NAMESPACE

class Ui_Sensor
{
public:
    QWidget *horizontalLayoutWidget;
    QGridLayout *gpsDash;
    QVBoxLayout *layout_Settings;
    QGridLayout *layout_Serial;
    QGroupBox *serial_connect;
    QComboBox *portSelect;
    QPushButton *serialConnectionButton;
    QPushButton *serialTerminationButton;
    QLabel *port;
    QLabel *baud;
    QComboBox *baudSelect;
    QRadioButton *saveButton;
    QLabel *statusLabel;
    QLedLabel *ledIndicator;
    QGroupBox *gps_data_display;
    QTextBrowser *textbrowser;
    QLabel *gpstype;
    QGroupBox *local_data;
    QLabel *path;
    QTextBrowser *pathBrowser;
    QPushButton *serialLocalConnectionButton;
    QPushButton *serialLocalTerminationButton;
    QVBoxLayout *layout_Display;
    QStackedWidget *stackedDisplay;
    QWidget *Map;
    QWidget *layoutWidget_2;
    QVBoxLayout *layout_map;
    QLabel *Label_LiveRocketView;
    QQuickWidget *QW_Map;
    QPushButton *next;
    QPushButton *resetBtn1;
    QWidget *Graph;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *layout_graph;
    QLabel *Label_LiveRocketData;
    QGridLayout *graph_display;
    QVBoxLayout *layout_altitude;
    QLabel *altitude;
    QCustomPlot *graph_alt;
    QVBoxLayout *layout_x_axis;
    QLabel *x_axis;
    QCustomPlot *graph_x;
    QVBoxLayout *layout_y_axis;
    QLabel *y_axis;
    QCustomPlot *graph_y;
    QPushButton *prev;
    QPushButton *resetBtn2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QTextBrowser *outputScreen;

    void setupUi(QWidget *Sensor)
    {
        if (Sensor->objectName().isEmpty())
            Sensor->setObjectName(QString::fromUtf8("Sensor"));
        Sensor->resize(1300, 775);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Sensor->sizePolicy().hasHeightForWidth());
        Sensor->setSizePolicy(sizePolicy);
        horizontalLayoutWidget = new QWidget(Sensor);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 1291, 771));
        gpsDash = new QGridLayout(horizontalLayoutWidget);
        gpsDash->setObjectName(QString::fromUtf8("gpsDash"));
        gpsDash->setSizeConstraint(QLayout::SetMinimumSize);
        gpsDash->setHorizontalSpacing(14);
        gpsDash->setVerticalSpacing(12);
        gpsDash->setContentsMargins(6, 0, 0, 0);
        layout_Settings = new QVBoxLayout();
        layout_Settings->setSpacing(6);
        layout_Settings->setObjectName(QString::fromUtf8("layout_Settings"));
        layout_Settings->setSizeConstraint(QLayout::SetDefaultConstraint);
        layout_Serial = new QGridLayout();
        layout_Serial->setObjectName(QString::fromUtf8("layout_Serial"));
        layout_Serial->setSizeConstraint(QLayout::SetFixedSize);
        serial_connect = new QGroupBox(horizontalLayoutWidget);
        serial_connect->setObjectName(QString::fromUtf8("serial_connect"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(serial_connect->sizePolicy().hasHeightForWidth());
        serial_connect->setSizePolicy(sizePolicy1);
        serial_connect->setMinimumSize(QSize(345, 207));
        portSelect = new QComboBox(serial_connect);
        portSelect->setObjectName(QString::fromUtf8("portSelect"));
        portSelect->setGeometry(QRect(50, 30, 79, 22));
        serialConnectionButton = new QPushButton(serial_connect);
        serialConnectionButton->setObjectName(QString::fromUtf8("serialConnectionButton"));
        serialConnectionButton->setGeometry(QRect(10, 90, 80, 22));
        serialTerminationButton = new QPushButton(serial_connect);
        serialTerminationButton->setObjectName(QString::fromUtf8("serialTerminationButton"));
        serialTerminationButton->setEnabled(false);
        serialTerminationButton->setGeometry(QRect(100, 90, 80, 22));
        port = new QLabel(serial_connect);
        port->setObjectName(QString::fromUtf8("port"));
        port->setGeometry(QRect(10, 30, 41, 17));
        baud = new QLabel(serial_connect);
        baud->setObjectName(QString::fromUtf8("baud"));
        baud->setGeometry(QRect(140, 30, 81, 20));
        baudSelect = new QComboBox(serial_connect);
        baudSelect->addItem(QString());
        baudSelect->addItem(QString());
        baudSelect->addItem(QString());
        baudSelect->addItem(QString());
        baudSelect->addItem(QString());
        baudSelect->addItem(QString());
        baudSelect->addItem(QString());
        baudSelect->addItem(QString());
        baudSelect->addItem(QString());
        baudSelect->addItem(QString());
        baudSelect->addItem(QString());
        baudSelect->addItem(QString());
        baudSelect->addItem(QString());
        baudSelect->addItem(QString());
        baudSelect->setObjectName(QString::fromUtf8("baudSelect"));
        baudSelect->setGeometry(QRect(220, 30, 86, 25));
        saveButton = new QRadioButton(serial_connect);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setGeometry(QRect(10, 60, 141, 23));
        saveButton->setChecked(false);
        statusLabel = new QLabel(serial_connect);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));
        statusLabel->setGeometry(QRect(10, 140, 161, 21));
        ledIndicator = new QLedLabel(serial_connect);
        ledIndicator->setObjectName(QString::fromUtf8("ledIndicator"));
        ledIndicator->setGeometry(QRect(170, 140, 80, 21));

        layout_Serial->addWidget(serial_connect, 0, 0, 1, 1);

        gps_data_display = new QGroupBox(horizontalLayoutWidget);
        gps_data_display->setObjectName(QString::fromUtf8("gps_data_display"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(gps_data_display->sizePolicy().hasHeightForWidth());
        gps_data_display->setSizePolicy(sizePolicy2);
        textbrowser = new QTextBrowser(gps_data_display);
        textbrowser->setObjectName(QString::fromUtf8("textbrowser"));
        textbrowser->setEnabled(true);
        textbrowser->setGeometry(QRect(10, 60, 311, 192));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(textbrowser->sizePolicy().hasHeightForWidth());
        textbrowser->setSizePolicy(sizePolicy3);
        gpstype = new QLabel(gps_data_display);
        gpstype->setObjectName(QString::fromUtf8("gpstype"));
        gpstype->setGeometry(QRect(10, 30, 341, 21));
        gpstype->setFrameShape(QFrame::NoFrame);

        layout_Serial->addWidget(gps_data_display, 2, 0, 1, 1);

        local_data = new QGroupBox(horizontalLayoutWidget);
        local_data->setObjectName(QString::fromUtf8("local_data"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(local_data->sizePolicy().hasHeightForWidth());
        local_data->setSizePolicy(sizePolicy4);
        local_data->setMinimumSize(QSize(0, 110));
        path = new QLabel(local_data);
        path->setObjectName(QString::fromUtf8("path"));
        path->setGeometry(QRect(10, 30, 41, 17));
        pathBrowser = new QTextBrowser(local_data);
        pathBrowser->setObjectName(QString::fromUtf8("pathBrowser"));
        pathBrowser->setGeometry(QRect(60, 30, 251, 41));
        pathBrowser->setReadOnly(false);
        serialLocalConnectionButton = new QPushButton(local_data);
        serialLocalConnectionButton->setObjectName(QString::fromUtf8("serialLocalConnectionButton"));
        serialLocalConnectionButton->setGeometry(QRect(10, 80, 80, 22));
        serialLocalTerminationButton = new QPushButton(local_data);
        serialLocalTerminationButton->setObjectName(QString::fromUtf8("serialLocalTerminationButton"));
        serialLocalTerminationButton->setEnabled(false);
        serialLocalTerminationButton->setGeometry(QRect(100, 80, 80, 22));

        layout_Serial->addWidget(local_data, 1, 0, 1, 1);


        layout_Settings->addLayout(layout_Serial);


        gpsDash->addLayout(layout_Settings, 0, 2, 1, 1);

        layout_Display = new QVBoxLayout();
        layout_Display->setObjectName(QString::fromUtf8("layout_Display"));
        layout_Display->setContentsMargins(-1, -1, -1, 0);
        stackedDisplay = new QStackedWidget(horizontalLayoutWidget);
        stackedDisplay->setObjectName(QString::fromUtf8("stackedDisplay"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(stackedDisplay->sizePolicy().hasHeightForWidth());
        stackedDisplay->setSizePolicy(sizePolicy5);
        Map = new QWidget();
        Map->setObjectName(QString::fromUtf8("Map"));
        Map->setContextMenuPolicy(Qt::PreventContextMenu);
        layoutWidget_2 = new QWidget(Map);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(0, 0, 921, 611));
        layout_map = new QVBoxLayout(layoutWidget_2);
        layout_map->setObjectName(QString::fromUtf8("layout_map"));
        layout_map->setContentsMargins(0, 0, 0, 0);
        Label_LiveRocketView = new QLabel(layoutWidget_2);
        Label_LiveRocketView->setObjectName(QString::fromUtf8("Label_LiveRocketView"));
        QSizePolicy sizePolicy6(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(Label_LiveRocketView->sizePolicy().hasHeightForWidth());
        Label_LiveRocketView->setSizePolicy(sizePolicy6);
        Label_LiveRocketView->setMaximumSize(QSize(1209, 16777215));
        QFont font;
        font.setPointSize(24);
        Label_LiveRocketView->setFont(font);

        layout_map->addWidget(Label_LiveRocketView);

        QW_Map = new QQuickWidget(layoutWidget_2);
        QW_Map->setObjectName(QString::fromUtf8("QW_Map"));
        QW_Map->setResizeMode(QQuickWidget::SizeRootObjectToView);

        layout_map->addWidget(QW_Map);

        next = new QPushButton(Map);
        next->setObjectName(QString::fromUtf8("next"));
        next->setGeometry(QRect(850, 10, 61, 29));
        resetBtn1 = new QPushButton(Map);
        resetBtn1->setObjectName(QString::fromUtf8("resetBtn1"));
        resetBtn1->setGeometry(QRect(740, 10, 105, 29));
        stackedDisplay->addWidget(Map);
        Graph = new QWidget();
        Graph->setObjectName(QString::fromUtf8("Graph"));
        verticalLayoutWidget_2 = new QWidget(Graph);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(0, 0, 921, 611));
        layout_graph = new QVBoxLayout(verticalLayoutWidget_2);
        layout_graph->setObjectName(QString::fromUtf8("layout_graph"));
        layout_graph->setContentsMargins(0, 0, 0, 0);
        Label_LiveRocketData = new QLabel(verticalLayoutWidget_2);
        Label_LiveRocketData->setObjectName(QString::fromUtf8("Label_LiveRocketData"));
        sizePolicy6.setHeightForWidth(Label_LiveRocketData->sizePolicy().hasHeightForWidth());
        Label_LiveRocketData->setSizePolicy(sizePolicy6);
        Label_LiveRocketData->setFont(font);

        layout_graph->addWidget(Label_LiveRocketData);

        graph_display = new QGridLayout();
        graph_display->setSpacing(6);
        graph_display->setObjectName(QString::fromUtf8("graph_display"));
        layout_altitude = new QVBoxLayout();
        layout_altitude->setObjectName(QString::fromUtf8("layout_altitude"));
        altitude = new QLabel(verticalLayoutWidget_2);
        altitude->setObjectName(QString::fromUtf8("altitude"));
        sizePolicy6.setHeightForWidth(altitude->sizePolicy().hasHeightForWidth());
        altitude->setSizePolicy(sizePolicy6);
        QFont font1;
        font1.setPointSize(16);
        altitude->setFont(font1);

        layout_altitude->addWidget(altitude);

        graph_alt = new QCustomPlot(verticalLayoutWidget_2);
        graph_alt->setObjectName(QString::fromUtf8("graph_alt"));

        layout_altitude->addWidget(graph_alt);


        graph_display->addLayout(layout_altitude, 0, 0, 2, 1);

        layout_x_axis = new QVBoxLayout();
        layout_x_axis->setObjectName(QString::fromUtf8("layout_x_axis"));
        x_axis = new QLabel(verticalLayoutWidget_2);
        x_axis->setObjectName(QString::fromUtf8("x_axis"));
        sizePolicy6.setHeightForWidth(x_axis->sizePolicy().hasHeightForWidth());
        x_axis->setSizePolicy(sizePolicy6);
        x_axis->setFont(font1);

        layout_x_axis->addWidget(x_axis);

        graph_x = new QCustomPlot(verticalLayoutWidget_2);
        graph_x->setObjectName(QString::fromUtf8("graph_x"));
        graph_x->setMaximumSize(QSize(875, 16777215));

        layout_x_axis->addWidget(graph_x);


        graph_display->addLayout(layout_x_axis, 0, 1, 1, 1);

        layout_y_axis = new QVBoxLayout();
        layout_y_axis->setObjectName(QString::fromUtf8("layout_y_axis"));
        y_axis = new QLabel(verticalLayoutWidget_2);
        y_axis->setObjectName(QString::fromUtf8("y_axis"));
        sizePolicy6.setHeightForWidth(y_axis->sizePolicy().hasHeightForWidth());
        y_axis->setSizePolicy(sizePolicy6);
        QFont font2;
        font2.setPointSize(16);
        font2.setBold(false);
        y_axis->setFont(font2);

        layout_y_axis->addWidget(y_axis);

        graph_y = new QCustomPlot(verticalLayoutWidget_2);
        graph_y->setObjectName(QString::fromUtf8("graph_y"));

        layout_y_axis->addWidget(graph_y);


        graph_display->addLayout(layout_y_axis, 1, 1, 1, 1);


        layout_graph->addLayout(graph_display);

        prev = new QPushButton(Graph);
        prev->setObjectName(QString::fromUtf8("prev"));
        prev->setGeometry(QRect(850, 10, 61, 29));
        resetBtn2 = new QPushButton(Graph);
        resetBtn2->setObjectName(QString::fromUtf8("resetBtn2"));
        resetBtn2->setGeometry(QRect(740, 10, 105, 29));
        stackedDisplay->addWidget(Graph);

        layout_Display->addWidget(stackedDisplay);


        gpsDash->addLayout(layout_Display, 0, 1, 1, 1);

        scrollArea = new QScrollArea(horizontalLayoutWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        QSizePolicy sizePolicy7(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy7);
        scrollArea->setMinimumSize(QSize(0, 150));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 1282, 148));
        QSizePolicy sizePolicy8(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(scrollAreaWidgetContents_2->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents_2->setSizePolicy(sizePolicy8);
        outputScreen = new QTextBrowser(scrollAreaWidgetContents_2);
        outputScreen->setObjectName(QString::fromUtf8("outputScreen"));
        outputScreen->setGeometry(QRect(0, 0, 1281, 151));
        outputScreen->setMinimumSize(QSize(0, 120));
        scrollArea->setWidget(scrollAreaWidgetContents_2);

        gpsDash->addWidget(scrollArea, 1, 1, 1, 2);


        retranslateUi(Sensor);

        stackedDisplay->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Sensor);
    } // setupUi

    void retranslateUi(QWidget *Sensor)
    {
        Sensor->setWindowTitle(QCoreApplication::translate("Sensor", "Form", nullptr));
        serial_connect->setTitle(QCoreApplication::translate("Sensor", "Serial Connections", nullptr));
        serialConnectionButton->setText(QCoreApplication::translate("Sensor", "Start", nullptr));
        serialTerminationButton->setText(QCoreApplication::translate("Sensor", "Stop", nullptr));
        port->setText(QCoreApplication::translate("Sensor", "Port ", nullptr));
        baud->setText(QCoreApplication::translate("Sensor", "Baud rate", nullptr));
        baudSelect->setItemText(0, QCoreApplication::translate("Sensor", "110", nullptr));
        baudSelect->setItemText(1, QCoreApplication::translate("Sensor", "300", nullptr));
        baudSelect->setItemText(2, QCoreApplication::translate("Sensor", "600", nullptr));
        baudSelect->setItemText(3, QCoreApplication::translate("Sensor", "1200", nullptr));
        baudSelect->setItemText(4, QCoreApplication::translate("Sensor", "2400", nullptr));
        baudSelect->setItemText(5, QCoreApplication::translate("Sensor", "4800", nullptr));
        baudSelect->setItemText(6, QCoreApplication::translate("Sensor", "9600", nullptr));
        baudSelect->setItemText(7, QCoreApplication::translate("Sensor", "14400", nullptr));
        baudSelect->setItemText(8, QCoreApplication::translate("Sensor", "19200", nullptr));
        baudSelect->setItemText(9, QCoreApplication::translate("Sensor", "38400", nullptr));
        baudSelect->setItemText(10, QCoreApplication::translate("Sensor", "57600", nullptr));
        baudSelect->setItemText(11, QCoreApplication::translate("Sensor", "115200", nullptr));
        baudSelect->setItemText(12, QCoreApplication::translate("Sensor", "128000", nullptr));
        baudSelect->setItemText(13, QCoreApplication::translate("Sensor", "256000", nullptr));

        saveButton->setText(QCoreApplication::translate("Sensor", "Save Data", nullptr));
        statusLabel->setText(QCoreApplication::translate("Sensor", "Connection Status", nullptr));
        ledIndicator->setText(QString());
        gps_data_display->setTitle(QCoreApplication::translate("Sensor", "GPS Data", nullptr));
        textbrowser->setHtml(QCoreApplication::translate("Sensor", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:11pt;\"><br /></p></body></html>", nullptr));
        gpstype->setText(QCoreApplication::translate("Sensor", "...", nullptr));
        local_data->setTitle(QCoreApplication::translate("Sensor", "Read Local Data", nullptr));
        path->setText(QCoreApplication::translate("Sensor", "Path", nullptr));
        pathBrowser->setHtml(QCoreApplication::translate("Sensor", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:11pt;\"><br /></p></body></html>", nullptr));
        serialLocalConnectionButton->setText(QCoreApplication::translate("Sensor", "Start", nullptr));
        serialLocalTerminationButton->setText(QCoreApplication::translate("Sensor", "Stop", nullptr));
        Label_LiveRocketView->setText(QCoreApplication::translate("Sensor", "Live Rocket Position", nullptr));
        next->setText(QCoreApplication::translate("Sensor", "Next", nullptr));
        resetBtn1->setText(QCoreApplication::translate("Sensor", "Reset Plot", nullptr));
        Label_LiveRocketData->setText(QCoreApplication::translate("Sensor", "Live Rocket Data", nullptr));
        altitude->setText(QCoreApplication::translate("Sensor", "Altitude (1 Unit = 1m)", nullptr));
        x_axis->setText(QCoreApplication::translate("Sensor", "Latitude", nullptr));
        y_axis->setText(QCoreApplication::translate("Sensor", "Longitude", nullptr));
        prev->setText(QCoreApplication::translate("Sensor", "Prev", nullptr));
        resetBtn2->setText(QCoreApplication::translate("Sensor", "Reset Plot", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Sensor: public Ui_Sensor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENSOR_H
