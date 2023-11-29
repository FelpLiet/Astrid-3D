#include "../include/disparo.hpp"
#include <GL/glut.h>
#include <cmath>

namespace spc
{

    void disparo::draw() const
    {
        glPushMatrix();

        // Ajuste a posição inicial para evitar que o disparo fique dentro da câmera
        glm::vec3 posicaoAjustada = position + 0.1f * direction;

        glColor3f(1.0f, 0.0f, 0.0f); // Configura a cor antes de começar o desenho

        glTranslatef(posicaoAjustada.x, posicaoAjustada.y, posicaoAjustada.z);

        glutSolidSphere(radius, 20, 20); // Desenha uma esfera

        glPopMatrix();
    }

    void disparo::updatePointStatus()
    {
        auto currentTime = std::chrono::steady_clock::now();
        if (drawPoint && std::chrono::duration_cast<std::chrono::seconds>(currentTime - pointTimerStart).count() >= 1)
        {
            drawPoint = false;
        }

        // Atualize a posição do disparo com base na direção e velocidade
        position += direction * speed * deltaTime();
    }

    bool disparo::isAlive() const
    {
        auto currentTime = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::seconds>(currentTime - timeCreated).count() < 1;
    }

}