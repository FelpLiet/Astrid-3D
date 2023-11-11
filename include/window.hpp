#pragma once

#include "camera.hpp"
// #include "nave.hpp"
#include "espaco.hpp"
#include "asteroide.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <map>
#include <vector>
#include <chrono>

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
void aspecRatio(GLFWwindow *window);
// bool isAsteroideInsideDisparo(spc::asteroide &asteroide, std::vector<spc::disparo> &disparos);
// bool isAsteroideInsideTerra(spc::asteroide &asteroide, spc::space &space);