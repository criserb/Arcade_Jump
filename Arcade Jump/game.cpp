#include "all_headers.h"

const float initial_speed = 4.42;
float speed = initial_speed; // speed of moving map
int ground;

void game(void)
{
	bool done = false;
	bool main_menu_on = false;
	float jump_speed = 12.42;
	const int start_ground = height - 60 - blocksize;
	ground = start_ground;
	bool jump = false;

	ALLEGRO_BITMAP *pause_background = al_load_bitmap("Graphics/Pause_background.png");
	ALLEGRO_BITMAP *game_background = al_load_bitmap("Graphics/Game_background.jpg");
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	ALLEGRO_FONT *progress = al_load_ttf_font("Arcade_Classic.ttf", 11, 0);
	ALLEGRO_BITMAP *bar = al_load_bitmap("Graphics/Bar.png");
	ALLEGRO_BITMAP *bar_background = al_load_bitmap("Graphics/Bar_background.png");

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(fps_timer));

	//==============================================
	//COLLIDE OBJECTS
	//==============================================

	int elements = 2;
	c_object *collide_objects = new c_object[elements];
	// spike
	collide_objects[0].image = al_load_bitmap("Graphics/Spike.png");
	collide_objects[0].mask = Mask_New(collide_objects[0].image);
	// tile
	collide_objects[1].image = al_load_bitmap("Graphics/Tile.png");
	collide_objects[1].mask = Mask_New(collide_objects[1].image);

	//==============================================
	//PLAYER
	//==============================================

	player player;
	player.image = al_load_bitmap("Graphics/Avatar.png");
	player.mask = Mask_New(player.image);
	player.w = al_get_bitmap_width(player.image);
	player.h = al_get_bitmap_height(player.image);
	player.y = start_ground;

	//==============================================
	//MAP
	//==============================================

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
		case 0: coordsY[i] = start_ground; break;
		case 1: coordsY[i] = start_ground - blocksize; break;
		case 2: coordsY[i] = start_ground - 2 * blocksize; break;
		case 3: coordsY[i] = start_ground - 3 * blocksize; break;
		case 4: coordsY[i] = start_ground - 4 * blocksize; break;
		case 5: coordsY[i] = start_ground - 5 * blocksize; break;
		case 6: coordsY[i] = start_ground - 6 * blocksize; break;
		case 7: coordsY[i] = start_ground - 7 * blocksize; break;
		}
	}
	// variables for moving map
	float map_max = coordsX[sizeX - 1];
	float map_min = 0;

	//==============================================
	//GAME LOOP
	//==============================================

	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_SPACE:
			{
				if (jump)
				{
					player.vely = -jump_speed;
					jump = false;
				}
				break;
			}
			case ALLEGRO_KEY_A:
			{	// speed
				speed += 4;
				break;
			}
			case ALLEGRO_KEY_S:
			{	// speed
				if (speed > initial_speed)
					speed -= 4;
				break;
			}
			case ALLEGRO_KEY_D:
			{	// speed
				speed = initial_speed;
				break;
			}
			case ALLEGRO_KEY_ESCAPE:
			{	//pause
				// rendering background
				al_draw_scaled_bitmap(game_background, 0, 0, al_get_bitmap_width(game_background), al_get_bitmap_height(game_background), 0, 0, width, height, 0);
				// rendering player
				al_draw_bitmap(player.image, player.x, player.y+(blocksize - player.h), 0);
				// rendering line start_ground
				al_draw_line(0, start_ground + blocksize, width, start_ground + blocksize, al_map_rgb(0, 0, 0), 0);
				// rendering objects
				drawmap(map, coordsX, coordsY, player, collide_objects);
				// progress
				al_draw_scaled_bitmap(bar_background, 1, 1, al_get_bitmap_width(bar_background), al_get_bitmap_height(bar_background), (width / 2) - 110, height - (height - 20), al_get_bitmap_width(bar_background), al_get_bitmap_height(bar_background), ALLEGRO_ALIGN_CENTER);
				al_draw_scaled_bitmap(bar, 0, 0, al_get_bitmap_width(bar), al_get_bitmap_height(bar), (width / 2) - 100, height - (height - 20), map_min / map_max*al_get_bitmap_width(bar), al_get_bitmap_height(bar), ALLEGRO_ALIGN_CENTER);
				al_draw_textf(progress, al_map_rgb(255, 255, 200), (width / 2) + 122, height - (height - 20), ALLEGRO_ALIGN_CENTER, "%.f%%", map_min / map_max * 100);
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
		//==============================================
		//GAME UPDATE & RENDER
		//==============================================
		else if (ev.timer.source == fps_timer)
		{
			//==============================================
			//JUMP
			//==============================================
			if (!jump)
				player.vely += player.gravity;
			else
				player.vely = 0;
			player.y += player.vely;
			jump = (player.y >= ground);
			if (jump)
			{
				player.y = ground;
			}
			// rendering background
			al_draw_scaled_bitmap(game_background, 0, 0, al_get_bitmap_width(game_background), al_get_bitmap_height(game_background), 0, 0, width, height, 0);
			// rendering player
			//al_draw_rectangle(player.x, player.y, player.x + player.w, player.y - player.h, al_map_rgb(0, 0, 0), 0);
			al_draw_bitmap(player.image, player.x, player.y + (blocksize - player.h), 0);
			// rendering line start_ground
			al_draw_line(0, start_ground + blocksize, width, start_ground + blocksize, al_map_rgb(0, 0, 0), 0);
			// rendering objects
			drawmap(map, coordsX, coordsY, player, collide_objects);
			// progress
			if (map_min <= map_max)
			{
				al_draw_scaled_bitmap(bar_background, 1, 1, al_get_bitmap_width(bar_background), al_get_bitmap_height(bar_background), (width / 2) - 110, height - (height - 20), al_get_bitmap_width(bar_background), al_get_bitmap_height(bar_background), ALLEGRO_ALIGN_CENTER);
				al_draw_scaled_bitmap(bar, 0, 0, al_get_bitmap_width(bar), al_get_bitmap_height(bar), (width / 2) - 100, height - (height - 20), map_min / map_max*al_get_bitmap_width(bar), al_get_bitmap_height(bar), ALLEGRO_ALIGN_CENTER);
				al_draw_textf(progress, al_map_rgb(255, 255, 200), (width / 2) + 122, height - (height - 20), ALLEGRO_ALIGN_CENTER, "%.f%%", map_min / map_max * 100);
			}
			else
			{
				// end of map
				done = true;
				main_menu_on = true;
			}
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
			map_min += speed;
		}
	}
	// destroying objects
	al_destroy_bitmap(pause_background);
	al_destroy_event_queue(event_queue);
	al_destroy_font(progress);
	al_destroy_bitmap(bar);
	al_destroy_bitmap(bar_background);
	al_destroy_bitmap(game_background);
	al_destroy_bitmap(player.image);
	Mask_Delete(player.mask);
	for (int i = 0; i < elements; ++i)
	{
		al_destroy_bitmap(collide_objects[i].image);
		Mask_Delete(collide_objects[i].mask);
	}
	delete[] collide_objects;
	for (int i = 0; i < sizeX; ++i) {
		delete[] map[i];
	}
	delete[] map;
	delete[] coordsX;
	delete[] coordsY;
	filemap.close();
	if (main_menu_on == true) menu();
}