//---------------------------------//
// Special Transformation Matrices //
//---------------------------------//

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

	struct Frustrum
	{
		float left;
		float right;
		float bottom;
		float top;
		float near;
		float far;

		Frustrum(float left, float right, float bottom, float top, float near, float far)
			: left(left), right(right), bottom(bottom), top(top), near(near), far(far)
		{ }

		Frustrum(float width, float height, float near, float far)
			: left(-width / 2.f), right(width / 2.f), bottom(-height / 2.f), top(height / 2.f), near(near), far(far)
		{ }

		static Frustrum WithFieldOfViewX(float fov_x, float aspect, float near, float far)
		{
			const float width = 2.f * near * tanf(fov_x / 2.f);
			return Frustrum(width, width / aspect, near, far);
		}

		static Frustrum WithFieldOfViewY(float fov_y, float aspect, float near, float far)
		{
			const float height = 2.f * near * tanf(fov_y / 2.f);
			return Frustrum(height * aspect, height, near, far);
		}

		float width() const  { return right - left; }
		float height() const { return top - bottom; }
		float depth() const  { return far - near; }
	};

	struct ProjectionSettings
	{
		Frustrum    frustrum;
		bool        zclip_zero;
		Coordinates coordinates;

		ProjectionSettings(const Frustrum& frustrum, bool zclip_zero, Coordinates coordinates = Coordinates::LeftHanded)
			: frustrum(frustrum), zclip_zero(zclip_zero), coordinates(coordinates)
		{ }
	};

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
		return float3x3_translate(t.x, t.y);
	}

	hlslpp_inline float4x4 float4x4_translate(float tx, float ty, float tz, MatrixLayout layout = MatrixLayout::RowMajor)
	{
		return float4x4(
			1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			tx,  ty,  tz,  1.f
		);
	}

	hlslpp_inline float4x4 float4x4_translate(const float3& t, MatrixLayout layout = MatrixLayout::RowMajor)
	{
		return float4x4_translate(t.x, t.y, t.z);
	}

	// World to View coordinates transformation

	hlslpp_inline float4x4 float4x4_look_at(const float3& position, const float3& target, const float3& up,
											Coordinates coordinates = Coordinates::LeftHanded,
											MatrixLayout layout = MatrixLayout::RowMajor)
	{
		const float3 look = normalize(target - position) * (coordinates == Coordinates::LeftHanded ? 1.f : -1.f);
		const float3 right = normalize(cross(up, look));
		const float3 up_dir = cross(look, right);

		return layout == MatrixLayout::RowMajor
			? float4x4(
				right.x,               up_dir.x,               look.x,               0.f,
				right.y,               up_dir.y,               look.y,               0.f,
				right.z,               up_dir.z,               look.z,               0.f,
				-dot(position, right), -dot(position, up_dir), -dot(position, look), 1.f
			)
			: float4x4(
				float4(right,  -dot(position, right)),
				float4(up_dir, -dot(position, up_dir)),
				float4(look,   -dot(position, look)),
				float4(0.f, 0.f, 0.f, 1.f)
			);
	}

	// View to Orthographic Projection coordinates transformation

	hlslpp_inline float4x4 float4x4_orthographic(const ProjectionSettings& settings, MatrixLayout layout = MatrixLayout::RowMajor)
	{
		const float inv_width  = 1.f / settings.frustrum.width();
		const float inv_height = 1.f / settings.frustrum.height();
		const float inv_depth  = 1.f / settings.frustrum.depth();
		const float s = settings.coordinates == Coordinates::LeftHanded ? 1.f : -1.f;

		const float rl = settings.frustrum.right + settings.frustrum.left;
		const float tb = settings.frustrum.top   + settings.frustrum.bottom;
		const float nf = settings.frustrum.near  + (settings.zclip_zero ? 0.f : settings.frustrum.far);
		const float sd = s * (settings.zclip_zero ? 1.f : 2.f);

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

	// View to Perspective Projection coordinates transformation

	hlslpp_inline float4x4 float4x4_perspective(const ProjectionSettings& settings, MatrixLayout layout = MatrixLayout::RowMajor)
	{
		const float inv_width  = 1.f / settings.frustrum.width();
		const float inv_height = 1.f / settings.frustrum.height();
		const float inv_depth  = 1.f / settings.frustrum.depth();
		const float dbl_near   = 2.f * settings.frustrum.near;

		const float s   = settings.coordinates == Coordinates::LeftHanded ? 1.f : -1.f;
		const float rl  = settings.frustrum.right + settings.frustrum.left;
		const float tb  = settings.frustrum.top   + settings.frustrum.bottom;
		const float nf  = settings.frustrum.far   + (settings.zclip_zero ? 0.f : settings.frustrum.near);
		const float m22 = s * nf * inv_depth;
		const float m23 = settings.zclip_zero
		                ? -s * settings.frustrum.near * m22
		                : -2.f * settings.frustrum.far * settings.frustrum.near * inv_depth;

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

} // namespace hlslpp
