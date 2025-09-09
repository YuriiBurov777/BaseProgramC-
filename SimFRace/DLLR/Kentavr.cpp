#include "DLLR.h"

void DinLR::Kentavr::calculateTime(double distance) {

	int value{ 0 };
	value = static_cast<int> (distance / speed) / time_move;

	_distance = ((pausa1 * (value)) + (distance / speed));

}