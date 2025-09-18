//
// Created by libin on 2025/6/8.
//

#ifndef KNOWLEDGETEST_VEC_H
#define KNOWLEDGETEST_VEC_H
#include <memory>
#include <initializer_list>

template<typename T> class Vec;

template<typename T> void swap(Vec<T> &lhs, Vec<T> & rhs);
template<typename T> bool operator==(const Vec<T> & lhs, const Vec<T> & rhs);
template<typename T> bool operator!=(const Vec<T> & lhs, const Vec<T> & rhs);

template <typename T>
class Vec {
public:
    // 友元
    friend void swap<T>( Vec<T> & lhs, Vec<T> & rhs);
    friend bool operator==<T>(const Vec<T> & lhs, const Vec<T> & rhs);
    friend bool operator!=<T>(const Vec<T> & lhs, const Vec<T> & rhs);
    // 拷贝控制成员
    Vec() : first_element(nullptr), first_free(nullptr), cap(nullptr) { }
    Vec(std::initializer_list<T> il);
    Vec(const Vec & rhs);
    Vec & operator=(const Vec & rhs);
    Vec(Vec && rhs) noexcept;
    Vec & operator = (Vec && rhs) noexcept;
    ~Vec();

    // 接受列表参数的赋值运算符
    Vec & operator=(std::initializer_list<T> il);

    // 元素访问
    T & operator[](size_t n) { return first_element[n]; }
    const T & operator[](size_t n) const { return first_element[n]; }
    T * begin() { return first_element; }
    T * end() { return first_free; }
    T * cbegin() const { return first_element; }
    T * cend() const { return first_free; }

    // 元素数目与内存大小
    size_t size() const { return first_free - first_element; }
    size_t capacity() const { return cap - first_element; }

    // 改变内存大小与元素数目大小
    void reserve(size_t n);
    void resize(size_t n);
    void resize(size_t n, const T & t);

    //添加删除元素
    void push_back(const T & );
    void push_back(T &&);


private:
    static std::allocator<T> alloc;     // 用来分配内存
    // 被添加元素的成员所使用
    void check_n_alloc() { if (size() == capacity()) reallocate(); }
    // 被拷贝控制成员所使用
    std::pair<T*, T*> alloc_n_copy(const T *, const T *);   // 返回拷贝后指向首尾元素的指针
    void free();    // 销毁元素释放内存
    void reallocate();  // 获取更多内存空间，并拷贝原来元素
    void alloc_n_move(size_t newCap);
    void range_initialize(const T *, const T *);

private:
    T * first_element;  // 指向数组首元素
    T * first_free;     // 指向数组尾元素之后的位置
    T * cap;    // 指向分配内存末尾之后的位置
};


#endif //KNOWLEDGETEST_VEC_H
