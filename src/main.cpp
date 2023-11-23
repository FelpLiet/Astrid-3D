#include "../include/window.hpp"

spc::espaco* espaco = nullptr;
spc::planeta* planetaTerra = nullptr;

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Astrid");

    glutDisplayFunc(drawScene);
    glutKeyboardFunc(input);
    glutReshapeFunc(resize_callback);
    glutPassiveMotionFunc(mouseMotion);
    glutTimerFunc(0, update, 0);

    espaco = new spc::espaco(50.0f, "assets/espaco.png");
    planetaTerra = new spc::planeta(glm::vec3(10.0f, 0.0f, -10.0f), glm::vec3(5.0f, 5.0f, 5.0f), "assets/terra.png");

    glutMainLoop();

    return 0;
}