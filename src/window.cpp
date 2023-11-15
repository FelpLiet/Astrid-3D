#include "../include/window.hpp"

#define TARGET_FPS 60

spc::planeta newPlaneta(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(3.0f, 3.0f, 3.0f));
spc::camera camera(glm::vec3(0.0f, 0.0f, 5.0f));

GLFWwindow *window;
GLFWmonitor *monitor;

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

    window = glfwCreateWindow(WIDTH, HEIGHT, "ASTRID-3D", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Erro ao criar a janela GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetCursorPosCallback(window, mouse_callback);
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


    // Set up the view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    camera.lookAt();


    newPlaneta.draw();


    glfwSwapBuffers(window);
}

void runAstrid()
{
    initWindow();
    newPlaneta.loadTexture("assets/wesley.jpg");

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
   
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        camera.setCursorMode(window, GLFW_CURSOR_DISABLED);
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    static double lastX = 0.0, lastY = 0.0;
    static bool firstMouse = true;

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    double xoffset = xpos - lastX;
    double yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    camera.rotate(xoffset, yoffset);
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