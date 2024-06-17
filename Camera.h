// Camera.h
#pragma once
#define _USE_MATH_DEFINES
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "CameraObservable.h"
#include "ShaderApp.h"
#include <vector>
#include <iostream>
#include <cmath>

class ShaderApp;
class Camera : public CameraObservable
{
private:
    glm::vec3 eye;
    glm::vec3 target;
    glm::vec3 up;
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 300.0f);
    float alpha= 0.f;
    float fi=4.7f;
    float pos_x = 0.f;
    float pos_y = 0.f;
    float width;
    float height;

    float rotateSpeed = 0.2f;
    float moveSpeed = 0.2f;

    bool mouseMoveEnable = false;
    int frontMove = 0;
    int sideMove = 0;
    void updateProjectionMatrix();
    std::vector<CameraObserver*> cameraObservers;
public:
    glm::vec3 getCameraPos();
    Camera(glm::vec3 eye, glm::vec3 target, glm::vec3 up);
    glm::mat4 getCamera();
    glm::mat4 getProjectionMatrix();
    void updateAngle(float dtx, float dty);
    void setAngles();
    void setMouseMoveState(bool state);
    void setFrontMoveState(int state);
    void setSideMoveState(int state);
    void setMousePos(int mouseX, int mouseY);
    void toFront();
    void toBack();
    void toRight();
    void toLeft();
    void update();
    void setAspectRatio(float width, float height);
    void addCameraObserver(CameraObserver* observer) override;
    void removeCameraObserver(CameraObserver* observer) override;
    void notifyCameraObservers() override;
};
