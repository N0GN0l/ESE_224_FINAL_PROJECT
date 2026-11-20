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
    if (findQuiet(u->getID()) != nullptr) {
        std::cerr << "Cannot add delivery units with duplicate IDs" << std::endl;
        delete u;
        return false;
    }

    UnitNode* temp = new UnitNode(u, nullptr);

    if (head == nullptr || u->getID() < head->unit->getID()) {
        temp->next = head;          // new head (covers empty list too)
        head = temp;
    } else {
        UnitNode* prev = head;
        while (prev->next != nullptr && prev->next->unit->getID() < u->getID())
            prev = prev->next;
        temp->next = prev->next;
        prev->next = temp;
    }

    index.insert(u);
    count++;
    return true;
}

bool Fleet::removeUnit(int id)
{
    UnitNode* prev = nullptr;
    UnitNode* curr = head;
    while (curr != nullptr && curr->unit->getID() != id) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == nullptr) {
        std::cerr << "Could not find a delivery unit with the given id" << std::endl;
        return false;
    }

    if (prev == nullptr) head = curr->next;   // removing the head
    else prev->next = curr->next;

    index.remove(id);
    delete curr->unit;
    delete curr;
    count--;
    return true;
}

DeliveryUnit* Fleet::findQuiet(int id) const
{
    if (head == nullptr){
        return nullptr;
    }
    UnitNode* curr = head;
    while (curr->next != nullptr && curr->next->unit->getID() <= id){
        curr = curr->next;
    }
    if (curr->unit->getID() == id){
        return curr->unit;
    }
    return nullptr;
}

DeliveryUnit* Fleet::findByID(int id) const
{
    int comp = 0;
    if (head == nullptr){
        std::cerr << "ERROR: List is empty" << std::endl;
        return nullptr;
    }
    UnitNode* curr = head;
    while (curr->next != nullptr && curr->next->unit->getID() <= id){
        comp++;
        curr = curr->next;
    }
    if (curr->unit->getID() == id){
        comp++;
        std::cout << "Comparison count: " << comp << std::endl;
        return curr->unit;
    }
    comp++;   // the final check 
    std::cout << "Comparison count: " << comp << std::endl;
    std::cerr << "ERROR: ID not found" << std::endl;
    return nullptr;

    // TODO: one comparison per node examined; stop at the first larger ID; print the count
}

DeliveryUnit* Fleet::searchTree(int id) const
{
    int comp;
    DeliveryUnit* unit = index.search(id, comp);
    if (unit != nullptr) std::cout << "BST search: found ID" << id << " after " << comp << "comparisons." << std::endl;
    else std::cout << "BST search: ID" << id << " not found after " << comp << "comparisons." << std::endl;
    return unit;
}

int Fleet::getSize() const { 
    return count; 
}

void Fleet::displayAll() const {
    UnitNode* curr = head;
    while (curr != nullptr){
        curr->unit->display();
        std::cout << std::endl;
        curr = curr->next;
    }
}

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
