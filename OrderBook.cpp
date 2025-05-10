//
// Created by tomhi on 5/9/2025.
//

#include "OrderBook.hpp"

void OrderBook::addOrder(const std::string &id, double price, int quantity, bool isBuy) {
    Order order = {id, price, quantity, isBuy};
    orderLevels[price][id] = order;
    orderLookup[id] = order;
}

void OrderBook::modifyOrder(const std::string &id, double newPrice, int newQuantity) {
    if (orderLookup.find(id) != orderLookup.end()) {
        Order oldOrder = orderLookup[id];
        orderLevels[oldOrder.price].erase(id);
        addOrder(id, newPrice, newQuantity, oldOrder.isBuy);
    }
}

void OrderBook::deleteOrder(const std::string &id) {
    if (orderLookup.find(id) != orderLookup.end()) {
        Order order = orderLookup[id];
        orderLevels[order.price].erase(id);
        orderLookup.erase(id);
    }
}

Order *OrderBook::getOrder(const std::string &id) {
    if (orderLookup.find(id) != orderLookup.end()) {
        return &orderLookup[id];
    }
    return nullptr;
}

void OrderBook::reset() {
    orderLevels.clear();
    orderLookup.clear();
}
