//
// Created by libin on 2025/4/28.
//

#include "Excess_quote.h"
#include <iostream>

Excess_quote::Excess_quote(const std::string &book, double p, std::size_t qty, double disc) :
                    Disc_quote(book, p, qty, disc) { }

double Excess_quote::net_price(std::size_t cnt) const {
    if (cnt <= quantity)
        return cnt * (1 - discount) * price;
    else {
        double result = quantity * (1 - discount) * price + (cnt - quantity) + price; // 未超出部分有折扣，超出部分按原价
        return result;
    }
}