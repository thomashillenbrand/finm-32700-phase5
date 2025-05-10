//
// Created by tomhi on 5/9/2025.
//

#include "OptimizedOrderBook.hpp"

OptimizedOrderBook::OptimizedOrderBook(size_t maxOrders) {
    orderPool.resize(maxOrders);
    for (int i = 0; i < maxOrders; ++i) {
        freeIndices.push(i);
    }
}

void OptimizedOrderBook::addOrder(const std::string &id, double price, int quantity, bool isBuy) {
    if (freeIndices.empty()) {
        throw std::runtime_error("Memory pool exhausted");
    }
    size_t index = freeIndices.top();
    freeIndices.pop();
    orderPool[index] = {id, price, quantity, isBuy};
    orderLevels[price][id] = &orderPool[index];
    orderLookup[id] = &orderPool[index];
}

void OptimizedOrderBook::modifyOrder(const std::string &id, double newPrice, int newQuantity) {
    if (orderLookup.find(id) != orderLookup.end()) {
        Order* oldOrder_ptr = orderLookup[id];
        orderLevels[oldOrder_ptr->price].erase(id);
        addOrder(id, newPrice, newQuantity, oldOrder_ptr->isBuy);
    }
}

void OptimizedOrderBook::deleteOrder(const std::string &id) {
    if (orderLookup.find(id) != orderLookup.end()) {
        Order* order_ptr = orderLookup[id];
        orderLevels[order_ptr->price].erase(id);
        orderLookup.erase(id);
        size_t index = order_ptr - &orderPool[0];
        freeIndices.push(index);
    }
}

Order *OptimizedOrderBook::getOrder(const std::string &id) {
    if (orderLookup.find(id) != orderLookup.end()) {
        return orderLookup[id];
    }
    return nullptr;
}

void OptimizedOrderBook::reset() {
    orderLevels.clear();
    orderLookup.clear();
    freeIndices = std::stack<size_t>();
    for (size_t i = 0; i < orderPool.size(); ++i) {
        freeIndices.push(i);
    }
}
