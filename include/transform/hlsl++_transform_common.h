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
// It can be changed by overriding this definition value in external project
#ifndef HLSLPP_LOGICAL_LAYOUT
	#define HLSLPP_LOGICAL_LAYOUT HLSLPP_LOGICAL_LAYOUT_ROW_MAJOR
#endif

// Left-Handed coordinate system (default,  in DirectX and Metal):
// The positive x, y and z axes point right, up and forward.
// Positive rotation is clockwise about the axis of rotation. ()
#define HLSLPP_COORDINATES_LEFT_HANDED 0

// Right-Handed coordinate system (optional, used in OpenGL and Vulkan):
// The positive x, y and z axes point right, up and backward.
// Positive rotation is counterclockwise about the axis of rotation.
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

namespace hlslpp
{

	enum class zclip
	{
		zero,        // Clip points with z < 0 in projection coordinates
		negative_one // Clip points with z < -1 in projection coordinates
	};

	struct frustrum
	{
		float left_x;
		float right_x;
		float bottom_y;
		float top_y;
		float near_z;
		float far_z;

		frustrum(float left_x, float right_x, float bottom_y, float top_y, float near_z, float far_z)
			: left_x(left_x), right_x(right_x), bottom_y(bottom_y), top_y(top_y), near_z(near_z), far_z(far_z)
		{ }

		frustrum(float width, float height, float near_z, float far_z)
			: left_x(-width / 2.0f), right_x(width / 2.0f), bottom_y(-height / 2.0f), top_y(height / 2.0f), near_z(near_z), far_z(far_z)
		{ }

		// Field of view functions should be used for perspective projections only
		// - fov_angle_rad: either horizontal (x) or vertical (y) angle depending on function variant
		// - aspect: width / height

		static frustrum field_of_view_x(float fov_angle_rad, float aspect, float near_z, float far_z)
		{
			const float width = 2.0f * near_z * tanf(fov_angle_rad / 2.0f);
			return frustrum(width, width / aspect, near_z, far_z);
		}

		static frustrum field_of_view_y(float fov_angle_rad, float aspect, float near_z, float far_z)
		{
			const float height = 2.0f * near_z * tanf(fov_angle_rad / 2.0f);
			return frustrum(height * aspect, height, near_z, far_z);
		}

		float width() const  { return right_x - left_x; }
		float height() const { return top_y - bottom_y; }
		float depth() const  { return far_z - near_z; }
	};

	struct projection
	{
		frustrum frust;
		zclip    z_clip;

		projection(const frustrum& frust, zclip z_clip)
			: frust(frust), z_clip(z_clip)
		{ }
	};

} // namespace hlslpp

#endif // HLSLPP_FEATURE_TRANSFORM
