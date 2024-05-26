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
    this->updatePosition(position);
    this->setAngle(0.f);
    return true;
}

void CameraController::updatePosition(const glm::vec3& position, const glm::vec3& target) {
    this->view = glm::lookAt(this->position = position, this->target = target, glm::vec3(0.f, 1.f, 0.f));
    this->refresh();
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
    this->model = glm::rotate(glm::mat4{ 1.f }, glm::radians(this->angle), glm::normalize(glm::vec3(0.f, 1.f, 0.f)));

    this->refresh();
    return oldAngle;
}

float CameraController::updateAngle(float angle) {
    float newAngle = NormalizeAngle(this->angle + angle);
    this->setAngle(newAngle);
    return newAngle;
}

float CameraController::setZoom(float zoom) {
    float oldZoom = this->getZoomValue();
    this->zoom[0][0] = this->zoom[1][1] = this->zoom[2][2] = zoom;
    this->refresh();
    return oldZoom;
}

float CameraController::updateZoom(float zoom) {
    float newZoom = this->getZoomValue() + fabs(this->getZoomValue()) * zoom;
    this->setZoom(newZoom);
    return newZoom;
}

void CameraController::refresh() {
    this->mvp = this->projection * this->view * this->model;
}
