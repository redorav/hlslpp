#ifdef HLSLPP_FEATURE_TRANSFORM

//------------------------------------------//
// World to View coordinates transformation //
//------------------------------------------//

static hlslpp_inline float4x4 look_at(const float3& position, const float3& target, const float3& up)
{
	const float3 look   = normalize(target - position) * HLSLPP_COORDINATES_SIGN;
	const float3 xRight = normalize(cross(up, look));
	const float3 upDir = cross(look, xRight);

#if HLSLPP_LOGICAL_LAYOUT == HLSLPP_LOGICAL_LAYOUT_ROW_MAJOR
	return float4x4(
		xRight.x,               upDir.x,               look.x,               0.0f,
		xRight.y,               upDir.y,               look.y,               0.0f,
		xRight.z,               upDir.z,               look.z,               0.0f,
		-dot(position, xRight), -dot(position, upDir), -dot(position, look), 1.0f
	);
#else
	return float4x4(
		float4(xRight, -dot(position, xRight)),
		float4(upDir,  -dot(position, upDir)),
		float4(look,   -dot(position, look)),
		float4(0.0f, 0.0f, 0.0f, 1.0f)
	);
#endif
}

//-----------------------------------------------//
// View to Projection coordinates transformation //
//-----------------------------------------------//

static hlslpp_inline float4x4 projection(const ProjectionSettings& proj)
{
	const float invWidth  = 1.0f / proj.frustrum.width();
	const float invHeight = 1.0f / proj.frustrum.height();
	const float invDepth  = 1.0f / proj.frustrum.depth();

	const float s  = HLSLPP_COORDINATES_SIGN;
	const float rl = proj.frustrum.xRight + proj.frustrum.xLeft;
	const float tb = proj.frustrum.yTop   + proj.frustrum.yBottom;

	if (proj.type == ProjectionType::Perspective)
	{
		const float dblNear = 2.0f * proj.frustrum.zNear;
		const float nf  = proj.frustrum.zFar   + (proj.zClip == ZClip::Zero ? 0.0f : proj.frustrum.zNear);
		const float m22 = s * nf * invDepth;
		const float m23 = proj.zClip == ZClip::Zero
		                ? -s * proj.frustrum.zNear * m22
		                : -2.0f * proj.frustrum.zFar * proj.frustrum.zNear * invDepth;

#if HLSLPP_LOGICAL_LAYOUT == HLSLPP_LOGICAL_LAYOUT_ROW_MAJOR
		return float4x4(
			dblNear * invWidth, 0.0f,                0.0f, 0.0f,
			0.0f,               dblNear * invHeight, 0.0f, 0.0f,
			-s * rl * invWidth, -s * tb * invHeight, m22,  s,
			0.0f,               0.0f,                m23,  0.0f
		);
#else
		return float4x4(
			dblNear * invWidth, 0.0f,                -s * rl * invWidth,  0.0f,
			0.0f,               dblNear * invHeight, -s * tb * invHeight, 0.0f,
			0.0f,               0.0f,                m22,                 m23,
			0.0f,               0.0f,                s,                   0.0f
		);
#endif
	}
	else
	{
		const float nf = proj.frustrum.zNear  + (proj.zClip == ZClip::Zero ? 0.0f : proj.frustrum.zFar);
		const float sd = s * (proj.zClip == ZClip::Zero ? 1.0f : 2.0f);

#if HLSLPP_LOGICAL_LAYOUT == HLSLPP_LOGICAL_LAYOUT_ROW_MAJOR
		return float4x4(
			2.0f * invWidth, 0.0f,             0.0f,          0.0f,
			0.0f,            2.0f * invHeight, 0.0f,          0.0f,
			0.0f,            0.0f,             sd * invDepth, 0.0f,
			-rl * invWidth,  -tb * invHeight, -nf * invDepth, 1.0f
		);
#else
		return float4x4(
			2.0f * invWidth, 0.0f,             0.0f,          -rl * invWidth,
			0.0f,            2.0f * invHeight, 0.0f,          -tb * invHeight,
			0.0f,            0.0f,             sd * invDepth, -nf * invDepth,
			0.0f,            0.0f,             0.0f,           1.0f
		);
#endif
	}
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

static hlslpp_inline float4x4 rotation_z(float angleRad)
{
	const float s = sinf(angleRad) * HLSLPP_MATRIX_LAYOUT_SIGN * HLSLPP_COORDINATES_SIGN;
	const float c = cosf(angleRad);

	return float4x4(
		c,    s,    0.0f, 0.0f,
		-s,   c,    0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

static hlslpp_inline float4x4 rotation_y(float angleRad)
{
	const float s = sinf(angleRad) * HLSLPP_MATRIX_LAYOUT_SIGN * HLSLPP_COORDINATES_SIGN;
	const float c = cosf(angleRad);

	return float4x4(
		c,    0.0f, -s,   0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		s,    0.0f, c,    0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

static hlslpp_inline float4x4 rotation_x(float angleRad)
{
	const float s = sinf(angleRad) * HLSLPP_MATRIX_LAYOUT_SIGN * HLSLPP_COORDINATES_SIGN;
	const float c = cosf(angleRad);

	return float4x4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, c,    s,    0.0f,
		0.0f, -s,   c,    0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

static hlslpp_inline float4x4 rotation_axis(const float3& axis, float angleRad)
{
	const float s  = sinf(angleRad) * HLSLPP_MATRIX_LAYOUT_SIGN * HLSLPP_COORDINATES_SIGN;
	const float c  = cosf(angleRad);

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

#endif // HLSLPP_FEATURE_TRANSFORM
