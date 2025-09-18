//
// Created by libin on 2025/6/9.
//

#ifndef KNOWLEDGETEST_DEBUGDELETE_H
#define KNOWLEDGETEST_DEBUGDELETE_H
#include <iostream>

class DebugDelete {
public:
    DebugDelete(std::ostream & s = std::cerr) : os(s) { }

    template<typename T> void operator() (T * p) {
        std::cout << "deleting unique_ptr" << std::endl;
        delete p;
    }
private:
    std::ostream & os;
};
#endif //KNOWLEDGETEST_DEBUGDELETE_H
