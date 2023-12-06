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
            *texture = SOIL_load_OGL_texture(path, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
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
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glTranslatef(position.x, position.y, position.z);
        
        try
        {
            glBindTexture(GL_TEXTURE_2D, *textureGif.at(currentFrame));
        }
        catch (const std::out_of_range &oor)
        {
            std::cerr << "Out of Range error: " << oor.what() << '\n';
        }

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
        glDisable(GL_BLEND);
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
                delete *it;
                it = explosaoAsteroides.erase(it);
            }
        }
    }

    void drawExplosao(std::vector<spc::animacao *> &explosaoAsteroides)
    {
        for (const auto &explosao : explosaoAsteroides)
        {
            explosao->drawGif();
        }
    }

    void gerarExplosao(std::vector<spc::animacao *> &explosaoAsteroides, glm::vec3 position)
    {
        spc::animacao *explosao = new spc::animacao();
        explosao->setPosition(position);
        explosaoAsteroides.push_back(explosao);
    }
}