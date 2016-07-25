#include "llum.h"

Llum::Llum(Lights t){

    switch(t) {
        case Puntual:
            name = "puntual";
            id = 0;
            type = t;
            position = vec4(2.0,2.0,2.0,1.0);
            direction = vec4(2.0,2.0,2.0,1.0);
            diffuse = vec3(0.8,0.8,0.8);
            ambient = vec3(0.2, 0.2, 0.2);
            specular = vec3(1.0,1.0,1.0);
            a = 0.0;
            b = 0.0;
            c = 1.0;
            on = true;
        break;

        case Direccional:
            name = "direccional";
            id = 1;
            type = t;

            direction = vec4(1.0,1.0,1.0,1.0);
            diffuse = vec3(0.8,0.8,0.8);
            ambient = vec3(0.2, 0.2, 0.2);
            specular = vec3(1.0,1.0,1.0);
            a = 0.0;
            b = 0.0;
            c = 1.0;
            on = true;
        break;

        case SpotLight:
            name = "spotlight";
            id = 2;
            type = t;
            position = vec4(2.0,2.0,2.0,1.0);
            direction = vec4(2.0,2.0,2.0,1.0);

            angle = 0.5f;
            diffuse = vec3(0.8,0.8,0.8);
            ambient = vec3(0.2, 0.2, 0.2);
            specular = vec3(1.0,1.0,1.0);
            a = 0.0;
            b = 0.0;
            c = 1.0;
            on = true;
        break;
      }

}

Llum::Llum(QString name, point4 position, point4 direction, GLfloat angle, GLfloat a, GLfloat b,
           GLfloat c, point3 ambient, point3 specular, point3 diffuse){
    this->name = name;
    this->position = position;
    this->direction = direction;
    this->angle = angle;
    this->a = a;
    this->b = b;
    this->c = c;
    this->diffuse = diffuse;
    this->specular = specular;
    this->ambient = ambient;
}

void Llum::setTipusLlum(Lights t) {
}


vec3 Llum::getDiffuseIntensity() {
    return(diffuse);
}

vec4 Llum::getLightPosition() {
    return(position);
}


void Llum::setDiffuseIntensity(vec3 i) {
   this->diffuse = i;
}

void Llum::setLightPosition(vec4 v) {
    position = v;
}

void Llum::switchOnOff(QGLShaderProgram *program, int llumActual) {
    on = !on;
    this->toGPU(program);

}
void Llum::toGPU(QGLShaderProgram *program){
    gl_IdLlum  luz[3];
    int llumActual = this->id;
    luz[llumActual].ambient = program->uniformLocation(QString("glLlums[%1].ambient").arg(llumActual));
    luz[llumActual].position = program->uniformLocation(QString("glLlums[%1].position").arg(llumActual));
    luz[llumActual].direction = program->uniformLocation(QString("glLlums[%1].direction").arg(llumActual));
    luz[llumActual].angle = program->uniformLocation(QString("glLlums[%1].angle").arg(llumActual));
    luz[llumActual].a = program->uniformLocation(QString("glLlums[%1].a").arg(llumActual));
    luz[llumActual].b = program->uniformLocation(QString("glLlums[%1].b").arg(llumActual));
    luz[llumActual].c = program->uniformLocation(QString("glLlums[%1].c").arg(llumActual));
    luz[llumActual].diffuse = program->uniformLocation(QString("glLlums[%1].diffuse").arg(llumActual));
    luz[llumActual].specular = program->uniformLocation(QString("glLlums[%1].specular").arg(llumActual));
    luz[llumActual].on = program->uniformLocation(QString("glLlums[%1].on").arg(llumActual));
    glUniform3fv(luz[llumActual].ambient, 1, this->ambient);
    glUniform4fv(luz[llumActual].position, 1, this->position);
    glUniform4fv(luz[llumActual].direction, 1, this->direction);
    glUniform1f(luz[llumActual].angle, this->angle);
    glUniform1f(luz[llumActual].a, this->a);
    glUniform1f(luz[llumActual].b, this->b);
    glUniform1f(luz[llumActual].c, this->c);
    glUniform3fv(luz[llumActual].ambient, 1, this->ambient);
    glUniform3fv(luz[llumActual].diffuse, 1, this->diffuse);
    glUniform3fv(luz[llumActual].specular, 1, this->specular);
    glUniform1i(luz[llumActual].on, this->on);


   }
