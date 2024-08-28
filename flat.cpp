# include "flatsManager.hpp"

void Flat::addItem(FlatsManager & manager, const Item & item) {
    std::vector<Flat> flatsAtSameAddress = manager.findFlats(addr.street, addr.conscriptionNumber, addr.streetNumber, addr.city, addr.postCode);
    for (const auto &flat : flatsAtSameAddress) {
        auto it = std::find_if(flat.items.begin(), flat.items.end(), [&item](const Item &existingItem) {
           return existingItem.id == item.id;
        });
        if (it != flat.items.end()) {
            throw std::invalid_argument("An item with the same ID already exists in a flat at this address");
        }
    }
    auto it = std::lower_bound(this->items.begin(), this->items.end(), item.id, [&](const Item & i, const int & id) {
        return (i.id < item.id);
    });
    items.insert(it, item);
}

void Flat::removeItem(int id) {
    auto it = std::find_if(items.begin(), items.end(), [id](const Item& item) {
        return item.id == id;
    });
    if (it != items.end()) {
        items.erase(it);
    } else {
        throw std::invalid_argument("Item with the specified ID does not exist");
    }
}

void Flat::addContract(const Contract & contract) {
    if (contract.expDate < contract.startDate) {
        throw std::invalid_argument("New contract expDate is earlier than startDate");
    }
    auto it = std::lower_bound(this->contracts.begin(), this->contracts.end(), contract.startDate, 
        [](const Contract & c, const Date & date) {
            return c.startDate < date;
        });
    // Check if there's a previous contract and if the startDate overlaps with the previous contract's expDate
    if (it != this->contracts.begin()) {
        auto prevContract = std::prev(it);
        if (contract.startDate < prevContract->expDate) {
            throw std::invalid_argument("New contract startDate overlaps with the previous contract's expDate");
        }
    }
    if (it != contracts.end()) {
        if (it->startDate < contract.expDate) {
            throw std::invalid_argument("New contract expDate overlaps with next contract startDate");
        }
    }
    contracts.insert(it, contract);
}

void Flat::removeContract(const Contract &contract) {
    auto it = std::find_if(contracts.begin(), contracts.end(), [&](const Contract &c) {
        return c == contract;
    });
    if (it != contracts.end()) {
        contracts.erase(it);
    } else {
        throw std::invalid_argument("The specified contract does not exist");
    }
}


// For simple terminal/command line output
void Flat::simpleDescription() const {
    std::cout << std::left << std::setw(40) << (this->addr.street + " " + std::to_string(this->addr.conscriptionNumber) + "/"
        + this->addr.streetNumber + ", " + this->addr.city + ", " + std::to_string(this->addr.postCode));
    std::cout << std::left << std::setw(20) << ("| " + std::to_string(this->number));
    std::cout << std::left << std::setw(20) << ("| " + std::to_string(this->items.size()));
    if (!this->contracts.empty()) {
        std::cout << std::left << std::setw(20) << ("| " + this->contracts.back().tenant.name);
    } else {
        std::cout << std::left << std::setw(20) << "| no contracts";
    }
    std::cout << std::endl;
}

// For simple terminal/command line output
void Flat::fullDescription() const {
    // First line
    std::cout << std::left << std::setw(40) << (this->addr.street + " " + std::to_string(this->addr.conscriptionNumber) + "/"
        + this->addr.streetNumber + ", " + this->addr.city + ", " + std::to_string(this->addr.postCode));
    std::cout << std::left << std::setw(17) << ("| " + std::to_string(this->number));
    if (!this->items.empty() && !this->contracts.empty()) {
        std::cout << std::left << std::setw(20) << ("| " + std::to_string(this->items.front().id) + ", " + this->items.front().name);
        std::cout << std::left << std::setw(35) << ("| " + std::to_string(this->contracts.front().startDate.month) + "/" + std::to_string(this->contracts.front().startDate.year)
            + " - " + std::to_string(this->contracts.front().expDate.month) + "/" + std::to_string(this->contracts.front().expDate.year) + " " + this->contracts.front().tenant.name);
    } else if (this->items.empty() && !this->contracts.empty()) {
        std::cout << std::left << std::setw(20) << "| no items";
        std::cout << std::left << std::setw(35) << ("| " + std::to_string(this->contracts.front().startDate.month) + "/" + std::to_string(this->contracts.front().startDate.year)
            + " - " + std::to_string(this->contracts.front().expDate.month) + "/" + std::to_string(this->contracts.front().expDate.year) + " " + this->contracts.front().tenant.name);
    } else if (this->items.empty() && !this->contracts.empty()) {
        std::cout << std::left << std::setw(20) << ("| " + std::to_string(this->items.front().id) + ", " + this->items.front().name);
        std::cout << std::left << std::setw(35) << "| no contracts";
    } else {
        std::cout << std::left << std::setw(20) << "| no items";
        std::cout << std::left << std::setw(35) << "| no contracts";
    }
    std::cout << std::endl;

    // Other lines
    auto contract = this->contracts.begin();
    if (!this->contracts.empty()) ++contract;

    auto item = this->items.size() > 1 ? this->items.begin() + 1 : this->items.end();

    while (item != this->items.end() || contract != this->contracts.end()) {
        std::cout << std::string(40, ' ') << std::string(17, ' ');

        if (item != this->items.end()) {
            std::cout << std::left << std::setw(20) << ("| " + std::to_string(item->id) + ", " + item->name);
            ++item;
        } else {
            std::cout << std::left << std::setw(20) << "|";
        }

        if (contract != this->contracts.end()) {
            std::cout << std::left << std::setw(35) 
                      << ("| " + std::to_string(contract->startDate.month) + "/" + std::to_string(contract->startDate.year)
                          + " - " + std::to_string(contract->expDate.month) + "/" + std::to_string(contract->expDate.year) + " " + contract->tenant.name);
            ++contract;
        } else {
            std::cout << std::left << std::setw(35) << "|";
        }

        std::cout << std::endl;
    }
}