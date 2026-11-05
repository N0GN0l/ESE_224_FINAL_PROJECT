// Order.h
// ESE 224 Fall 2026 Final Project (Part II) starter code
// Team members: TODO

#ifndef ORDER_H
#define ORDER_H

#include <string>
using namespace std;

// One delivery order from orders.txt
struct Order
{
    int orderID;
    int x;
    int y;
    double weight;
};

// Everything needed to undo one dispatch
struct DispatchRecord
{
    Order order;          // the order that was delivered
    int unitID;           // who delivered it
    double oldBattery;    // the unit's state just before the delivery
    int oldX;
    int oldY;
    string oldStatus;
};

#endif
