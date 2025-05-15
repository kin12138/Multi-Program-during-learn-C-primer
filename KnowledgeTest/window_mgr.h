//
// Created by libin on 2025/3/24.
//

#ifndef KNOWLEDGETEST_WINDOW_MGR_H
#define KNOWLEDGETEST_WINDOW_MGR_H

//#include "Screen.h"
#include <vector>

class Screen;

class window_mgr {
public:
    using ScreenIndex = std::vector<Screen>::size_type;
    // 构造函数声明，在其中初始化 screens
    window_mgr();
    void clear(ScreenIndex);

    // 向窗口添加一个 Screen, 返回它的编号
    ScreenIndex  addScreen(const Screen &);
private:
    // 默认情况下，一个 window_mgr 包含一个标准尺寸的空白 Screen
//    std::vector<Screen> screens{Screen(24, 80, ' ')};
    std::vector<Screen> screens;
};


#endif //KNOWLEDGETEST_WINDOW_MGR_H
