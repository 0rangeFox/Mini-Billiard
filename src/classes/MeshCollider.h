#ifndef MINI_BILLIARD_MESHCOLLIDER_H
#define MINI_BILLIARD_MESHCOLLIDER_H

#include "MeshType.h"
#include "Object.h"

#define DEFAULT_VALUE 1.f

typedef struct MeshCollider: public Object {
public:
    explicit MeshCollider(MeshType type, const glm::vec3& position, const glm::vec3& orientation, float radius = DEFAULT_VALUE, float minX = DEFAULT_VALUE, float maxX = DEFAULT_VALUE, float minY = DEFAULT_VALUE, float maxY = DEFAULT_VALUE, float minZ = DEFAULT_VALUE, float maxZ = DEFAULT_VALUE) : Object(position, orientation), type(type), radius(radius), min({ minX, minY, minZ }), max({ maxX, maxY, maxZ }) {}
    explicit MeshCollider(const glm::vec3& position, const glm::vec3& orientation, float radius) : MeshCollider(MeshType::SPHERE, position, orientation, radius) {}
    MeshCollider(float radius = DEFAULT_VALUE, float minX = 0.f, float maxX = 0.f, float minZ = 0.f, float maxZ = 0.f) : MeshCollider(glm::vec3(Random(minX, maxX), 0.f, Random(minZ, maxZ)), RandomVec3(-360, 360), radius) {}

    const MeshType& getMeshType() const { return this->type; }

    // https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection#sphere_vs._sphere
    bool collideWith(const MeshCollider& other, const glm::vec3& updatedPosition) const {
        if (this == &other) {
            return false;
        } else if (this->type == MeshType::SPHERE && other.type == MeshType::SPHERE)
            return glm::distance(updatedPosition, other.position) <= this->radius + other.radius;
        else if (this->type == MeshType::SPHERE && other.type == MeshType::CUBE) {
            auto closestPoint = glm::clamp(updatedPosition, other.position - other.min, other.position + other.max);
            return glm::distance(updatedPosition, closestPoint) <= this->radius;
        } else
            return false;
    }

    bool collideWith(const MeshCollider& other) const {
        return collideWith(other, this->position);
    }

protected:
    float radius;
    glm::vec3 min, max;

private:
    MeshType type;
} * MeshColliderPtr;

#endif //MINI_BILLIARD_MESHCOLLIDER_H
