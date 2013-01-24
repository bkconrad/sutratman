#ifndef MATH_UTIL_H
#define MATH_UTIL_H

namespace mathutil {

   static const float PI = 3.141592654;
   static const float TAU = PI * 2.0;
   static const float EPSILON = 0.01;
   static const float DEGREES = 360.0;
   static const float RADIANS = TAU;

   float degreesToRadians(float d);
   float radiansToDegrees(float r);
}

#endif // MATH_UTIL_H
