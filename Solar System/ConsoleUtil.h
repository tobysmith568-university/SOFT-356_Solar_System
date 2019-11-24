#pragma once

#include "FileUtil.h"

#include <string>

class ConsoleUtil
{
public:
	ConsoleUtil(FileUtil& _fileUtil);
	void ClearConsole();
	void Print(std::string message);
	std::string GetInput(std::string question);
	std::string GetFileName(std::string question);

private:
	FileUtil& fileUtil;
};