#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include <obj_loader/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>
#include<png.h>

class BMPProcessor 
{
public:
	GLuint loadBitmap(const char *fname);
};
