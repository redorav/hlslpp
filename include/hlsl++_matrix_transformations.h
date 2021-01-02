//---------------------------------//
// Special Transformation Matrices //
//---------------------------------//

#include <cmath>

namespace hlslpp
{

	hlslpp_inline float2x2 rotation_2d_matrix(float angle_rad)
	{
		const float s = std::sin(angle_rad);
		const float c = std::cos(angle_rad);

		return float2x2(c, -s,
						s,  c);
	}

	hlslpp_inline float3x3 rotation_3d_matrix(const float3& axis, float angle_rad)
	{
		const float s  = std::sin(angle_rad);
		const float c  = std::cos(angle_rad);

		const float3 as = axis * s;
		const float3 ac = axis * (1.f - c);
		const float3 v1 = axis * ac;
		const float3 v2 = axis * ac.yzx;

		return float3x3(v1.x + c,    v2.x + as.z, v2.z - as.y,
						v2.x - as.z, v1.y + c,    v2.y + as.x,
						v2.z + as.y, v2.y - as.x, v1.z + c);
	}

} // namespace hlslpp