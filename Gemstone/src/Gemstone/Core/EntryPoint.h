#pragma once

#ifdef GS_PLATFORM_WINDOWS

extern Gemstone::Application* Gemstone::CreateApplication();

int main(int argc, char** argv)
{
	Gemstone::Log::Init();
	GS_CORE_WARN("Initialized Log!");
	int a = 5;
	GS_INFO("Hello! Var={0}", a);

	auto app = Gemstone::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif