//
// Created by libin on 2025/4/28.
//

#ifndef KNOWLEDGETEST_BULK_QUOTE_H
#define KNOWLEDGETEST_BULK_QUOTE_H

#include "Disc_quote.h"

class Bulk_quote : public Disc_quote{        // Bulk_quote 继承自 Quote
public:
    Bulk_quote();
    Bulk_quote(const Bulk_quote & rhs);
    Bulk_quote(Bulk_quote && rhs) noexcept;
    Bulk_quote & operator=(const Bulk_quote & rhs);
    Bulk_quote & operator=(Bulk_quote && rhs) noexcept;
    ~Bulk_quote() override;

//    Bulk_quote(const std::string &, double , std::size_t , double );
    // 覆盖基类的函数版本以实现基于大量购买的折扣政策
    using Disc_quote::Disc_quote;
    double net_price(std::size_t cnt) const override;

    Bulk_quote * clone() const & override { return new Bulk_quote(*this); }
    Bulk_quote * clone() const && override { return new Bulk_quote(std::move(*this)); }
};


#endif //KNOWLEDGETEST_BULK_QUOTE_H
