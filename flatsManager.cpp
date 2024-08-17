# include "flatsManager.hpp"

void flatsManager::addFlat (const Flat & flat) {
    // Check if the flat already exists
    auto it = std::lower_bound(flats.begin(), flats.end(), flat.addr, [&](const Flat & f, const Address & addr) {
        return (f.addr < flat.addr || f.number < flat.number);
    });
    if (it != flats.end() && it->addr == flat.addr && it->number == flat.number) {
        throw std::invalid_argument("Flat already exists");
    }
    flats.insert(it, flat);
}

void flatsManager::printAll () {
    for (const auto & flat : flats) {
        std::cout << "Address: " << flat.addr.city << " " << flat.addr.street << " " << flat.addr.conscriptionNumber << "/" << flat.addr.streetNumber << std::endl;
        std::cout << "Flat number: " << flat.number << std::endl;
        std::cout << std::endl;
    }
}