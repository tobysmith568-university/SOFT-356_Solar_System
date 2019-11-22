#pragma once

#include "FileUtil.h"

#include <iostream>

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

	const std::string arrow = "--> ";
	const std::string fileDoesNotExist = "File does not exist!";
};