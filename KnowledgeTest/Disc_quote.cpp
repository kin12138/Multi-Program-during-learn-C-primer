//
// Created by libin on 2025/4/29.
//

#include "Disc_quote.h"
#include <iostream>

Disc_quote::Disc_quote(const Disc_quote &rhs) :
            Quote(rhs), quantity(rhs.quantity), discount(rhs.discount) { }

Disc_quote::Disc_quote(Disc_quote &&rhs) noexcept :
         Quote(std::move(rhs)), quantity(std::move(rhs.quantity)), discount(std::move(rhs.discount)) { }

Disc_quote & Disc_quote::operator=(const Disc_quote &rhs) {
    if (this != &rhs) {
        Quote::operator=(rhs);
        quantity = rhs.quantity;
        discount = rhs.discount;
    }
    return *this;
}

Disc_quote & Disc_quote::operator=(Disc_quote &&rhs) noexcept {
    if (this != &rhs) {
        Quote::operator=(std::move(rhs));
        quantity = std::move(rhs.quantity);
        discount = std::move(rhs.discount);
    }
    return *this;
}

Disc_quote::~Disc_quote() = default;

void Disc_quote::debug() const {
    Quote::debug();
    std::cout << "Disc_quote class: "
              << "quantity: " << quantity
              << ", discount: " << discount << std::endl;
}