//
// Created by libin on 2025/5/10.
//

#include "OrQuery.h"

QueryResult OrQuery::eval(const TextQuery & text) const {
    std::cout << "OrQuery::eval" << std::endl;
    // 通过 Query 成员 lhs 和 rhs 进行的虚调用
    // 调用 eval 返回每个运算对象的 QueryResult
    auto right = rhs.eval(text), left = lhs.eval(text);
    // 将左侧运算对象的行号 set 拷贝到结果 set 中
    auto ret_lines = std::make_shared<std::set<line_no>>(left.begin(), left.end());
    // 插入右侧运算对象所得的行号
    ret_lines->insert(right.begin(), right.end());
    // 返回一个新的 QueryResult，表示 lhs 和 rhs 的并集
    return QueryResult{rep(), ret_lines, left.get_file()};
}