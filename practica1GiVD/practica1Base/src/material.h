#ifndef MATERIAL_H
#define MATERIAL_H
#include <Common.h>
#include <QGLShaderProgram>

struct gl_IdMaterial{
    GLuint ambient;
    GLuint diffuse;
    GLuint specular;
    GLuint shininess;
};

class Material {
    typedef Common::vec3 point3;

    public:
        Material(point3 ambient, point3 diffuse, point3 specular, float shininess);
        ~Material();
        point3 ambient;
        point3 diffuse;
        point3 specular;
        float shininess;
        void toGPU(QGLShaderProgram *program);
};

#endif // MATERIAL_H
