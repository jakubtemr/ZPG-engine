// Camera.cpp
#include "Camera.h"

Camera::Camera() : eye(0.0f, 0.0f, 3.0f), up(0.0f, 1.0f, 0.0f), alpha(1.0f), fi(1.0f) {
    updateTarget();
}

glm::mat4 Camera::getCamera() {
    return glm::lookAt(eye, eye + target, up);
   /*return glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f));/**/
}

void Camera::updateTarget() {
    target.x = sin(alpha) * cos(fi);
    target.z = sin(alpha) * sin(fi);
    target.y = cos(alpha);
}

void Camera::rotate(float dAlpha, float dFi) {
    alpha += dAlpha;
    fi += dFi;
    if (alpha > 1.5f) alpha = 1.5f;
    if (alpha < -1.5f) alpha = -1.5f;
    updateTarget();
}
