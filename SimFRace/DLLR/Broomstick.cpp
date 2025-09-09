#include "DLLR.h"

void DinLR::Broomstick::calculateTime(double distance) {

	double value{ 0 };
	value = static_cast<double>(static_cast <int>(distance / 1000.0));

	_distance = (distance * (1.0 - (value / 100)) / speed);

}