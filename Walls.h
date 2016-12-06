#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "gl_common/GLAppearance.h"
#include "gl_common/GLObjectObj.h"
#include "FieldConfiguration.h"

class Walls
{
	GLObjectObj* left_wall;
	GLObjectObj* right_wall;
	GLObjectObj* back_wall;

public:
	Walls();
	~Walls();
	/**
	 * \brief Initializes the Walls and configures them based on the specified FieldConfiguration object.
	 * \param configuration The configuration object used throughout the program.
	 */
	void init(FieldConfiguration configuration);
	void draw() const;
};

