#ifndef MINI_BILLIARD_APPLICATION_H
#define MINI_BILLIARD_APPLICATION_H

#include <tuple>
#include <unordered_map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Constants.h"
#include "../controllers/CameraController.h"
#include "../classes/ObjectType.h"

typedef std::tuple<double, double> MouseCoord;
typedef std::tuple<MouseCoord, MouseCoord> MouseCoords;
typedef std::unordered_map<GLuint, GLuint>* TexturesCache;

class ObjectRenderable;

class Application {
public:
    Application(const char*, int, int);
    ~Application();

    float getAspectRatio() const { return this->aspectRatio; }

    bool updateResolution(int width, int height) {
        glfwGetWindowSize(this->actualWindow, &this->width, &this->height);

        if (this->width == width && this->height == height)
            return false;

        glfwSetWindowSize(this->actualWindow, this->width = width, this->height = height);
        glViewport(0, 0, this->width, this->height);
        this->aspectRatio = float(this->width) / float(this->height);

        return true;
    }

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

    const GLuint& getVAO(ObjectType type) const { return this->VAO[type]; }
    const GLuint& getVBO(ObjectType type, GLuint index) const { return this->VBO[type][index]; }

    bool addObject(ObjectRenderable*, bool = true, float = 1.f, float = 1.f);

    const CameraController& getCamera() const { return this->camera; }
    CameraController* const getCameraPtr() { return &this->camera; }
    const TexturesCache getTexturesCache() const { return this->textures; }

    bool animateBall(GLuint ball) {
        if (this->ballIdToAnimate)
            return false;

        this->ballIdToAnimate = ball;
        return true;
    }

    int run();

private:
    bool isInitialized = false, mouseLeftButtonDownStatus = false;
    int width = 0, height = 0;
    float aspectRatio = 0.f;

    MouseCoord mouseX{ 0, 0 }, mouseY{ 0, 0 };

    GLFWwindow* actualWindow;
    CameraController camera{ this };

    GLuint VAO[VAOs]{};
    GLuint VBO[VAOs][VBOs]{};
    TexturesCache textures;
    std::vector<const ObjectRenderable*> objects;

    GLuint ballIdToAnimate = 0;

    bool setupVAOsAndVBOs();
    void renderAnimations();
};

typedef const Application* ApplicationPtr;

#endif //MINI_BILLIARD_APPLICATION_H
