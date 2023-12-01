#include "../include/window.hpp"

bool running = true, fullscreen;

//TODO implementar camera na classe
GLfloat cameraX = 16.0f, cameraY = 2.0f, cameraZ = -16.0f; // Camera position
GLfloat lookX = -0.67f, lookY = 0.24f, lookZ = 0.7f;      // Direction the camera is looking
int speed = 1;
GLfloat yaw = 0.0f, pitch = 0.0f; // Camera speed

extern spc::espaco *espaco;
extern spc::planeta *planetaTerra;

std::vector<spc::disparo> disparos;

void mouseButton(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        disparar();
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
    std::cout << lookX << " " << lookY << " " << lookZ << std::endl;
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClearDepth(1.0f);

    spc::drawDisparos(disparos);
    
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(cameraX, cameraY, cameraZ);
    espaco->draw();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    planetaTerra->draw();
    glPopMatrix();

    glutSwapBuffers();
}

void update(int)
{
    glutPostRedisplay();
    planetaTerra->updateRotation(1.0f);
    spc::verificaDisparos(disparos);
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
    glViewport(0, 0, x, y);
}

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

void mouseMotion(int x, int y)
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

    // Limit pitch to avoid flipping the camera upside down
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

//TODO colocar o disparar na classe
void disparar()
{
    glm::vec3 direcaoDisparo = glm::normalize(glm::vec3(lookX, lookY, lookZ));

    spc::disparo novoDisparo(glm::vec3(cameraX, cameraY, cameraZ), direcaoDisparo);
    disparos.push_back(novoDisparo);
}