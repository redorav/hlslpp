//---------------------------------//
// Special Transformation Matrices //
//   (Optional Extension Header)   //
//---------------------------------//
#pragma once

#include "hlsl++.h"

#include <math.h>

// Row-Major layout assumes "vector-row(N) * matrix(NxM)" multiplication order
#define HLSLPP_LOGICAL_LAYOUT_ROW_MAJOR 0

// Column-Major layout assumes "matrix(MxN) * vector-col(N)" multiplication order
#define HLSLPP_LOGICAL_LAYOUT_COL_MAJOR 1

// Default HLSL++ logical layout of transformation matrices is Row-Major
// It can be changed by overriding this definition value in external project
#ifndef HLSLPP_LOGICAL_LAYOUT
#define HLSLPP_LOGICAL_LAYOUT HLSLPP_LOGICAL_LAYOUT_ROW_MAJOR
#endif

// The positive x, y and z axes point right, up and forward.  Positive rotation is clockwise about the axis of rotation. (used in DirectX)
#define HLSLPP_COORDINATES_LEFT_HANDED 0

// The positive x, y and z axes point right, up and backward. Positive rotation is counterclockwise about the axis of rotation. (used in OpenGL)
#define HLSLPP_COORDINATES_RIGHT_HANDED 1

// Default HLSL++ coordinate system is Left-Handed
// It can be changed by overriding this definition value in external project
#ifndef HLSLPP_COORDINATES
#define HLSLPP_COORDINATES HLSLPP_COORDINATES_LEFT_HANDED
#endif

#if HLSLPP_LOGICAL_LAYOUT == HLSLPP_LOGICAL_LAYOUT_ROW_MAJOR
#define HLSLPP_MATRIX_LAYOUT_SIGN 1.0f
#else
#define HLSLPP_MATRIX_LAYOUT_SIGN -1.0f
#endif

#if HLSLPP_COORDINATES == HLSLPP_COORDINATES_LEFT_HANDED
#define HLSLPP_COORDINATES_SIGN 1.0f
#else
#define HLSLPP_COORDINATES_SIGN -1.0f
#endif

#define HLSLPP_ROTATION_MATRIX_SIGN HLSLPP_MATRIX_LAYOUT_SIGN * HLSLPP_COORDINATES_SIGN

namespace hlslpp
{
	enum class ZClip
	{
		Zero,       // Clip points with z < 0 in projection coordinates
		NegativeOne // Clip points with z < -1 in projection coordinates
	};

	enum class ProjectionType
	{
		Perspective, // Frustrum is truncated pyramid
		Orthographic // Frustrum is parallelepiped
	};

	struct Frustrum
	{
		float xLeft;
		float xRight;
		float yBottom;
		float yTop;
		float zNear;
		float zFar;

		Frustrum(float xLeft, float xRight, float yBottom, float yTop, float zNear, float zFar)
			: xLeft(xLeft), xRight(xRight), yBottom(yBottom), yTop(yTop), zNear(zNear), zFar(zFar)
		{ }

		Frustrum(float width, float height, float zNear, float zFar)
			: xLeft(-width / 2.f), xRight(width / 2.f), yBottom(-height / 2.f), yTop(height / 2.f), zNear(zNear), zFar(zFar)
		{ }

		// Field of view fabric function should be used with perspective projections only
		// - fovAngleRad: either horizontal (x) or vertical (y) angle depending on function variant
		// - aspect: width / height

		static Frustrum withFieldOfViewX(float fovAngleRad, float aspect, float zNear, float zFar)
		{
			const float width = 2.f * zNear * tanf(fovAngleRad / 2.f);
			return Frustrum(width, width / aspect, zNear, zFar);
		}

		static Frustrum withFieldOfViewY(float fovAngleRad, float aspect, float zNear, float zFar)
		{
			const float height = 2.f * zNear * tanf(fovAngleRad / 2.f);
			return Frustrum(height * aspect, height, zNear, zFar);
		}

		float width() const  { return xRight - xLeft; }
		float height() const { return yTop - yBottom; }
		float depth() const  { return zFar - zNear; }
	};

	struct ProjectionSettings
	{
		Frustrum       frustrum;
		ProjectionType type;
		ZClip          zClip;

		ProjectionSettings(const Frustrum& frustrum, ProjectionType type, ZClip zClip)
			: frustrum(frustrum), type(type), zClip(zClip)
		{ }
	};

	// World to View coordinates transformation

	hlslpp_inline float4x4 float4x4_look_at(const float3& position, const float3& target, const float3& up)
	{
		const float3 look   = normalize(target - position) * HLSLPP_COORDINATES_SIGN;
		const float3 xRight = normalize(cross(up, look));
		const float3 upDir = cross(look, xRight);

#if HLSLPP_LOGICAL_LAYOUT == HLSLPP_LOGICAL_LAYOUT_ROW_MAJOR
		return float4x4(
			xRight.x,               upDir.x,               look.x,               0.f,
			xRight.y,               upDir.y,               look.y,               0.f,
			xRight.z,               upDir.z,               look.z,               0.f,
			-dot(position, xRight), -dot(position, upDir), -dot(position, look), 1.f
		);
#else
		return float4x4(
			float4(xRight, -dot(position, xRight)),
			float4(upDir,  -dot(position, upDir)),
			float4(look,   -dot(position, look)),
			float4(0.f, 0.f, 0.f, 1.f)
		);
#endif
	}

