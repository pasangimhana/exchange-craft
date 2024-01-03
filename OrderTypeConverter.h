//
// Created by phaser on 03/01/24.
//

#ifndef EXCHANGE_CRAFT_ORDERTYPECONVERTER_H
#define EXCHANGE_CRAFT_ORDERTYPECONVERTER_H

#include <string>
#include "Order.h"

OrderType stringToOrdertype(std::string s);
std::string orderTypeToString(OrderType orderType);


#endif //EXCHANGE_CRAFT_ORDERTYPECONVERTER_H
