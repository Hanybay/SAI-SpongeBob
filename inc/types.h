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
#include <time.h>

// Constantes
#define DEFAULT_FOV 45.0f
#define DEFAULT_CLIP_FRONT 0.1f
#define DEFAULT_CLIP_BACK 200.0f
#define DEFAULT_CAMERA_SPEED 3.6f
#define DEFAULT_MOVE_STEP 0.1f
#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600

// Types
// // Type représentant un point
typedef struct {
    float x, y, z;
} t_point;

// // // Initialise le point avec les coordonnées données
#define INIT_POINT(p, _x, _y, _z) do { \
    (p).x = (_x); \
    (p).y = (_y); \
    (p).z = (_z); \
} while (0)

// // // Affiche les coordonnées du point
#define PRINT_POINT(p) do { \
    printf("(x = %f, y = %f, z = %f)\n", (p).x, (p).y, (p).z); \
} while (0)

// // // Translate le point par le vecteur
#define  TRANSLATE_POINT(p, _v) do { \
    (p).x += (_v).x; \
    (p).y += (_v).y; \
    (p).z += (_v).z; \
} while (0)

// // Type représentant un vecteur (<=> t_point)
typedef t_point t_vector;

// // // Soustrait le vecteur par un autre vecteur
#define SUBTRACT_VECTOR(result, vec1, vec2) do { \
    (result).x = (vec1).x - (vec2).x; \
    (result).y = (vec1).y - (vec2).y; \
    (result).z = (vec1).z - (vec2).z; \
} while (0)

// // // Ajoute un vecteur au vecteur
#define ADD_VECTOR(result, vec1, vec2) do { \
    (result).x = (vec1).x + (vec2).x; \
    (result).y = (vec1).y + (vec2).y; \
    (result).z = (vec1).z + (vec2).z; \
} while (0)

// // Type représentant une couleur
typedef struct {
    float r, g, b;
} t_color;

// // // Initialise la couleur avec le code rgb donné
#define INIT_COLOR(c, _r, _g, _b) do { \
    (c).r = (_r); \
    (c).g = (_g); \
    (c).b = (_b); \
} while (0)

// // Type représentant un AABB parallélépipède
// // rectangle dont tous les côtés sont parallèles avec les axes
typedef struct {
    float min_x, max_x;
    float min_y, max_y;
    float min_z, max_z;
} t_AABB;

#endif