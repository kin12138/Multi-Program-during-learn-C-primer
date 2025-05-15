//
// Created by libin on 2025/4/18.
//

#ifndef KNOWLEDGETEST_HASPTR_H
#define KNOWLEDGETEST_HASPTR_H
#include <string>
#include <iostream>

/* HasPtr 类的行为像一个值*/
class HasPtr{
    friend void swap(HasPtr &, HasPtr &);
public:
    HasPtr(const std::string &s = std::string() ):
            ps(new std::string (s)), i(0) { std::cout << "executed the constructor" << std::endl; }

    HasPtr(const HasPtr& rhs) :
            ps(new std::string(*rhs.ps)), i(0) { std::cout << "executed the copy constructor" << std::endl; }
    HasPtr(HasPtr &&rhs) noexcept : ps(rhs.ps), i(rhs.i) { rhs.ps = nullptr; }

//    HasPtr & operator=(HasPtr rhs);
    HasPtr & operator=(const HasPtr &rhs);
    HasPtr & operator=(HasPtr &&rhs) noexcept;

    bool operator< (const HasPtr & rhs) const;

    ~HasPtr(){
        delete ps;
        std::cout << "executed destructor." << std::endl;
    }
private:
    std::string *ps;
    int i;
};

inline
void swap(HasPtr & lhs, HasPtr & rhs) {
    std::cout << "execute the swap" << std::endl;
    using std::swap;
    swap(lhs.ps, rhs.ps);     // 交换指针，而不是 string 数据
    swap(lhs.i, rhs.i);       // 交换 i 数据
}

class HasPtr2{
public:
    // 构造函数分配新的 string 和计数器，将计数器设置为 1
    HasPtr2(const std::string &s = std::string() ) :
            ps2(new std::string(s)), i2(0), use(new std::size_t(1)) { }
    // 拷贝构造函数拷贝三个数据成员，并递增计数器
    HasPtr2(const HasPtr2 & rhs) :
            ps2(rhs.ps2), i2(rhs.i2), use(rhs.use) { ++*use; }
    HasPtr2 & operator= (const HasPtr2 & rhs);
    ~HasPtr2();
private:
    std::string *ps2;
    int i2;
    std::size_t *use;
};





#endif //KNOWLEDGETEST_HASPTR_H
