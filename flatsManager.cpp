# include "flatsManager.hpp"

/*Usage examples:
    auto allFlats = manager.findFlats();
    auto flatsOnMainStreet = manager.findFlats("Main Street");
    auto flatsInPrague = manager.findFlats(std::nullopt, std::nullopt, std::nullopt, "Prague");
    auto specificFlat = manager.findFlats("Main Street", 123, "45A", "Prague", 11000, 1);
*/
std::vector<Flat> FlatsManager::findFlats(const std::optional<std::string> & street,
                                          const std::optional<int> & conscriptionNumber,
                                          const std::optional<std::string> & streetNumber,
                                          const std::optional<std::string> & city,
                                          const std::optional<int> & postCode,
                                          const std::optional<int> & number,
                                          const std::optional<std::string> & tenantName) const {
    std::vector<Flat> results;
    for (const auto & flat : flats) {
        bool matches = true;

        if (street && flat.addr.street != *street) matches = false;
        if (conscriptionNumber && flat.addr.conscriptionNumber != *conscriptionNumber) matches = false;
        if (streetNumber && flat.addr.streetNumber != *streetNumber) matches = false;
        if (city && flat.addr.city != *city) matches = false;
        if (postCode && flat.addr.postCode != *postCode) matches = false;
        if (number && flat.number != *number) matches = false;
        if (tenantName) {
            if (!flat.contracts.empty()) {
                if (tenantName && flat.contracts.back().tenant.name != *tenantName) matches = false;
            } else {
                matches = false;
            }
        }

        if (matches) {
            results.push_back(flat);
        }
    }
    return results;
}

void FlatsManager::addFlat (const Flat & flat) {
    auto it = std::lower_bound(flats.begin(), flats.end(), flat.addr, [&](const Flat & f, const Address & addr) {
        return (f.addr < flat.addr || f.number < flat.number);
    });
    if (it != flats.end() && it->addr == flat.addr && it->number == flat.number) {
        throw std::invalid_argument("Flat already exists");
    }
    flats.insert(it, flat);
}

void FlatsManager::removeFlat (const Flat & flat) {
    auto it = std::lower_bound(flats.begin(), flats.end(), flat.addr, [&](const Flat & f, const Address & addr) {
        return (f.addr < flat.addr || f.number < flat.number);
    });
    if (it != flats.end() && it->addr == flat.addr && it->number == flat.number){
        flats.erase(it);
    } else throw std::invalid_argument("Flat does not exist");
}

// For simple terminal/command line output
void FlatsManager::printAllSimple () {
    std::cout << std::endl;
    std::cout << std::left << std::setw(40) << "Address:";
    std::cout << std::left << std::setw(20) << "| Flat number:";
    std::cout << std::left << std::setw(20) << "| Number of items:";
    std::cout << std::left << std::setw(20) << "| Latest tenant:";
    std::cout << std::endl;
    std::cout << std::string(40, '-') + "+" + std::string(19, '-') + "+" + std::string(19, '-') + "+" + std::string(19, '-') << std::endl;
    for (const auto & flat : flats) {
        flat.simpleDescription();
    }
}

void FlatsManager::printAllFull () {
    std::cout << std::endl;
    std::cout << std::left << std::setw(40) << "Address:";
    std::cout << std::left << std::setw(17) << "| Flat number:";
    std::cout << std::left << std::setw(20) << "| Items:";
    std::cout << std::left << std::setw(35) << "| Contracts";
    std::cout << std::endl;
    std::cout << std::string(40, '-') + "+" + std::string(16, '-') + "+" + std::string(19, '-') + "+" + std::string(34, '-') << std::endl;
    for (const auto & flat : flats) {
        flat.fullDescription();
        std::cout << std::endl;
    }
}

