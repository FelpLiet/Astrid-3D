#include "../include/camera.hpp"

extern bool debug;

namespace spc
{
    camera::~camera()
    {
    }

    void camera::cameraLookAt()
    {
        gluLookAt(cameraX, cameraY, cameraZ,                         // Camera position
                  cameraX + lookX, cameraY + lookY, cameraZ + lookZ, // Look at point
                  0.0f, 1.0f, 0.0f);

        std::cout << lookX << " " << lookY << " " << lookZ << std::endl;
        std::cout << cameraX << " " << cameraY << " " << cameraZ << std::endl;
        if (cameraX > 16.0f)
            cameraX = 16.0f;
        if (cameraX < -16.0f)
            cameraX = -16.0f;
        if (cameraZ > 16.0f)
            cameraZ = 16.0f;
        if (cameraZ < -16.0f)
            cameraZ = -16.0f;
        if(cameraY > 10.0f)
            cameraY = 10.0f;
        if(cameraY < -10.0f)
            cameraY = -10.0f;
    }

    void camera::updateCameraLook(GLfloat x, GLfloat y)
    {
        static int lastX = -1, lastY = -1;
        if (lastX == -1)
            lastX = x;
        if (lastY == -1)
            lastY = y;

        int dx = x - lastX;
        int dy = y - lastY;

        const float sensitivity = 0.007f;
        yaw += dx * sensitivity;
        pitch -= dy * sensitivity;

        // Limit pitch and yaw
        // if (debug)
        // {
        //     if (pitch > 1.0f)
        //         pitch = 1.0f;
        //     if (pitch < -1.0f)
        //         pitch = -1.0f;
        //     if (yaw > 4.0f)
        //         yaw = 4.0f;
        //     if (yaw < 1.3f)
        //         yaw = 1.3f;
        // }else{
        if (pitch > 1.0f)
            pitch = 1.0f;
        if (pitch < -1.0f)
            pitch = -1.0f;
        // Wrap yaw value for smooth 360 degree rotation
        if (yaw > 2.0f * M_PI)
            yaw -= 2.0f * M_PI;
        if (yaw < 0.0f)
            yaw += 2.0f * M_PI;
        // }

        std::cout << "pitch: " << pitch << std::endl;
        std::cout << "yaw: " << yaw << std::endl;
        // Update camera direction
        lookX = cos(yaw) * cos(pitch);
        lookY = sin(pitch);
        lookZ = sin(yaw) * cos(pitch);

        // Update last mouse position
        lastX = x;
        lastY = y;
    }

    void camera::moveForward()
    {
        // Move forward
        // std::cout << "w" << std::endl;
        cameraX += lookX * speed;
        cameraZ += lookZ * speed;
    }

    void camera::moveBackward()
    {
        // Move backward
        // std::cout << "s" << std::endl;
        cameraX -= lookX * speed;
        cameraZ -= lookZ * speed;
    }

    void camera::moveLeft()
    {
        // Strafe left
        // std::cout << "a" << std::endl;
        cameraX += lookZ * speed;
        cameraZ -= lookX * speed;
    }

    void camera::moveRight()
    {
        // Strafe right
        // std::cout << "d" << std::endl;
        cameraX -= lookZ * speed;
        cameraZ += lookX * speed;
    }

    void camera::moveUp()
    {
        // Move up
        // std::cout << "q" << std::endl;
        cameraY += speed;
    }

    void camera::moveDown()
    {
        // Move down
        // std::cout << "e" << std::endl;
        cameraY -= speed;
    }
}