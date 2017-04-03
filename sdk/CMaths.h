#define DOUBLE_PI    (M_PI * 2)
#define PI           M_PI
#define HALF_PI      M_PI_2
#define RADS_PER_DEG (PI / 180.0f)
#define DEGS_PER_RAD (180.0f / PI)

#define EULER	M_E
#define EPSILON	std::numeric_limits<float_t>::epsilon()
#define IS_FLOAT_ZERO(_f)	(((_f) <= EPSILON) && ((_f) >= (-EPSILON)))

#ifdef FIVEMP_DOUBLE_PRECISION
#define SQRT(_v) sqrt(_v)
typedef double float_t;
#else
#define SQRT(_v) sqrtf(_v)
typedef float float_t;
#endif

namespace Math
{
	static float_t WrapAround(float_t fValue, float_t fHigh);

	static float_t ConvertRadiansToDegrees(float_t fRotation);

	static CVector3 ConvertRadiansToDegrees(const CVector3 &vecRotation);

	static float_t ConvertDegreesToRadians(float_t fRotation);

	static CVector3 ConvertDegreesToRadians(const CVector3 &vecRotation);

	static float_t GetOffsetDegrees(float_t a, float_t b);

	static CVector3 GetOffsetDegrees(const CVector3& a, const CVector3& b);

	template <typename T>
	static T Lerp(const T& start, float_t fAlpha, const T& end)
	{
		return (end - start) * fAlpha + start;
	}

	// Clamps a value between two other values
	template<class T>
	static T Clamp(const T& min, const T& a, const T& max)
	{
		if (a < min)
			return min;

		if (a > max)
			return max;

		return a;
	}

	// Find the relative position of fPos between fStart and fEnd
	static const float_t Unlerp(const double fStart, const double fPos, const double fEnd);

	// Find the relative position of fPos between fStart and fEnd
	// and clamp it between 0 and 1 avoiding extrapolation
	static const float_t UnlerpClamped(const double fStart, const double fPos, const double fEnd);

	// Find the distance between two 2D points
	static float_t GetDistanceBetweenPoints2D(float_t x, float_t y, float_t xx, float_t yy);

	// Find the distance between two 3D points
	static float_t GetDistanceBetweenPoints3D(float_t x, float_t y, float_t z, float_t xx, float_t yy, float_t zz);

	// Check if a 2D point is within the specified circle
	static bool IsPointInCircle(float_t circleX, float_t circleY, float_t circleDistance, float_t pointX, float_t pointY);

	// Check if a 3D point is within the specified tube
	static bool IsPointInTube(float_t tubeX, float_t tubeY, float_t tubeZ, float_t tubeHeight, float_t tubeRadius, float_t pointX, float_t pointY, float_t pointZ);

	// Check if a 3D point is within the specified ball
	static bool IsPointInBall(float_t ballX, float_t ballY, float_t ballZ, float_t ballRadius, float_t pointX, float_t pointY, float_t pointZ);

	// Check if a 2D point is within the specified 2D area
	static bool IsPointInArea(float_t areaX, float_t areaY, float_t areaX2, float_t areaY2, float_t pointX, float_t pointY);

	// Check if a 3D point is within the specified 3D area
	static bool IsPointInArea(float_t fAreaX, float_t fAreaY, float_t fAreaZ, float_t fAreaX2, float_t fAreaY2, float_t fAreaZ2, float_t fPointX, float_t fPointY, float_t fPointZ);

	// Check if a 3D point is within the specified cuboid
	static bool IsPointInCuboid(float_t areaX, float_t areaY, float_t areaZ, float_t areaX2, float_t areaY2, float_t areaZ2, float_t pointX, float_t pointY, float_t pointZ);

	// polyX and polyY as arrays
	static bool IsPointInPolygon(int nvert, float_t *polyX, float_t *polyY, float_t pointX, float_t pointY);
};