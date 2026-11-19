// Drone.cpp
// ESE 224 Fall 2026 Final Project (Part II) starter code
// Team members: Ella Chen, Daniel Zhou, Logan Jeong

#include "Drone.h"
#include <iostream>

Drone::Drone() : DeliveryUnit() {}

Drone::Drone(const std::string& n, int id, const std::string& m, double b, double p, int x, int y, const std::string& s)
    : DeliveryUnit()
{
    // TODO: set every member through its mutator (Section 3.3)
}

bool Drone::setModel(const std::string& m)
{
    // TODO: valid when m is Kestrel, Falcon, or Condor
    return false;
}

double Drone::batteryNeeded(int x, int y, double weight) const
{
    // TODO: distance x BATTERY_PER_UNIT x (1 + PAYLOAD_FACTOR x weight)
    return 0.0;
}

std::string Drone::type() const { return "Drone"; }
