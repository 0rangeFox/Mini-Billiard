//
// Created by João Fernandes on 20/05/2024.
//

#ifndef MINI_BILLIARD_CAMERACONTROLLER_H
#define MINI_BILLIARD_CAMERACONTROLLER_H

#include <glm/glm.hpp>

class Application;

class CameraController {
public:
    CameraController(const Application*);

    const glm::mat4& getMVP() const { return this->mvp; }
    float getAngle() const { return this->angle; }
    float getZoom() const { return this->zoom; }

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

    void refresh();

private:
    const Application* application;
    float angle, zoom;

    glm::mat4 mvp{ .0f };
};

#endif //MINI_BILLIARD_CAMERACONTROLLER_H
