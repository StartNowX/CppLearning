#include <iostream>

#include "smart_ptr.h"

using namespace std;

class Shape {
   public:
    virtual ~Shape() {}
};

class Circle : public Shape {
   public:
    ~Circle() { puts("~Circle()"); }
};

int main(int argc, char* argv[]) {
    Circle* circle_ptr = new Circle();
    smart_ptr<Circle> ptr1(circle_ptr);
    cout << "use count of ptr1 is " << ptr1.use_count() << endl;  // use count of ptr1 is 1

    smart_ptr<Shape> ptr2;
    cout << "use count of ptr2 is " << ptr2.use_count() << endl;  // use count of ptr2 is 0

    ptr2 = ptr1;
    cout << "use count of ptr2 is " << ptr2.use_count() << endl;  // use count of ptr2 is 2

    if (ptr1) {
        cout << "ptr1 is noempty." << endl;  // ptr1 is noempty
    }

    smart_ptr<Shape> ptr4 = dynamic_pointer_cast<Shape>(ptr2);
    cout << "use count of ptr4 is " << ptr4.use_count() << endl;  // use count of ptr4 is 3

    smart_ptr<Shape> ptr3 = std::move(ptr2);
    cout << "use count of ptr3 is " << ptr3.use_count() << ", count of ptr2 is " << ptr2.use_count()
         << endl;  // use count of ptr3 is 3, 0

    return 0;
}