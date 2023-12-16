#pragma once 

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

GLuint loadAndCompileShader(GLenum shaderType, const std::string& filename);
void initShaders(GLuint &shaderProgram);