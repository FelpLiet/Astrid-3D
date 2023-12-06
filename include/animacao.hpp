#pragma once

#include <GL/glut.h>
#include <glm/glm.hpp>
#include <SOIL/SOIL.h>
#include <iostream>
#include <vector>
#include <chrono>

namespace spc
{
    class animacao
    {
        private:
            std::vector<GLuint*> textureGif;
            glm::vec3 position;
            int currentFrame = 2;
            int maxFrames = 0;
            bool drawPoint;
        public:
            animacao(){
                loadGifTexture();
            }
            void setPosition(glm::vec3 position){
                this->position = position;
            }
            glm::vec3 getPosition(){
                return position;
            }
            bool getDrawpoint(){
                return drawPoint;
            }
            bool updatePointStatus();
            void loadGifTexture();
            void drawGif();
    };

    void verificaExplosao(std::vector<spc::animacao *> &explosaoAsteroides);
    void drawExplosao(std::vector<spc::animacao *> &explosaoAsteroides);
    void gerarExplosao(std::vector<spc::animacao *> &explosaoAsteroides, glm::vec3 position);
}