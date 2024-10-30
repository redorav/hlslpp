#pragma once

#include "hlsl++/vector_float_type.h"
#include "hlsl++/vector_uint.h"
#include "hlsl++/half.h"
#include "hlsl++/dependent.h"

hlslpp_module_export namespace hlslpp
{
	hlslpp_inline uint32_t pack_float4_rgba8_unorm(const float4& v)
	{
		return _hlslpp_pack_epu32_rgba8_unorm(v.vec);
	}
	
	hlslpp_inline float4 unpack_rgba8_unorm_float4(uint32_t p)
	{
		return float4(_hlslpp_unpack_rgba8_unorm_epu32(p));
	}
	
	hlslpp_inline uint32_t pack_float4_rgba8_snorm(const float4& v)
	{
		return _hlslpp_pack_epu32_rgba8_snorm(v.vec);
	}

	hlslpp_inline float4 unpack_rgba8_snorm_float4(uint32_t p)
	{
		return float4(_hlslpp_unpack_rgba8_snorm_epu32(p));
	}
	
	uint32_t pack_float3_rg11b10f(const float3& v)
	{
		uint32_t r11 = f32tof16(v.x);
		uint32_t g11 = f32tof16(v.y);
		uint32_t b10 = f32tof16(v.z);
		return ((r11 & 0x7ff0) << 17) | ((g11 & 0x7ff0) << 6) | ((b10 & 0x7fe0) >> 5);
	}

	float3 unpack_rg11b10f_float3(uint32_t packed)
	{
		uint32_t ri = (packed >> 17) & 0x7ff0;
		uint32_t gi = (packed >> 6) & 0x7ff0;
		uint32_t bi = (packed << 5) & 0x7fe0;
		return float3(f16tof32(ri), f16tof32(gi), f16tof32(bi));
	}
	
	// https://github.com/microsoft/DirectX-Graphics-Samples/blob/58cdb4ee7ce9d1b4c5e2f4e39e97885750591a6a/MiniEngine/Core/Shaders/PixelPacking_RGBE.hlsli#L17
	hlslpp_inline uint32_t pack_float3_rgb9e5f(const float3& v)
	{
		// Clamp the channels to an expressible range
		const float MaxValue = asfloat(0x477f8000); // 0.ff x 2^+15
	
		float3 clampedValue = clamp(v, 0.0f, MaxValue);
	
		// Compute maximum channel of clamped value
		float maxChannel = max(clampedValue.x, max(clampedValue.y, clampedValue.z));
	
		// 'bias' has to have the biggest exponent plus 15 (and nothing in the mantissa). When added to the three channels, 
		// it shifts the explicit '1' and the 8 most significant mantissa bits into the low 9 bits. IEEE rules of float 
		// addition will round rather than truncate the discarded bits. Channels with smaller natural exponents will be
		// shifted further to the right (discarding more bits)

		// Reinterpret the maximum channel as a uint
		uint32_t maxChannelUint = asuint(maxChannel);

		// Bias the exponent by 15, and shift the mantissa into the low 9 bits
		// 0x07804000 == 0b 0 00001111 00000000100000000000000
		uint32_t maxChannelBiased = maxChannelUint + 0x07804000;

		// Keep only the exponent of the resulting float
		// 0x7F800000 == 0b 0 11111111 00000000000000000000000
		uint32_t biasu = maxChannelBiased & 0x7F800000;

		// Shift the bias 4 positions to keep only 5 bits
		uint32_t biass = biasu << 4;
		uint32_t exponent = biass + 0x10000000;

		// Turn bias back into float and add to the original value to shift bits into the right places
		float bias = asfloat(biasu);

		float3 clampedBiased = clampedValue + bias;
		uint3 rgb = (uint3&)(clampedBiased);

		return exponent | rgb.z << 18 | rgb.y << 9 | (rgb.x & 0x1ff);
	}
	
	hlslpp_inline float3 unpack_rgb9e5f_float3(uint32_t p)
	{
		float3 rgb = uint3(p, p >> 9, p >> 18) & uint3(0x1ff);
		return ldexp(rgb, (int)(p >> 27) - 24);
	}
}