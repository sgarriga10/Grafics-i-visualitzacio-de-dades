#ifndef SCENE_H
#define SCENE_H

#include "Camera.h"
#include "Ray.h"
#include "Object.h"
#include "Llum.h"
#include "Materiales.h"
#include <vector> //Notice that vector in C++ is different from Vector2, Vector3 or similar things in a graphic library.

class Scene
{
public:
    Scene();
    ~Scene();

    bool  CheckIntersection(const Ray &ray, IntersectInfo &info);
    glm::vec3 CastRay(Ray &ray, Payload &payload);
    glm::vec3 calculaAmbiental(int x,IntersectInfo &info);
    glm::vec3 calculaDiffuse(int x,IntersectInfo &info);

    glm::vec3 calculaSpecular(int x,IntersectInfo &info);
    glm::vec3 calulBlinPhong(IntersectInfo &info);
    glm::vec3 ComputeColor(IntersectInfo &info);
    /*
    ** std::vector d'objectes continguts a l'escena
    */
    std::vector<Object*> objects;
    std::vector<Llum*> llums;
    std::vector<Materiales*> materials;
    IntersectInfo inform;
    glm::vec3 Shade(IntersectInfo &info);
    glm::vec3 ambientGlobal=glm::vec3(0.3f,0.3f,0.3f);
    /*
     * camera de l'escena
     */
    Camera *cam;
    /*
     * TODO: Cal afegir el conjunt de llums de l'escena
     */

};

#endif // SCENE_H
