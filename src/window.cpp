#include "../include/window.hpp"

bool running = true, fullscreen;

void input(unsigned char key, int x, int y)
{
    switch (key)
    {
    // case GLUT_KEY_UP:
    //     camera.moveForward(0.1f);
    //     break;
    // case GLUT_KEY_DOWN:
    //     camera.moveForward(-0.1f);
    //     break;
    // case GLUT_KEY_LEFT:
    //     camera.moveRight(-0.1f);
    //     break;
    // case GLUT_KEY_RIGHT:
    //     camera.moveRight(0.1f);
    //     break;
    case 'F':
    case 'f':
        fullscreen = !fullscreen;
        if (fullscreen)
        {
            glutFullScreen();
        }
        else
        {
            glutReshapeWindow(WIDTH, HEIGHT);
            glutPositionWindow(100, 100);
        }
        break;
    case 27:
        exit(0);
        break;
    default:
        break;
    }
}


void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT);
    //grey background
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

    // gluLookAt(0.0f, 0.0f, 0.0f,
    //           0.0f, 0.0f, -5.0f,
    //           0.0f, 1.0f, 0.0f);
    // Draw a sphere
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -5.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glutWireSphere(1.0f, 20, 20);
    glPopMatrix();



    glutSwapBuffers();
}

void update()
{
    glutPostRedisplay();
}

void resize_callback(int x, int y)
{
if (y == 0 || x == 0)
      return;
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glViewport(0, 0, x, y); // renderiza en toda la ventana
}

