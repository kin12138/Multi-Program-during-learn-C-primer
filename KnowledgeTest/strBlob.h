//
// Created by libin on 2025/4/10.
//

#ifndef KNOWLEDGETEST_STRBLOB_H
#define KNOWLEDGETEST_STRBLOB_H

#include <initializer_list>
#include <vector>
#include <memory>
#include <string>
#include "strBlobPtr.h"

class strBlob {
    friend class strBlobPtr;
    friend bool operator==(const strBlob & lhs, const strBlob & rhs);
    friend bool operator!=(const strBlob & lhs, const strBlob & rhs);
public:
    using  size_type = std::vector<std::string>::size_type;
    strBlob();
    strBlob(std::initializer_list<std::string> il);
    strBlob(const strBlob & rhs);
    strBlob & operator=(const strBlob & rhs);
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }

    // 添加和删除元素
    void push_back(const std::string & s) { data->push_back(s);}
    void push_back(std::string && rhs) { data->push_back(rhs); }
    void pop_back();
    // 元素访问
    std::string & front();
    std::string & front() const;
    std::string & back();
    std::string & back() const;

    // 返回指向首元素和尾后元素的 strBlobPtr
    strBlobPtr begin() { return strBlobPtr(*this); }
    strBlobPtr end() {
        auto ret = strBlobPtr(*this, data->size());
        return ret;
    }

    strBlobPtr cbegin() const { return strBlobPtr(*this); }
    strBlobPtr cend() const {
        auto ret = strBlobPtr(*this, data->size());
        return ret;
    }

private:
    std::shared_ptr<std::vector<std::string>> data;
    // 如果 data[i] 不合法，抛出一个异常
    void check(size_type i, const std::string & msg) const;
};

bool operator==(const strBlob & lhs, const strBlob & rhs);
bool operator!=(const strBlob & lhs, const strBlob & rhs);


#endif //KNOWLEDGETEST_STRBLOB_H
