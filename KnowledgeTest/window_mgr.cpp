//
// Created by libin on 2025/3/24.
//

#include "window_mgr.h"
#include "Screen.h"

// 构造函数定义，对 screens 初始化
window_mgr::window_mgr() : screens{Screen(24, 80, ' ')} { }

void window_mgr::clear(window_mgr::ScreenIndex i) {
    // s 是 Screen 的引用，指向想清空的那个 Screen
    Screen &s = screens[i];
    // 将选定 Screen 重置为空白
    s.contents = std::string(s.height * s.width, ' ');
}

window_mgr::ScreenIndex             // 首先处理返回类型
        window_mgr::addScreen(const Screen & s) {
    screens.push_back(s);
    return screens.size() - 1;
}