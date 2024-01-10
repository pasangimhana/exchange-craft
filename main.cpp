#include <iostream>
#include <chrono>
#include <filesystem>
#include <stdlib.h>

#include "ExchangeCore.h"

int main(int argc, char **argv)
{
    auto start = std::chrono::high_resolution_clock::now();


    ExchangeCore exchangeCore;
    exchangeCore.parseCSV("/home/phaser/personal-projects/exchange-craft/data.csv");
    exchangeCore.matchOrders();
    exchangeCore.printOrderBooks();
    exchangeCore.printOrderBookSize();
    exchangeCore.cleanUp();
    exchangeCore.printFilledBookSize();

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;

    std::cout << "Elapsed time: " << elapsed.count() << " s\n";
}
