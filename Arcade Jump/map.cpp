#include "all_headers.h"

bool ground_collision(avatar &avatar, int x, int y)
{
	if (avatar.x + avatar.w >= x && avatar.x + avatar.w <= x + blocksize + avatar.w)
	{
		if (avatar.y + avatar.h == y)
			return true;
	}
	return false;
}

void drawmap(int **map, int &sizeX, int &map_speed, int *coordsX, int *coordsY, avatar &avatar, c_object *collide_objects, bool &collision, int &ground, int &start_ground, bool color_on)
{
	bool tile_collision = false;

	for (int i = 0; i < sizeX; ++i)
	{
		if (coordsX[i] < width && coordsX[i]>-20)
		{
			switch (map[i][1])
			{
			case 1:
				if (!color_on)
					al_draw_bitmap(collide_objects[0].image, coordsX[i], coordsY[i], 0);
				else
					al_draw_tinted_bitmap(collide_objects[0].image, tint_color, coordsX[i], coordsY[i], 0);
				(Mask_Collide(avatar.mask, collide_objects[0].mask, avatar.x - coordsX[i], avatar.y - coordsY[i])) ? collision = true : collision = false;
				break;
			case 2:
				if (!color_on)
					al_draw_bitmap(collide_objects[1].image, coordsX[i], coordsY[i], 0);
				else
					al_draw_tinted_bitmap(collide_objects[1].image, tint_color, coordsX[i], coordsY[i], 0);
				(Mask_Collide(avatar.mask, collide_objects[1].mask, avatar.x - coordsX[i], avatar.y - (coordsY[i] + 1))) ? collision = true : collision = false;
				(ground_collision(avatar, coordsX[i], coordsY[i])) ? tile_collision = true : tile_collision = false;
				if (coordsX[i] <= 0)
				{
					if (coordsX[i + 1] > coordsX[i] + blocksize)
						ground = start_ground;
					if (map[i + 1][1] == 2 && coordsX[i + 1] == coordsX[i] + blocksize && coordsY[i + 1] > coordsY[i])
						ground = coordsY[i + 1] - blocksize;
				}
				break;
			case 3:
				if (!color_on)
					al_draw_bitmap(collide_objects[0].image, coordsX[i], (coordsY[i] + blocksize), ALLEGRO_FLIP_VERTICAL);
				else
					al_draw_tinted_bitmap(collide_objects[0].image, tint_color, coordsX[i], (coordsY[i] + blocksize), ALLEGRO_FLIP_VERTICAL);
				(Mask_Collide(avatar.mask, collide_objects[2].mask, avatar.x - coordsX[i], avatar.y - (coordsY[i] + blocksize))) ? collision = true : collision = false;
				break;
			case 4:
				if (!color_on)
					al_draw_rotated_bitmap(collide_objects[0].image, 0, 0, coordsX[i] - blocksize, coordsY[i] + blocksize, 3 * ALLEGRO_PI / 2, 0);
				else
					al_draw_tinted_rotated_bitmap(collide_objects[0].image, tint_color, 0, 0, coordsX[i] - blocksize, coordsY[i] + blocksize, 3 * ALLEGRO_PI / 2, 0);
				(Mask_Collide(avatar.mask, collide_objects[1].mask, avatar.x - (coordsX[i] - blocksize), avatar.y - (coordsY[i]))) ? collision = true : collision = false;
				break;
			case 5:
				if (!color_on)
					al_draw_bitmap(collide_objects[1].image, coordsX[i], coordsY[i], 0);
				else
					al_draw_tinted_bitmap(collide_objects[1].image, tint_color, coordsX[i], coordsY[i], 0);
				(Mask_Collide(avatar.mask, collide_objects[1].mask, avatar.x - coordsX[i], avatar.y - coordsY[i])) ? collision = true : collision = false;
				break;
			}//switch

			//==============================================
			//COLLISION DETECTION
			//==============================================

			if (tile_collision)
				ground = coordsY[i] - blocksize;

			if (collision)
				return;
		}//if 
		coordsX[i] -= map_speed;
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
