#pragma once

#if defined(HLSLPP_FEATURE_TRANSFORM)

//-------//
// Scale //
//-------//

static hlslpp_inline float2x2 scale(float sx, float sy)
{
	return float2x2(
		sx,   0.0f,
		0.0f, sy
	);
}

static hlslpp_inline float2x2 scale(const float2& s)
{
	return scale(s.x, s.y);
}

static hlslpp_inline float2x2 scale(float su)
{
	return scale(su, su);
}

//----------//
// Rotation //
//----------//

static hlslpp_inline float2x2 rotation(float angle_rad)
{
#if defined(HLSLPP_LAYOUT_COORDINATES_FLIP_SIGN)
	angle_rad = -angle_rad;
#endif

	const float s = sinf(angle_rad);
	const float c = cosf(angle_rad);

	return float2x2(
		c,  s,
		-s, c
	);
}

#endif
