//
// Created by libin on 2025/5/10.
//

#ifndef KNOWLEDGETEST_BASKET_H
#define KNOWLEDGETEST_BASKET_H
#include <memory>
#include <set>
#include "Quote.h"

class Basket {
public:
    // Basket 使用合成默认构造函数和拷贝控制成员
    void add_item(const Quote & sale)
        { items.insert(std::shared_ptr<Quote>(sale.clone())); }
    void add_item(Quote && sale) {
        items.insert(std::shared_ptr<Quote> (std::move(sale).clone()));
    }
    // 打印每本书的总价，和购物篮中所有书的总价
    double total_receipt(std::ostream &) const;
private:
    // 该函数用于比较 shared_ptr，multiset 成员会用到它
    static bool compare(const std::shared_ptr<Quote> & lhs,
                        const std::shared_ptr<Quote> & rhs)
    { return lhs->isbn() < rhs->isbn(); }
private:
    using cmp = decltype(compare)*;
    // multiset 保存多个报价，按 compare 成员排序
    std::multiset<std::shared_ptr<Quote>, cmp> items{compare};
};

#endif //KNOWLEDGETEST_BASKET_H
