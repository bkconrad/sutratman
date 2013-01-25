#ifndef MATHUTIL_H_
#define MATHUTIL_H_

namespace mathutil
{

static const float DEGREES = 360.0;
static const float EPSILON = 0.01;
static const float PI = 3.141592654;
static const float TAU = PI * 2.0;
static const float RADIANS = TAU;

float degreesToRadians(float d);
float radiansToDegrees(float r);
}

#endif /* MATHUTIL_H_ */
