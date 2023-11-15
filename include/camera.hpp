#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

namespace spc
{

    class camera
    {
    private:
        glm::vec3 position;
        float yaw;
        float pitch;

        glm::vec3 getForward() const
        {
            glm::vec3 forward;
            forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
            forward.y = sin(glm::radians(pitch));
            forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
            return glm::normalize(forward);
        }

        glm::vec3 getRight() const
        {
            return glm::normalize(glm::cross(getForward(), glm::vec3(0.0f, 1.0f, 0.0f)));
        }

    public:
        camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
               float yaw = 0.0f, float pitch = 0.0f)
            : position(position), yaw(yaw), pitch(pitch) {}

        void moveForward(float distance)
        {
            position += distance * getForward();
        }

        void moveRight(float distance)
        {
            position += distance * getRight();
        }

        void rotate(float deltaYaw, float deltaPitch)
        {
            yaw += deltaYaw;
            pitch = glm::clamp(pitch + deltaPitch, -89.0f, 89.0f);
        }

        void lookAt() const
        {
            gluLookAt(position.x, position.y, position.z,
                      position.x + getForward().x, position.y + getForward().y, position.z + getForward().z,
                      0.0f, 1.0f, 0.0f);
        }

        void setCursorMode(GLFWwindow *window, int mode)
        {
            glfwSetInputMode(window, GLFW_CURSOR, mode);
        }

    };
}