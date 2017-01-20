#include "all_headers.h"

int color[] = { 255, 240, 110 };

// menu variables
int att_count;

// menu
void menu(void)
{
	int r[] = { 196,196,196,196,196,196 }, g[] = { 119,119,119,119,119,119 }, b[] = { 89,89,89,89,89,89 }; // colors of pressed buttons
	bool done = false;
	bool game_on = false;
	bool settings_on = false;

	int cord_cursor_x = (width / 2) - 120;
	int cord_cursor_y = ((height / 2) - 4) + 30;

	ALLEGRO_BITMAP *cursor = al_load_bitmap("Graphics/Cursor_small.png");
	ALLEGRO_BITMAP *menu_background = al_load_bitmap("Graphics/Menu_background.jpg");
	ALLEGRO_FONT *menu_item = al_load_ttf_font("Arcade_Classic.ttf", 18, 0);
	ALLEGRO_FONT *credit = al_load_ttf_font("Arcade_Classic.ttf", 10, 0);
	ALLEGRO_BITMAP *logo = al_load_bitmap("Graphics/Logo.png");
	ALLEGRO_SAMPLE *click = al_load_sample("Sounds/Click.ogg");
	ALLEGRO_SAMPLE *swish = al_load_sample("Sounds/Swish.ogg");
	ALLEGRO_EVENT_QUEUE *menu_event_queue = al_create_event_queue();

	al_reserve_samples(1);

	al_register_event_source(menu_event_queue, al_get_keyboard_event_source());

	while (!done)
	{
		//==============================================
		//CUROSR POSITION
		//==============================================
		if (cord_cursor_y == ((height / 2) - 4) + 30)
			color_press(r, g, b, 0, 3);
		if (cord_cursor_y == ((height / 2) - 4) + 60)
			color_press(r, g, b, 1, 3);
		if (cord_cursor_y == ((height / 2) - 4) + 90)
			color_press(r, g, b, 2, 3);
		//==============================================
		//RENDERING
		//==============================================
		al_draw_scaled_bitmap(menu_background, 0, 0, al_get_bitmap_width(menu_background), al_get_bitmap_height(menu_background), 0, 0, width, height, 0);
		al_draw_scaled_bitmap(logo, 0, 0, al_get_bitmap_width(logo), al_get_bitmap_height(logo), width / 4, 0, width / 2, height / 2, 0);
		al_draw_text(menu_item, al_map_rgb(r[0], g[0], b[0]), width / 2, (height / 2) + 30, ALLEGRO_ALIGN_CENTRE, "START GAME");
		al_draw_text(menu_item, al_map_rgb(r[1], g[1], b[1]), width / 2, (height / 2) + 60, ALLEGRO_ALIGN_CENTRE, "SETTINGS");
		al_draw_text(menu_item, al_map_rgb(r[2], g[2], b[2]), width / 2, (height / 2) + 90, ALLEGRO_ALIGN_CENTRE, "EXIT");
		al_draw_text(credit, al_map_rgb(color[0], color[1], color[2]), 20, height - 20, ALLEGRO_ALIGN_LEFT, "SOUND EFFECTS FROM: HTTP://WWW.FREESFX.CO.UK");
		al_draw_bitmap(cursor, cord_cursor_x, cord_cursor_y, 0);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));

		ALLEGRO_EVENT menu_ev;
		al_wait_for_event(menu_event_queue, &menu_ev);
		if (menu_ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (menu_ev.keyboard.keycode)
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
				if (cord_cursor_y < ((height / 2) - 4) + 90)
					cord_cursor_y += 30;
				break;
			case ALLEGRO_KEY_ENTER:
				al_stop_samples();
				al_play_sample(click, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
				if (cord_cursor_y == ((height / 2) - 4) + 30)
				{
					// fading screen
					al_stop_samples();
					al_play_sample(swish, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					al_rest(0.4);
					// start game
					done = true;
					game_on = true;
					att_count = 1;
				}
				else if (cord_cursor_y == ((height / 2) - 4) + 60)
				{
					// settings
					settings_on = true;
					done = true;
					cord_cursor_x = (width / 2) - 120;
					cord_cursor_y = ((height / 2) - 4) + 30;
				}
				else if (cord_cursor_y == ((height / 2) - 4) + 90)
				{
					done = true;
				}
				break;
			case ALLEGRO_KEY_ESCAPE:
			{
				al_stop_samples();
				al_play_sample(click, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
				done = true;
				break;
			}
			}
		}
	}
	// destroying objects
	al_destroy_font(menu_item);
	al_destroy_font(credit);
	al_destroy_bitmap(menu_background);
	al_destroy_bitmap(cursor);
	al_destroy_bitmap(logo);
	al_destroy_event_queue(menu_event_queue);
	al_destroy_sample(click);
	al_destroy_sample(swish);
	if (game_on == true) game();
	if (settings_on == true) settings(cord_cursor_x, cord_cursor_y);
}

