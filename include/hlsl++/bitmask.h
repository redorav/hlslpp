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

		template<typename To, typename From>
		To union_cast(const From& from)
		{
			static_assert(sizeof(From) == sizeof(To), "Size of From and To must be the same");

			union union_cast_helper
			{
				union_cast_helper(From from) : from(from) {}

				To to;
				From from;
			};

			union_cast_helper helper(from);
			return helper.to;
		}
	};
}