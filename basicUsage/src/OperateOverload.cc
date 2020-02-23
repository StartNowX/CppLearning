#include "OperateOverload.hpp"

Time::Time(){};

Time::Time(int h, int m){
    minutes = m;
    hours = h;
}

void Time::AddHour(int h){
    hours += h;
}

void Time::AddMin(int m){
    minutes += m;
    hours += (minutes / 60);
    minutes %= 60;
}

void Time::Reset(int h, int m){
    minutes = m;
    hours = h;
}

Time Time::operator+(const Time& t) const{
    Time tmpTime;
    tmpTime.minutes = minutes + t.minutes;
    tmpTime.hours = hours + (t.hours + tmpTime.minutes / 60);
    tmpTime.minutes %= 60;

    return tmpTime;
}

Time Time::operator-(const Time& t) const{
    Time tmpTime;
    int tmpM1, tmpM2;
    tmpM1 = hours * 60 + minutes;
    tmpM2 = t.hours * 60 + t.minutes;
    tmpTime.hours = (tmpM1 - tmpM2) / 60;
    tmpTime.minutes = (tmpM1 - tmpM2) % 60;
    return tmpTime;
}

Time Time::operator*(double n) const{
    Time tmpTime;
    long totalMins = hours * n * 60 + minutes * n;
    tmpTime.hours = totalMins / 60;
    tmpTime.minutes = totalMins % 60;
    return tmpTime;
}

std::ostream& operator<<(std::ostream& os, const Time& t){
    std::cout << t.hours << " hours " << t.minutes << " minutes";
    return os;
}


