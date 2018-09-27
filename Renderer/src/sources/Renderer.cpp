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
	}
}

void Renderer::DrawElements(const Model& model, const IndexBuffer& indices, const Shader& shader) const
{
	model.Bind();
	indices.Bind();
	shader.Use();
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
	GLCall(glDrawElements(GL_TRIANGLES, indices.GetCount(), GL_UNSIGNED_INT, nullptr));
}
