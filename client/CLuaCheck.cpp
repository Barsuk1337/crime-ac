#include "CLuaCheck.h"
#include "Misc.h"

#include "util/Logger.h"

std::vector<std::string> CLuaCheck::m_FileNames;

bool CLuaCheck::Scan()
{
	int lua_count = 0;
    m_FileNames.clear();

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
                if(!IsFileExist(Misc::utf8_encode(file)))
                {
                    //std::wstring msg = TEXT("Для запуска игры с античитом удалите файл ") + file;
                    //MessageBox(NULL, msg.c_str(), L"Crime Streets Anticheat", MB_ICONERROR);

                    std::wstring path_file = path + TEXT("/") + file;
                    Logger::LogToFile("Найден запрещенный lua файл %s", Misc::utf8_encode(path_file).c_str());

                    lua_count++;
                }
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

void CLuaCheck::AddWhiteList(std::string file)
{
    m_FileNames.push_back(file);
}

bool CLuaCheck::IsFileExist(std::string file)
{
	for (std::vector<std::string>::iterator it = m_FileNames.begin(); it != m_FileNames.end(); ++it)
	{
		if (strcmp(it->c_str(), file.c_str()) == 0)
		{
			return true;
		}
	}

	return false;
}