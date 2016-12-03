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

GLFWwindow* window;
GLuint program;

extern Trackball trackball;

extern int g_change_texture_blend;

int main(int argc, const char * argv[])
{
	window = initWindow();

	initGlew();

	CoordSystem* coordinate_system = new CoordSystem(40.0);

	float x_minimum = -12.0;
	float x_maximum = 12.0;
	float z_start = 12.0;
	float num_rows = 5;

	BlockColorSequencer color_sequencer;
	vector<Block*> blocks = {};

	for(float z = z_start; z <= z_start + num_rows; ++z)
	{
		for(float x = x_minimum; x < x_maximum; x += 3)
		{
			Block* block = new Block();
			block->init(x, z, color_sequencer.next_color());
			blocks.push_back(block);
		}
	}


#pragma region Render Loop
	static const GLfloat clear_color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	// the first parameter is the eye position, the second the center location, and the third the up vector.
	SetViewAsLookAt(glm::vec3(20.0f, 20.0f, 65.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	while(!glfwWindowShouldClose(window))
	{
		glClearBufferfv(GL_COLOR, 0, clear_color);
		glClearBufferfv(GL_DEPTH, 0, clear_depth);

		SetTrackballLocation(trackball.getRotationMatrix());

		// Draw our objects
		coordinate_system->draw();
		
		for (Block* block : blocks)
		{
			block->draw();
		}

		// TODO: Draw the scene.

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	delete coordinate_system;
#pragma endregion
}
