#pragma once

class IndexBuffer {
private:
	unsigned int id;
	unsigned int count;
public:
	IndexBuffer(unsigned int* data, unsigned int _count);

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return count; }
};