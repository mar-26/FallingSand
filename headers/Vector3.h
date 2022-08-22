#ifndef VECTOR3_H
#define VECTOR3_H

#include <math.h>
#include <iostream>

class Vector3
{
	public:
		int x, y, z;

		Vector3() : x(0), y(0), z(0) {}
		Vector3(int x, int y, int z) : x(x), y(y), z(z) {}

		void invert();
		void normalize();
		float magnitude() const;
		void addScaledVector(const Vector3& v, int scale);
		Vector3 crossProduct(const Vector3& v) const;

		void operator*=(const int scale);
		void operator+=(const Vector3& v);
		void operator-=(const Vector3& v);

		int operator*(const Vector3& v) const;
		Vector3 operator*(const int scale) const;
		Vector3 operator+(const Vector3& v);
		Vector3 operator-(const Vector3& v);
		friend std::ostream& operator<<(std::ostream& os, const Vector3& v);
};

#endif
