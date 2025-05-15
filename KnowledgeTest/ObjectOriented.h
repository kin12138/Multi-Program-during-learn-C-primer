//
// Created by libin on 2025/4/28.
//

#ifndef KNOWLEDGETEST_OBJECTORIENTED_H
#define KNOWLEDGETEST_OBJECTORIENTED_H

#include "Bulk_quote.h"
#include <iostream>
#include <vector>
#include <memory>
#include "Basket.h"


/*-----------15.3*/
// 计算并打印销售给定数量的书籍所得的总费用
/*double print_total(std::ostream &os, const Quote & item, std::size_t n ) {
    // 根据传入 item 形参的对象类型选择调用 Quote::net_price 或者 Bulk_quote::net_price
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn()
       << " # sold: " << n << " total due: " << ret << std::endl;
    return ret;
}*/


/*void _15_6() {
    Quote qItem;
    Bulk_quote bItem;
    auto result = print_total(std::cout, qItem, 3);
    auto result2 = print_total(std::cout, bItem, 4);
}*/

void _15_17() {
//    Disc_quote item;
}

class Base{
public:
    void pub_mem();
protected:
    int prot_mem();
private:
    char priv_mem();
};

struct Pub_Derv : public Base {
    void memfcn(Base & b) { b = *this; }
};

struct Priv_Derv : private Base {
    void memfcn(Base & b) { b = *this; }
};

struct Prot_Derb : protected Base {
    void memfcn(Base & b) { b = *this; }
};

struct Derived_from_public : public Pub_Derv{
    void memfcn(Base & b) { b = *this; }
};

struct Derived_from_protected : public Prot_Derb {
    void memfcn(Base & b) { b = *this; }
};

struct Derived_from_private : public Priv_Derv {
//    void memfcn(Base & b) { b = *this; }
};

/*------------15.26--------------*/
void _15_26() {
    Quote obj1; Bulk_quote obj2;
    Quote *bp1, *bp2, *bp3;
    bp1 = &obj1;
    bp2 = &obj2;
    Quote obj3 = *bp2;
    Bulk_quote obj5(obj2);
    Bulk_quote obj4 ;
    obj4 = std::move(obj2);
}

void _15_28() {
    std::vector<Quote> basket;
    for (unsigned i = 1; i != 10; ++i) {
        basket.push_back(Bulk_quote("sss", i * 10.1, 10, 0.3));
    }
    double total = 0;
    for (const auto & item : basket)
        total += item.net_price(20);
    std::cout << "total: " << total << std::endl;
}

void _15_29() {
    std::vector<std::shared_ptr<Quote>> basket;
    for (unsigned i = 1; i != 10; ++i) {
        basket.push_back(std::make_shared<Bulk_quote>(Bulk_quote("sss", i * 10.1, 10, 0.3)));
    }
    double total = 0;
    for (const auto & item : basket)
        total += item->net_price(20);
    std::cout << "total: " << total << std::endl;
}

void _15_30() {
    Basket basket;

    for (unsigned i = 0; i != 10; ++i)
        basket.add_item(Bulk_quote("Bible", 20.6, 20, 0.3));

    for (unsigned i = 0; i != 10; ++i)
        basket.add_item(Bulk_quote("C++Primer", 30.9, 5, 0.4));

    for (unsigned i = 0; i != 10; ++i)
        basket.add_item(Quote("CLRS", 40.1));

    std::ofstream log("../Resource/Basket_log.txt", std::ios_base::app | std::ios_base::out);

    basket.total_receipt(log);
}

#endif //KNOWLEDGETEST_OBJECTORIENTED_H
