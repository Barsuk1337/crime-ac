#include <Boost\thread.hpp>

#include "CLoader.h"
#include "Addresses.h"
#include "util/Logger.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		{
			MessageBoxA(NULL, "Нажмите для продолжения", "Crime Streets Anticheat", NULL);

			if (!CLoader::IsLoaded())
			{
				// Make sure we aren't loading this DLL at sometime other than init
				if (ADDRESS_LOADED >= 6)
				{
					FreeLibraryAndExitThread(hModule, 0);
				}

				// Do the main loading procedure in a new thread.
				boost::thread theThread(&CLoader::Initialize, hModule);
			}

			break;
		}
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}