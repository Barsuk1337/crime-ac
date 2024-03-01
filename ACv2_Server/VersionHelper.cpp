#include "VersionHelper.h"
#include "../Shared/SelfUpdater/CSelfUpdater.h"

#include "GDK/sampgdk.h"
#include "Utility.h"
#include <stdio.h>

namespace VersionHelper
{
#ifdef WIN32
	const char* AC_UPDATE_URL = "https://whitetigerswt.github.io/SAMP_AC_v2/API/SelfUpdater/Server_Windows.html";
#else
	const char* AC_UPDATE_URL = "https://whitetigerswt.github.io/SAMP_AC_v2/API/SelfUpdater/Server_Linux.html";
#endif

	char HTTP_REQUEST_USER_AGENT[32];
	char AC_SERVER_VERSION_STRING[16];
	CSelfUpdater::stVersion AC_SERVER_VERSION{ 2, 83, 0 };
	// Incrementing the version will force the server to update when they run it next.
	// Only MAJOR and/or MINOR version numbers determine if server is compatible with client.
	// If only PATCH version number is different, server and client are compatible.

	bool IsClientCompatible(CSelfUpdater::stVersion clientVersion)
	{
		if (AC_SERVER_VERSION.major != clientVersion.major) return 0;
		if (AC_SERVER_VERSION.minor != clientVersion.minor) return 0;

		return 1;
	}

	void Initialize()
	{
		snprintf(AC_SERVER_VERSION_STRING, sizeof(AC_SERVER_VERSION_STRING), "%d.%02d.%d", AC_SERVER_VERSION.major, AC_SERVER_VERSION.minor, AC_SERVER_VERSION.patch);
		snprintf(HTTP_REQUEST_USER_AGENT, sizeof(HTTP_REQUEST_USER_AGENT), "ACSVR_%s", AC_SERVER_VERSION_STRING);
	}

	void CheckForUpdate()
	{
		Utility::Printf("Crime Streets Anticheat: v%s.", AC_SERVER_VERSION_STRING);
	}
}