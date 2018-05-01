/**LAB WEEK 7: VIEW CONTEXT
 * CS3210
 * @author Dennis Droese
 * @file viewcontext.h
 * @date April 25, 2018
 */

#ifndef VIEWCONTEXT_H_
#define VIEWCONTEXT_H_

#include "matrix.h"
//#include "image.h"
//#include "shape.h"
//#include "dynamicdraw.h"
#include <cmath>


#define MINIMUM_ALLOWED_SCALE 0.0000001


class viewcontext {
public:

	viewcontext();
	~viewcontext();

	matrix* convertFromCartesian(matrix* input);

	matrix* convertToCartesian(matrix* input);

	void translate(double x, double y, double z);

	void rotate(double roll, double pitch, double yaw);

	void scale(double x, double y, double z);

	void out();

	matrix applyTransform(matrix target);

	matrix applyInverse(matrix target);

private:

	matrix* transform;

	matrix* mTranslate;
	matrix* mRotate;
	matrix* mScale;

	matrix* inverse;

};




#endif /* VIEWCONTEXT_H_ */
