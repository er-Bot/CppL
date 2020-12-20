solution "NLO"
	configurations {"Debug", "Release"}
	location "build"
	targetdir "build/bin"

	configurations "Debug"
		defines {"DEBUG"}
		flags {"Symbols"}

	configurations "Release"
		defines {"NDEBUG"}
		flags {"Optimize"}

project "nlo"
	kind "ConsoleApp"
	language "C++"
	
	files {
		"**.cpp", "**.h"
	}