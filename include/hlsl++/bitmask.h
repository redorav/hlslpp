#pragma once

#include "hlsl++/config.h"

namespace hlslpp
{
	namespace detail
	{
		union packed_union
		{
			packed_union() {}
			explicit packed_union(uint32_t u32) : _u32(u32) {}
			explicit packed_union(int32_t i32) : _i32(i32) {}
			explicit packed_union(float f32) : _f32(f32) {}

			uint32_t _u32;
			int32_t _i32;
			float _f32;
			uint8_t _u8[4];
			char _c[4];
		};
	};

	const detail::packed_union fffMask(0xffffffffu); // Negative NaN
	const detail::packed_union nanMask(0x7fffffffu); // Positive NaN
	const detail::packed_union infMask(0x7f800000u);
	const detail::packed_union minusinfMask(0xff800000u);
	const detail::packed_union absMask(0x7fffffffu);
	const detail::packed_union negMask(0x80000000u);
}