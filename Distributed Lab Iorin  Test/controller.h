#pragma once
#include"TrainLeg.h"
#include<vector>
#include<string>
#include<iostream>
#include<memory>
class Controller
{
public:
	Controller();
	~Controller();
	void Load(const char * _p );
	void makeMatrPrice();
	void DeikstraforPriceLess();
private:
	std::vector<std::unique_ptr<TrainLeg>> TrainLegs;
	double Matr[6][6];
};


