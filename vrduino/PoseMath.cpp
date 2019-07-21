#include "PoseMath.h"

/**
 * TODO: see header file for documentation
 */
void convertTicksTo2DPositions(uint32_t clockTicks[8], double pos2D[8])
{
 	//use variable CLOCKS_PER_SECOND defined in PoseMath.h
 	//for number of clock ticks a second

	// elevation angles
	uint32_t curTicks;
	double deltaT, angle;
	for (int i = 0; i < 8; i+=2) {
		// horizontal sweep
		curTicks = clockTicks[i];
		deltaT = (double)curTicks / (double)CLOCKS_PER_SECOND;

		angle = ( (-1 * deltaT ) / (1.0/60.0/360.0)) + 90;
		pos2D[i] = tan(angle * (2.0*PI/360.0));

		// vertical oriented sweep
		curTicks = clockTicks[i+1];
		deltaT = (double)curTicks / (double)CLOCKS_PER_SECOND;

		angle = ( (deltaT ) / (1.0/60.0/360.0)) - 90;
		pos2D[i+1] = tan(angle * (2.0*PI/360.0));
	}

}

/**
 * TODO: see header file for documentation
 */
void formA(double pos2D[8], double posRef[8], double Aout[8][8]) {
	// can get rid of setting all 0 locations since initialized to 0

	// first 2 rows
	Aout[0][0] = Aout[1][3] = posRef[0];
	Aout[0][1] = Aout[1][4] = posRef[1];
	Aout[0][2] = Aout[1][5] = 1.0;
	Aout[0][3] = Aout[0][4] = Aout[0][5] = Aout[1][0] = Aout[1][1] = Aout[1][2] = 0.0;
	Aout[0][6] = -1.0 * posRef[0] * pos2D[0];			// -x1*x1_n
	Aout[0][7] = -1.0 * posRef[1] * pos2D[0];			// -y1*x1_n
	Aout[1][6] = -1.0 * posRef[0] * pos2D[1];			// -x1*y1_n
	Aout[1][7] = -1.0 * posRef[1] * pos2D[1];			// -y1*y1_n

	// second 2 rows
	Aout[2][0] = Aout[3][3] = posRef[2];
	Aout[2][1] = Aout[3][4] = posRef[3];
	Aout[2][2] = Aout[3][5] = 1.0;
	Aout[2][3] = Aout[2][4] = Aout[2][5] = Aout[3][0] = Aout[3][1] = Aout[3][2] = 0.0;
	Aout[2][6] = -1.0 * posRef[2] * pos2D[2];			// -x2*x2_n
	Aout[2][7] = -1.0 * posRef[3] * pos2D[2];			// -y2*x2_n
	Aout[3][6] = -1.0 * posRef[2] * pos2D[3];			// -x2*y2_n
	Aout[3][7] = -1.0 * posRef[3] * pos2D[3];			// -y2*y2_n

	// third 2 rows
	Aout[4][0] = Aout[5][3] = posRef[4];
	Aout[4][1] = Aout[5][4] = posRef[5];
	Aout[4][2] = Aout[5][5] = 1.0;
	Aout[4][3] = Aout[4][4] = Aout[4][5] = Aout[5][0] = Aout[5][1] = Aout[5][2] = 0.0;
	Aout[4][6] = -1.0 * posRef[4] * pos2D[4];			// -x3*x3_n
	Aout[4][7] = -1.0 * posRef[5] * pos2D[4];			// -y3*x3_n
	Aout[5][6] = -1.0 * posRef[4] * pos2D[5];			// -x3*y3_n
	Aout[5][7] = -1.0 * posRef[5] * pos2D[5];			// -y3*y3_n

	// last 2 rows
	Aout[6][0] = Aout[7][3] = posRef[6];
	Aout[6][1] = Aout[7][4] = posRef[7];
	Aout[6][2] = Aout[7][5] = 1.0;
	Aout[6][3] = Aout[6][4] = Aout[6][5] = Aout[7][0] = Aout[7][1] = Aout[7][2] = 0.0;
	Aout[6][6] = -1.0 * posRef[6] * pos2D[6];			// -x4*x4_n
	Aout[6][7] = -1.0 * posRef[7] * pos2D[6];			// -y4*x4_n
	Aout[7][6] = -1.0 * posRef[6] * pos2D[7];			// -x4*y4_n
	Aout[7][7] = -1.0 * posRef[7] * pos2D[7];			// -y4*y4_n

}


/**
 * TODO: see header file for documentation
 */
bool solveForH(double A[8][8], double b[8], double hOut[8]) {
  	//use Matrix Math library for matrix operations
  	//example:
  	//int inv = Matrix.Invert((double*)A, 8);
  	//if inverse fails (Invert returns 0), return false 

	int res = Matrix.Invert((double*)A, 8);
	if ( res == 0 ) {
		return false;
	}

	Matrix.Multiply((double*) A, (double*) b, 8, 8, 1, (double*) hOut);
  
  	return true;

}


/**
 * TODO: see header file for documentation
 */
void getRtFromH(double h[8], double ROut[3][3], double pos3DOut[3]) {

	double s = 2 / (sqrt(pow(h[0], 2) + pow(h[3], 2) + pow(h[6], 2)) + sqrt(pow(h[1], 2) + pow(h[4], 2) + pow(h[7], 2)));
	pos3DOut[0] = s * h[2];
	pos3DOut[1] = s * h[5];
	pos3DOut[2] = -1.0 * s;

	// get rotation matrix
	double r1_len = sqrt(pow(h[0], 2) + pow(h[3], 2) + pow(h[6], 2));
	double r1[3] = {h[0] / r1_len, h[3] / r1_len, -1*h[6]/r1_len};

	double r2_tild[3] = {
		h[1] - (r1[0]*(r1[0]*h[1] + r1[1]*h[4] - r1[2]*h[7])),
		h[4] - (r1[1]*(r1[0]*h[1] + r1[1]*h[4] - r1[2]*h[7])),
		-1*h[7] - (r1[2]*(r1[0]*h[1] + r1[1]*h[4] - r1[2]*h[7]))
	};

	double r2_tild_len = sqrt(pow(r2_tild[0], 2) + pow(r2_tild[1], 2) + pow(r2_tild[2], 2));
	double r2[3] = {r2_tild[0]/r2_tild_len, r2_tild[1]/r2_tild_len, r2_tild[2]/r2_tild_len};

	double r3[3] = {r1[1]*r2[2] - r1[2]*r2[1],
					r1[2]*r2[0] - r1[0]*r2[2],
					r1[0]*r2[1] - r1[1]*r2[0] };
	double r3_len = sqrt(pow(r3[0], 2) + pow(r3[1], 2) + pow(r3[2], 2));

	ROut[0][0] = r1[0];
	ROut[1][0] = r1[1];
	ROut[2][0] = r1[2];
	ROut[0][1] = r2[0];
	ROut[1][1] = r2[1];
	ROut[2][1] = r2[2];
	ROut[0][2] = r3[0] / r3_len;
	ROut[1][2] = r3[1] / r3_len;
	ROut[2][2] = r3[2] / r3_len;

}



/**
 * TODO: see header file for documentation
 */
Quaternion getQuaternionFromRotationMatrix(double R[3][3]) {

	double qw = sqrt(1 + R[0][0] + R[1][1] + R[2][2]) / 2;
	double qx = (R[2][1] - R[1][2])/ (4*qw);
	double qy = (R[0][2] - R[2][0]) / (4*qw);
	double qz = (R[1][0] - R[0][1]) / (4*qw);

  return Quaternion(qw, qx, qy, qz).normalize();

}
