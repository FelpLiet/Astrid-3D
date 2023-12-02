#include "../include/disparo.hpp"
#include <GL/glut.h>
#include <cmath>

namespace spc
{

    void disparo::draw() const
    {
        glPushMatrix();
        glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT | GL_LIGHTING_BIT | GL_TEXTURE_BIT);

        // Ajuste a posição inicial para evitar que o disparo fique dentro da câmera
        glm::vec3 posicaoAjustada = position + 0.1f * direction;

        // Ativar iluminação
        glEnable(GL_LIGHTING);

        // Ativar a luz específica para o disparo
        glEnable(GL_LIGHT0);

        // Configuração de luz ambiente global, se necessário
        GLfloat globalAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

        // Configuração da cor e intensidade para um disparo de laser vermelho
        GLfloat lightColor[] = {1.0f, 0.0f, 0.0f, 1.0f};
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);

        // Definir a intensidade da luz (experimente diferentes valores)
        GLfloat lightIntensity = 1.0f;
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, lightIntensity);

        // Configurações adicionais da luz
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.01f); // Ajuste a atenuação para um efeito mais realista

        // Configuração de material para o disparo (ajuste conforme necessário)
        GLfloat materialAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
        GLfloat materialDiffuse[] = {1.0f, 0.0f, 0.0f, 1.0f};
        GLfloat materialSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
        GLfloat materialShininess = 50.0f;

        glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
        glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);

        glColor3f(1.0f, 0.0f, 0.0f); // Configura a cor antes de começar o desenho

        glTranslatef(posicaoAjustada.x, posicaoAjustada.y, posicaoAjustada.z);

        glutSolidSphere(radius, 20, 20); // Desenha uma esfera

        glDisable(GL_LIGHTING);
        glPopMatrix();
        glPopAttrib(); 
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

    void verificaDisparos(std::vector<spc::disparo> &disparos)
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
    }

    void drawDisparos(const std::vector<spc::disparo> &disparos)
    {
        for (const auto &disparo : disparos)
        {
            disparo.draw();
        }
    }

    void disparar(std::vector<spc::disparo> &disparos, const glm::vec3 &position, const glm::vec3 &direction)
    {
        glm::vec3 newDirection = glm::normalize(direction);
        spc::disparo novoDisparo(position, newDirection);
        disparos.push_back(novoDisparo);
    }

}