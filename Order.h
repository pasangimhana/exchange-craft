//
// Created by phaser on 03/01/24.
//

#ifndef EXCHANGE_CRAFT_ORDER_H
#define EXCHANGE_CRAFT_ORDER_H

#include <string>

enum class OrderType {
    buy,
    sell,
    sold
};


struct Order {
    int orderId;
    double price;
    double amount;
    std::string timestamp;
    std::string product;
    OrderType orderType;

    Order(double _price, double _amount, std::string _timestamp, std::string _product, OrderType _orderType);

    static long long int orderIdCounter;
};

#endif //EXCHANGE_CRAFT_ORDER_H
