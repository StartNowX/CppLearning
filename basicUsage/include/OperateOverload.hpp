#ifndef OPERATE_OVERLOAD_HPP
#define OPERATE_OVERLOAD_HPP

#include <iostream>

class Time{
private:
    int hours;
    int minutes;

public:
    Time();
    Time(int h, int m = 0);
    void AddHour(int h);
    void AddMin(int m);
    void Reset(int h, int m);

    Time operator+(const Time& t) const;
    Time operator-(const Time& t) const;
    Time operator*(double n) const;

    friend Time operator*(double m, const Time& t){
        return t * m;
    };

    friend std::ostream& operator<<(std::ostream& os, const Time& t);

};// class Test


#endif
