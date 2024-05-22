#ifndef MINI_BILLIARD_OBJECT_H
#define MINI_BILLIARD_OBJECT_H

#include "../utils/RandomUtil.hpp"

typedef struct Object {
    explicit Object(const glm::vec3& position, const glm::vec3& orientation) {
        this->position = position;
        this->orientation = orientation;
    }

    virtual const glm::vec3& getPosition() const { return this->position; }
    virtual const glm::vec3& getOrientation() const { return this->orientation; }

    virtual void updatePosition(const glm::vec3& position) { this->position = position; }
    virtual void updateOrientation(const glm::vec3& orientation) { this->orientation = orientation; }

protected:
    glm::vec3 position;
    glm::vec3 orientation;
} * ObjectPtr;

#endif //MINI_BILLIARD_OBJECT_H
