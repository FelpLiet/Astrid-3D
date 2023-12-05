#pragma once

#include <GL/glut.h>
#include <glm/glm.hpp>
#include <vector>
#include <chrono>
#include "primitivas.hpp"

namespace spc
{
    class asteroide
    {
    private:
        glm::vec3 position;
        glm::vec3 direction;
        float radius;
        bool drawPoint;
        float speed = 10.0f;
        std::chrono::steady_clock::time_point lastUpdateTime;
        std::chrono::steady_clock::time_point timeCreated;
        std::chrono::steady_clock::time_point pointTimerStart;
        std::vector<std::vector<glm::vec3>> pontos;
        std::vector<std::vector<glm::vec2>> texCoords;
        GLuint texture;
        GLuint nStacks;
        GLuint nSectors;
        GLfloat raio;

        float deltaTime()
        {
            auto currentTime = std::chrono::steady_clock::now();
            float deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastUpdateTime).count() / 1000.0f;
            lastUpdateTime = currentTime;
            return deltaTime;
        }

    public:
        asteroide(const glm::vec3 &newPosition, const glm::vec3 &newDirection)
        {
            timeCreated = std::chrono::steady_clock::now();
            pointTimerStart = timeCreated;
            lastUpdateTime = timeCreated;
            position = newPosition;
            direction = newDirection;
            radius = 1.0f;
            nStacks = 50;
            nSectors = 50;
            texture = SOIL_load_OGL_texture("assets/asteroide.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
            if (texture == 0)
            {
                std::cout << "Error loading texture " << std::endl;
            }
        }

        glm::vec3 getPosition() const
        {
            return position;
        }

        float getRadius() const
        {
            return radius;
        }

        void setDrawPoint(bool drawPoint)
        {
            this->drawPoint = drawPoint;
            pointTimerStart = std::chrono::steady_clock::now();
        }

        void draw();
        void updatePointStatus();
        bool isAlive() const;
        bool isColliding(const glm::vec3 &position, float radius) const;

        const std::chrono::steady_clock::time_point &getTimeCreated() const
        {
            return timeCreated;
        }

    };

    void verificaAsteroides(std::vector<spc::asteroide*> &asteroides);

    void drawAsteroides(std::vector<spc::asteroide*> &asteroides);

    void gerarAsteroide(std::vector<spc::asteroide*> &asteroides);
}