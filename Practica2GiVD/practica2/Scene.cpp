#include "Scene.h"

Scene::Scene()
{
    // Afegeix la camera a l'escena
    cam = new Camera();
    // TODO: Cal crear els objectes de l'escena (punt 2 de l'enunciat)
    materials.push_back(new Materiales(glm::vec3(0.2125f,0.1275f,0.054f),glm::vec3(0.714f,0.4284f,0.18144f),glm::vec3(0.393548f,0.271906f,0.166721f),0.2f));
    materials.push_back(new Materiales(glm::vec3(0.1f,	0.05f,0.1f),glm::vec3(0.4f,0.5f,0.4f),glm::vec3(0.5f,0.0f,0.2f),20.0f));
    materials.push_back(new Materiales(glm::vec3(0.19225f,0.19225f,0.19225f),glm::vec3(0.4f,0.4f,0.4f),glm::vec3(0.774597f,0.774597f,0.774597f),0.6f));
    materials.push_back(new Materiales(glm::vec3(0.02f,0.02f,0.02f),glm::vec3(0.01f,0.01f,0.01f),glm::vec3(0.4f,0.4f,0.4f),0.078125f));
    materials.push_back(new Materiales(glm::vec3(0.0f,0.05f,0.0f),glm::vec3(0.4f,0.5f,0.4f),glm::vec3(0.0f,0.0f,0.0f),20.0f));
    materials.push_back(new Materiales(glm::vec3(0.3f,0.0f,0.0f),glm::vec3(0.7f,0.0f,0.0f),glm::vec3(0.0f,0.0f,0.0f),2.0f));
    materials.push_back(new Materiales(glm::vec3(0.0f,0.0f,0.3f),glm::vec3(0.0f,0.0f,0.7f),glm::vec3(0.0f,0.0f,0.0f),2.0f));

    objects.push_back(new Sphere(glm::vec3(-5.0f, 2.4f, 5.0f), 1.0f,*materials[5]));

    //Escondemos una bola azul detras de la roja para comprobar que en las reflexiones nos aparece.

    objects.push_back(new Sphere(glm::vec3(-8.0f,2.0f, 1.0f), 1.0f,*materials[4]));
    objects.push_back(new Sphere(glm::vec3(-2.5f, 1.4f, 6.0f), 1.0f,*materials[5]));
    objects.push_back(new Sphere(glm::vec3(-2.5f, 0.4f, 2.3f), 1.0f,*materials[6]));
    objects.push_back(new Sphere(glm::vec3(-5.0f, 0.4f, 2.3f), 1.0f,*materials[6]));

    objects.push_back(new Plane(glm::vec3(0.0f,1.0f,0.0f), 0.8f,*materials[0]));
    objects.push_back(new Plane(glm::vec3(0.0f,0.0f,1.0f), 0.8f,*materials[3]));
    objects.push_back(new Plane(glm::vec3(1.0f,0.0f,0.0f), 0.8f,*materials[3]));




    llums.push_back(new Llum(0));

}

Scene::~Scene()
{
    delete cam;
    for(unsigned int i = 0; i < objects.size(); ++i){
        if(objects[i]) {
            delete objects[i];
        }
    }
}


/*
** TODO: Metode que testeja la interseccio contra tots els objectes de l'escena
**
** Si un objecte es intersecat pel raig, el parametre  de tipus IntersectInfo conte
** la informació sobre la interesccio.
** El metode retorna true si algun objecte es intersecat o false en cas contrari.
**
*/

