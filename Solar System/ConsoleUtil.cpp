#include "ConsoleUtil.h"

using namespace std;

ConsoleUtil::ConsoleUtil(FileUtil& _fileUtil)
	: fileUtil(_fileUtil)
{
}

void ConsoleUtil::ClearConsole()
{
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl
		<< endl << endl << endl << endl << endl << endl << endl << endl << endl << endl
		<< endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
}

void ConsoleUtil::Print(std::string message)
{
	cout << message;
}

std::string ConsoleUtil::GetInput(std::string question)
{
	cout << endl << question << endl << arrow;

	string result;
	getline(cin, result);

	return result;
}

std::string ConsoleUtil::GetFileName(std::string question)
{
	string input = GetInput(question);
	while (!fileUtil.DoesFileExist(input))
	{
		ClearConsole();
		Print(fileDoesNotExist);
		input = GetInput(question);
	}

	return input;
}