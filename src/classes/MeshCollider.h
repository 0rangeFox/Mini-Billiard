//
// Created by João Fernandes on 21/05/2024.
//

#ifndef MINI_BILLIARD_MESHCOLLIDER_H
#define MINI_BILLIARD_MESHCOLLIDER_H

#include "MeshType.h"
#include "Object.h"

#define DEFAULT_VALUE 1.f

typedef struct MeshCollider: public Object {
public:
    explicit MeshCollider(MeshType type, const glm::vec3& position, const glm::vec3& orientation, float radius = DEFAULT_VALUE, float minX = DEFAULT_VALUE, float maxX = DEFAULT_VALUE, float minY = DEFAULT_VALUE, float maxY = DEFAULT_VALUE, float minZ = DEFAULT_VALUE, float maxZ = DEFAULT_VALUE) : Object(position, orientation), type(type), radius(radius), min({ minX, minY, minZ }), max({ maxX, maxY, maxZ }) {}
    explicit MeshCollider(const glm::vec3& position, const glm::vec3& orientation, float radius) : MeshCollider(MeshType::SPHERE, position, orientation, radius) {}
    MeshCollider(float radius = DEFAULT_VALUE, float min = 0, float max = 0) : MeshCollider(RandomVec3(min, max), RandomVec3(0, 0), radius) {}

    // https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection#sphere_vs._sphere
    bool collideWith(const MeshCollider& other) const {
        if (this->type == MeshType::SPHERE && other.type == MeshType::SPHERE)
            return glm::distance(this->position, other.position) <= this->radius + other.radius;
        else if (this->type == MeshType::SPHERE && other.type == MeshType::CUBE) {
            auto closestPoint = glm::clamp(this->position, other.position - other.min, other.position + other.max);
            return glm::distance(this->position, closestPoint) <= this->radius;
        } else
            return false;
    }

protected:
    float radius;
    glm::vec3 min, max;

private:
    MeshType type;
} * MeshColliderPtr;

#endif //MINI_BILLIARD_MESHCOLLIDER_H
