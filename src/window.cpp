#include "../include/window.hpp"

bool running = true, fullscreen = true, debug = false, mouse = false;
extern GLuint shaderProgram;
extern spc::espaco *espaco;
extern spc::planeta *planetaTerra;
extern spc::sol *sol;
extern spc::camera *camera;
extern spc::animacao *explosao;

std::vector<spc::disparo> disparos;
std::vector<spc::asteroide *> asteroides;
std::vector<spc::animacao *> explosaoAsteroides;

void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_MULTISAMPLE);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    camera->cameraLookAt();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClearDepth(1.0f);

    spc::drawDisparos(disparos);

    spc::drawAsteroides(asteroides);

    spc::drawExplosao(explosaoAsteroides);

    espaco->draw();

    planetaTerra->draw();

    sol->draw();

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
        spc::disparar(disparos, camera->getCameraPosition(), camera->getLookPosition());
    }
}

void timerUpdate(int)
{
    glutPostRedisplay();
    planetaTerra->updateRotations(0.1f);
    spc::verificaDisparos(disparos);
    spc::verificaAsteroides(asteroides);
    disparoColideAsteroide(disparos, asteroides);
    asteroideColidePlaneta(asteroides, planetaTerra);
    glutTimerFunc(1000 / FPS, timerUpdate, 0);
}

void createAsteroid(int)
{
    spc::gerarAsteroide(asteroides);
    glutTimerFunc(2000, createAsteroid, 0);
}

void timerExplosao(int)
{
    spc::verificaExplosao(explosaoAsteroides);
    glutTimerFunc(1000 / 30, timerExplosao, 0);
}

void resize_callback(int x, int y)
{
    if (y == 0 || x == 0)
        return;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0, (GLdouble)x / (GLdouble)y, 0.5, 50.0);
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
        if (fullscreen)
            glutFullScreen();
        else
            glutReshapeWindow(1366, 768);
        fullscreen = !fullscreen;
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
        if(mouse){
            glutSetCursor(GLUT_CURSOR_NONE);
        }else{
            glutSetCursor(GLUT_CURSOR_INHERIT);
        }
        mouse = !mouse;
        break;
    case ';':
        debug = !debug;
    default:
        break;
    }
}

void disparoColideAsteroide(std::vector<spc::disparo> &disparos, std::vector<spc::asteroide *> &asteroides)
{
    for (auto it = disparos.begin(); it != disparos.end();)
    {
        for (auto it2 = asteroides.begin(); it2 != asteroides.end();)
        {
            if (it[0].isColliding(it2[0]->getPosition(), it2[0]->getRadius()))
            {
                gerarExplosao(explosaoAsteroides, it2[0]->getPosition());
                it2[0]->setDrawPoint(true);
                it = disparos.erase(it);
                it2 = asteroides.erase(it2);
                // std::cout << "Asteroide atingido" << std::endl;
            }
            else
            {
                ++it2;
            }
        }
        if (it != disparos.end())
        {
            ++it;
        }
    }
}

void asteroideColidePlaneta(std::vector<spc::asteroide *> &asteroides, spc::planeta *planetaTerra)
{
    for (auto it = asteroides.begin(); it != asteroides.end();)
    {
        if (it[0]->isColliding(planetaTerra->getPosition(), planetaTerra->getRadius()))
        {
            it[0]->setDrawPoint(true);
            it = asteroides.erase(it);
            // std::cout << "Planeta Terra atingido" << std::endl;
        }
        else
        {
            ++it;
        }
    }
}


