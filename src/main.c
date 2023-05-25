/* 
* Module : principal
* Type : fichier source
* Auteurs : Mourtaza AKIL, BAYAZID Hany
* Date de création : 
*/

#include "types.h"
#include "observer.h"
#include "drawing.h"
#include "bullet.h"
#include "object.h"
#include "house.h"
#include "sphere.h"
#include "tree.h"

// Variables globales
float camera_horizontal_angle = 0.0f;        // Angle horizontal de la caméra en degrés
float camera_vertical_angle = 0.0f;          // Angle vertical de la caméra en degrés
t_point camera_position = {                  // Position de la caméra
    1.0f, 1.0f, -3.0f
};
t_point camera_target;
float camera_distance = 5.0f;                // Distance entre la caméra et sa cible
float window_width = DEFAULT_WINDOW_WIDTH,   // Largeur de la fenêtre
      window_height = DEFAULT_WINDOW_HEIGHT; // Hauteur de la fenêtre
float aspect;
float delta_time = 0;
int last_time = 0;
int frames_counter = 0;
int onclickChoice = 0;

t_point platform_min_corner = {
    -100.0f, 0.0f, -100.0f
}, platform_max_corner = {
    100.0f, 0.0f, 100.0f
};

// Horloge précédente en millisecondes
static clock_t previous_clock = 0;

// Délai de mise à jour maximale en millisecondes
static const int update_delay = 1000 / 30;


// Affiche la notice d'utilisation
void help_notice() {
    fprintf(stdout, "\n////////////////////////////BALLALAND////////////////////////////\n\n"
                    "\n- Les touches suivantes sont interactives :\n"
                    "\n-----------------------------------------------------------------\n\n"
                    "    '[GAUCHE]'     :    déplace l'observateur vers la gauche.\n"
                    "    '[DROITE]'     :    déplace l'observateur vers la droite.\n"
                    "    '[AVANT]'      :    avance l'observateur.\n"
                    "    '[ARRIERE]'    :    recule l'observateur.\n\n"

                    "    '[Q]'          :    déplace la caméra vers la gauche.\n"
                    "    '[D]'          :    déplace la caméra vers la droite.\n"
                    "    '[S]'          :    déplace la caméra vers le bas.\n"
                    "    '[Z]'          :    déplace la caméra vers le haut.\n\n"

                    "    '[B]'          :    permet de tirer une balle.\n"
                    "    '[W]'          :    permet de créer une boule vivante.\n"
                    "    '[A]'          :    permet d'ouvrir une porte qui se trouve \n"
                    "                        à proximité.\n\n"
                    "\n-----------------------------------------------------------------\n\n");
}

// Affiche la notice d'utilisation du programme
void usage(char * programme, char * message, ...) {
    va_list arg;
    va_start(arg, message);
    if (strlen(message) != 0) {
        fprintf(stderr, "- Message -> ");
        vfprintf(stderr, message, arg);
        if (message[strlen(message) - 2] != '\n')
            fprintf(stderr, "\n");
        fprintf(stderr, "\n");
    }
    va_end(arg);
    fprintf(stderr, "- Usage : %s \n",
            programme);
    exit(EXIT_FAILURE);
}

// Réalise l'affichage
void display() {
    // Temps écoulé entre chaque image
    int current_time = glutGet(GLUT_ELAPSED_TIME);
    delta_time = (current_time - last_time) / 1000.0f; // Conversion en secondes
    last_time = current_time;

    // Nettoyage
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Projection perspective pour le rendu 3D
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(DEFAULT_FOV, aspect, DEFAULT_CLIP_FRONT, DEFAULT_CLIP_BACK);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Caméra
    update_camera(camera_horizontal_angle, camera_vertical_angle, camera_distance);

    // Skybox
    draw_skybox(camera_position, 50.0f);

    // Plateforme
    glColor3f(194 / 255.0f, 178 / 255.0f, 128 / 255.0f);  // Couleur de la plateforme
    glBegin(GL_QUADS);
        glVertex3f(platform_min_corner.x, platform_min_corner.y, platform_min_corner.z); // Coin inférieur gauche
        glVertex3f(platform_max_corner.x, platform_min_corner.y, platform_min_corner.z); // Coin inférieur droit
        glVertex3f(platform_max_corner.x, platform_max_corner.y, platform_max_corner.z); // Coin supérieur droit
        glVertex3f(platform_min_corner.x, platform_max_corner.y, platform_max_corner.z); // Coin supérieur gauche
    glEnd();

    // Plan
    draw_plane();

    // Balles
    draw_bullets();

    // Arbres
    draw_trees();

    // Espèces
    drawSpecies();

    // Maisons
    draw_houses();

    // Projection orthogonale pour le rendu 2D
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, window_width, window_height, 0.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Viseur
    draw_view_finder(window_width, window_height);

    glutSwapBuffers();
}

