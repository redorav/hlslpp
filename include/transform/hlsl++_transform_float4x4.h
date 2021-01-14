#if defined(HLSLPP_FEATURE_TRANSFORM)

//------------------------------------------//
// World to View coordinates transformation //
//------------------------------------------//

static hlslpp_inline float4x4 look_at(const float3& position, const float3& target, const float3& up)
{
	const float3 look   = normalize(target - position) * HLSLPP_COORDINATES_SIGN;
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
	const float inv_width  = 1.0f / proj.frust.width();
	const float inv_height = 1.0f / proj.frust.height();
	const float inv_depth  = 1.0f / proj.frust.depth();

	const float s  = HLSLPP_COORDINATES_SIGN;
	const float rl = proj.frust.right + proj.frust.left;
	const float tb = proj.frust.top   + proj.frust.bottom;

	const float dbl_near = 2.0f * proj.frust.near_z;
	const float nf  = proj.frust.far_z   + (proj.z_clip == zclip::zero ? 0.0f : proj.frust.near_z);
	const float m22 = s * nf * inv_depth;
	const float m32 = proj.z_clip == zclip::zero
	                ? -s * proj.frust.near_z * m22
	                : -2.0f * proj.frust.far_z * proj.frust.near_z * inv_depth;

#if HLSLPP_LOGICAL_LAYOUT == HLSLPP_LOGICAL_LAYOUT_ROW_MAJOR
	return float4x4(
		dbl_near * inv_width, 0.0f,                  0.0f, 0.0f,
		0.0f,                 dbl_near * inv_height, 0.0f, 0.0f,
		-s * rl * inv_width,  -s * tb * inv_height,  m22,  s,
		0.0f,                 0.0f,                  m32,  0.0f
	);
#else
	return float4x4(
		dbl_near * inv_width, 0.0f,                  -s * rl * inv_width,  0.0f,
		0.0f,                 dbl_near * inv_height, -s * tb * inv_height, 0.0f,
		0.0f,                 0.0f,                  m22,                  m32,
		0.0f,                 0.0f,                  s,                    0.0f
	);
#endif
}

static hlslpp_inline float4x4 orthographic(const projection& proj)
{
	const float inv_width  = 1.0f / proj.frust.width();
	const float inv_height = 1.0f / proj.frust.height();
	const float inv_depth  = 1.0f / proj.frust.depth();

	const float s  = HLSLPP_COORDINATES_SIGN;
	const float rl = proj.frust.right + proj.frust.left;
	const float tb = proj.frust.top   + proj.frust.bottom;

	const float nf = proj.frust.near_z  + (proj.z_clip == zclip::zero ? 0.0f : proj.frust.far_z);
	const float sd = s * (proj.z_clip == zclip::zero ? 1.0f : 2.0f);

#if HLSLPP_LOGICAL_LAYOUT == HLSLPP_LOGICAL_LAYOUT_ROW_MAJOR
	return float4x4(
		2.0f * inv_width, 0.0f,              0.0f,            0.0f,
		0.0f,             2.0f * inv_height, 0.0f,            0.0f,
		0.0f,             0.0f,              sd * inv_depth,  0.0f,
		-rl * inv_width,  -tb * inv_height,  -nf * inv_depth, 1.0f
	);
#else
	return float4x4(
		2.0f * inv_width, 0.0f,              0.0f,           -rl * inv_width,
		0.0f,             2.0f * inv_height, 0.0f,           -tb * inv_height,
		0.0f,             0.0f,              sd * inv_depth, -nf * inv_depth,
		0.0f,             0.0f,              0.0f,           1.0f
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
	const float s = sinf(angle_rad) * HLSLPP_MATRIX_LAYOUT_SIGN * HLSLPP_COORDINATES_SIGN;
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
	const float s = sinf(angle_rad) * HLSLPP_MATRIX_LAYOUT_SIGN * HLSLPP_COORDINATES_SIGN;
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
	const float s = sinf(angle_rad) * HLSLPP_MATRIX_LAYOUT_SIGN * HLSLPP_COORDINATES_SIGN;
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
	const float s = sinf(angle_rad) * HLSLPP_MATRIX_LAYOUT_SIGN * HLSLPP_COORDINATES_SIGN;
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
