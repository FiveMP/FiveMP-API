#include "FiveMP.h"

static float_t Math::WrapAround(float_t value, float_t high)
{
	return value - (high * floor((float_t)(value / high)));
}

static float_t Math::ConvertRadiansToDegrees(float_t radians)
{
	return Math::WrapAround((((radians * 180.0f) / (float_t)PI) + 360.0f), 360.0f);
}

static CVector3 Math::ConvertRadiansToDegrees(const CVector3 &vecRotation)
{
	return CVector3(Math::ConvertRadiansToDegrees(vecRotation.x),
		Math::ConvertRadiansToDegrees(vecRotation.y),
		Math::ConvertRadiansToDegrees(vecRotation.z));
}

static float_t Math::ConvertDegreesToRadians(float_t degrees)
{
	return Math::WrapAround((degrees * (float_t)PI / 180.0f + 2 * (float_t)PI),
		(float_t)DOUBLE_PI);
}

static CVector3 Math::ConvertDegreesToRadians(const CVector3 &vec_degrees)
{
	return CVector3(Math::ConvertDegreesToRadians(vec_degrees.x),
		Math::ConvertDegreesToRadians(vec_degrees.y),
		Math::ConvertDegreesToRadians(vec_degrees.z));
}

static float_t Math::GetOffsetRadians(float_t a, float_t b)
{
	float_t ret = (b > a) ? (b - a) : (-(a - b));
	if (ret > PI)
		ret = (float_t)-(DOUBLE_PI - ret);
	else if (ret <= -PI)
		ret = (float_t)(DOUBLE_PI + ret);
	return ret;
}

static CVector3 Math::GetOffsetRadians(const CVector3 & a, const CVector3 & b)
{
	return CVector3(Math::GetOffsetRadians(a.x, b.x), Math::GetOffsetRadians(a.y, b.y), Math::GetOffsetRadians(a.z, b.z));
}

static float_t Math::GetOffsetDegrees(float_t a, float_t b)
{
	float_t c = (b > a) ? (b - a) : (-(a - b));
	if (c > 180.0f)
		c = -(360.0f - c);
	else if (c <= -180.0f)
		c = (360.0f + c);
	return c;
}

static CVector3 Math::GetOffsetDegrees(const CVector3 & a, const CVector3 & b)
{
	return CVector3(Math::GetOffsetDegrees(a.x, b.x), Math::GetOffsetDegrees(a.y, b.y), Math::GetOffsetDegrees(a.z, b.z));
}

static const float_t Math::Unlerp(const double start, const double pos, const double end)
{
	// Avoid dividing by 0 (results in INF values)
	if (start == end) return 1.0f;

	return (float_t)((pos - start) / (end - start));
}

static const float_t Math::UnlerpClamped(const double start, const double pos, const double end)
{
	return Math::Clamp(0.0f, Math::Unlerp(start, pos, end), 1.0f);
}

static float_t Math::GetDistanceBetweenPoints2D(float_t x, float_t y, float_t xx, float_t yy)
{
	return CVector2(xx - x, yy - y).Magnitude();
}

static float_t Math::GetDistanceBetweenPoints3D(float_t x, float_t y, float_t z, float_t xx, float_t yy, float_t zz)
{
	return CVector3(xx - x, yy - y, zz - z).Magnitude();
}

static bool Math::IsPointInCircle(float_t circle_x, float_t circle_y, float_t circle_radius, float_t point_x, float_t point_y)
{
	return CVector2(circle_x, circle_y).IsInRange(CVector2(point_x, point_y), circle_radius);
}

static bool Math::IsPointInTube(float_t tube_x, float_t tube_y, float_t tube_z, float_t tube_height, float_t tube_radius, float_t point_x, float_t point_y, float_t point_z)
{
	return (point_z >= tube_z) && (point_z <= (tube_z + tube_height)) && IsPointInCircle(tube_x, tube_y, tube_radius, point_x, point_y);
}

static bool Math::IsPointInBall(float_t ball_x, float_t ball_y, float_t ball_z, float_t ball_radius, float_t point_x, float_t point_y, float_t point_z)
{
	return CVector3(ball_x, ball_y, ball_z).IsInRange(CVector3(point_x, point_y, point_z), ball_radius);
}

static bool Math::IsPointInArea(float_t min_x, float_t min_y, float_t max_x, float_t max_y, float_t point_x, float_t point_y)
{
	return ((point_x >= min_x) && (point_x <= max_x) && (point_y >= min_y) && (point_y <= max_y));
}

static bool Math::IsPointInCuboid(float_t min_x, float_t min_y, float_t min_z, float_t max_x, float_t max_y, float_t max_z, float_t point_x, float_t point_y, float_t point_z)
{
	return ((point_x >= min_x) && (point_x <= max_x) && (point_y >= min_y) && (point_y <= max_y) && (point_z >= min_z) && (point_z <= max_z));
}

static bool Math::IsPointInPolygon(std::vector < std::pair < float_t, float_t > > & poly, float_t point_x, float_t point_y)
{
	bool ret = false;
	for (size_t sz = poly.size(), i = 0, j = (sz - 1); i != sz; j = i++)
	{
		if (((poly[i].second > point_y) != (poly[j].second > point_y)) && (point_x < (poly[j].first - poly[i].first) * (point_y - poly[i].second) / (poly[j].second - poly[i].second) + poly[i].first))
			ret = !ret;
	}
	return ret;
}