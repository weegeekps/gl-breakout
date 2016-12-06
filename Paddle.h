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

enum PaddleMoveDirection {
	PADDLE_STAY = 0,
	PADDLE_LEFT = 1,
	PADDLE_RIGHT = 2
};

class Paddle
{
	GLObjectObj* object = nullptr;
	PaddleMoveDirection move = PADDLE_STAY;

	float x_position = 0.0f;
	float z_position = 0.0f;

public:
	Paddle();
	~Paddle();
	
	void init(FieldConfiguration configuration);
	void draw();

	void start_move_left();
	void start_move_right();
	void stop_move();
};
