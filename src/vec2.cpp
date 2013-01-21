#include "vec2.h"

Vec2::Vec2() : x(0), y(0) { }
Vec2::Vec2(float x, float y) : x(x), y(y) { }
/** @brief copy constructor */
Vec2::Vec2(const Vec2& v) : x(v.x), y(v.y) { }

Vec2& Vec2::operator=(Vec2& v) {
   x = v.x;
   y = v.y;
}

void Vec2::set(float x, float y) {
   this->x = x;
   this->y = y;
}
