#pragma once
// allegro extensions
#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include "allegro5\allegro_video.h"
#include <fstream>
#include "PPCD.h"
#include "structures.h"

// menu functions
void menu(void);
void settings(int &cord_cursor_x, int &cord_cursor_y);
// colors
void color_press(int *r, int *g, int *b, int selection, int max); // coloring selected option
// game
void game(void);
bool pause(ALLEGRO_BITMAP *pause_image); // return true if user press main menu in pause menu, return false if user press continue in pause menu
// maps
void loadmap(std::ifstream &filename, int **map); // loading map
void drawmap(int **map, int &sizeX, int &map_speed, int *coordsX, int *coordsY, struct avatar &avatar, struct c_object *collide_objects, bool &collision, int &ground, int &start_ground, bool color_on); // drawing map
// intro
void intro(void);
// parallax functions
void InitBackground(struct parallax_image &back, float x, float y, float velx, float vely, int width, int height, int dirX, int dirY, ALLEGRO_BITMAP *image);
void UpdateBackground(struct parallax_image &back);
void DrawBackground(struct parallax_image &back);
// explosions & crash & animation in end of map
void drawExplosions(struct explosion &explosion, int frame_width, int frame_height, int size, struct avatar &avatar, bool color_on);
char crash(ALLEGRO_BITMAP *collision_image);
void end_of_map(ALLEGRO_BITMAP *game_end);
ALLEGRO_BITMAP *resize_bitmap(const char *filename, int destination_width, int destination_height);
// drawing all objects
void redraw(struct avatar &avatar, int **map, int &sizeX, int &map_speed, int &ground, int &start_ground, int *coordsX, int *coordsY,struct c_object *collide_objects, struct game_backgrounds game_backgrounds, float &angle, bool &collision, struct parallax_image BG, bool color_on);



// global variables
#define blocksize 40
#define fps 60
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_COLOR tint_color;
extern int width;
extern int height;
extern int color[]; // color of unpressed button
extern int att_count;