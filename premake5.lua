workspace "Wolfenstein"
	architecture "x86"
	
	configurations
	{
		"Debug",
		"Release"
	}
	
outputdir = "%{cfg.buildcfg}"

project "Wolfenstein"
	location "Wolfenstein"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"
	
	targetdir("bin/%{cfg.buildcfg}/%{prj.name}");
	objdir("obj/%{cfg.buildcfg}/%{prj.name}");
	pchheader "pch.h"
	pchsource "Wolfenstein/src/pch.cpp"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	links
	{
		"opengl32.lib",
		"glfw3.lib",
		"glad.lib"
	}
	
	includedirs { "deps/include", "Wolfenstein/src" }
	libdirs { "deps/lib/%{cfg.buildcfg}" }
	
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		
	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
			
	filter "configurations:Release"
		runtime "Release"
		optimize "On"