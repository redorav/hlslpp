#pragma once

#if defined(HLSLPP_FEATURE_TRANSFORM)

//------------------------------------------//
// World to View coordinates transformation //
//------------------------------------------//

static hlslpp_inline float4x4 look_at(const float3& position, const float3& target, const float3& up)
{
#if HLSLPP_COORDINATES == HLSLPP_COORDINATES_LEFT_HANDED
	const float3 look   = normalize(target - position);
#else
	const float3 look   = normalize(position - target); // Negate without the extra cost
#endif
	const float3 right  = normalize(cross(up, look));
	const float3 up_dir = cross(look, right);

#if HLSLPP_LOGICAL_LAYOUT == HLSLPP_LOGICAL_LAYOUT_ROW_MAJOR
	return float4x4(
		float4(right.x,               up_dir.x,               look.x,               0.0f),
		float4(right.y,               up_dir.y,               look.y,               0.0f),
		float4(right.z,               up_dir.z,               look.z,               0.0f),
		float4(-dot(position, right), -dot(position, up_dir), -dot(position, look), 1.0f)
	);
#else
	return float4x4(
		float4(right,  -dot(position, right)),
		float4(up_dir, -dot(position, up_dir)),
		float4(look,   -dot(position, look)),
		float4(0.0f, 0.0f, 0.0f, 1.0f)
	);
#endif
}

//-----------------------------------------------//
// View to Projection coordinates transformation //
//-----------------------------------------------//

static hlslpp_inline float4x4 perspective(const projection& proj)
{
	const float r = proj.frustum_planes.right;
	const float l = proj.frustum_planes.left;
	const float t = proj.frustum_planes.top;
	const float b = proj.frustum_planes.bottom;
	const float n = proj.frustum_planes.near_z;
	const float f = proj.frustum_planes.far_z;
	const float s  = HLSLPP_COORDINATES_SIGN;

	const float m00 = 2.0f * n / (r - l);
	const float m11 = 2.0f * n / (t - b);

	const float m20 = -s * (r + l) / (r - l);
	const float m21 = -s * (t + b) / (t - b);
	const float m23 = s;

	float m22 = 0.0f;
	float m32 = 0.0f;

	if (proj.z_clip == zclip::zero)
	{
		if (proj.z_direction == zdirection::forward)
		{
			if (proj.z_plane == zplane::finite)
			{
				m22 = s * f / (f - n);
				m32 = -n * f / (f - n);
			}
			else
			{
				m22 = s;
				m32 = -n;
			}
		}
		else
		{
			if (proj.z_plane == zplane::finite)
			{
				m22 = s * n / (n - f);
				m32 = -f * n / (n - f);
			}
			else
			{
				m22 = 0.0f;
				m32 = 0.0f;
			}
		}
	}
	else
	{
		if (proj.z_direction == zdirection::forward)
		{
			if (proj.z_plane == zplane::finite)
			{
				m22 = s * (f + n) / (f - n);
				m32 = -2.0f * f * n / (f - n);
			}
			else
			{
				m22 = s;
				m32 = -2.0f * n;
			}
		}
		else
		{
			if (proj.z_plane == zplane::finite)
			{
				m22 = s * (n + f) / (n - f);
				m32 = -2.0f * n * f / (n - f);
			}
			else
			{
				m22 = -s;
				m32 = 2.0f * n;
			}
		}
	}

#if HLSLPP_LOGICAL_LAYOUT == HLSLPP_LOGICAL_LAYOUT_ROW_MAJOR
	return float4x4(
		m00,  0.0f, 0.0f, 0.0f,
		0.0f, m11,  0.0f, 0.0f,
		m20,  m21,  m22,  m23,
		0.0f, 0.0f, m32,  0.0f
	);
#else
	return float4x4(
		m00,  0.0f, m20, 0.0f,
		0.0f, m11,  m21, 0.0f,
		0.0f, 0.0f, m22, m32,
		0.0f, 0.0f, m23, 0.0f
	);
#endif
}

