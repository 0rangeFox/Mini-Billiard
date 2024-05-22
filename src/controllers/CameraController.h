#ifndef MINI_BILLIARD_CAMERACONTROLLER_H
#define MINI_BILLIARD_CAMERACONTROLLER_H

#include <glm/glm.hpp>
#include "../classes/LightType.h"
#include <iostream>

#define MIN_FOV 30
#define MAX_FOV 120

class Application;

class CameraController {
public:
    CameraController(const Application*);

    bool initialize(const glm::vec3&, float = MIN_FOV);
    const glm::mat4& getView() const { return this->view; }
    const glm::mat4& getModel() const { return this->model; }
    const glm::mat4& getMVP() const { return this->mvp; }
    glm::mat4 translate(const glm::vec3&, const glm::vec3&) const;

    const bool* getLights() const { return this->lights; }
    float getAngle() const { return this->angle; }
    float getZoom() const { return this->zoom[0][0]; }

    void updateLight(LightType type) { this->lights[type] = !this->lights[type]; }

    float updateFOV(float);

    /// Set a value to the angle
    /// \return  The last angle value
    float setAngle(float);

    /// Update the angle with the value (Without replacing, it's only sum with the value)
    /// \param angle The value to be summed into the angle
    /// \return
    float updateAngle(float angle);

    /// Set a value to the zoom
    /// \return The last zoom value
    float setZoom(float);

    /// Update the zoom with the value (Without replacing, it's only sum with the value)
    /// \param zoom The value to be summed into the zoom
    /// \return The new zoom value
    float updateZoom(float zoom);

private:
    const Application* application;

    glm::vec3 position, target;
    float fov, angle;

    bool lights[TOTAL_LIGHTS] = { true, true, true, true };

    glm::mat4 zoom, projection, view, model{ 1.f };
    glm::mat4 mvp{ .0f };

    void refresh();
};

#endif //MINI_BILLIARD_CAMERACONTROLLER_H
