//
// Created by libin on 2025/4/28.
//

#include "Bulk_quote.h"
#include <iostream>

Bulk_quote::Bulk_quote() = default;

Bulk_quote::Bulk_quote(const Bulk_quote &rhs) = default;

Bulk_quote::Bulk_quote(Bulk_quote &&rhs) noexcept : Disc_quote(std::move(rhs)){
}

Bulk_quote & Bulk_quote::operator=(const Bulk_quote & rhs) {
    if (this != &rhs)
        Disc_quote::operator=(rhs);
    return *this;
}

Bulk_quote & Bulk_quote::operator=(Bulk_quote && rhs) noexcept {
    if (this != &rhs)
        Disc_quote::operator=(std::move(rhs));
    return *this;
}

Bulk_quote::~Bulk_quote() = default;

/*Bulk_quote::Bulk_quote(const std::string &book, double p, std::size_t qty, double disc) :
        Disc_quote(book, p, qty, disc) { }*/

// 如果达到购买书籍的某个最低限量值，就可以使用折扣
double Bulk_quote::net_price(std::size_t cnt) const {
    if (cnt >= quantity)
        return cnt * (1 - discount) * price;
    else
        return cnt * price;
}