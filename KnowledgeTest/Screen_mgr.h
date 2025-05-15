//
// Created by libin on 2025/3/27.
//

#include "Screen.h"
#include <iostream>

void testMyScreen() {
    Screen myScreen(5, 5, 'x');
    myScreen.move(4, 0).set('#').display(std::cout);
    std::cout << "\n";
    myScreen.display(std::cout);
    std::cout << "\n";
}
