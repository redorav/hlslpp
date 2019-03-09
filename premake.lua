Workspace = "workspace/".._ACTION

-- Compilers
PlatformMSVC64	= "MSVC 64"
PlatformMSVC32	= "MSVC 32"
PlatformLLVM64	= "LLVM 64"
PlatformLLVM32	= "LLVM 32"

PlatformOSX64	= "OSX 64"

PlatformLinux64_GCC		= "Linux64_GCC"
PlatformLinux64_Clang	= "Linux64_Clang"

PlatformARM = "MSVC ARM"
PlatformARM64 = "MSVC ARM64"

-- Directories
srcDir = "src"

workspace "hlsl++"
	configurations { "Debug", "Release" }	
	location (Workspace)
	
	includedirs
	{
		srcDir,
	}
	
	vectorextensions ("SSE4.1")
		
	if(_ACTION == "xcode4") then
	
		platforms { PlatformOSX64 }
		toolset("clang")
		architecture("x64")
		buildoptions { "-std=c++11 -msse4.1 -Wno-unused-variable" }
		linkoptions { "-stdlib=libc++" }
		
	elseif(_ACTION == "gmake") then
	
		platforms { PlatformLinux64_GCC, PlatformLinux64_Clang }
		architecture("x64")
		buildoptions { "-std=c++11 -msse4.1 -Wno-unused-variable" }
		
		filter { "platforms:"..PlatformLinux64_GCC }
			toolset("gcc")
		
		filter { "platforms:"..PlatformLinux64_Clang }
			toolset("clang")
		
	else
	
		platforms { PlatformMSVC64, PlatformMSVC32, PlatformLLVM64, PlatformLLVM32, PlatformARM }
	
		filter { "platforms:"..PlatformMSVC64 }
			toolset("msc")
			architecture("x64")
		
		filter { "platforms:"..PlatformMSVC32 }
			toolset("msc")
			
		filter { "platforms:"..PlatformLLVM64 }
			toolset("msc-llvm")
			architecture("x64")
			buildoptions { "-Wno-unused-variable -msse4.1" }
			
		filter { "platforms:"..PlatformLLVM32 }
			toolset("msc-llvm")
			buildoptions { "-Wno-unused-variable -msse4.1" }
			
		filter { "platforms:"..PlatformARM }
			architecture("arm")
			vectorextensions ("default")
			
		-- Doesn't work until a future premake
		--filter { "platforms:"..PlatformARM64 }
			--architecture("arm64")
	
	end
	
	configuration "Debug"
		defines { "DEBUG" }
		symbols "on"
		inlining("auto") -- hlslpp relies on inlining for speed, big gains in debug builds without losing legibility
		optimize("debug")
		
	configuration "Release"
		defines { "NDEBUG" }
		optimize "on"
		inlining("auto")
		optimize("full")

project "hlsl++"
	kind("StaticLib")
	language("C++")
	files
	{
		srcDir.."/**.h",
		srcDir.."/hlsl++.cpp"
	}
	
project "unit_tests"
	kind("ConsoleApp")
	--links { "hlsl++" }
	files
	{
		srcDir.."/hlsl++_unit_tests.cpp",
		srcDir.."/**.natvis"
	}
	
	includedirs
	{
		srcDir.."/**.h"
	}