#include "OpenGL.h"
#include <vector>

struct LayoutElement {
	unsigned int count;
	unsigned int type;
	unsigned char normalized;
};

class VertexLayout {

private:
	unsigned int stride;
	std::vector<LayoutElement> elements;
public:
	VertexLayout() : stride(0) {}

	template<typename T>
	void Push(unsigned int count);

	template<>
	void Push<float>(unsigned int count) {
		elements.push_back({ count, GL_FLOAT, GL_FALSE });
	}

	inline unsigned int GetStride() const { return stride; }
	inline std::vector<LayoutElement> GetElements() const { return elements; }

	static unsigned int SizeOf(unsigned int type) {

		switch (type) {
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
		}
		return 0;
	}
};