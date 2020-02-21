## Notes of *C++ Template*

> David Vandevoorde, Nicolai M. Josuttis, Douglas Gregor - C++ Templates The Complete Guide (2017)


### Chapter 1 Function Templates
#### A first look at function template
1. Definition and Usage
    ```C++
    template <typename T> // T: the template parameter
    T max(T& a, T&b) { // a&b: the call parameters
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

#### Template Argument Deduction
##### Type conversions during type deduction
1. Automatic type conversion are limited during type deduction,
    * declaring call parameters **by reference**, do not apply type conversion.
    * declaring call parameters **by value**, only type conversions that decay are supported.
    * two arguments declared with same template parameter T must match exactly.
        ```C++
        template <typename T>
        T foo(T a, T b);

        foo(4, 7.2); // error, T can be duduced as int or double
        std::string s;
        foo("string", s); // error, T can be duduced as char const[6] or std::string

        // solution 1
        foo(static_cast<double>4, 7.2); // cast the arguments
        // solution 2
        foo<double>(4, 7.2); // specify explicitly the type of T to prevent the compiler from attempting type deduction
        // solution 3
        template <typename T1, typename T2, typename RT> // RT cannot be deduced, see **Multiple template parameters**
        RT foo(T1 a, T2 b); // specify the template parameters have different types
        
        ```

##### Type conversion for default parameters
1. set a default argument for template parameter
    ```C++
    template <typename T = std::string>
    void foo(T = ""){}
    ```

##### Multiple template parameters
1. We can set as many as template parameter as we want. Such as:
    ```C++
    template <typename T1, typename T2>
    T1 foo(T1 a, T2 b){
        
    } // The return value type depend on T1
    ```
2. Solutions
    * Introduce a third template parameter as return value type
    * Let compiler to find the return value type
    * Declare the return type to be the “common type” of the two parameter types

3. **When there is not connection between template parameter and call parameter, the type deduction will not happen**
4. Solution 1: introduce a third template parameter as return value type
    * As the return type does not appear in the types of function call parameters, **The template argument deduction does not take return types into account**, the caller need to specify the template arguments explictly.
    * Specify only the first argument explicitly and to allow deduction process to derive the rest
        ```C++
        template <typename T1, typename T2, typename RT>
        RT foo(T1 a, T2 b){}

        // caller
        ::foo<double, int, double>(4, 7.2); // OK, but tedious


        template <typename RT, typename T1, typename T2>
        RT foo(T1 a, T2 b){}
        // caller
        ::foo<double>(4, 7.2); // T1 and T2 are deduced, but still not the best
        ```
5. Solution 2: Deducing the return type
    * Before C++ 14, must use **auto** and **trailing return type**.
        ```C++
        template <typename T1, typename T2>
        auto max(T1 a, T2 b) -> decltype(a>b?a:b) { // decltype(true?a:b) is enough
            return a > b ? a : b;
        }
        ```
    * drawback: **it will happen that the return type is a reference type**, as T might be a reference.
        ```C++
        #include <type_traits>

        template <typename T1, typename T2>
        auto max(T1 a, T2 b) -> typename std::decay<decltype(true?a:b)>::type { // member function *type* is a type, thus need use typename
            return a > b ? a : b;
        }
        ```
6. Solution 3: Return type as common type
    * Since C++11, the C++ standard library provide `std::common_type` to specify choosing "the more general type".
        ```C++
        #include <type_traits>

        // C++ 11
        template <typename T1, typename T2>
        typename std::common_type<T1, T2>::type max(T1 a, T2 b){
            return a > b ? a : b;
        }

        // C++ 14
        template <typename T1, typename T2>
        std::common_type_t<T1, T2> max(T1 a, T2 b){
            return a > b ? a : b;
        }
        ```

#### Default Template Arguments
1. Users can define default values for template parameters. The values are called default template argumments and can be used with any kind of template.
2. **The best and easiest solution is to let the compiler deduce the return type.**


#### Overloading Function Template
1. The overloaded resolution process prefer to nontemplate over one generated from template if all other factors are equal; And also, it will choose the better matched one.(little or no type conversion)
2. It's a good idea not to change more than necessary when overloading function templates.
    ```C++
    template <typename T1, typename T2>
    auto max(T1 a, T2 b){
        return a > b ? a : b;
    }

    template <typename RT, typename T1, typename T2>
    RT max(T1 a, T2 b){
        return a > b ? a : b;
    }

    // caller
    auto a = ::max(4, 7.2); // match first
    auto b = ::max<long double>(4, 7.2); // match second

    auto c = ::max<int>(4, 7.2); // error, ambiguity error
    ```

#### Advices
1. Passing value or reference? Passing value is in general better.
    * The syntax is simple
    * Compiler optimizes better
    * Move semantics often makes copies cheap
    * Sometimes there is no copy at all.
    * A template may be used for both complex and simple types, choosing the approach for complex types may be counterproductive for simple types
    * The caller can still decide to pass arguments by reference
    * Although passing string literals or raw arrays always can become a problem, passing them by reference often become the bigger problem

2. Why not inline?
    * In general, function template don't have to be declared with inline.(As noninline function template can be **defined** in header file and be included in multiple tanslation unit, but noninline oridinary function cannot)
    * The keyword *inline* is just a request, but not command. And **the compiler are better at deciding whether the function should be "expanded inline".**

3. Why not constexpr?
    * Since C++11, we can use **constexpr** to provide the ability to use code to compute some values in compile time.
        ```C++
        template <typename T1, typename T2>
        constexpr auto max(T1 a, T2 b){
            return a > b ? a : b;
        }

        // call
        int a[::max(sizeof(char), 1000u)];
        ```
    * Here skip it for focusing on fundamentals.


### Chapter 2 Class Templates

#### Declaration&Implementation of Class Templates
1. Before declaration, you have to declare one or more identifiers as type parameters.(Similar to function template)
2. It's better to using class not followed by template arguments inside a class, which denotes the class with its template parameters as its arguments. But outside, must use full type qualification of class template.
    * As ususlly <T> signals special handling of special template parameters.
        ```C++
        template <typename T>
        class Stack{
            ...
            Stack(Stack const &); // copy constructor
            Stack& operator=(Stack const&); // assignment operator
            ...
        };
        ```

3. **Unlike nontemplate classes, class template must not be declared or defined inside function or block scope**. In general, template can only be defined in global/namespace scope or inside class declarations.
