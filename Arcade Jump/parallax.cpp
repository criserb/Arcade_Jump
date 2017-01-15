#include "all_headers.h"

void InitBackground(parallax_image &back, float x, float y, float velx, float vely, int width, int height, int dirX, int dirY, ALLEGRO_BITMAP *image)
{
	back.x = x;
	back.y = y;
	back.velX = velx;
	back.velY = vely;
	back.width = width;
	back.height = height;
	back.dirX = dirX;
	back.dirY = dirY;
	back.image = image;
}
void UpdateBackground(parallax_image &back)
{
	back.x += back.velX * back.dirX;
	if (back.x + back.width <= 0)
		back.x = 0;
}
void DrawBackground(parallax_image &back)
{
	al_draw_bitmap(back.image, back.x, back.y, 0);

	if (back.x + back.width < width)
		al_draw_bitmap(back.image, back.x + back.width, back.y, 0);
}