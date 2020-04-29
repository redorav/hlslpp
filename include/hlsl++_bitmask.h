#include <cstdint>

namespace hlslpp
{
	union BitMask
	{
		uint32_t i;
		float f;
		explicit BitMask(uint32_t i) : i(i) {}
		explicit BitMask(float f) : f(f) {}
	};

	const BitMask fffMask(0xffffffffu); // Negative NaN
	const BitMask nanMask(0x7fffffffu); // Positive NaN
	const BitMask infMask(0x7f800000u);
	const BitMask minusinfMask(0xff800000u);
	const BitMask absMask(0x7fffffffu);
	const BitMask negMask(0x80000000u);
}