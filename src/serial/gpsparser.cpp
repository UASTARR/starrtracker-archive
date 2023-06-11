#include "gpsparser.h"
#include <iostream>

GPSParser::GPSParser(QObject *parent) : QObject(parent)
{

}

GPSParser::~GPSParser()
{

}

void GPSParser::parse(QByteArray &data)
{
    std::cout << data.constData();
}
