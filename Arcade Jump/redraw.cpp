#include "all_headers.h"

void redraw(avatar &avatar, int **map, int &sizeX, int &map_speed, int &ground, int &start_ground, int *coordsX, int *coordsY, c_object *collide_objects, game_backgrounds game_backgrounds, float &angle, bool &collision, parallax_image BG, bool color_on)
{
	// rendering game up_background
	if (!color_on)
		al_draw_scaled_bitmap(game_backgrounds.game_background_up, 0, 0, al_get_bitmap_width(game_backgrounds.game_background_up), al_get_bitmap_height(game_backgrounds.game_background_up),
			0, 0, width, start_ground + blocksize, 0);
	else
		al_draw_tinted_scaled_bitmap(game_backgrounds.game_background_up, tint_color, 0, 0, al_get_bitmap_width(game_backgrounds.game_background_up), al_get_bitmap_height(game_backgrounds.game_background_up),
			0, 0, width, start_ground + blocksize, 0);
	// rendering parralax effect
	if (color_on)
		BG.velX = 6;
	else
		BG.velX = 1;
	DrawBackground(BG);
	// rendering game down_background
	if (!color_on)
		al_draw_scaled_bitmap(game_backgrounds.game_background_down, 0, height / 1.5, al_get_bitmap_width(game_backgrounds.game_background_down), al_get_bitmap_height(game_backgrounds.game_background_down),
			0, start_ground + blocksize, width, height, 0);
	else
		al_draw_tinted_scaled_bitmap(game_backgrounds.game_background_down, tint_color, 0, height / 1.5, al_get_bitmap_width(game_backgrounds.game_background_down), al_get_bitmap_height(game_backgrounds.game_background_down),
			0, start_ground + blocksize, width, height, 0);
	// rendering avatar
	if (!collision)
	{
		if (!color_on)
			al_draw_rotated_bitmap(avatar.image, 20, 20, avatar.x + 20, avatar.y + 20, -angle, 0);
		else
			al_draw_tinted_rotated_bitmap(avatar.image, tint_color, 20, 20, avatar.x + 20, avatar.y + 20, -angle, 0);
	}
	// rendering map
	drawmap(map, sizeX, map_speed, coordsX, coordsY, avatar, collide_objects, collision, ground, start_ground, color_on);
	if (!collision)
	{
		angle -= 0.1;
		if (angle <= 1)
			angle -= 0.1;
		if (angle <= 0)
			angle = 100;
	}
}