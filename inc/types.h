#ifndef _TYPES_H_
#define _TYPES_H_

// Constantes
#define SIZE 1024
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define DEFAULT_DISTANCE 4096
#define DEFAULT_ANGLE 0
#define DEFAULT_ANGLE_STEP 1
#define DEFAULT_MOVE_STEP 204.8
#define DEFAULT_MOUSE_SENSITIVITY 0.1

// Types
typedef struct {
    float left, right, top, bottom, near, far;
} t_frustum;

typedef struct {
    float x, y, z;
} t_point;

typedef t_point t_vector;

#endif