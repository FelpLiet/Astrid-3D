#include "../include/window.hpp"

// spc::nave ship;
// spc::space space;
// spc::asteroide asteroide1;
#define TARGET_FPS 60

GLFWwindow *window;
GLFWmonitor *monitor;

// std::vector<spc::disparo> disparos;
std::map<int, key> keyMap;

bool running = true, fullscreen;
int WIDTH = 1366, HEIGHT = 768;

int initWindow()
{
    if (!glfwInit())
    {
        std::cerr << "Erro ao inicializar o GLFW" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "ASTRID", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Erro ao criar a janela GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSetMouseButtonCallback(window, mouse_button_callback);

    monitor = glfwGetPrimaryMonitor();
    running = true;
    fullscreen = false;

    // Inicializa GLEW
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Erro ao inicializar o GLEW" << std::endl;
        return -1;
    }

    return 0;
}

void input(GLFWwindow *window)
{
    glfwPollEvents();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        running = false;
        glfwWindowShouldClose(window);
    }

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && keyMap[GLFW_KEY_F].prev)
    {
        glfwWaitEventsTimeout(0.7);
        if (!fullscreen)
            glfwSetWindowMonitor(window, monitor, 0, 0, WIDTH, HEIGHT, 0);
        if (fullscreen)
            glfwSetWindowMonitor(window, NULL, 0, 0, WIDTH, HEIGHT, 0);
        fullscreen = !fullscreen;
    }
    keyMap[GLFW_KEY_F].prev = glfwGetKey(window, GLFW_KEY_F);
}

void drawScene(GLFWwindow *window)
{
    aspecRatio(window);

    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-0.5f, -0.5f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(0.5f, -0.5f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(0.0f, 0.5f);
    glEnd();

    // ship.draw();

    // space.drawEstrelas();

    // space.getTerra().draw();

    // spc::drawDisparos(disparos, window);

    // asteroide1.draw_asteroide();
    // asteroide1.draw_lines(); // desenha as linhas de trajetoria do asteroide

    glfwSwapBuffers(window);
}

void runAstrid()
{
    initWindow();
    double lasttime = glfwGetTime();
    while (running && !glfwWindowShouldClose(window))
    {
        while (glfwGetTime() < lasttime + 1.0 / TARGET_FPS)
        {
            // TODO: Put the thread to sleep, yield, or simply do nothing
        }
        lasttime += 1.0 / TARGET_FPS;
        input(window);
        update(window);
        drawScene(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

void update(GLFWwindow *window)
{
    // asteroide1.calculo_trajetoria(window);
    // spc::verificaDisparos(disparos);
    // ship.updatePosition(window);
    // if (isAsteroideInsideDisparo(asteroide1, disparos))
    // {
    //     std::cout << "Na mosca!" << std::endl;
    //     asteroide1.reset();
    // }
    // if (isAsteroideInsideTerra(asteroide1, space))
    // {
    //     std::cout << "Cuidado!!" << std::endl;
    //     asteroide1.reset();
    // }
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        GLdouble modelview[16], projection[16];
        GLint viewport[4];

        // This code retrieves the current modelview, projection, and viewport matrices
        // from OpenGL and stores them in the modelview, projection, and viewport arrays.
        glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
        glGetDoublev(GL_PROJECTION_MATRIX, projection);
        glGetIntegerv(GL_VIEWPORT, viewport);

        // This code uses gluUnProject to convert the mouse click coordinates from
        // screen space to world space. The xpos and ypos parameters are the screen
        // coordinates of the mouse click, while the modelview, projection, and viewport
        // parameters are the matrices retrieved in the previous lines. The resulting
        // world coordinates are stored in the worldX, worldY, and worldZ variables
        // GLdouble worldX, worldY, worldZ;
        // gluUnProject(xpos, viewport[3] - ypos, 0.0, modelview, projection, viewport, &worldX, &worldY, &worldZ);
        // glm::vec2 centerXY(worldX, worldY);
        // spc::disparo newDisparo(centerXY, std::chrono::steady_clock::now());
        // std::cout << "x: " << worldX << " y: " << worldY << std::endl;
        // disparos.push_back(newDisparo);
    }
}

void aspecRatio(GLFWwindow *window)
{
    // Set up the viewport
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // Set up the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspectRatio = (float)width / (float)height;
    float size = 10.0f;
    if (aspectRatio > 1.0f)
    {
        glOrtho(-size * aspectRatio, size * aspectRatio, -size, size, -1.0f, 1.0f);
    }
    else
    {
        glOrtho(-size, size, -size / aspectRatio, size / aspectRatio, -1.0f, 1.0f);
    }

    // Switch back to the modelview matrix
    glMatrixMode(GL_MODELVIEW);
}

// bool isAsteroideInsideDisparo(spc::asteroide &asteroide, std::vector<spc::disparo> &disparos)
// {
//     glm::vec2 centerXY(asteroide.getX(), asteroide.getY());
//     for (auto disparo : disparos)
//     {
//         float distance = glm::length(centerXY - disparo.getCenter());
//         if (distance < disparo.getRadius())
//             return true;
//     }
//     return false;
// }

// bool isAsteroideInsideTerra(spc::asteroide &asteroide, spc::space &space)
// {
//     glm::vec2 centerXY(asteroide.getX(), asteroide.getY());

//     float distance = glm::length(centerXY - space.getTerra().getCenter());
//     if (distance < space.getTerra().getRadius())
//         return true;

//     return false;
// }