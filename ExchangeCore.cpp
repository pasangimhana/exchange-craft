//
// Created by phaser on 02/01/24.
//

#include "ExchangeCore.h"
#include "OrderTypeConverter.h"

void ExchangeCore::parseCSV(std::string file) {
    std::vector<Order> orders = csvProcessor.processCSV(file);
    for (auto &order : orders)
    {
        if (order.orderType == OrderType::buy)
        {
            buyOrders.push_back(order);
        }
        else if (order.orderType == OrderType::sell)
        {
            sellOrders.push_back(order);
        }
    }
    reOrder();
}

bool ExchangeCore::buyOrderComparator(const Order &first, const Order &second)
{
    if (first.price == second.price)
    {
        if (first.timestamp == second.timestamp)
        {
            return first.amount < second.amount;
        }
        return first.timestamp.compare(second.timestamp) < 0; // Compare timestamps using the compare function
    }
    return first.price > second.price;
}

bool ExchangeCore::sellOrderComparator(const Order &first, const Order &second)
{
    if (first.price == second.price)
    {
        if (first.timestamp == second.timestamp)
        {
            return first.amount < second.amount;
        }
        return first.timestamp.compare(second.timestamp) < 0; // Compare timestamps using the compare function
    }
    return first.price < second.price;
}

void ExchangeCore::fillOrder(Order &buyOrder, Order &sellOrder)
{
    Order filledOrder = buyOrder;
    filledOrder.orderType = OrderType::sold;

    if (buyOrder.amount > sellOrder.amount)
    {
        filledOrder.amount = sellOrder.amount;
        buyOrder.amount = buyOrder.amount - sellOrder.amount;
        sellOrder.amount = 0;
    }
    else if (buyOrder.amount < sellOrder.amount)
    {
        filledOrder.amount = buyOrder.amount;
        sellOrder.amount = sellOrder.amount - buyOrder.amount;
        buyOrder.amount = 0;
    }
    else
    {
        filledOrder.amount = buyOrder.amount;
        buyOrder.amount = 0;
        sellOrder.amount = 0;
    }

    filledBook.push_back(filledOrder);
}

void ExchangeCore::printOrderBooks()
{
    std::cout << "Orderbook for " << product << std::endl;
    std::cout << "Buy" << std::endl;
    for (auto &order : buyOrders)
    {
        std::cout << "Price: " << order.price << " Amount: " << order.amount << " Timestamp: " << order.timestamp << " Product: " << order.product << " OrderType: " << orderTypeToString(order.orderType) << std::endl;
    }
    std::cout << "Sell" << std::endl;
    for (auto &order : sellOrders)
    {
        std::cout << "Price: " << order.price << " Amount: " << order.amount << " Timestamp: " << order.timestamp << " Product: " << order.product << " OrderType: " << orderTypeToString(order.orderType) << std::endl;
    }
}

void ExchangeCore::printOrderBookSize()
{
    std::cout << "Buybook size: " << buyOrders.size() << std::endl;
    std::cout << "Sellbook size: " << sellOrders.size() << std::endl;
}

// Print the filledbook.
void ExchangeCore::printFilledBook()
{
    for (auto &order : filledBook)
    {
        std::cout << "Price: " << order.price << " Amount: " << order.amount << " Timestamp: " << order.timestamp << " Product: " << order.product << " OrderType: " << orderTypeToString(order.orderType) << std::endl;
    }
}


void ExchangeCore::printFilledBookSize()
{
    std::cout << "Filledbook size: " << filledBook.size() << std::endl;
}

// Cleanup function to remove the orders with amount 0 from the buyorder,sellorder orderbooks
void ExchangeCore::cleanUp()
{
    buyOrders.erase(std::remove_if(buyOrders.begin(), buyOrders.end(), [](const Order &order)
                    { return order.amount == 0; }),
                    buyOrders.end());
    sellOrders.erase(std::remove_if(sellOrders.begin(), sellOrders.end(), [](const Order &order)
                     { return order.amount == 0; }),
                     sellOrders.end());
    filledBook.erase(std::remove_if(filledBook.begin(), filledBook.end(), [](const Order &order)
                     { return order.amount == 0; }),
                     filledBook.end());
}

void ExchangeCore::reOrder()
{
    std::sort(buyOrders.begin(), buyOrders.end(), buyOrderComparator);
    std::sort(sellOrders.begin(), sellOrders.end(), sellOrderComparator);
}

void ExchangeCore::matchOrders()
{
    for (auto &buyOrder : buyOrders)
    {
        for (auto &sellOrder : sellOrders)
        {
            if (std::abs(buyOrder.price - sellOrder.price) < epsilon)
            {
                fillOrder(buyOrder, sellOrder);
            }
        }
    }
    cleanUp();
    reOrder();
}

