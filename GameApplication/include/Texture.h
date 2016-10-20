#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "Common.h"

//Loads Texture from Memory
GLuint loadTextureFromMemory(const char * pMem, int size);

//Load Texture from File
GLuint	loadTextureFromFile(const std::string& filename);

//Load Texture from font
GLuint	loadTextureFromFont(const std::string& fontFilename, int	pointSize, const std::string& text);

//Utility function to convert any SDL surface to OpenGL Texture
GLuint convertSDLSurfaceToTexture(SDL_Surface * surface);

#endif
