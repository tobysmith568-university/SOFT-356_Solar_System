#include "Model.h"

using namespace std;

Model::Model(CameraUtil& _cameraUtil, GLuint& _program)
	: program(_program), mvpBuilder(_cameraUtil)
{
	// Create an MVP builder with some default values
	mvpBuilder
		.AddScale(1.0f, 1.0f, 1.0f)
		.AddTranslation(0.0f, 0.0f, 0.0f);

	UseMVP();
}

// OpenGL Setup
void Model::Init()
{
	for (size_t i = 0; i < objects.size(); i++)// For every object
	{
		objects[i].Init();// Init it
	}
}

// To be run every game tick
void Model::Update()
{
	UseMVP();

	for (size_t i = 0; i < objects.size(); i++)// For every object
	{
		objects[i].Update();// Update it
	}
}

void Model::AddObject(Object& object)
{
	objects.push_back(object);
}

std::vector<Object>& Model::GetObjects()
{
	return objects;
}

void Model::AddMaterial(Material& material)
{
	materials[material.name] = material;
}

Material& Model::GetMaterial(std::string& name)
{
	return materials[name];
}

std::vector<Material> Model::GetMaterials()
{
	vector<Material> results = vector<Material>();

	for (auto& pair : materials)// For every material in the materials map
	{
		results.push_back(pair.second);// Add it to a vector
	}

	return results;
}

MVPBuilder& Model::GetMVPBuilder()
{
	return mvpBuilder;
}

void Model::SetMVPBuilder(MVPBuilder _mvpBuilder)
{
	mvpBuilder = _mvpBuilder;
}

// Sets this Model's MVP as the current one in the shader program
void Model::UseMVP()
{
	int mvLoc = glGetUniformLocation(program, "mv_matrix");
	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvpBuilder.BuildMV()));

	int pLoc = glGetUniformLocation(program, "p_matrix");
	glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(mvpBuilder.BuildP()));
}