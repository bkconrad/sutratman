#include "mathutil.h"

namespace mathutil
{
float degreesToRadians(float d)
{
    return d * RADIANS / DEGREES;
};

float radiansToDegrees(float r)
{
    return r * DEGREES / RADIANS;
};
}
