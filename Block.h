#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "gl_common/GLObjectObj.h"

class Block
{
public:
	Block();
	~Block();
	void draw() const;
	void init(double x_position, double z_position, glm::vec3 color);
private:
	GLObjectObj* _object;
};