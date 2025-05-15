//
// Created by libin on 2025/4/18.
//

#ifndef KNOWLEDGETEST_COPYCONTROL_H
#define KNOWLEDGETEST_COPYCONTROL_H
#include <string>
#include <iostream>
#include <utility>
#include <vector>
#include "HasPtr.h"
#include "algorithm"
#include "String.h"

void _13_5() {

}

void _13_13() {
    struct X{
        X(){ std::cout << "X() " << "default constructor" << std::endl; }
        X(const X& x) { std::cout << "X(const X&) " << "copy constructor" << std::endl; }
        X& operator=(const X&) {
            std::cout << "X& operator=(const X&) " << "copy-assignment operator" << std::endl;
            return *this;
        }
        ~X(){ std::cout << "~X() " << "destructor" << std::endl; }
    };

    auto f = [] (const X &rx,X x)
    {
        std::vector<X> vec;
        vec.reserve(2);
        vec.push_back(rx);
        vec.push_back(x);
    };


    X *px = new X;
    f(*px, *px);
    delete px;
}

class numbered{
public:
    numbered() : mysn(++unique) { }
    numbered(numbered & s) : mysn(++unique) { }
    unsigned mysn;
    static unsigned unique;
};

unsigned numbered::unique = 10;

void f(numbered s) {
    std::cout << s.mysn << std::endl;
}

void _13_17() {
    numbered a, b = a, c = b;
    f(a);
    f(b);
    f(c);
}

class Employee{
public:
    Employee() : id(++unique) {
        std::cout << "default construct" << std::endl;
        std::cout << unique << std::endl;
    }
    Employee(const std::string &s) :
                name(s), id(++unique) {
        std::cout << "other constructor" << std::endl;
        std::cout << unique << std::endl;
    }
    Employee(const Employee&) = delete;
    Employee & operator=(const Employee&) = delete;
private:
    static unsigned unique;
    std::string name;
    unsigned id;
};

unsigned Employee::unique = 0;

void _13_19(){
    Employee e;
    Employee e2 = Employee("string");
}

/* _13_28 */

void _13_30() {
    HasPtr hp1("1111111");
    hp1 = HasPtr("22222");
}

void _13_31() {
    std::vector<HasPtr> vec;
    vec.emplace_back("111");
    vec.emplace_back("222");
    vec.emplace_back("333");
    std::sort(vec.begin(), vec.end());
}

/*-------------13.42----------------*/
#include <memory>
#include <map>
#include <set>
#include <fstream>
#include "StrVec.h"
#include "sstream"

class QueryResult2;
class TextQuery2 {
public:
    using line_no = unsigned ;
    using Line_set = std::set<line_no>;
    using Line_map = std::map<std::string, std::shared_ptr<Line_set>>;
    TextQuery2(std::ifstream &);
    QueryResult2 query(const std::string &) const;

private:
    std::shared_ptr<StrVec> data;
    //wl_map 关联单词与行号 set
    Line_map wl_map;
};

class QueryResult2 {
    friend std::ostream & print(std::ostream & os, const QueryResult2 &);

public:
    QueryResult2(const std::string & s,
                std::shared_ptr<StrVec> sp,
                std::shared_ptr<std::set<unsigned>> ls )
            : sought(s),  contents(std::move(sp)), lines(std::move(ls)){ }
private:
    std::string sought;
    std::shared_ptr<StrVec> contents;
    std::shared_ptr<std::set<unsigned>> lines;
};

std::ostream & print(std::ostream & os, const QueryResult2 &);

TextQuery2::TextQuery2(std::ifstream & infile)
            : data(std::make_shared<StrVec>()){
    std::string text;
    while (std::getline(infile, text)) {
        // 将一行文本保存为 vector 的一个元素
        data->push_back(text);
        line_no line_number = data->size() - 1;    // 当前行号

        // 在 map 中保存每个单词和它相应的行号
        std::string word;
        std::istringstream stream(text);
        while (stream >> word) {
            auto &lines = wl_map[word];
            if (!lines)     // 如果单词是第一次碰到的，此指针为空
                lines.reset(new Line_set);  // 分配一个新的 set
            lines->insert(line_number);
        }
    }
}

QueryResult2 TextQuery2::query(const std::string & word) const {
    static auto no_lines = std::make_shared<Line_set> ();

    auto it = wl_map.find(word);
    if (it == wl_map.end())
        return QueryResult2(word, data, no_lines);
    else
        return QueryResult2(word, data, it->second);
}

std::ostream & print(std::ostream & os, const QueryResult2 & qr){
    size_t count = qr.lines->size();
    os << qr.sought << " occurs " << count
       << (count > 1 ? " times " : " time ")
       << "\n";

    // 逐个打印
    for (auto lineno : *qr.lines) {
//        strBlobPtr pb(qr.contents, lineno);
        auto SVptr = qr.contents->begin();
        os << "\t(line " << lineno + 1 << ") "
           << *(SVptr+lineno)
           << "\n";

    }

    return os;
}

void runQueries2(std::ifstream &infile) {
    TextQuery2 tq(infile);   // 保存文件并建立查询 map
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

void _13_42() {
    std::ifstream ifs("../Resource/letter.txt");
    runQueries2(ifs);
}

void _13_44() {
    String s1("Hello");
    String s2(", world!");
    std::cout << "s1 = " << s1 << std::endl;
    std::cout << "s2 = " << s2 << std::endl;

    // 测试 operator+
    String s3 = s1 + s2;
    std::cout << "s3 = s1 + s2 = " << s3 << std::endl;

    // push_back & pop_back
    s1.push_back('!');
    std::cout << "s1 after push_back: " << s1 << std::endl;
    s1.pop_back();
    std::cout << "s1 after pop_back: " << s1 << std::endl;

    // reserve & capacity
    std::cout << "s3 size: " << s3.size()
              << ", capacity: " << s3.capacity() << "\n";
    s3.reserve(50);
    std::cout << "s3.capacity() after reserve(50): " << s3.capacity() << "\n";

    // resize 增大与缩小
    s3.resize(5);
    std::cout << "s3 after resize(5): " << s3 << std::endl;
    s3.resize(10, 'x');
    std::cout << "s3 after resize(10,'x'): " << s3 << std::endl;
}

void _13_48() {
    std::vector<String> vec;
    String s1("s1"), s2("s2"), s3("s3");
    vec.push_back(std::move(s1));
    vec.push_back(std::move(s2));
    vec.push_back(std::move(s3));
}

class Foo{
public:
    Foo sorted() &&;
    Foo sorted() const &;
private:
    std::vector<int> data;
};

Foo Foo::sorted() &&{
    std::cout << "sorted() &&" << std::endl;
    std::sort(data.begin(), data.end());
    return *this;
}

Foo Foo::sorted() const &{
    std::cout << "sorted() const &" << std::endl;
    Foo ret(*this);
    std::sort(ret.data.begin(), ret.data.end());
    return *this;
}

void _13_58() {
    Foo().sorted();
    Foo f;
    f.sorted();
}



#endif //KNOWLEDGETEST_COPYCONTROL_H
