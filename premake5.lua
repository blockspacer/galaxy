-- premake5 build script.

---
--- START WORKSPACE
---
workspace "starlight"
	language "C++"
	cppdialect "C++17"
	platforms { "Win32", "Win64", "MacOS", "Linux32", "Linux64" }
	configurations {"Debug", "Release"}
---
--- END WORKSPACE
---

---
--- START ARCHITECTURE FILTERS
---
	filter "platforms:Win32"
		architecture "x32"
		defines { "WIN32" }
		libdirs { "libs/libxml2/x32", "libs/allegro/x32/lib", "libs/allegro_deps/x32" }

	filter "platforms:Win64"
		architecture "x64"
		defines { "WIN64" }
		libdirs { "libs/libxml2/x64", "libs/allegro/x64/lib", "libs/allegro_deps/x64" }

	filter "platforms:MacOS"
		system "macosx"
		architecture "x64"
		includedirs { "starlight/source", os.findheader("libxml2"), os.findheader("allegro"), os.findheader("flac"), os.findheader("freetype"), os.findheader("libogg"), os.findheader("libvorbis"), os.findheader("opusfile"), os.findheader("physfs"), os.findheader("theora"), os.findheader("webp"), os.findheader("libpng"), os.findheader("opus"), os.findheader("jpeg"), os.findheader("openssl") }
		libdirs { os.findlib("libxml2"), os.findlib("allegro"), os.findlib("flac"), os.findlib("freetype"), os.findlib("libogg"), os.findlib("libvorbis"), os.findlib("opusfile"), os.findlib("physfs"), os.findlib("theora"), os.findlib("webp"), os.findlib("libpng"), os.findlib("opus"), os.findlib("jpeg"), os.findlib("openssl") }
		links { "libxml2", "allegro", "flac", "freetype", "libogg", "libvorbis", "opusfile", "physfs", "theora", "webp", "libpng", "opus", "jpeg", "openssl" }

	filter "platforms:Linux32"
		architecture "x32"
		
	filter "platforms:Linux64"
		architecture "x64"
---
--- END PLATFORM FILTERS
---


---
--- START CONFIGURATIONS
---
	filter "configurations:Debug"
		defines { "_DEBUG" }
		symbols "On"
		optimize "Debug"

	filter "configurations:Release"
		defines { "NDEBUG" }
		symbols "Off"
		optimize "Speed"	
---
--- END CONFIGURATIONS
---


---
--- START SPECIFIC PLATFORM FILTERS
---
	filter { "platforms:Win32 or Win64" }
		system "windows"
		systemversion "latest"
		flags { "NoPCH" }
		defines { "_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS", "_CRT_SECURE_NO_WARNINGS", "_CRT_SECURE_NO_DEPRECATE", "_CRT_NONSTDC_NO_DEPRECATE" }
		buildoptions { "/bigobj" }
		includedirs { "starlight/source", "libs/libxml2/include", "libs/allegro/include", "libs/allegro_deps/include" }
		links { "libxml2", "opengl32", "dumb", "FLAC", "freetype", "jpeg", "libpng16", "ogg", "opus", "opusfile", "physfs", "theoradec", "vorbis", "vorbisfile", "zlib" }

	filter { "platforms:Win32 or Win64", "configurations:Debug"}
		links { "allegro-debug", "allegro_main-debug", "allegro_image-debug", "allegro_physfs-debug", "allegro_color-debug", "allegro_memfile-debug", "allegro_font-debug", "allegro_ttf-debug", "allegro_primitives-debug", "allegro_dialog-debug", "allegro_audio-debug", "allegro_acodec-debug", "allegro_video-debug" }

	filter { "platforms:Win32 or Win64", "configurations:Release"}
		links { "allegro_monolith-static", "winmm", "Shlwapi", "psapi", "dsound" }

	filter { "platforms:Linux32 or Linux64"}
		system "linux"
		includedirs { "starlight/source", os.findheader("libxml2"), os.findheader("liballegro5-dev") }
		libdirs { os.findlib("libxml2"), os.findlib("liballegro5.2") }
		links { "GL", "libxml2", "liballegro5.2" }
---
--- END SPECIFIC PLATFORM FILTERS
---


---
--- START PROJECTS
---
project "starlight"
	kind "StaticLib"
	location "build/starlight"
	defines { "ALLEGRO_STATICLINK", "LIBXML_STATIC" }
	files { "starlight/source/**.hpp", "starlight/source/**.cpp", "starlight/source/**.h", "starlight/source/**.c" }

project "sandbox"
	kind "ConsoleApp"
	location "build/sandbox"
	defines { "ALLEGRO_STATICLINK", "LIBXML_STATIC" }
	links { "starlight" }
	dependson { "starlight" }
	files { "sandbox/source/**.hpp", "sandbox/source/**.cpp" }
---
--- END PROJECTS
---