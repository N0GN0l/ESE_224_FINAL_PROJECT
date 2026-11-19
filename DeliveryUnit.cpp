// DeliveryUnit.cpp
// ESE 224 Fall 2026 Final Project (Part II) starter code
// Team members: Ella Chen, Daniel Zhou, Logan Jeong
//
// Much of this is your Part I Drone code, moved into the base class (Section 3.2).

#include "DeliveryUnit.h"
#include "myDouble.h"
#include <iostream>
#include <cmath>

DeliveryUnit::DeliveryUnit()
{
    // TODO: the Part I defaults
    name = " ";
    ID = -1;
    model = "";
    battery = 100.0;
    maxPayload = 0.0;
    position[0] = 0;
    position[1] = 0;
    status = "IDLE";
    deliveriesCompleted = 0;
}

DeliveryUnit::~DeliveryUnit() {}

// ---------- Accessors ----------
std::string DeliveryUnit::getName() const { return name; }
int DeliveryUnit::getID() const { return ID; }
std::string DeliveryUnit::getModel() const { return model; }
double DeliveryUnit::getBattery() const { return battery; }
double DeliveryUnit::getMaxPayload() const { return maxPayload; }
std::string DeliveryUnit::getStatus() const { return status; }
int DeliveryUnit::getDeliveriesCompleted() const { return deliveriesCompleted; }

int DeliveryUnit::getPosition(int index) const
{
    if(index == 0)
    {
        return position[0];
    }
    else if(index == 1)
    {
        return position[1];
    }
    return -1;
}

// ---------- Mutators (validate as in Part I; setMaxPayload: 0 < p <= MAX_PAYLOAD_LIMIT) ----------
void DeliveryUnit::setName(const std::string& n) { name = n; }

bool DeliveryUnit::setID(int id) 
{
    if(id > 0)
    {
        ID = id;
        return true;
    }
    std::cerr<<"You must provide a positive ID"<<std::endl;
    return false; 
}
bool DeliveryUnit::setBattery(double b) 
{
    if(b >= 0 && b <= 100)
    {
        battery = b;
        return true;
    } 
    std::cerr<<"Battery must be provided as a percentage between 0 and 100"<<std::endl;
    return false; 
}
bool DeliveryUnit::setMaxPayload(double p) 
{ 
    if(p > 0)
    {
        if(p <= MAX_PAYLOAD_LIMIT)
        {
            maxPayload = p;
            return true;
        }
        else {
            std::cerr<<"Max payload must be below the defined limit"<<std::endl;
        }
    }
    else {
        std::cerr<<"Max payload must be positive"<<std::endl;
    }
    return false;
}
bool DeliveryUnit::setPosition(int index, int value) 
{ 
    if(index == 0 || index == 1)
    {
        if(value >= 0)
        {
            position[index] = value;
            return true;
        }
        std::cerr<<"Value must be greater than or equal to 0"<<std::endl;
    }
    else {
        std::cerr<<"Index must be either 0 or 1"<<std::endl;
    }
    return false;
}
bool DeliveryUnit::setStatus(const std::string& s) 
{
    if(s == "IDLE" || s == "CHARGING" || s == "MAINTENANCE")
    {
        status = s;
        return true;
    }
    std::cerr<<"Status must be either 'IDLE', 'CHARGING', or 'MAINTENANCE' "<<std::endl;
    return false; 
}

// ---------- Shared behaviour ----------
double DeliveryUnit::distanceTo(int x, int y) const
{
    double distance = 0;
    //myDouble wraps the differences so ^2 means squaring
    myDouble deltaY(position[1] - y);
    myDouble deltaX(position[0] - x);
    distance = sqrt((deltaX^2) + (deltaY^2));
    return distance;
}

bool DeliveryUnit::canDeliver(int x, int y, double weight) const
{
    if((status == "IDLE") && (weight <= maxPayload) && (battery - batteryNeeded(x, y, weight) >= SAFETY_RESERVE))
    {
        return true;
    }
    return false;
}

void DeliveryUnit::completeDelivery(int x, int y, double weight)
{
    //double-check the delivery is still possible
    if(canDeliver(x, y, weight))
    {
        //use up battery, move to the destination, and count the delivery
        battery -= batteryNeeded(x, y, weight);
        position[0] = x;
        position[1] = y;
        deliveriesCompleted++;

        //send it to charge if the battery got too low
        if(battery < LOW_BATTERY)
        {
            setStatus("CHARGING");
        }
    }
    else
    {
        std::cerr<<"Drone cannot complete the delivery"<<std::endl;
    }
}

void DeliveryUnit::undoDelivery(double oldBattery, int oldX, int oldY, const std::string& oldStatus)
{
    if((deliveriesCompleted - 1) >= 0)
    {
        deliveriesCompleted--;
    }
    else {
        std::cout<<"No deliveries have been completed, cannot undo something that never happened"<<std::endl;
        return;
    }

    setBattery(oldBattery);
    setPosition(0, oldX);
    setPosition(1, oldY);
    setStatus(oldStatus);
}

void DeliveryUnit::display() const
{
    // TODO: print [type()] and every member with a label
    std::cout<<"[name]"<<getName() <<std::endl;
    std::cout<<"[ID]"<<getID() <<std::endl;
    std::cout<<"[model]"<<getModel() <<std::endl;
    std::cout<<"[battery]"<<getBattery() <<std::endl;
    std::cout<<"[max payload]"<<getMaxPayload() <<std::endl;
    std::cout<<"[X position]"<<getPosition(0) <<std::endl;
    std::cout<<"[Y position]"<<getPosition(1) <<std::endl;
    std::cout<<"[status]"<<getStatus() <<std::endl;
    std::cout<<"[deliveries completed]"<<getDeliveriesCompleted() <<std::endl;
}
