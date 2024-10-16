workspace "TekEngine"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "Editor"

OutputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

   -- Workspace-wide build options
   filter "system:windows"
      toolset "clang"
      buildoptions
      {
         "-m64",
      }
      defines
      {
         "_CRT_SECURE_NO_WARNINGS",
         "_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS"
      }

group "Core"
	include "TekEngine-Core/Build-Core.lua"
group ""

include "TekEngine-Editor/Build-Editor.lua"
--include "TekEngine-Runtime/Build-Runtime.lua"

IncludeDir = {}
IncludeDir["GLFW"] = "vendor/GLFW/include"
IncludeDir["GLAD"] = "vendor/GLAD/include"
IncludeDir["ImGui"] = "vendor/imgui"
IncludeDir["glm"] = "vendor/glm"
IncludeDir["stb_image"] = "vendor/stb_image"
IncludeDir["assimp"] = "vendor/assimp/include"
IncludeDir["ImGuizmo"] = "vendor/ImGuizmo"

include "TekEngine-Core/vendor/GLFW/premake5.lua"
include "TekEngine-Core/vendor/GLAD/premake5.lua"
include "TekEngine-Core/vendor/imgui/premake5.lua"
include "TekEngine-Core/vendor/assimp/premake5.lua"