#include "all_headers.h"
#include <iostream>

int sizeX; // elements it the map

bool ground_collision(player &player, float b2_x, float b2_y)
{
	if (player.x + player.w >= b2_x && player.x + player.w <= b2_x + blocksize + player.w)
	{
		if (player.y + player.h == b2_y)
		{
			return true;
		}
	}
	return false;
}

void drawmap(int **map, int *coordsX, int *coordsY, player &player, c_object *collide_objects)
{
	bool collision = false;
	bool tile_collision = false;

	for (int i = 0; i < sizeX; ++i)
	{
		//==============================================
		//COLLISION
		//==============================================
		switch (map[i][1])
		{
		case 1: /*al_draw_triangle(coordsX[i], coordsY[i], coordsX[i] + blocksize, coordsY[i], coordsX[i] + blocksize / 2, coordsY[i] - blocksize,
			al_map_rgb(0, 0, 0), 0);*/
			al_draw_bitmap(collide_objects[0].image, coordsX[i], coordsY[i], 0);
			(Mask_Collide(player.mask, collide_objects[0].mask, player.x - coordsX[i], player.y - coordsY[i])) ? collision = true : collision = false;
			break;
		case 2: //al_draw_rectangle(coordsX[i], coordsY[i], coordsX[i] + blocksize, coordsY[i] - blocksize, al_map_rgb(0, 0, 0), 0);
			//al_draw_bitmap(collide_objects[1].image, coordsX[i], coordsY[i], 0);
			//(Mask_Collide(player.mask, collide_objects[1].mask, player.x - coordsX[i], player.y - coordsY[i])) ? collision = true : collision= false;
			al_draw_bitmap(collide_objects[1].image, coordsX[i], coordsY[i], 0);
			(Mask_Collide(player.mask, collide_objects[1].mask, player.x - coordsX[i], player.y - coordsY[i])) ? collision = true : collision = false;
			(Mask_Collide(player.mask, collide_objects[1].mask, player.x - coordsX[i], player.y - (coordsY[i] - blocksize))) ? tile_collision = true : tile_collision = false;
			//if (coordsY[i - 1] < coordsY[i])
			//	(Mask_Collide(player.mask, collide_objects[1].mask, player.x - coordsX[i], player.y - (coordsY[i - 1] - blocksize))) ? tile_back_collision = true : tile_back_collision = false;

			//al_draw_filled_rectangle(player.x, player.y, player.x + player.w, player.y + player.h, al_map_rgba_f(.6, 0, .6, .6));
			//al_draw_filled_rectangle(coordsX[i], coordsY[i], coordsX[i] + blocksize, coordsY[i] + blocksize, al_map_rgba_f(.6, 0, .6, .6));
			break;
		case 3: /*al_draw_triangle(coordsX[i], coordsY[i], coordsX[i] + blocksize, coordsY[i], coordsX[i] + blocksize / 2, coordsY[i] + blocksize,
			al_map_rgb(0, 0, 0), 0);*/
			al_draw_bitmap(collide_objects[0].image, coordsX[i], (coordsY[i] + blocksize), ALLEGRO_FLIP_VERTICAL);
			(Mask_Collide(player.mask, collide_objects[1].mask, player.x - coordsX[i], player.y - (coordsY[i] + blocksize))) ? collision = true : collision = false;
			break;
		case 4:
			/*al_draw_triangle(coordsX[i] - blocksize, coordsY[i] - blocksize / 2, coordsX[i], coordsY[i] - blocksize, coordsX[i], coordsY[i],
				al_map_rgb(0, 0, 0), 0);*/
			al_draw_rotated_bitmap(collide_objects[0].image, 0, 0, coordsX[i] - blocksize, coordsY[i] + blocksize, 3 * ALLEGRO_PI / 2, 0);
			(Mask_Collide(player.mask, collide_objects[1].mask, player.x - (coordsX[i] - blocksize), player.y - (coordsY[i]))) ? collision = true : collision = false;
			//FOR DEBUG
			//if (collision)
			//{
			//	//al_draw_rectangle(width / 2, height / 2, width / 2 + blocksize, height / 2 - blocksize, al_map_rgb(0, 0, 0), 0);
			//	Mask_Draw(player.mask, player.x, player.y - blocksize / 2);
			//	Mask_Draw(collide_objects[1].mask, coordsX[i] - blocksize, coordsY[i] - blocksize / 2);
			//}
			break;
		}
		if (tile_collision)
		{
			ground = coordsY[i] - blocksize;
		}


		if (collision)
			al_draw_rectangle(width / 2, height / 2, width / 2 + blocksize, height / 2 - blocksize, al_map_rgb(0, 0, 0), 0);
		coordsX[i] -= speed;
	}
}

void loadmap(std::ifstream &filemap, int **map)
{
	int loadCounterX = 0, loadCounterY = 0;
	if (filemap.is_open())
	{
		while (!filemap.eof())
		{
			filemap >> map[loadCounterX][loadCounterY];
			loadCounterY++;
			if (loadCounterY == 3)
			{
				loadCounterY = 0;
				loadCounterX++;
			}
		}
	}
	else
		al_show_native_message_box(display, "Arcade Jump", "ERROR", "ERROR WITH LOAD MAP", "Error with map", ALLEGRO_MESSAGEBOX_WARN);
}
