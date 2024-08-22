# include "flatsManager.hpp"

void Flat::addItem(flatsManager & manager, const Item & item) {
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
    // Find the correct position to insert the contract based on startDate
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

    // If the contract is found, remove it
    if (it != contracts.end()) {
        contracts.erase(it);
    } else {
        // If the contract does not exist, throw an exception or handle the error
        throw std::invalid_argument("The specified contract does not exist");
    }
}