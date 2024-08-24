project "Core"
   kind "StaticLib"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "on"

   pchheader "tekpch.h"
   pchsource "Source/tekpch.cpp"

   files 
   { 
    "Source/**.h", 
    "Source/**.cpp",
    "vendor/glm/glm/**.hpp",
    "vendor/glm/glm/**.inl"
   }

   includedirs
   {
      "Source",

      "vendor/spdlog/include",
      "%{IncludeDir.GLFW}",
      "%{IncludeDir.GLAD}",
      "%{IncludeDir.ImGui}",
      "%{IncludeDir.glm}",
      "%{IncludeDir.stb_image}",
      "%{IncludeDir.assimp}"
   }

   links{
      "GLFW",
      "GLAD",
      "ImGui",
      "assimp",
      "opengl32.lib"
   }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines 
        { 
            "TEK_PLATFORM_WINDOWS" ,
            "_CRT_SECURE_NO_WARNINGS",
            "GLFW_INCLUDE_NONE"
        }

   filter "configurations:Debug"
       defines { "TEK_DEBUG", "TEK_ENABLE_ASSERTS" }
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