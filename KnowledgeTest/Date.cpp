//
// Created by libin on 2025/3/27.
//

#include "Date.h"
#include <algorithm>

// check if the Date object passed in is invalid
bool check(const Date & d) {
    if (d.month_ == 0 || d.month_ > 12) return false;
    else  {
        // month 1 3 5 7 8 10 12
        if (d.month_ == 1 || d.month_ == 3 || d.month_ == 5 ||
            d.month_ == 7 || d.month_ == 8 || d.month_ == 10 ||
            d.month_ == 12) {
            if (d.day_ == 0 || d.day_ > 31) return false;
            else return true;
        }
        // month 4 6 9 11
        else if(d.month_ == 4 || d.month_ == 6 ||
                d.month_ == 9 || d.month_ == 11) {
            if (d.day_ == 0 || d.day_ > 30) return false;
            else return true;
        }
        // month 2
        else {
            if (isLeapYear(d.year_)) {
                if (d.day_ == 0 || d.day_ > 29) return false;
                else return true;
            }
            else {
                if (d.day_ == 0 || d.day_ > 28) return false;
                else return true;
            }
        }
    }
}

// check if the year is leap year
bool isLeapYear(Date::Size y) {
    if (!(y % 400)) return true;
    else {
        if (!(y % 100)) return false;
        else return !(y % 4);
    }
}

Date::Date(Date::Size days) {
    // calculate the year
    Size y400 = days / YtoD_400;
    Size y100 = (days - y400*YtoD_400) / YtoD_100;
    Size y4 = (days - y400*YtoD_400 - y100*YtoD_100) / YtoD_4;
    Size y = (days - y400*YtoD_400 - y100*YtoD_100 - y4*YtoD_4) / YtoD_1;
    Size d = days - y400*YtoD_400 - y100*YtoD_100 - y4*YtoD_4 - y * YtoD_1;
    year_ = y400 * 400 +  y100 * 100 + y4 * 4 + y;


    // check if leap year and choose the months vector accordingly
    std::vector<Size> currYear = isLeapYear(year_) ? monthsVec_1 : monthsVec_n;

    // calculate day and month
    Size D_accumu = 0, M_accumu = 0;
    std::find_if(currYear.begin(), currYear.end(),
                 [&](Size m)
                 {
                    D_accumu += m;
                    M_accumu++;
                    if (d < D_accumu) {
                        month_ = M_accumu;
                        day_ = d - (D_accumu - m);
                        return true;
                    } else
                        return false;
                 });
    if (M_accumu == 0 || month_ < 1 || month_ > 12)
        throw std::out_of_range("days out of valid range");

}

Date::Date(std::istream &is, std::ostream &os) {
    is >> day_ >> month_ >> year_;
    if (is) {
        if (check(*this)) return;
        else {
            os << "Invalid input! Object is default initialized.";
            *this = Date();
        }
    } else{
        os << "Invalid input! Object is default initialized.";
        *this = Date();
    }
}

Date::Date(const Date & rhs) :
    day_(rhs.day_), month_(rhs.month_), year_(rhs.year_) { std::cout << "copy constructor" << std::endl; }

Date& Date::operator=(const Date & rhs) {
    std::cout << "copy-assignment operator" << std::endl;
    if(this != &rhs) {
        year_ = rhs.year_;
        month_ = rhs.month_;
        day_ = rhs.day_;
    }
    return *this;
}

Date::~Date() {
    std::cout << "Date destroyed" << std::endl;
}

Date::Date(Date &&rhs) noexcept  :
        day_(rhs.day_), month_(rhs.month_), year_(rhs.year_){
    rhs.day_ = 1; rhs.month_ = 1; rhs.year_ = 0;
    std::cout << "move constructor" << std::endl;
}

Date& Date::operator=(Date &&rhs) noexcept {
    std::cout << "move-assignment operator" << std::endl;
    if(this != &rhs) {
        year_ = rhs.year_;
        month_ = rhs.month_;
        day_ = rhs.day_;
        rhs.day_ = 1; rhs.month_ = 1; rhs.year_ = 0;
    }
    return *this;
}

Date::Size Date::toDays() const {
    Size result = day_;

    // check if leap year and choose the months vector accordingly
    std::vector<Size> currYear = isLeapYear(year_) ? monthsVec_1 : monthsVec_n;

    // calculate result + days by years
    result += (year_ / 400) * YtoD_400;
    result += (year_ % 400 / 100) * YtoD_100;
    result += (year_ % 100 / 4) * YtoD_4;
    result += (year_ % 4) * YtoD_1;

    // 累加当年从年初到上月末的天数
    for (Size i = 0; i + 1 < month_; ++i)
        result += currYear[i];
    return result;
}

Date & Date::operator+=(Date::Size offset) {
    *this = Date(toDays() + offset);
    return *this;
}

Date & Date::operator-=(Date::Size offset) {
    if (toDays() > offset)
        *this = Date(toDays() - offset);
    else
        *this = Date();
    return *this;
}

std::ostream & operator<<(std::ostream & os, const Date & rhs) {
    os << rhs.day_ << " " << rhs.month_ << " " << rhs.year_;
    return os;
}

std::istream & operator>>(std::istream & is, Date & rhs) {
    rhs = Date(is, std::cout);
    return is;
}

int operator-(const Date & lhs, const Date & rhs) {
    return lhs.toDays() - rhs.toDays();
}

bool operator==(const Date & lhs, const Date & rhs) {
    return lhs.day_ == rhs.day_ &&
            lhs.month_ == rhs.month_ &&
            lhs.year_ == rhs.year_;
}
bool operator!=(const Date & lhs, const Date & rhs) {
    return !(lhs == rhs);
}

bool operator<(const Date & lhs, const Date & rhs) {
    return lhs.toDays() < rhs.toDays();
}
bool operator<=(const Date & lhs, const Date & rhs) {
    return !(rhs < lhs);
}
bool operator>(const Date & lhs, const Date & rhs) {
    return rhs < lhs;
}
bool operator>=(const Date & lhs, const Date & rhs) {
    return !(lhs < rhs);
}
Date operator+(const Date & lhs, Date::Size rhs) {
    Date result(lhs);
    return result += rhs;
}
Date operator-(const Date & lhs, Date::Size rhs) {
    Date result(lhs);
    return result -= rhs;
}