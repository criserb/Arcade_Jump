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
#include "allegro5\allegro_video.h"
#include <fstream>
#include "PPCD.h"

// menu functions
void menu(void);
void settings(void);
// colors
void color_press(int *r, int *g, int *b, int selection, int max); // coloring selected option
// game
void game(void);
bool pause(ALLEGRO_BITMAP *pause_image); // return true if user press main menu in pause menu, return false if user press continue in pause menu
// maps
void loadmap(std::ifstream &filename, int **map); // loading map
void drawmap(int **map, int *coordsX, int *coordsY, struct player &player, struct c_object *collide_objects, bool &collision); // drawing map
// intro
void intro(void);
// parallax functions
void InitBackground(struct parallax_image &back, float x, float y, float velx, float vely, int width, int height, int dirX, int dirY, ALLEGRO_BITMAP *image);
void UpdateBackground(struct parallax_image &back);
void DrawBackground(struct parallax_image &back);
// explosions
void drawExplosions(struct explosion &explosion, int size, player &player);
char crash(ALLEGRO_BITMAP *collision_image);
void end_of_map(ALLEGRO_BITMAP *game_end);
ALLEGRO_BITMAP *resize(const char *filename, int destination_width, int destination_height);



// global variables
#define blocksize 40
extern ALLEGRO_TIMER *fps_timer;
extern ALLEGRO_DISPLAY *display;
extern int width;
extern int height;
extern int fps;
extern int color[]; // color of unpressed button
extern int sizeX; // elements in the map
extern int speed; // speed of the map
extern int ground;
extern int start_ground;

//structures
typedef struct player {
	int w, h;
	int x = 40; // position of player in X
	int y; // position of player in Y
	float vely = 0;
	const float gravity = 1.05;
	ALLEGRO_BITMAP *image;
	mask_t *mask;
}player;

typedef struct c_object {
	ALLEGRO_BITMAP *image;
	mask_t *mask;
}c_object;

typedef struct parallax_image {
	float x;
	float y;
	float velX;
	float velY;
	int dirX;
	int dirY;

	int width;
	int height;

	ALLEGRO_BITMAP *image;
}parallax_image;

typedef struct backgrounds {
	ALLEGRO_BITMAP *game_background_up;
	ALLEGRO_BITMAP *game_background_down;
}backgrounds;

typedef struct explosion {
	int count = 0, fx = 0, fy = 0;
	int frame_width = 256;
	int frame_height = 256;
	ALLEGRO_BITMAP *image;
}explosion;