#include "MVPBuilder.h"

#include <glm/fwd.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <GLFW\glfw3.h>
#include "GlfwUtil.h"

using namespace glm;

MVPBuilder::MVPBuilder(CameraUtil& _cameraUtil)
	: cameraUtil(_cameraUtil)
{
}

// Returns the translation model
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

// Returns the projection matrix from the cameraUtil
glm::mat4 MVPBuilder::BuildP()
{
	return cameraUtil.GetProjectionMatrix();
}

// Returns a combined view and model matrix
glm::mat4 MVPBuilder::BuildMV()
{
	mat4 view = cameraUtil.GetViewMatrix();

	// Adding all matrices up to create combined matrix
	mat4 mv = view * translationModel * rotationModel * scaleModel;

	return mv;
}

// Returns a combined Projection, View, Translation, Rotation, and Scale matrix
mat4 MVPBuilder::BuildMVP()
{
	// Adding all matrices up to create combined matrix
	mat4 mvp = cameraUtil.GetProjectionMatrix() * BuildMV();

	return mvp;
}