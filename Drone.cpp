// Drone.cpp
// ESE 224 Fall 2026 Final Project (Part II) starter code
// Team members: Ella Chen, Daniel Zhou, Logan Jeong

#include "Drone.h"
#include <iostream>

Drone::Drone() : DeliveryUnit() 
{
    name = "";
    ID = -1;
    model = "";
    battery = 100.0;
    maxPayload = 0.0;
    position[0] = 0;
    position[1] = 0;
    status = "IDLE";
    deliveriesCompleted = 0;
}

Drone::Drone(const std::string& n, int id, const std::string& m, double b, double p, int x, int y, const std::string& s)
    : DeliveryUnit()
{
    setName(n);
    setID(id);
    setModel(m);
    setBattery(b);
    setMaxPayload(p);
    setPosition(0, x);
    setPosition(1, y);
    setStatus(s);
}

bool Drone::setModel(const std::string& m)
{
    // TODO: valid when m is Kestrel, Falcon, or Condor
    if (m == "Kestrel" || m == "Falcon" || m == "Condor") 
    {
        model = m;
        return true;
    }
    return false;
}

double Drone::batteryNeeded(int x, int y, double weight) const
{
    // TODO: distance x BATTERY_PER_UNIT x (1 + PAYLOAD_FACTOR x weight)
    double batteryNeeded = distanceTo(x, y) * BATTERY_PER_UNIT *(1 + PAYLOAD_FACTOR * weight);
    return batteryNeeded;
}

std::string Drone::type() const { return "Drone"; }
