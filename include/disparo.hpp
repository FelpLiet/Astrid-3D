#pragma once

#include <GL/glut.h>
#include <cmath>
#include <glm/glm.hpp>
#include <iostream>
#include <chrono>
#include <vector>

namespace spc
{

    class disparo
    {
    private:
        glm::vec3 position;
        glm::vec3 direction;
        float radius;
        bool drawPoint;
        float speed = 30.0f;
        std::chrono::steady_clock::time_point lastUpdateTime;
        std::chrono::steady_clock::time_point timeCreated;
        std::chrono::steady_clock::time_point pointTimerStart;

        float deltaTime()
        {
            auto currentTime = std::chrono::steady_clock::now();
            float deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastUpdateTime).count() / 1000.0f;
            lastUpdateTime = currentTime;
            return deltaTime;
        }

    public:
        disparo(const glm::vec3 &position, const glm::vec3 &direction)
            : position(position), direction(direction), radius(0.1f), drawPoint(true)
        {
            timeCreated = std::chrono::steady_clock::now();
            pointTimerStart = timeCreated;
            lastUpdateTime = timeCreated;
        }

        glm::vec3 getPosition() const
        {
            return position;
        }

        void draw() const;
        void updatePointStatus();
        bool isAlive() const;
        bool isColliding(const glm::vec3 &position, float radius) const;

        const std::chrono::steady_clock::time_point &getTimeCreated() const
        {
            return timeCreated;
        }

    };

    void verificaDisparos(std::vector<spc::disparo> &disparos);

    void drawDisparos(const std::vector<spc::disparo> &disparos);

    void disparar(std::vector<spc::disparo> &disparos, const glm::vec3 &position, const glm::vec3 &direction);
}
