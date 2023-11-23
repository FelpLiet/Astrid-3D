#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <SOIL/SOIL.h>
#include "textura.hpp"

namespace spc
{

    class planeta
    {
    private:
        glm::vec3 position;
        glm::vec3 size;
        glm::vec3 rotation;
        GLuint texture;

    public:
        /*
         * Construtor da classe planeta
         * @param newPosition posição do planeta
         * @param newSize tamanho do planeta
         * @param filename nome do arquivo da textura
         */
        planeta(glm::vec3 newPosition, glm::vec3 newSize, const char *filename)
        {
            position = newPosition;
            size = newSize;
            texture = SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
            if (texture == 0)
            {
                std::cout << "Error loading texture " << filename << std::endl;
            }
        }

        /*
         * Destrutor da classe planeta
         */
        ~planeta();

        /*
         * Desenha o planeta
         */
        void draw();

        void updateRotation(float angle)
        {
            rotation.y += angle;
        }
    };

    class espaco
    {
    private:
        GLfloat size;
        GLuint texture;

    public:
        espaco(GLfloat newSize, const char *filename)
        {
            size = newSize;
            texture = SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
            if (texture == 0)
            {
                std::cout << "Error loading texture " << filename << std::endl;
            }
        }
        void draw();
    };
}