/*
* TripleTexture.h
* Adam N. Morris
*
* HCI 557
*/
#pragma once
#include "gl_common/GLAppearanceBase.h"
#include <string>
#include <GL/gl.h>

struct TextureMetaData {
	unsigned int channels;
	unsigned int width;
	unsigned int height;
};

/* Based loosely on the GLMultiTexture class in Dr. Radkowski's examples. */
class TripleTexture
{
private:
	friend class GLAppearance;

#ifdef WIN32
	static std::string _glsl_names[];
#else
	const string _glsl_names[4] = { "gradient_texture", "landscape_texture", "person_texture", "texture_blend" };
#endif;

public:
	TripleTexture();
	~TripleTexture();

	int loadAndCreateTextures(std::string gradient_texture_path, std::string landscape_texture_path, std::string person_texture_path);

	bool setTextureBlendMode(int mode);

protected:
	virtual bool addVariablesToProgram(GLuint program, int variable_index);

	virtual bool dirty(GLuint program);
private:
	GLuint gradient_texture;
	GLuint landscape_texture;
	GLuint person_texture;
	int texture_blend_mode;

	int gradient_texture_index;
	int landscape_texture_index;
	int person_texture_index;
	int texture_blend_mode_index;
};

GLuint generateAndBindTexture(unsigned char* data, TextureMetaData meta_data);