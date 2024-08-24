project "Editor"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "on"

   files { "Source/**.h", "Source/**.cpp" }

   includedirs
   {
      "Source",

	  -- Include Core
	  "../TekEngine-Core/Source",
      "../TekEngine-Core/vendor/spdlog/include",
      "../TekEngine-Core/vendor",

      "%{IncludeDir.glm}"

   }

   links
   {
      "Core"
   }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS", "TEK_PLATFORM_WINDOWS" }

   filter "configurations:Debug"
       defines { "TEK_DEBUG" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "TEK_RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       defines { "TEK_DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"