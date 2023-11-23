#include "../include/window.hpp"

bool running = true, fullscreen;

GLfloat cameraX = 0.0f, cameraY = 0.0f, cameraZ = 5.0f; // Camera position
GLfloat lookX = 0.0f, lookY = 0.0f, lookZ = -1.0f;      // Direction the camera is looking
int speed = 1;
GLfloat yaw = 0.0f, pitch = 0.0f; // Camera speed

// spc::planeta planetaTerra(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, -1.0f), "assets/wesley.jpg");
extern spc::espaco *espaco;
extern spc::planeta *planetaTerra;

void input(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    case 'f':
    case 'F':
        fullscreen = !fullscreen;
        if (fullscreen)
            glutFullScreen();
        else
            glutReshapeWindow(1366, 768);
        break;
    case 'w':
        // Move forward
        // std::cout << "w" << std::endl;
        cameraX += lookX * speed;
        cameraY += lookY * speed;
        cameraZ += lookZ * speed;
        break;
    case 's':
        // Move backward
        // std::cout << "s" << std::endl;
        cameraX -= lookX * speed;
        cameraY -= lookY * speed;
        cameraZ -= lookZ * speed;
        break;
    case 'a':
        // Strafe left
        // std::cout << "a" << std::endl;
        cameraX += lookZ * speed;
        cameraZ -= lookX * speed;
        break;
    case 'd':
        // Strafe right
        // std::cout << "d" << std::endl;
        cameraX -= lookZ * speed;
        cameraZ += lookX * speed;
        break;
    case 'q':
        // Move up
        // std::cout << "q" << std::endl;
        cameraY += speed;
        break;
    case 'e':
        // Move down
        // std::cout << "e" << std::endl;
        cameraY -= speed;
        break;
    case 'm':
        // Lock the mouse to the center of the screen
        if (glutGet(GLUT_WINDOW_CURSOR) == GLUT_CURSOR_NONE)
            glutSetCursor(GLUT_CURSOR_INHERIT);
        else
            glutSetCursor(GLUT_CURSOR_NONE);
        break;
    default:
        break;
    }
}

void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ,                         // Camera position
              cameraX + lookX, cameraY + lookY, cameraZ + lookZ, // Look at point
              0.0f, 1.0f, 0.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClearDepth(1.0f);
    
    glPushMatrix();
    glTranslatef(cameraX, cameraY, cameraZ);
    espaco->draw();
    glPopMatrix();

    planetaTerra->draw();

    glutSwapBuffers();
}

void update(int)
{
    glutPostRedisplay();
    planetaTerra->updateRotation(1.0f);
    glutTimerFunc(1000 / FPS, update, 0);
}

void resize_callback(int x, int y)
{
    if (y == 0 || x == 0)
        return;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 50.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, x, y); // renderiza en toda la ventana
}

void mouseMotion(int x, int y)
{
    static int lastX = -1, lastY = -1; // Last mouse position
    if (lastX == -1)
        lastX = x; // Initialize lastX and lastY
    if (lastY == -1)
        lastY = y;

    // Calculate mouse movement
    int dx = x - lastX;
    int dy = y - lastY;

    // Update yaw and pitch
    const float sensitivity = 0.007f; // Adjust this value as needed
    yaw += dx * sensitivity;
    pitch -= dy * sensitivity;

    // Limit pitch to avoid flipping the camera upside down
    std::cout << "yaw: " << yaw << " pitch: " << pitch << std::endl;
    if (pitch > 1.0f)
        pitch = 1.0f;
    if (pitch < -1.0f)
        pitch = -1.0f;

    // Update camera direction
    lookX = cos(yaw) * cos(pitch);
    lookY = sin(pitch);
    lookZ = sin(yaw) * cos(pitch);

    // Update last mouse position
    lastX = x;
    lastY = y;
}