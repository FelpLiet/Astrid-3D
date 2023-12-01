#include "../include/window.hpp"

bool running = true, fullscreen;

extern spc::espaco *espaco;
extern spc::planeta *planetaTerra;
extern spc::camera *camera;

std::vector<spc::disparo> disparos;

void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    camera->cameraLookAt();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClearDepth(1.0f);

    spc::drawDisparos(disparos);
    
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    espaco->draw();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    planetaTerra->draw();
    glPopMatrix();

    glutSwapBuffers();
}

void mouseMotion(int x, int y)
{
    camera->updateCameraLook(x, y);
}

void mouseButton(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        disparar();
    }
}

void timerUpdate(int)
{
    glutPostRedisplay();
    planetaTerra->updateRotation(1.0f);
    spc::verificaDisparos(disparos);
    glutTimerFunc(1000 / FPS, timerUpdate, 0);
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
        camera->moveForward();
        break;
    case 's':
        // Move backward
        // std::cout << "s" << std::endl;
        camera->moveBackward();
        break;
    case 'a':
        // Strafe left
        // std::cout << "a" << std::endl;
        camera->moveLeft();
        break;
    case 'd':
        // Strafe right
        // std::cout << "d" << std::endl;
        camera->moveRight();
        break;
    case 'q':
        // Move up
        // std::cout << "q" << std::endl;
        camera->moveUp();
        break;
    case 'e':
        // Move down
        // std::cout << "e" << std::endl;
        camera->moveDown();
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

//TODO colocar o disparar na classe
void disparar()
{
    glm::vec3 direcaoDisparo = glm::normalize(glm::vec3(camera->getLookX(), camera->getLookY(), camera->getLookZ()));

    spc::disparo novoDisparo(glm::vec3(camera->getCameraX(), camera->getCameraY(), camera->getCameraZ()), direcaoDisparo);
    disparos.push_back(novoDisparo);
}