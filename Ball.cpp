#include "Ball.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "gl_common/GLObjectObj.h"


Ball::Ball()
{
}


Ball::~Ball()
{
	if (object != nullptr)
	{
		delete object;
	}
}

void Ball::init(FieldConfiguration configuration)
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

		object = new GLObjectObj("models/Ball.obj");
		object->setApperance(*appearance_0);
		object->init();

		z_position = configuration.z_start * -1.0f + 1.0f;

		glm::mat4 translation_matrix = glm::translate(glm::vec3(x_position, 0.0f, z_position));
		object->setMatrix(translation_matrix);
}

void Ball::draw()
{
	if (is_moving)
	{
		// I'm a bit proud about this. I probably shouldn't be, but I'm happy I realized a few key things here.
		//   I use the base_velocity to calculate the basic speed. The factors then dictate how narrow or wide
		//   the angle is. Finally, the direction (handled by an enum with a 1 and -1 value) dictates the sign
		//   of the velocity indicating whether or not it moves left or right.
		//
		// A couple notes so I don't forget:
		//   If the x_velocity_factor > z_velocity_factor, the angle is >45 degrees. The inverse is also true.
		//   On the x axis, positive direction means we're going left, negative going right.
		//   On the z axis, positive = up, negative = down.
		//   Equally increasing the velocity factor means the ball moves faster at the basic 45 degree angle.
		x_position += base_velocity * x_velocity_factor * x_direction;
		z_position += base_velocity * z_velocity_factor * z_direction;

		glm::mat4 translation_matrix = glm::translate(glm::vec3(x_position, 0.0f, z_position));
		object->setMatrix(translation_matrix);
	}

	object->draw();
}

void Ball::start_movement()
{
	is_moving = true;
}
