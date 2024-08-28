#include "frontend.hpp"

void addFlat(FlatsManager & manager) {
    char street[50], city[50], streetNumber[10];
    int conscriptionNumber, postCode, flatNumber;
    bool success = false;

    while (!success) {
        echo();
        curs_set(1);
        mvprintw(1, 2, "Enter Street Name: ");
        getstr(street);
        mvprintw(2, 2, "Enter Conscription Number: ");
        scanw("%d", &conscriptionNumber);
        mvprintw(3, 2, "Enter Street Number: ");
        getstr(streetNumber);
        mvprintw(4, 2, "Enter City: ");
        getstr(city);
        mvprintw(5, 2, "Enter Postcode: ");
        scanw("%d", &postCode);
        mvprintw(6, 2, "Enter Flat Number: ");
        scanw("%d", &flatNumber);
        curs_set(0);
        
        try {
            Address addr(street, conscriptionNumber, streetNumber, city, postCode);
            Flat flat(addr, flatNumber);
            manager.addFlat(flat);
            clear();
            mvprintw(1, 2, "Flat added successfully");
            mvprintw(3, 2, "Do you want to add item(s)? (y/n): ");
            char response = getch();
            if (response == 'y' || response == 'Y') {
                clear();
                refresh();
                addItem(manager, manager.flats.back());
            }
            // TO DO add contract?
            success = true; // Break the loop on success
            clear();
            refresh();
        } catch (const std::invalid_argument& e) {
            clear();
            mvprintw(1, 2, "Error: %s", e.what());
            mvprintw(3, 2, "Do you want to try again? (y/n): ");
            char response = getch();
            if (response != 'y' && response != 'Y') {
                clear();
                refresh();
                mvprintw(1, 2, "Operation cancelled. Press any key to return to the main menu.");
                getch();
                success = true; // Break the loop to exit
            }
            clear();
            refresh();
        }
    }
}

void removeFlat(FlatsManager & manager) {
    char street[50], city[50], streetNumber[10];
    int conscriptionNumber, postCode, flatNumber;
    bool success = false;

    while (!success) {
        echo();
        curs_set(1);
        mvprintw(1, 2, "Enter Street Name: ");
        getstr(street);
        mvprintw(2, 2, "Enter Conscription Number: ");
        scanw("%d", &conscriptionNumber);
        mvprintw(3, 2, "Enter Street Number: ");
        getstr(streetNumber);
        mvprintw(4, 2, "Enter City: ");
        getstr(city);
        mvprintw(5, 2, "Enter Postcode: ");
        scanw("%d", &postCode);
        mvprintw(6, 2, "Enter Flat Number: ");
        scanw("%d", &flatNumber);

        
        try {
            Address addr(street, conscriptionNumber, streetNumber, city, postCode);
            Flat flat(addr, flatNumber);
            manager.removeFlat(flat);
            clear();
            mvprintw(1, 2, "Flat removed successfully. Press any key to return to the main menu.");
            success = true; // Break the loop on success
            getch();
            clear();
            refresh();
        } catch (const std::invalid_argument& e) {
            clear();
            refresh();
            mvprintw(1, 2, "Error: %s", e.what());
            mvprintw(3, 2, "Do you want to try again? (y/n): ");
            char response = getch();
            if (response != 'y' && response != 'Y') {
                clear();
                refresh();
                mvprintw(1, 2, "Operation cancelled. Press any key to return to the main menu.");
                getch();
                success = true; // Break the loop to exit
            }
            clear();
            refresh();
        }
        curs_set(0);
    }
}

