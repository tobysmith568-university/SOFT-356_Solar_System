#include "ModelLoaderFactory.h"
#include "ObjModelLoader.h"

#include <stdexcept>

using namespace std;

ModelLoaderFactory::ModelLoaderFactory(FileUtil& _fileUtil, ConsoleUtil _consoleUtil)
									  : fileUtil(_fileUtil), consoleUtil(_consoleUtil)
{
}

IModelLoader& ModelLoaderFactory::GetLoaderForFile(std::string fileLocation)
{
	string fileExtension = fileUtil.GetExtension(fileLocation);// Get the file extension from the file path
	
	if (fileExtension == "obj")// If this file extension is for a .obj file
	{
		static MtlLoader mtlLoader = MtlLoader(fileUtil);
		static ObjModelLoader objModelLoader = ObjModelLoader(fileUtil, consoleUtil, mtlLoader);
		return objModelLoader;// Create and return an ObjModelLoader
	}
	else
	{
		throw std::invalid_argument("The given file extension has not been implemented");
	}
}