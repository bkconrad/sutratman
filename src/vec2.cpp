#include "vec2.h"

#include <cmath>

using namespace std;

const float Vec2::EPSILON = .001;
const float Vec2::PI = 3.141592654; // How many digits do you really need?
const float Vec2::TAU = Vec2::PI * 2.0;

Vec2::Vec2() : x(0), y(0) { }
Vec2::Vec2(float x, float y) : x(x), y(y) { }
/** @brief copy constructor */
Vec2::Vec2(const Vec2& v) : x(v.x), y(v.y) { }

const Vec2 Vec2::operator+(const Vec2& v) const
{
   return Vec2(x + v.x, y + v.y);
}

const Vec2& Vec2::operator=(const Vec2& v) {
   x = v.x;
   y = v.y;
   return *this;
}

const Vec2& Vec2::operator+=(const Vec2& v) {
   x += v.x;
   y += v.y;
   return *this;
}

/** @brief operator*=
  *
  * @todo: document this function
  */
const Vec2 & Vec2::operator*=(float k)
{
   x *= k;
   y *= k;
   return *this;
}

/** @brief operator*
  *
  * @todo: document this function
  */
const Vec2 Vec2::operator*(float k) const
{
   return Vec2(x * k, y * k);
}


bool Vec2::operator==(const Vec2& v)
{
   return abs(x - v.x) < EPSILON && abs(y - v.y) < EPSILON;
}

/** @brief Performs fmod(element, k) for each element of the vector
  */
void Vec2::mod(float k)
{
   x = fmod(x, k);
   y = fmod(y, k);
}

void Vec2::set(float x, float y) {
   this->x = x;
   this->y = y;
}

/** @brief setAngle
set the angle of this vector (also sets magnitude to 1.0)
  */
void Vec2::setAngle(float angle)
{
   x = cos(angle) * (angle > Vec2::PI ? -1.0 : 1.0);
   y = sin(angle) * (angle > Vec2::PI ? -1.0 : 1.0);
}

/** @brief getAngle
  */
float Vec2::getAngle()
{
   return atan2(y, x);
}
/** @brief operator-=
  *
  * @todo: document this function
  */
const Vec2 & Vec2::operator-=(const Vec2& v)
{
   x -= v.x;
   y -= v.y;
   return *this;
}

/** @brief operator-
  *
  * @todo: document this function
  */
const Vec2 Vec2::operator-(const Vec2& v) const
{
   return Vec2(x - v.x, y - v.y);
}
