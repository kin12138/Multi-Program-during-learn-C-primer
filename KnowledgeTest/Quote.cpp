//
// Created by libin on 2025/4/28.
//

#include "Quote.h"
#include "iostream"

Quote::Quote() : bookNo(), price(0.0){ }
Quote::Quote(const Quote& rhs) {
    bookNo = rhs.bookNo;
    price = rhs.price;
}

Quote::Quote(Quote && rhs) noexcept{
    bookNo = std::move(rhs.bookNo);
    price = std::move(rhs.price);
}
Quote & Quote::operator=(const Quote& rhs){
    if (this != &rhs) {
        bookNo = rhs.bookNo;
        price = rhs.price;
    }
    return *this;
}

Quote & Quote::operator=(Quote&& rhs) noexcept{
    if (this != &rhs) {
        bookNo = std::move(rhs.bookNo);
        price = std::move(rhs.price);
    }
    return *this;
}

Quote::~Quote() = default;

void Quote::debug() const {
    std::cout << "Quote class: "
              << "bookNo: " << bookNo
              << ", price: " << price << std::endl;
}