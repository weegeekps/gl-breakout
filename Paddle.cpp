#include "Paddle.h"



Paddle::Paddle()
{
}


Paddle::~Paddle()
{
	if (object != nullptr)
	{
		delete object;
	}
}

void Paddle::init(FieldConfiguration configuration)
{
	GLAppearance* appearance_0 = new GLAppearance("shaders/multi_vertex_lights.vs", "shaders/multi_vertex_lights.fs");

	GLDirectLightSource light_source;
	light_source._lightPos = glm::vec4(20.0, 20.0, 0.0, 0.0);
	light_source._ambient_intensity = 0.2f;
	light_source._specular_intensity = 4.0f;
	light_source._diffuse_intensity = 2.0f;
	light_source._attenuation_coeff = 0.0f;

	appearance_0->addLightSource(light_source);

	GLMaterial material_0;
	material_0._diffuse_material = glm::vec3(0.9f, 0.9f, 0.9f);
	material_0._ambient_material = glm::vec3(0.9f, 0.9f, 0.9f);
	material_0._specular_material = glm::vec3(1.0, 1.0, 1.0);
	material_0._shininess = 8.0f;
	material_0._transparency = 1.0f;

	appearance_0->setMaterial(material_0);
	appearance_0->finalize();

	object = new GLObjectObj("models/Paddle.obj");
	object->setApperance(*appearance_0);
	object->init();

	z_position = configuration.z_start * -1.0f;

	glm::mat4 translation_matrix = glm::translate(glm::vec3(x_position, 0.0f, z_position));
	object->setMatrix(translation_matrix);
}

void Paddle::draw()
{
	glm::mat4 translation_matrix;

	float new_x_position = x_position;
	switch(move)
	{
		case PADDLE_LEFT:
			new_x_position += 0.333f;
			break;
		case PADDLE_RIGHT:
			new_x_position -= 0.333f;
			break;
		case PADDLE_STAY:
		default:
			break;
	}

	if (new_x_position < 9.0f && new_x_position > -9.0f) {
		x_position = new_x_position;
	}

	translation_matrix = glm::translate(glm::vec3(x_position, 0.0f, z_position));
	object->setMatrix(translation_matrix);

	object->draw();
}

void Paddle::start_move_left()
{
	move = PADDLE_LEFT;
}

void Paddle::start_move_right()
{
	move = PADDLE_RIGHT;
}

void Paddle::stop_move()
{
	move = PADDLE_STAY;
}
