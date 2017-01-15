#include "all_headers.h"

char crash(ALLEGRO_BITMAP *collision_image)
{
	int r[] = { 196,196 }, g[] = { 119,119 }, b[] = { 89,89 }; // colors of pressed buttons
	bool done = false;
	bool replay = false;
	bool main_menu_on = false;

	int cord_cursor_x = (width / 2) - 160;
	int cord_cursor_y = ((height / 2) - 4) + 30;

	ALLEGRO_EVENT_QUEUE *crash_event_queue = al_create_event_queue();
	ALLEGRO_FONT *crash_title = al_load_ttf_font("Arcade_Classic.ttf", 42, 0);
	ALLEGRO_FONT *crash_item = al_load_ttf_font("Arcade_Classic.ttf", 18, 0);
	ALLEGRO_SAMPLE *click = al_load_sample("Sounds/Click.ogg"); ;
	ALLEGRO_BITMAP *cursor = al_load_bitmap("Graphics/Cursor_small.png");
	ALLEGRO_BITMAP *pause_background = al_load_bitmap("Graphics/Pause_background.png");

	al_register_event_source(crash_event_queue, al_get_keyboard_event_source());
	al_register_event_source(crash_event_queue, al_get_timer_event_source(fps_timer));

	while (!done)
	{
		ALLEGRO_EVENT crash_ev;
		al_wait_for_event(crash_event_queue, &crash_ev);
		if (crash_ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (crash_ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				al_stop_samples();
				al_play_sample(click, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
				if (cord_cursor_y > ((height / 2) - 4) + 30)
					cord_cursor_y -= 30;
				break;
			case ALLEGRO_KEY_DOWN:
				al_stop_samples();
				al_play_sample(click, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
				if (cord_cursor_y < ((height / 2) - 4) + 60)
					cord_cursor_y += 30;
				break;
			case ALLEGRO_KEY_ENTER:
				al_stop_samples();
				al_play_sample(click, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
				if (cord_cursor_y == ((height / 2) - 4) + 30)
				{
					// replay
					done = true;
					replay = true;
				}
				else if (cord_cursor_y == ((height / 2) - 4) + 60)
				{
					// back to main menu
					done = true;
					main_menu_on= true;
				}
				break;
			}
		}
		else if (crash_ev.type == ALLEGRO_EVENT_TIMER)
		{
			if (cord_cursor_y == ((height / 2) - 4) + 30)
				color_press(r, g, b, 0, 2);
			if (cord_cursor_y == ((height / 2) - 4) + 60)
				color_press(r, g, b, 1, 2);
			// rendering
			al_draw_bitmap(collision_image, 0, 0, 0);
			al_draw_bitmap(pause_background, 0, 0, 0);
			al_draw_text(crash_title, al_map_rgb(color[0], color[1], color[2]), width / 2, (height / 2) - 120, ALLEGRO_ALIGN_CENTRE, "YOU LOST");
			al_draw_text(crash_item, al_map_rgb(r[0], g[0], b[0]), width / 2, (height / 2) + 30, ALLEGRO_ALIGN_CENTRE, "PLAY AGAIN");
			al_draw_text(crash_item, al_map_rgb(r[1], g[1], b[1]), width / 2, (height / 2) + 60, ALLEGRO_ALIGN_CENTRE, "BACK TO MAIN MENU");
			al_draw_bitmap(cursor, cord_cursor_x, cord_cursor_y, 0);
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}
	// destroying objects
	al_destroy_bitmap(pause_background);
	al_destroy_font(crash_item);
	al_destroy_font(crash_title);
	al_destroy_event_queue(crash_event_queue);
	al_destroy_sample(click);
	al_destroy_bitmap(cursor);
	if (main_menu_on)
		return 'm';
	else if (replay)
		return 'r';
}