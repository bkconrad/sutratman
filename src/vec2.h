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
      static float EPSILON; // for comparing floats
      float x, y;

      Vec2();
      Vec2(float x, float y);
      Vec2(const Vec2& v);

      Vec2& operator=(const Vec2& v);
      bool operator==(const Vec2& v);

      void set(float x, float y);
};

#endif // VEC2_H
