#include "mon.h"

Mon::Mon() {
   /* QString name = "llum_1";
    point4 position = vec4(0, 0, -50, 50);
    point4 direction = vec4(0, 0, 50, 0);
    GLfloat angle = 0.57f;
    //intensidad
    point3 ambient= vec3(1.0f, 0.0f, 0.0f);
    point3 specular= vec3(0.9f);
    point3 diffuse= vec3(0.9f);
    GLfloat a, b, c;
    a = 0.0f;
    b = 0.0f;
    c = 1.0f;
    this->addLlum(new Llum(Puntual));
    */
    ambientGlobal = vec3(0.2, 0.2, 0.2);
    //this->addLlum(new Llum(name,position, direction, angle, a, b, c, ambient, specular, diffuse));
}

Mon::~Mon() {
    elements.clear();

}

void Mon::addObjecte(Objecte *obj) {
    elements.push_back(obj);
}

void Mon::draw() {
    for(unsigned int i=0; i < elements.size(); i++){
        elements.at(i)->draw();
    }
}

Llum* Mon::getLlumActual() {
    return (llums[idLlum]);
}

void Mon::setLlum(int id){
    idLlum = id;
}

void Mon::llumsToGPU(QGLShaderProgram *program){
    int numLlums = llums.size();
    for(int i = 0; i < numLlums; ++i){
        llums[i]->toGPU(program);
    }
}

void Mon::switchOnOffLlumActual(QGLShaderProgram *program){
    llums[idLlum]->switchOnOff(program, idLlum+1);

}

void Mon::addLlum(Llum *l) {
    llums.push_back(l);

}

void Mon::setAmbientToGPU(QGLShaderProgram *program){
    ambGlobal = program->uniformLocation("ambientGlobal");
    glUniform3fv(ambGlobal, 1, ambientGlobal);
}
void Mon::setTextureToGPU(QGLShaderProgram *program, bool textureOnOff){
    GLuint textureOn = program->uniformLocation("textureOn");
    glUniform1i(textureOn, textureOnOff);
}
