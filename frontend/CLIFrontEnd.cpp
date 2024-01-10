//
// Created by phaser on 10/01/24.
//

#include "CLIFrontEnd.h"
#include <iostream>
#include <chrono>
#include <thread>

CLIFrontEnd::CLIFrontEnd() {
    startFE();
}

void CLIFrontEnd::startFE() {
    std::cout << "Welcome to the ExchangeCraft CLI!" << std::endl << std::endl;
    // print some C++ animation to show a loading screen
    loadingAnimation();
    loadingAnimation();
    loadingAnimation();

    printMenu();
}

void loadingAnimation() {
    std::cout << "Loading";
    for (int i = 0; i < 10; i++) {
        std::cout << ".";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    std::cout << "\r                                      \r";
}

void CLIFrontEnd::printMenu() {
    std::cout << "Please select an option:" << std::endl;
    std::cout << "1. Insert an order" << std::endl;
    std::cout << "2. Delete an order" << std::endl;
    std::cout << "3. Print the best price" << std::endl;
    std::cout << "4. Print the order book" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "Enter your choice: ";
    int choice;
    std::cin >> choice;
    switch (choice) {
        case 1:
            insertOrder();
            break;
        case 2:
            deleteOrder();
            break;
        case 3:
            printPrice();
            break;
        case 4:
            printBook();
            break;
        case 5:
            std::cout << "Exiting..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            printMenu();
    }
}

void CLIFrontEnd::insertOrder() {
    std::cout << "Inserting an order..." << std::endl;
    printMenu();
}

void CLIFrontEnd::deleteOrder() {
    std::cout << "Deleting an order..." << std::endl;
    printMenu();
}

void CLIFrontEnd::printPrice() {
    std::cout << "Printing the best price..." << std::endl;
    printMenu();
}

void CLIFrontEnd::printBook() {
    std::cout << "Printing the order book..." << std::endl;
    printMenu();
}

