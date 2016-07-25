#include "RayTracer.h"

// Metode per netejar la memòria

void cleanup() {
    delete scene;
}

//Para pasar de coordenadas de window a coordenadas de mon necesitamos multiplicar las dos coordenadas
//de windows por la inversa de la matriz projection para poder pasar a coordenadas de camara y multiplicar el resultado por la inversa
//de la matriz viewmatrix para conseguir pasar finalmente a coordenadas de mundo.

//Para agilizar hemos multiplicado la inversa de la matriz projection por la inversa de la matriz viewmatrix y con la matriz resultante
//hemos multiplicado las coordenadas de window obteniendo asi, coordenadas de mundo.

void Render()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Netejar la finestra OpenGL

    // TODO: Cridar a IniViewProjMatrices de la classe camera (punt 2 de l'enunciat)

     scene->cam->IniViewProjMatrices();
    glBegin(GL_POINTS);	//S'activa el mode GL_POINTS. En aquest mode
                        // cada vertex especificat és un punt.
                        //	Reference https://en.wikibooks.org/wiki/OpenGL_Programming/GLStart/Tut3 si us interessa.

    std::cout<<"observador:"<<scene->cam->obs.x<<","<<scene->cam->obs.y<<","<<scene->cam->obs.z<<std::endl;
    // Recorregut de cada pixel de la imatge final

    scene->cam->projMatrix = glm::inverse(scene->cam->projMatrix);
    scene->cam->viewMatrix = glm::inverse(scene->cam->viewMatrix);

    glm::mat4 monMatrix = scene->cam->viewMatrix*scene->cam->projMatrix;

    for(int x = 0; x < scene->cam->viewportX; ++x)
        for(int y = 0; y < scene->cam->viewportY; ++y){
            float pixelX =  2*((x+0.5f)/scene->cam->viewportX)-1;
            float pixelY = -2*((y+0.5f)/scene->cam->viewportY)+1;

            glm::vec4 p1 = glm::vec4(pixelX,pixelY,-1.0f,1.0f); //zfar
            glm::vec4 p2 =  glm::vec4(pixelX,pixelY,1.0f,1.0f); //znear

            p1 = monMatrix*p1;
            p2 = monMatrix*p2;

            glm::vec3 p3 =  glm::vec3(p1[0]/p1[3],p1[1]/p1[3],p1[2]/p1[3]);
            glm::vec3 p4 =  glm::vec3(p2[0]/p2[3],p2[1]/p2[3],p2[2]/p2[3]);



            glm::vec3 direction = p4-p3;
            //glm::vec3 direction = glm::normalize(glm::vec3(pixelPosWorld-scene->cam->obs));
            Payload payload;
            // Creacio del raig
            // HELP: Ray(const glm::vec3 &origin, const glm::vec3 &direction)
            Ray ray(p3, direction) ;

            glm::vec3 color = scene->CastRay(ray,payload);
            glColor3f(color.x,color.y,color.z);
            glVertex3f(pixelX,pixelY,0.0f);
        }

    glEnd();
    glFlush();
}


// Metode principal del programa

int main(int argc, char **argv) {

    // inicialitza l'escena: el constructor de l'escena s'encarrega de
    // crear la camera, els objectes i les llums
    scene = new Scene();

    //inicialitza OpenGL
    glutInit(&argc, argv);
    //Define la mida de la window GL especificada per la mida del viewport
    glutInitWindowSize(scene->cam->viewportX, scene->cam->viewportY);

    //Creacio de la window per pintar amb GL
    glutCreateWindow("RayTracer");
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    //Posa la funcio Render per a que la window GL cridi quan es refresca
    glutDisplayFunc(Render);

    //	TODO: Afegir els objectes a l'escena
    //  TODO: Afegir les llums a l'escena

    atexit(cleanup);

    // Inicia el main loop per a poder refrescar l'escena
    glutMainLoop();

}
