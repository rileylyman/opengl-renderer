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

	glm::mat4 cameraView = glm::identity<glm::mat4>();
	cameraView = glm::translate(cameraView, glm::vec3(0.0f, 0.0f, -3.0f));

	glm::mat4 cameraProjection = glm::perspective(glm::radians(45.0f), 800.0f / 600, 0.1f, 100.0f);

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	/* Loop until the user closes the window */
	while (!window.ShouldClose())
	{
		renderer.Clear();

		for (unsigned int i = 0; i < 10; i++) {
			glm::vec3 t = cubePositions[i];

			model.SetModelMatrix(glm::translate(model.GetModelMatrix(), t));
			model.SetModelMatrix(
				glm::rotate(
					model.GetModelMatrix(), 
					glm::radians(20.0f * i), 
					glm::vec3(1.0f, 0.3f, 0.5f)
				)
			);

			shader.SetUniformMatrix4f("u_Transformation", cameraProjection * cameraView * model.GetModelMatrix());
			renderer.DrawElements(model, indices, shader);
			model.SetModelMatrix(glm::identity<glm::mat4>());
		}
		
		model.SetModelMatrix(glm::identity<glm::mat4>());

		window.SwapBuffers();
		WindowManager::PollEvents();
	}
	return 0;
}