// Fleet.h
// ESE 224 Fall 2026 Final Project (Part II) starter code
// Team members: TODO

#ifndef FLEET_H
#define FLEET_H

#include "DeliveryUnit.h"
#include "DroneTree.h"
#include "Order.h"
#include "Queue.h"
#include "Stack.h"
#include <string>
using namespace std;

class Fleet
{
private:
    // Singly linked list of units, always kept in ascending ID order. The Fleet owns the units.
    struct UnitNode
    {
        DeliveryUnit* unit;
        UnitNode* next;
    };
    UnitNode* head;
    int count;

    DroneTree index;                    // BST index by ID (does not own the units)
    Queue<Order> pending;               // orders waiting to be processed
    Queue<Order> retry;                 // orders that could not be assigned
    Stack<DispatchRecord> history;      // completed dispatches, most recent on top

    DeliveryUnit* findQuiet(int id) const;               // list lookup without printing
    void appendLog(const string& logFile, const string& line) const;

public:
    Fleet();
    ~Fleet();
    Fleet(const Fleet&) = delete;
    Fleet& operator=(const Fleet&) = delete;

    // Linked list
    bool addUnit(DeliveryUnit* u);                       // sorted insert; on a duplicate ID deletes u, returns false
    bool removeUnit(int id);                             // unlinks, removes from the tree, deletes the unit
    DeliveryUnit* findByID(int id) const;                // linear search, prints its comparison count
    DeliveryUnit* searchTree(int id) const;              // BST search, prints its comparison count
    int getSize() const;
    void displayAll() const;
    void displayTree() const;                            // three traversals and the height
    void countByStatus() const;
    void writeFleetToFile(const string& filename) const;

    // Dispatch center
    DeliveryUnit* findNearestAvailable(int x, int y, double weight) const;
    int loadOrders(const string& orderFile, const string& logFile);   // fills 'pending', starts a new log
    void processPending(const string& logFile);
    bool undoLastDispatch(const string& logFile);
    int rechargeAll(const string& logFile);
    void retryFailed(const string& logFile);
    int pendingCount() const;
    int retryCount() const;
    int historyCount() const;
};

#endif
