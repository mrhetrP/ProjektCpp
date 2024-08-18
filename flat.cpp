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
    items.push_back(item);
}

//void Flat::removeItem(int id);

//void Flat::addContract(const Contract & contract);
//void Flat::removeContract(const Contract & contract);