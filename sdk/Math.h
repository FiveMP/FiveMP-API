#ifndef _MATH_H_
#	define _MATH_H_
#	define _USE_MATH_DEFINES
#	include <math.h>
#	include "./sdk/DataTypes.h"
#	define PI	M_PI
#	define EULER	M_E
#	define EPSILON	std::numeric_limits<float_t>::epsilon()
#	define IS_FLOAT_ZERO(_f)	(((_f) <= EPSILON) && ((_f) >= (-EPSILON)))
#	ifdef FIVEMP_DOUBLE_PRECISION
#	define SQRT(_v)	sqrt(_v)
#	else
#	define SQRT(_v) sqrtf(_v)
#	endif
#endif
