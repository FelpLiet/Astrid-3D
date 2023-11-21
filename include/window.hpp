#pragma once

#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <iostream>
#include <map>
#include <vector>
#include <chrono>
#include "camera.hpp"
#include "espaco.hpp"
#include "asteroide.hpp"

#define WIDTH 1366
#define HEIGHT 768

void runAstrid();
void input(unsigned char key, int x, int y);
void drawScene();
//void reshapeWindow(GLFWwindow *window, int width, int height);
void update();
void mouse_button_callback(int button, int state, int x, int y);
void mouse_callback(int x, int y);
void resize_callback(int x, int y);
