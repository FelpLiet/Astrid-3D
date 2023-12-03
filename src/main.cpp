#include "../include/window.hpp"

spc::espaco *espaco = nullptr;
spc::planeta *planetaTerra = nullptr;
spc::sol *sol = nullptr;
spc::camera *camera = nullptr;

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Astrid");
    glutSetOption(GLUT_MULTISAMPLE, 8);

    glutDisplayFunc(drawScene);
    glutKeyboardFunc(input);
    glutReshapeFunc(resize_callback);
    glutPassiveMotionFunc(mouseMotion);
    glutMouseFunc(mouseButton);
    glutTimerFunc(0, timerUpdate, 0);

    espaco = new spc::espaco(50.0f, "assets/espaco.jpg");
    planetaTerra = new spc::planeta(glm::vec3(10.0f, 0.0f, -10.0f), 5.0f, "assets/earth.jpg");
    sol = new spc::sol(glm::vec3(10.0f, 10.0f, 20.0f), 0.5f, "assets/sun.jpg");
    camera = new spc::camera();

    glutMainLoop();

    return 0;
}