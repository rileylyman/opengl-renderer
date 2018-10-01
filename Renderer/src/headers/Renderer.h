#pragma once

class Model;
class IndexBuffer;
class Shader;

class Renderer {

private:
	bool depthTesting = false;
	bool blending = false;

public:
	Renderer();

	/**
	 * Renders a model with an index buffer specified.
	 */
	void DrawElements(const Model& model, const IndexBuffer& indices, const Shader& shader) const;
	void Clear() const;

	void EnableBlending(unsigned int source, unsigned int destination);
	void DisableBlending();

	void EnableDepthTesting();
	void DisableDepthTesting();

	inline bool GetDepthTestingIsEnabled() const { return depthTesting; }
	inline bool GetBleningIsEnabled() const { return blending; }

};