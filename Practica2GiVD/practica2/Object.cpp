#include "Object.h"

Material::Material():
    ambient(0.3f),
    diffuse(0.3),
    specular(1.0f),
    shininess(20.0f)
  {}
Material::Material(glm::vec3 ambient,
glm::vec3 diffuse,
glm::vec3 specular,
float shininess){
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->shininess = shininess;
}
Object::Object(const glm::mat4 &transform, const Material &material):
    transform(transform),material(material){}

Sphere::Sphere(glm::vec3 center, float radius,Materiales &material){
        this->center = center;
        this->radius = radius;
        this->material.ambient = material.ambient;
        this->material.diffuse = material.diffuse;
        this->material.specular = material.specular;
        this->material.shininess = material.shineness;
}
Plane::Plane(glm::vec3 vNormal, float d,Materiales &material){
    this->vNormal = vNormal;
    this->d = d;
    this->material.ambient = material.ambient;
    this->material.diffuse = material.diffuse;
    this->material.specular = material.specular;
    this->material.shininess = material.shineness;
}

/* TODO: Implementar en el punt 2 */

bool Sphere::Intersect(const Ray &ray, IntersectInfo &info) const {

    float a = glm::dot(ray.direction, ray.direction);
    float b = glm::dot((ray.origin - center), ray.direction) * 2.0f;
    float c = glm::dot(ray.origin - center, ray.origin - center) - pow(radius,2.0f);
    float d0,d1;

    float discr = pow(b,2.0f) - (4.0f * a * c); //La parte de dentro de la raiz cuadrada

    if (discr < 0.0f) return false; // No hay solucion, ni interseccion

    else{
        d0 = (-b + sqrt(discr)) / (2*a);
        d1 = (-b - sqrt(discr)) / (2*a);

        if ((d0 >= 0 && d0 <= 1) || (d1 >= 0 && d1 <= 1)){ // Minimo tendremos una solucion

        float min = glm::min(d0,d1);

        if(d0>0 && (fabs(d0-min)<0.0001)){ //comprobamos cual es el menor positivo y actualizamos
            info.hitPoint = ray.origin + d0 * ray.direction;
            info.normal = glm::normalize(info.hitPoint - center);
            info.time = d0;
            info.material = &this->material;
        }
        else if(d1>0 && (fabs(d1-min)<0.0001)){
            info.hitPoint = ray.origin + d1 * ray.direction;
            info.normal = glm::normalize(info.hitPoint - center);
            info.time = d1;
            info.material = &this->material;
        }
        return true;
    }
    }
     return false;
}
/* TODO: Implementar en el punt 2 */
bool Plane::Intersect(const Ray &ray, IntersectInfo &info) const {

    float disc = glm::dot(vNormal,ray.direction);
    float d0 = -(glm::dot(vNormal,ray.origin)+d)/disc;
    if(fabs(disc) < 0.001) return false;
    if(d0 >= 0.0f && d0<1){
        info.hitPoint = ray.origin+ray.direction*d0;
        info.normal = vNormal;
        info.time = d0;
        info.material = &this->material;
        return true;
    }
    return false;
}

/* TODO: Implementar com a extensio */
bool Triangle::Intersect(const Ray &ray, IntersectInfo &info) const { return -1.0f; }