// Réalise les calculs
void update() {

    // Horloge actuelle en millisecondes
    clock_t current_clock = clock() * 1000 / CLOCKS_PER_SEC;

    // Délai de mise à jour atteint
    if (current_clock - previous_clock >= update_delay) {
        // Mise à jour de l'horloge précédente
        previous_clock = current_clock;

        // Balles
        update_bullets_positions();

        // Espèces
        updateSpherePosition();
        speciesCollisions();
        attractBeings(update_delay);

        glutPostRedisplay();
    }
}

// Gère les événements de redimensionnement de la fenêtre
void reshape(int width, int height) {
    if(height == 0) height = 1; 
    aspect = (float)width / (float)height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(DEFAULT_FOV, aspect, DEFAULT_CLIP_FRONT, DEFAULT_CLIP_BACK);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Récupèration des nouvelles dimensions
    window_height = height;
    window_width = width;
}

// Gère les événements clavier
void keyboard(unsigned char key, int x, int y) {
    // Vitesse de rotation de la caméra en degrés par pression de touche
    const float camera_speed = DEFAULT_CAMERA_SPEED;

    switch (key) {
        case 'q': // Déplacement de la caméra vers la gauche
            camera_horizontal_angle += camera_speed;

            // Mise à jour des vecteurs de déplacement
            rotate_movement_vectors(camera_vertical_angle, camera_horizontal_angle);
            break;
        case 'd': // Déplacement de la caméra vers la droite
            camera_horizontal_angle -= camera_speed;

            // Mise à jour des vecteurs de déplacement
            rotate_movement_vectors(camera_vertical_angle, camera_horizontal_angle);  
            break;
        case 's': // Déplacement de la caméra vers le bas
            camera_vertical_angle -= camera_speed;

            // Limiter l'angle pour éviter de regarder trop bas
            if (camera_vertical_angle < -45.0f)
                camera_vertical_angle = -45.0f;
            break;
        case 'z': // Déplacement de la caméra vers le haut
            camera_vertical_angle += camera_speed;
            
            // Limiter l'angle pour éviter de regarder trop haut
            if (camera_vertical_angle > 45.0f)
                camera_vertical_angle = 45.0f;
            break;
        case 'b': // Tire une balle
            shoot_bullet(camera_position, camera_target, 0.1);
            break;
        case 'w': // Crée une espèce
             addSpecie((onclickChoice == 1 ? (t_color) SPONGEBOB_SPHERE_COLOR : (t_color)PATRICK_SPHERE_COLOR), 0);
             onclickChoice = (onclickChoice == 1) ? 0 : 1;
             printf("COULEUR VAL = %d\n",onclickChoice);
            break;
        case 'a':
            try_open_close_door();
            break;
    }
}

// Gère les événements clavier spécial
void special_keyboard(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            move_forward();
            break;
        case GLUT_KEY_DOWN:
            move_back();
            break;
        case GLUT_KEY_LEFT:
            move_left();
            break;
        case GLUT_KEY_RIGHT:
            move_right();
    }
}

// Fonction principale
int main(int argc, char **argv) {

    // Affichage de la notice d'utilisation
    help_notice();

    // Initialisations
    srand(time(NULL));

    // Initialisation des paramètres OpenGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("SpongeBob Universe");

    // Fonctions gérant la fenêtre et ces événements
    glutDisplayFunc(display);
    glutIdleFunc(update);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special_keyboard);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Initialisations du monde
    generate_random_houses(10, platform_min_corner, platform_max_corner);
    generate_random_trees(50, platform_min_corner, platform_max_corner);
    init_observer(camera_position);

    glutMainLoop();
    
    exit(EXIT_SUCCESS);
}

