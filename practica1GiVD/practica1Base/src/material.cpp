#include "material.h"

Material::Material(point3 ambient, point3 diffuse, point3 specular, float shininess) {
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->shininess = shininess;
}


void Material::toGPU(QGLShaderProgram *program){
    gl_IdMaterial mat;

    mat.ambient = program->uniformLocation("material.ambient");
    mat.diffuse = program->uniformLocation("material.diffuse");
    mat.specular = program->uniformLocation("material.specular");
    mat.shininess = program->uniformLocation("material.shininess");

    glUniform3fv(mat.ambient, 1, this->ambient);
    glUniform3fv(mat.specular, 1, this->specular);
    glUniform3fv(mat.diffuse, 1, this->diffuse);
    glUniform1f(mat.shininess, this->shininess);
}
Material::~Material(){

}
