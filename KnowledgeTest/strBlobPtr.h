//
// Created by libin on 2025/4/16.
//

#ifndef KNOWLEDGETEST_STRBLOBPTR_H
#define KNOWLEDGETEST_STRBLOBPTR_H

#include <memory>
#include <string>
#include <vector>

class strBlob;
class strBlobPtr {
    friend bool operator==(const strBlobPtr &, const strBlobPtr &);
    friend bool operator!=(const strBlobPtr &, const strBlobPtr &);
    friend std::size_t operator-(const strBlobPtr & lhs, const strBlobPtr & rhs);
    friend bool operator<(const strBlobPtr & lhs, const strBlobPtr & rhs);
    friend bool operator<=(const strBlobPtr & lhs, const strBlobPtr & rhs);
    friend bool operator>(const strBlobPtr & lhs, const strBlobPtr & rhs);
    friend bool operator>=(const strBlobPtr & lhs, const strBlobPtr & rhs);
public:
    strBlobPtr() : curr(0) {}
    strBlobPtr(const strBlob &a, size_t sz = 0);
    // deref 调用 check，检查使用 vector 是否安全以及 curr 是否在合法范围内
    std::string & deref() const;
    // 前缀递增，返回递增后对象的引用
    strBlobPtr & incr();

    // 前置运算符
    strBlobPtr & operator++();
    strBlobPtr & operator--();
    // 后置运算符
    strBlobPtr operator++(int);
    strBlobPtr operator--(int);

    strBlobPtr & operator+(std::size_t n);
    strBlobPtr & operator-(std::size_t n);
    strBlobPtr & operator+=(std::size_t n);
    strBlobPtr & operator-=(std::size_t n);

    std::string & operator*() const;
    std::string * operator->() const;


private:
    // 若检查成功，check 返回一个指向 vector 的 shared_ptr
    std::shared_ptr<std::vector<std::string >> check(std::size_t , const std::string &) const;

private:
    // 保存一个 weak_ptr，意味着底层 vector 可能被销毁
    std::weak_ptr<std::vector<std::string>> wptr;
    std::size_t curr;       // 在数组中的当前位置
};

bool operator==(const strBlobPtr & lhs, const strBlobPtr & rhs);
bool operator!=(const strBlobPtr & lhs, const strBlobPtr & rhs);
std::size_t operator-(const strBlobPtr & lhs, const strBlobPtr & rhs);
bool operator<(const strBlobPtr & lhs, const strBlobPtr & rhs);
bool operator<=(const strBlobPtr & lhs, const strBlobPtr & rhs);
bool operator>(const strBlobPtr & lhs, const strBlobPtr & rhs);
bool operator>=(const strBlobPtr & lhs, const strBlobPtr & rhs);
#endif //KNOWLEDGETEST_STRBLOBPTR_H
