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

    void disparo::drawLightPoints() const
    {
        glPushMatrix();

        // Ajuste a posição inicial para evitar que o disparo fique dentro da câmera
        glm::vec3 posicaoAjustada = position + 0.1f * direction;

        // Configuração da cor e intensidade para um disparo de laser vermelho
        GLfloat materialAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
        GLfloat materialDiffuse[] = {1.0f, 0.0f, 0.0f, 1.0f};
        GLfloat materialSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
        GLfloat materialShininess = 50.0f;

        glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
        glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);

        glColor3f(1.0f, 0.0f, 0.0f); // Configura a cor antes de começar o desenho

        // Aplica a mesma transformação à posição do disparo
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

    void verificaDisparos(std::vector<spc::disparo> &disparos, std::vector<spc::disparo> &lightPoints)
    {
        for (auto it = disparos.begin(); it != disparos.end();)
        {
            it->updatePointStatus();
            if (!it->isAlive())
            {
                it = disparos.erase(it);
            }
            else
            {
                ++it;
            }
        }

        // Verificar os pontos de luz correspondentes
        for (auto it = lightPoints.begin(); it != lightPoints.end();)
        {
            it->updatePointStatus(); // Supondo que a luz tenha uma função semelhante a updatePointStatus
            if (!it->isAlive())
            {
                it = lightPoints.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    void drawDisparos(const std::vector<spc::disparo> &disparos, const std::vector<spc::disparo> &lightPoints)
    {
        // Desenhar os disparos
        for (const auto &disparo : disparos)
        {
            disparo.draw();
        }

        // Desenhar os pontos de luz correspondentes
        for (const auto &lightPoint : lightPoints)
        {
            lightPoint.drawLightPoints(); // Supondo que exista uma função draw para a luz
        }
    }
}