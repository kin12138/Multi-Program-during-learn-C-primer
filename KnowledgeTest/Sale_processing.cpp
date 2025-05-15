//
// Created by libin on 2025/3/21.
//
#include "Sale_data.h"
#include <fstream>

void sale_process() {
    Sale_data total;
    if (read(std::cin, total)) {                        // 读入第一笔交易
        Sale_data trans;
        while (read(std::cin, trans)) {                 // 读入剩余交易
            if (total.isbn() == trans.isbn()) {               // 检查 ISBN
                total.combine(trans);                         // 更新变量 total 当前的值
            } else {
                print (std::cout, total) << std::endl;     // 输出结果
                total = trans;                                // 处理下一本书
            }
        }
        print(std::cout, total) << std::endl;              // 输出最后一条交易
    } else {                                                  // 没有输入任何信息
        std::cerr << "No data?!" << std::endl;
    }
}

void sale_process2() {
    if (std::cin) {
        Sale_data total = Sale_data(std::cin);
        while (std::cin) {
            Sale_data trans = Sale_data(std::cin);
            if (total.isbn() == trans.isbn())
                total.combine(trans);
            else {
                print(std::cout, total) << std::endl;
                total = trans;
            }
            print(std::cout, total) << std::endl;
        }
    } else {
        std::cerr << "No data?!" << std::endl;
    }
}

void sale_process3(std::string & filename) {
    std::ifstream input(filename);
    Sale_data total;
    if (read(input, total)){
        Sale_data trans;
        while (read(input, trans)) {
            if (total.isbn() == trans.isbn()) {
                total.combine(trans);
            } else {
                print(std::cout, total) << std::endl;
                total = trans;
            }
        }
        print(std::cout, total);
    } else {
        std::cerr << "No data?!" << std::endl;
    }
}