bool Scene::CheckIntersection(const Ray &ray, IntersectInfo &info) {
    IntersectInfo inform = info;
    bool salida = false;
   for(int i=0;i<objects.size();i++){
        if(objects[i]->Intersect(ray,info)){
             if(info.time <inform.time){
                 inform = info;
             }
             salida = true;
             info = inform;
        }
    }
    return salida;
    // TODO: Heu de codificar la vostra solucio per aquest metode substituint el 'return true'
    // Una possible solucio es cridar Intersect per a tots els objectes i quedar-se amb la interseccio
    // mes propera a l'observador, en el cas que n'hi hagi més d'una.
    // Cada vegada que s'intersecta un objecte s'ha d'actualitzar el PayLoad del raig,
    // pero no en aquesta funcio. Per això es posa const en el paràmetre ray, per a
    // que no es canvïi aqui.
}
/*
** TODO: Funcio recursiva del RayTracing.
** A modificar en el punt 4 de l'enunciat per incloure Blinn-Phong  i ombres
** A modificar en el punt 5 per a tractar reflexions
**
** Aquest metode es crida per a cada pixel, i cada cop que es calculen ombres o reflexions
** El paràmetre PayLoad es pot usar per a guardar informacio de sobre el quin es color actual del raig i el nombre de
** rebots que s'han fet.
** Aquest metode retorna el delta del raig (o t) en el cas que hi hagi interseccio o
** -1 si no hi ha interseccio amb cap objecte.
*/
//	La funcio CastRay ha de calcular la il·luminacio,
//  les ombres i les reflexions.


glm::vec3 Scene::CastRay(Ray &ray, Payload &payload) {

    IntersectInfo info;

    if (CheckIntersection(ray,info)) {
        /* TODO: Canviar aquesta assignacio pel color basat amb la il.luminacio basada amb Phong-Blinn segons
         * el material de l'objecte i les llums per l'apartat 4 de la practica
         * I per l'apartat 5, cal fer que tambe es tinguin en compte els rebots de les reflexions.

           Inicialment s'ha posat la direccio del raig per tenir un color diferents per a cada pixel pero
           payload ha d'anar tenint el color actualitzat segons els rebots.
        */

        payload.color = Shade(info);
        if(payload.numBounces < 1){
            Payload paycolor;
            payload.numBounces ++;
            paycolor.numBounces = payload.numBounces;
            glm::vec3 r = (-2.0f*glm::dot(info.normal,ray.direction) *info.normal) + ray.direction;
            Ray rebote(info.hitPoint+0.000001f*r,r);
            payload.color += info.material->specular * CastRay(rebote,paycolor);
        }

    }
    else{
        payload.color = ambientGlobal;
        // Si el ray des de la camera no intersecta amb cap objecte
        // no s'ha de veure res, encara que també es podria posar el color de la Intensita ambien global
    }
     return payload.color;
}

glm::vec3 Scene::calculaAmbiental(int x,IntersectInfo &info){
    glm::vec3 amb = llums[x]->ambient * info.material->ambient;
    return glm::vec3(amb);

}

glm::vec3 Scene::calculaDiffuse(int x,IntersectInfo &info){
    glm::vec3 dif = llums[x]->diffuse *  info.material->diffuse;
    return glm::vec3(dif);
}

glm::vec3 Scene::calculaSpecular(int x,IntersectInfo &info){
    glm::vec3 spe = llums[x]->specular * info.material->specular;
    return glm::vec3(spe);
}

glm::vec3 Scene::calulBlinPhong(IntersectInfo &info){
    int x = 0;
    glm::vec3 amb = calculaAmbiental(x,info);
    glm::vec3 dif = calculaDiffuse(x,info);
    glm::vec3 spe = calculaSpecular(x,info);
    float atenuacion;
    glm::vec3 L ;

    L = glm::normalize(glm::vec3(llums[x]->position) - info.hitPoint);
    float d = glm::length(glm::vec3(llums[x]->position) - info.hitPoint);
    glm:: vec3 V = glm::normalize(cam->obs - info.hitPoint);
    glm::vec3 H = glm::normalize(V+L);
    atenuacion = 1.0 / (llums[x]->a* pow(d,2) + llums[x]->b*d + llums[x]->c);
    float matSpec =  pow(glm::max(glm::dot(info.normal,H),0.0f), info.material->shininess);
    glm::vec3 I = atenuacion *( dif * glm::max(glm::dot(L,info.normal),0.0f)  + spe * matSpec + amb);

    return glm::vec3(I);
}

glm::vec3 Scene::Shade(IntersectInfo &info){
   glm::vec3 color = ambientGlobal * info.material->ambient;
   glm::vec3 L =llums[0]->position - info.hitPoint;
   glm::vec3 origin = info.hitPoint + 0.0001f * L;
   Ray newRay(origin,L);
   if(!CheckIntersection(newRay,info)){
      color += calulBlinPhong(info);
   }
   return color;
}
