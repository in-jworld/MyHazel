#pragma once

#ifdef GS_PLATFORM_WINDOWS

extern Gemstone::Application* Gemstone::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Gemstone::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif