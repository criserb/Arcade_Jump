#include "all_headers.h"

const int initial_speed = 5;
int speed = initial_speed; // speed of moving map
int start_ground;
int ground;
const int NUM_EXPLOSIONS = 32;

void redraw(player &player, int **map, int *coordsX, int *coordsY, c_object *collide_objects, backgrounds backgrounds, float &angle, bool &collision, parallax_image BG)
{
	// rendering game up_background
	al_draw_scaled_bitmap(backgrounds.game_background_up, 0, 0, al_get_bitmap_width(backgrounds.game_background_up), al_get_bitmap_height(backgrounds.game_background_up),
		0, 0, width, start_ground + blocksize, 0);
	// rendering parralax effect
	DrawBackground(BG);
	// rendering game down_background
	al_draw_scaled_bitmap(backgrounds.game_background_down, 0, height / 1.5, al_get_bitmap_width(backgrounds.game_background_down), al_get_bitmap_height(backgrounds.game_background_down),
		0, start_ground + blocksize, width, height, 0);
	// rendering player
	//al_draw_bitmap(player.image, player.x, player.y + (blocksize - player.h), 0);
	al_draw_rotated_bitmap(player.image, 20, 20, player.x + 20, player.y + 20, -angle, 0);
	// rendering map
	drawmap(map, coordsX, coordsY, player, collide_objects, collision);
	if (!collision)
	{
		angle -= 0.1;
		if (angle <= 1)
			angle -= 0.1;
		if (angle <= 0)
			angle = 100;
	}
}

void game(void)
{
	bool collision = false;
	bool done = false;
	bool main_menu_on = false;
	bool replay = false;
	float jump_speed = 12.42;
	start_ground = height - 60 - blocksize;
	ground = start_ground;
	bool jump = false;
	float angle = 100;


	// bg_images images
	parallax_image BG;
	ALLEGRO_BITMAP *bgImage = resize("Graphics/star1.png", width, height);
	InitBackground(BG, 0, 0, 1, 0, width, height, -1, 1, bgImage);

	//==============================================
	//BACKGROUNDS IMAGES
	//==============================================
	backgrounds backgrounds;
	backgrounds.game_background_up = al_load_bitmap("Graphics/Game_background1.jpg");
	backgrounds.game_background_down = al_load_bitmap("Graphics/Game_background2.jpg");
	explosion explosion;
	explosion.image = al_load_bitmap("Graphics/Explosion.png");

	//==============================================
	//BAR IMAGES AND FONT
	//==============================================
	ALLEGRO_FONT *progress = al_load_ttf_font("Arcade_Classic.ttf", 11, 0);
	ALLEGRO_BITMAP *bar = al_load_bitmap("Graphics/Bar.png");
	ALLEGRO_BITMAP *bar_background = al_load_bitmap("Graphics/Bar_background.png");

	//==============================================
	//COLLIDE OBJECTS
	//==============================================

	int elements = 3;
	c_object *collide_objects = new c_object[elements];
	// spike
	collide_objects[0].image = al_load_bitmap("Graphics/Spike.png");
	collide_objects[0].mask = Mask_New(collide_objects[0].image);
	// tile
	collide_objects[1].image = al_load_bitmap("Graphics/Tile.png");
	collide_objects[1].mask = Mask_New(collide_objects[1].image);
	// 180 degree spike
	collide_objects[2].image = al_load_bitmap("Graphics/Spike_reverse.png");
	collide_objects[2].mask = Mask_New(collide_objects[2].image);

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
	/* variables for moving map */
	// start of map
	float map_min = 0;
	// end of map
	float map_max = coordsX[sizeX - 1];

	//==============================================
	//GAME LOOP
	//==============================================

	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(fps_timer));

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
				ALLEGRO_BITMAP *pause_image = al_create_bitmap(width, height);
				al_set_target_bitmap(pause_image);
				redraw(player, map, coordsX, coordsY, collide_objects, backgrounds, angle, collision, BG);
				// progress
				al_draw_scaled_bitmap(bar_background, 1, 1, al_get_bitmap_width(bar_background), al_get_bitmap_height(bar_background), (width / 2) - 110, height - (height - 20), al_get_bitmap_width(bar_background), al_get_bitmap_height(bar_background), ALLEGRO_ALIGN_CENTER);
				al_draw_scaled_bitmap(bar, 0, 0, al_get_bitmap_width(bar), al_get_bitmap_height(bar), (width / 2) - 100, height - (height - 20), map_min / map_max*al_get_bitmap_width(bar), al_get_bitmap_height(bar), ALLEGRO_ALIGN_CENTER);
				al_draw_textf(progress, al_map_rgb(255, 255, 200), (width / 2) + 122, height - (height - 20), ALLEGRO_ALIGN_CENTER, "%.f%%", map_min / map_max * 100);
				al_pause_event_queue(event_queue, 1);
				al_set_target_backbuffer(display);
				if (pause(pause_image))
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
		else if (ev.timer.source == fps_timer)
		{
			//==============================================
			//GAME UPDATE
			//==============================================

			UpdateBackground(BG);

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
			//==============================================
			//RENDER
			//==============================================
			redraw(player, map, coordsX, coordsY, collide_objects, backgrounds, angle, collision, BG);
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
				ALLEGRO_BITMAP *game_end = al_create_bitmap(width, height);
				al_set_target_bitmap(game_end);
				redraw(player, map, coordsX, coordsY, collide_objects, backgrounds, angle, collision, BG);
				al_set_target_backbuffer(display);
				end_of_map(game_end);
				al_destroy_bitmap(game_end);
				al_rest(0.5);
				done = true;
				main_menu_on = true;
			}
			//==============================================
			//IF COLLISION
			//==============================================
			if (collision)
			{
				al_pause_event_queue(event_queue, 1);
				for (int i = 0; i < NUM_EXPLOSIONS - 1; ++i)
				{
					redraw(player, map, coordsX, coordsY, collide_objects, backgrounds, angle, collision, BG);
					drawExplosions(explosion, NUM_EXPLOSIONS, player);
					al_flip_display();
					al_clear_to_color(al_map_rgb(0, 0, 0));
				}
				ALLEGRO_BITMAP *collision_image = al_create_bitmap(width, height);
				al_set_target_bitmap(collision_image);
				redraw(player, map, coordsX, coordsY, collide_objects, backgrounds, angle, collision, BG);
				drawExplosions(explosion, NUM_EXPLOSIONS, player);
				al_set_target_backbuffer(display);
				if (crash(collision_image) == 'r')
				{
					done = true;
					replay = true;
				}
				else
				{
					done = true;
					main_menu_on = true;
				}
				al_destroy_bitmap(collision_image);
			}
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
			map_min += speed;
		}
	}
	/* destroying objects */
	// destroying backgrounds
	al_destroy_bitmap(backgrounds.game_background_up);
	al_destroy_bitmap(backgrounds.game_background_down);
	al_destroy_event_queue(event_queue);
	al_destroy_font(progress);
	al_destroy_bitmap(bar);
	al_destroy_bitmap(bar_background);
	al_destroy_bitmap(player.image);
	Mask_Delete(player.mask);
	// destroying bg_images
	al_destroy_bitmap(bgImage);
	al_destroy_bitmap(explosion.image);
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
	if (replay == true) game();
}