//
// Created by libin on 2025/4/22.
//

#ifndef KNOWLEDGETEST_STRING_H
#define KNOWLEDGETEST_STRING_H
#include <utility>
#include <memory>
#include <iostream>

/* 简化的 String 类*/
class String {
    friend void swap(String &, String &);
    friend String operator+(const String &lhs, const String & rhs);
    friend std::ostream & operator<<(std::ostream & os, const String &s);
    friend bool operator==(const String & lhs, const String & rhs);
    friend bool operator!=(const String & lhs, const String & rhs);
    friend bool operator<(const String & lhs, const String & rhs);
public:
    String();
    String(const char *cstr);
    // 拷贝控制成员
    String(const String &rhs);
    String(String &&rhs) noexcept;
    String & operator=(String);
    ~String();
    // 有关容量与元素数量的成员函数
    void reserve(size_t n);     // 申请指定大小的容量
    void resize(size_t n);
    void resize(size_t n, char c);  // 调整容器大小为 n 个元素。任何新添加元素都初始化为 c
    size_t size() const {return first_free - elements; }
    size_t capacity() const { return cap - elements; }

    char & operator[](std::size_t n)  { return elements[n];}
    const char & operator[](std::size_t n) const { return elements[n];}
    // 添加、删除元素的成员函数
    void push_back(char c);
    void push_back(const String & rhs);

    void pop_back();

    char* begin() { return elements; }
    char* end() { return first_free; }
    const char* begin() const { return elements; }
    const char* end() const { return first_free; }

private:
    static std::allocator<char> alloc;
    // 被添加元素的函数访问
    void chk_n_alloc() { if (size() == capacity()) reallocate(); }
    void chk_n_alloc(size_t n) {if (n > capacity()) reserve(n); }
    // 被 拷贝控制成员与析构函数访问
    std::pair<char*, char*> alloc_n_copy(const char*, const char *);
    void free();
    void alloc_n_move(size_t newCap);   // 申请一块指定大小的新内存，将原有元素移动到新内存
    void reallocate();  // 获取更多内存空间，并拷贝已有元素
    // 拼接两个字符串，返回值 first 指向首元素，second 指向尾元素之后位置
    void splice(const char*, const char*);

private:
    char * elements;
    char * first_free;
    char * cap;
};

void swap(String &, String &);
String operator+(const String &lhs, const String & rhs);
std::ostream & operator<<(std::ostream & os, const String &s);
bool operator==(const String & lhs, const String & rhs);
bool operator!=(const String & lhs, const String & rhs);
bool operator<(const String & lhs, const String & rhs);
bool operator>(const String & lhs, const String & rhs);
bool operator<=(const String & lhs, const String & rhs);
bool operator>=(const String & lhs, const String & rhs);

#endif //KNOWLEDGETEST_STRING_H
