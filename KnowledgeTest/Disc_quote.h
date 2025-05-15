//
// Created by libin on 2025/4/29.
//

#ifndef KNOWLEDGETEST_DISC_QUOTE_H
#define KNOWLEDGETEST_DISC_QUOTE_H
#include "Quote.h"
#include <string>
#include <iostream>

class Disc_quote : public Quote{
public:
    Disc_quote() : Quote() { }
    Disc_quote(const std::string & book, double price, std::size_t qty, double disc) :
            Quote(book, price), quantity(qty), discount(disc) { }

    Disc_quote(const Disc_quote& rhs);
    Disc_quote(Disc_quote && rhs) noexcept;
    Disc_quote & operator=(const Disc_quote& rhs);
    Disc_quote & operator=(Disc_quote && rhs) noexcept;
    ~Disc_quote() override;

    double net_price(std::size_t ) const override = 0;
    void debug() const override;

protected:
    std::size_t quantity = 0;   // 折扣适用的购买量
    double discount = 0.0;      // 表示折扣的小数值
};


#endif //KNOWLEDGETEST_DISC_QUOTE_H
