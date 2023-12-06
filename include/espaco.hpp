#pragma once

#include <glm/glm.hpp>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include <SOIL/SOIL.h>
#include "primitivas.hpp"

namespace spc
{
    class espaco
    {
    private:
        GLuint texture;
        glm::vec3 position;
        glm::vec3 size;
        std::vector<std::vector<glm::vec3>> pontos;
        std::vector<std::vector<glm::vec2>> texCoords;
        GLfloat raio = 0.5f;
        GLuint nStacks = 50;
        GLuint nSectors = 50;

    public:
        espaco(GLfloat newSize, const char *filename)
        {
            position = glm::vec3(0.0f, 0.0f, 0.0f);
            size = glm::vec3(newSize, newSize, newSize);
            texture = SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
            if (texture == 0)
            {
                std::cout << "Error loading texture " << filename << std::endl;
            }
        }
        void draw();
    };

    class sol
    {
    private:
        glm::vec3 position;
        glm::vec3 size;
        std::vector<std::vector<glm::vec3>> pontos;
        std::vector<std::vector<glm::vec2>> texCoords;
        GLuint texture;
        GLfloat raio;
        GLuint nStacks;
        GLuint nSectors;

    public:
        sol(glm::vec3 newPosition, GLfloat newSize, const char *filename)
        {
            raio = 0.5f;
            nStacks = 50;
            nSectors = 50;
            position = newPosition;
            size.x = newSize;
            size.y = newSize;
            size.z = newSize;
            texture = SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
            if (texture == 0)
            {
                std::cout << "Error loading texture " << filename << std::endl;
            }
        }

        void draw();
    };

    class planeta
    {
    private:
        glm::vec3 position;
        glm::vec3 size;
        std::vector<std::vector<glm::vec3>> pontos;
        std::vector<std::vector<glm::vec2>> texCoords;
        GLuint texture;
        GLuint nStacks;
        GLuint nSectors;
        GLfloat raio;
        GLfloat rotation;

    public:
        planeta(glm::vec3 newPosition, GLfloat newSize, const char *filename)
        {
            raio = 0.5f;
            nStacks = 50;
            nSectors = 50;
            position = newPosition;
            size.x = newSize;
            size.y = newSize;
            size.z = newSize;
            texture = SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
            if (texture == 0)
            {
                std::cout << "Error loading texture " << filename << std::endl;
            }
        }

        glm::vec3 getPosition() const
        {
            return position;
        }

        float getRadius() const
        {
            return raio;
        }

        void updateRotations(GLfloat newRotation)
        {
            rotation += newRotation;
            if(rotation > 360.0f){
                rotation = 0.0f;
            }
        }

        void draw();
    };
}