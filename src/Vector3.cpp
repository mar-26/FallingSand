#include "Vector3.h"

void Vector3::invert()
{
	x = -x;
	y = -y;
	z = -z;
}

void Vector3::normalize()
{
	float l = magnitude();
	if (l > 0)
	{
		(*this) *= ((float)1)/l;
	}
}

float Vector3::magnitude() const
{
	return sqrt(x*x + y*y + z*z);
}

void Vector3::addScaledVector(const Vector3& v, int scale)
{
	x += v.x * scale;
	y += v.y * scale;
	z += v.z * scale;
}

Vector3 Vector3::crossProduct(const Vector3& v) const
{
	return Vector3(y*v.z-z*v.y,
				   z*v.x-x*v.z,
				   x*v.y-y*v.x);
}

void Vector3::operator*=(const int scale)
{
	x *= scale;
	y *= scale;
	z *= scale;
}

void Vector3::operator+=(const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}

void Vector3::operator-=(const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

int Vector3::operator*(const Vector3& v) const
{
	return x*v.x + y*v.y + z*v.z;
}

Vector3 Vector3::operator*(const int scale) const
{
	return Vector3(x*scale, y*scale, z*scale);
}

Vector3 Vector3::operator+(const Vector3& v)
{
	return Vector3(x+v.x, y+v.y, z+v.z);
}

Vector3 Vector3::operator-(const Vector3& v)
{
	return Vector3(x-v.x, y-v.y, z-v.z);
}

std::ostream& operator<<(std::ostream& os, const Vector3& v)
{
	os << "<" << v.x << ", " << v.y << ", " << v.z << ">";
	return os;
}
