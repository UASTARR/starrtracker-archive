#include "FlightTrajectory.h"
#include "../RocketMath.h"

FlightTrajectory::FlightTrajectory() {

};

FlightTrajectory::~FlightTrajectory() {

};

std::vector<Position>& getRawFlightData() {
    return positions_;
};

double calculateFlightDistance() {
    // Calculates the distances between all adjacent positions and sums up.
    int position_count = positions_.size();
    double total_distance = 0.0;
    // Loop over every pair of adjacent positions, compute distance, add it up.
    for (int i = 0; i < position_count-1; i++) {
        Position& p1 = positions_[i];
        Position& p2 = positions_[i+1];
        total_distance += RocketMath::haversine2D(p1, p2);
    }
};