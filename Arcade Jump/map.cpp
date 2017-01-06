#include "all_headers.h"
#include <iostream>

int sizeX; // elements in the map

bool ground_collision(player &player, int x, int y)
{
	if (player.x + player.w >= x && player.x + player.w <= x + blocksize + player.w)
	{
		if (player.y + player.h == y)
			return true;
	}
	return false;
}

void drawmap(int **map, int *coordsX, int *coordsY, player &player, c_object *collide_objects)
{
	bool collision = false;
	bool tile_collision = false;

	for (int i = 0; i < sizeX; ++i)
	{
		if (coordsX[i] < width && coordsX[i]>-20)
		{
			switch (map[i][1])
			{
			case 1:
				al_draw_bitmap(collide_objects[0].image, coordsX[i], coordsY[i], 0);
				(Mask_Collide(player.mask, collide_objects[0].mask, player.x - coordsX[i], player.y - coordsY[i])) ? collision = true : collision = false;
				break;
			case 2:
				al_draw_bitmap(collide_objects[1].image, coordsX[i], coordsY[i], 0);
				(Mask_Collide(player.mask, collide_objects[1].mask, player.x - coordsX[i], player.y - (coordsY[i]+1))) ? collision = true : collision = false;
				//(Mask_Collide(player.mask, collide_objects[1].mask, player.x - coordsX[i], player.y - (coordsY[i] - blocksize))) ? tile_collision = true : tile_collision = false;
				(ground_collision(player, coordsX[i], coordsY[i])) ? tile_collision = true : tile_collision = false;
				if (coordsX[i] <= 0)
				{
					if (coordsX[i + 1] > coordsX[i] + blocksize)
						ground = start_ground;
					if (map[i+1][1]==2 && coordsX[i + 1] == coordsX[i] + blocksize && coordsY[i+1] > coordsY[i])
						ground = coordsY[i + 1] - blocksize;
				}
				break;
			case 3:
				al_draw_bitmap(collide_objects[0].image, coordsX[i], (coordsY[i] + blocksize), ALLEGRO_FLIP_VERTICAL);
				(Mask_Collide(player.mask, collide_objects[2].mask, player.x - coordsX[i], player.y - (coordsY[i] + blocksize))) ? collision = true : collision = false;
				break;
			case 4:
				al_draw_rotated_bitmap(collide_objects[0].image, 0, 0, coordsX[i] - blocksize, coordsY[i] + blocksize, 3 * ALLEGRO_PI / 2, 0);
				(Mask_Collide(player.mask, collide_objects[1].mask, player.x - (coordsX[i] - blocksize), player.y - (coordsY[i]))) ? collision = true : collision = false;
				break;
			case 5:
				(Mask_Collide(player.mask, collide_objects[1].mask, player.x - coordsX[i], player.y - coordsY[i])) ? collision = true : collision = false;
				al_draw_bitmap(collide_objects[1].image, coordsX[i], coordsY[i], 0);
				break;
			}//switch
			if (tile_collision)
				ground = coordsY[i] - blocksize;

			//FOR DEBUG
			//if (collision)
			//{
			//	//al_draw_rectangle(width / 2, height / 2, width / 2 + blocksize, height / 2 - blocksize, al_map_rgb(0, 0, 0), 0);
			//	Mask_Draw(player.mask, player.x, player.y - blocksize / 2);
			//	Mask_Draw(collide_objects[1].mask, coordsX[i] - blocksize, coordsY[i] - blocksize / 2);
			//}

			if (collision)
			{
				al_draw_rectangle(width / 2, height / 2, width / 2 + blocksize, height / 2 - blocksize, al_map_rgb(0, 0, 0), 0);
			}
		}//if 
		coordsX[i] -= speed;
	}//for
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
