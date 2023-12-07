#include "../include/cannon.hpp"
#include <GL/glut.h>
#include <cmath>

namespace spc
{
    void canhao::draw() const
    {
        glPushAttrib(GL_CURRENT_BIT);
        glPushMatrix();

        // Ajuste a posição inicial para evitar que o disparo fique dentro da câmera
        glm::vec3 posicaoAjustada = position + 0.1f * direction;

        // // Inclinação do cilindro em 45 graus no eixo Y
        // float angleInRadians = glm::radians(45.0f);
        // float cosTheta = std::cos(angleInRadians);
        // float sinTheta = std::sin(angleInRadians);

        // // Matriz de rotação manual
        // glm::mat3 rotationMatrixY = {
        //     cosTheta, 0.0f, sinTheta,
        //     0.0f, 1.0f, 0.0f,
        //     -sinTheta, 0.0f, cosTheta};

        // // Aplica a rotação ao vetor de direção
        // glm::vec3 rotatedDirection = rotationMatrixY * direction;

        // Translada para a posição do canhão
        glTranslatef(posicaoAjustada.x, posicaoAjustada.y, posicaoAjustada.z);

        // Rotaciona o canhão para apontar na direção correta
        float angle = glm::degrees(glm::atan(direction.y, direction.x));
        glRotatef(angle, 0.0f, 0.0f, 1.0f);

        glColor3f(0.0f, 1.0f, 0.0f); // Cor verde para o canhão
        const int sides = 30;
        const float height = 0.5f; // Reduzi a altura do cilindro

        // Desenha a base do cilindro
        glBegin(GL_POLYGON);
        for (int i = 0; i < sides; ++i)
        {
            float angle = 2.0f * M_PI * static_cast<float>(i) / static_cast<float>(sides);
            float x = posicaoAjustada.x + radius * std::cos(angle);
            float y = posicaoAjustada.y + radius * std::sin(angle);
            glVertex3f(x, y, posicaoAjustada.z);
        }
        glEnd();

        // Desenha a parte lateral do cilindro
        glBegin(GL_QUAD_STRIP);
        for (int i = 0; i <= sides; ++i)
        {
            float angle = 2.0f * M_PI * static_cast<float>(i) / static_cast<float>(sides);
            float x = posicaoAjustada.x + radius * std::cos(angle);
            float y = posicaoAjustada.y + radius * std::sin(angle);

            glVertex3f(x, y, posicaoAjustada.z);
            glVertex3f(x, y, posicaoAjustada.z + height);
        }
        glEnd();

        glPopMatrix();
        glPopAttrib();
    }
}
