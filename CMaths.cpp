#include "FiveMP.h"

static float_t Math::WrapAround(float_t fValue, float_t fHigh)
{
	return fValue - (fHigh * floor((float_t)(fValue / fHigh)));
}

static float_t Math::ConvertRadiansToDegrees(float_t fRotation)
{
	return Math::WrapAround((fRotation * 180.0f / (float_t)PI + 360.0f), 360.0f);
}

static CVector3 Math::ConvertRadiansToDegrees(const CVector3 &vecRotation)
{
	return CVector3(Math::ConvertRadiansToDegrees(vecRotation.x),
		Math::ConvertRadiansToDegrees(vecRotation.y),
		Math::ConvertRadiansToDegrees(vecRotation.z));
}

static float_t Math::ConvertDegreesToRadians(float_t fRotation)
{
	return Math::WrapAround((fRotation * (float_t)PI / 180.0f + 2 * (float_t)PI), (float_t)DOUBLE_PI);
}

static CVector3 Math::ConvertDegreesToRadians(const CVector3 &vecRotation)
{
	return CVector3(Math::ConvertDegreesToRadians(vecRotation.x),
		Math::ConvertDegreesToRadians(vecRotation.y),
		Math::ConvertDegreesToRadians(vecRotation.z));
}

static float_t Math::GetOffsetDegrees(float_t a, float_t b)
{
	float_t c = (b > a) ? b - a : 0.0f - (a - b);

	if (c > 180.0f)
		c = 0.0f - (360.0f - c);
	else if (c <= -180.0f)
		c = (360.0f + c);

	return c;
}

static CVector3 Math::GetOffsetDegrees(const CVector3& a, const CVector3& b)
{
	return CVector3(Math::GetOffsetDegrees(a.x, b.x), Math::GetOffsetDegrees(a.y, b.y), Math::GetOffsetDegrees(a.z, b.z));
}

// Find the relative position of fPos between fStart and fEnd
static const float_t Math::Unlerp(const double fStart, const double fPos, const double fEnd)
{
	// Avoid dividing by 0 (results in INF values)
	if (fStart == fEnd) return 1.0f;

	return (float_t)((fPos - fStart) / (fEnd - fStart));
}

// Find the relative position of fPos between fStart and fEnd
// and clamp it between 0 and 1 avoiding extrapolation
static const float_t Math::UnlerpClamped(const double fStart, const double fPos, const double fEnd)
{
	return Math::Clamp(0.0f, Math::Unlerp(fStart, fPos, fEnd), 1.0f);
}

// Find the distance between two 2D points
static float_t Math::GetDistanceBetweenPoints2D(float_t x, float_t y, float_t xx, float_t yy)
{
	float_t newx = (xx - x);
	float_t newy = (yy - y);
	return SQRT(newx * newx + newy * newy);
}

// Find the distance between two 3D points
static float_t Math::GetDistanceBetweenPoints3D(float_t x, float_t y, float_t z, float_t xx, float_t yy, float_t zz)
{
	float_t newx = (xx - x);
	float_t newy = (yy - y);
	float_t newz = (zz - z);
	return SQRT(newx * newx + newy * newy + newz * newz);
}

// Check if a 2D point is within the specified circle
static bool Math::IsPointInCircle(float_t circleX, float_t circleY, float_t circleDistance, float_t pointX, float_t pointY)
{
	float_t distancebetween = Math::GetDistanceBetweenPoints2D(circleX, circleY, pointX, pointY);
	return (distancebetween < circleDistance);
}

// Check if a 3D point is within the specified tube
static bool Math::IsPointInTube(float_t tubeX, float_t tubeY, float_t tubeZ, float_t tubeHeight, float_t tubeRadius, float_t pointX, float_t pointY, float_t pointZ)
{
	float_t distancebetween = Math::GetDistanceBetweenPoints2D(tubeX, tubeY, pointX, pointY);
	return (distancebetween < tubeRadius && pointZ < tubeZ + tubeHeight && pointZ >= tubeZ);
}

// Check if a 3D point is within the specified ball
static bool Math::IsPointInBall(float_t ballX, float_t ballY, float_t ballZ, float_t ballRadius, float_t pointX, float_t pointY, float_t pointZ)
{
	float_t distancebetween = Math::GetDistanceBetweenPoints3D(ballX, ballY, ballZ, pointX, pointY, pointZ);
	return (distancebetween < ballRadius);
}

// Check if a 2D point is within the specified 2D area
static bool Math::IsPointInArea(float_t areaX, float_t areaY, float_t areaX2, float_t areaY2, float_t pointX, float_t pointY)
{
	return (pointX >= areaX && pointX <= areaX2 && pointY >= areaY && pointY <= areaY2);
}

// Check if a 3D point is within the specified 3D area
static bool Math::IsPointInArea(float_t fAreaX, float_t fAreaY, float_t fAreaZ, float_t fAreaX2, float_t fAreaY2, float_t fAreaZ2, float_t fPointX, float_t fPointY, float_t fPointZ)
{
	return ((fPointX >= fAreaX && fPointX <= fAreaX2) && (fPointY >= fAreaY && fPointY <= fAreaY2) && (fPointZ >= fAreaZ && fPointZ <= fAreaZ2));
}

// Check if a 3D point is within the specified cuboid
static bool Math::IsPointInCuboid(float_t areaX, float_t areaY, float_t areaZ, float_t areaX2, float_t areaY2, float_t areaZ2, float_t pointX, float_t pointY, float_t pointZ)
{
	return (pointX >= areaX && pointX <= areaX2 && pointY >= areaY && pointY <= areaY2 && pointZ >= areaZ && pointZ <= areaZ2);
}

// polyX and polyY as arrays
static bool Math::IsPointInPolygon(int nvert, float_t *polyX, float_t *polyY, float_t pointX, float_t pointY)
{
	bool bValid = false;

	for (int i = 0, j = (nvert - 1); i < nvert; j = i++)
	{
		if (((polyY[i] > pointY) != (polyY[j] > pointY)) && (pointX < (polyX[j] - polyX[i]) * (pointY - polyY[i]) / (polyY[j] - polyY[i]) + polyX[i]))
			bValid = !bValid;
	}

	return bValid;
}