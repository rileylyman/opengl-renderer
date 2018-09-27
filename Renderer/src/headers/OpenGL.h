#pragma once

#include "GL/glew.h"
#include <iostream>

#define ASSERT(x) if (!(x)) __debugbreak();

/**
 * Clears all Gl errors, then checks if the wrapped call created any errors.
 */
#define GLCall(x) GLClearError();x;ASSERT(GLLogCall());

#ifndef OPEN_GL_ERROR
#define OPEN_GL_ERROR

/**
 * Clears all errors from the OpenGL error log.
 */
extern void GLClearError();

/**
 * Returns true if OpenGL has logged errors.
 */
extern bool GLLogCall();

#endif