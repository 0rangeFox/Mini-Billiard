//
// Created by João Fernandes on 20/05/2024.
//

#include "CameraController.h"

#include "../app/Application.h"
#include <glm/gtc/matrix_transform.hpp>

CameraController::CameraController(ApplicationPtr application) {
    this->application = application;
    this->zoom = 10.f;
}

bool CameraController::initialize(const glm::vec3& position, float fov) {
    this->updateFOV(fov);
    this->position = position;
    this->target = glm::vec3(0.f);
    this->refresh();
    return true;
}

glm::mat4 CameraController:: translate(const glm::vec3& position, const glm::vec3& orientation) const {
    glm::mat4 modelTranslated = glm::translate(this->model, position);

    modelTranslated = glm::rotate(modelTranslated, glm::radians(orientation.x), glm::vec3(1.f, 0.f, 0.f));
    modelTranslated = glm::rotate(modelTranslated, glm::radians(orientation.y), glm::vec3(0.f, 1.f, 0.f));
    modelTranslated = glm::rotate(modelTranslated, glm::radians(orientation.z), glm::vec3(0.f, 0.f, 1.f));

//    std::cout << "===========" << std::endl;
//    std::cout << "Position: " << position.x << " | " << position.y << " | " << position.z << std::endl;
//    std::cout << "Orientation: " << orientation.x << " | " << orientation.y << " | " << orientation.z << std::endl;
//    std::cout << modelTranslated[0].x << " | " << modelTranslated[0].y << " | " << modelTranslated[0].z << std::endl;
//    std::cout << modelTranslated[1].x << " | " << modelTranslated[1].y << " | " << modelTranslated[1].z << std::endl;
//    std::cout << modelTranslated[2].x << " | " << modelTranslated[2].y << " | " << modelTranslated[2].z << std::endl;
//    std::cout << modelTranslated[3].x << " | " << modelTranslated[3].y << " | " << modelTranslated[3].z << std::endl;
//    std::cout << "===========" << std::endl;

    glm::mat4 matZoom = glm::scale(glm::mat4(1.0f), glm::vec3(this->zoom));
    return this->projection * (this->view * matZoom) * modelTranslated;
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
    this->angle = angle;
    this->refresh();
    return oldAngle;
}

float CameraController::updateAngle(float angle) {
    float newAngle = this->angle + angle;
    this->setAngle(newAngle);
    return angle;
}

float CameraController::setZoom(float zoom) {
    float oldZoom = this->zoom;
    this->position.z = this->zoom = zoom;
    this->refresh();
    return oldZoom;
}

float CameraController::updateZoom(float zoom) {
    float newZoom = this->zoom + fabs(this->zoom) * zoom;
    this->setZoom(newZoom);
    return newZoom;
}

void CameraController::refresh() {
    this->view = glm::lookAt(this->position, target, glm::vec3(0.f, 1.f, 0.f));

    // Rotations
    // https://www.songho.ca/opengl/files/gl_camera07.jpg
    // https://learnopengl.com/img/getting-started/camera_pitch_yaw_roll.png
    this->model = glm::rotate(this->model, this->angle, glm::normalize(glm::vec3(0.f, 1.f, 0.f)));

    this->mvp = this->projection * this->view * this->model;
}
