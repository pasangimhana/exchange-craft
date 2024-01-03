//
// Created by phaser on 02/01/24.
//

#ifndef EXCHANGE_CRAFT_CSVPROCESSOR_H
#define EXCHANGE_CRAFT_CSVPROCESSOR_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "Order.h"

class CSVProcessor {
    // Function Declarations
public:
    CSVProcessor();

    std::vector<Order> processCSV(const std::string& fileName);

    std::vector<std::string> tokenize(std::string csvLine, char separator);

    static Order stringstoOBE(std::vector<std::string> tokens);

    // Variable Declarations
private:
    std::vector<Order> entries;
};


#endif //EXCHANGE_CRAFT_CSVPROCESSOR_H
