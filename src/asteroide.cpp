#include "../include/asteroide.hpp"

namespace spc
{
    void asteroide::draw()
    {
        glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT | GL_LIGHTING_BIT | GL_TEXTURE_BIT);
        glPushMatrix();
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT1);
        GLfloat light_position[] = {10.0, 9.0, 10.0, 1.0};
        GLfloat light_ambient[] = {0.1, 0.1, 0.1, 1.0};
        GLfloat light_diffuse[] = {1.5f, 1.5f, 1.5f, 1.0f}; 
        GLfloat light_specular[] = {2.0f, 2.0f, 2.0f, 1.0f};
        GLfloat att_constant = 0.2;
        GLfloat att_linear = 0.1;
        GLfloat att_quadratic = 0.0;
        GLfloat spot_direction[] = {0.0, 0.0, 0.0};
        GLfloat spot_exponent = 0.0;
        GLfloat spot_cutoff = 180.0;

        glLightfv(GL_LIGHT1, GL_POSITION, light_position);
        glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
        glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
        glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, att_constant);
        glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, att_linear);
        glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, att_quadratic);
        glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
        glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spot_exponent);
        glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spot_cutoff);
        glm::vec3 posicaoAjustada = position + 0.1f * direction;
        glTranslatef(posicaoAjustada.x, posicaoAjustada.y, posicaoAjustada.z);
        // glutSolidSphere(radius, 20, 20);
        drawSphere(radius, nStacks, nSectors, texture, pontos, texCoords);
        glPopMatrix();
        glPopAttrib();
    }
    void asteroide::updatePointStatus()
    {
        auto currentTime = std::chrono::steady_clock::now();
        if (drawPoint && std::chrono::duration_cast<std::chrono::seconds>(currentTime - pointTimerStart).count() >= 1)
        {
            drawPoint = false;
        }
        position += direction * speed * deltaTime();
        // std::cout << position.x << " " << position.y << " " << position.z << std::endl;
    }

    bool asteroide::isAlive() const
    {
        return position.y > 0;
    }

    bool asteroide::isColliding(const glm::vec3 &position, float radius) const
    {
        return glm::distance(this->position, position) <= this->radius + radius;
    }

    void verificaAsteroides(std::vector<spc::asteroide*> &asteroides)
    {
        for (auto it = asteroides.begin(); it != asteroides.end();)
        {
            it[0]->updatePointStatus();
            if (!it[0]->isAlive())
            {
                it = asteroides.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    void drawAsteroides(std::vector<spc::asteroide*> &asteroides)
    {
        for (auto &asteroide : asteroides)
        {
            asteroide->draw();
        }
    }

    void gerarAsteroide(std::vector<spc::asteroide*> &asteroides)
    {
        // ramdom x position between -16 and 16
        float x = (float)(rand() % 32) - 16.0f;
        // random y position between 12 and 16
        float y = (float)(rand() % 4) + 12.0f;
        // random z position between 0 and 16
        float z = (float)(rand() % 16);
        glm::vec3 pontoPartida = glm::vec3(x, y, z);
        glm::vec3 pontoFinal = glm::vec3(10, 0, -10);
        glm::vec3 newDirection = glm::normalize(pontoFinal - pontoPartida);

        // glm::vec3 pontoPartida = glm::vec3(20, 10, 40);
        // glm::vec3 pontoFinal = glm::vec3(10, 0, -10);
        // glm::vec3 newDirection = glm::normalize(pontoFinal - pontoPartida);
        spc::asteroide *novoAsteroide = new spc::asteroide(pontoPartida, newDirection);
        asteroides.push_back(novoAsteroide);
    }
}