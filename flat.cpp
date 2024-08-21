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

//void Flat::removeItem(int id);

void Flat::addContract(const Contract & contract) {
    auto it = std::lower_bound(this->contracts.begin(), this->contracts.end(), contract.startDate, [&](const Contract & c, const Date & date) {
        return (c.startDate < contract.startDate);
    });
    contracts.insert(it, contract);
}

//void Flat::removeContract(const Contract & contract);