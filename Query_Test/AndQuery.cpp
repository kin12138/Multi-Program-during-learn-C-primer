//
// Created by libin on 2025/5/10.
//

#include "AndQuery.h"
#include <algorithm>

QueryResult AndQuery::eval(const TextQuery & text) const {
    std::cout << "AndQuery::eval" << std::endl;
    // 通过 Query 运算对象进行的虚调用，以获得运算对象的查询结果 set
    auto right = rhs.eval(text), left = lhs.eval(text);
    // 创建保存 left 与 right 交集的 set
    auto ret_lines = std::make_shared<std::set<line_no>>();
    // 将两个范围的交集写入一个目的迭代器中
    // 本次调用的目的迭代器向 ret_lines 中添加元素
    std::set_intersection(left.begin(), left.end(),
                          right.begin(), right.end(),
                          std::inserter(*ret_lines, ret_lines->begin()));
    // 返回一个新的 QueryResult 对象，表示两个运算对象的交集
    return QueryResult{rep(), ret_lines, left.get_file()};
}