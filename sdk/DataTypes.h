#ifndef _DATATYPES_H_
#	define _DATATYPES_H_
#include <limits>
#include <stdexcept>
#include <cstdint>
#	ifdef FIVEMP_DOUBLE_PRECISION
typedef double float_t;
#	else
typedef float float_t;
#	endif
#endif