#include "all_headers.h"


void drawExplosions(explosion &explosion, int size, player &player)
{
			al_draw_bitmap_region(explosion.image, explosion.fx, explosion.fy, explosion.frame_width,
				explosion.frame_height, player.x-explosion.frame_width/3, player.y - explosion.frame_height /3, 0);
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
