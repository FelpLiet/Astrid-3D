#pragma once

#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace spc
{
    class camera
    {
    private:
        glm::vec3 position;
        glm::vec3 direction;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 worldUp;
        float yaw;
        float pitch;
        float movementSpeed;
        float mouseSensitivity;
        float zoom;

        void updateCameraVectors();
    
    public:
        camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
               glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
               float yaw = -90.0f,
               float pitch = 0.0f);
        ~camera();

        glm::mat4 getViewMatrix();
        void moveForward(float deltaTime);
        void moveRight(float deltaTime);
        void moveUp(float deltaTime);
        void rotate(float xoffset, float yoffset, bool constrainPitch = true);
        void zoomIn(float yoffset);
    };

}