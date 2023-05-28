#ifndef ROCKET_MATH_H
#define ROCKET_MATH_H

#include "map/position.h"

namespace RocketMath {
    double haversine2D(const Position& p1, const Position& p2);
};

#endif