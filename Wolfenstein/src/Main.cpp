#include "pch.h"
#include "Application.h"

int main(int argc, char** argv)
{
	Application* app = new Application();
	app->Init();
	delete app;

	return 0;
}