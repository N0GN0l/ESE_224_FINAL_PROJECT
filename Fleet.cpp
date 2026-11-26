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
#include <cmath>

static std::string oneDecimal(double value)
{
    std::string s = std::to_string(std::round(value * 10.0) / 10.0); 
    return s.substr(0, s.find('.') + 2);                              
}

Fleet::Fleet() : head(nullptr), count(0) {}

Fleet::~Fleet()
{
    UnitNode* curr = head;
    while (curr != nullptr)
    {
        UnitNode* next = curr->next;
        delete curr->unit;
        delete curr;
        curr = next;
    }
    head = nullptr;
    count = 0;
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
    for (UnitNode* curr = head; curr != nullptr; curr = curr->next)
    {
        comp++;
        int currID = curr->unit->getID();
        if (currID == id)
        {
            std::cout << "Linked list search: found ID " << id << " after " << comp << " comparisons." << std::endl;
            return curr->unit;
        }
        if (currID > id)
        {
            break;
        }
    }
    std::cout << "Linked list search: ID " << id << " not found after " << comp << " comparisons." << std::endl;
    return nullptr;
}

DeliveryUnit* Fleet::searchTree(int id) const
{
    int comp;
    DeliveryUnit* unit = index.search(id, comp);
    if (unit != nullptr){    
        std::cout << "BST search: found ID " << id << " after " << comp << " comparisons." << std::endl;
    }
    else{
         std::cout << "BST search: ID " << id << " not found after " << comp << " comparisons." << std::endl;
    }
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
    std::cout << "In-order:   ";
    index.inOrder();
    std::cout << "Pre-order:  ";
    index.preOrder();
    std::cout << "Post-order: ";
    index.postOrder();
    std::cout << "Height: " << index.height() << " (" << index.size() << " units)" << std::endl;
}

void Fleet::countByStatus() const
{
    int drones = 0, heavies = 0;
    int idle = 0, charging = 0, maintenance = 0;
    double batteryTotal = 0.0;

    for (UnitNode* curr = head; curr != nullptr; curr = curr->next)
    {
        DeliveryUnit* u = curr->unit;

        if (u->type() == "Drone") drones++;
        else if (u->type() == "Heavy") heavies++;

        std::string s = u->getStatus();
        if (s == "IDLE") idle++;
        else if (s == "CHARGING") charging++;
        else if (s == "MAINTENANCE") maintenance++;

        batteryTotal += u->getBattery();
    }

    std::cout << "Units by type:   Drone " << drones << ", Heavy " << heavies << std::endl;
    std::cout << "Units by status: IDLE " << idle << ", CHARGING " << charging
              << ", MAINTENANCE " << maintenance << std::endl;

    std::cout << "Average battery: ";
    if (count > 0)
        std::cout << oneDecimal(batteryTotal / count) << "%" << std::endl;
    else
        std::cout << "N/A (no units)" << std::endl;

    std::cout << "Pending orders:  " << pending.size() << std::endl;
    std::cout << "Retry orders:    " << retry.size() << std::endl;
    std::cout << "History records: " << history.size() << std::endl;
}

void Fleet::writeFleetToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile){
        std::cerr << "ERROR: Could not open file" << std::endl;
        return; 
    }
    UnitNode* curr = head;
    outFile << std::fixed << std::setprecision(1);
    while (curr != nullptr){
        char type = (curr->unit->type() == "Heavy") ? 'H' : 'D';
        outFile << type << " " <<  curr->unit->getName() << " " << curr->unit->getID() <<
                " " << curr->unit->getModel() << " " << curr->unit->getBattery() << " " <<
                curr->unit->getMaxPayload() << " " << curr->unit->getPosition(0) << " " <<
                curr->unit->getPosition(1) << " " << curr->unit->getStatus() << " " << 
                curr->unit->getDeliveriesCompleted() << std::endl;
        curr = curr->next;
    }
}

// ---------- Dispatch center ----------
DeliveryUnit* Fleet::findNearestAvailable(int x, int y, double weight) const
{
    UnitNode* curr = head;
    DeliveryUnit* curr_shortest = nullptr;
    while(curr != nullptr){
        if (curr->unit->canDeliver(x, y, weight)){
            if (curr_shortest == nullptr) curr_shortest = curr->unit;
            if (curr->unit->distanceTo(x,y) < curr_shortest->distanceTo(x,y)) curr_shortest = curr->unit;
        }
        curr = curr->next;
    }
    return curr_shortest;
}

