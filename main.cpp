// main.cpp
// ESE 224 Fall 2026 Final Project (Part II) starter code
// Team members: Ella Chen, Daniel Zhou, Logan Jeong
//
// This skeleton compiles and shows the menu. Fill in each TODO (Section 8).
// You can reuse your Part I login and input-checking code.

#include "DeliveryUnit.h"
#include "Drone.h"
#include "HeavyDrone.h"
#include "Fleet.h"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>

const std::string LOG_FILE = "delivery_log.txt";

// TODO: ask for a username and password until the pair is in users.txt; greet the user
bool login()
{
    return true;
}

// TODO: read every line of drones.txt until end of file. The first word is D (Drone) or H (HeavyDrone):
//       create the unit with new, add it to the fleet, and print how many were loaded.
void loadFleet(Fleet& fleet, const std::string& filename)
{
    char unit_type; // first word - classifying Drone or HeavyDrone
    std::string name;
    std::string model;
    int ID, x, y;
    double battery, maxPayload;
    std::string status;
    int count = 0;
    std::ifstream fin(filename);

    while (fin>>unit_type>>name>>ID>>model>>battery>>maxPayload>>x>>y>>status) // until eof
    {
        DeliveryUnit* temp = nullptr; // base-class ptr can point to objects of any DeliveryUnit derived class
        
        // runtime polymorphism - implementation to be executed determined during runtime
        if (unit_type == 'D')
        {
            temp = new Drone(name,ID,model,battery,maxPayload,x,y,status);
        } 
        else if (unit_type == 'H')
        {
            temp = new HeavyDrone(name,ID,model,battery,maxPayload,x,y,status);
        }
        
        if (temp != nullptr) // add unit if successfully created
        {
            if (fleet.addUnit(temp)) count++;
            else delete temp; // free if couldn't add
        }
    }

    std::cout<<count<<" drones loaded"<<std::endl; // print how many loaded
}

void showMenu()
{
    std::cout << std::endl
         << "===== SkyDrop Dispatch Center =====" << std::endl
         << " 1. Display fleet (ID order)" << std::endl
         << " 2. Display ID tree (traversals and height)" << std::endl
         << " 3. Search by ID (linked list and tree)" << std::endl
         << " 4. Add a unit" << std::endl
         << " 5. Remove a unit" << std::endl
         << " 6. Find nearest available unit" << std::endl
         << " 7. Load orders into the pending queue" << std::endl
         << " 8. Process pending orders" << std::endl
         << " 9. Undo last dispatch" << std::endl
         << "10. Recharge all charging units" << std::endl
         << "11. Retry failed orders" << std::endl
         << "12. Fleet status summary" << std::endl
         << "13. Write fleet to file" << std::endl
         << " 0. Quit" << std::endl;
}

int main()
{
    if (!login())
        return 0;

    Fleet fleet;
    loadFleet(fleet, "drones.txt");

    int choice = -1;
    while (choice != 0)
    {
        showMenu();
        std::cout << "Choose an option: ";
        std::cin >> choice;
        // TODO: recover from a letter (cin.clear and cin.ignore) instead of crashing or looping forever

        switch (choice)
        {
        case 1:
            fleet.displayAll();
            break;
        // TODO: cases 2 to 13 (table in Section 8)
        case 0:
            std::cout << "Goodbye!" << std::endl;
            break;
        default:
            std::cout << "Invalid option." << std::endl;
        }
    }
    return 0;   // the Fleet destructor frees everything here
}
