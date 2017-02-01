

Workspace = "workspace/".._ACTION

-- Compilers
PlatformMSVC64 = "MSVC 64"
PlatformMSVC32 = "MSVC 32"
PlatformLLVM = "LLVM"

-- Directories
srcDir = "src"

workspace "hlsl++"
	configurations { "Debug", "Release" }
	platforms { PlatformMSVC64, PlatformMSVC32, PlatformLLVM }
	location (Workspace)
	
	includedirs
	{
		srcDir,
	}
	
	filter { "platforms:"..PlatformMSVC64, "platforms:"..PlatformMSVC32,  }
		toolset("msc")
		
	filter { "platforms:"..PlatformLLVM }
		toolset("msc-llvm-vs2014")
		buildoptions { "-Wno-unused-variable -msse4.1" }

project "hlsl++"
	--kind("StaticLib")
	kind("WindowedApp")
	language("C++")
	files
	{
		srcDir.."/**.h", srcDir.."/**.cpp"
	}
	
project "UnitTests"
	kind("WindowedApp")
	--lalal
	
project("Natvis")
	kind("StaticLib")
	files{ srcDir.."/**.natvis" }