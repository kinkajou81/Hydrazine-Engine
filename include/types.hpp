#pragma once

#include <stdint.h>

#include <atomic>
#include <string>
#include <stdfloat>

#include <SDL3/SDL.h>

typedef SDL_Window window_t;

typedef struct {
	bool fullscreen : 1;
	bool resizable : 1;
	bool maximized : 1;
	bool minimized : 1;
	bool grab_mouse : 1;
	bool vsync : 1;
} window_properties;

// core system rely on float16_t as such an incorrect alias is provided but code may not be reasonably functional if at all without support
// an incorrect alias is provided for float128_t despite low or no usage in the engine, but it ensures anything built on this engine compiles
#if defined(__STDCPP_FLOAT16_T__)
	typedef std::float16_t float16_t;
#else
	typedef float float16_t;
#endif
#if defined(__STDCPP_FLOAT32_T__)
	typedef std::float32_t float32_t;
#else
	typedef float float32_t;
#endif
#if defined(__STDCPP_FLOAT64_T__)
	typedef std::float64_t float64_t;
#else
	typedef double float64_t;
#endif
#if defined(__STDCPP_FLOAT128_T__)
	typedef std::float128_t float128_t;
#
#endif

typedef std::atomic<SDL_Window*> window_t;

typedef struct {
	uint16_t resolution_x;
	uint16_t resolution_y;
} window_control;

typedef struct {
	float64_t depth;
	float16_t rotation_x;
	float16_t rotation_y;
	float16_t rotation_z;
} background_control;

typedef struct {
	float64_t offset_z;
	float64_t offset_x;
	float64_t offset_y;
	float16_t rotation_x;
	float16_t rotation_y;
	float16_t rotation_z;
} sprite_control;

typedef struct {
	bool flip_x : 1;
	bool flip_y : 1;
	uint16_t shader_id;
} tile_control;

typedef struct {
	uint8_t volume;
	uint16_t shader_id;
} sound_control;
