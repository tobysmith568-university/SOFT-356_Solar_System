#pragma once

#include "GL/glew.h"

#include "GLFW/glfw3.h"
#include "Object.h"

#include "Texture.h"
#include "Vertex.h"
#include "Material.h"

#include <vector>
#include <map>

#include "Mesh.h"
#include "MVPBuilder.h"

class Model
{
public:
	Model(CameraUtil& _cameraUtil, GLuint& _program);
	void Init();
	void Update();

	void AddObject(Object& object);
	std::vector<Object>& GetObjects();

	void AddMaterial(Material& material);
	Material& GetMaterial(std::string& name);
	std::vector<Material> GetMaterials();

	MVPBuilder& GetMVPBuilder();
	void SetMVPBuilder(MVPBuilder _mvpBuilder);

private:
	void UseMVP();

	GLuint& program;

	std::vector<Object> objects;
	std::map<std::string, Material> materials;

	MVPBuilder mvpBuilder;
};