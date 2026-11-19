// Drone.h
// ESE 224 Fall 2026 Final Project (Part II) starter code
// Team members: Ella Chen, Daniel Zhou, Logan Jeong

#ifndef DRONE_H
#define DRONE_H

#include "DeliveryUnit.h"

// A standard drone: the Part I battery formula and models
class Drone : public DeliveryUnit
{
public:
    Drone();
    Drone(const std::string& n, int id, const std::string& m, double b, double p, int x, int y, const std::string& s);

    bool setModel(const std::string& m) override;                       // Kestrel, Falcon, or Condor
    double batteryNeeded(int x, int y, double weight) const override;
    std::string type() const override;                                 // "Drone"
};

#endif
