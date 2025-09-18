//
// Created by libin on 2025/6/7.
//

#ifndef KNOWLEDGETEST_BLOBPTR_H
#define KNOWLEDGETEST_BLOBPTR_H
#include <memory>
#include <vector>
#include <string>

template <typename T> class Blob;
template <typename T> class BlobPtr;
template <typename T> bool operator==(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs);
template <typename T> bool operator!=(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs);
template <typename T> bool operator<(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs);

template <typename T>
class BlobPtr {
public:
    friend bool operator == <T> (const BlobPtr<T> &, const BlobPtr<T> &);
    friend bool operator != <T>(const BlobPtr<T> &, const BlobPtr<T> &);
    friend bool operator < <T>(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs);

    BlobPtr() : curr(0) { }
    BlobPtr(Blob<T> &a, size_t sz = 0) :
                wptr(a.data), curr(sz) { }
    T & operator*() const {
        auto p = check(curr, "dereference past end");
        return (*p)[curr];
    }
    // 递增和递减
    BlobPtr & operator++();     // 前置运算符
    BlobPtr operator++(int);  // 后置运算符
    BlobPtr & operator--();
    BlobPtr operator--(int);

private:
    // 若检查成功，check 返回一个指向 vector 的 shared_ptr
    std::shared_ptr<std::vector<T>>
            check(std::size_t i, const std::string & msg) const;
private:
    // 保存一个 weak_ptr 表示底层 vector 可能被销毁
    std::weak_ptr<std::vector<T>> wptr;
    std::size_t curr;       // 当前位置
};


#endif //KNOWLEDGETEST_BLOBPTR_H
