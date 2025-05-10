#pragma once

#include <string>

struct Order {
    std::string id; // String-based order ID
    double price;
    int quantity;
    bool isBuy;
};