void Fleet::appendLog(const std::string& logFile, const std::string& line) const
{
    std::cout << line << std::endl;
    std::ofstream out(logFile, std::ios::app);
    out << line << std::endl;
}

int Fleet::loadOrders(const std::string& orderFile, const std::string& logFile)
{
    std::ifstream fin(orderFile);

    if (!fin){
        std::cerr << "ERROR: Could not open file" << std::endl;
        return 0;
    }

    int id, x, y;
    double weight;
    int loaded = 0;
    while (fin >> id >> x >> y >> weight) {
        pending.enqueue(Order{id, x, y, weight});
        loaded++;
    }
    std::ofstream log(logFile);  

    return loaded;
}

void Fleet::processPending(const std::string& logFile)
{
    int processed = 0, assigned = 0, failed = 0;
    double totalDistance = 0.0;     // sum of exact distances; rounded only when printed

    while (!pending.isEmpty()){
        Order temp;
        pending.dequeue(temp);
        processed++;

        DeliveryUnit* delTemp = findNearestAvailable(temp.x, temp.y, temp.weight);
        std::string line;

        if (delTemp != nullptr){
            double oldBattery = delTemp->getBattery();
            double dist = delTemp->distanceTo(temp.x, temp.y);

            history.push(DispatchRecord{temp, delTemp->getID(), oldBattery, delTemp->getPosition(0), delTemp->getPosition(1), delTemp->getStatus()});
            delTemp->completeDelivery(temp.x, temp.y, temp.weight);

            totalDistance += dist;
            assigned++;

            line = "Order " + std::to_string(temp.orderID) + ": " + delTemp->type() + " "
                 + std::to_string(delTemp->getID()) + " (" + delTemp->getName() + ") distance "
                 + oneDecimal(dist) + " battery " + oneDecimal(oldBattery) + " -> "
                 + oneDecimal(delTemp->getBattery());
        }
        else{
            retry.enqueue(temp);
            failed++;

            line = "Order " + std::to_string(temp.orderID) + ": no unit available, moved to retry queue";
        }
        appendLog(logFile, line);
    }

    appendLog(logFile, "Processed " + std::to_string(processed) + " orders: "
                       + std::to_string(assigned) + " assigned, " + std::to_string(failed)
                       + " moved to retry queue. Distance flown: " + oneDecimal(totalDistance));
}

bool Fleet::undoLastDispatch(const std::string& logFile)
{
    if (history.isEmpty()){
        std::cout << "Nothing to undo." << std::endl;
        return false;
    }

    DispatchRecord temp;
    history.pop(temp);
    retry.enqueue(temp.order);

    DeliveryUnit* unit = findQuiet(temp.unitID);
    if (unit == nullptr){
        appendLog(logFile, "Undo order " + std::to_string(temp.order.orderID) + ": unit "
                  + std::to_string(temp.unitID) + " was removed, order moved to retry queue");
        return true;
    }

    unit->undoDelivery(temp.oldBattery, temp.oldX, temp.oldY, temp.oldStatus);

    // Undo order 5020: Drone 342 (Meteor) restored to battery 82.6 at (26, 6) IDLE, order moved to retry queue
    appendLog(logFile, "Undo order " + std::to_string(temp.order.orderID) + ": " + unit->type() + " "
              + std::to_string(unit->getID()) + " (" + unit->getName() + ") restored to battery "
              + oneDecimal(unit->getBattery()) + " at (" + std::to_string(unit->getPosition(0)) + ", "
              + std::to_string(unit->getPosition(1)) + ") " + unit->getStatus()
              + ", order moved to retry queue");
    return true;
}


int Fleet::rechargeAll(const std::string& logFile)
{
    int recharged = 0;
    for (UnitNode* curr = head; curr != nullptr; curr = curr->next){
        if (curr->unit->getStatus() == "CHARGING"){     // MAINTENANCE units are left alone
            curr->unit->setBattery(100.0);
            curr->unit->setStatus("IDLE");
            recharged++;
        }
    }

    appendLog(logFile, "Recharged " + std::to_string(recharged) + " units to 100%.");
    return recharged;
}

void Fleet::retryFailed(const std::string& logFile)
{
    appendLog(logFile, "Retrying " + std::to_string(retry.size()) + " orders.");

    Order temp;
    while (!retry.isEmpty()){
        retry.dequeue(temp);
        pending.enqueue(temp);
    }

    processPending(logFile);
}

int Fleet::pendingCount() const { return pending.size(); }
int Fleet::retryCount() const { return retry.size(); }
int Fleet::historyCount() const { return history.size(); }
