#ifndef _TYPES_H_
#define _TYPES_H_

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

// // Type représentant un vecteur
typedef t_point t_vector;

// // Type représentant une couleur
typedef struct {
    float r, g, b;
} t_color;

#endif