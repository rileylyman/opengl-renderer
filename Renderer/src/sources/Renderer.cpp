#include "Renderer.h"

#include "Model.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include "OpenGL.h"

#include <iostream>

void GLClearError() { while (glGetError()); }

bool GLLogCall() {
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGl Error] (" << error << ")" << std::endl;
		return false;
	}
	return true;
}

/**
 * This initializes GLEW. Must be called after a valid OpenGL context is created,
 * and before any other OpenGL calls.
 */
Renderer::Renderer() {
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to init GLEW" << std::endl;
		ASSERT(false);
	}
	EnableBlending(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	EnableDepthTesting();
}

void Renderer::DrawElements(const Model& model, const IndexBuffer& indices, const Shader& shader) const
{
	model.Bind();
	indices.Bind();
	shader.Use();

	GLCall(glDrawElements(GL_TRIANGLES, indices.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const
{
	if (depthTesting) {
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}
	else {
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}
}

void Renderer::EnableBlending(unsigned int source, unsigned int destination) 
{
	GLCall(glBlendFunc(source, destination));
	GLCall(glEnable(GL_BLEND));

	blending = true;
}

void Renderer::DisableBlending() 
{
	GLCall(glDisable(GL_BLEND));

	blending = false;
}

void Renderer::EnableDepthTesting() 
{
	GLCall(glEnable(GL_DEPTH_TEST));

	depthTesting = true;
}

void Renderer::DisableDepthTesting() 
{
	GLCall(glDisable(GL_DEPTH_TEST));

	depthTesting = false;
}
