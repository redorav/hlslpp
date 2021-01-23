//---------------------------------------------------//
// Common Transformation Macro-Definitions and Types //
//---------------------------------------------------//

#ifdef HLSLPP_FEATURE_TRANSFORM

#include <cmath>

// Row-Major logical layout (default)
// assumes "vector-row(N) * matrix(NxM)" multiplication order
#define HLSLPP_LOGICAL_LAYOUT_ROW_MAJOR 0

// Column-Major logical layout (optional)
// assumes "matrix(MxN) * vector-column(N)" multiplication order
#define HLSLPP_LOGICAL_LAYOUT_COL_MAJOR 1

// Default HLSL++ logical layout is Row-Major
// It can be changed by overriding this definition value externally
#ifndef HLSLPP_LOGICAL_LAYOUT
	#define HLSLPP_LOGICAL_LAYOUT HLSLPP_LOGICAL_LAYOUT_ROW_MAJOR
#endif

// Left-Handed coordinate system (e.g. DirectX, Metal)
// The positive x, y and z axes point right, up and forward.
// Positive rotation is clockwise about the axis of rotation.
#define HLSLPP_COORDINATES_LEFT_HANDED 0

// Right-Handed coordinate system (e.g. OpenGL, Vulkan)
// The positive x, y and z axes point right, up and backward.
// Positive rotation is counterclockwise about the axis of rotation.
#define HLSLPP_COORDINATES_RIGHT_HANDED 1

// Default HLSL++ coordinate system is Left-Handed
// It can be changed by overriding this definition value externally
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

namespace hlslpp
{
	namespace zclip
	{
		enum t
		{
			zero,     // Clip points with z < 0 in projection coordinates (e.g. DirectX, Vulkan, Metal)
			minus_one // Clip points with z < -1 in projection coordinates (e.g. OpenGL)
		};
	}

	struct frustum
	{
		float left;
		float right;
		float bottom;
		float top;
		float near_z;
		float far_z;

		frustum(float left, float right, float bottom, float top, float near_z, float far_z)
			: left(left), right(right), bottom(bottom), top(top), near_z(near_z), far_z(far_z)
		{ }

		frustum(float width, float height, float near_z, float far_z)
			: left(-width / 2.0f), right(width / 2.0f), bottom(-height / 2.0f), top(height / 2.0f), near_z(near_z), far_z(far_z)
		{ }

		// Field of view functions should be used for perspective projections only
		// - fov_angle_rad: either horizontal (x) or vertical (y) angle depending on function variant
		// - aspect: width / height

		static frustum field_of_view_x(float fov_angle_rad, float aspect, float near_z, float far_z)
		{
			const float width = 2.0f * near_z * tanf(fov_angle_rad / 2.0f);
			return frustum(width, width / aspect, near_z, far_z);
		}

		static frustum field_of_view_y(float fov_angle_rad, float aspect, float near_z, float far_z)
		{
			const float height = 2.0f * near_z * tanf(fov_angle_rad / 2.0f);
			return frustum(height * aspect, height, near_z, far_z);
		}

		float width() const  { return right - left; }
		float height() const { return top - bottom; }
		float depth() const  { return far_z - near_z; }
	};

	struct projection
	{
		frustum  frustum_planes;
		zclip::t z_clip;

		projection(const frustum& frustum_planes, zclip::t z_clip)
			: frustum_planes(frustum_planes), z_clip(z_clip) {}
	};
}

#endif
