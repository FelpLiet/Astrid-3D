#pragma once

#include <GL/glut.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include <SOIL/SOIL.h>

namespace spc
{
    void drawSphere(GLfloat raio, GLuint nStacks, GLuint nSectors, GLuint texture,
                    std::vector<std::vector<glm::vec3>> &pontos,
                    std::vector<std::vector<glm::vec2>> &texCoords);
}