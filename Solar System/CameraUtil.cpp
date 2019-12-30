#include "CameraUtil.h"
#include <glm\ext\matrix_transform.hpp>

using namespace glm;

CameraUtil::CameraUtil()
{
	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::mat4 CameraUtil::GetView()
{
	return lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}