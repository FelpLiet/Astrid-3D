#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <map>
#include <vector>
#include <chrono>
#include "camera.hpp"
#include "espaco.hpp"
#include "asteroide.hpp"

struct key
{
    bool curr;
    bool prev;
};

int initWindow();
void runAstrid();
void input(GLFWwindow *window);
void drawScene(GLFWwindow *window);
//void reshapeWindow(GLFWwindow *window, int width, int height);
void update(GLFWwindow *window);
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void aspecRatio(GLFWwindow *window);
