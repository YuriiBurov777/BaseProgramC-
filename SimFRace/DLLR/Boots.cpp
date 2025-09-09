#include "DLLR.h"

void DinLR::Boots::calculateTime(double distance) {

	int value{ 0 };
	value = static_cast<int> (distance / speed) / time_move;

	if (value == 0) {
		_distance = distance / speed;
	}
	if (value >= 1) {
		_distance = (pausa1 + (distance / speed) + (pausa2 * (value - 1)));
	}

}