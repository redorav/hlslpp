#include "hlsl++/vector_float_type.h"
#include "hlsl++/vector_int_type.h"
#include "hlsl++/vector_uint_type.h"
#include "hlsl++/vector_double_type.h"
#include "hlsl++/quaternion_type.h"

void Declaration()
{
	hlslpp::float1 f1;
	hlslpp::float2 f2;
	hlslpp::float3 f3;
	hlslpp::float4 f4;

	hlslpp::int1 i1;
	hlslpp::int2 i2;
	hlslpp::int3 i3;
	hlslpp::int4 i4;

	hlslpp::uint1 ui1;
	hlslpp::uint2 ui2;
	hlslpp::uint3 ui3;
	hlslpp::uint4 ui4;

#if defined(HLSLPP_DOUBLE)
	hlslpp::double1 d1;
	hlslpp::double2 d2;
	hlslpp::double3 d3;
	hlslpp::double4 d4;
#endif

	hlslpp::quaternion q;
}