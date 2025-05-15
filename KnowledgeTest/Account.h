//
// Created by libin on 2025/3/27.
//

#ifndef KNOWLEDGETEST_ACCOUNT_H
#define KNOWLEDGETEST_ACCOUNT_H

#include <string>

class Account {
public:
    void calculate() { amount += amount * interestRate; }
    static double rate() { return interestRate; }
    static void rate( double );
private:
    std::string owner;
    double amount;
    static double interestRate;
    static double initRate();
};


#endif //KNOWLEDGETEST_ACCOUNT_H
