//
// Created by libin on 2025/4/24.
//

#ifndef KNOWLEDGETEST_OVERLOADOPERATOR_H
#define KNOWLEDGETEST_OVERLOADOPERATOR_H

#include "Date.h"
#include <map>
#include <vector>
#include <functional>

void _14_25() {
    Date lhs(9999999), rhs(1);
    std::cout << (lhs -= 12000) << std::endl;
}

/*------14.34-----*/
struct if_else{
    int operator()(bool b, int ia, int ib){
        return b ? ia : ib;
    }
};

/*-------14.35------------*/

class PrintString{
public:
    PrintString(std::ostream & o = std::cout, char c = ' ') :
                os(o), sep(c) { }
    void operator() (std::string & s) { os << s << sep; }
private:
    std::ostream & os;
    char sep;
};

class getInputString {
public:
    getInputString(std::istream & i = std::cin) : is(i) { }
    std::string operator()() {
        std::string str;
        std::getline(is, str);
        return is ? str : std::string();
    }
private:
    std::istream & is;
};

void _14_36() {
    std::vector<std::string> vec;
    getInputString getInput;
    for (std::string temp; !(temp = getInput()).empty(); vec.push_back(temp));
    std::for_each(vec.begin(), vec.end(), PrintString(std::cout,' '));
}

/*---------14.37------------*/
class IsEqual{
public:
    IsEqual(int v) : value(v) { }
    bool operator() (int elem) {
        return elem == value;
    }
private:
    int value;
};

void _14_37() {
    std::vector<int> vec = { 3, 2, 1, 4, 3, 7, 8, 6 };
    std::replace_if(vec.begin(), vec.end(), IsEqual(3), 5);
    for (int i : vec) std::cout << i << " ";
}

/*----------14.38----------------*/
class CheckSize{
public:
    explicit CheckSize(size_t n) : SIZE(n) { }
    bool operator() (const std::string & str) const { return !str.empty() && str.size() < SIZE; }
    std::size_t limit() const { return SIZE; }
private:
    size_t SIZE;
};

void _14_38() {
    std::vector<CheckSize > Threshold;
    for(size_t i = 1; i <= 10; ++i) {
        Threshold.emplace_back(i);
    }

    std::map<size_t ,size_t > count_table;
    for(size_t i = 1; i <= 10; ++i) {
        count_table[i] = 0;
    }

    std::ifstream ifs("../Resource/letter.txt");
    std::string word;
    while (ifs >> word) {
        for (auto check : Threshold) {
            if (check(word))
                count_table[check.limit()]++;
        }
    }

    for (auto pair : count_table) {
        std::cout << "count " << pair.first << ": " << pair.second << std::endl;
    }
}

void _14_39() {
    CheckSize check(10);
    std::map<size_t ,size_t > count_table;
    count_table[0] = 0,count_table[1] = 0;

    std::ifstream ifs("../Resource/letter.txt");
    std::string word;
    while (ifs >> word) {
        if (check(word))
            count_table[0]++;
        else
            count_table[1]++;
    }
    for (auto pair : count_table)
        std::cout << "count in range " << pair.first << ": " << pair.second << std::endl;
}

/*---------------14.44---------------*/
int add(int i, int j) { return i + j; }
auto mod = [](int i, int j) { return i % j; };
struct Div{ int operator() (int i, int j) { return i / j; }};

void _14_44() {
    auto binops = std::map<std::string, std::function<int(int,int)>> {
            { "+", add},
            { "-", std::minus<int>()},
            { "/", Div()},
            { "*", [](int i, int j) { return i * j; }},
            { "%", mod}
    };

    std::cout << "Pls enter as: number operator number:\n";
    int lhs, rhs; std::string op;
    std::cin >> lhs >> op >> rhs;
    std::cout << binops[op] (lhs, rhs) << std::endl;
}

class SmallInt{
public:
    SmallInt(int i = 0) : val(i) {
        if (i < 0 || i > 255)
            throw std::out_of_range("Bad SmallInt value");
    }
    explicit operator int() const { return val; }
private:
    std::size_t val;
};

#endif //KNOWLEDGETEST_OVERLOADOPERATOR_H
