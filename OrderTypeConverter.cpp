//
// Created by phaser on 03/01/24.
//

#include "OrderTypeConverter.h"

OrderType stringToOrdertype(std::string s)
{
    if (s == "buy")
    {
        return OrderType::buy;
    }
    else if (s == "sell")
    {
        return OrderType::sell;
    }
    else if (s == "sold")
    {
        return OrderType::sold;
    }
    else
    {
        throw std::exception{};
    }
}

std::string orderTypeToString(OrderType orderType)
{
    if (orderType == OrderType::buy)
    {
        return "buy";
    }
    else if (orderType == OrderType::sell)
    {
        return "sell";
    }
    else if (orderType == OrderType::sold)
    {
        return "sold";
    }
    else
    {
        throw std::exception{};
    }
}