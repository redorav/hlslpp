#ifdef HLSLPP_FEATURE_TRANSFORM

//-------//
// Scale //
//-------//

static hlslpp_inline float2x2 scale(float sx, float sy)
{
	return float2x2(
		sx,   0.0f,
		0.0f, sy
	);
}

static hlslpp_inline float2x2 scale(const float2& s)
{
	return scale(s.x, s.y);
}

static hlslpp_inline float2x2 scale(float su)
{
	return scale(su, su);
}

//----------//
// Rotation //
//----------//

static hlslpp_inline float2x2 rotation(float angleRad)
{
	const float s = sinf(angleRad) * HLSLPP_MATRIX_LAYOUT_SIGN * HLSLPP_COORDINATES_SIGN;
	const float c = cosf(angleRad);

	return float2x2(
		c,  s,
		-s, c
	);
}

#endif // HLSLPP_FEATURE_TRANSFORM
