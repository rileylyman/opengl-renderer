#pragma once

#include <vector>
#include "VertexLayout.h"

/**
 * A Model contains both a VertexArrayObject and a VertexBufferObject.
 */
class Model
{
private:
	unsigned int vertexArrayId;
	unsigned int vertexBufferId;
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
};

