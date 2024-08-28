#include <ncurses.h>
//#include "flatsManager.hpp"
#include "frontend.hpp"
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
    //x.printAllSimple();
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
    
    //x.loadFromCSV("flats.csv");
    x.printAllFull();
    return EXIT_SUCCESS;
}
*/

int main() {
    initscr(); // Initialize the screen
    cbreak(); // Disable line buffering
    keypad(stdscr, TRUE); // Enable special keys like arrow keys
    curs_set(0); // Hide the cursor

    FlatsManager manager;

    int highlight = 0;
    int choice = 0;
    int c;

    WINDOW* menu_win = newwin(10, 30, 2, 150); // Create a new window for the menu
    keypad(menu_win, TRUE); // Enable special keys in the menu window

    while (true) {
        clear();
        displayMenu(menu_win, highlight);
        c = wgetch(menu_win);

        switch (c) {
            case KEY_UP:
                if (highlight > 0) --highlight; // Move highlight up
                break;
            case KEY_DOWN:
                if (highlight < 7) ++highlight; // Move highlight down
                break;
            case 10: // Enter key
                choice = highlight;
                handleMenuSelection(choice, manager);
                if (choice == 7) {
                    endwin(); // End ncurses mode
                    return EXIT_SUCCESS;
                }
                clear();
                break;
            default:
                break;
        }
    }

    endwin(); // End ncurses mode
    return EXIT_SUCCESS;
}
