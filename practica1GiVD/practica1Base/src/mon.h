#ifndef ESCENA_H
#define ESCENA_H

#include <cmath>
#include <iostream>
#include <stdlib.h>

#include <list>
#include <vector>
#include <string>
#include <stdio.h>

#include <Common.h>
#include <objecte.h>
#include <llum.h>
#include <QGLShaderProgram>

using namespace std;

// Virtual World: contains all objects, lights to visualize the scene
// the viewer is placed in the z+ axis and the  visible frustum is enclosed to (-1,-1,-1) to (1,1,1)



class Mon {

public:
    Mon();
    ~Mon();

    void addObjecte(Objecte *obj);


    void draw();

    void addLlum(Llum *l);
    Llum *getLlumActual();
    void llumsToGPU(QGLShaderProgram *program);
    void setAmbientToGPU(QGLShaderProgram *program);
    void setLlum(int id);
    void switchOnOffLlumActual(QGLShaderProgram *program);
    void setTextureToGPU(QGLShaderProgram *program, bool textureOn);

    vector <Objecte*> elements;
    vector<Llum*> llums;
    vec3 ambientGlobal;
    int idLlum;

    GLuint ambGlobal;
};

#endif // ESCENA_H
