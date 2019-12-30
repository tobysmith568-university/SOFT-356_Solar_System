#pragma once

#include <glm/glm.hpp>
#include <glm/fwd.hpp>

class CameraUtil
{
public:
	CameraUtil();

	glm::mat4 GetView();

private:
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
};