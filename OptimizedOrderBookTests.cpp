//
// Created by tomhi on 5/10/2025.
//

#include <cassert>
#include <chrono>
#include <iostream>
#include <random>

#include "OptimizedOrderBook.hpp"
#include "OptimizedOrderBookTests.hpp"

using std::cout;
using std::endl;

void testAddOrder(OptimizedOrderBook &ob) {
    cout << "Testing addOrder" << endl;
    cout << "================" << endl;
    ob.addOrder("ORD001", 50.10, 100, true);
    Order *order = ob.getOrder("ORD001");
    assert(order->price == 50.10);
    assert(order->quantity == 100);
    assert(order->isBuy == true);
    cout << "Order added successfully: " << order->id << endl << endl;
}

void testModifyOrder(OptimizedOrderBook &ob) {
    cout << "Testing modifyOrder" << endl;
    cout << "===================" << endl;
    ob.addOrder("ORD001", 50.10, 100, true);
    ob.modifyOrder("ORD001", 55.20, 150);
    Order *order = ob.getOrder("ORD001");
    assert(order->price == 55.20);
    assert(order->quantity == 150);
    assert(order->isBuy == true);
    cout << "Order modified successfully: " << order->id << endl << endl;
}

void testDeleteOrder(OptimizedOrderBook &ob) {
    cout << "Testing deleteOrder" << endl;
    cout << "===================" << endl;

    ob.addOrder("ORD001", 50.10, 100, true);
    assert(ob.getOrder("ORD001") != nullptr);
    ob.deleteOrder("ORD001");
    assert(ob.getOrder("ORD001") == nullptr);
    cout << "Order deleted successfully!" << endl << endl;
}

void stressTestOrderBook(OptimizedOrderBook &ob, int numOrders) {
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> priceDist(50.0, 100.0);
    std::uniform_int_distribution<int> quantityDist(1, 500);

    cout << "Stress Test OptimizedOrderBook" << endl;
    cout << "=====================" << endl;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numOrders; ++i) {
        ob.addOrder("ORD" + std::to_string(i), priceDist(rng), quantityDist(rng), i % 2 == 0);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    cout << "addOrder (N = " << numOrders << ") execution time: " << duration << " ms" << endl;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numOrders; ++i) {
        ob.modifyOrder("ORD" + std::to_string(i), priceDist(rng), quantityDist(rng));
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    cout << "modifyOrder (N = " << numOrders << ") execution time: " << duration << " ms" << endl;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numOrders; ++i) {
        ob.deleteOrder("ORD" + std::to_string(i));
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    cout << "deleteOrder (N = " << numOrders << ") execution time: " << duration << " ms" << endl;
}
