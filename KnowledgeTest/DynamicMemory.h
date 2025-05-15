//
// Created by libin on 2025/4/10.
//

#ifndef KNOWLEDGETEST_DYNAMICMEMORY_H
#define KNOWLEDGETEST_DYNAMICMEMORY_H

#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include "strBlobPtr.h"
#include "strBlob.h"
#include <fstream>
#include "TextQuery.h"
#include "QueryResult.h"

std::vector<int> * make_DVector() {
    auto * vec = new std::vector<int> ();
    return vec;
}

std::vector<int> * mem_vec(std::istream & is) {
    auto vec = make_DVector();
    int item = 0;
    while (is >> item) {
        vec->push_back(item);
    }
    return vec;
}

void print_d(std::vector<int> * vec) {
    std::ostream_iterator<int> out(std::cout, " ");
    std::copy(vec->begin(), vec->end(), out);
    delete vec;
}

void _12_6() {
    print_d(mem_vec(std::cin));
}

std::shared_ptr<std::vector<int>> make_vec () {
    return std::shared_ptr<std::vector<int>> ();
}

std::shared_ptr<std::vector<int>> mem(std::istream & is) {
    auto vec = make_vec();
    int item = 0;
    while (is >> item) {
        vec->emplace_back(item);
    }
    return vec;
}

void print(std::shared_ptr<std::vector<int>> vec) {
    std::ostream_iterator<int> out(std::cout, " ");
    std::copy(vec->cbegin(), vec->cend(), out);
}

void _12_7() {
    print(mem(std::cin));
}

/*--------- 12_14 ---------*/

struct connection{
    std::string ip;
    int port;
    connection(std::string i, int p) : ip(i), port(p) {}
};

struct destination{
    std::string ip;
    int port;
    destination(std::string i, int p) : ip(i), port(p) {}
};

connection connect(destination *pDest) {
    std::shared_ptr<connection> pConn(new connection(pDest->ip, pDest->port));
    std::cout << "created connection (" << pConn.use_count() << ")" << std::endl;
    return *pConn;
}

void disconnect(connection pConn) {
    std::cout << "connection close(" << pConn.ip  << ":" << pConn.port << ")" << std::endl;
}

void end_connection(connection * pConn) {
    disconnect(*pConn);
}

void f(destination &d) {
    connection conn = connect(&d);
    std::shared_ptr<connection> p(&conn, end_connection);
    std::cout << "connecting now(" << p.use_count() << ")" << std::endl;
}

void _12_14() {
    destination dest("220.181.111.111", 1024);
    f(dest);
}

void _12_16() {
    std::unique_ptr<int> p(new int(42));
}

void _12_17() {
    using IntP = std::unique_ptr<int>;
    int ix = 1024, *pi = &ix, *pi2 = new int(2048);
    IntP p1(pi);
    IntP p2(pi2);
    IntP p3(&ix);
    IntP p4(p2.get());
}

void _12_20() {
    std::ifstream ifs("../Resource/converted.txt");
    strBlob sb;
    std::string text;
    while (std::getline(ifs, text)) {
        sb.push_back(text);
    }

    for (auto sbp = sb.begin(); sbp != sb.end(); sbp.incr()) {
        std::cout << sbp.deref() << std::endl;
    }
}


void _12_23() {
    const char *c1 = "hello";
    const char *c2 = "world";
    unsigned len = strlen(c1) +strlen(c2) + 1;
    char *r = new char[len]();
    strcat_s(r, len, c1);
    strcat_s(r, len, c2);
    std::cout << r << std::endl;

    std::string s1 = "Hello";
    std::string s2 = "World";
    strcpy_s(r, len, (s1+s2).c_str());
    std::cout << r << std::endl;

    delete [] r;
}

void _12_24() {
    std::string word;
    std::cin >> word;
    char *c = new char[word.size()+1]();
    strcpy_s(c, word.size()+1, word.c_str());
    std::cout << c << std::endl;
    delete [] c;
}

void _12_26() {
    std::allocator<std::string> alloc;
    int n = 10;
    auto const p = alloc.allocate(n);

    auto q = p;
    std::string s;
    while (std::cin >> s && q != p + n) {
        alloc.construct(q++, s);
    }
    const size_t size = q - p;

    while (q != p) {
        std::cout << *q << std::endl;
        alloc.destroy(--q);
    }
    alloc.deallocate(p, n);
}

void runQueries(std::ifstream &infile) {
    TextQuery tq(infile);   // 保存文件并建立查询 map
    // 与用户交互: 提示用户输入要查询的单词，完成查询并打印结果
    while(true) {
        std::cout << "enter word to look for, or q to quie: \n";
        std::string s;
        // 若遇到文件尾或用户输入 'q' 时终止
        if (!(std::cin>>s) || s == "q") break;

        // 指向查询并打印结果
        print(std::cout, tq.query(s))  << std::endl;
    }
}

void _12_27() {
    std::ifstream ifs("../Resource/letter.txt");
    runQueries(ifs);
}

void _12_28() {
    using line_no = unsigned;
    using line_set = std::set<line_no>;
    using line_map = std::map<std::string, line_set>;

    // 保存数据
    std::vector<std::string> data;
    line_map wl_map;

    std::string text;
    std::ifstream infile("../Resource/letter.txt");
    line_no line_number = 0;
    while (std::getline(infile, text)) {
        // 按行保存文本
        data.push_back(text);

        // 保存每个单词与它的行号
        std::istringstream stream(text);
        std::string word;
        while (stream >> word) {
            auto it = wl_map.find(word);
            if (it == wl_map.end())
                wl_map[word].insert(line_number);
            else
                it->second.insert(line_number);
        }
        ++line_number;
    }

    // 查询单词

    while (true) {
        std::cout << "enter word to look for, or q to quit: \n";
        std::string s;
        if (!(std::cin >> s) || s == "q") break;

        // 查询并打印结果
        auto it = wl_map.find(s);
        if (it == wl_map.end()) {
            std::cout << s << " occurs " << "0 time" << std::endl;
        } else {
            std::cout << s << "occurs " << it->second.size() << " times\n";
            for (auto item : it->second) {
                std::cout << "\t(line " << item + 1 << ") "
                          << data.at(item) << "\n";
            }
            std::cout << std::endl;
        }
    }
}
#endif //KNOWLEDGETEST_DYNAMICMEMORY_H
