//
// Created by libin on 2025/5/10.
//

#include "NotQuery.h"


QueryResult NotQuery::eval(const TextQuery &text) const {
    // 通过 Query 对象对 eval 进行虚调用
    auto result = query.eval(text);
    // 创建一个空 set 用来保存没有出现运算对象的行号
    auto ret_lines = std::make_shared<std::set<line_no>>();
    // 必须在运算对象出现的所有行进行迭代
    auto beg = result.begin(), end = result.end();
    // 对于输入文件的每一行，如果该行不在 result 中，则将其添加到 ret_lines 中
    auto sz = result.get_file()->size();
    for (size_t n = 0; n != sz; ++n) {
        // 如果还没有处理完 result 的所有行
        // 检查当前行是否在 result 中
        if (beg == end || *beg != n )
            ret_lines->insert(n);   // 如果不在 result 中，添加这一行
        else if (beg != end)
            ++beg;                  // 否则继续获取 result 的下一个行号
    }
    return QueryResult{rep(), ret_lines, result.get_file()};
}