Xbox 360 module
===============

This module allows you to create projects that will compile with the Xbox 360 XDK.

How to use
==========

Clone or download the repository somewhere where Premake can find it. In your project's premake script import the module like this:

```lua
require("premake-xbox360/xbox360")
```

Example
=======

```lua
workspace "MyWorkspace"
	configurations { "Debug", "Release" }	
	
	platforms { "MyXbox360Config" }
	
	filter { "platforms:MyXbox360Config" }
		system("xbox360")
	
		-- Xbox360-specific properties
		xexoutput("test_output.xex")
		titleid("0x1234567")
		baseaddress("0x88000000")
		inlineassembly("true")
		prescheduling("true")
		callattributedprofiling("callcap")
```

The full list of available api extensions can be found in _preload.lua
