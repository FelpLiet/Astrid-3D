#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include <chrono>
#include "camera.hpp"
#include "espaco.hpp"
#include "disparo.hpp"
#include "asteroide.hpp"
#include "animacao.hpp"
#include "shader.hpp"

#define WIDTH 1366
#define HEIGHT 768
#define FPS 60

void drawScene();
void timerUpdate(int);
void createAsteroid(int);
void timerExplosao(int);
void mouseMotion(int x, int y);
void mouseButton(int button, int state, int x, int y);
void resize_callback(int x, int y);
void input(unsigned char key, int x, int y);
void disparoColideAsteroide(std::vector<spc::disparo> &disparos, std::vector<spc::asteroide *> &asteroides);
void asteroideColidePlaneta(std::vector<spc::asteroide *> &asteroides, spc::planeta *planetaTerra);