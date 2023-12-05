#include "../include/asteroide.hpp"

namespace spc
{
    void asteroide::draw()
    {
        glPushMatrix();
        glm::vec3 posicaoAjustada = position + 0.1f * direction;
        glTranslatef(posicaoAjustada.x, posicaoAjustada.y, posicaoAjustada.z);
        glColor3f(1.0f, 1.0f, 1.0f);
        glutSolidSphere(radius, 20, 20);
        // drawSphere(raio, nStacks, nSectors, texture, pontos, texCoords);
        glPopMatrix();
    }
    void asteroide::updatePointStatus()
    {
        auto currentTime = std::chrono::steady_clock::now();
        if (drawPoint && std::chrono::duration_cast<std::chrono::seconds>(currentTime - pointTimerStart).count() >= 1)
        {
            drawPoint = false;
        }
        position += direction * speed * deltaTime();
        std::cout << position.x << " " << position.y << " " << position.z << std::endl;
    }

    bool asteroide::isAlive() const
    {
        return position.y > 0;
    }

    void verificaAsteroides(std::vector<spc::asteroide> &asteroides)
    {
        for (auto it = asteroides.begin(); it != asteroides.end();)
        {
            it->updatePointStatus();
            if (!it->isAlive())
            {
                it = asteroides.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    void drawAsteroides(std::vector<spc::asteroide> &asteroides)
    {
        for (auto &asteroide : asteroides)
        {
            asteroide.draw();
        }
    }

    void gerarAsteroide(std::vector<spc::asteroide> &asteroides)
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
        spc::asteroide novoAsteroide(pontoPartida, newDirection);
        asteroides.push_back(novoAsteroide);
    }
}