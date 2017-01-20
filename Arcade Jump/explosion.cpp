#include "all_headers.h"


void drawExplosions(explosion &explosion, int frame_width, int frame_height, int size, avatar &avatar, bool color_on)
{
	explosion.frame_width = frame_width;
	explosion.frame_height = frame_height;
	if (!color_on)
		al_draw_bitmap_region(explosion.image, explosion.fx, explosion.fy, explosion.frame_width,
			explosion.frame_height, avatar.x - explosion.frame_width / 3, avatar.y - explosion.frame_height / 3, 0);
	else
		al_draw_tinted_bitmap_region(explosion.image, tint_color, explosion.fx, explosion.fy, explosion.frame_width,
			explosion.frame_height, avatar.x - explosion.frame_width / 3, avatar.y - explosion.frame_height / 3, 0);
	// frames delay
	al_rest(0.05);

	explosion.fx += explosion.frame_width;

	++explosion.count;
	if (explosion.count == 8)
	{
		explosion.count = 0;
		explosion.fy += explosion.frame_height;
		explosion.fx = 0;
	}
}
