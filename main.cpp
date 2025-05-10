#include <iostream>

#include "OrderBook.hpp"
#include "OrderBookTests.hpp"
#include "OptimizedOrderBook.hpp"
#include "OptimizedOrderBookTests.hpp"

using std::cout;
using std::endl;

int main() {
    cout << "Running OrderBook Tests" << endl;
    OrderBook ob;

    testAddOrder(ob);
    ob.reset();

    testModifyOrder(ob);
    ob.reset();

    testDeleteOrder(ob);
    ob.reset();

    // stressTestOrderBook(ob, 1000000);
    incrementalStressTestOrderBook(ob);
    cout << "-------------------------" << endl;

    cout << "Running OptimizedOrderBook Tests" << endl;
    OptimizedOrderBook optob(2000000);

    testAddOrder(optob);
    optob.reset();

    testModifyOrder(optob);
    optob.reset();

    testDeleteOrder(optob);
    optob.reset();

    // stressTestOrderBook(optob, 1000000);
    incrementalStressTestOrderBook();
}
