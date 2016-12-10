
#include "Block.h"
#include <glm/detail/type_mat.hpp>

Block::Block()
{
	object = nullptr;
	is_visible = true;
}

Block::~Block()
{
	if (object != nullptr)
	{
		delete object;
	}
}

void Block::draw() const
{
	if (object != nullptr)
	{
		object->draw();
	} else
	{
		assert("Call Block::init() prior to calling Block::draw()");
	}
}

void Block::init(double x_position, double z_position, glm::vec3 color)
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
	material_0._diffuse_material = color;
	material_0._ambient_material = color;
	material_0._specular_material = glm::vec3(1.0, 1.0, 1.0);
	material_0._shininess = 8.0f;
	material_0._transparency = 1.0f;

	appearance_0->setMaterial(material_0);
	appearance_0->finalize();

	object = new GLObjectObj("models/Normal_Block.obj");
	object->setApperance(*appearance_0);
	object->init();

	// Correct based on the center point of model.
	// This is a quality of life thing so I can have a consistent point at the bottom left corner.
	x_position += 1.5;
	z_position += 0.5;

	glm::vec3 initial_position = glm::vec3(x_position, 0.0, z_position);
	glm::mat4 transform = glm::translate(initial_position);
	object->setMatrix(transform);

	bounding_box = new BoundingBox(*object);
	bounding_box->recalculate(initial_position); // This is the only time we have to recalcuate the AABB for the block.
}

void Block::toggle_block()
{
	is_visible = !is_visible;
}

bool Block::is_block_visible() const
{
	return is_visible;
}
