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

    Date(int y, int m, int d);

    static int daysInMonth(int month, int year);
    static bool isLeapYear(int year);
};

struct Address {
    std::string street; 
    int conscriptionNumber; // číslo popisné
    std::string streetNumber; // číslo orientační - must be number or number followed by a letter
    std::string city;
    int postCode; // number between 10000 and 99999

    Address(const std::string& street, int conscriptionNumber, const std::string& streetNumber,
            const std::string& city, int postCode);
private:
    bool isValidStreetNumber(const std::string& str);
};

struct Tenant {
    std::string name;
    Date birthDate;
    Address domicile;
};

struct Item {
    std::string name;
    int id;
};

struct Contract {
    Date startDate;
    Date expDate;
    Tenant tenant;
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
