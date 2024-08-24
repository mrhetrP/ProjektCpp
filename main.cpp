#include <ncurses.h>
#include "flatsManager.hpp"
/*
int main (void) {
    //Date day(2022, 7, 28);
    
    FlatsManager x;
    
    Address addr1("Blanicka", 1256, "123A", "Prag", 12345);
    Flat flat1(addr1, 1);
    x.addFlat(flat1);

    Address addr2("Blanicka", 1256, "123B", "Prag", 12346);
    Flat flat2(addr2, 2);
    x.addFlat(flat2);
    x.printAllSimple();
    Item item("xy", 15);
    x.flats.back().addItem(x, item);
    x.flats.back().addItem(x, Item("yz", 12));
    Date date(2015, 5, 12);
    x.flats.back().addContract(Contract(date, date, Tenant("Antonín Novák", date, addr1)));
    x.flats.back().addContract(Contract(Date(2016, 3, 12), Date(2016, 5, 12), Tenant("Dobromila Wagenknechtová", date, addr1)));
    //x.printAllSimple();
    
    //x.flats.back().removeItem(12);
    //x.flats.back().removeContract(Contract(Date(2016, 3, 12), Date(2016, 5, 12), Tenant("name1", date, addr1)));
    //x.removeFlat(flat2);
    //auto flatsOnMainStreet = x.findFlats("Blanická");

    x.saveToCSV("flats.csv");
    
    x.loadFromCSV("flats.csv");
    x.printAllFull();
    return EXIT_SUCCESS;
}
*/
void addFlat(FlatsManager & manager) {
    char street[50], city[50], streetNumber[10];
    int conscriptionNumber, postCode, flatNumber;
    bool success = false;

    while (!success) {
        echo();
        mvprintw(0, 0, "Enter Street Name: ");
        getstr(street);
        mvprintw(1, 0, "Enter Conscription Number: ");
        scanw("%d", &conscriptionNumber);
        mvprintw(2, 0, "Enter Street Number: ");
        getstr(streetNumber);
        mvprintw(3, 0, "Enter City: ");
        getstr(city);
        mvprintw(4, 0, "Enter Postcode: ");
        scanw("%d", &postCode);
        mvprintw(5, 0, "Enter Flat Number: ");
        scanw("%d", &flatNumber);

        
        try {
            Address addr(street, conscriptionNumber, streetNumber, city, postCode);
            Flat flat(addr, flatNumber);
            manager.addFlat(flat);
            clear();
            mvprintw(0, 0, "Flat added successfully. Press any key to return to the main menu.");
            success = true; // Break the loop on success
            getch();
            clear();
            refresh();
        } catch (const std::invalid_argument& e) {
            clear();
            mvprintw(0, 0, "Error: %s", e.what());
            mvprintw(1, 0, "Do you want to try again? (y/n): ");
            char response = getch();
            if (response != 'y' && response != 'Y') {
                mvprintw(3, 0, "Operation cancelled. Press any key to return to the main menu.");
                getch();
                success = true; // Break the loop to exit
            }
            clear();
            refresh();
        }
    }
}

void listFlatsSimple(std::vector<Flat> flats) {
    clear();
    std::cout << std::left << std::setw(40) << "Address:";
    std::cout << std::left << std::setw(20) << "| Flat number:";
    std::cout << std::left << std::setw(20) << "| Number of items:";
    std::cout << std::left << std::setw(20) << "| Latest tenant:";
    std::cout << std::endl;
    std::cout << std::string(40, '-') + "+" + std::string(19, '-') + "+" + std::string(19, '-') + "+" + std::string(19, '-') << std::endl;
    for (const auto & flat : flats) {
        flat.simpleDescription();
    }
}

void loadFromCSV(FlatsManager &manager) {
    char file[100];
    echo(); // Enable echoing of user input
    curs_set(1); // Show cursor to indicate input is expected

    // Ask for the file name
    mvprintw(0, 0, "Enter File Name: ");
    getstr(file); // Get the file name from the user

    // Check if the file exists
    std::ifstream infile(file);
    if (!infile) {
        mvprintw(2, 0, "Error: File does not exist. Press any key to return to the menu.");
        getch(); // Wait for the user to press a key
        clear(); // Clear the screen
        noecho(); // Disable echoing
        curs_set(0); // Hide cursor
        return; // Exit the function, returning to the menu
    }

    // File exists, proceed with loading
    manager.loadFromCSV(file);
    mvprintw(2, 0, "Flats loaded successfully! Press any key to return to the menu.");
    getch(); // Wait for the user to press a key
    clear(); // Clear the screen

    noecho(); // Disable echoing of user input
    curs_set(0); // Hide cursor
    clear();
    refresh();
}

void displayMenu(WINDOW* menu_win, int highlight) {
    std::string choices[] = {
        "Add Flat",
        "Remove Flat",
        "Find Flat",
        "List All Flats (short form)",
        "List All Flats (full form)",
        "Load From CSV",
        "Save To CSV",
        "Exit"
    };
    int n_choices = sizeof(choices) / sizeof(choices[0]);

    box(menu_win, 0, 0);
    for (int i = 0; i < n_choices; ++i) {
        if (i == highlight) {
            wattron(menu_win, A_REVERSE); // Highlight selection
        }
        mvwprintw(menu_win, i + 1, 1, "%s", choices[i].c_str());
        wattroff(menu_win, A_REVERSE);
    }
    wrefresh(menu_win);
}

void handleMenuSelection(int choice, FlatsManager &manager) {
    switch (choice) {
        case 0:
            addFlat(manager);
            break;
        case 1:
            //removeFlat(manager);
            break;
        case 2:
            //findFlat(manager);
            break;
        case 3:
            listFlatsSimple(manager.flats);
            break;
        case 4:
            //listFlatsFull(manager.flats);
            break;
        case 5:
            loadFromCSV(manager);
            break;
        case 6:
            //saveToCSV;
            break;
        case 7:
            // Exit the program
            break;
    }
}

int main() {
    initscr(); // Initialize the screen
    cbreak(); // Disable line buffering
    noecho(); // Disable automatic echoing of typed characters
    keypad(stdscr, TRUE); // Enable special keys like arrow keys
    curs_set(0); // Hide the cursor

    FlatsManager manager; // Create the FlatsManager instance

    int highlight = 0;
    int choice = 0;
    int c;

    WINDOW* menu_win = newwin(10, 30, 2, 150); // Create a new window for the menu
    keypad(menu_win, TRUE); // Enable special keys in the menu window

    while (true) {
        clear(); // Clear the screen before displaying the menu
        displayMenu(menu_win, highlight); // Display the menu
        c = wgetch(menu_win); // Get user input

        switch (c) {
            case KEY_UP:
                if (highlight > 0) --highlight; // Move highlight up
                break;
            case KEY_DOWN:
                if (highlight < 7) ++highlight; // Move highlight down
                break;
            case 10: // Enter key
                choice = highlight;
                handleMenuSelection(choice, manager); // Handle the menu selection
                if (choice == 7) {
                    endwin(); // End ncurses mode
                    return 0; // Exit the program
                }
                clear();
                break;
            default:
                break;
        }
    }

    endwin(); // End ncurses mode
    return 0; // Exit the program
}
