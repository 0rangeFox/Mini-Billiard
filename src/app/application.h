//
// Created by João Fernandes on 13/05/2024.
//

#ifndef MINI_BILLIARD_APPLICATION_H
#define MINI_BILLIARD_APPLICATION_H

#include <tuple>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../constants.h"
#include "../classes/ObjectRenderable.h"

typedef std::tuple<double, double> MouseCoord;
typedef std::tuple<MouseCoord, MouseCoord> MouseCoords;

class Application {
public:
    GLuint VAO[VAOs]{};
    GLuint VBO[VBOs]{};

    Application(const char*, int, int);
    ~Application();

    float getAngle() const { return this->angle; }
    float getZoom() const { return this->zoom; }

    /// Update the coordinates of mouse
    /// \param x The new position in X
    /// \param y The new position in Y
    /// \return Return a tuple with the two coordinates of mouse from X and Y,
    /// the left side is coord X and right side is coord Y.
    /// Inside of coord, the left size is last coord and right side is actual coord.
    MouseCoords updateMouseCoords(double x, double y) {
        std::get<0>(this->mouseX) = std::get<1>(this->mouseX);
        std::get<1>(this->mouseX) = x;

        std::get<0>(this->mouseY) = std::get<1>(this->mouseY);
        std::get<1>(this->mouseY) = y;

        return std::make_tuple(this->mouseX, this->mouseY);
    }

    bool isMouseLeftButtonDown() const { return this->mouseLeftButtonDownStatus; }
    void setMouseLeftButtonDown(bool status) { this->mouseLeftButtonDownStatus = status; }

    void addObject(const ObjectRenderable*);

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

    int run();

private:
    int width, height;
    float angle, zoom;
    bool mouseLeftButtonDownStatus = false;
    MouseCoord mouseX{ 0, 0 }, mouseY{ 0, 0 };
    glm::mat4 mvp{ .0f };

    GLFWwindow* actualWindow;
    std::vector<const ObjectRenderable*> objects;

    bool setupVAOsAndVBOs();
    void updateCamera();
};

#endif //MINI_BILLIARD_APPLICATION_H
