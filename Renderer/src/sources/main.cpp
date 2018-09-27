#include "OpenGL.h"
#include "WindowManager.h"
#include <string>
#include "Renderer.h"
#include "Model.h"
#include "IndexBuffer.h"
#include "Shader.h"

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


	float data[] = {
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.5f, 0.5f,
		-0.5f, 0.5f
	};
	unsigned int size = 8 * sizeof(float);
	unsigned int idxs[] = {
		0, 1, 2,
		2, 3, 0
	};

	VertexLayout layout;
	layout.Push<float>(2);

	Model model;
	model.Build(data, size, layout);

	IndexBuffer indices(idxs, size);

	Shader shader("res/shaders/Basic.shader");

	/* Loop until the user closes the window */
	while (!window.ShouldClose())
	{

		shader.SetUniform4f("u_Color", 0.3f, 0.4f, 0.5f, 1.0f);
		renderer.DrawElements(model, indices, shader);
		
		window.SwapBuffers();
		WindowManager::PollEvents();
	}
	return 0;
}