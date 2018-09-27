#include "Model.h"
#include "OpenGL.h"

Model::Model() : vertexArrayId(0), vertexBufferId(0) {}

Model::~Model()
{
	GLCall(glDeleteVertexArrays(1, &vertexArrayId));
	GLCall(glDeleteBuffers(1, &vertexBufferId));
}

/**
 * Every element of layout specifies another attribute on the VAO. The for-loop
 * retrieves these attributes and binds them accordingly.
 */
void Model::Build(const void* data, unsigned int size, const VertexLayout& layout) {

	GLCall(glGenVertexArrays(1, &vertexArrayId));
	GLCall(glBindVertexArray(vertexArrayId));

	GLCall(glGenBuffers(1, &vertexBufferId));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId));

	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));

	unsigned int offset = 0;
	auto elements = layout.GetElements();
	for (unsigned int i = 0; i < elements.size(); i++) {
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, elements[i].count, elements[i].type, elements[i].normalized, 
			layout.GetStride(), (const void*)offset));
		offset += elements[i].count * VertexLayout::SizeOf(elements[i].type);
	}

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));

}
void Model::Bind() const {
	GLCall(glBindVertexArray(vertexArrayId));
}
void Model::Unbind() const {
	GLCall(glBindVertexArray(0));
}
