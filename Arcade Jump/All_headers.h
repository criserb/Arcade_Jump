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
#include <allegro5\allegro_video.h>
#include <fstream>
#include <iostream>

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
void drawmap(int **map, int *coordsX, int *coordsY, struct player player); // drawing map
// splash screen
void splash_screen(void);

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
typedef struct player
{
	int w = 38;
	int h = 38;
	int x = 40; // position of player in X
	int y = height - 60; // position of player in Y
	float vely = 0;
	const float gravity = 1.05;
}player;