// For simple terminal/command line output
void FlatsManager::loadFromCSV(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file");
    }

    std::string line;
    std::getline(file, line); // skip the header

    while (std::getline(file, line)) {
        std::stringstream lineStream(line);
        std::string token;

        // Address fields
        std::string street, streetNumber, city;
        int conscriptionNumber, postCode, number;
        std::getline(lineStream, street, ',');
        std::getline(lineStream, token, ','); conscriptionNumber = std::stoi(token);
        std::getline(lineStream, streetNumber, ',');
        std::getline(lineStream, city, ',');
        std::getline(lineStream, token, ','); postCode = std::stoi(token);

        // Flat number
        std::getline(lineStream, token, ','); number = std::stoi(token);

        // Items
        std::vector<Item> items;
        std::getline(lineStream, token, ',');
        if (!token.empty() && token[0] == '\"') token = token.substr(1, token.size() - 2);  // remove quotes
        std::stringstream itemsStream(token);
        std::string itemToken;
        while (std::getline(itemsStream, itemToken, ';')) {
            std::stringstream itemStream(itemToken);
            std::string name;
            int id;
            std::getline(itemStream, name, ':');
            itemStream >> id;
            items.push_back({name, id});
        }

        // Contracts
        std::vector<Contract> contracts;
        std::getline(lineStream, token, ',');
        if (!token.empty() && token[0] == '\"') token = token.substr(1, token.size() - 2);
        std::stringstream contractsStream(token);
        std::string contractToken = "";
        while (std::getline(contractsStream, contractToken, ';')) {
            std::stringstream contractStream(contractToken);
            int sy, sm, sd, ey, em, ed;
            std::string name;
            std::string tenantStreet, tenantStreetNumber, tenantCity;
            int tenantConscriptionNumber, tenantPostCode;
            int by, bm, bd;
            std::getline(contractStream, token, '-'); sy = std::stoi(token);
            std::getline(contractStream, token, '-'); sm = std::stoi(token);
            std::getline(contractStream, token, ':'); sd = std::stoi(token);

            std::getline(contractStream, token, '-'); ey = std::stoi(token);
            std::getline(contractStream, token, '-'); em = std::stoi(token);
            std::getline(contractStream, token, ':'); ed = std::stoi(token);

            std::getline(contractStream, name, ':');

            std::getline(contractStream, token, '-'); by = std::stoi(token);
            std::getline(contractStream, token, '-'); bm = std::stoi(token);
            std::getline(contractStream, token, ':'); bd = std::stoi(token);

            std::getline(contractStream, tenantStreet, '.');
            std::getline(contractStream, token, '.'); tenantConscriptionNumber = std::stoi(token);
            std::getline(contractStream, tenantStreetNumber, '.');
            std::getline(contractStream, tenantCity, '.');
            std::getline(contractStream, token, '.'); tenantPostCode = std::stoi(token);

            Date startDate(sy, sm, sd);
            Date expDate(ey, em, ed);
            Address tenantAddress(tenantStreet, tenantConscriptionNumber, tenantStreetNumber, tenantCity, tenantPostCode);
            Tenant tenant{name, Date(by, bm, bd), tenantAddress};
            contracts.push_back({startDate, expDate, tenant});
        }

        Flat flat(Address(street, conscriptionNumber, streetNumber, city, postCode), number);
        flat.items = items;
        flat.contracts = contracts;
        flats.push_back(flat);
    }
    file.close();
}

void FlatsManager::saveToCSV(const std::string &filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file");
    }

    file << "street,conscriptionNumber,streetNumber,city,postCode,number,items,contracts\n";

    for (const auto &flat : flats) {
        file << flat.addr.street << ","
             << flat.addr.conscriptionNumber << ","
             << flat.addr.streetNumber << ","
             << flat.addr.city << ","
             << flat.addr.postCode << ","
             << flat.number << ",";

        // Serialize items
        std::stringstream itemsStream;
        for (const auto &item : flat.items) {
            itemsStream << item.name << ":" << item.id << ";";
        }
        std::string items = itemsStream.str();
        if (!items.empty()) items.pop_back(); // remove the last ';'

        file << "\"" << items << "\",";

        // Serialize contracts
        std::stringstream contractsStream;
        for (const auto &contract : flat.contracts) {
            contractsStream << contract.startDate.year << "-" << contract.startDate.month << "-" << contract.startDate.day << ":"
                            << contract.expDate.year << "-" << contract.expDate.month << "-" << contract.expDate.day << ":"
                            << contract.tenant.name << ":"
                            << contract.tenant.birthDate.year << "-" << contract.tenant.birthDate.month << "-" << contract.tenant.birthDate.day << ":"
                            << contract.tenant.domicile.street << "." << contract.tenant.domicile.conscriptionNumber << "."
                            << contract.tenant.domicile.streetNumber << "." << contract.tenant.domicile.city << "."
                            << contract.tenant.domicile.postCode << ";";
        }
        std::string contracts = contractsStream.str();
        if (!contracts.empty()) contracts.pop_back(); // remove the last ';'

        file << "\"" << contracts << "\"\n";
    }
    file.close();
}
