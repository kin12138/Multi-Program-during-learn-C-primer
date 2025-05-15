//
// Created by libin on 2025/3/21.
//
#include "Sale_data.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>


Sale_data & Sale_data::combine(const Sale_data & rhs) {
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;       // 返回调用该函数的对象
}

// 输入交易信息包括 ISBN, 售出总数，售出价格
std::istream & read(std::istream & is, Sale_data & item) {
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}

std::ostream & print(std::ostream & os, const Sale_data & item) {
    os << item.isbn() << " " << item.units_sold << " "
        << item.revenue << " " << item.avg_price();
    return os;
}

// 接受两个 Sale_data 对象，返回一个新的 Sale_data 对象，用于表示两个对象的和
Sale_data add(const Sale_data &lhs, const Sale_data &rhs) {
    Sale_data sum = lhs;
    sum.combine(rhs);
    return sum;
}

// main 函数接受文件名，从文件读取交易记录
std::ifstream & read(std::ifstream & ifs, Sale_data & item) {
    double price = 0;
    std::string record;
    std::getline(ifs, record);
    std::istringstream  iss(record);
    iss >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return ifs;
}

// 比较两个 Sale_data 对象的 isbn() 成员
bool compareIsbn(Sale_data & s1, Sale_data & s2) {
    return s1.isbn() < s2.isbn();
}

// 排序一个保存 Sale_data 对象的 vector
void sort_Sale_data(std::vector<Sale_data> & vec) {
//    std::sort(vec.begin(), vec.end(), compareIsbn);
    // lambda 表达式版本
    std::sort(vec.begin(), vec.end(),
              [] (const Sale_data & s1, const Sale_data &s2)
              { return s1.isbn() < s2.isbn();});
}

std::ostream & operator<<(std::ostream & os, const Sale_data & item){
    os << item.isbn() << " " << item.units_sold << " "
        << item.revenue << " " << item.avg_price();
    return os;
}

std::istream & operator>>(std::istream & is, Sale_data & item){
    double price;
    is >> item.bookNo >> item.units_sold >> price;
    if (is)     // 检查输入是否成功
        item.revenue = item.units_sold * price;
    else
        item = Sale_data();     // 输入失败，对象被赋予默认状态
    return is;
}

Sale_data operator+(const Sale_data &lhs, const Sale_data &rhs) {
    Sale_data sum = lhs;
    sum += rhs;
    return sum;
}

bool operator==(const Sale_data & lhs, const Sale_data & rhs){
    return lhs.isbn() == rhs.isbn() &&
            lhs.units_sold == rhs.units_sold &&
            lhs.revenue == rhs.revenue;
}

bool operator!=(const Sale_data & lhs, const Sale_data & rhs) {
    return !(lhs == rhs);
}

Sale_data & Sale_data::operator=(const std::string &isbn) {
    *this = Sale_data(isbn);
    return *this;
}

// 作为成员的二元运算符，左侧对象隐式绑定到 this 指针
// 假定两个对象表示的是同一本书
Sale_data & Sale_data::operator+=(const Sale_data &rhs) {
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}