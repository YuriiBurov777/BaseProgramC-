#include "DLLR.h"

void DinLR::AirCarpet::calculateTime(double distance) {

	if (distance < 1000) {
		_distance = distance / speed;
	}
	if (distance >= 1000 && distance < 5000) {
		_distance = ((distance * 0.97) / speed);
	}
	if (distance >= 5000 && distance < 10000) {
		_distance = ((distance * 0.9) / speed);
	}
	if (distance >= 10000) {
		_distance = ((distance * 0.95) / speed);
	}
}