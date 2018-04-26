/**LAB WEEK 7: VIEW CONTEXT
 * CS3210
 * @author Dennis Droese
 * @file viewcontext.cpp
 * @date April 25, 2018
 */

#include "viewcontext.h"


void updateInverse();


viewcontext::viewcontext(){
	transform = new matrix(4,4);
	*transform = matrix::identity(4);
	inverse = new matrix(4,4);
	*inverse = matrix::identity(4);
}

viewcontext::~viewcontext(){
	delete transform;
	delete inverse;
}

matrix* viewcontext::convertFromCartesian(matrix* input){
	//TODO
	return input;
}

matrix* viewcontext::convertToCartesian(matrix* input){
	//TODO
	return input;
}

// Rotation matrix
// [ cos(roll)	-sin(roll)	0	0 |
// | sin(roll)	cos(roll)	0	0 |
// | 0			0			1	0 |
// | 0			0			0	1 ]
void viewcontext::rotate(double roll, double pitch, double yaw){
	//TODO

	matrix rotato = matrix::identity(4);

	matrix rotatoInverse = matrix::identity(4);

	// convert degrees to radians.
	double radRoll = 	roll * (M_PI/180);
	//double radPitch = 	roll * (M_PI/180);
	//double radYaw = 	roll * (M_PI/180);

	rotato[0][0] = cos(radRoll);
	rotato[0][1] = -sin(radRoll);
	rotato[1][0] = sin(radRoll);
	rotato[1][1] = cos(radRoll);

	rotatoInverse[0][0] = cos(-radRoll);
	rotatoInverse[0][1] = -sin(-radRoll);
	rotatoInverse[1][0] = sin(-radRoll);
	rotatoInverse[1][1] = cos(-radRoll);

	*transform = rotato * *transform;
	*inverse =   rotatoInverse * *inverse;
}

// Scaling matrix
// [ X 0 0 0 |
// | 0 Y 0 0 |
// | 0 0 Z 0 |
// | 0 0 0 1 ]
void viewcontext::scale(double x, double y, double z){
	//TODO



	matrix scaler = matrix::identity(4);
	matrix scalerInverse = matrix::identity(4);


	if(x == 0.0){
		//scaler[0][0] = MINIMUM_ALLOWED_SCALE;
	} else {
		scaler[0][0] = x;
		scalerInverse[0][0] = 1.0/x;
	}

	if(y == 0.0){
		//scaler[1][1] = MINIMUM_ALLOWED_SCALE;
	} else {
		scaler[1][1] = y;
		scalerInverse[1][1] = 1.0/y;
	}

	if(z == 0.0){
		//scaler[2][2] = MINIMUM_ALLOWED_SCALE;
	} else {
		scaler[2][2] = z;
		scalerInverse[2][2] = 1.0/z;
	}

	*transform = *transform * scaler;
	*inverse = *inverse * scalerInverse;
}

// Translation matrix
// [ 1 0 0 X |
// | 0 1 0 Y |
// | 0 0 1 Z |
// | 0 0 0 1 |
void viewcontext::translate(double x, double y, double z){
	//TODO

//	matrix translator(4,4);
//	matrix translatorInverse(4,4);
	matrix translator = matrix::identity(4);
	matrix translatorInverse = matrix::identity(4);

	translator[0][3] = x;
	translator[1][3] = y;
	translator[2][3] = z;

	translatorInverse[0][3] = -x;
	translatorInverse[1][3] = -y;
	translatorInverse[2][3] = -z;

	*transform = translator * *transform;

	*inverse = translatorInverse * *inverse;

}

void viewcontext::out(){
	std::cout << *transform;
}

matrix viewcontext::applyTransform(matrix target){
	return *transform * target;
}

matrix viewcontext::applyInverse(matrix target){
	return *inverse * target;
}


/// private "Helper" Functions


void updateInverse(){




}
