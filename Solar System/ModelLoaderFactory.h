#pragma once

#include "IModelLoader.h"
#include "FileUtil.h"
#include "ConsoleUtil.h"

#include <string>
#include <map>
#include <memory>

class ModelLoaderFactory
{
public:
	ModelLoaderFactory(FileUtil& _fileUtil, ConsoleUtil _consoleUtil);
	IModelLoader& GetLoaderForFile(std::string fileLocation);

private:
	FileUtil fileUtil;
	ConsoleUtil consoleUtil;
};