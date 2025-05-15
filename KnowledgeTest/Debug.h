//
// Created by libin on 2025/3/27.
//

#ifndef KNOWLEDGETEST_DEBUG_H
#define KNOWLEDGETEST_DEBUG_H

class Debug{
public:
    constexpr Debug(bool b) : hw(b), io(b), other(b) {}
    constexpr Debug(bool h, bool i, bool o) :
        hw(h), io(i), other(o) { }
    constexpr bool any() { return hw || io || other; }

    void set_io(bool b) { io = b; }
    void set_hw(bool b) { hw = b; }
    void set_other(bool b) { other = b; }
private:
    bool hw;    // 硬件错误，而非 IO 错误
    bool io;    // IO 错误
    bool other; // 其他错误
};

#endif //KNOWLEDGETEST_DEBUG_H
