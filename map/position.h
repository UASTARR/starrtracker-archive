#ifndef POSITION_H
#define POSITION_H

class Position {
public:
    Position(double lat, double longi);
    ~Position();
    double getLatitude();
    void setLatitude(double lat);
    double getLongitude();
    void setLongitude(double longi);
private:
    double latitude_;
    double longitude_;
};

#endif