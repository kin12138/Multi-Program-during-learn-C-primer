//
// Created by libin on 2025/5/10.
//

#include "Basket.h"
#include <iostream>

// 计算并打印销售给定数量的书籍所得的总费用
double print_total(std::ostream &os, const Quote & item, std::size_t n ) {
    // 根据传入 item 形参的对象类型选择调用 Quote::net_price 或者 Bulk_quote::net_price
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn()
       << " # sold: " << n << " total due: " << ret << std::endl;
    return ret;
}

double Basket::total_receipt(std::ostream &os) const {
    double sum = 0;     // 保存实时计算的总价
    // iter 指向 ISBN 相同的同一批元素中的第一个
    // upper_bound 返回一个迭代器，该迭代器指向这批元素的尾后位置
    for (auto iter = items.cbegin();
        iter != items.cend();
        iter = items.upper_bound(*iter)) {
        // 打印该书籍对应的项目
        sum += print_total(os, **iter, items.count(*iter));
    }
    os << "Total Sale: " << sum << std::endl;
    return sum;
}