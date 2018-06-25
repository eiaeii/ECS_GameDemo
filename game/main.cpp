#include "client.h"

using namespace terra;
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	if (Client::StaticInit())
	{
		return Client::sInstance->Run();
	}
	else
	{
		SDL_Quit();
		return 1;
	}
}
