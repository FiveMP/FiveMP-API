#ifndef __CMATHS_H__
#	define __CMATHS_H__
#	define DOUBLE_PI    (M_PI * 2)
#	define PI           M_PI
#	define HALF_PI      M_PI_2
#	define RADS_PER_DEG (PI / 180.0f)
#	define DEGS_PER_RAD (180.0f / PI)

#	define EULER	M_E
#	define EPSILON	std::numeric_limits<float_t>::epsilon()
#	define IS_FLOAT_ZERO(_f)	(((_f) <= EPSILON) && ((_f) >= (-EPSILON)))

#	ifdef FIVEMP_DOUBLE_PRECISION
#		define SQRT(_v) sqrt(_v)
typedef double float_t;
#	else
#		define SQRT(_v) sqrtf(_v)
typedef float float_t;
#	endif

/// <summary>
/// Math namespace
/// </summary>
namespace Math
{
	/// <summary>
	/// Wrap around value
	/// </summary>
	/// <param name="value">Value to wrap around</param>
	/// <param name="high">Highest value</param>
	/// <returns>Wrapped value</returns>
	static float_t WrapAround(float_t value, float_t high);

	/// <summary>
	/// Convert radians to degrees
	/// </summary>
	/// <param name="radians">Radians</param>
	/// <returns>Degrees</returns>
	static float_t ConvertRadiansToDegrees(float_t radians);

	/// <summary>
	/// Convert radians in vector to degrees in vector
	/// </summary>
	/// <param name="vec_radians">Radians in vector</param>
	/// <returns>Degrees in vector</returns>
	static CVector3 ConvertRadiansToDegrees(const CVector3 & vec_radians);

	/// <summary>
	/// Convert degrees to radians
	/// </summary>
	/// <param name="degrees">Degrees</param>
	/// <returns>Radians</returns>
	static float_t ConvertDegreesToRadians(float_t degrees);

	/// <summary>
	/// Convert degrees in vector to radians in vector
	/// </summary>
	/// <param name="vec_degrees">Degrees in vector</param>
	/// <returns>Radians in vector</returns>
	static CVector3 ConvertDegreesToRadians(const CVector3 & vec_degrees);

	/// <summary>
	/// Get radians offset in radians
	/// </summary>
	/// <param name="a">Radians a</param>
	/// <param name="b">Radans b</param>
	/// <returns>Radians offset</returns>
	static float_t GetOffsetRadians(float_t a, float_t b);

	/// <summary>
	/// Get radians in vector offset in radians in vector
	/// </summary>
	/// <param name="a">Radians vector a</param>
	/// <param name="b">Radans vector b</param>
	/// <returns>Radians vector offset</returns>
	static CVector3 GetOffsetRadians(const CVector3 & a, const CVector3 & b);

	/// <summary>
	/// Get degrees offset in degrees
	/// </summary>
	/// <param name="a">Degrees a</param>
	/// <param name="b">Degrees b</param>
	/// <returns>Degrees offset</returns>
	static float_t GetOffsetDegrees(float_t a, float_t b);

	/// <summary>
	/// Get degrees in vector offset in degrees in vector
	/// </summary>
	/// <param name="a">Degrees vector a</param>
	/// <param name="b">Degrees vector b</param>
	/// <returns>Degrees vector offset</returns>
	static CVector3 GetOffsetDegrees(const CVector3 & a, const CVector3 & b);

	/// <summary>
	/// Lerp value
	/// </summary>
	/// <param name="start">Start value</param>
	/// <param name="alpha">Alpha</param>
	/// <param name="end">End value</param>
	/// <returns>Lerped value</returns>
	template <typename T>
	static T Lerp(const T& start, float_t alpha, const T& end)
	{
		return (end - start) * alpha + start;
	}

	/// <summary>
	/// Clamp value
	/// </summary>
	/// <param name="min">Minimum value</param>
	/// <param name="a">Value</param>
	/// <param name="max">Maximal value</param>
	/// <returns>Clamped value</returns>
	template<class T>
	static T Clamp(const T& min, const T& a, const T& max)
	{
		if (a < min)
			return min;

		if (a > max)
			return max;

		return a;
	}

	/// <summary>
	/// Unlerp value
	/// </summary>
	/// <param name="start">Start value</param>
	/// <param name="pos">Position</param>
	/// <param name="end">End value</param>
	/// <returns>Unlerped value</returns>
	static const float_t Unlerp(const double start, const double pos, const double end);

	/// <summary>
	/// Find the relative position of "pos" between "start" and "end"
	/// and clamp it between 0 and 1 avoiding extrapolation
	/// </summary>
	/// <param name="start">Start value</param>
	/// <param name="pos">Position</param>
	/// <param name="end">End value</param>
	/// <returns>Unlerped and clamped value</returns>
	static const float_t UnlerpClamped(const double start, const double pos, const double end);

