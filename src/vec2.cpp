#include "vec2.h"

#include <cmath>

using namespace std;

float Vec2::EPSILON = .001;

Vec2::Vec2() : x(0), y(0) { }
Vec2::Vec2(float x, float y) : x(x), y(y) { }
/** @brief copy constructor */
Vec2::Vec2(const Vec2& v) : x(v.x), y(v.y) { }

Vec2& Vec2::operator=(const Vec2& v) {
   x = v.x;
   y = v.y;
}

bool Vec2::operator==(const Vec2& v)
{
   return abs(x - v.x) < EPSILON && abs(y - v.y) < EPSILON;
}

void Vec2::set(float x, float y) {
   this->x = x;
   this->y = y;
}
