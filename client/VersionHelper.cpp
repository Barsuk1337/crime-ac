#include "VersionHelper.h"
#include "../Shared/SelfUpdater/CSelfUpdater.h"
#include "CLoader.h"

namespace VersionHelper
{
	wchar_t AC_CLIENT_VERSION_STRING[16];
	CSelfUpdater::stVersion AC_CLIENT_VERSION{ 1, 0, 0 };
	// Incrementing the version will force the client to update when they run it next.
	// Only MAJOR and/or MINOR version numbers determine if server is compatible with client.
	// If only PATCH version number is different, server and client are compatible.

	void Initialize()
	{
		swprintf_s(AC_CLIENT_VERSION_STRING, L"%d.%02d.%d", AC_CLIENT_VERSION.major, AC_CLIENT_VERSION.minor, AC_CLIENT_VERSION.patch);
	}
}