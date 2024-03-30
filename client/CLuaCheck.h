#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <map>

class CLuaCheck
{
public:
	static bool Scan();	

private:
	static bool ScanDirectory(std::wstring path);
	static void AddWhiteList(std::string file);
	static bool IsFileExist(std::string file);

private:
	static std::vector<std::string> m_FileNames;
};


