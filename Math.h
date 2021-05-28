#pragma once
#include <cmath>
#include <vector>

constexpr float PI     = 3.14159265358F;
constexpr float TWOPI  = 6.28318530717F;
constexpr float HALFPI = 1.57079632679F;
constexpr float E      = 2.71828182845F;
#define SQR(x) ((x)*(x))




struct float2
{
  float2() :x(0), y(0) {}
  float2(float a, float b) : x(a), y(b) {}

  float x, y;
};

struct float3
{
  float3() :x(0), y(0), z(0) {}
  float3(float a, float b, float c) : x(a), y(b), z(c) {}
  float3(const float* ptr) : x(ptr[0]), y(ptr[1]), z(ptr[0]) {}

  float x, y, z;
};

struct float4
{
  float4() : x(0), y(0), z(0), w(0) {}
  float4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}
  explicit float4(float a[4]) : x(a[0]), y(a[1]), z(a[2]), w(a[3]) {}

  float x, y, z, w;
};

static inline float4 make_float4(float a, float b, float c, float d) { return float4(a, b, c, d); }
static inline float4 make_float4_1(float a) { return float4(a, a, a, a); }
static inline float3 make_float3(float a, float b, float c) { return float3(a, b, c); }
static inline float3 make_float3(float4 f4) { return float3(f4.x, f4.y, f4.z); }
static inline float2 make_float2(float a, float b) { return float2(a, b); }

static inline float2 to_float2(float4 v) { return make_float2(v.x, v.y); }
static inline float2 to_float2(float3 v) { return make_float2(v.x, v.y); }
static inline float3 to_float3(float4 v) { return make_float3(v.x, v.y, v.z); }
static inline float4 to_float4(float3 v, float w) { return make_float4(v.x, v.y, v.z, w); }


//**********************************************************************************
// float3 operators and functions
//**********************************************************************************
static inline float3 operator * (const float3 & u, float v) { return make_float3(u.x * v, u.y * v, u.z * v); }
static inline float3 operator / (const float3 & u, float v) { return make_float3(u.x / v, u.y / v, u.z / v); }
static inline float3 operator + (const float3 & u, float v) { return make_float3(u.x + v, u.y + v, u.z + v); }
static inline float3 operator - (const float3 & u, float v) { return make_float3(u.x - v, u.y - v, u.z - v); }
static inline float3 operator * (float v, const float3 & u) { return make_float3(v * u.x, v * u.y, v * u.z); }
static inline float3 operator / (float v, const float3 & u) { return make_float3(v / u.x, v / u.y, v / u.z); }
static inline float3 operator + (float v, const float3 & u) { return make_float3(u.x + v, u.y + v, u.z + v); }
static inline float3 operator - (float v, const float3 & u) { return make_float3(u.x - v, u.y - v, u.z - v); }

static inline float3 operator + (const float3 & u, const float3 & v) { return make_float3(u.x + v.x, u.y + v.y, u.z + v.z); }
static inline float3 operator - (const float3 & u, const float3 & v) { return make_float3(u.x - v.x, u.y - v.y, u.z - v.z); }
static inline float3 operator * (const float3 & u, const float3 & v) { return make_float3(u.x * v.x, u.y * v.y, u.z * v.z); }
static inline float3 operator / (const float3 & u, const float3 & v) { return make_float3(u.x / v.x, u.y / v.y, u.z / v.z); }

static inline float3 operator - (const float3 & u) { return make_float3(-u.x, -u.y, -u.z); }

static inline float3 & operator += (float3 & u, const float3 & v) { u.x += v.x; u.y += v.y; u.z += v.z; return u; }
static inline float3 & operator -= (float3 & u, const float3 & v) { u.x -= v.x; u.y -= v.y; u.z -= v.z; return u; }
static inline float3 & operator *= (float3 & u, const float3 & v) { u.x *= v.x; u.y *= v.y; u.z *= v.z; return u; }
static inline float3 & operator /= (float3 & u, const float3 & v) { u.x /= v.x; u.y /= v.y; u.z /= v.z; return u; }

static inline float3 & operator += (float3 & u, float v) { u.x += v; u.y += v; u.z += v; return u; }
static inline float3 & operator -= (float3 & u, float v) { u.x -= v; u.y -= v; u.z -= v; return u; }
static inline float3 & operator *= (float3 & u, float v) { u.x *= v; u.y *= v; u.z *= v; return u; }
static inline float3 & operator /= (float3 & u, float v) { u.x /= v; u.y /= v; u.z /= v; return u; }

static inline float  length(const float3 & u) { return sqrtf(SQR(u.x) + SQR(u.y) + SQR(u.z)); }
static inline float3 normalize(const float3 & u) { return u / length(u); }



struct point2
{
  float x;
  float y;

  point2() { x = 0.0f; y = 0.0f; }
  point2(float x1, float y1) { x = x1; y = y1; }

  friend bool operator == (const point2 a, const point2 b) { return (a.x == b.x && a.y == b.y); }
  //point2& operator = (const point2& p) { x = p.x; y = p.y; }
};


struct point3
{
  float x;
  float y;
  float z;

  point3() { x = 0.0f; y = 0.0f; z = 0.0f; }
  point3(float x1, float y1, float z1) { x = x1; y = y1; z = z1;}
};


struct vec2
{
  float x;
  float y;

  vec2() { x = 0.0f; y = 0.0f; }
  vec2(float x1, float y1) { x = x1; y = y1; }

};


struct vec3 // simple 3D vector class
{
  vec3(const float xx, const float yy, const float zz) : x(xx), y(yy), z(zz) {}  
  
  inline vec3  operator + (const vec3 t)       { return vec3(x + t.x, y + t.y, z + t.z); }
  inline vec3  operator - (const vec3 t)       { return vec3(x - t.x, y - t.y, z - t.z); }
  inline vec3  operator * (const float t)      { return vec3(x * t, y * t, z * t); }        // dot product    
  inline float operator * (const vec3 t) const { return x * t.x + y * t.y + z * t.z; }      // scalar product    
  inline vec3  operator ^ (const vec3 t)       { return vec3(y * t.z - z * t.y, t.x * z - x * t.z, x * t.y - y * t.x); } // cross product
  inline float length()                  const { return sqrt(x * x + y * y + z * z); }      // pythagorean length
  inline bool  zero()                    const { return x == 0 && y == 0 && z == 0; }       // returns true if a zero vector    
  inline bool  equals(vec3 t)            const { return x == t.x && y == t.y && z == t.z; } // returns true if exactly equal
  inline vec3  unit() // normalized to a length of 1
  {
    float l = length();    
    if (l == 0.0) 
      return vec3(0.0, 0.0, 0.0);
    else
      return vec3(x / l, y / l, z / l);
  }

  float x = 0.0F;
  float y = 0.0F;
  float z = 0.0F;
};


float Distance(point2 a, point2 b);
void  SimpleCompress(float3 &outColor);
void  Clamp(float3 &outColor);
void  ClampMinMax(float &a);

float dot(const vec2 & u, const vec2 & v); 
vec2  VectorFromPoint(const point2 & a, const point2 & b);
vec2  NormalToVect(const vec2 & a);


