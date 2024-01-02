#include <math.h>  // sin(), cos(), atan2(), sqrt()

#include "RocketMath.h"
#include "map/Position.h"

//RocketMath::haversine2D(const Position& p1, const Position& p2) {
//    // Calculates the distance between two points along the surface of the Earth.
//    double a, c, d;
//    const double R = 6371000;  // Approximation of Earth's radius (in meters)
//    const double degToRad = M_PI / 180;

//    double phi_1 = p1.getLatitude() * degToRad;
//    double phi_2 = p2.getLatitude() * degToRad;

//    double deltaPhi = (p2.getLatitude() - p1.getLatitude()) * degToRad;
//    double deltaLambda = (p2.getLongitude() - p1.getLongitude()) * degToRad;

//    a = sin(deltaPhi/2)*sin(deltaPhi/2) + cos(phi_1)*cos(phi_2)*sin(deltaLambda/2)*sin(deltaLambda/2);
//    c = 2 * atan2(sqrt(a), sqrt(1-a));
//    d = R * c;

//    return d;
//};
