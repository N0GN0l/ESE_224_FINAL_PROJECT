// HeavyDrone.h
// ESE 224 Fall 2026 Final Project (Part II) starter code
// Team members: TODO

#ifndef HEAVYDRONE_H
#define HEAVYDRONE_H

#include "DeliveryUnit.h"

// A heavy-lift drone: costs more per grid unit, but weight matters much less
class HeavyDrone : public DeliveryUnit
{
public:
    HeavyDrone();
    HeavyDrone(const string& n, int id, const string& m, double b, double p, int x, int y, const string& s);

    bool setModel(const string& m) override;                       // only "Hauler"
    double batteryNeeded(int x, int y, double weight) const override;
    string type() const override;                                 // "Heavy"
};

#endif
