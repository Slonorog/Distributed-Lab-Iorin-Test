#include "TrainLeg.h"



TrainLeg::TrainLeg(int _id, int _DSid, int _ASid, double _p, Time _DTS, Time _ATS) :
	TrainId(_id), DepartureStationId(_DSid), ArrivalStationId(_ASid),
	Price(_p), DepartureTimeString(_DTS), ArrivalTimeString(_ATS)
{

}

