#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <optional>

struct Date {
    int year; // must be between 2000 and 2100
    int month; // must be between 1 and 12
    int day; // must be between 1 and 28/29/30/31

    Date(int y, int m, int d);

    bool operator<(const Date & other) const;

private:
    static int daysInMonth(int month, int year);
    static bool isLeapYear(int year);
};

struct Address {
    std::string street; 
    int conscriptionNumber; // číslo popisné
    std::string streetNumber; // číslo orientační - must be number or number followed by a letter
    std::string city;
    int postCode; // number between 10000 and 99999

    Address(const std::string & street, int conscriptionNumber, const std::string & streetNumber,
            const std::string & city, int postCode);

    bool operator<(const Address & other) const;
    bool operator==(const Address & other) const;
private:
    bool isValidStreetNumber(const std::string & str);
};

struct Tenant {
    std::string name;
    Date birthDate;
    Address domicile;

    Tenant(const std::string & name, Date birthDate, Address domicile)
         : name(name), birthDate(birthDate), domicile(domicile) {};
};

struct Item {
    std::string name;
    int id;

    Item(const std::string & name, int id) : name(name), id(id) {}
};

struct Contract {
    Date startDate;
    Date expDate;
    Tenant tenant;

    Contract(Date startDate, Date expDate, Tenant tenant)
        : startDate(startDate), expDate(expDate), tenant(tenant) {}
};

class flatsManager;
struct Flat {
    Address addr;
    int number;
    std::vector<Item> items;
    std::vector<Contract> contracts;

    Flat(Address address, int number) : addr(address), number(number) {}

    void addItem(flatsManager & manager, const Item & item);
    void removeItem(int id);

    void addContract(const Contract & contract);
    void removeContract(const Contract & contract);

    std::string simpleDescription() const;
    std::string fullDescription() const;
};


class flatsManager {
    public:
        std::vector<Flat> flats;
        
        std::vector<Flat> findFlats(const std::optional<std::string> & street = std::nullopt,
                                const std::optional<int> & conscriptionNumber = std::nullopt,
                                const std::optional<std::string> & streetNumber = std::nullopt,
                                const std::optional<std::string> & city = std::nullopt,
                                const std::optional<int> & postCode = std::nullopt,
                                const std::optional<int> & number = std::nullopt,
                                const std::optional<std::string> & tenantName = std::nullopt) const;
        void addFlat(const Flat & flat);
        void removeFlat(const Flat & flat);

        void loadFromCSV(const std::string &filename);
        void saveToCSV(const std::string &filename) const;

        void printAll(); //TODO rewrite
};
