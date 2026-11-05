// Drone.h
// ESE 224 Fall 2026 Final Project (Part II) starter code
// Team members: TODO

#ifndef DRONE_H
#define DRONE_H

#include "DeliveryUnit.h"

// A standard drone: the Part I battery formula and models
class Drone : public DeliveryUnit
{
public:
    Drone();
    Drone(const string& n, int id, const string& m, double b, double p, int x, int y, const string& s);

    bool setModel(const string& m) override;                       // Kestrel, Falcon, or Condor
    double batteryNeeded(int x, int y, double weight) const override;
    string type() const override;                                 // "Drone"
};

#endif
