#pragma once

#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include <chrono>
#include "camera.hpp"
#include "espaco.hpp"
#include "asteroide.hpp"
#include "disparo.hpp"

#define WIDTH 1366
#define HEIGHT 768
#define FPS 60

void drawScene();
void update(int);
void input(unsigned char key, int x, int y);
// void mouse_button_callback(int button, int state, int x, int y);
// void mouse_callback(int x, int y);
void resize_callback(int x, int y);
void mouseMotion(int x, int y);
void mouseButton(int button, int state, int x, int y);
void disparar();