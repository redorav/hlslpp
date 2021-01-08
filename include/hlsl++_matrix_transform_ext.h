//---------------------------------//
// Special Transformation Matrices //
//   (Optional Extension Header)   //
//---------------------------------//
#pragma once

#include "hlsl++.h"

#include <math.h>

namespace hlslpp
{
	enum class MatrixLayout
	{
		RowMajor,   // Row-Major matrix layout assumes "vector-row(N) * matrix(NxM)" multiplication order
		ColumnMajor // Column-Major matrix layout assumes "matrix(MxN) * vector-col(N)" multiplication order
	};

	enum class Coordinates
	{
		LeftHanded, // The positive x, y and z axes point right, up and forward.  Positive rotation is clockwise about the axis of rotation. (used in DirectX)
		RightHanded // The positive x, y and z axes point right, up and backward. Positive rotation is counterclockwise about the axis of rotation. (used in OpenGL)
	};

	enum class ZClip
	{
		Zero,		// Clip all points wtih z < 0
		NegativeOne // Clip all points wtih z < -1
	};

    enum class ProjectionType
    {
        Perspective, // Frustrum is truncated pyramid
        Orthographic // Frustrum is parallelepiped
    };

	struct Frustrum
	{
		float x_left;
		float x_right;
		float y_bottom;
		float y_top;
		float z_near;
		float z_far;

		Frustrum(float x_left, float x_right, float y_bottom, float y_top, float z_near, float z_far)
			: x_left(x_left), x_right(x_right), y_bottom(y_bottom), y_top(y_top), z_near(z_near), z_far(z_far)
		{ }

		Frustrum(float width, float height, float z_near, float z_far)
			: x_left(-width / 2.f), x_right(width / 2.f), y_bottom(-height / 2.f), y_top(height / 2.f), z_near(z_near), z_far(z_far)
		{ }

		// Field of view fabric function should be used with perspective projections only
		// - fov_angle_rad is either horizontal (x) or vertical (y) angle depending on function variant
		// - aspect = width / height

		static Frustrum WithFieldOfViewX(float fov_angle_rad, float aspect, float z_near, float z_far)
		{
			const float width = 2.f * z_near * tanf(fov_angle_rad / 2.f);
			return Frustrum(width, width / aspect, z_near, z_far);
		}

		static Frustrum WithFieldOfViewY(float fov_angle_rad, float aspect, float z_near, float z_far)
		{
			const float height = 2.f * z_near * tanf(fov_angle_rad / 2.f);
			return Frustrum(height * aspect, height, z_near, z_far);
		}

		float width() const  { return x_right - x_left; }
		float height() const { return y_top - y_bottom; }
		float depth() const  { return z_far - z_near; }
	};

	struct ProjectionSettings
	{
		Frustrum       frustrum;
		ProjectionType type;
		ZClip          zclip;
		Coordinates    coordinates;

		ProjectionSettings(const Frustrum& frustrum, ProjectionType type, ZClip zclip, Coordinates coordinates = Coordinates::LeftHanded)
			: frustrum(frustrum), type(type), zclip(zclip), coordinates(coordinates)
		{ }
	};

	// World to View coordinates transformation

	hlslpp_inline float4x4 float4x4_look_at(const float3& position, const float3& target, const float3& up,
											Coordinates coordinates = Coordinates::LeftHanded,
											MatrixLayout layout = MatrixLayout::RowMajor)
	{
		const float3 look = normalize(target - position) * (coordinates == Coordinates::LeftHanded ? 1.f : -1.f);
		const float3 x_right = normalize(cross(up, look));
		const float3 up_dir = cross(look, x_right);

		return layout == MatrixLayout::RowMajor
			? float4x4(
				x_right.x,               up_dir.x,               look.x,               0.f,
				x_right.y,               up_dir.y,               look.y,               0.f,
				x_right.z,               up_dir.z,               look.z,               0.f,
				-dot(position, x_right), -dot(position, up_dir), -dot(position, look), 1.f
			)
			: float4x4(
				float4(x_right,  -dot(position, x_right)),
				float4(up_dir, -dot(position, up_dir)),
				float4(look,   -dot(position, look)),
				float4(0.f, 0.f, 0.f, 1.f)
			);
	}

	// View to Projection coordinates transformation

