//
// Created by phaser on 10/01/24.
//

#ifndef EXCHANGE_CRAFT_CLIFRONTEND_H
#define EXCHANGE_CRAFT_CLIFRONTEND_H


class CLIFrontEnd {

public:
    CLIFrontEnd();
    void startFE();

private:
    void loadingAnimation();
    void printMenu();
    void insertOrder();
    void deleteOrder();
    void printPrice();
    void printBook();
};


#endif //EXCHANGE_CRAFT_CLIFRONTEND_H
