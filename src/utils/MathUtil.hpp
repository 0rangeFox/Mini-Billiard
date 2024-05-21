//
// Created by João Fernandes on 21/05/2024.
//

#ifndef MINI_BILLIARD_MATHUTIL_HPP
#define MINI_BILLIARD_MATHUTIL_HPP

/// Normalize the angle to be within 0 to 360 degrees
/// \param angle The angle to be normalized
/// \return The normalized angle
static float NormalizeAngle(float angle) {
    while (angle < 0.f) angle += 360.f;
    while (angle >= 360.f) angle -= 360.f;
    return angle;
}

#endif //MINI_BILLIARD_MATHUTIL_HPP
