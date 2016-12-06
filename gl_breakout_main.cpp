/* 
 * gl_breakout_main.cpp
 * Author: Adam N. Morris
 * 
 * Several classes based on code created by Rafael Radkowski
 */

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "gl_common/controls.h"
#include "gl_common/HCI557Common.h"
#include "gl_common/CoordSystem.h"
#include "Block.h"
#include "BlockColorSequencer.h"
#include "Walls.h"
#include "Paddle.h"
#include "Ball.h"

GLFWwindow* window;
GLuint program;

extern Trackball trackball;

extern int g_change_texture_blend;

FieldConfiguration configuration;
BlockColorSequencer color_sequencer;
vector<Block*> blocks = {};
Walls* walls;
Paddle* paddle;
Ball* ball;

void keyboard_handler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (action == GLFW_PRESS)
	{
		switch (key)
		{
			case GLFW_KEY_LEFT:
				cout << "PRESSING LEFT" << endl;
				paddle->start_move_left();
				break;
			case GLFW_KEY_RIGHT:
				cout << "PRESSING RIGHT" << endl;
				paddle->start_move_right();
				break;
			case GLFW_KEY_SPACE:
				cout << "SPACE PRESSED" << endl;
				ball->start_movement();
				break;
			default:
				break;
		}
	}

	if (action == GLFW_RELEASE)
	{
		switch (key)
		{
			case GLFW_KEY_LEFT:
			case GLFW_KEY_RIGHT:
				cout << "KEY RELEASED" << endl;
				paddle->stop_move();
				break;
			default:
				break;
		}
	}
}

int main(int argc, const char * argv[])
{
	window = initWindow();

	initGlew();

	CoordSystem* coordinate_system = new CoordSystem(40.0);

	// These values are used to configure the playing field.
	configuration.x_minimum = -12.0f;
	configuration.x_maximum = 12.0f;
	configuration.z_start = 12.0;
	configuration.num_rows = 5;

#pragma region Generate Walls
	walls = new Walls();
	walls->init(configuration);
#pragma endregion 

#pragma region Generate Blocks
	for(float z = configuration.z_start; z <= configuration.z_start + configuration.num_rows; ++z)
	{
		for(float x = configuration.x_minimum; x < configuration.x_maximum; x += 3)
		{
			Block* block = new Block();
			block->init(x, z, color_sequencer.next_color());
			blocks.push_back(block);
		}
	}
#pragma endregion

#pragma region Generate Paddle
	paddle = new Paddle();
	paddle->init(configuration);
#pragma endregion 

#pragma region Generate Ball
	ball = new Ball();
	ball->init(configuration);
#pragma endregion

	// Set our keyboard event handler.
	glfwSetKeyCallback(window, keyboard_handler);

#pragma region Render Loop
	static const GLfloat clear_color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	// the first parameter is the eye position, the second the center location, and the third the up vector.
	SetViewAsLookAt(glm::vec3(0.0f, 16.0f, -19.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	while(!glfwWindowShouldClose(window))
	{
		glClearBufferfv(GL_COLOR, 0, clear_color);
		glClearBufferfv(GL_DEPTH, 0, clear_depth);

		SetTrackballLocation(trackball.getRotationMatrix());

		// Draw our objects
		//coordinate_system->draw();
		walls->draw();
		
		for (Block* block : blocks)
		{
			block->draw();
		}

		paddle->draw();
		ball->draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	delete coordinate_system;
#pragma endregion
}
