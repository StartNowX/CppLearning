#ifndef BLOB_TEMPLATE_H_
#define BLOB_TEMPLATE_H_

#include <memory>
#include <string>
#include <vector>

template <typename T>
class Blob {
   public:
    using value_type = T;
    using size_type = typename std::vector<T>::size_type;

    Blob();
    Blob(std::initializer_list<T> il);

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

   private:
    void check(size_type i, const std::string& msg) const;

    std::shared_ptr<std::vector<T>> data;
};


#endif  // BLOB_TEMPLATE_H_