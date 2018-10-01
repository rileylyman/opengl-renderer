#pragma once

#include <vector>
#include "VertexLayout.h"
#include "glm/glm.hpp"

/**
 * A Model contains both a VertexArrayObject and a VertexBufferObject.
 */
class Model
{
private:
	unsigned int vertexArrayId;
	unsigned int vertexBufferId;
	glm::mat4 modelMatrix;
	VertexLayout layout;

public:
	Model();
	~Model();

	/**
	 * Buffer data into the VAO using layout. Will create a new VAO.  
	 */
	void Build(const void* data, unsigned int size, const VertexLayout& layout);
	void Bind() const;
	void Unbind() const;

	inline glm::mat4 GetModelMatrix() const { return modelMatrix; }
	void SetModelMatrix(glm::mat4 matrix);
};

