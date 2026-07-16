#pragma once

#include <stdint.h>
#include <types.hpp>
#include <type_traits>
#include <concepts>

namespace cv {
class vec2;
class vec3;
class vec4;
class vec5;
class vec6;

template<typename T>
concept vector = std::is_same_v<T, vec2>
                 ||std::is_same_v<T, vec3>
                 ||std::is_same_v<T, vec4>
                 ||std::is_same_v<T, vec5>
                 ||std::is_same_v<T, vec6>;

template<typename T>
class vec2_internal {
    public:
    T x;
    T y;

    vec2() {x, y = 0;}
    vec2(std::arithmetic auto a) {x = a; y = 0;}
    vec2(vec2 a) {x = a.x; y = a.y;}
};
}