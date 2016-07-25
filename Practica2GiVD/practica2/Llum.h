#ifndef LLUM_H
#define LLUM_H
#include "Ray.h"

class Llum {

    public:
        Llum(int l);
        glm::vec3 position;
        glm::vec3 direction;
        float angle;
        glm::vec3 ambient;
        glm::vec3 specular;
        glm::vec3 diffuse;

        float a, b, c;
        int id;

};

#endif // LLUM_H
