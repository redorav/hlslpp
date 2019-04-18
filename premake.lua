require ('premake-xbox360/xbox360')

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

Platform360 = "Xbox 360"

PlatformAndroidARM = "Android ARM"

UnitTestProject = "unit_tests"
AndroidProject = "hlsl++_android"

-- Directories
srcDir = "src"

workspace("hlsl++")
	configurations { "Debug", "Release" }
	location (Workspace)
	
	includedirs
	{
		srcDir,
	}
	
	vectorextensions ("sse4.1")
	cppdialect("c++11")
		
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
	
		platforms { PlatformMSVC64, PlatformMSVC32, PlatformLLVM64, PlatformLLVM32, PlatformARM, PlatformARM64, PlatformAndroidARM, Platform360 }
	
		local llvmToolset;
		
		if (_ACTION == "vs2015") then
			llvmToolset = "msc-llvm-vs2014";
		else
			llvmToolset = "msc-llvm";
		end
		
		startproject(UnitTestProject)
		
		filter { "platforms:"..PlatformMSVC64 }
			toolset("msc")
			architecture("x64")
			vectorextensions("avx")
		
		filter { "platforms:"..PlatformMSVC32 }
			toolset("msc")
			vectorextensions("avx")
			
		filter { "platforms:"..PlatformLLVM64 }
			toolset(llvmToolset)
			architecture("x64")
			buildoptions { "-Wno-unused-variable -msse4.1" }
			
		filter { "platforms:"..PlatformLLVM32 }
			toolset(llvmToolset)
			buildoptions { "-Wno-unused-variable -msse4.1" }
			
		filter { "platforms:"..PlatformARM }
			architecture("arm")
			vectorextensions ("neon")
			
		filter { "platforms:"..PlatformARM64 }
			architecture("arm64")
			vectorextensions ("neon")
			
		filter { "platforms:"..PlatformAndroidARM }
			system("android")
			architecture("arm")
			vectorextensions("neon")
			buildoptions { "-Wno-unused-variable" }
			linkoptions { "-lm" } -- Link against the standard math library
			
		filter { "platforms:"..Platform360 }
			system("xbox360")
			vectorextensions ("default")
			defines("_XBOX")
			
		filter{}
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

project ("hlsl++")
	kind("staticlib")
	language("c++")
	files
	{
		srcDir.."/**.h",
		srcDir.."/hlsl++.cpp"
	}
	
project (UnitTestProject)
	kind("consoleapp")
	--links { "hlsl++" }
	files
	{
		srcDir.."/hlsl++_unit_tests.cpp",
		srcDir.."/**.natvis"
	}
	
	filter { "platforms:"..PlatformAndroidARM }
		kind("sharedlib")
		files
		{
			"src/android/android_native_app_glue.h",
			"src/android/android_native_app_glue.c",
		}
		
	filter{}
	
	includedirs
	{
		srcDir.."/**.h"
	}

project (AndroidProject)
	removeplatforms("*")
	platforms { AndroidARM }
	kind("Packaging") -- This type of project builds the apk
	architecture("arm")
	links (UnitTestProject) -- Android needs to link to the main project which was built as a dynamic library
	androidapplibname(UnitTestProject)
	files
	{
		"src/android/AndroidManifest.xml",
		"src/android/build.xml",
		"src/android/project.properties",
		"src/android/res/values/strings.xml",
	}