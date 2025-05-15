//
// Created by libin on 2025/3/24.
//

#include "Screen.h"

 // 在函数定义处指定 inline

Screen& Screen::move(Screen::pos r, Screen::pos c) {
    pos row = r * width;        // 计算行的位置
    cursor = row + c;           // 将光标移动到指定的列
    return  *this;              // 以左值的形式返回对象
}

char Screen::get(Screen::pos r, Screen::pos c) const {      // 在类的内部声明为内联函数
    pos row = r * width;        // 计算行的位置
    return contents[row + c];   // 返回给定列的字符
}

void Screen::some_member() const {
    ++access_ctr;       // 保存一个计数值，用于记录成员函数被调用的次数
}


Screen & Screen::set(char c) {
    contents[cursor] = c;       // 设置当前光标所在位置新值
    return *this;               // 将 this 对象作为左值返回
}

Screen & Screen::set(pos r, pos col, char c) {
    contents[r*width + col] = c;        // 设置指定位置的值
    return *this;                       // 将 this 对象作为左值返回
}