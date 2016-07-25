#ifndef LLUM_H
#define LLUM_H

#include <Common.h>
#include <QGLShaderProgram> //revisar

enum Lights {Puntual, Direccional, SpotLight};

struct gl_IdLlum{
    GLuint position;
    GLuint direction;
    GLuint ambient;
    GLuint specular;
    GLuint diffuse;
    GLuint angle;
    GLuint a, b, c;
    GLuint on;
};



class Llum {
    typedef Common::vec3 point3;
    typedef Common::vec4 point4;


    public:
        Llum(Lights l);
        QString name;
        point4 position;
        point4 direction;
        GLfloat angle;
        bool on;
        point3 ambient;
        point3 specular;
        point3 diffuse;

        GLfloat a, b, c;


        int type;
        int id;


        Llum(QString name, point4 position, point4 dir, GLfloat angle, GLfloat a, GLfloat b,
                   GLfloat c, point3 ambient, point3 specular, point3 diffuse);
        void setTipusLlum(Lights t);
        vec3 getDiffuseIntensity();
        vec4 getLightPosition();
        void setDiffuseIntensity(vec3 i);
        void setLightPosition(vec4 v);
        void switchOnOff(QGLShaderProgram *program, int llumActual);
        void toGPU(QGLShaderProgram *program);
};

#endif // LLUM_H
