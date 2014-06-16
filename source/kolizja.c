#include "biblioteki.h"

int Intersects(float x1, float y1, float x2, float y2, float halfSize) {
	int k = 0;

	float k1_Min_X = x1 - halfSize;
	float k1_Max_X = x1 + halfSize;
	float k1_Min_Y = y1 - halfSize;
	float k1_Max_Y = y1 + halfSize;
	float k2_Min_X = x2 - halfSize;
	float k2_Max_X = x2 + halfSize;
	float k2_Min_Y = y2 - halfSize;
	float k2_Max_Y = y2 + halfSize;

	if ((k1_Max_X >= k2_Min_X) &&
		(k1_Min_X <= k2_Max_X) &&
		(k1_Max_Y >= k2_Min_Y) &&
		(k1_Min_Y <= k2_Max_Y)) {
		k = 1;
	}

	return k;
}
