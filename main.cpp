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
    std::string name, pass;
    std::string validName, validPass;

    while (true) // indefinite until valid pair entered (break) or file cannot be opened (false)
    {
        std::cout << "input username: ";
        std::cin >> name;
        std::cout << "input password: ";
        std::cin >> pass;

        std::ifstream fin("users.txt");
        if (!fin)
        {
            std::cout << "unable to open users.txt" << std::endl;
            return false;
        }

        bool logged = false;
        while (fin >> validName >> validPass)
        {
            if (name == validName && pass == validPass)
            {
                logged = true;
                break;
            }
        }

        fin.close();

        if (logged)
        {
            std::cout << "Hello " << name << ", welcome to SkyDrop!" << std::endl;
            return true;
        }

        std::cout << "please enter a valid username & password pair" << std::endl;
    }
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
    if (!login()) // if login fails terminate program
        return 0;

    Fleet fleet; // create fleet object
    loadFleet(fleet, "drones.txt"); // load fleet with input file

    int choice = -1;
    while (choice != 0)
    {
        showMenu();
        std::cout << "Choose an option: ";
        std::cin >> choice;
        // TODO: recover from a letter (cin.clear and cin.ignore) instead of crashing or looping forever
        if (std::cin.fail()) // isn't int (ie, is letter)
        {
            std::cin.clear(); // reset error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // extract & discard bad input (more than just one)
            std::cout << "input failed, try again\n";
            continue; // jump back to beginning of loop
        }
 
        char unit_type;
        std::string name;
        std::string model;
        int ID, x, y;
        double battery, maxPayload, weight;
        std::string status;

        switch (choice)
        {
            case 1:
                fleet.displayAll();
                break;
            case 2:
                fleet.displayTree();
                break;
            case 3:
            { // brackets for local var declared inside case
                std::cout << "input ID to search: ";
                std::cin >> ID;

                DeliveryUnit* temp = fleet.findByID(ID);
                fleet.searchTree(ID);

                if (temp != nullptr) { // use findByID to determine whether id was foudn
                    temp->display(); // display unit info
                } else {
                    std::cout << "unit not found" << std::endl;
                }
                break;
            }
            case 4: // add only if every validating mutator accepts & ID is not duplicate
            {
                DeliveryUnit* temp = nullptr; // point to either derived class
                
                std::cout << "input new unit's type (D or H): ";
                std::cin >> unit_type;
                std::cout << "input unit's name: ";
                std::cin >> name;

                if (unit_type == 'D')
                {
                    temp = new Drone();
                }
                else if (unit_type == 'H')
                {
                    temp = new HeavyDrone();
                }

                std::cout << "input with no commas - ID, model, battery, maxPayload, x, y, status: ";
                std::cin >> ID >> model >> battery >> maxPayload >> x >> y >> status;
                
                // temp-> = (*temp).
                if (temp->setID(ID) && temp->setModel(model) && temp->setBattery(battery) && temp->setMaxPayload(maxPayload) &&temp->setPosition(0, x) && temp->setPosition(1, y) && temp->setStatus(status)) { // validate
                    fleet.addUnit(temp);
                } else {
                    std::cout << "invalid specs - could not add unit" << std::endl;
                    delete temp;
                }
                break;
            }
            case 5:
                std::cout << "input ID to remove: ";
                std::cin >> ID;
                fleet.removeUnit(ID);
                break;
            case 6:
            {
                std::cout << "input x, y, weight to find nearest available unit: ";
                std::cin >> x >> y >> weight;
                DeliveryUnit* temp = fleet.findNearestAvailable(x, y, weight);
                if (temp != nullptr) {
                    temp->display();
                } else {
                    std::cout << "no unit found to complete this delivery :(" << std::endl;
                }
                break;
            }
            case 7:
                fleet.loadOrders("orders.txt", "delivery_log.txt");
                break;
            case 8:
                fleet.processPending("delivery_log.txt");
                break;
            case 9:
                fleet.undoLastDispatch("delivery_log.txt");
                break;
            case 10:
                fleet.rechargeAll("delivery_log.txt");
                break;
            case 11:
                fleet.retryFailed("delivery_log.txt");
                break;
            case 12:
                fleet.countByStatus();
                break;
            case 13:
                fleet.writeFleetToFile("fleet_output.txt");
                break;
            case 0:
                std::cout << "Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid option." << std::endl;
        }
    }

    return 0;   // the Fleet destructor frees everything here
}
