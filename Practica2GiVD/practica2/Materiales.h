#ifndef MATERIAL_H
#define MATERIAL_H
#include "Ray.h"

class Materiales
{
public:
    //material();
    Materiales(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shineness;
};

#endif // MATERIAL_H
