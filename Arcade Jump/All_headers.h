#pragma once
// allegro extensions
#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>

// menu functions
void menu(void);
void settings(void);
void color_press(int *r, int *g, int *b, int selection, int max); // coloring selected option
void game(void);
char pause(void); // return m if user press main menu in pause menu, return g if user press continue in pause menu

// global variables 
extern ALLEGRO_TIMER *fps_timer;
extern ALLEGRO_DISPLAY *display;
extern int width;
extern int height;
extern int fps;