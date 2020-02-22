#ifndef BLOB_TEMPLATE_H_
#define BLOB_TEMPLATE_H_

#include <memory>
#include <string>
#include <vector>

template <typename T>
using twin = std::pair<T, T>;

template <typename T>
class BlobTemplate {
   public:
    using value_type = T;
    using size_type = typename std::vector<T>::size_type;

    BlobTemplate() : data(std::make_shared<std::vector<T>>()){};
    BlobTemplate(std::initializer_list<T> il) : data(std::make_shared<std::vector<T>>(il)){};
    // 成员模板
    template <typename It>
    BlobTemplate(It a, It b);  //: data(std::make_shared<std::vector<T>>(a, b)) {}

    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }

    // 增删
    void push_back(const T& t) { data->push_back(t); }
    // 移动版本
    void push_back(T&& t) { data->push_back(std::move(t)); }
    void pop_back() { data->pop_back(); }

    // 访问
    T& back();
    T& operator[](size_type i);
    T& front();
    // const重载
    const T& back() const;
    const T& operator[](size_type i) const;
    const T& front() const;

    // T& begin() { return *(data->front()); }
    // T& end() { return *(data->back()); }
    // T& operator++() {
    //     ++*this;
    //     return *this;
    // }
    // bool operator!=(const BlobTemplate<T&> other) { return other->data == *this; }

   private:
    void check(size_type i, const std::string& msg) const;

    std::shared_ptr<std::vector<T>> data;
};

// 如果在类外实现成员模板，则需要同时提供类模板参数列表、成员模板参数列表，前者在前
template <typename T>
template <typename It>
BlobTemplate<T>::BlobTemplate(It a, It b) {
    // 将迭代器a和b指定的范围内的元素拷贝到新的vector中
    data = std::make_shared<std::vector<T>>(a, b);
}

template <typename T>
T& BlobTemplate<T>::back() {
    check(0, "back on empty blob");
    return data->back();
}

template <typename T>
const T& BlobTemplate<T>::back() const {
    check(0, "back on empty blob");
    return data->back();
}

template <typename T>
T& BlobTemplate<T>::operator[](size_type i) {
    check(i, "subscript out of range");
    return (*data)[i];
}

template <typename T>
const T& BlobTemplate<T>::operator[](size_type i) const {
    check(i, "subscript out of range");
    return (*data)[i];
}

template <typename T>
T& BlobTemplate<T>::front() {
    check(0, "front on empty blob");
    return data->front();
}

template <typename T>
const T& BlobTemplate<T>::front() const {
    check(0, "front on empty blob");
    return data->front();
}

template <typename T>
void BlobTemplate<T>::check(size_type i, const std::string& msg) const {
    if (i >= data->size()) {
        throw std::out_of_range(msg);
    }
}

#endif  // BLOB_TEMPLATE_H_