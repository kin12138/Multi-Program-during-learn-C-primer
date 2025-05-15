//
// Created by libin on 2025/4/18.
//

#include "HasPtr.h"

//HasPtr & HasPtr::operator=(const HasPtr &rhs) {
//    auto newp = new std::string(*rhs.ps);
//    delete ps;
//    ps = newp;
//    i = rhs.i;
//    return *this;
//}

// 注意 rhs 按值传递，
// 意味着 HasPtr 的拷贝构造函数将右侧运算对象中的 string 拷贝到 rhs
/*HasPtr & HasPtr::operator=(HasPtr rhs) {
    std::cout << "copy-swap copy-assignment operator: " << *rhs.ps << std::endl;
    swap(*this, rhs);
    return *this;
}*/

HasPtr & HasPtr::operator=(const HasPtr &rhs) {
    std::cout << "normal copy-assignment operator: " << *rhs.ps << std::endl;
    delete ps;
    ps = rhs.ps;
    i = rhs.i;
    return *this;
}

HasPtr & HasPtr::operator=(HasPtr &&rhs) noexcept{
    std::cout << "move-assignment  operator: " << *rhs.ps << std::endl;
    delete ps;
    ps = rhs.ps;
    i = rhs.i;
    rhs.ps = nullptr;
    return *this;
}

bool HasPtr::operator<(const HasPtr &rhs) const{
    std::cout << "executed the <" << std::endl;
    return *ps < *rhs.ps;
}

HasPtr2 & HasPtr2::operator=(const HasPtr2 &rhs) {
    ++*rhs.use;     // 递增右侧对象的引用计数
    if(--*use == 0) {   // 递减本对象的引用计数
        delete ps2;     // 如果引用计数变为 0，释放本对象分配的成员
        delete use;
    }
    // 将数据从 rhs 拷贝到本对象
    ps2 = rhs.ps2;
    i2 = rhs.i2;
    use = rhs.use;
    return *this;
}

HasPtr2::~HasPtr2() {
    if (--*use == 0) {
        delete ps2;
        delete use;
    }
}


