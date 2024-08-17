#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

struct Date {
    int year; // must be between 2000 and 2100
    int month; // must be between 1 and 12
    int day; // must be between 1 and 28/29/30/31
};

struct Address {
    std::string street; 
    int conscriptionNumber; // číslo popisné
    std::string streetNumber; // číslo orientační (string protože např 1a)
    std::string city;
    int postCode; // number between 10000 and 99999
};


struct Item {
    std::string name;
    int id;
};

struct Contract {
    Date startDate;
    Date expDate;
    std::string tenantName;
};


struct Flat {
    Address addr;
    int number;
    std::vector<Item> items;
    std::vector<Contract> contracts;

    void addItem(const Item& item);
    void removeItem(int id);

    void addContract(const Contract& contract);
    void removeContract(const std::string& date);

    std::string simpleDescription() const;
    std::string fullDescription() const;

    bool operator<(const Flat& other) const;
};


class flatsManager {
    public:
        std::vector<Flat> flats;

        void addFlat(const Flat& flat);
        void removeFlat(const Flat& flat);
        
    private:
        /* data */
};
