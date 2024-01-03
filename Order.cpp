// order.cpp
#include "Order.h"

long long int Order::orderIdCounter = 0;

Order::Order(double _price, double _amount, std::string _timestamp, std::string _product, OrderType _orderType)
        : orderId(Order::orderIdCounter++),
          price(_price),
          amount(_amount),
          timestamp(_timestamp),
          product(_product),
          orderType(_orderType)
{ }
