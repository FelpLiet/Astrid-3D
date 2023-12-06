#include "../include/animacao.hpp"

namespace spc
{
    bool animacao::updatePointStatus()
    {
        if (currentFrame == maxFrames)
        {
            drawPoint = false;
            return false;
        }
        else
        {
            drawPoint = true;
            currentFrame++;
            return true;
        }
    }

    void animacao::loadGifTexture()
    {
        while (true)
        {
            GLuint *texture = new GLuint;
            char path[100];
            sprintf(path, "assets/explosao/frame_%d.png", currentFrame);
            *texture = SOIL_load_OGL_texture(path, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
            if (*texture == 0)
            {
                std::cout << "Error loading texture " << path << std::endl;
                break;
            }
            textureGif.push_back(texture);
            currentFrame++;
        }
        currentFrame = 2;
        maxFrames = textureGif.size();
    }

    void animacao::drawGif()
    {
        glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT | GL_LIGHTING_BIT | GL_TEXTURE_BIT);
        glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glTranslatef(position.x, position.y, position.z);
        glBindTexture(GL_TEXTURE_2D, *textureGif[currentFrame]);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, 0.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f, 0.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(1.0f, -1.0f, 0.0f);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
        glPopAttrib();
        // std::cout << "currentFrame: " << currentFrame << std::endl;
    }

    void verificaExplosao(std::vector<spc::animacao *> &explosaoAsteroides)
    {
        for (auto it = explosaoAsteroides.begin(); it != explosaoAsteroides.end();)
        {
            if ((*it)->updatePointStatus())
            {
                it++;
            }
            else
            {
                it = explosaoAsteroides.erase(it);
            }
        }
    }

    void drawExplosao(std::vector<spc::animacao *> &explosaoAsteroides)
    {
        std::cout << "tamanho esplosoes: " << explosaoAsteroides.size() << std::endl;
        for (const auto &explosao : explosaoAsteroides)
        {
            explosao->drawGif();
            if(explosao->getDrawpoint())
                std::cout << "desenhou" << std::endl;
            else
                std::cout << "nao desenhou" << std::endl;
            //std::cout << "desenhou" << explosao->getPosition().x<< " " << explosao->getPosition().y<< " " << explosao->getPosition().z<< " " << std::endl;
        }
        
    }

    void gerarExplosao(std::vector<spc::animacao *> &explosaoAsteroides, glm::vec3 position)
    {
        spc::animacao *explosao = new spc::animacao();
        explosao->setPosition(position);
        explosaoAsteroides.push_back(explosao);
        std::cout << "gerou" << std::endl;
    }
}