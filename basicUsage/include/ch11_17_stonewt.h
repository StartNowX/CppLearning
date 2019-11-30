#pragma once
#ifndef STONE_WT_H_
#define STONE_WT_H_

class Stonewt {
private:
	enum { Lbs_per_stn = 14 };
	int stone;
	double pds_left;  // fractional pounds
	double pounds; // entire weight in pounds

public:
	Stonewt(double lbs);
	Stonewt(int stn, double lbs);
	Stonewt();
	~Stonewt();

	void show_lbs() const;
	void show_stn() const;

	// 转换函数
	// 也可以将转换符声明为显示的，explicit
	operator int() const;
	operator double() const;
};




#endif // STONE_WT_H
