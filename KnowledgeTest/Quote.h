//
// Created by libin on 2025/4/28.
//

#ifndef KNOWLEDGETEST_QUOTE_H
#define KNOWLEDGETEST_QUOTE_H

#include <string>

class Quote {
public:
    Quote();
    Quote(const Quote& rhs);
    Quote(Quote &&) noexcept;
    Quote & operator=(const Quote&);
    Quote & operator=(Quote&&) noexcept;
    virtual ~Quote();     // 对析构函数进行动态绑定

    std::string isbn() const { return bookNo; }
    Quote(const std::string & book, double sale_price) :
            bookNo(book), price(sale_price) { }

    // 返回给定数量的书籍的销售总额
    // 派生类负责改写并使用不同的折扣计算算法
    virtual double net_price(std::size_t n) const {
        return n * price;
    }
    virtual void debug() const ;

    virtual Quote * clone() const & { return new Quote(*this); }
    virtual Quote * clone() const && { return new Quote(std::move(*this)); }

private:
    std::string bookNo;         // 书籍的 ISBN 编号
protected:
    double price = 0.0;         // 代表普通状态下不打折的价格
};


#endif //KNOWLEDGETEST_QUOTE_H
