#include "FileUtil.h"

using namespace std;

bool FileUtil::DoesFileExist(std::string& fileLocation)
{
	ifstream f(fileLocation.c_str());
	return f.good();
}

std::string FileUtil::GetExtension(std::string& fileLocation)
{
	if (fileLocation.size() < 1)
	{
		throw invalid_argument(error_EmptyPath);
	}

	string result = "";

	for (size_t i = fileLocation.size(); i > 0; i--)
	{
		if (fileLocation[i - 1] == '.')
		{
			return result;
		}

		result = fileLocation[i - 1] + result;
	}

	return result;
}

std::string FileUtil::GetName(std::string& fileLocation)
{
	if (fileLocation.size() < 1)
	{
		throw invalid_argument(error_EmptyPath);
	}

	string result = "";

	bool foundDot = false;
	for (size_t i = fileLocation.size(); i > 0; i--)
	{
		if (foundDot)
		{
			result = fileLocation[i - 1] + result;
		}
		else if (fileLocation[i - 1] == '.')
		{
			foundDot = true;
		}
	}

	if (result == "")
	{
		throw invalid_argument(error_ExtensionNotFound);
	}

	return result;
}

std::string FileUtil::GetNameWithExtension(std::string& fileLocation)
{
	if (fileLocation.size() < 1)
	{
		throw invalid_argument(error_EmptyPath);
	}

	string result = "";

	for (size_t i = fileLocation.size(); i > 0; i--)
	{
		if (fileLocation[i - 1] == '/' || fileLocation[i - 1] == '\\')
		{
			return result;
		}

		result = fileLocation[i - 1] + result;
	}

	return result;
}

std::string FileUtil::GetFolder(std::string& fileLocation)
{
	if (fileLocation.size() < 1)
	{
		throw invalid_argument(error_EmptyPath);
	}

	string result = "";

	bool foundSlash = false;
	for (size_t i = fileLocation.size(); i > 0; i--)
	{
		if (!foundSlash && (fileLocation[i - 1] == '/' || fileLocation[i - 1] == '\\'))
		{
			foundSlash = true;
		}

		if (foundSlash)
		{
			result = fileLocation[i - 1] + result;
		}
	}

	if (result == "")
	{
		throw invalid_argument(error_FolderNotFound);
	}

	return result;
}

void FileUtil::EnsureFolderExists(std::string& folderLocation)
{
	struct stat info;

	if (stat(folderLocation.c_str(), &info) != 0 || !(info.st_mode & S_IFDIR))
	{
		int result = _mkdir(folderLocation.c_str());
	}
}

std::string FileUtil::ReadFile(std::string fileLocation)
{
	try
	{
		ifstream stream(fileLocation);
		string content = string(istreambuf_iterator<char>(stream), istreambuf_iterator<char>());

		return content;
	}
	catch (...)
	{
		throw runtime_error("Could not open the file[" + fileLocation + "]. It is either missing, locked, corrupt, or empty.");
	}
}

std::vector<std::string> FileUtil::ReadFileAsLines(std::string fileLocation)
{
	vector<string> result = vector<string>();

	ifstream file(fileLocation);
	if (!file.is_open())
	{
		throw runtime_error("Could not open the file [" + fileLocation + "]. It is either missing, locked, corrupt, or empty.");
	}

	string readLine;
	while (getline(file, readLine))
	{
		result.push_back(readLine);
	}

	return result;
}

void FileUtil::SaveFile(std::string& data, std::string& fileLocation)
{
	ofstream file;
	file.open(fileLocation, ios::out | ios::trunc);

	if (!file.is_open())
	{
		throw runtime_error("Could not open the file [" + fileLocation + "]");
	}

	file << data;

	file.close();
}