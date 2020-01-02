#pragma once

#include "CameraUtil.h"

#include "GLFW/glfw3.h"

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

	MVPBuilder& operator = (const MVPBuilder& _mvpBuilder)
	{
		scaleModel = _mvpBuilder.scaleModel;
		rotationModel = _mvpBuilder.rotationModel;
		translationModel = _mvpBuilder.translationModel;

		return *this;
	}

private:
	CameraUtil& cameraUtil;

	glm::mat4 scaleModel = glm::mat4(1.0f);
	glm::mat4 rotationModel = glm::mat4(1.0f);
	glm::mat4 translationModel = glm::mat4(1.0f);
};