//
// Created by phaser on 02/01/24.
//

#include "CSVProcessor.h"
#include "OrderTypeConverter.h"


CSVProcessor::CSVProcessor()
    {
        std::cout << "CSVProcessor created" << std::endl;
    }

    std::vector<Order> CSVProcessor::processCSV(const std::string& fileName)
    {

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

    std::vector<std::string> CSVProcessor::tokenize(std::string csvLine, char separator)
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

    Order CSVProcessor::stringstoOBE(std::vector<std::string> tokens)
    {
        double price, amount;
        if (tokens.size() != 5) //
        {
            std::cout << "Error in Line" << std::endl;
            throw std::exception{};
        }

        try
        {
            price = std::stod(tokens[3]);
            amount = std::stod(tokens[4]);
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
        return obe;
    }
