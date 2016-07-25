#ifndef RayTracer_h

#define RayTracer_h

#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>

#include <GL/glut.h> //OpenGL Utility Toolkits

#include "Scene.h"

Scene *scene;
glm::vec4 p1;
glm::vec4 p2;

void Render();

#endif

