/**
File:
	CVector2.cpp

Author:
	Ethem Kurt (BigETI)
*/

#include "./sdk/CVector2.h"

const CVector2 CVector2::unit(1.0f, 1.0f);
const CVector2 CVector2::null(0.0f, 0.0f);
const CVector2 CVector2::up(0.0f, 1.0f);
const CVector2 CVector2::down(0.0f, -1.0f);
const CVector2 CVector2::left(-1.0f, 0.0f);
const CVector2 CVector2::right(1.0f, 0.0f);

CVector2::CVector2() : x(0.0f), y(0.0f)
{
	//
}

CVector2::CVector2(const CVector2 & v) : x(v.x), y(v.y)
{
	//
}

CVector2::CVector2(float_t _x, float_t _y) : x(_x), y(_y)
{
	//
}

CVector2::~CVector2()
{
	//
}

CVector2 & CVector2::operator=(const CVector2 & v)
{
	x = v.x;
	y = v.y;
	return (*this);
}

CVector2 & CVector2::operator+=(const CVector2 & v)
{
	x += v.x;
	y += v.y;
	return (*this);
}

CVector2 & CVector2::operator-=(const CVector2 & v)
{
	x -= v.x;
	y -= v.y;
	return (*this);
}

CVector2 & CVector2::operator*=(float_t s)
{
	x *= s;
	y *= s;
	return (*this);
}

CVector2 & CVector2::operator/=(float_t s)
{
	if (IS_FLOAT_ZERO(s))
		throw std::overflow_error("Division by zero");
	x /= s;
	y /= s;
	return (*this);
}

CVector2 CVector2::operator+(const CVector2 & v)
{
	return CVector2(*this) += v;
}

CVector2 CVector2::operator-(const CVector2 & v)
{
	return CVector2(*this) -= v;
}

float_t CVector2::operator*(const CVector2 & v)
{
	return (x * v.x) + (y * v.y);
}

CVector2 CVector2::operator*(float_t s)
{
	return CVector2(*this) *= s;
}

CVector2 CVector2::operator/(float_t s)
{
	return CVector2(*this) /= s;
}

bool CVector2::IsNull()
{
	return (IS_FLOAT_ZERO(x) && IS_FLOAT_ZERO(y));
}

float_t CVector2::MagnitudeSquared()
{
	return (x * x) + (y * y);
}

float_t CVector2::Magnitude()
{
	return SQRT(MagnitudeSquared());
}

void CVector2::SetMagnitude(float_t m)
{
	if (IsNull())
		throw std::overflow_error("Vector is null");
	else
	{
		float_t mag(Magnitude());
		x = (x * m) / mag;
		y = (x * m) / mag;
	}
}

bool CVector2::IsInRange(const CVector2 & p, float_t range)
{
	return MagnitudeSquared() <= (range * range);
}

CVector2 CVector2::SquareAngle()
{
	return CVector2(-y, x);
}

float_t CVector2::GetAngle(const CVector2 & v)
{
	return atan2(v.y, v.x) - atan2(x, y);
}

float_t CVector2::GetAngleDegrees(const CVector2 & v)
{
	return (GetAngle(v) * 180.0f) / PI;
}

void CVector2::Rotate(float_t radians)
{
	(*this) = CVector2((x * cos(radians)) - (y * sin(radians)), (x * sin(radians)) + (y * cos(radians)));
}

void CVector2::RotateDegrees(float_t degrees)
{
	Rotate((degrees * PI) / 180.0f);
}

void CVector2::Negate()
{
	x = -x;
	y = -y;
}
