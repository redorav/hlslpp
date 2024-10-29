#pragma once

#include "hlsl++/common.h"

namespace hlslpp
{
	class half;

	namespace binary
	{
		enum t
		{
			tag
		};
	}

	union float_bits
	{
		explicit float_bits(float f) : f(f) {}
		explicit float_bits(uint32_t u) : u(u) {}

		float f;
		uint32_t u;
	};

	// https://stackoverflow.com/questions/1659440/32-bit-to-16-bit-floating-point-conversion

	inline uint16_t float2half(float value)
	{
		const uint32_t b = float_bits(value).u + 0x00001000; // round-to-nearest-even: add last bit after truncated mantissa
		const uint32_t e = (b & 0x7F800000) >> 23; // exponent
		const uint32_t m = b & 0x007FFFFF;         // mantissa; in line below: 0x007FF000 = 0x00800000-0x00001000 = decimal indicator flag - initial rounding
		const uint32_t result = 
			(b & 0x80000000) >> 16 | 
			(e > 112) * ((((e - 112) << 10) & 0x7C00) | m >> 13) | 
			((e < 113) & (e > 101)) * ((((0x007FF000 + m) >> (125 - e)) + 1) >> 1) | 
			(e > 143) * 0x7FFF; // sign : normalized : denormalized : saturate

		return (uint16_t)result;
	}

	inline float half2float(uint16_t h)
	{
		const uint32_t e = (uint32_t)((h & 0x7C00) >> 10); // exponent
		const uint32_t m = (uint32_t)((h & 0x03FF) << 13); // mantissa
		const uint32_t v = float_bits((float)m).u >> 23; // evil log2 bit hack to count leading zeros in denormalized format
		const uint32_t result = 
			(uint32_t)((h & 0x8000) << 16) | 
			(uint32_t)((e != 0) * ((e + 112) << 23 | m)) |
			(uint32_t)(((e == 0) & (m != 0)) * ((v - 37) << 23 | ((m << (150 - v)) & 0x007FE000))); // sign : normalized : denormalized

		return float_bits(result).f;
	}

	hlslpp_inline uint32_t f32tof16(float f)
	{
		return (uint32_t)float2half(f);
	}

	hlslpp_inline float f16tof32(uint32_t h)
	{
		return half2float((uint16_t)h);
	}

	class half
	{
	public:

		half() : binary_value(0) {}

		explicit half(float f) : binary_value(float2half(f)) {}

		explicit half(binary::t, uint16_t binary_value) : binary_value(binary_value) {}

		operator float() const
		{
			return half2float(binary_value);
		}

	private:

		uint16_t binary_value;
	};

#if defined(HLSLPP_USER_DEFINED_LITERALS)

	namespace half_literal
	{
		inline half operator "" _h(long double value)
		{
			return half(binary::tag, float2half((float)value));
		}
	}

#endif
};
