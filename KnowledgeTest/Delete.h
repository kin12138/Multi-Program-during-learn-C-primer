//
// Created by libin on 2025/6/9.
//

#ifndef KNOWLEDGETEST_DELETE_H
#define KNOWLEDGETEST_DELETE_H

template<typename T>
class Delete{
public:
    void operator()(T * p) const noexcept {
        delete p;
    }
};

#endif //KNOWLEDGETEST_DELETE_H