// settings options
void settings(int &cord_cursor_x, int &cord_cursor_y)
{
	int r[] = { 196,196,196,196,196,196 }, g[] = { 119,119,119,119,119,119 }, b[] = { 89,89,89,89,89,89 }; // colors of pressed buttons
	bool menu_on = false;
	bool done = false;
	ALLEGRO_MONITOR_INFO info;
	ALLEGRO_BITMAP *cursor = al_load_bitmap("Graphics/Cursor_small.png");
	ALLEGRO_BITMAP *menu_background = al_load_bitmap("Graphics/Menu_background.jpg");
	ALLEGRO_FONT *menu_item = al_load_ttf_font("Arcade_Classic.ttf", 18, 0);
	ALLEGRO_SAMPLE *click = al_load_sample("Sounds/Click.ogg");
	ALLEGRO_EVENT_QUEUE *menu_event_queue = al_create_event_queue();
	ALLEGRO_FONT *settings_item = al_load_ttf_font("Arcade_Classic.ttf", 18, 0);
	ALLEGRO_FONT *escape = al_load_ttf_font("Arcade_Classic.ttf", 12, 0);

	cord_cursor_x = (width / 2) - 120;
	cord_cursor_y = ((height / 2) - 4) + 30;

	al_register_event_source(menu_event_queue, al_get_keyboard_event_source());

	while (!done)
	{
		//==============================================
		//CUROSR POSITION
		//==============================================
		if (cord_cursor_y == ((height / 2) - 4) + 30)
			color_press(r, g, b, 0, 6);
		else if (cord_cursor_y == ((height / 2) - 4) + 60)
			color_press(r, g, b, 1, 6);
		else if (cord_cursor_y == ((height / 2) - 4) + 90)
			color_press(r, g, b, 2, 6);
		else if (cord_cursor_y == ((height / 2) - 4) + 120)
			color_press(r, g, b, 3, 6);
		else if (cord_cursor_y == ((height / 2) - 4) + 150)
			color_press(r, g, b, 4, 6);
		else if (cord_cursor_y == ((height / 2) - 4) + 180)
			color_press(r, g, b, 5, 6);
		//==============================================
		//RENDERING
		//==============================================
		al_draw_scaled_bitmap(menu_background, 0, 0, al_get_bitmap_width(menu_background), al_get_bitmap_height(menu_background), 0, 0, width, height, 0);
		al_draw_text(settings_item, al_map_rgb(r[0], g[0], b[0]), width / 2, (height / 2) + 30, ALLEGRO_ALIGN_CENTRE, "FULLSCREEN");
		al_draw_text(settings_item, al_map_rgb(r[1], g[1], b[1]), width / 2, (height / 2) + 60, ALLEGRO_ALIGN_CENTRE, "WINDOWED");
		al_draw_text(settings_item, al_map_rgb(r[2], g[2], b[2]), width / 2, (height / 2) + 90, ALLEGRO_ALIGN_CENTRE, "640x480");
		al_draw_text(settings_item, al_map_rgb(r[3], g[3], b[3]), width / 2, (height / 2) + 120, ALLEGRO_ALIGN_CENTRE, "800x600");
		al_draw_text(settings_item, al_map_rgb(r[4], g[4], b[4]), width / 2, (height / 2) + 150, ALLEGRO_ALIGN_CENTRE, "1280x720");
		al_draw_text(settings_item, al_map_rgb(r[5], g[5], b[5]), width / 2, (height / 2) + 180, ALLEGRO_ALIGN_CENTRE, "1920x1080");
		al_draw_bitmap(cursor, cord_cursor_x, cord_cursor_y, 0);
		al_draw_bitmap(cursor, 0, height - 30, ALLEGRO_FLIP_HORIZONTAL);
		al_draw_text(escape, al_map_rgb(color[0], color[1], color[2]), 30, height - 25, ALLEGRO_ALIGN_LEFT, "PRESS ESC TO BACK");
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));

		ALLEGRO_EVENT settings_ev;
		al_wait_for_event(menu_event_queue, &settings_ev);

		if (settings_ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (settings_ev.keyboard.keycode)
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
				if (cord_cursor_y < ((height / 2) - 4) + 180)
					cord_cursor_y += 30;
				break;
			case ALLEGRO_KEY_ENTER:
				al_stop_samples();
				al_play_sample(click, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
				if (cord_cursor_y == ((height / 2) - 4) + 30)
				{
					// option 1
					al_get_monitor_info(0, &info);
					width = info.x2 - info.x1; height = info.y2 - info.y1;
					cord_cursor_x = (width / 2) - 120;
					cord_cursor_y = ((height / 2) - 4) + 30;
					al_set_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, 1);
				}
				else if (cord_cursor_y == ((height / 2) - 4) + 60)
				{
					// option 2
					al_set_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, 0);
					width = al_get_display_width(display); height = al_get_display_height(display);
					cord_cursor_x = (width / 2) - 120;
					cord_cursor_y = ((height / 2) - 4) + 30;
					al_resize_display(display, width, height);
					al_set_window_position(display, 0, 0);
				}
				else if (cord_cursor_y == ((height / 2) - 4) + 90)
				{
					// option 3
					width = 640; height = 480;
					cord_cursor_x = (width / 2) - 120;
					cord_cursor_y = ((height / 2) - 4) + 30;
					al_resize_display(display, width, height);
					al_set_window_position(display, 0, 0);
				}
				else if (cord_cursor_y == ((height / 2) - 4) + 120)
				{
					// option 4
					width = 800; height = 600;
					cord_cursor_x = (width / 2) - 120;
					cord_cursor_y = ((height / 2) - 4) + 30;
					al_resize_display(display, width, height);
					al_set_window_position(display, 0, 0);
				}
				else if (cord_cursor_y == ((height / 2) - 4) + 150)
				{
					// option 5
					width = 1280; height = 720;
					cord_cursor_x = (width / 2) - 120;
					cord_cursor_y = ((height / 2) - 4) + 30;
					al_resize_display(display, width, height);
					al_set_window_position(display, 0, 0);
				}
				else if (cord_cursor_y == ((height / 2) - 4) + 180)
				{
					// option 6
					width = 1920; height = 1080;
					cord_cursor_x = (width / 2) - 120;
					cord_cursor_y = ((height / 2) - 4) + 30;
					al_resize_display(display, width, height);
					al_set_window_position(display, 0, 0);
				}
				break;
			case ALLEGRO_KEY_ESCAPE:
				al_stop_samples();
				al_play_sample(click, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
				menu_on = true;
				done = true;
				break;
			}
		}
	}
	al_destroy_font(menu_item);
	al_destroy_bitmap(menu_background);
	al_destroy_bitmap(cursor);
	al_destroy_event_queue(menu_event_queue);
	al_destroy_sample(click);
	al_destroy_font(settings_item);
	al_destroy_font(escape);
	if (menu_on)
		return menu();
}

// coloring buttons
void color_press(int *r, int *g, int *b, int selection, int max)
{
	for (int i = 0; i < max; ++i)
	{
		r[i] = color[0]; g[i] = color[1]; b[i] = color[2];
	}
	r[selection] = 255; g[selection] = 120; b[selection] = 0;
}