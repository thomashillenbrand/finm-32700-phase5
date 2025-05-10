//
// Created by tomhi on 5/10/2025.
//

#pragma once

void testAddOrder(OptimizedOrderBook &ob);

void testModifyOrder(OptimizedOrderBook &ob);

void testDeleteOrder(OptimizedOrderBook &ob);

void stressTestOrderBook(OptimizedOrderBook &ob, int numOrders);

void incrementalStressTestOrderBook();
