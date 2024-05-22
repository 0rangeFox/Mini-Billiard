#ifndef MINI_BILLIARD_OBJECT_H
#define MINI_BILLIARD_OBJECT_H

#include "../utils/RandomUtil.hpp"

typedef struct Object {
    explicit Object(const glm::vec3& position, const glm::vec3& orientation) {
        this->position = position;
        this->orientation = orientation;
    }

    Object(float min = 0, float max = 0) : Object(RandomVec3(min, max), RandomVec3(min, max)) {}

    virtual const glm::vec3& getPosition() const { return this->position; }
    virtual const glm::vec3& getOrientation() const { return this->orientation; }

protected:
    glm::vec3 position;
    glm::vec3 orientation;
} * ObjectPtr;

#endif //MINI_BILLIARD_OBJECT_H
