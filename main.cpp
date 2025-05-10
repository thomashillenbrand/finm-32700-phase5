
#include "OrderBook.hpp"
#include "OrderBookTests.hpp"


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
