#pragma once

//------------------------------------------------------------------
// Common Transformation Macro-Definitions and Types
//
// HLSL++ assumes a left-handed coordinate system for view and 
// projection matrices by default. In a left-handed system 
// positive rotations around an angle naturally move clockwise,
// e.g. rotating the z axis 90 degrees around y returns the x axis.
// 
// However in a right-handed coordinate system, applying the
// same transform computes the same numerical result but ends
// up being a different physical rotation as it becomes anti-
// clockwise. For that reason we must flip the sign of the angle.
// The same thing happens with quaternions.
// 
// HLSL++ also assumes a logical row major layout, i.e. vectors are
// laid out like a row, e.g.
// 
// [ x y z w ] * | m00 m01 m02 m03 |
//               | m10 m11 m12 m13 |
//               | m20 m21 m22 m23 |
//               | m30 m31 m32 m33 |
// 
// This property also changes which direction an angle goes in as
// a rotation matrix's inverse is the same as its transpose.
// 
// These defaults can be changed by defining HLSLPP_LOGICAL_LAYOUT
// and/or HLSLPP_COORDINATES
// 
// Because of this behavior (where angles get flipped) creating your
// own matrices and quaternions only works if you know that the raw
// values being put in correspond to the convention you're using,
// because those do not get reversed
//------------------------------------------------------------------

#if defined(HLSLPP_MODULE_DECLARATION)
import <math.h>;
#else
#include <math.h>
#endif

// Row-Major logical layout (default)
// assumes "vector-row(N) * matrix(NxM)" multiplication order
#define HLSLPP_LOGICAL_LAYOUT_ROW_MAJOR 0

// Column-Major logical layout (optional)
// assumes "matrix(MxN) * vector-column(N)" multiplication order
#define HLSLPP_LOGICAL_LAYOUT_COL_MAJOR 1

// Default HLSL++ logical layout is Row-Major
// It can be changed by overriding this definition value externally
#if !defined(HLSLPP_LOGICAL_LAYOUT)
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
#if !defined(HLSLPP_COORDINATES)
	#define HLSLPP_COORDINATES HLSLPP_COORDINATES_LEFT_HANDED
#endif

#if HLSLPP_COORDINATES == HLSLPP_COORDINATES_LEFT_HANDED
	#define HLSLPP_COORDINATES_SIGN 1.0f
#else
	#define HLSLPP_COORDINATES_SIGN -1.0f
#endif

// If row major and right handed, or column major and left handed, we need to swap sign
// In other cases either we don't need to do anything or two swaps cancel each other
#if ((HLSLPP_LOGICAL_LAYOUT == HLSLPP_LOGICAL_LAYOUT_ROW_MAJOR) && (HLSLPP_COORDINATES == HLSLPP_COORDINATES_RIGHT_HANDED)) || \
	((HLSLPP_LOGICAL_LAYOUT == HLSLPP_LOGICAL_LAYOUT_COL_MAJOR) && (HLSLPP_COORDINATES == HLSLPP_COORDINATES_LEFT_HANDED))

	#define HLSLPP_LAYOUT_COORDINATES_FLIP_SIGN

#endif

#if defined(HLSLPP_FEATURE_TRANSFORM)

hlslpp_module_export namespace hlslpp
{
	namespace zclip
	{
		enum t
		{
			zero,     // Clip points with z < 0 in projection coordinates (e.g. DirectX, Vulkan, Metal)
			minus_one // Clip points with z < -1 in projection coordinates (e.g. OpenGL)
		};
	}
	
	namespace zdirection
	{
		enum t
		{
			forward, // Near plane maps to 0, far plane maps to 1
			reverse  // Near plane maps to 1, far plane maps to 0
		};
	};

	namespace zplane
	{
		enum t
		{
			finite,  // Far plane is at value specified by the frustum
			infinite // Far plane is at +infinity
		};
	};

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
		zdirection::t z_direction;
		zplane::t z_plane;

		projection(const frustum& frustum_planes, zclip::t z_clip)
			: frustum_planes(frustum_planes), z_clip(z_clip), z_direction(zdirection::forward), z_plane(zplane::finite) {}
		
		projection(const frustum& frustum_planes, zclip::t z_clip, zdirection::t z_direction, zplane::t z_plane)
			: frustum_planes(frustum_planes), z_clip(z_clip), z_direction(z_direction), z_plane(z_plane) {}
	};
}

#endif
