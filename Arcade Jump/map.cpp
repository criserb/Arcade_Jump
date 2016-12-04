#include "All_headers.h"

int sizeX; // elements it the map

void drawmap(int **map, int *coordsX, int *coordsY, player player)
{
	for (int i = 0; i < sizeX; ++i)
	{
		switch (map[i][1])
		{
		case 1: al_draw_triangle(coordsX[i], coordsY[i], coordsX[i] + blocksize, coordsY[i], coordsX[i] + blocksize / 2, coordsY[i] - blocksize,
			al_map_rgb(255, 255, 255), 0);
			break;
		case 2: al_draw_rectangle(coordsX[i], coordsY[i], coordsX[i] + blocksize, coordsY[i] - blocksize, al_map_rgb(255, 255, 255), 0);
			break;
		case 3: al_draw_triangle(coordsX[i], coordsY[i], coordsX[i] + blocksize, coordsY[i], coordsX[i] + blocksize / 2, coordsY[i] + blocksize,
			al_map_rgb(255, 255, 255), 0);
			break;
		case 4:
			al_draw_triangle(coordsX[i] - blocksize, coordsY[i] - blocksize / 2, coordsX[i], coordsY[i] - blocksize, coordsX[i], coordsY[i],
				al_map_rgb(255, 255, 255), 0);
			break;
		}
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
