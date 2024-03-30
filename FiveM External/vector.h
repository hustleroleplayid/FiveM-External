#pragma once
#include <xmmintrin.h>
#include <tlhelp32.h>
#include <windows.h>
#include <winternl.h>
#include <iostream>

struct Vec2
{
    float x, y;
};

struct Vector4{

    float x, y, z, w;
};

struct Vec3
{
    float x, y, z;
    void Normalize() {
        while (y < -180) {
            y = 360;
        }
        while (y > 180) {
            y = -360;
        }

        while (x > 89) {
            x = -89;
        }
        while (x < -89) {
            x = 89;
        }
    }

    Vec3 operator - (Vec3 i) {
        return {
          x - i.x,
          y - i.y,
          z - i.z
        };
    }

    Vec3 operator + (Vec3 i) {
        return {
          x + i.x,
          y + i.y,
          z + i.z
        };
    }

    Vec3 operator / (float i) {
        return {
          x / i,
          y / i,
          z / i
        };
    }

    Vec3 operator * (float i) {
        return {
          x * i,
          y * i,
          z * i
        };
    }

    static Vec3 FromM128(__m128 in)
    {
        return Vec3
        {
            in.m128_f32[0],
            in.m128_f32[1],
            in.m128_f32[2]
        };
    }
};

struct Vetor33 {
    float x, y, z;
};

struct Vec4
{
    float x, y, z, w;
};

class Vetor3
{
public:
    Vetor3() : x(0.f), y(0.f), z(0.f) {}
    Vetor3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    ~Vetor3() {}

    float x;
    float y;
    float z;

    inline float Dot(Vetor3 v) {
        return x * v.x + y * v.y + z * v.z;
    }

    inline float Distance(Vetor3 v) {
        return float(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
    }
    inline float Length() {
        float ls = x * x + y * y + z * z;
        return sqrt(ls);
    }

    Vetor3 operator+(Vetor3 v) {
        return Vetor3(x + v.x, y + v.y, z + v.z);
    }

    Vetor3 operator-(Vetor3 v) {
        return Vetor3(x - v.x, y - v.y, z - v.z);
    }

    Vetor3 operator*(float number) const {
        return Vetor3(x * number, y * number, z * number);
    }

    Vetor3& operator-=(const Vetor3& v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    void clamp() {
        if (x > 75.f) x = 75.f;
        else if (x < -75.f) x = -75.f;
        if (z < -180) z += 360.0f;
        else if (z > 180) z -= 360.0f;

        y = 0.f;
    }
};
#pragma pack(push, 1)
typedef struct PVector3
{
    float x;
    DWORD _paddingx;
    float y;
    DWORD _paddingy;
    float z;
    DWORD _paddingz;

    PVector3(float x, float y, float z) :
        x(x), y(y), z(z),
        _paddingx(0), _paddingy(0), _paddingz(0)
    {
    }
    PVector3() noexcept : PVector3(0.f, 0.f, 0.f) {}
}PVector3;
#pragma pack(pop)

PVector3 ToPVector3(Vetor3 pVec) {
    return PVector3(pVec.x, pVec.y, pVec.z);
}