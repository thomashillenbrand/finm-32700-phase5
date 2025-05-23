#pragma once

#include <map>
#include <unordered_map>
#include <string>

#include "Order.hpp"

class OrderBook {
public:
    void addOrder(const std::string &id, double price, int quantity, bool isBuy);

    void modifyOrder(const std::string &id, double newPrice, int newQuantity);

    void deleteOrder(const std::string &id);

    Order *getOrder(const std::string &id);

    void reset();

private:
    std::map<double, std::unordered_map<std::string, Order> > orderLevels;
    std::unordered_map<std::string, Order> orderLookup;
};
