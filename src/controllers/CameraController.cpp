//
// Created by João Fernandes on 20/05/2024.
//

#include "CameraController.h"

#include "../app/Application.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../utils/MathUtil.hpp"

CameraController::CameraController(ApplicationPtr application) {
    this->application = application;
    this->zoom = 10.f;
}

bool CameraController::initialize(const glm::vec3& position, float fov) {
    this->updateFOV(fov);
    this->position = position;
    this->target = glm::vec3(0.f);
    this->setAngle(0.f);
    return true;
}

glm::mat4 CameraController::translate(const glm::vec3& position, const glm::vec3& orientation) const {
    glm::mat4 modelTranslated = glm::translate(this->model, position);

    modelTranslated = glm::rotate(modelTranslated, glm::radians(orientation.x), glm::vec3(1.f, 0.f, 0.f));
    modelTranslated = glm::rotate(modelTranslated, glm::radians(orientation.y), glm::vec3(0.f, 1.f, 0.f));
    modelTranslated = glm::rotate(modelTranslated, glm::radians(orientation.z), glm::vec3(0.f, 0.f, 1.f));

    return this->projection * (this->view * this->zoom) * modelTranslated;
}

float CameraController::updateFOV(float fov) {
    if (fov < MIN_FOV && fov > MAX_FOV)
        return this->fov;

    float oldFOV = this->fov;
    this->fov = fov;

    this->projection = glm::perspective(glm::radians(this->fov), this->application->getAspectRatio(), .1f, 100.f);

    this->refresh();
    return oldFOV;
}

float CameraController::setAngle(float angle) {
    float oldAngle = this->angle;
    this->angle = NormalizeAngle(angle);

    // Rotations
    // https://www.songho.ca/opengl/files/gl_camera07.jpg
    // https://learnopengl.com/img/getting-started/camera_pitch_yaw_roll.png
    this->model = glm::rotate(this->model, glm::radians(this->angle), glm::normalize(glm::vec3(0.f, 1.f, 0.f)));

    this->refresh();
    return oldAngle;
}

float CameraController::updateAngle(float angle) {
    float newAngle = NormalizeAngle(this->angle + angle);
    this->setAngle(newAngle);
    return newAngle;
}

float CameraController::setZoom(float zoom) {
    float oldZoom = this->getZoom();
    this->zoom[0][0] = this->zoom[1][1] = this->zoom[2][2] = zoom;
    this->refresh();
    return oldZoom;
}

float CameraController::updateZoom(float zoom) {
    float newZoom = this->getZoom() + fabs(this->getZoom()) * zoom;
    this->setZoom(newZoom);
    return newZoom;
}

void CameraController::refresh() {
    this->view = glm::lookAt(this->position, target, glm::vec3(0.f, 1.f, 0.f));
    this->mvp = this->projection * this->view * this->model;
}
