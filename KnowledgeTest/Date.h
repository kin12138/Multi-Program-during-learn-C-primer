//
// Created by libin on 2025/3/27.
//

#ifndef KNOWLEDGETEST_DATE_H
#define KNOWLEDGETEST_DATE_H

#include <iostream>
#include <vector>

class Date {
    friend bool check(const Date & d);
    friend bool operator==(const Date & lhs, const Date & rhs);
    friend bool operator<(const Date & lhs, const Date & rhs);
    friend std::ostream & operator<<(std::ostream & os, const Date & rhs);
public:
    using Size = std::size_t;
    // constructor
    Date() = default;
    explicit Date(Size days);   // constructor taking Size as days
    Date(Size day, Size month, Size year) : day_(day), month_(month), year_(year) { } // constructor taking three Size
    Date(std::istream & is, std::ostream & os); // constructor taking iostream

    // 拷贝控制成员
    Date(const Date &);     // copy constructor
    Date & operator= (const Date&); // copy-assignment operator
    ~Date();    // destructor
    Date(Date && rhs) noexcept; // move constructor
    Date& operator=(Date && rhs) noexcept;  // move-assignment operator

    // 其他成员
    Size toDays() const;
    Date& operator+=(Size offset);
    Date& operator-=(Size offset);

    explicit operator bool() const { return year_ < 4000; }
private:
    Size day_ = 1;
    Size month_ = 1;
    Size year_ = 0;
};

static const Date::Size YtoD_400 = 146097;  // 365*400 + 400/4 - 3 == 146097
static const Date::Size YtoD_100 = 36524;   // 365*100 + 100/4 - 3 == 36524
static const Date::Size YtoD_4 = 1461;      // 365*4 + 1 == 1461
static const Date::Size YtoD_1 = 365;       // 365

// the number of a month of normal year
static const std::vector<Date::Size> monthsVec_n = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// the number of a month of leap year
static const std::vector<Date::Size> monthsVec_1 = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// non-member operator: << >> - == != < <= > >= +
std::ostream & operator<<(std::ostream & os, const Date & rhs);
std::istream & operator>>(std::istream & is, Date & rhs);
int operator-(const Date & lhs, const Date & rhs);
bool operator==(const Date & lhs, const Date & rhs);
bool operator!=(const Date & lhs, const Date & rhs);
bool operator<(const Date & lhs, const Date & rhs);
bool operator<=(const Date & lhs, const Date & rhs);
bool operator>(const Date & lhs, const Date & rhs);
bool operator>=(const Date & lhs, const Date & rhs);
Date operator+(const Date & lhs, Date::Size rhs);
Date operator-(const Date & lhs, Date::Size rhs);

// utilities
bool check(const Date & d);
bool isLeapYear(Date::Size y);

#endif //KNOWLEDGETEST_DATE_H
