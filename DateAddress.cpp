#include <regex>
# include "flatsManager.hpp"

Date::Date(int y, int m, int d) {
    if (y < 2000 || y > 2100) {
        throw std::out_of_range("Year must be between 2000 and 2100.");
    }
    if (m < 1 || m > 12) {
        throw std::out_of_range("Month must be between 1 and 12.");
    }
    if (d < 1 || d > daysInMonth(m, y)) {
        throw std::out_of_range("Day is out of range for the given month and year.");
    }
    year = y;
    month = m;
    day = d;
}

bool Date::operator<(const Date &other) const {
    if (year < other.year) {
        return true;
    } else if (year > other.year) {
        return false;
    } 
    if (month < other.month) {
        return true;
    } else if (month > other.month) {
        return false;
    } 
    return day < other.day;
}

int Date::daysInMonth(int month, int year) {
    if (month == 2) { // February
        return (isLeapYear(year) ? 29 : 28);
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) {    // Months with 30 days
        return 30;
    }
    return 31;  // Months with 31 days
}

bool Date::isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

Address::Address (const std::string & street, int conscriptionNumber, const std::string & streetNumber, const std::string & city, int postCode) {
    if (!isValidStreetNumber(streetNumber)) {
        throw std::invalid_argument("Street number must be a number or a number followed by a letter.");
    }
    if (postCode < 10000 || postCode > 99999) {
        throw std::out_of_range("Post code must be in formate nnnnn.");
    }
    this->street = street;
    this->conscriptionNumber = conscriptionNumber;
    this->streetNumber = streetNumber;
    this->city = city;
    this->postCode = postCode;
}

bool Address::isValidStreetNumber(const std::string & str) { //must be a number or a number followed by a letter
    std::regex pattern("^\\d+[A-Za-z]?$");
    return std::regex_match(str, pattern);
}

bool Address::operator<(const Address &other) const {
    if (city != other.city) {
        return city < other.city;
    }
    if (street != other.street) {
        return street < other.street;
    }
    if (conscriptionNumber != other.conscriptionNumber) {
        return conscriptionNumber < other.conscriptionNumber;
    }
    if (streetNumber != other.streetNumber) {
        return streetNumber < other.streetNumber;
    }
    return postCode < other.postCode;
}

bool Address::operator==(const Address & other) const {
    return street == other.street &&
               conscriptionNumber == other.conscriptionNumber &&
               streetNumber == other.streetNumber &&
               city == other.city &&
               postCode == other.postCode;
}