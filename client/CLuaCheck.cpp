#include "CLuaCheck.h"
#include "Misc.h"

#include "util/Logger.h"

bool CLuaCheck::Scan()
{
	int lua_count = 0;

    if(ScanDirectory(TEXT("/moonloader")))
    {
        lua_count++;
    }

    if(ScanDirectory(TEXT("/moonloader/lib")))
    {
        lua_count++;
    }

    if(ScanDirectory(TEXT("/moonloader/lib/samp")))
    {
        lua_count++;
    }

    if(ScanDirectory(TEXT("/moonloader/lib/samp/events")))
    {
        lua_count++;
    }

    if(ScanDirectory(TEXT("/moonloader/lib/game")))
    {
        lua_count++;
    }

    return lua_count > 0;
}

bool CLuaCheck::ScanDirectory(std::wstring path)
{
    std::wstring gtadir = Misc::GetGTADirectory();

    WIN32_FIND_DATA filedata;
    HANDLE hf = FindFirstFile((gtadir + path + TEXT("/*")).c_str(), &filedata);

    int lua_count = 0;

    if(hf != INVALID_HANDLE_VALUE)
    {
        do 
        {
            std::wstring file(filedata.cFileName);

            if(file.find(TEXT(".lua")) != -1)
            {
                std::wstring msg = TEXT("Для запуска игры с античитом удалите файл ") + file;
                MessageBox(NULL, msg.c_str(), L"Crime Streets Anticheat", MB_ICONERROR);

                Logger::LogToFile("Найден запрещенный lua файл %s", Misc::utf8_encode(path + TEXT("/") + file).c_str());

                lua_count++;
            }
        }
        while (FindNextFile(hf, &filedata) != 0);

        FindClose(hf);

        if(lua_count > 0)
        {
            return true;
        }
    }

    return false;
}