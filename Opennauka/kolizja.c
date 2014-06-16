#include "biblioteki.h"

int Intersects(float x1, float y1, float x2, float y2) {
    int k;
	float k1_Min_X = x1 - 5;
	float k1_Max_X = x1 + 5;
	float k1_Min_Y = y1 - 5;
	float k1_Max_Y = y1 + 5;
	float k2_Min_X = x2 - 5;
	float k2_Max_X = x2 + 5;
	float k2_Min_Y = y2 - 5;
	float k2_Max_Y = y2 + 5;
    if ((k1_Max_X < k2_Min_X) || (k1_Min_X > k2_Max_X)) {
		return k=0;
	} else if((k1_Max_Y < k2_Min_Y) || (k1_Min_Y > k2_Max_Y)){
        return k=1;
    }
}
