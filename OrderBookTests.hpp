//
// Created by tomhi on 5/10/2025.
//

#pragma once

void testAddOrder(OrderBook &ob);

void testModifyOrder(OrderBook &ob);

void testDeleteOrder(OrderBook &ob);

void stressTestOrderBook(OrderBook &ob, int numOrders);

void incrementalStressTestOrderBook(OrderBook &ob);

