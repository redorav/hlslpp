
#if defined(_WIN32)
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#include <cstdio>
#include <iostream>

#include "hlsl++.h"
#include "hlsl++_unit_tests.h"

using std::cout;

int main()
{
	RunSpeedTests();
	RunUnitTests();
	RunExperiments();

	getchar();
}