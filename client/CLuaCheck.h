#pragma once
#include <Windows.h>
#include <iostream>


class CLuaCheck
{
public:
	static bool Scan();	

private:
	static bool ScanDirectory(std::wstring path);
};


