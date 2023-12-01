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
        GLfloat cameraX, cameraY, cameraZ;         
        GLfloat lookX, lookY, lookZ;
        GLfloat yaw, pitch;
        int speed;

    public:
        camera()
        {
            std::cout << "Camera criada" << std::endl;
            cameraX = 16.0f;
            cameraY = 2.0f;
            cameraZ = -16.0f;
            lookX = -0.67f;
            lookY = 0.24f;
            lookZ = 0.7f;
            speed = 1;
            yaw = 2.3f;
            pitch = 0.21f;
        }
        ~camera();

        GLfloat getCameraX() { return cameraX; }
        GLfloat getCameraY() { return cameraY; }
        GLfloat getCameraZ() { return cameraZ; }
        GLfloat getLookX() { return lookX; }
        GLfloat getLookY() { return lookY; }
        GLfloat getLookZ() { return lookZ; }
        GLfloat getYaw() { return yaw; }
        GLfloat getPitch() { return pitch; }
        int getSpeed() { return speed; }

        void cameraLookAt();

        void updateCameraLook(GLfloat x, GLfloat y);

        void moveForward();

        void moveBackward();

        void moveLeft();

        void moveRight();

        void moveUp();

        void moveDown();
    };

}