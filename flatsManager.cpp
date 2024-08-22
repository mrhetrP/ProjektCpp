# include "flatsManager.hpp"

/*Usage examples:
    auto allFlats = manager.findFlats();
    auto flatsOnMainStreet = manager.findFlats("Main Street");
    auto flatsInPrague = manager.findFlats(std::nullopt, std::nullopt, std::nullopt, "Prague");
    auto specificFlat = manager.findFlats("Main Street", 123, "45A", "Prague", 11000, 1);
*/
std::vector<Flat> flatsManager::findFlats(const std::optional<std::string> & street,
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
                throw std::invalid_argument("No tenants");
            }
        }

        if (matches) {
            results.push_back(flat);
        }
    }
    return results;
}

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

void flatsManager::removeFlat (const Flat & flat) {
    auto it = std::lower_bound(flats.begin(), flats.end(), flat.addr, [&](const Flat & f, const Address & addr) {
        return (f.addr < flat.addr || f.number < flat.number);
    });
    if (it != flats.end() && it->addr == flat.addr && it->number == flat.number){
        flats.erase(it);
        std::cout << "Flat removed successfully" << std::endl;
    }
    else throw std::invalid_argument("Flat does not exist");
}

void flatsManager::printAll () {
    for (const auto & flat : flats) {
        std::cout << "Address: " << flat.addr.city << " " << flat.addr.street << " " << flat.addr.conscriptionNumber << "/" << flat.addr.streetNumber << std::endl;
        std::cout << "Flat number: " << flat.number << std::endl;
        std::cout << "Items: " << std::endl;
        for (const auto & item : flat.items) {
            std::cout << "\t" << item.id << " " << item.name << std::endl;
        }
        std::cout << "Contracts: " << std::endl;
        for (const auto & contract : flat.contracts) {
            std::cout << "\t" << contract.startDate.month << "/" << contract.startDate.year << " - " << contract.expDate.month << "/" << contract.expDate.year << std::endl;
        }
        std::cout << std::endl;
    }
}

void flatsManager::loadFromCSV(const std::string &filename) {
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
        if (!token.empty() && token[0] == '\"') token = token.substr(1, token.size() - 2);
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
        std::string contractToken;
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

            std::getline(contractStream, tenantStreet, ',');
            std::getline(contractStream, token, ','); tenantConscriptionNumber = std::stoi(token);
            std::getline(contractStream, tenantStreetNumber, ',');
            std::getline(contractStream, tenantCity, ',');
            std::getline(contractStream, token, ','); tenantPostCode = std::stoi(token);

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

void flatsManager::saveToCSV(const std::string &filename) const {
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
                            << contract.tenant.domicile.street << "," << contract.tenant.domicile.conscriptionNumber << ","
                            << contract.tenant.domicile.streetNumber << "," << contract.tenant.domicile.city << ","
                            << contract.tenant.domicile.postCode << ";";
        }
        std::string contracts = contractsStream.str();
        if (!contracts.empty()) contracts.pop_back(); // remove the last ';'

        file << "\"" << contracts << "\"\n";
    }
    file.close();
}