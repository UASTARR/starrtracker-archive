#include "gpsparser.h"
#include <iostream>
#include <QDebug>

GPSParser::GPSParser(QObject *parent) : QObject(parent)
{

}

GPSParser::~GPSParser()
{

}

void GPSParser::parse(QByteArray &data)
{
    qInfo(data.constData());
}
