//
// Created by libin on 2025/6/7.
//

#ifndef KNOWLEDGETEST_BLOB_H
#define KNOWLEDGETEST_BLOB_H
#include <memory>
#include <vector>
#include <string>
#include <initializer_list>

// 前置声明，在 Blob 中声明友元所必须的
template <typename T> class BlobPtr;
template <typename T> class Blob;   // 运算符 == 中参数所需要的
template <typename T> bool operator==(const Blob<T> &, const Blob<T> &);
template <typename T> bool operator!=(const Blob<T> &, const Blob<T> &);

template <typename T>
class Blob {
public:
    // 每个 Blob 实例将访问权限授予用相同类型实例化的 BlobPtr 和 相等运算符
    friend class BlobPtr<T>;
    friend bool operator==<T>(const Blob<T>&, const Blob<T> &);
    friend bool operator!=<T>(const Blob<T> &, const Blob<T> &);

    using value_type = T;
    using size_type = typename std::vector<T>::size_type;

    // 构造函数
    Blob();
    Blob(std::initializer_list<T> il);

    template<typename IT>
    Blob(IT b, IT e);

    // Blob 中的元素数目
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    // 添加或删除元素
    void push_back(const T & t) { data->push_back(t); }
    void push_back( T && t) { data->push_back(std::move(t));}
    void pop_back();

    // 元素访问
    T & front();
    T & front() const;
    T & back();
    T & back() const;
    T & operator[] (size_type i);
    T & operator[] (size_type i) const;

    // 获取迭代器
    BlobPtr<T> begin() { return BlobPtr<T>(*this); }
    BlobPtr<T> end() {
        auto ret = BlobPtr<T> (*this, data->size());
        return ret;
    }
    BlobPtr<T> cbegin() const { return BlobPtr<T> (*this); }
    BlobPtr<T> cend() const {
        auto ret = BlobPtr<T> (*this, data->size());
        return ret;
    }

private:
    void check(size_type i, const std::string & msg) const;
private:
    std::shared_ptr<std::vector<T>> data;
};


#endif //KNOWLEDGETEST_BLOB_H
