#pragma once
#include "FieldConfiguration.h"
#include "gl_common/GLObjectObj.h"

enum BallXDirection
{
	BALL_LEFT = 1,
	BALL_RIGHT = -1
};

enum BallZDirection
{
	BALL_UP = 1,
	BALL_DOWN = -1
};

class Ball
{
	GLObjectObj* object = nullptr;

	float x_position = 0.0f;
	float z_position = 0.0f;

	float base_velocity = 0.05f;

	unsigned int x_velocity_factor = 1;
	unsigned int z_velocity_factor = 2;

	BallXDirection x_direction = BALL_LEFT;
	BallZDirection z_direction = BALL_UP;

	bool is_moving = false;

public:
	Ball();
	~Ball();

	void init(FieldConfiguration configuration);
	void draw();

	void start_movement();
};

