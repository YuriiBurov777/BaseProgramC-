#include "DLLR.h"

void DinLR::CamelSpeed::calculateTime(double distance) {

	int value{ 0 };
	value = static_cast<int> (distance / speed) / time_move;

	if (value == 0) {
		_distance = distance / speed;
	}
	if (value == 1) {
		_distance = (pausa1 + (distance / speed));
	}
	if (value >= 2) {
		_distance = (pausa1 + pausa2 + (distance / speed) + (pausa2 * (value - 2)));
	}

}