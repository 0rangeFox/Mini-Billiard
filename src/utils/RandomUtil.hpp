//
// Created by João Fernandes on 20/05/2024.
//

#ifndef MINI_BILLIARD_RANDOMUTIL_HPP
#define MINI_BILLIARD_RANDOMUTIL_HPP

#include <cstdlib>
#include <random>
#include <glm/glm.hpp>

static double Random(double min, double max) {
    return min + (float) rand() / ((float) RAND_MAX / (max - min));
}

static size_t Random(size_t min, size_t max) {
    return min + (rand() % (max - min + 1));
}

static glm::vec2 RandomVec2(float min, float max) {
    return { Random(min, max), Random(min, max) };
}

static glm::vec3 RandomVec3(float min, float max) {
    return { RandomVec2(min, max), Random(min, max) };
}

#endif //MINI_BILLIARD_RANDOMUTIL_HPP
