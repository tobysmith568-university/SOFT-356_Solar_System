#pragma once

#include "GLFW/glfw3.h"

#include "CameraUtil.h"

#include <glm/glm.hpp>
#include <glm/fwd.hpp>

class MVPBuilder
{
public:
	MVPBuilder(CameraUtil& _cameraUtil);

	MVPBuilder& AddScale(GLfloat x, GLfloat y, GLfloat z);
	MVPBuilder& AddRotation(GLfloat degrees, GLfloat x, GLfloat y, GLfloat z);
	MVPBuilder& AddTranslation(GLfloat x, GLfloat y, GLfloat z);
	glm::mat4 Build();

private:
	CameraUtil& cameraUtil;

	glm::mat4 scaleModel = glm::mat4(1.0f);
	glm::mat4 rotationModel = glm::mat4(1.0f);
	glm::mat4 translationModel = glm::mat4(1.0f);
};