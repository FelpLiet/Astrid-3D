#pragma once

#include <glm/glm.hpp>
#include <iostream>
#include <chrono>

namespace spc
{

    class canhao
    {
    public:
        canhao(const glm::vec3 &position, const glm::vec3 &direction)
            : position(position), direction(direction), radius(0.1f), drawCannon(true)
        {
            timeCreated = std::chrono::steady_clock::now();
            cannonTimerStart = timeCreated;
            lastUpdateTime = timeCreated;
        }

        void draw() const;

        const std::chrono::steady_clock::time_point &getTimeCreated() const
        {
            return timeCreated;
        }

        void updatePosition(const glm::vec3 &newPosition, const glm::vec3 &newDirection)
        {
            // Atualiza a posição do canhão para que ele esteja sempre na frente da câmera
            position = newPosition + newDirection * distanceFromCamera;

            // Atualiza a direção do canhão para que ele esteja sempre apontando na mesma direção que a câmera
            direction = newDirection;
        }

    private:
        std::chrono::steady_clock::time_point lastUpdateTime;
        glm::vec3 position;
        glm::vec3 direction;
        float radius;
        bool drawCannon;
        std::chrono::steady_clock::time_point timeCreated;
        std::chrono::steady_clock::time_point cannonTimerStart;
        float distanceFromCamera = -2.0f;
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