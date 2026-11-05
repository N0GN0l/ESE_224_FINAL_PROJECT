// HeavyDrone.cpp
// ESE 224 Fall 2026 Final Project (Part II) starter code
// Team members: TODO

#include "HeavyDrone.h"
#include <iostream>
using namespace std;

HeavyDrone::HeavyDrone() : DeliveryUnit() {}

HeavyDrone::HeavyDrone(const string& n, int id, const string& m, double b, double p, int x, int y, const string& s)
    : DeliveryUnit()
{
    // TODO: set every member through its mutator (Section 3.3)
}

bool HeavyDrone::setModel(const string& m)
{
    // TODO: valid only when m is Hauler
    return false;
}

double HeavyDrone::batteryNeeded(int x, int y, double weight) const
{
    // TODO: distance x HEAVY_BATTERY_PER_UNIT x (1 + HEAVY_PAYLOAD_FACTOR x weight)
    return 0.0;
}

string HeavyDrone::type() const { return "Heavy"; }
