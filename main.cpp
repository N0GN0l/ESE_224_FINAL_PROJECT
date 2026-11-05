// main.cpp
// ESE 224 Fall 2026 Final Project (Part II) starter code
// Team members: TODO
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
using namespace std;

const string LOG_FILE = "delivery_log.txt";

// TODO: ask for a username and password until the pair is in users.txt; greet the user
bool login()
{
    return true;
}

// TODO: read every line of drones.txt until end of file. The first word is D (Drone) or H (HeavyDrone):
//       create the unit with new, add it to the fleet, and print how many were loaded.
void loadFleet(Fleet& fleet, const string& filename)
{
}

void showMenu()
{
    cout << endl
         << "===== SkyDrop Dispatch Center =====" << endl
         << " 1. Display fleet (ID order)" << endl
         << " 2. Display ID tree (traversals and height)" << endl
         << " 3. Search by ID (linked list and tree)" << endl
         << " 4. Add a unit" << endl
         << " 5. Remove a unit" << endl
         << " 6. Find nearest available unit" << endl
         << " 7. Load orders into the pending queue" << endl
         << " 8. Process pending orders" << endl
         << " 9. Undo last dispatch" << endl
         << "10. Recharge all charging units" << endl
         << "11. Retry failed orders" << endl
         << "12. Fleet status summary" << endl
         << "13. Write fleet to file" << endl
         << " 0. Quit" << endl;
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
        cout << "Choose an option: ";
        cin >> choice;
        // TODO: recover from a letter (cin.clear and cin.ignore) instead of crashing or looping forever

        switch (choice)
        {
        case 1:
            fleet.displayAll();
            break;
        // TODO: cases 2 to 13 (table in Section 8)
        case 0:
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << "Invalid option." << endl;
        }
    }
    return 0;   // the Fleet destructor frees everything here
}
