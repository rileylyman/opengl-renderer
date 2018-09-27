#include "Texture.h"
#include "OpenGL.h"
#include "stb/stb_image.h"

/** This function will overwrite any textures bound to slot 0, since it uses slot 0 to bind
 *  the new texture it is creating. Be sure to bind any other textures to slot 0 after you are done
 *  instatiating all of your textures.
 */
Texture::Texture(const std::string & path)
	: id(0), width(0), height(0), bpp(0), slot(0), filepath(path)
{
	stbi_set_flip_vertically_on_load(1);
	const void* buffer = stbi_load(path.c_str(), &width, &height, &bpp, 4);

	GLCall(glGenTextures(1, &id));
	GLCall(glBindTexture(GL_TEXTURE_2D, id));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (buffer) {
		stbi_image_free((void*)buffer);
	}
}

Texture::~Texture() {
	glDeleteTextures(1, &id);
}

void Texture::Bind(unsigned int s) {
	slot = s;
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, id));
	GLCall(glActiveTexture(GL_TEXTURE0));
}

void Texture::Unbind() const {
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
