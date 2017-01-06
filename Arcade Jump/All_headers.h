#pragma once
// allegro extensions
#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include <fstream>
#include "PPCD.h"

// menu functions
void menu(void);
void settings(void);
// colors
void color_press(int *r, int *g, int *b, int selection, int max); // coloring selected option
// game
void game(void);
char pause(void); // return m if user press main menu in pause menu, return g if user press continue in pause menu
// maps
void loadmap(std::ifstream &filename, int **map); // loading map
void drawmap(int **map, int *coordsX, int *coordsY, struct player &player, struct c_object *collide_objects); // drawing map
// intro
void intro(void);

// global variables
#define blocksize 40
extern ALLEGRO_TIMER *fps_timer;
extern ALLEGRO_DISPLAY *display;
extern int width;
extern int height;
extern int fps;
extern int color[]; // color of unpressed button
extern int sizeX; // elements in the map
extern float speed; // speed of the map
extern int ground;
extern int start_ground;

typedef struct player
{
	int w, h;
	int x = 40; // position of player in X
	int y; // position of player in Y
	float vely = 0;
	const float gravity = 1.05;
	ALLEGRO_BITMAP *image;
	mask_t *mask;
}player;

typedef struct c_object
{
	ALLEGRO_BITMAP *image;
	mask_t *mask;
}c_object;