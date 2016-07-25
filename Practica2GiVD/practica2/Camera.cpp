#include "Camera.h"

Camera::Camera():
    obs(glm::vec3(-10.0f,5.0f,10.0f)),
    vrp(glm::vec3(0.0f, 0.0f, 0.0f)),
    vup(glm::vec3(0.0f, 1.0f, 0.0f)),
    angleObertura(45.0f), zNear(1.0f), zFar(1000.0f),
    viewportX(640), viewportY(480),
    h(23.0f),w(30.0f)
{
}
Camera::Camera(const glm::vec3 &_obs,
               const glm::vec3 &_vrp,
               const glm::vec3 &_vup,
               float _angleObertura,
               float _w,
               float _h,
               float _zNear,
               float _zFar,
               int _viewportX,
               int _viewportY):
    obs(_obs), vrp(_vrp), vup(_vup),
    angleObertura(_angleObertura), zNear(_zNear), zFar(_zFar),
    viewportX(_viewportX), viewportY(_viewportY),h(_h),w(_w){
}

void Camera::IniViewProjMatrices()
{

    // Inicialització de les matrius viewMatrix i projMatrix
    //	Utilitzeu els metodes de lookAt i perspective
    //  que teniu a  glm.h

    this->angleObertura = 180.0f*(2.0f*glm::atan((h/2.0f)/glm::length(this->obs-this->vrp)))/M_PI;
    projMatrix= glm::perspective(this->angleObertura,(w/h),this->zNear,this->zFar);
    viewMatrix = glm::lookAt(this->obs,this->vrp,this->vup);


}
