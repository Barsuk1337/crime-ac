#include "CLuaCheck.h"
#include "Misc.h"

#include "util/Logger.h"

void CLuaCheck::Scan()
{
	WIN32_FIND_DATA filedata;
    HANDLE hf;

    std::wstring gtadir = Misc::GetGTADirectory();

    hf = FindFirstFile((gtadir + TEXT("/moonloader/*")).c_str(), &filedata);

    if(hf != INVALID_HANDLE_VALUE)
    {
        do 
        {
            std::wstring file(filedata.cFileName);

            if(file.find(TEXT(".lua")) != -1)
            {
                std::wstring msg = TEXT("Для запуска игры удалите файл ") + file;
                MessageBox(NULL, msg.c_str(), L"Crime Streets Anticheat", MB_ICONERROR);

                ExitProcess(0);
            }
        }
        while (FindNextFile(hf, &filedata) != 0);

        FindClose(hf);
    }
}
