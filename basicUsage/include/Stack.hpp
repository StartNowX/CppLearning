#ifndef STACK_HPP
#define STACK_HPP

template <class T>
class Stack{
public:
    Stack();
    bool isempty() const;
    bool isfull() const;
    bool push(const T& item);
    bool pop(T& item);

private:
    enum {MAX = 10};
    T items[MAX];
    T top;
};

#endif // STACK_HPP
