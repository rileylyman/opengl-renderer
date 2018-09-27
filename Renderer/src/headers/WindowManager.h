#include <GLFW/glfw3.h>
#include <string>
#include <vector>

class WindowManager {
private:
	GLFWwindow * window;
	int width, height;
	std::string name;
public:
	WindowManager(bool *success);
	~WindowManager(); 

	bool CreateWindow(int width, int height, std::string& name);

	void MakeContextCurrent();

	inline static void PollEvents() { glfwPollEvents(); }

	inline void SwapBuffers() { glfwSwapBuffers(window); }
	inline bool ShouldClose() { return glfwWindowShouldClose(window); }

	inline GLFWwindow * GetWindow() const { return window; }
	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }
	inline std::string GetName() const { return name; }
};