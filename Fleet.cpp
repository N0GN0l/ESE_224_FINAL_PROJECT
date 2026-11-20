// Fleet.cpp
// ESE 224 Fall 2026 Final Project (Part II) starter code
// Team members: Ella Chen, Daniel Zhou, Logan Jeong
//
// The fleet is a singly linked list kept in ascending ID order (Section 5) plus the dispatch center (Section 7).
// No vector or other STL containers: use your own list, Queue, Stack, and DroneTree.

#include "Fleet.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

Fleet::Fleet() : head(nullptr), count(0) {}

Fleet::~Fleet()
{
    // TODO: delete every node AND every unit (the Fleet owns the units)
}

// ---------- Linked list ----------
bool Fleet::addUnit(DeliveryUnit* u)
{
    UnitNode* temp = new UnitNode(u,nullptr);
    if(head == nullptr)
    {
        head = temp;
        return true;
    }

    UnitNode* curr = head;
    UnitNode* prev = curr;
    while(temp->unit->getID() > curr->unit->getID())
    {
        if(temp->unit->getID() == curr->unit->getID())
        {
            std::cerr<<"Cannot add delivery units with duplicate IDs"<<std::endl;
            delete temp;
            delete u;
            return false;
        }
        prev = curr;
        curr = curr->next;
    }

    prev->next = temp;
    temp->next = curr;
    return true;
    //Make this work with the binary tree!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1

    // TODO: sorted insert by ID and insert into 'index'; on a duplicate ID print a message, delete u, return false
}

bool Fleet::removeUnit(int id)
{
    UnitNode* curr = head;
    UnitNode* prev;
    while(curr->unit->getID() != id)
    {
        prev = curr;
        if(curr->next == nullptr)
        {
            std::cerr<<"Could not find a delivery unit with the given ID"<<std::endl;
            return false;
        }
        curr = curr->next;
        
    }

    delete curr->unit;

    prev->next = curr->next;
    delete curr;
    //make this work with the binary tree!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // TODO: unlink, remove from 'index', delete the unit and the node
}

DeliveryUnit* Fleet::findQuiet(int id) const
{
    // TODO: list lookup without printing (used by addUnit and undo)
    return nullptr;
}

DeliveryUnit* Fleet::findByID(int id) const
{
    // TODO: one comparison per node examined; stop at the first larger ID; print the count
    return nullptr;
}

DeliveryUnit* Fleet::searchTree(int id) const
{
    // TODO: index.search(...) and print the count
    return nullptr;
}

int Fleet::getSize() const { return count; }

void Fleet::displayAll() const { /* TODO */ }

void Fleet::displayTree() const
{
    // TODO: in-order, pre-order, post-order, and height
}

void Fleet::countByStatus() const { /* TODO */ }

void Fleet::writeFleetToFile(const std::string& filename) const { /* TODO */ }

// ---------- Dispatch center ----------
DeliveryUnit* Fleet::findNearestAvailable(int x, int y, double weight) const
{
    // TODO: closest unit that canDeliver; a tie goes to the smaller ID
    return nullptr;
}

void Fleet::appendLog(const std::string& logFile, const std::string& line) const
{
    // Prints a line and appends it to the log file
    std::cout << line << std::endl;
    std::ofstream out(logFile, std::ios::app);
    out << line << std::endl;
}

int Fleet::loadOrders(const std::string& orderFile, const std::string& logFile)
{
    // TODO: enqueue every order into 'pending' in file order; start a new, empty log file
    return 0;
}

void Fleet::processPending(const std::string& logFile)
{
    // TODO: dequeue until empty; dispatch (push a DispatchRecord first) or move to 'retry'; log each line and a summary
}

bool Fleet::undoLastDispatch(const std::string& logFile)
{
    // TODO: pop the last record, undoDelivery on that unit, move the order to 'retry'
    return false;
}

int Fleet::rechargeAll(const std::string& logFile)
{
    // TODO: every CHARGING unit -> battery 100, IDLE
    return 0;
}

void Fleet::retryFailed(const std::string& logFile)
{
    // TODO: move every order from 'retry' to 'pending' (keep the order), then processPending
}

int Fleet::pendingCount() const { return pending.size(); }
int Fleet::retryCount() const { return retry.size(); }
int Fleet::historyCount() const { return history.size(); }
