#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>

enum class OrderType
{
    buy,
    sell,
    sold
};

const double epsilon = 1e-8;

struct Order
{
    int orderId; // Non-static member for a unique ID per instance
    double price;
    double amount;
    std::string timestamp;
    std::string product;
    OrderType orderType;

    Order(double _price, double _amount, std::string _timestamp, std::string _product, OrderType _orderType)
        : orderId(Order::orderIdCounter++), // Increment per instance
          price(_price),
          amount(_amount),
          timestamp(_timestamp),
          product(_product),
          orderType(_orderType)
    { }

private:
    static long long int orderIdCounter; // Static member to keep track of the next ID
};

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

std::string ordertypeToString(OrderType orderType)
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

class CSVProcessor
{
public:
    CSVProcessor()
    {
        std::cout << "CSVProcessor created" << std::endl;
    }

    std::vector<Order> processCSV(std::string fileName)
    {
        std::vector<Order> entries;

        std::ifstream csvFile{fileName};
        std::string line;

        if (csvFile.is_open())
        {

            while (std::getline(csvFile, line))
            {
                try
                {
                    Order obe = stringstoOBE(tokenize(line, ','));
                    entries.push_back(obe);
                }
                catch (const std::exception &e)
                {
                    std::cout << "Error in Line" << std::endl;
                    continue;
                }
            } // end of while
        }     // end of if

        std::cout << "CSVReader::readCSV() - read " << entries.size() << " entries." << std::endl;

        return entries;
    }

    std::vector<std::string> tokenize(std::string csvLine, char separator)
    {
        std::vector<std::string> tokens;
        signed int start, end;

        start = csvLine.find_first_not_of(separator, 0);

        do
        {
            end = csvLine.find(separator, start); // Find next separator after start

            if (start == csvLine.length() || start == end)
            {
                // Nothing more to find
                break;
            }

            std::string token;
            if (end >= 0)
            {
                token = csvLine.substr(start, end - start); // Get token between start and separator
            }
            else
            {
                token = csvLine.substr(start, csvLine.length() - start); // Get remaining string
            }

            tokens.push_back(token); // Add token to the end of the vector
            start = end + 1;         // Move past this token
        } while (end > 0);

        return tokens;
    }

    Order stringstoOBE(std::vector<std::string> tokens)
    {
        double price, amount;
        if (tokens.size() != 5) //
        {
            std::cout << "Error in Line" << std::endl;
            throw std::exception{};
        }

        try
        {
            // print the string first
            std::cout << "Price String" << tokens[3] << std::endl;
            price = std::stod(tokens[3]);
            std::cout << "Price double" << price << std::endl;

            std::cout << "Amount String" << tokens[4] << std::endl;
            amount = std::stod(tokens[4]);
            std::cout << "Amount double" << amount << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cout << "Bad float!";
            throw;
        }

        Order obe{
            price,
            amount,
            tokens[0],
            tokens[1],
            stringToOrdertype(tokens[2])};

        // print the obe
        std::cout << "OBE is created." << std::endl
                  << "Price: " << obe.price << " Amount: " << obe.amount << " Timestamp: " << obe.timestamp << " Product: " << obe.product << " OrderType: " << ordertypeToString(obe.orderType) << std::endl;

        return obe;
    }
    // Any useful functi
    // CSVParser that parses the csv file in the  and returns a vector of OrderBookEntry objects.
};

// ATS class for each product.
// This class will be acting as the central software that will be handling the orderbooks, filledbook vector that has tuple of matched orders,, matching engine, etc, There should be two orderbooks for each product, one for buys and one for sells.

class ATS
{
public:
    CSVProcessor csvProcessor;

    // Parse the csv file and add the orders to the relevant orderbooks.
    // @param file: csv file name
    void parseCSV(std::string file)
    {
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
        printOrderBooks();
    }

    // Buy order sorting comparator.
    static bool buycomparator(const Order &first, const Order &second)
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

    // Sell order sorting comparator.
    static bool sellcomparator(const Order &first, const Order &second)
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

    // Sort the two orderbooks for buy and sell order. Using the custom comparator.

    // Fill the fillbook with the ordertype converted to sale and only the amount that is sold. Other fields remain the same. Order wil
    void fillOrder(Order &order1, Order &order2)
    {
        Order filledOrder = order1;
        filledOrder.orderType = OrderType::sold;

        if (order1.amount > order2.amount)
        {
            filledOrder.amount = order2.amount;
            order1.amount = order1.amount - order2.amount;
            order2.amount = 0;
        }
        else if (order1.amount < order2.amount)
        {
            filledOrder.amount = order1.amount;
            order2.amount = order2.amount - order1.amount;
            order1.amount = 0;
        }
        else
        {
            filledOrder.amount = order1.amount;
            order1.amount = 0;
            order2.amount = 0;
        }

        filledBook.push_back(filledOrder);
    }

    void printOrderBooks()
    {
        std::cout << "Orderbook for " << product << std::endl;
        std::cout << "Buy" << std::endl;
        for (auto &order : buyOrders)
        {
            std::cout << "Price: " << order.price << " Amount: " << order.amount << " Timestamp: " << order.timestamp << " Product: " << order.product << " OrderType: " << ordertypeToString(order.orderType) << std::endl;
        }
        std::cout << "Sell" << std::endl;
        for (auto &order : sellOrders)
        {
            std::cout << "Price: " << order.price << " Amount: " << order.amount << " Timestamp: " << order.timestamp << " Product: " << order.product << " OrderType: " << ordertypeToString(order.orderType) << std::endl;
        }
    }

    // Print the filledbook.
    void printFilledBook()
    {
        for (auto &order : filledBook)
        {
            std::cout << "Price: " << order.price << " Amount: " << order.amount << " Timestamp: " << order.timestamp << " Product: " << order.product << " OrderType: " << ordertypeToString(order.orderType) << std::endl;
        }
    }

    // Cleanup function to remove the orders with amount 0 from the buyorder,sellorder orderbooks
    void cleanUp()
    {
        buyOrders.erase(std::remove_if(buyOrders.begin(), buyOrders.end(), [](const Order &order)
                                       { return order.amount == 0; }),
                        buyOrders.end());
        sellOrders.erase(std::remove_if(sellOrders.begin(), sellOrders.end(), [](const Order &order)
                                        { return order.amount == 0; }),
                         sellOrders.end());
    }

    void reOrder()
    {
        std::sort(buyOrders.begin(), buyOrders.end(), buycomparator);
        std::sort(sellOrders.begin(), sellOrders.end(), sellcomparator);
    }

    void matchOrders()
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

private:
    std::string product;
    std::vector<Order> buyOrders;
    std::vector<Order> sellOrders;
    std::vector<Order> filledBook;
};

long long int Order::orderIdCounter = 345660;
// create a simple main function to read a csv file and print the orderbook and filledbook.
int main(int argc, char **argv)
{

    ATS ats;
    ats.parseCSV("data.csv");
    ats.matchOrders();
    ats.printOrderBooks();

    std::cout << std::endl;
    std::cout << "Filledbook" << std::endl;
    ats.printFilledBook();
}
