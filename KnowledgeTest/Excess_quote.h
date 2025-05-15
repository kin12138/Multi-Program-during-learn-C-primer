//
// Created by libin on 2025/4/28.
//

#ifndef KNOWLEDGETEST_EXCESS_QUOTE_H
#define KNOWLEDGETEST_EXCESS_QUOTE_H
#include "Disc_quote.h"

class Excess_quote : public Disc_quote{
    Excess_quote() = default;
    Excess_quote(const std::string &book, double p, std::size_t qty, double disc);

    // 覆盖虚函数
    double net_price(std::size_t cnt) const override;
};


#endif //KNOWLEDGETEST_EXCESS_QUOTE_H