	hlslpp_inline float4x4 float4x4_projection(const ProjectionSettings& proj, MatrixLayout layout = MatrixLayout::RowMajor)
	{
		const float inv_width  = 1.f / proj.frustrum.width();
		const float inv_height = 1.f / proj.frustrum.height();
		const float inv_depth  = 1.f / proj.frustrum.depth();

		const float s  = proj.coordinates == Coordinates::LeftHanded ? 1.f : -1.f;
		const float rl = proj.frustrum.x_right + proj.frustrum.x_left;
		const float tb = proj.frustrum.y_top   + proj.frustrum.y_bottom;

		if (proj.type == ProjectionType::Perspective)
		{
			const float dbl_near = 2.f * proj.frustrum.z_near;
			const float nf  = proj.frustrum.z_far   + (proj.zclip == ZClip::Zero ? 0.f : proj.frustrum.z_near);
			const float m22 = s * nf * inv_depth;
			const float m23 = proj.zclip == ZClip::Zero
			                ? -s * proj.frustrum.z_near * m22
			                : -2.f * proj.frustrum.z_far * proj.frustrum.z_near * inv_depth;

			return layout == MatrixLayout::RowMajor
				? float4x4(
					dbl_near * inv_width, 0.f,                   0.f, 0.f,
					0.f,                  dbl_near * inv_height, 0.f, 0.f,
					-s * rl * inv_width,  -s * tb * inv_height,  m22, s,
					0.f,                  0.f,                   m23, 0.f
				)
				: float4x4(
					dbl_near * inv_width, 0.f,                   -s * rl * inv_width,  0.f,
					0.f,                  dbl_near * inv_height, -s * tb * inv_height, 0.f,
					0.f,                  0.f,                   m22,                  m23,
					0.f,                  0.f,                   s,                    0.f
				);
		}
		else
		{
			const float nf = proj.frustrum.z_near  + (proj.zclip == ZClip::Zero ? 0.f : proj.frustrum.z_far);
			const float sd = s * (proj.zclip == ZClip::Zero ? 1.f : 2.f);

			return layout == MatrixLayout::RowMajor
				? float4x4(
					2.f * inv_width, 0.f,              0.f,             0.f,
					0.f,             2.f * inv_height, 0.f,             0.f,
					0.f,             0.f,              sd * inv_depth,  0.f,
					-rl * inv_width, -tb * inv_height, -nf * inv_depth, 1.f
				)
				: float4x4(
					2.f * inv_width, 0.f,              0.f,             -rl * inv_width,
					0.f,             2.f * inv_height, 0.f,             -tb * inv_height,
					0.f,             0.f,              sd * inv_depth,  -nf * inv_depth,
					0.f,             0.f,              0.f,             1.f
				);
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

	hlslpp_inline float2x2 float2x2_rotate(float angle_rad)
	{
		const float s = sinf(angle_rad);
		const float c = cosf(angle_rad);

		return float2x2(
			c,  s,
			-s, c
		);
	}

	hlslpp_inline float3x3 float3x3_rotate_z(float angle_rad)
	{
		const float s = sinf(angle_rad);
		const float c = cosf(angle_rad);

		return float3x3(
			c,   s,   0.f,
			-s,  c,   0.f,
			0.f, 0.f, 1.f
		);
	}

	hlslpp_inline float4x4 float4x4_rotate_z(float angle_rad)
	{
		const float s = sinf(angle_rad);
		const float c = cosf(angle_rad);

		return float4x4(
			c,   s,   0.f, 0.f,
			-s,  c,   0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f
		);
	}
	
	hlslpp_inline float3x3 float3x3_rotate_y(float angle_rad)
	{
		const float s = sinf(angle_rad);
		const float c = cosf(angle_rad);

		return float3x3(
			c,   0.f, -s,
			0.f, 1.f, 0.f,
			s,  0.f, c
		);
	}

	hlslpp_inline float4x4 float4x4_rotate_y(float angle_rad)
	{
		const float s = sinf(angle_rad);
		const float c = cosf(angle_rad);

		return float4x4(
			c,   0.f, -s,   0.f,
			0.f, 1.f, 0.f, 0.f,
			s,  0.f,  c,   0.f,
			0.f, 0.f, 0.f, 1.f
		);
	}

	hlslpp_inline float3x3 float3x3_rotate_x(float angle_rad)
	{
		const float s = sinf(angle_rad);
		const float c = cosf(angle_rad);

		return float3x3(
			1.f, 0.f, 0.f,
			0.f, c,   s,
			0.f, -s,  c
		);
	}

	hlslpp_inline float4x4 float4x4_rotate_x(float angle_rad)
	{
		const float s = sinf(angle_rad);
		const float c = cosf(angle_rad);

		return float4x4(
			1.f, 0.f, 0.f, 0.f,
			0.f, c,   s,   0.f,
			0.f, -s,  c,   0.f,
			0.f, 0.f, 0.f, 1.f
		);
	}

	hlslpp_inline float3x3 float3x3_rotate_axis(const float3& axis, float angle_rad)
	{
		const float s  = sinf(angle_rad);
		const float c  = cosf(angle_rad);

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

	hlslpp_inline float4x4 float4x4_rotate_axis(const float3& axis, float angle_rad)
	{
		const float s  = sinf(angle_rad);
		const float c  = cosf(angle_rad);

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

	hlslpp_inline float3x3 float3x3_translate(float tx, float ty, MatrixLayout layout = MatrixLayout::RowMajor)
	{
		return layout == MatrixLayout::RowMajor
			? float3x3(
				1.f, 0.f, 0.f,
				0.f, 1.f, 0.f,
				tx,  ty,  1.f
			)
			: float3x3(
				1.f, 0.f, tx,
				0.f, 1.f, ty,
				0.f, 0.f, 1.f
			);
	}

	hlslpp_inline float3x3 float3x3_translate(const float2& t, MatrixLayout layout = MatrixLayout::RowMajor)
	{
		return float3x3_translate(t.x, t.y, layout);
	}

	hlslpp_inline float4x4 float4x4_translate(float tx, float ty, float tz, MatrixLayout layout = MatrixLayout::RowMajor)
	{
		return layout == MatrixLayout::RowMajor
			? float4x4(
				1.f, 0.f, 0.f, 0.f,
				0.f, 1.f, 0.f, 0.f,
				0.f, 0.f, 1.f, 0.f,
				tx,  ty,  tz,  1.f
			)
			: float4x4(
				1.f, 0.f, 0.f, tx,
				0.f, 1.f, 0.f, ty,
				0.f, 0.f, 1.f, tz,
				0.f, 0.f, 0.f, 1.f
			);
	}

	hlslpp_inline float4x4 float4x4_translate(const float3& t, MatrixLayout layout = MatrixLayout::RowMajor)
	{
		return float4x4_translate(t.x, t.y, t.z, layout);
	}

} // namespace hlslpp
