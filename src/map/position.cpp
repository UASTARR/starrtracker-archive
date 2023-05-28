#include "position.h"

Position::Position(double lat, double longi) {
    latitude_ = lat;
    longitude_ = longi;
};

Position::~Position() {

};

double Position::getLatitude() {
    return latitude_;
};

void Position::setLatitude(double lat) {
    latitude_ = lat;
};

double Position::getLongitude() {
    return longitude_;
};

void Position::setLongitude(double longi) {
    longitude_ = longi;
};