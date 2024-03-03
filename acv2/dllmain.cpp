#include <Boost\thread.hpp>

#include "CLoader.h"
#include "Addresses.h"
#include "util/Logger.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReasonForCall, LPVOID)
{
	if (dwReasonForCall != DLL_PROCESS_ATTACH)
        return TRUE;

	Logger::Init("csac_log.txt");
	Logger::LogToFile("CLoader initining..");

	if (!CLoader::IsLoaded())
	{
		//CModuleSecurity::AddAllowedModules();

		// Make sure we aren't loading this DLL at sometime other than init
		if (ADDRESS_LOADED >= 6)
		{
			FreeLibraryAndExitThread(hModule, 0);
		}

		// Do the main loading procedure in a new thread.
		boost::thread theThread(&CLoader::Initialize, hModule);
	}

	return TRUE;
}