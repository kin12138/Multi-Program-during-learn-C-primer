//
// Created by libin on 2025/4/21.
//

#ifndef KNOWLEDGETEST_STRVEC_H
#define KNOWLEDGETEST_STRVEC_H
#include <memory>
#include <string>
#include <utility>
#include <initializer_list>

class StrVec {
    friend void swap(StrVec &, StrVec &);
    friend bool operator==(const StrVec & lhs, const StrVec & rhs);
    friend bool operator!=(const StrVec & lhs, const StrVec & rhs);
public:
    StrVec() :  // allcator 成员进行默认初始化
            elements(nullptr), first_free(nullptr), cap(nullptr) { }
    StrVec(const std::initializer_list<std::string> &il);
    // 拷贝控制成员
    StrVec(const StrVec &);     // 拷贝构造函数
    StrVec & operator=(StrVec); // 拷贝赋值运算符
    ~StrVec();      // 析构函数
    StrVec(StrVec &&s) noexcept;    // 移动构造函数
    StrVec & operator=(StrVec &&rhs) noexcept;
    StrVec & operator=(std::initializer_list<std::string> il);
    std::string & operator[](std::size_t n) { return elements[n]; }
    const std::string & operator[](std::size_t n) const { return elements[n]; }

    size_t size() const  { return first_free - elements; }
    size_t capacity() const { return cap - elements; }
    void reserve(size_t n);
    void resize(size_t n);
    void resize(size_t n, const std::string &t);

    void push_back(const std::string &);    // 拷贝元素
    void push_back(std::string &&);

    std::string * begin() const { return elements; }
    std::string * end() const { return first_free; }

private:
    static std::allocator<std::string> alloc;       // 分配元素
    // 被添加元素的成员所使用
    void chk_n_alloc() { if (size() == capacity()) reallocate(); }
    // 被拷贝构造函数、赋值运算符、析构函数使用
    std::pair<std::string *, std::string *> alloc_n_copy(const std::string *, const std::string *);
    void free();    // 销毁元素并释放内存
    void reallocate();      // 获取更多内存空间并拷贝已有元素
    void alloc_n_move(size_t newCap);
    void range_initialize(const std::string *, const std::string *);
private:
    std::string * elements;      // 指向数组首元素
    std::string * first_free;   // 指向最后一个实际元素之后的位置
    std::string * cap;      // 指向分配内存末尾之后的位置
};

void swap(StrVec &lhs, StrVec &rhs);
bool operator==(const StrVec & lhs, const StrVec & rhs);
bool operator!=(const StrVec & lhs, const StrVec & rhs);
#endif //KNOWLEDGETEST_STRVEC_H
