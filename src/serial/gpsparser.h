#ifndef GPSPARSER_H
#define GPSPARSER_H


class GPSParser
{
public:
    GPSParser();
    ~GPSParser();
    void parse(QByteArray& data);
    double getLongitude();
    double getLatitude();
private:
    double longitude_;
    double latitude_;

};

#endif // GPSPARSER_H
