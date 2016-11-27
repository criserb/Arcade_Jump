#include "All_headers.h"

struct player {
	int x = 0;
	int y = height - 60;
	int velx = 2;
	int vely = 0;
};

int sizeX;
const int bs = 40;
int speed = 3;

void game(void)
{
	player player;
	bool done = false;
	bool main_menu_on = false;
	bool jump_on = false;
	int ground = player.y;
	int c = 0; // jump count

	ALLEGRO_BITMAP *pause_background = al_load_bitmap("Pause_background.png");
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	ALLEGRO_TIMER *action_timer = al_create_timer(1.0);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(fps_timer));
	al_register_event_source(event_queue, al_get_timer_event_source(action_timer));

	al_start_timer(action_timer);

	std::ifstream filemap;
	filemap.open("map1.txt");
	filemap >> sizeX;

	int **map = new int*[sizeX];
	for (int i = 0; i < sizeX; ++i)
		map[i] = new int[3];
	int i = 0;
	int *coordsX = new int[sizeX];
	int *coordsY = new int[sizeX];
	loadmap(filemap, map);
	for (int i = 0; i < sizeX; ++i)
		coordsX[i] = width + map[i][0];
	for (int i = 0; i < sizeX; ++i)
	{
		switch (map[i][2])
		{
		case 0: coordsY[i] = ground; break;
		case 1: coordsY[i] = ground - 40; break;
		case 2: coordsY[i] = ground - 80; break;
		case 3: coordsY[i] = ground - 120; break;
		case 4: coordsY[i] = ground - 160; break;
		case 5: coordsY[i] = ground - 200; break;
		}
	}

	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_SPACE:
			{	// jump_on
				jump_on = true;
				break;
			}
			case ALLEGRO_KEY_A:
			{	// speed
				speed = 6;
				break;
			}
			case ALLEGRO_KEY_ESCAPE:
			{	//pause
				al_draw_line(0, ground, width, ground, al_map_rgb(255, 255, 255), 0);
				drawmap(map, coordsX, coordsY);
				al_draw_rectangle(player.x, player.y, player.x + bs, player.y - bs, al_map_rgb(255, 255, 255), 0);
				al_draw_bitmap(pause_background, 0, 0, 0);
				al_pause_event_queue(event_queue, 1);
				if (pause() == 'm')
				{
					done = true;
					main_menu_on = true;
				}
				else
					al_pause_event_queue(event_queue, 0);
				break;
			}
			}
		}
		if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_A:
			{	// speed
				speed = 3;
				break;
			}
			}
		}
		else if (ev.timer.source == fps_timer)
		{
			// rendering player
			al_draw_rectangle(player.x, player.y, player.x + bs, player.y - bs, al_map_rgb(255, 255, 255), 0);
			// rendering line ground
			al_draw_line(0, ground, width, ground, al_map_rgb(255, 255, 255), 0);
			// rendering objects
			drawmap(map, coordsX, coordsY);
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
		if (jump_on)
		{
			player.y -= 4;
			c += 5;
		}
		if (c == 100)
			jump_on = false;
		if (c > 0 && jump_on == false)
		{
			player.y += 4;
			c -= 5;
		}
	}
	// destroying objects
	al_destroy_bitmap(pause_background);
	al_destroy_timer(action_timer);
	al_destroy_event_queue(event_queue);
	for (int i = 0; i < sizeX; ++i) {
		delete[] map[i];
	}
	delete[] map;
	delete[] coordsX;
	delete[] coordsY;
	filemap.close();
	if (main_menu_on == true) menu();
}

void drawmap(int **map, int *coordsX, int *coordsY)
{
	ALLEGRO_BITMAP *triangle = al_load_bitmap("Triangle.png");
	for (int i = 0; i < sizeX; ++i)
	{
		switch (map[i][1])
		{
		case 1: al_draw_triangle(coordsX[i], coordsY[i], coordsX[i] + bs, coordsY[i], coordsX[i] + bs / 2, coordsY[i] - bs,
			al_map_rgb(255, 255, 255), 0);
			break;
		case 2: al_draw_rectangle(coordsX[i], coordsY[i], coordsX[i] + bs, coordsY[i] - bs, al_map_rgb(255, 255, 255), 0);
			break;
		case 3:
			al_draw_rectangle(coordsX[i], coordsY[i], coordsX[i] + bs, coordsY[i] - bs, al_map_rgb(255, 255, 255), 0);
			al_draw_triangle(coordsX[i], coordsY[i] - bs, coordsX[i] + bs, coordsY[i] - bs, coordsX[i] + bs / 2, coordsY[i] - 2 * bs,
				al_map_rgb(255, 255, 255), 0);
			break;
		case 4:
			al_draw_rectangle(coordsX[i], coordsY[i], coordsX[i] + bs, coordsY[i] - bs, al_map_rgb(255, 255, 255), 0);
			al_draw_triangle(coordsX[i], coordsY[i], coordsX[i] + bs, coordsY[i], coordsX[i] + bs / 2, coordsY[i] + bs - 5,
				al_map_rgb(255, 255, 255), 0);
			break;
		}
		coordsX[i] -= speed;
	}
	al_destroy_bitmap(triangle);
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
	{
		al_show_native_message_box(display, "Arcade Jump", "Error", "Error", "Error with map", ALLEGRO_MESSAGEBOX_WARN);
	}
}