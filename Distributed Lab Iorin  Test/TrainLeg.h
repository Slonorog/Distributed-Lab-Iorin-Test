#pragma once
#include "Time.h"
class TrainLeg
{
public:
	TrainLeg(int _id, int _DSid,
		int _ASid, double _p,Time _DTS, Time _ATS);
	~TrainLeg(){}

	//<TrainLeg TrainId = "910" DepartureStationId = "1929"  ArrivalStationId = "1909" 
	//Price = "1790.87" ArrivalTimeString = "10:01:00" ArrivalTimeString = "01:00:00"></TrainLeg> 
	int TrainId;
	int DepartureStationId;
	int ArrivalStationId;
	double Price;
	Time DepartureTimeString;
	Time ArrivalTimeString;
	
};

