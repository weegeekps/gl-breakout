#include "Walls.h"


Walls::Walls()
{
}


Walls::~Walls()
{
	if (left_wall != nullptr)
	{
		delete left_wall;
	}

	if (right_wall != nullptr)
	{
		delete right_wall;
	}

	if (back_wall != nullptr)
	{
		delete back_wall;
	}
}

void Walls::init(FieldConfiguration configuration)
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

	left_wall = new GLObjectObj("models/Side_Wall.obj");
	left_wall->setApperance(*appearance_0);
	left_wall->init();

	right_wall = new GLObjectObj("models/Side_Wall.obj");
	right_wall->setApperance(*appearance_0);
	right_wall->init();

	back_wall = new GLObjectObj("models/Back_Wall.obj");
	back_wall->setApperance(*appearance_0);
	back_wall->init();

	glm::mat4 side_wall_rotate = glm::rotate(1.5708f, glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 left_wall_translate = glm::translate(glm::vec3(configuration.x_minimum, 0.0f, 0.0f));
	glm::mat4 left_wall_transform = left_wall_translate * side_wall_rotate;
	left_wall->setMatrix(left_wall_transform);

	glm::mat4 right_wall_translate = glm::translate(glm::vec3(configuration.x_maximum, 0.0f, 0.0f));
	glm::mat4 right_wall_transform = right_wall_translate * side_wall_rotate;
	right_wall->setMatrix(right_wall_transform);

	glm::mat4 back_wall_translate = glm::translate(glm::vec3(0.0f, 0.0f, configuration.z_start + configuration.num_rows + 2.0f)); // The extra 2.0f is for a little space in the back.
	back_wall->setMatrix(back_wall_translate);
}

void Walls::draw() const
{
	if (left_wall == nullptr ||
		right_wall == nullptr ||
		back_wall == nullptr)
	{
		assert("You must call Walls::init(FieldConfiguration) before calling Walls::draw()");
	}

	left_wall->draw();
	right_wall->draw();
	back_wall->draw();
}
