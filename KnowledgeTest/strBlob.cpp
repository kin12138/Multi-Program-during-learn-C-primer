//
// Created by libin on 2025/4/10.
//

#include "strBlob.h"
#include <stdexcept>

strBlob::strBlob() : data(std::make_shared<std::vector<std::string>> () ) { }
strBlob::strBlob(std::initializer_list<std::string> il)
                : data( std::make_shared<std::vector<std::string>> (il) ) { }

strBlob::strBlob(const strBlob &rhs) {
    data = std::make_shared<std::vector<std::string>>(*rhs.data);
}

strBlob & strBlob::operator=(const strBlob &rhs) {
    data = std::make_shared<std::vector<std::string>>( *rhs.data);
    return *this;
}

void strBlob::check(strBlob::size_type i, const std::string &msg) const {
    if (i >= data->size()) {
        throw std::out_of_range(msg);
    }
}

std::string & strBlob::front() {
    check(0, "front on empty strBlob");
    return data->front();
}

std::string & strBlob::front() const {
    check(0, "front on empty strBlob");
    return data->front();
}

std::string & strBlob::back() {
    check(0, "back on empty strBlob");
    return data->back();
}

std::string & strBlob::back() const {
    check(0, "back on empty strBlob");
    return data->back();
}

void strBlob::pop_back() {
    check(0, "pop_back on empty strBlob");
    data->pop_back();
}

bool operator==(const strBlob & lhs, const strBlob & rhs) {
    return lhs.data == rhs.data;
}

bool operator!=(const strBlob & lhs, const strBlob & rhs) {
    return !(lhs==rhs);
}