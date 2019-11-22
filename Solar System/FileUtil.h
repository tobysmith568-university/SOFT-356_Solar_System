#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <direct.h>

class FileUtil
{
public:
	bool DoesFileExist(std::string& fileLocation);
	std::string GetExtension(std::string& fileLocation);
	std::string GetName(std::string& fileLocation);
	std::string GetNameWithExtension(std::string& fileLocation);
	std::string GetFolder(std::string& fileLocation);

	void EnsureFolderExists(std::string& folderLocation);
	std::string ReadFile(std::string fileLocation);
	std::vector<std::string> ReadFileAsLines(std::string fileLocation);

	void SaveFile(std::string& data, std::string& fileLocation);

private:
	const std::string error_EmptyPath = "An empty file path was given";
	const std::string error_ExtensionNotFound = "An extension was never found in the given path";
	const std::string error_FolderNotFound = "A slash was never found in the given path";
};