void findFlat(FlatsManager & manager) {
    char street[50] = "", city[50] = "", streetNumber[10] = "", tenantName[50] = "";
    int conscriptionNumber = -1, postCode = -1, flatNumber = -1;

    echo();
    curs_set(1);
    mvprintw(1, 2, "Enter flat parameters, if you want to skip a parameter just press Enter.");
    mvprintw(3, 2, "Enter Street Name:");
    getstr(street);
    mvprintw(4, 2, "Enter Conscription Number:");
    scanw("%d", &conscriptionNumber);
    mvprintw(5, 2, "Enter Street Number:");
    getstr(streetNumber);
    mvprintw(6, 2, "Enter City:");
    getstr(city);
    mvprintw(7, 2, "Enter Postcode:");
    scanw("%d", &postCode);
    mvprintw(8, 2, "Enter Flat Number:");
    scanw("%d", &flatNumber);
    mvprintw(9, 2, "Tenant Name:");
    getstr(tenantName);
    curs_set(0);
    
    auto foundFlats = manager.findFlats(
        street[0] ? std::optional<std::string>(street) : std::nullopt,
        conscriptionNumber != -1 ? std::optional<int>(conscriptionNumber) : std::nullopt,
        streetNumber[0] ? std::optional<std::string>(streetNumber) : std::nullopt,
        city[0] ? std::optional<std::string>(city) : std::nullopt,
        postCode != -1 ? std::optional<int>(postCode) : std::nullopt,
        flatNumber != -1 ? std::optional<int>(flatNumber) : std::nullopt,
        tenantName[0] ? std::optional<std::string>(tenantName) : std::nullopt
    ); 
    clear();
    refresh();
    if (foundFlats.size() > 1) {
        handleMultipleFlatsMenu(foundFlats);
    } else if (foundFlats.size() == 1) {
        handleSingleFlatMenu(manager, foundFlats[0]);
    } else {
        mvprintw(1, 2, "No flats found.");
        getch();
        clear();
        refresh();
    }
}

void handleMultipleFlatsMenu(const std::vector<Flat>& foundFlats) {
    mvprintw(1, 2, "%ld flats found", foundFlats.size());
    mvprintw(2, 2, "What do you want to do with them?");
    refresh();

    int highlight = 0;
    int choice = 0;
    int c;
    WINDOW* menu_win = newwin(10, 40, 3, 2);
    keypad(menu_win, TRUE);

    std::string choices[] = {
        "Display Flats Simple",
        "Display Flats Full"
    };
    int n_choices = sizeof(choices) / sizeof(choices[0]);

    while (true) {
        for (int i = 0; i < n_choices; ++i) {
            if (i == highlight) {
                wattron(menu_win, A_REVERSE);
            }
            mvwprintw(menu_win, i + 1, 1, "%s", choices[i].c_str());
            wattroff(menu_win, A_REVERSE);
        }
        wrefresh(menu_win);

        c = wgetch(menu_win);

        switch (c) {
            case KEY_UP:
                if (highlight > 0) --highlight;
                break;
            case KEY_DOWN:
                if (highlight < n_choices - 1) ++highlight;
                break;
            case 10: // Enter key
                choice = highlight;
                break;
            default:
                break;
        }

        if (c == 10) break;
    }

    clear();
    refresh();

    if (choice == 0) {
        listFlatsSimple(foundFlats);
    } else if (choice == 1) {
        listFlatsFull(foundFlats);
    }
}

void handleSingleFlatMenu(FlatsManager & manager, Flat & flat) {
    mvprintw(1, 2, "1 flat found");
    mvprintw(2, 2, "What do you want to do with it?");
    refresh();

    int highlight = 0;
    int choice = 0;
    int c;
    WINDOW* menu_win = newwin(10, 40, 3, 2);
    keypad(menu_win, TRUE);

    std::string choices[] = {
        "Remove Flat",
        "Add Item",
        "Remove Item",
        "Add Contract",
        "Remove Contract"
    };
    int n_choices = sizeof(choices) / sizeof(choices[0]);

    while (true) {
        for (int i = 0; i < n_choices; ++i) {
            if (i == highlight) {
                wattron(menu_win, A_REVERSE);
            }
            mvwprintw(menu_win, i + 1, 1, "%s", choices[i].c_str());
            wattroff(menu_win, A_REVERSE);
        }
        wrefresh(menu_win);

        c = wgetch(menu_win);

        switch (c) {
            case KEY_UP:
                if (highlight > 0) --highlight;
                break;
            case KEY_DOWN:
                if (highlight < n_choices - 1) ++highlight;
                break;
            case 10: // Enter key
                choice = highlight;
                break;
            default:
                break;
        }

        if (c == 10) break;
    }

    clear();
    refresh();

    switch (choice) {
        case 0: // Remove flat
            manager.removeFlat(flat);
            mvprintw(1, 2, "Flat removed successfully. Press any key to return to the main menu.");
            getch();
            clear();
            refresh();
            break;
        case 1: // Add item
            addItem(manager, flat);
            mvprintw(1, 2, "Adding item...");
            break;
        case 2:
            // Remove item
            mvprintw(1, 2, "Removing item...");
            // Add code to remove item from the flat
            break;
        case 3:
            // Add contract
            mvprintw(1, 2, "Adding contract...");
            // Add code to add contract to the flat
            break;
        case 4:
            // Remove contract
            mvprintw(1, 2, "Removing contract...");
            // Add code to remove contract from the flat
            break;
    }
}

