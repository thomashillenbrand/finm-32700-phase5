#include <cassert>
#include <chrono>
#include <iostream>
#include <random>
#include "OrderBook.hpp"

void testAddOrder(OrderBook &ob) {
    ob.addOrder("ORD001", 50.10, 100, true);
    Order *order = ob.getOrder("ORD001");
    assert(order->price == 50.10);
    assert(order->quantity == 100);
    assert(order->isBuy == true);
}

void testModifyOrder(OrderBook &ob) {
    ob.addOrder("ORD001", 50.10, 100, true);
    ob.modifyOrder("ORD001", 55.20, 150);
    Order *order = ob.getOrder("ORD001");
    assert(order->price == 55.20);
    assert(order->quantity == 150);
    assert(order->isBuy == true);
}

void testDeleteOrder(OrderBook &ob) {
    ob.addOrder("ORD001", 50.10, 100, true);
    assert(ob.getOrder("ORD001") != nullptr);
    ob.deleteOrder("ORD001");
    assert(ob.getOrder("ORD001") == nullptr);
}

void stressTestOrderBook(OrderBook &ob, int numOrders) {
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> priceDist(50.0, 100.0);
    std::uniform_int_distribution<int> quantityDist(1, 500);

    std::cout << "Stress Test OrderBook" << std::endl;
    std::cout << "=====================" << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numOrders; ++i) {
        ob.addOrder("ORD" + std::to_string(i), priceDist(rng), quantityDist(rng), i % 2 == 0);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "addOrder (N = " << numOrders << ") execution time: " << duration << " ms" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numOrders; ++i) {
        ob.modifyOrder("ORD" + std::to_string(i), priceDist(rng), quantityDist(rng));
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "modifyOrder (N = " << numOrders << ") execution time: " << duration << " ms" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numOrders; ++i) {
        ob.deleteOrder("ORD" + std::to_string(i));
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "deleteOrder (N = " << numOrders << ") execution time: " << duration << " ms" << std::endl;
}

int main() {
    OrderBook ob;
    testAddOrder(ob);
    ob.reset();

    testModifyOrder(ob);
    ob.reset();

    testDeleteOrder(ob);
    ob.reset();

    stressTestOrderBook(ob, 1000000); // Stress test with 1 million orders
}
