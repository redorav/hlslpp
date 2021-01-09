#ifdef HLSLPP_FEATURE_TRANSFORM

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

namespace hlslpp
{

	enum class ZClip
	{
		Zero,       // Clip points with z < 0 in projection coordinates
		NegativeOne // Clip points with z < -1 in projection coordinates
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
			: xLeft(-width / 2.0f), xRight(width / 2.0f), yBottom(-height / 2.0f), yTop(height / 2.0f), zNear(zNear), zFar(zFar)
		{ }

		// Field of view fabric function should be used with perspective projections only
		// - fovAngleRad: either horizontal (x) or vertical (y) angle depending on function variant
		// - aspect: width / height

		static Frustrum withFieldOfViewX(float fovAngleRad, float aspect, float zNear, float zFar)
		{
			const float width = 2.0f * zNear * tanf(fovAngleRad / 2.0f);
			return Frustrum(width, width / aspect, zNear, zFar);
		}

		static Frustrum withFieldOfViewY(float fovAngleRad, float aspect, float zNear, float zFar)
		{
			const float height = 2.0f * zNear * tanf(fovAngleRad / 2.0f);
			return Frustrum(height * aspect, height, zNear, zFar);
		}

		float width() const  { return xRight - xLeft; }
		float height() const { return yTop - yBottom; }
		float depth() const  { return zFar - zNear; }
	};

	struct ProjectionSettings
	{
		Frustrum frustrum;
		ZClip    zClip;

		ProjectionSettings(const Frustrum& frustrum, ZClip zClip)
			: frustrum(frustrum), zClip(zClip)
		{ }
	};

} // namespace hlslpp

#endif // HLSLPP_FEATURE_TRANSFORM
