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
        textura *text;

    public:
        /*
        * Construtor da classe planeta
        * @param newPosition posição do planeta
        * @param newSize tamanho do planeta
        */
        planeta(glm::vec3 newPosition, glm::vec3 newSize);

        /*
        * Destrutor da classe planeta
        */
        ~planeta();

        /*
        * Desenha o planeta
        */
        void draw();

        /*
        * Carrega a textura do planeta
        * @param filename nome do arquivo da textura
        */
        void loadTexture(const char *filename);
    };

}