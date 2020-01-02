#include "MVPBuilder.h"

#include <glm/fwd.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <GLFW\glfw3.h>

using namespace glm;

MVPBuilder::MVPBuilder(CameraUtil& _cameraUtil)
	: cameraUtil(_cameraUtil)
{
}

glm::mat4 MVPBuilder::GetTranslationMatrix()
{
	return translationModel;
}

// Modifies the scale of the MVP
MVPBuilder& MVPBuilder::AddScale(GLfloat x, GLfloat y, GLfloat z)
{
	scaleModel = scale(scaleModel, glm::vec3(x, y, z));
	return *this;
}

// Adds a rotation to the MVP
MVPBuilder& MVPBuilder::AddRotation(GLfloat degrees, GLfloat x, GLfloat y, GLfloat z)
{
	rotationModel = glm::rotate(rotationModel, radians(degrees), vec3(x, y, z));
	return *this;
}

// Adds a translation to the MVP
MVPBuilder& MVPBuilder::AddTranslation(GLfloat x, GLfloat y, GLfloat z)
{
	translationModel = glm::translate(translationModel, vec3(x, y, z));
	return *this;
}

// Combines a Projection, a View, and the Translation, Rotation, and Scale matrices
mat4 MVPBuilder::Build()
{
	mat4 view = cameraUtil.GetView();

	// creating the projection matrix
	mat4 projection = perspective(45.0f, 4.0f / 3, 0.1f, 20.0f);

	// Adding all matrices up to create combined matrix
	mat4 mvp = projection * view * translationModel * rotationModel * scaleModel;

	return mvp;
}