	// View to Projection coordinates transformation

	hlslpp_inline float4x4 float4x4_projection(const ProjectionSettings& proj)
	{
		const float invWidth  = 1.f / proj.frustrum.width();
		const float invHeight = 1.f / proj.frustrum.height();
		const float invDepth  = 1.f / proj.frustrum.depth();

		const float s  = HLSLPP_COORDINATES_SIGN;
		const float rl = proj.frustrum.xRight + proj.frustrum.xLeft;
		const float tb = proj.frustrum.yTop   + proj.frustrum.yBottom;

		if (proj.type == ProjectionType::Perspective)
		{
			const float dblNear = 2.f * proj.frustrum.zNear;
			const float nf  = proj.frustrum.zFar   + (proj.zClip == ZClip::Zero ? 0.f : proj.frustrum.zNear);
			const float m22 = s * nf * invDepth;
			const float m23 = proj.zClip == ZClip::Zero
			                ? -s * proj.frustrum.zNear * m22
			                : -2.f * proj.frustrum.zFar * proj.frustrum.zNear * invDepth;

#if HLSLPP_LOGICAL_LAYOUT == HLSLPP_LOGICAL_LAYOUT_ROW_MAJOR
			return float4x4(
				dblNear * invWidth, 0.f,                 0.f, 0.f,
				0.f,                dblNear * invHeight, 0.f, 0.f,
				-s * rl * invWidth, -s * tb * invHeight, m22, s,
				0.f,                0.f,                 m23, 0.f
			);
#else
			return float4x4(
				dblNear * invWidth, 0.f,                 -s * rl * invWidth,  0.f,
				0.f,                dblNear * invHeight, -s * tb * invHeight, 0.f,
				0.f,                0.f,                 m22,                 m23,
				0.f,                0.f,                 s,                   0.f
			);
#endif
		}
		else
		{
			const float nf = proj.frustrum.zNear  + (proj.zClip == ZClip::Zero ? 0.f : proj.frustrum.zFar);
			const float sd = s * (proj.zClip == ZClip::Zero ? 1.f : 2.f);

#if HLSLPP_LOGICAL_LAYOUT == HLSLPP_LOGICAL_LAYOUT_ROW_MAJOR
			return float4x4(
				2.f * invWidth, 0.f,             0.f,            0.f,
				0.f,            2.f * invHeight, 0.f,            0.f,
				0.f,            0.f,             sd * invDepth,  0.f,
				-rl * invWidth, -tb * invHeight, -nf * invDepth, 1.f
			);
#else
			return float4x4(
				2.f * invWidth, 0.f,             0.f,           -rl * invWidth,
				0.f,            2.f * invHeight, 0.f,           -tb * invHeight,
				0.f,            0.f,             sd * invDepth, -nf * invDepth,
				0.f,            0.f,             0.f,           1.f
			);
#endif
		}
	}

	// Scaling

	hlslpp_inline float2x2 float2x2_scale(float sx, float sy)
	{
		return float2x2(
			sx,  0.f,
			0.f, sy
		);
	}

	hlslpp_inline float2x2 float2x2_scale(const float2& s)
	{
		return float2x2_scale(s.x, s.y);
	}

	hlslpp_inline float2x2 float2x2_scale(float su)
	{
		return float2x2_scale(su, su);
	}

	hlslpp_inline float3x3 float3x3_scale(float sx, float sy, float sz = 1.f)
	{
		return float3x3(
			sx,  0.f, 0.f,
			0.f, sy,  0.f,
			0.f, 0.f, sz
		);
	}

	hlslpp_inline float3x3 float3x3_scale(const float3& s)
	{
		return float3x3_scale(s.x, s.y, s.z);
	}

	hlslpp_inline float3x3 float3x3_scale(const float2& s)
	{
		return float3x3_scale(s.x, s.y, 1.f);
	}

	hlslpp_inline float3x3 float3x3_scale(float su)
	{
		return float3x3_scale(su, su, su);
	}

	hlslpp_inline float4x4 float4x4_scale(float sx, float sy, float sz)
	{
		return float4x4(
			sx,  0.f, 0.f, 0.f,
			0.f, sy,  0.f, 0.f,
			0.f, 0.f, sz,  0.f,
			0.f, 0.f, 0.f, 1.f
		);
	}

	hlslpp_inline float4x4 float4x4_scale(const float3& s)
	{
		return float4x4_scale(s.x, s.y, s.z);
	}

	hlslpp_inline float4x4 float4x4_scale(float su)
	{
		return float4x4_scale(su, su, su);
	}

	// Rotation

	hlslpp_inline float2x2 float2x2_rotate(float angleRad)
	{
		const float s = sinf(angleRad) * HLSLPP_ROTATION_MATRIX_SIGN;
		const float c = cosf(angleRad);

		return float2x2(
			c,  s,
			-s, c
		);
	}

