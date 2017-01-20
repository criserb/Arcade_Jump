#include "all_headers.h"

ALLEGRO_COLOR tint_color;

void game(void)
{
	tint_color = al_map_rgb(255, 40, 40);
	const int initial_speed = 5;
	const int NUM_EXPLOSIONS = 32;
	bool collision = false;
	bool done = false;
	bool main_menu_on = false;
	bool replay = false;
	float jump_speed = 12.42;
	int start_ground = height - 60 - blocksize;
	int ground = start_ground;
	bool jump = false;
	float angle = 100;
	int map_speed = initial_speed; // map_speed of moving map
	bool color_on = false;
	ALLEGRO_SAMPLE *sample1 = al_load_sample("Sounds/Arcade_background_music.ogg");
	ALLEGRO_SAMPLE_INSTANCE *music = al_create_sample_instance(sample1);
	al_attach_sample_instance_to_mixer(music, al_get_default_mixer());
	//==============================================
	//ATTEMPT COUNT
	//==============================================
	ALLEGRO_FONT *att_font = al_load_ttf_font("Arcade_Classic.ttf", 32, 0);
	int att_coordx = 0;

	//==============================================
	//PARALLAX IMAGES
	//==============================================
	parallax_image BG;
	ALLEGRO_BITMAP *bgImage = resize_bitmap("Graphics/star1.png", width, height);
	InitBackground(BG, 0, 0, 1, 0, width, height, -1, 1, bgImage);

	//==============================================
	//BACKGROUNDS IMAGES
	//==============================================
	game_backgrounds game_backgrounds;
	game_backgrounds.game_background_up = al_load_bitmap("Graphics/Game_background1.jpg");
	game_backgrounds.game_background_down = al_load_bitmap("Graphics/Game_background2.jpg");
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

	avatar avatar;
	avatar.image = al_load_bitmap("Graphics/Star_avatar.png");
	avatar.mask = Mask_New(avatar.image);
	avatar.w = al_get_bitmap_width(avatar.image);
	avatar.h = al_get_bitmap_height(avatar.image);
	avatar.y = start_ground;

	//==============================================
	//MAP
	//==============================================
	int sizeX; // elements in the map

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
	ALLEGRO_TIMER *fps_timer = al_create_timer(1.0 / fps);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(fps_timer));
	al_start_timer(fps_timer);

	al_stop_samples();
	al_play_sample_instance(music);

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
					avatar.vely = -jump_speed;
					jump = false;
				}
				break;
			}
			case ALLEGRO_KEY_A:
			{	// map_speed
				map_speed += 4;
				break;
			}
			case ALLEGRO_KEY_S:
			{	// map_speed
				if (map_speed > initial_speed)
					map_speed -= 4;
				break;
			}
			case ALLEGRO_KEY_D:
			{	// map_speed
				map_speed = initial_speed;
				break;
			}
			case ALLEGRO_KEY_ESCAPE:
			{	//pause
				unsigned int sample_position = al_get_sample_instance_position(music);
				al_set_sample_instance_playing(music, 0);
				ALLEGRO_BITMAP *pause_image = al_create_bitmap(width, height);
				al_set_target_bitmap(pause_image);
				redraw(avatar, map, sizeX, map_speed, ground, start_ground, coordsX, coordsY, collide_objects, game_backgrounds, angle, collision, BG, color_on);
				// attempt
				if (att_coordx > -height)
				{
					al_draw_textf(att_font, al_map_rgb(color[0], color[1], color[2]), (width / 2) + att_coordx, height / 2 - height / 4, ALLEGRO_ALIGN_CENTER, "ATTEMPT : %d", att_count);
					att_coordx -= map_speed / 2;
				}
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
				{
					al_pause_event_queue(event_queue, 0);
					al_set_sample_instance_position(music, sample_position);
					al_set_sample_instance_playing(music, 1);
				}
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
				avatar.vely += avatar.gravity;
			else
				avatar.vely = 0;
			avatar.y += avatar.vely;
			jump = (avatar.y >= ground);
			if (jump)
			{
				avatar.y = ground;
			}
			//==============================================
			//RENDER
			//==============================================
			redraw(avatar, map, sizeX, map_speed, ground, start_ground, coordsX, coordsY, collide_objects, game_backgrounds, angle, collision, BG, color_on);
			// attempt
			if (att_coordx > -height)
			{
				al_draw_textf(att_font, al_map_rgb(color[0], color[1], color[2]), (width / 2) + att_coordx, height / 2 - height / 4, ALLEGRO_ALIGN_CENTER, "ATTEMPT : %d", att_count);
				if (att_count % 5 == 0)
					al_draw_text(att_font, al_map_rgb(color[0], color[1], color[2]), (width / 2) + att_coordx, height / 2 - (height / 4) + 40, ALLEGRO_ALIGN_CENTER, "C'MON YOU CAN DO IT!");
				att_coordx -= map_speed / 2;
			}
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
				redraw(avatar, map, sizeX, map_speed, ground, start_ground, coordsX, coordsY, collide_objects, game_backgrounds, angle, collision, BG, color_on);
				al_set_target_backbuffer(display);
				end_of_map(game_end);
				al_destroy_bitmap(game_end);
				done = true;
				main_menu_on = true;
			}
			//==============================================
			//IF COLLISION
			//==============================================
			if (collision)
			{
				al_pause_event_queue(event_queue, 1);
				ALLEGRO_SAMPLE *crash_sound = al_load_sample("Sounds/Plastic_crash.ogg");
				al_reserve_samples(1);
				al_stop_sample_instance(music);
				al_play_sample(crash_sound, 1, 0, 0.8, ALLEGRO_PLAYMODE_ONCE, 0);
				for (int i = 0; i < NUM_EXPLOSIONS - 1; ++i)
				{
					redraw(avatar, map, sizeX, map_speed, ground, start_ground, coordsX, coordsY, collide_objects, game_backgrounds, angle, collision, BG, color_on);
					drawExplosions(explosion, 256, 256, NUM_EXPLOSIONS, avatar, color_on);
					al_flip_display();
					al_clear_to_color(al_map_rgb(0, 0, 0));
				}
				ALLEGRO_BITMAP *collision_image = al_create_bitmap(width, height);
				al_set_target_bitmap(collision_image);
				redraw(avatar, map, sizeX, map_speed, ground, start_ground, coordsX, coordsY, collide_objects, game_backgrounds, angle, collision, BG, color_on);
				drawExplosions(explosion, 256, 256, NUM_EXPLOSIONS, avatar, color_on);
				al_set_target_backbuffer(display);
				if (crash(collision_image) == 'r')
				{
					done = true;
					replay = true;
					++att_count;
				}
				else
				{
					done = true;
					main_menu_on = true;
				}
				al_destroy_sample(crash_sound);
				al_destroy_bitmap(collision_image);
			}
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
			map_min += map_speed;
			if ((map_min / map_max * 100) >= 59)
				color_on = true;
		}
	}
	//==============================================
	//DESTROYING OBJECTS
	//==============================================
	// destroying game_backgrounds
	al_destroy_bitmap(game_backgrounds.game_background_up);
	al_destroy_bitmap(game_backgrounds.game_background_down);
	al_destroy_event_queue(event_queue);
	al_destroy_font(progress);
	al_destroy_font(att_font);
	al_destroy_bitmap(bar);
	al_destroy_bitmap(bar_background);
	al_destroy_bitmap(avatar.image);
	Mask_Delete(avatar.mask);
	// destroying bg_images
	al_destroy_bitmap(bgImage);
	al_destroy_bitmap(explosion.image);
	al_destroy_timer(fps_timer);
	al_destroy_sample_instance(music);
	al_destroy_sample(sample1);
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