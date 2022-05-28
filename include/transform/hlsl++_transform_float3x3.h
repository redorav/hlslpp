#pragma once

#if defined(HLSLPP_FEATURE_TRANSFORM)

//-------//
// Scale //
//-------//

static hlslpp_inline float3x3 scale(float sx, float sy, float sz = 1.0f)
{
	return float3x3(
		sx,   0.0f, 0.0f,
		0.0f, sy,   0.0f,
		0.0f, 0.0f, sz
	);
}

static hlslpp_inline float3x3 scale(const float3& s)
{
	return scale(s.x, s.y, s.z);
}

static hlslpp_inline float3x3 scale(const float2& s)
{
	return scale(s.x, s.y, 1.0f);
}

static hlslpp_inline float3x3 scale(float su)
{
	return scale(su, su, su);
}

//----------//
// Rotation //
//----------//

static hlslpp_inline float3x3 rotation_z(float angle_rad)
{
#if defined(HLSLPP_LAYOUT_COORDINATES_FLIP_SIGN)
	angle_rad = -angle_rad;
#endif

	const float s = sinf(angle_rad);
	const float c = cosf(angle_rad);

	return float3x3(
		c,    s,    0.0f,
		-s,   c,    0.0f,
		0.0f, 0.0f, 1.0f
	);
}

static hlslpp_inline float3x3 rotation_y(float angle_rad)
{
#if defined(HLSLPP_LAYOUT_COORDINATES_FLIP_SIGN)
	angle_rad = -angle_rad;
#endif

	const float s = sinf(angle_rad);
	const float c = cosf(angle_rad);

	return float3x3(
		c,    0.0f, -s,
		0.0f, 1.0f, 0.0f,
		s,    0.0f, c
	);
}

static hlslpp_inline float3x3 rotation_x(float angle_rad)
{
#if defined(HLSLPP_LAYOUT_COORDINATES_FLIP_SIGN)
	angle_rad = -angle_rad;
#endif

	const float s = sinf(angle_rad);
	const float c = cosf(angle_rad);

	return float3x3(
		1.0f, 0.0f, 0.0f,
		0.0f, c,    s,
		0.0f, -s,   c
	);
}

static hlslpp_inline float3x3 rotation_axis(const float3& axis, float angle_rad)
{
#if defined(HLSLPP_LAYOUT_COORDINATES_FLIP_SIGN)
	angle_rad = -angle_rad;
#endif

	const float s = sinf(angle_rad);
	const float c = cosf(angle_rad);

	const float3 as = axis * s;
	const float3 ac = axis * (1.0f - c);
	const float3 v1 = axis * ac;
	const float3 v2 = axis * ac.yzx;

	return float3x3(
		v1.x + c,    v2.x + as.z, v2.z - as.y,
		v2.x - as.z, v1.y + c,    v2.y + as.x,
		v2.z + as.y, v2.y - as.x, v1.z + c
	);
}

//-------------//
// Translation //
//-------------//

static hlslpp_inline float3x3 translation(float tx, float ty)
{
#if HLSLPP_LOGICAL_LAYOUT == HLSLPP_LOGICAL_LAYOUT_ROW_MAJOR
	return float3x3(
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		tx,   ty,   1.0f
	);
#else
	return float3x3(
		1.0f, 0.0f, tx,
		0.0f, 1.0f, ty,
		0.0f, 0.0f, 1.0f
	);
#endif
}

static hlslpp_inline float3x3 translation(const float2& t)
{
	return translation(t.x, t.y);
}

#endif
