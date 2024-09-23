#pragma once

#ifdef TEK_PLATFORM_WINDOWS

extern TEK::Application* TEK::CreateApplication();

int main(int argc, char** argv) 
{
	TEK::Logger::Init();
	TEK_CORE_INFO("Initialized Log");

	auto app = TEK::CreateApplication();
	app->Run();
	delete app;
}
#endif