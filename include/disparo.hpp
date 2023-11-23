#pragma once

#include <glm/glm.hpp>
#include <iostream>
#include <chrono>

namespace spc
{

    class disparo
    {
    public:
        disparo(const glm::vec3 &position, const glm::vec3 &direction)
            : position(position), direction(direction), radius(0.1f), drawPoint(true)
        {
            timeCreated = std::chrono::steady_clock::now();
            pointTimerStart = timeCreated;
            lastUpdateTime = timeCreated;
        }

        void draw() const;
        void updatePointStatus();
        bool isAlive() const;

        const std::chrono::steady_clock::time_point &getTimeCreated() const
        {
            return timeCreated;
        }

    private:
        std::chrono::steady_clock::time_point lastUpdateTime;
        glm::vec3 position;
        glm::vec3 direction;
        float radius;
        bool drawPoint;
        std::chrono::steady_clock::time_point timeCreated;
        std::chrono::steady_clock::time_point pointTimerStart;
        float speed = 5.0f;

        float deltaTime()
        {
            auto currentTime = std::chrono::steady_clock::now();
            float deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastUpdateTime).count() / 1000.0f;
            lastUpdateTime = currentTime;
            return deltaTime;
        }
    };

}
