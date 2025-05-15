//
// Created by libin on 2025/3/21.
//

#ifndef KNOWLEDGETEST_SALE_DATA_H
#define KNOWLEDGETEST_SALE_DATA_H

#include <string>
#include <iostream>

class Sale_data;
std::istream & read(std::istream &, Sale_data &);

class Sale_data{

    // 为 Sale_data 的非成员函数做友元声明
    friend Sale_data add(const Sale_data &, const Sale_data &);
    friend std::istream & read(std::istream &, Sale_data &);
    friend std::ostream & print(std::ostream &, const Sale_data &);
    friend std::ifstream & read(std::ifstream &, Sale_data &);
    friend std::ostream & operator<<(std::ostream & os, const Sale_data & item);
    friend std::istream & operator>>(std::istream & is, Sale_data & item);
    friend bool operator==(const Sale_data & lhs, const Sale_data & rhs);
    friend bool operator!=(const Sale_data & lhs, const Sale_data & rhs);
public:
    // 非委托构造函数
    Sale_data(std::string s, unsigned n, double p) :
            bookNo(s), units_sold(n), revenue(p) { }

    // 委托构造函数
    Sale_data() : Sale_data("", 0, 0) { }
    Sale_data(std::string &s) : Sale_data(s, 0, 0) { }
    Sale_data(const std::string &s) : bookNo(s) { }
    Sale_data(std::istream &is) : Sale_data() { read(is, *this); }

    // 成员函数：关于 Sale_data 对象的操作
    std::string isbn() const { return bookNo; }
    Sale_data & combine( const Sale_data&);
    Sale_data & operator=(const std::string & str);

    Sale_data & operator+=(const Sale_data & rhs);

    explicit operator std::string() const { return bookNo; }
    explicit operator double () const { return revenue; }

private:
    double avg_price() const{
        return units_sold ? revenue / units_sold : 0;       // 隐式内联
    }

    // data member
    std::string bookNo; // ISBN 编号
    unsigned units_sold = 0;    // 某本书的销量
    double revenue = 0.0;   // 这本书的总销售收入
};

// Sale_data 的非成员接口函数
Sale_data add(const Sale_data &, const Sale_data &);
std::ostream & print(std::ostream &, const Sale_data &);
std::istream & read(std::istream &, Sale_data &);
std::ifstream & read(std::ifstream &, Sale_data &);

std::ostream & operator<<(std::ostream & os, const Sale_data & item);
std::istream & operator>>(std::istream & is, Sale_data & item);
Sale_data operator+(const Sale_data &lhs, const Sale_data &rhs);
bool operator==(const Sale_data & lhs, const Sale_data & rhs);
bool operator!=(const Sale_data & lhs, const Sale_data & rhs);

#endif //KNOWLEDGETEST_SALE_DATA_H