static hlslpp_inline float4x4 orthographic(const projection& proj)
{
	const float r = proj.frustum_planes.right;
	const float l = proj.frustum_planes.left;
	const float t = proj.frustum_planes.top;
	const float b = proj.frustum_planes.bottom;
	const float n = proj.frustum_planes.near_z;
	const float f = proj.frustum_planes.far_z;

	const float s = HLSLPP_COORDINATES_SIGN;

	const float m00 = 2.0f / (r - l);
	const float m11 = 2.0f / (t - b);

	const float m30 = -(r + l) / (r - l);
	const float m31 = -(t + b) / (t - b);

	float m22 = 0.0f;
	float m32 = 0.0f;

	// There's no real concept of infinite far plane for an orthographic
	// projection matrix because we are subdividing the depth plane linearly
	if (proj.z_clip == zclip::zero)
	{
		if (proj.z_direction == zdirection::forward)
		{
			m22 = s / (f - n);
			m32 = -n / (f - n);
		}
		else
		{
			m22 = s / (n - f);
			m32 = -f / (n - f);
		}
	}
	else
	{
		if (proj.z_direction == zdirection::forward)
		{
			m22 = s * 2.0f / (f - n);
			m32 = -(f + n) / (f - n);
		}
		else
		{
			m22 = s * 2.0f / (n - f);
			m32 = -(n + f) / (n - f);
		}
	}

#if HLSLPP_LOGICAL_LAYOUT == HLSLPP_LOGICAL_LAYOUT_ROW_MAJOR
	return float4x4(
		m00,  0.0f, 0.0f, 0.0f,
		0.0f, m11,  0.0f, 0.0f,
		0.0f, 0.0f, m22,  0.0f,
		m30,  m31,  m32,  1.0f
	);
#else
	return float4x4(
		m00,  0.0f, 0.0f, m30,
		0.0f, m11,  0.0f, m31,
		0.0f, 0.0f, m22,  m32,
		0.0f, 0.0f, 0.0f, 1.0f
	);
#endif
}

//-------//
// Scale //
//-------//

static hlslpp_inline float4x4 scale(float sx, float sy, float sz)
{
	return float4x4(
		sx,  0.0f, 0.0f, 0.0f,
		0.0f, sy,  0.0f, 0.0f,
		0.0f, 0.0f, sz,  0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

static hlslpp_inline float4x4 scale(const float3& s)
{
	return scale(s.x, s.y, s.z);
}

static hlslpp_inline float4x4 scale(float su)
{
	return scale(su, su, su);
}

//----------//
// Rotation //
//----------//

static hlslpp_inline float4x4 rotation_z(float angle_rad)
{
#if defined(HLSLPP_LAYOUT_COORDINATES_FLIP_SIGN)
	angle_rad = -angle_rad;
#endif

	const float s = sinf(angle_rad);
	const float c = cosf(angle_rad);

	return float4x4(
		c,    s,    0.0f, 0.0f,
		-s,   c,    0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

static hlslpp_inline float4x4 rotation_y(float angle_rad)
{
#if defined(HLSLPP_LAYOUT_COORDINATES_FLIP_SIGN)
	angle_rad = -angle_rad;
#endif

	const float s = sinf(angle_rad);
	const float c = cosf(angle_rad);

	return float4x4(
		c,    0.0f, -s,   0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		s,    0.0f, c,    0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

static hlslpp_inline float4x4 rotation_x(float angle_rad)
{
#if defined(HLSLPP_LAYOUT_COORDINATES_FLIP_SIGN)
	angle_rad = -angle_rad;
#endif

	const float s = sinf(angle_rad);
	const float c = cosf(angle_rad);

	return float4x4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, c,    s,    0.0f,
		0.0f, -s,   c,    0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

static hlslpp_inline float4x4 rotation_axis(const float3& axis, float angle_rad)
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

	return float4x4(
		v1.x + c,    v2.x + as.z, v2.z - as.y, 0.0f,
		v2.x - as.z, v1.y + c,    v2.y + as.x, 0.0f,
		v2.z + as.y, v2.y - as.x, v1.z + c,    0.0f,
		0.0f,        0.0f,        0.0f,        1.0f
	);
}

//-------------//
// Translation //
//-------------//

static hlslpp_inline float4x4 translation(float tx, float ty, float tz)
{
#if HLSLPP_LOGICAL_LAYOUT == HLSLPP_LOGICAL_LAYOUT_ROW_MAJOR
	return float4x4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		tx,   ty,   tz,   1.0f
	);
#else
	return float4x4(
		1.0f, 0.0f, 0.0f, tx,
		0.0f, 1.0f, 0.0f, ty,
		0.0f, 0.0f, 1.0f, tz,
		0.0f, 0.0f, 0.0f, 1.0f
	);
#endif
}

static hlslpp_inline float4x4 translation(const float3& t)
{
	return translation(t.x, t.y, t.z);
}

#endif
