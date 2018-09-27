#pragma once

class Model;
class IndexBuffer;
class Shader;

class Renderer {

public:
	Renderer();

	/**
	 * Renders a model with an index buffer specified.
	 */
	void DrawElements(const Model& model, const IndexBuffer& indices, const Shader& shader) const;

	void EnableBlending(unsigned int source, unsigned int destination) const;

};