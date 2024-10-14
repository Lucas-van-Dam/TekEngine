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
      "Assets",
      
	  -- Include Core
	  "../TekEngine-Core/Source",
      "../TekEngine-Core/vendor/spdlog/include",
      "../TekEngine-Core/vendor",

      "../TekEngine-Core/%{IncludeDir.GLFW}",
      "../TekEngine-Core/%{IncludeDir.GLAD}",
      "../TekEngine-Core/%{IncludeDir.ImGui}",
      "../TekEngine-Core/%{IncludeDir.glm}",
      "../TekEngine-Core/%{IncludeDir.stb_image}",
      "../TekEngine-Core/%{IncludeDir.assimp}",
      "../TekEngine-Core/%{IncludeDir.ImGuizmo}"
   }

   links
   {
      "Core",
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