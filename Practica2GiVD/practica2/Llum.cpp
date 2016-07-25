#include "Llum.h"

Llum::Llum(int t){
    //Dejamos prepado el switch por si nos da tiempo implementar mas luces.
    switch(t) {
        case 0:
            //name = "puntual";
            id = 0;
            position = glm::vec3(-10.0f,10.0f,10.0f);
            diffuse = glm::vec3(0.9f,0.9f,0.9f);
            ambient = glm::vec3(0.3f, 0.3f,0.3f);
            specular = glm::vec3(1.0f,1.0f,1.0f);
            a = 0.0f;
            b = 0.0f;
            c = 0.8f;
      }
}