void addItem(FlatsManager & manager, Flat & flat) {
    char name[50] = "";
    int id = -1;

    echo();
    curs_set(1);
    mvprintw(3, 2, "Enter Item Name:");
    getstr(name);
    mvprintw(4, 2, "Enter Id Number:");
    scanw("%d", &id);
    curs_set(0);

    try {
        flat.addItem(manager, Item(name, id));
        clear();
        mvprintw(1, 2, "Item added successfully. Do you want to add another item? (y/n):");
        char response = getch();
        if (response == 'y' || response == 'Y') {
            clear();
            refresh();
            addItem(manager, flat);
        }
        clear();
        refresh();
    } catch(const std::exception& e) {
        clear();
        mvprintw(1, 2, "Error: %s", e.what());
        mvprintw(3, 2, "Do you want to try again? (y/n): ");
        char response = getch();
        if (response == 'y' || response == 'Y') {
            clear();
            refresh();
            addItem(manager, flat);
        }
        clear();
        refresh();
    }
    
}

void removeItem(Flat & flat) {
    // code
}

void addContract(Flat & flat) {
    // code
}

void removeContract(Flat & flat) {
    // code
}

void listFlatsSimple(std::vector<Flat> flats) {
    clear();
    refresh();
    mvprintw(1, 2, "%ld flats:", flats.size());
    mvprintw(3, 2, "Address:");                         mvprintw(3, 45, "| Flat number:");                    mvprintw(3, 65, "| Number of items:");                mvprintw(3, 85, "| Latest tenant:");
    mvprintw(4, 2, "%s", std::string(45, '-').c_str()); mvprintw(4, 45, "+%s", std::string(29, '-').c_str()); mvprintw(4, 65, "+%s", std::string(29, '-').c_str()); mvprintw(4, 85, "+%s", std::string(29, '-').c_str());
    int line = 5;
    for (const auto & flat : flats) {
        mvprintw(line, 2, "%s %d/%s, %s, %d", flat.addr.street.c_str(), flat.addr.conscriptionNumber, flat.addr.streetNumber.c_str(), flat.addr.city.c_str(), flat.addr.postCode);
        mvprintw(line, 45, "| %d", flat.number);    mvprintw(line, 65, "| %ld", flat.items.size());
        if (!flat.contracts.empty()) {
            mvprintw(line, 85, "| %s", flat.contracts.back().tenant.name.c_str());
        } else {
            mvprintw(line, 85, "| no contracts");
        }
        line++;
        mvprintw(line, 45, "|"); mvprintw(line, 65, "|"); mvprintw(line, 85, "|");
        line++;
    }
    refresh();
}

