## Notes of *C++ Template*

> David Vandevoorde, Nicolai M. Josuttis, Douglas Gregor - C++ Templates The Complete Guide (2017)


### Chapter 1 Function Templates
#### A first look at function template
1. Definition and Usage
    ```C++
    template <typename T>
    T max(T& a, T&b) {
        return a > b ? a : b
    }

    // usage 
    std::cout << "max value is: " << ::max(3, 5) << std::endl;
    ```
    * Use `::` to qualify `max()` to ensure this template is found in global namespace. (Avoid std::max() in standard library)
    * The keyword `typename` can be replaced by `class` which is prior to C++98 standard, but recommend to use the former.
    * Void is valid template argument provided the resulting code is valid.

2. Two-phase translation
    * Without instantiation as *definition time*, check the template code and ignoring the template parameter.
    * *Instantiation time*, check template code to ensure all code is valid.
        ```C++
        template <typename T>
        T foo(T t){
            undeclared(); // first-phase failed, if undeclared() unknown
            undeclared(t); // second-phase failed, if undeclared(t) unknown

            static_assert(sizeof(int) > 10, "error check"); // always failed as sizeof(int)<10
            static_assert(sizeof(T) > 10, "error check");  // depend size of T
        }
        ```
    * This two-phase translation leads to a problem that *a compiler need to see function template definition which has been called*. One solution is to **implement each template inside a header file**.