	hlslpp_inline float3x3 float3x3_rotate_z(float angleRad)
	{
		const float s = sinf(angleRad) * HLSLPP_ROTATION_MATRIX_SIGN;
		const float c = cosf(angleRad);

		return float3x3(
			c,   s,   0.f,
			-s,  c,   0.f,
			0.f, 0.f, 1.f
		);
	}

	hlslpp_inline float4x4 float4x4_rotate_z(float angleRad)
	{
		const float s = sinf(angleRad) * HLSLPP_ROTATION_MATRIX_SIGN;
		const float c = cosf(angleRad);

		return float4x4(
			c,   s,   0.f, 0.f,
			-s,  c,   0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f
		);
	}
	
	hlslpp_inline float3x3 float3x3_rotate_y(float angleRad)
	{
		const float s = sinf(angleRad) * HLSLPP_ROTATION_MATRIX_SIGN;
		const float c = cosf(angleRad);

		return float3x3(
			c,   0.f, -s,
			0.f, 1.f, 0.f,
			s,  0.f, c
		);
	}

	hlslpp_inline float4x4 float4x4_rotate_y(float angleRad)
	{
		const float s = sinf(angleRad) * HLSLPP_ROTATION_MATRIX_SIGN;
		const float c = cosf(angleRad);

		return float4x4(
			c,   0.f, -s,   0.f,
			0.f, 1.f, 0.f, 0.f,
			s,  0.f,  c,   0.f,
			0.f, 0.f, 0.f, 1.f
		);
	}

	hlslpp_inline float3x3 float3x3_rotate_x(float angleRad)
	{
		const float s = sinf(angleRad) * HLSLPP_ROTATION_MATRIX_SIGN;
		const float c = cosf(angleRad);

		return float3x3(
			1.f, 0.f, 0.f,
			0.f, c,   s,
			0.f, -s,  c
		);
	}

	hlslpp_inline float4x4 float4x4_rotate_x(float angleRad)
	{
		const float s = sinf(angleRad) * HLSLPP_ROTATION_MATRIX_SIGN;
		const float c = cosf(angleRad);

		return float4x4(
			1.f, 0.f, 0.f, 0.f,
			0.f, c,   s,   0.f,
			0.f, -s,  c,   0.f,
			0.f, 0.f, 0.f, 1.f
		);
	}

	hlslpp_inline float3x3 float3x3_rotate_axis(const float3& axis, float angleRad)
	{
		const float s  = sinf(angleRad) * HLSLPP_ROTATION_MATRIX_SIGN;
		const float c  = cosf(angleRad);

		const float3 as = axis * s;
		const float3 ac = axis * (1.f - c);
		const float3 v1 = axis * ac;
		const float3 v2 = axis * ac.yzx;

		return float3x3(
			v1.x + c,    v2.x + as.z, v2.z - as.y,
			v2.x - as.z, v1.y + c,    v2.y + as.x,
			v2.z + as.y, v2.y - as.x, v1.z + c
		);
	}

	hlslpp_inline float4x4 float4x4_rotate_axis(const float3& axis, float angleRad)
	{
		const float s  = sinf(angleRad) * HLSLPP_ROTATION_MATRIX_SIGN;
		const float c  = cosf(angleRad);

		const float3 as = axis * s;
		const float3 ac = axis * (1.f - c);
		const float3 v1 = axis * ac;
		const float3 v2 = axis * ac.yzx;

		return float4x4(
			v1.x + c,    v2.x + as.z, v2.z - as.y, 0.f,
			v2.x - as.z, v1.y + c,    v2.y + as.x, 0.f,
			v2.z + as.y, v2.y - as.x, v1.z + c,    0.f,
			0.f,         0.f,         0.f,         1.f
		);
	}

	// Translation

	hlslpp_inline float3x3 float3x3_translate(float tx, float ty)
	{
#if HLSLPP_LOGICAL_LAYOUT == HLSLPP_LOGICAL_LAYOUT_ROW_MAJOR
		return float3x3(
			1.f, 0.f, 0.f,
			0.f, 1.f, 0.f,
			tx,  ty,  1.f
		);
#else
		return float3x3(
			1.f, 0.f, tx,
			0.f, 1.f, ty,
			0.f, 0.f, 1.f
		);
#endif
	}

	hlslpp_inline float3x3 float3x3_translate(const float2& t)
	{
		return float3x3_translate(t.x, t.y);
	}

	hlslpp_inline float4x4 float4x4_translate(float tx, float ty, float tz)
	{
#if HLSLPP_LOGICAL_LAYOUT == HLSLPP_LOGICAL_LAYOUT_ROW_MAJOR
		return float4x4(
			1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			tx,  ty,  tz,  1.f
		);
#else
		return float4x4(
			1.f, 0.f, 0.f, tx,
			0.f, 1.f, 0.f, ty,
			0.f, 0.f, 1.f, tz,
			0.f, 0.f, 0.f, 1.f
		);
#endif
	}

	hlslpp_inline float4x4 float4x4_translate(const float3& t)
	{
		return float4x4_translate(t.x, t.y, t.z);
	}

} // namespace hlslpp
