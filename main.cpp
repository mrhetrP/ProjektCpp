#include "flatsManager.hpp"

int main (void) {
    //Date day(2022, 7, 28);
    
    flatsManager x;

    Address addr1("Blanická", 1256, "123A", "Prag", 12345);
    Flat flat1(addr1, 1);
    x.addFlat(flat1);

    Address addr2("Blanická", 1256, "123B", "Prag", 12346);
    Flat flat2(addr2, 1);
    x.addFlat(flat2);
    x.printAll();
    Item item(12, "xy");
    flat2.addItem(x, item);
    std::cout << flat2.items.back().id << std::endl;

    //x.removeFlat(flat2);
    //auto flatsOnMainStreet = x.findFlats("Blanická");

    x.saveToCSV("flats.csv");
    //x.loadFromCSV("flats.csv");
    x.printAll();
    return EXIT_SUCCESS;
}