	/// <summary>
	/// Get distance between two 2D points
	/// </summary>
	/// <param name="x">Point 1 X</param>
	/// <param name="y">Point 1 Y</param>
	/// <param name="xx">Point 2 X</param>
	/// <param name="yy">Point 2 Y</param>
	/// <returns>Distance between two 2D points</returns>
	static float_t GetDistanceBetweenPoints2D(float_t x, float_t y, float_t xx, float_t yy);

	/// <summary>
	/// Get distance between two 3D points
	/// </summary>
	/// <param name="x">Point 1 X</param>
	/// <param name="y">Point 1 Y</param>
	/// <param name="z">Point 1 Z</param>
	/// <param name="xx">Point 2 X</param>
	/// <param name="yy">Point 2 Y</param>
	/// <param name="zz">Point 2 Z</param>
	/// <returns>Distance between two 3D points</returns>
	static float_t GetDistanceBetweenPoints3D(float_t x, float_t y, float_t z, float_t xx, float_t yy, float_t zz);

	/// <summary>
	/// Is 2D point within circle
	/// </summary>
	/// <param name="circle_x">Circle point X</param>
	/// <param name="circle_y">Circle point Y</param>
	/// <param name="circle_radius">Circle radius</param>
	/// <param name="point_x">Point X</param>
	/// <param name="point_y">Point Y</param>
	/// <returns>If in range true, otherwise false</returns>
	static bool IsPointInCircle(float_t circle_x, float_t circle_y, float_t circle_radius, float_t point_x, float_t point_y);

	/// <summary>
	/// Is 3D point within tube
	/// </summary>
	/// <param name="tube_x">Tube point X</param>
	/// <param name="tube_y">Tube point Y</param>
	/// <param name="tube_z">Tube point Z</param>
	/// <param name="tube_height">Tube height</param>
	/// <param name="point_x">Point X</param>
	/// <param name="point_y">Point Y</param>
	/// <param name="point_z">Point Z</param>
	/// <returns>If in range true, otherwise false</returns>
	static bool IsPointInTube(float_t tube_x, float_t tube_y, float_t tube_z, float_t tube_height, float_t tube_radius, float_t point_x, float_t point_y, float_t point_z);

	/// <summary>
	/// Is 3D point within ball
	/// </summary>
	/// <param name="ball_x">Ball point X</param>
	/// <param name="ball_y">Ball point Y</param>
	/// <param name="ball_z">Ball point Z</param>
	/// <param name="ball_radius">Ball radius</param>
	/// <param name="point_x">Point X</param>
	/// <param name="point_y">Point Y</param>
	/// <param name="point_z">Point Z</param>
	/// <returns>If in range true, otherwise false</returns>
	static bool IsPointInBall(float_t ball_x, float_t ball_y, float_t ball_z, float_t ball_radius, float_t point_x, float_t point_y, float_t point_z);

	/// <summary>
	/// Is 2D point in area
	/// </summary>
	/// <param name="min_x">Minimum X</param>
	/// <param name="min_y">Minimum Y</param>
	/// <param name="max_x">Maximum X</param>
	/// <param name="max_y">Maximum Y</param>
	/// <param name="point_x">Point Y</param>
	/// <param name="point_y">Point Y</param>
	/// <returns>If in area true, otherwise false</returns>
	static bool IsPointInArea(float_t min_x, float_t min_y, float_t max_x, float_t max_y, float_t point_x, float_t point_y);

	/// <summary>
	/// Is 3D point in cuboid
	/// </summary>
	/// <param name="min_x">Minimum X</param>
	/// <param name="min_y">Minimum Y</param>
	/// <param name="min_z">Minimum Z</param>
	/// <param name="max_x">Maximum X</param>
	/// <param name="max_y">Maximum Y</param>
	/// <param name="max_z">Maximum Z</param>
	/// <param name="point_x">Point Y</param>
	/// <param name="point_y">Point Y</param>
	/// <param name="point_z">Point z</param>
	/// <returns>If in area true, otherwise false</returns>
	static bool IsPointInCuboid(float_t min_x, float_t min_y, float_t min_z, float_t max_x, float_t max_y, float_t max_z, float_t point_x, float_t point_y, float_t point_z);

	/// <summary>
	/// Is 2D point in 2D polygon
	/// </summary>
	/// <param name="poly">2D polygon</param>
	/// <param name="point_x">Point Y</param>
	/// <param name="point_y">Point Y</param>
	/// <returns>If in area true, otherwise false</returns>
	static bool IsPointInPolygon(std::vector < CVector2 > & poly, float_t point_x, float_t point_y);
};
#endif