void listFlatsFull(std::vector<Flat> flats) {
    clear();
    refresh();
    mvprintw(1, 2, "%ld flats:", flats.size());
    mvprintw(3, 2, "Address:");                         mvprintw(3, 45, "| Flat number:");                    mvprintw(3, 62, "| Items:");                mvprintw(3, 82, "| Contracts:");
    mvprintw(4, 2, "%s", std::string(45, '-').c_str()); mvprintw(4, 45, "+%s", std::string(16, '-').c_str()); mvprintw(4, 62, "+%s", std::string(19, '-').c_str()); mvprintw(4, 82, "+%s", std::string(40, '-').c_str());
    int line = 5;
    for (const auto & flat : flats) {
        // first line
        mvprintw(line, 2, "%s %d/%s, %s, %d", flat.addr.street.c_str(), flat.addr.conscriptionNumber, flat.addr.streetNumber.c_str(), flat.addr.city.c_str(), flat.addr.postCode);
        mvprintw(line, 45, "| %d", flat.number);
        if (!flat.items.empty()) {
            mvprintw(line, 62, "| %d, %s", flat.items.front().id, flat.items.front().name.c_str());
        } else {
            mvprintw(line, 62, "| no items");
        }
        if (!flat.contracts.empty()) {
            mvprintw(line, 82, "| %d/%d - %d/%d %s", flat.contracts.front().startDate.month, flat.contracts.front().startDate.year, flat.contracts.front().expDate.month, flat.contracts.front().expDate.year, flat.contracts.front().tenant.name.c_str());
        } else {
            mvprintw(line, 82, "| no contracts");
        }
        // other lines
        int itemLine = line +1;
        for (const auto & item : flat.items) {
            mvprintw(itemLine, 45, "|");
            mvprintw(itemLine, 62, "| %d, %s", item.id, item.name.c_str());
        }
        int contrLine = line +1;
        for (const auto & contract : flat.contracts) {
            mvprintw(contrLine, 45, "|");
            mvprintw(contrLine, 82, "| %d/%d - %d/%d %s", contract.startDate.month, contract.startDate.year, contract.expDate.month, contract.expDate.year, contract.tenant.name.c_str());
        }
        line = itemLine > contrLine ? itemLine : contrLine;
        if (flat.items.size() > 1 || flat.contracts.size() > 1) line++;
        mvprintw(line, 45, "|"); mvprintw(line, 62, "|"); mvprintw(line, 82, "|");
        line++;
    }
    refresh();
}

void loadFromCSV(FlatsManager & manager) {
    char file[100];
    echo(); // Enable echoing of user input
    curs_set(1); // Show cursor to indicate input is expected

    mvprintw(1, 2, "Enter File Name: ");
    getstr(file); // Get the file name from the user

    // Check if the file exists
    std::ifstream infile(file);
    if (!infile) {
        clear();
        refresh();
        mvprintw(1, 2, "Error: File does not exist. Press any key to return to the menu.");
        getch(); // Wait for the user to press a key
        noecho(); // Disable echoing
        curs_set(0); // Hide cursor
        clear();
        refresh();
        return; // Exit the function, returning to the menu
    }

    // File exists, proceed with loading
    manager.loadFromCSV(file);
    clear();
    refresh();
    mvprintw(1, 2, "Flats loaded successfully! Press any key to return to the menu.");
    getch(); // Wait for the user to press a key
    clear(); // Clear the screen
    noecho(); // Disable echoing of user input
    curs_set(0); // Hide cursor
    clear();
    refresh();
}

void saveToCSV(FlatsManager &manager) {
    char file[100];
    echo();
    mvprintw(1, 2, "Enter File Name to Save: ");
    getstr(file);
    clear();
    noecho();

    std::string filename(file);

    std::regex pattern("^[\\w\\-. ]+\\.csv$");
    if (filename.empty() || !std::regex_match(filename, pattern)) {
        mvprintw(1, 2, "Error: Invalid file name!");
        getch(); // Wait for user input before clearing the screen
        clear();
        return;
    }

    // Assuming FlatsManager has a method to serialize its data to CSV
    manager.saveToCSV(filename);

    mvprintw(1, 2, "Data saved successfully to %s", file);
    getch(); // Wait for user input before clearing the screen
    clear();
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

void handleMenuSelection(int choice, FlatsManager & manager) {
    switch (choice) {
        case 0:
            addFlat(manager);
            break;
        case 1:
            removeFlat(manager);
            break;
        case 2:
            findFlat(manager);
            break;
        case 3:
            listFlatsSimple(manager.flats);
            break;
        case 4:
            listFlatsFull(manager.flats);
            break;
        case 5:
            loadFromCSV(manager);
            break;
        case 6:
            saveToCSV(manager);
            break;
        case 7:
            // Exit the program
            break;
    }
}
