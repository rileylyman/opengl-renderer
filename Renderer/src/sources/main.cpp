#include "OpenGL.h"
#include "WindowManager.h"
#include <string>
#include "Renderer.h"
#include "Model.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

int main(void)
{
	bool success;
	WindowManager window(&success);
	if (!success) {
		return -1;
	}

	std::string name("OpenGL Renderer");
	if (!window.CreateWindow(800, 600, name)) {
		return -1;
	}

	Renderer renderer;
	renderer.EnableBlending(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	float data[] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, 1.0f, 0.5f, 0.3f, 0.8f
	};
	unsigned int size = 28 * sizeof(float);
	unsigned int idxs[] = {
		0, 1, 2,
		2, 3, 0
	};

	VertexLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	layout.Push<float>(3);

	Model model;
	model.Build(data, size, layout);

	IndexBuffer indices(idxs, size);

	Shader shader("res/shaders/Basic.shader");

	Texture tex("res/pngs/moon.png");
	tex.Bind(2);
	shader.SetUniform1i("u_Texture", tex.GetSlot());

	Texture tex2("res/pngs/smiley.png");
	tex2.Bind(1);
	shader.SetUniform1i("u_OtherTexture", tex2.GetSlot());

	/* Loop until the user closes the window */
	while (!window.ShouldClose())
	{
		model.SetModelMatrix (
			glm::translate(glm::rotate (
				model.GetModelMatrix(), 
				glm::radians(1.0f), 
				glm::vec3(0.0f, 0.0f, 1.0f)
			), glm::vec3(-0.005f, -0.005f, 0.0f))
		);
		shader.SetUniformMatrix4f("u_Transformation", model.GetModelMatrix());
		renderer.DrawElements(model, indices, shader);
		
		window.SwapBuffers();
		WindowManager::PollEvents();
	}
	return 0;
}