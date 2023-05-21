#ifndef _TYPES_H_
#define _TYPES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

// Constantes
#define DEFAULT_FOV 45.0f
#define DEFAULT_CLIP_FRONT 0.1f
#define DEFAULT_CLIP_BACK 100.0f
#define DEFAULT_CAMERA_SPEED 3.0f
#define DEFAULT_MOVE_STEP 0.1f
#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600

// Types
// // Type représentant un point
typedef struct {
    float x, y, z;
} t_point;

#define INIT_POINT(p, _x, _y, _z) do { \
    (p).x = (_x); \
    (p).y = (_y); \
    (p).z = (_z); \
} while (0)

#define PRINT_POINT(p) do { \
    printf("(x = %f, y = %f, z = %f)\n", (p).x, (p).y, (p).z); \
} while (0)

// // Type représentant un vecteur
typedef t_point t_vector;

// // Type représentant une couleur
typedef struct {
    float r, g, b;
} t_color;

#define INIT_COLOR(c, _r, _g, _b) do { \
    (c).r = (_r); \
    (c).g = (_g); \
    (c).b = (_b); \
} while (0)

#endif