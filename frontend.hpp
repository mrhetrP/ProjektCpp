#include <ncurses.h>
#include "flatsManager.hpp"

void addFlat(FlatsManager & manager);
void removeFlat(FlatsManager & manager);

void findFlat(FlatsManager & manager);
void handleMultipleFlatsMenu(const std::vector<Flat>& foundFlats);
void handleSingleFlatMenu(FlatsManager & manager, Flat & flat);
void addItem(FlatsManager & manager, Flat & flat);
void removeItem(Flat & flat);
void addContract(Flat & flat);
void removeContract(Flat & flat);

void listFlatsSimple(std::vector<Flat> flats);
void listFlatsFull(std::vector<Flat> flats);

void loadFromCSV(FlatsManager & manager);
void saveToCSV(FlatsManager & manager);

void displayMenu(WINDOW* menu_win, int highlight);
void handleMenuSelection(int choice, FlatsManager & manager);