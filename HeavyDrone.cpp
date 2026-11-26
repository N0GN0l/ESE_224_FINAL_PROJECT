// HeavyDrone.cpp
// ESE 224 Fall 2026 Final Project (Part II) starter code
// Team members: Ella Chen, Daniel Zhou, Logan Jeong

#include "HeavyDrone.h"
#include <iostream>

HeavyDrone::HeavyDrone() : DeliveryUnit() 
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

HeavyDrone::HeavyDrone(const std::string& n, int id, const std::string& m, double b, double p, int x, int y, const std::string& s)
    : DeliveryUnit()
{
    // set every member through its mutator (Section 3.3)
    setName(n);
    setID(id);
    setModel(m);
    setBattery(b);
    setMaxPayload(p);
    setPosition(0, x);
    setPosition(1, y);
    setStatus(s);
}

bool HeavyDrone::setModel(const std::string& m)
{
    // valid only when m is Hauler
    if (m == "Hauler") 
    {
        model = m;
        return true;
    }
    std::cerr<<"Invalid model provided"<<std::endl;
    return false;
}

double HeavyDrone::batteryNeeded(int x, int y, double weight) const
{
    // distance x HEAVY_BATTERY_PER_UNIT x (1 + HEAVY_PAYLOAD_FACTOR x weight)
    double batteryNeeded = distanceTo(x, y) * HEAVY_BATTERY_PER_UNIT *(1 + HEAVY_PAYLOAD_FACTOR * weight);
    return batteryNeeded;
}

std::string HeavyDrone::type() const { return "Heavy"; }
