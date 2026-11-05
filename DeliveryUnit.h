// DeliveryUnit.h
// ESE 224 Fall 2026 Final Project (Part II) starter code
// Team members: TODO

#ifndef DELIVERYUNIT_H
#define DELIVERYUNIT_H

#include <string>
using namespace std;

// Constants (Part I constants plus the HeavyDrone ones)
const double BATTERY_PER_UNIT = 2.0;        // Drone: battery % per grid unit with no payload
const double PAYLOAD_FACTOR = 0.2;          // Drone: extra fraction per kg
const double HEAVY_BATTERY_PER_UNIT = 3.0;  // HeavyDrone: battery % per grid unit with no payload
const double HEAVY_PAYLOAD_FACTOR = 0.05;   // HeavyDrone: extra fraction per kg
const double SAFETY_RESERVE = 20.0;         // minimum battery % left after a delivery
const double LOW_BATTERY = 30.0;            // below this after a delivery -> CHARGING
const double MAX_PAYLOAD_LIMIT = 25.0;      // no unit can be rated above 25 kg

// Abstract base class for everything the fleet can dispatch
class DeliveryUnit
{
protected:
    string name;
    int ID;
    string model;
    double battery;
    double maxPayload;
    int position[2];
    string status;
    int deliveriesCompleted;

public:
    DeliveryUnit();
    virtual ~DeliveryUnit();

    // Accessors
    string getName() const;
    int getID() const;
    string getModel() const;
    double getBattery() const;
    double getMaxPayload() const;
    int getPosition(int index) const;
    string getStatus() const;
    int getDeliveriesCompleted() const;

    // Mutators (print an error, leave the member unchanged, return false if invalid)
    void setName(const string& n);
    bool setID(int id);
    virtual bool setModel(const string& m) = 0;   // each unit type accepts different models
    bool setBattery(double b);
    bool setMaxPayload(double p);
    bool setPosition(int index, int value);
    bool setStatus(const string& s);

    // Polymorphic behaviour
    virtual double batteryNeeded(int x, int y, double weight) const = 0;
    virtual string type() const = 0;              // "Drone" or "Heavy"

    // Shared behaviour (uses the virtual functions above)
    double distanceTo(int x, int y) const;
    bool canDeliver(int x, int y, double weight) const;
    void completeDelivery(int x, int y, double weight);
    void undoDelivery(double oldBattery, int oldX, int oldY, const string& oldStatus);
    void display() const;
};

#endif
