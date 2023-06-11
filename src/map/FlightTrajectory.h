#ifndef FLIGHT_TRAJECTORY_H
#define FLIGHT_TRAJECTORY_H

#include <vector>

#include "Position.h"

class FlightTrajectory {
public:
    FlightTrajectory();
    ~FlightTrajectory();
    std::vector<Position>& getRawFlightData();
    double calculateFlightDistance();
private:
    std::vector<Position> positions_;
};

#endif