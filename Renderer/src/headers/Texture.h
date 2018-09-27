#pragma once

#include <string>

class Texture {
	
private:
	unsigned int id;
	int width;
	int height;
	int bpp;
	std::string filepath;

	unsigned int slot;

public:
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int s = 0);
	void Unbind() const;

	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }
	inline int GetBPP() const { return bpp; }
	inline std::string GetFilepath() const { return filepath; }

	inline unsigned int GetSlot() const { return slot; }
};
