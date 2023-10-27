// Camera.h
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
private:
    
    float alpha;
    float fi;

public:
    Camera();
    glm::mat4 getCamera();
    void updateTarget();
    void rotate(float dAlpha, float dFi);
    glm::vec3 eye;
    glm::vec3 target;
    glm::vec3 up;
};
