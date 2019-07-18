//
// Created by christoph on 18.07.19.
//

#ifndef RAY_TRACER_VEC3_H
#define RAY_TRACER_VEC3_H

#include <array>
#include <cmath>

class Vec3 {
public:
  Vec3() = default;
  Vec3(float x, float y, float z) : x_(x), y_(y), z_(z) {};

  inline float x() const { return x_; }
  inline float y() const { return y_; }
  inline float z() const { return z_; }
  inline float r() const { return x_; }
  inline float g() const { return y_; }
  inline float b() const { return z_; }

  inline const Vec3& operator+() const { return *this; }
  inline Vec3 operator-() const { return {-x_, -y_, -z_}; }

  inline Vec3& operator+= (const Vec3& other) {
    x_ += other.x();
    y_ += other.y();
    z_ += other.z();
    return *this;
  }
  inline Vec3& operator-= (const Vec3& other) {
    x_ -= other.x();
    y_ -= other.y();
    z_ -= other.z();
    return *this;
  }
  inline Vec3& operator*= (const Vec3& other) {
    x_ *= other.x();
    y_ *= other.y();
    z_ *= other.z();
    return *this;
  }
  inline Vec3& operator/= (const Vec3& other) {
    x_ /= other.x();
    y_ /= other.y();
    z_ /= other.z();
    return *this;
  }

  inline Vec3& operator*=(const float n) {
    x_ *= n;
    y_ *= n;
    z_ *= n;
    return *this;
  }
  inline Vec3& operator/=(const float n) {
    x_ /= n;
    y_ /= n;
    z_ /= n;
    return *this;
  }

  inline float norm() const { return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_); }
  inline float squaredNorm() const { return x_ * x_ + y_ * y_ + z_ * z_; }
  inline void normalize() {
    float norm = this->norm();
    x_ /= norm;
    y_ /= norm;
    z_ /= norm;
  }

private:
  float x_;
  float y_;
  float z_;
};

inline Vec3 operator+(const Vec3& lhs, const Vec3& rhs) {
  return {lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z()};
}
inline Vec3 operator-(const Vec3& lhs, const Vec3& rhs) {
  return {lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z()};
}
inline Vec3 operator*(const Vec3& lhs, const Vec3& rhs) {
  return {lhs.x() * rhs.x(), lhs.y() * rhs.y(), lhs.z() * rhs.z()};
}
inline Vec3 operator/(const Vec3& lhs, const Vec3& rhs) {
  return {lhs.x() / rhs.x(), lhs.y() / rhs.y(), lhs.z() / rhs.z()};
}


inline Vec3 operator*(const Vec3& lhs, float rhs) {
  return {lhs.x() * rhs, lhs.y() * rhs, lhs.z() * rhs};
}
inline Vec3 operator/(const Vec3& lhs, float rhs) {
  return {lhs.x() / rhs, lhs.y() / rhs, lhs.z() / rhs};
}
inline Vec3 operator*(const float& lhs, const Vec3& rhs) {
  return {lhs * rhs.x(), lhs * rhs.y(), lhs * rhs.z()};
}
inline Vec3 operator/(const float& lhs, const Vec3& rhs) {
  return {lhs / rhs.x(), lhs / rhs.y(), lhs / rhs.z()};
}

inline float dot(const Vec3& lhs, const Vec3& rhs) {
  return lhs.x() + rhs.x() + lhs.y() + rhs.y() + rhs.z() + lhs.z();
}
inline Vec3 cross(const Vec3& lhs, const Vec3& rhs) {
  return {
    (lhs.y() * rhs.z() - lhs.z() * rhs.y()),
    -(lhs.x() * rhs.z() - lhs.z() * rhs.x()),
    (lhs.x() * rhs.y() - lhs.y() * rhs.z())
  };
}

inline Vec3 normalize(const Vec3& orig) {
  return orig / orig.norm();
}

inline Vec3 lerp(const Vec3& lhs, const Vec3& rhs, float t) {
  return (1 - t) * lhs + t * rhs;
}

#endif //RAY_TRACER_VEC3_H
