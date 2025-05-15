//
// Created by libin on 2025/3/24.
//

#ifndef SCREEN_H
#define SCREEN_H

#include <string>
#include <vector>

#include "window_mgr.h"

class Screen {
    // window_mgr 成员可以访问 Screen 的私有成员
    friend void window_mgr::clear(ScreenIndex);  // 声明window_mgr的clear为友元函数
public:
//    typedef std::string::size_type pos;
    using pos = std::string::size_type;
    Screen() = default;
    Screen(pos ht, pos wd) : height(ht), width(wd), contents(ht * wd, ' ') { }
    Screen(pos ht, pos wd, char c) : height(ht), width(wd), contents(ht * wd, c) { }

    char get() {        // 读取光标处的字符
        return contents[cursor];
    }
    inline char get(pos ht, pos wd) const;

    Screen & move(Screen::pos r, Screen::pos c);

    Screen & set(char);
    Screen & set(pos, pos, char);

    void some_member() const;

    // 根据对象是否是 const 重载了 display 函数
    Screen & display(std::ostream & os) {
        do_display(os);
        return *this;
    }
    const Screen & display(std::ostream & os) const {
        do_display(os);
        return *this;
    }
private:
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;

    mutable size_t access_ctr = 0;      // 即使在一个 const 对象内也能被修改

    // 该函数负责显示 Screen 的内容
    void do_display(std::ostream & os) const { os << contents; }
};


#endif //SCREEN_H
