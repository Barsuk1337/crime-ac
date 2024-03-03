#include "Logger.h"

#include <ShlObj.h>
#pragma comment(lib, "shell32.lib")

bool Logger::Init(const char* const fileName) noexcept
{
    const std::lock_guard<std::mutex> lockFile { Logger::logFileMutex };

    if (Logger::logFile != nullptr)
        return false;

    wchar_t my_documents[MAX_PATH];
    HRESULT result = SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, NULL, my_documents);

    if (result != S_OK)
        return false;

    constexpr char user_files[] = "\\GTA San Andreas User Files\\Crime Streets\\anticheat";

    char path[MAX_PATH];
    wcstombs(path, my_documents, MAX_PATH - 1);

    strcat(path, user_files);
    strcat(path, fileName);

    Logger::logFile = std::fopen(path, "wt");

    if (Logger::logFile == nullptr)
        return false;

    return true;
}

bool Logger::Free() noexcept
{
    const std::lock_guard<std::mutex> lockFile { Logger::logFileMutex };

    if (std::fclose(Logger::logFile) == EOF)
        return false;

    Logger::logFile = nullptr;

    return true;
}

std::FILE* Logger::logFile { nullptr };

std::mutex Logger::logFileMutex;
std::mutex Logger::logChatMutex;
