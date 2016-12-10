#pragma once
#include "FieldConfiguration.h"
#include "gl_common/GLObjectObj.h"
#include "BoundingBox.h"
#include "Block.h"

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

class Ball : public CollisionObject
{
	GLObjectObj* object = nullptr;
	BoundingBox* bounding_box = nullptr;

	float x_position = 0.0f;
	float z_position = 0.0f;

	float base_velocity = 0.05f;

	unsigned int x_velocity_factor = 1;
	unsigned int z_velocity_factor = 1;

	BallXDirection x_direction = BALL_LEFT;
	BallZDirection z_direction = BALL_UP;

	bool is_moving = false;
	int dont_switch_x_counter = 0;

	FieldConfiguration configuration;

public:
	
	Ball();
	~Ball();

	void init(FieldConfiguration configuration);
	void draw();

	void start_movement();
	void stop_movement();
	void reset();

	void bounce_on_x_axis();
	void bounce_on_z_axis();
};

