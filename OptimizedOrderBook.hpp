#pragma once

#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

#include "Order.hpp"

class OptimizedOrderBook {
public:
    OptimizedOrderBook() = delete;

    explicit OptimizedOrderBook(size_t maxOrders);

    void addOrder(const std::string &id, double price, int quantity, bool isBuy);

    void modifyOrder(const std::string &id, double newPrice, int newQuantity);

    void deleteOrder(const std::string &id);

    Order *getOrder(const std::string &id);

    void reset();

private:
    std::vector<Order> orderPool;
    std::stack<size_t> freeIndices;
    std::map<double, std::unordered_map<std::string, Order *>> orderLevels;
    std::unordered_map<std::string, Order *> orderLookup;
};
