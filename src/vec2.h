#ifndef VEC2_H
#define VEC2_H

/**
A 2D vector class with math utilities and operator overloads

There are three ways to assign to a Vec2:
Direct member assignment:
Vec2 v;
v.x = 1.0;
v.y = 0.0;

Assignment from another vector:
Vec2 a;
Vec2 b(1.0, 2.0);
a = b;

Calling the set function:
Vec2 v;
v.set(1.0, 0.0);

*/
class Vec2
{
   public:
      static const float EPSILON; // for comparing floats
      static const float PI;
      static const float TAU; // 2 * PI. For more info see http://tauday.com/
      float x, y;

      Vec2();
      Vec2(float x, float y);
      Vec2(const Vec2& v);

      const Vec2 operator*(const float k) const;
      const Vec2& operator*=(const float k);
      const Vec2 operator+(const Vec2& v) const;
      const Vec2& operator+=(const Vec2& v);
      const Vec2 operator-(const Vec2& v) const;
      const Vec2& operator-=(const Vec2& v);
      const Vec2& operator=(const Vec2& v);
      bool operator==(const Vec2& v);

      float getAngle();

      // mutators
      void normalize();
      void setAngle(float angle);
      void set(float x, float y);
      void mod(float k);
};

#endif // VEC2_H
