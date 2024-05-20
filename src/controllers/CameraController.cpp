//
// Created by João Fernandes on 20/05/2024.
//

#include "CameraController.h"

#include "../app/Application.h"
#include <glm/gtc/matrix_transform.hpp>

CameraController::CameraController(ApplicationPtr application) {
    this->application = application;
    this->zoom = 10.f;
    this->angle = 0.f;
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
    this->zoom = zoom;
    this->refresh();
    return oldZoom;
}

float CameraController::updateZoom(float zoom) {
    float newZoom = this->zoom + fabs(this->zoom) * zoom;
    this->setZoom(newZoom);
    return newZoom;
}

void CameraController::refresh() {
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), this->application->getAspectRatio(), 0.1f, 100.f);

    glm::mat4 view = glm::lookAt(
            glm::vec3(0.0f, 5.0f, this->zoom),
            glm::vec3(0.0f, 0.f, -1.0f),
            glm::vec3(0.0f, 1.f, 0.0f)
    );

    // Rotations
    // https://www.songho.ca/opengl/files/gl_camera07.jpg
    // https://learnopengl.com/img/getting-started/camera_pitch_yaw_roll.png
    glm::mat4 model = glm::rotate(glm::mat4(1.0f), this->angle, glm::normalize(glm::vec3(0.f, 1.f, 0.f)));

    this->mvp = projection * view * model;
}
