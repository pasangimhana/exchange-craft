//
// Created by phaser on 02/01/24.
//

#ifndef EXCHANGE_CRAFT_EXCHANGECORE_H
#define EXCHANGE_CRAFT_EXCHANGECORE_H

#include "CSVProcessor.h"
#include "Order.h"
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>



class ExchangeCore {
public:

    void parseCSV(std::string file);
    static bool buyOrderComparator(const Order &first, const Order &second);
    static bool sellOrderComparator(const Order &first, const Order &second);
    void fillOrder(Order &buyOrder, Order &sellOrder);
    void printOrderBooks();
    void printOrderBookSize();
    void printFilledBook();
    void printFilledBookSize();
    void cleanUp();
    void reOrder();
    void matchOrders();

private:
    CSVProcessor csvProcessor;
    std::string product;
    std::vector<Order> buyOrders;
    std::vector<Order> sellOrders;
    std::vector<Order> filledBook;
    const double epsilon = 1e-8;
};


#endif //EXCHANGE_CRAFT_EXCHANGECORE_H
