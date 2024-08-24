#include "flatsManager.hpp"

int main (void) {
    //Date day(2022, 7, 28);
    
    flatsManager x;
    
    Address addr1("Blanická", 1256, "123A", "Prag", 12345);
    Flat flat1(addr1, 1);
    x.addFlat(flat1);

    Address addr2("Blanická", 1256, "123B", "Prag", 12346);
    Flat flat2(addr2, 2);
    x.addFlat(flat2);
    //x.printAllSimple();
    Item item("xy", 15);
    x.flats.back().addItem(x, item);
    x.flats.back().addItem(x, Item("yz", 12));
    Date date(2015, 5, 12);
    x.flats.back().addContract(Contract(date, date, Tenant("name1", date, addr1)));
    x.flats.back().addContract(Contract(Date(2016, 3, 12), Date(2016, 5, 12), Tenant("name1", date, addr1)));
    //x.printAllSimple();
    
    x.flats.back().removeItem(12);
    x.flats.back().removeContract(Contract(Date(2016, 3, 12), Date(2016, 5, 12), Tenant("name1", date, addr1)));
    //x.removeFlat(flat2);
    //auto flatsOnMainStreet = x.findFlats("Blanická");

    x.saveToCSV("flats.csv");
    
    //x.loadFromCSV("flats.csv");
    x.printAllSimple();
    return EXIT_SUCCESS;
}
