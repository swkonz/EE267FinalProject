#include "TestPose.h"

bool testPose1() {

	uint32_t ticks[8] = {299750, 172100, 110930, 329410,0,0,0,0};
	double positions[8] = {0,0,0,0,0,0,0,0};

	convertTicksTo2DPositions( ticks,  positions);

	for(int i = 0; i < 8; i++) {
		Serial.printf("%f\n",positions[i] );
	}

  return true;

}

void testPoseMain() {

  Serial.printf("testing\n");
  Serial.printf("Testing CountTicks\n");
  testPose1();

}
