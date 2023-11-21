#include "../include/window.hpp"

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Astrid");

    glutDisplayFunc(drawScene);
    glutIdleFunc(update);
    glutKeyboardFunc(input);
    glutReshapeFunc(resize_callback);
    // glutPassiveMotionFunc(mouse_callback);
    // glutMouseFunc(mouse_button_callback);

    glutMainLoop();

    return 0;
}